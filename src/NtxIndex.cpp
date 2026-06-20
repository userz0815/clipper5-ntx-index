#include "../include/NtxIndex.h"
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <cctype>

NtxIndex::NtxIndex()
    : m_hFile(nullptr)
    , m_keyLength(0)
    , m_bUnique(false)
    , m_bReadonly(false)
    , m_bShared(false)
    , m_bIsOpen(false)
    , m_bModified(false)
    , m_bLocked(false)
    , m_curKeyValue(nullptr)
    , m_curDbfRecordNumber(0)
    , m_currentIndex(0)
{
    memset(&m_header, 0, sizeof(NtxHeader));
}

NtxIndex::~NtxIndex()
{
    CloseIndex();
    if (m_curKeyValue) {
        delete[] m_curKeyValue;
        m_curKeyValue = nullptr;
    }
}

int NtxIndex::CreateIndex(const char* IndexFileName, const char* KeyExpression, int KeyLength, bool bUnique)
{
    if (!IndexFileName || !KeyExpression) {
        return NTX_ERR_INVALID_PARAMS;
    }

    if (KeyLength <= 0 || KeyLength > NTX_KEY_MAX_LENGTH) {
        return NTX_ERR_INVALID_PARAMS;
    }

    // Check if file already exists
    FILE* test = fopen(IndexFileName, "rb");
    if (test) {
        fclose(test);
        return NTX_ERR_FILE_EXISTS;
    }

    // Create new file in binary write mode
    m_hFile = fopen(IndexFileName, "w+b");
    if (!m_hFile) {
        return NTX_ERR_FILE_OPEN;
    }

    m_fileName = IndexFileName;
    m_keyExpression = KeyExpression;
    m_keyLength = KeyLength;
    m_bUnique = bUnique;
    m_bReadonly = false;
    m_bShared = false;
    m_bIsOpen = true;
    m_bModified = true;
    m_indexTree.clear();

    // Initialize Clipper 5 compatible header
    if (InitializeHeader(KeyExpression, KeyLength, bUnique) != NTX_OK) {
        fclose(m_hFile);
        m_hFile = nullptr;
        m_bIsOpen = false;
        return NTX_ERR_FILE_WRITE;
    }

    // Write header to file
    if (WriteHeader() != NTX_OK) {
        fclose(m_hFile);
        m_hFile = nullptr;
        m_bIsOpen = false;
        return NTX_ERR_FILE_WRITE;
    }

    return NTX_OK;
}

int NtxIndex::OpenIndex(const char* IndexFileName, bool bReadonly, bool bShared)
{
    if (!IndexFileName) {
        return NTX_ERR_INVALID_PARAMS;
    }

    if (m_bIsOpen) {
        return NTX_ERR_FILE_OPEN;
    }

    // Open file in appropriate mode
    const char* mode = bReadonly ? "rb" : "r+b";
    m_hFile = fopen(IndexFileName, mode);
    if (!m_hFile) {
        return NTX_ERR_FILE_NOT_FOUND;
    }

    m_fileName = IndexFileName;
    m_bReadonly = bReadonly;
    m_bShared = bShared;
    m_bIsOpen = true;
    m_indexTree.clear();

    // Read and validate Clipper 5 header
    if (ReadHeader() != NTX_OK) {
        fclose(m_hFile);
        m_hFile = nullptr;
        m_bIsOpen = false;
        return NTX_ERR_INVALID_FILE;
    }

    // Validate Clipper 5 .ntx signature
    if (m_header.signature != NTX_SIGNATURE) {
        fclose(m_hFile);
        m_hFile = nullptr;
        m_bIsOpen = false;
        return NTX_ERR_INVALID_FILE;
    }

    // Store key properties from header
    m_keyLength = m_header.keyLength;
    m_bUnique = (m_header.unique == 1);
    
    // Read key expression from header
    char keyExprBuffer[NTX_MAX_KEY_EXPR_LEN + 1];
    memset(keyExprBuffer, 0, sizeof(keyExprBuffer));
    
    if (m_header.keyExpressionLength > 0 && m_header.keyExpressionLength <= NTX_MAX_KEY_EXPR_LEN) {
        // Key expression is stored after header
        if (fseek(m_hFile, m_header.keyExpressionOffset, SEEK_SET) == 0) {
            if (fread(keyExprBuffer, 1, m_header.keyExpressionLength, m_hFile) == m_header.keyExpressionLength) {
                keyExprBuffer[m_header.keyExpressionLength] = '\0';
                m_keyExpression = keyExprBuffer;
            }
        }
    }

    // Read index tree from file
    if (ReadIndexTree() != NTX_OK) {
        fclose(m_hFile);
        m_hFile = nullptr;
        m_bIsOpen = false;
        return NTX_ERR_FILE_READ;
    }

    return NTX_OK;
}

int NtxIndex::CloseIndex(void)
{
    if (!m_bIsOpen) {
        return NTX_OK;
    }

    // Write pending changes to disk
    if (m_bModified && !m_bReadonly && m_hFile) {
        FlushIndex();
    }

    if (m_bLocked) {
        UnLockIndex();
    }

    if (m_hFile) {
        fclose(m_hFile);
        m_hFile = nullptr;
    }

    m_bIsOpen = false;
    m_bModified = false;
    m_indexTree.clear();
    m_currentIndex = 0;
    m_currentKey.clear();
    m_curDbfRecordNumber = 0;

    return NTX_OK;
}

int NtxIndex::AddKey(const char* KeyBuffer, int KeyLength, long DbfRecordNumber)
{
    if (!m_bIsOpen) {
        return NTX_ERR_NOT_OPEN;
    }

    if (m_bReadonly) {
        return NTX_ERR_READONLY;
    }

    if (!KeyBuffer || KeyLength <= 0 || KeyLength > m_keyLength) {
        return NTX_ERR_INVALID_PARAMS;
    }

    if (DbfRecordNumber <= 0) {
        return NTX_ERR_INVALID_PARAMS;
    }

    // Convert key to string for storage
    std::string keyStr = KeyToString(KeyBuffer, KeyLength);

    // Check for duplicate key if index is unique
    if (m_bUnique) {
        auto it = m_indexTree.find(keyStr);
        if (it != m_indexTree.end() && !it->second.empty()) {
            return NTX_ERR_DUPLICATE_KEY;
        }
    }

    // Add key to index (allows duplicates if !bUnique)
    m_indexTree[keyStr].push_back(DbfRecordNumber);
    m_bModified = true;
    m_header.totalKeys++;

    return NTX_OK;
}

int NtxIndex::DeleteKey(const char* KeyBuffer, int nKeyLen, long DbfRecordNumber)
{
    if (!m_bIsOpen) {
        return NTX_ERR_NOT_OPEN;
    }

    if (m_bReadonly) {
        return NTX_ERR_READONLY;
    }

    if (!KeyBuffer || nKeyLen <= 0 || nKeyLen > m_keyLength) {
        return NTX_ERR_INVALID_PARAMS;
    }

    std::string keyStr = KeyToString(KeyBuffer, nKeyLen);

    auto it = m_indexTree.find(keyStr);
    if (it == m_indexTree.end()) {
        return NTX_ERR_KEY_NOT_FOUND;
    }

    // Find and remove specific record number
    auto& records = it->second;
    auto recIt = std::find(records.begin(), records.end(), DbfRecordNumber);
    if (recIt == records.end()) {
        return NTX_ERR_KEY_NOT_FOUND;
    }

    records.erase(recIt);

    // If no more records for this key, remove the key entry
    if (records.empty()) {
        m_indexTree.erase(it);
    }

    m_bModified = true;
    if (m_header.totalKeys > 0) {
        m_header.totalKeys--;
    }

    return NTX_OK;
}

int NtxIndex::FindKey(const char* KeyBuffer, int KeyLength, bool bSoftSeek)
{
    if (!m_bIsOpen) {
        return NTX_ERR_NOT_OPEN;
    }

    if (!KeyBuffer || KeyLength <= 0) {
        return NTX_ERR_INVALID_PARAMS;
    }

    std::string searchKey = KeyToString(KeyBuffer, KeyLength);

    if (bSoftSeek) {
        // Soft seek: find first key that starts with searchKey
        auto it = m_indexTree.lower_bound(searchKey);
        if (it != m_indexTree.end()) {
            // Check if found key starts with search key
            if (it->first.length() >= searchKey.length() &&
                it->first.substr(0, searchKey.length()) == searchKey) {
                m_currentKey = it->first;
                m_currentIndex = std::distance(m_indexTree.begin(), it);
                if (!it->second.empty()) {
                    m_curDbfRecordNumber = it->second[0];
                }
                return NTX_OK;
            }
        }
    } else {
        // Exact match required
        auto it = m_indexTree.find(searchKey);
        if (it != m_indexTree.end()) {
            m_currentKey = it->first;
            m_currentIndex = std::distance(m_indexTree.begin(), it);
            if (!it->second.empty()) {
                m_curDbfRecordNumber = it->second[0];
            }
            return NTX_OK;
        }
    }

    return NTX_ERR_KEY_NOT_FOUND;
}

int NtxIndex::GetNextKey()
{
    if (!m_bIsOpen) {
        return NTX_ERR_NOT_OPEN;
    }

    if (m_indexTree.empty()) {
        return NTX_ERR_EOF;
    }

    auto it = m_indexTree.begin();
    if (m_currentIndex < m_indexTree.size()) {
        std::advance(it, m_currentIndex);
    }

    // Move to next element
    ++it;
    if (it == m_indexTree.end()) {
        return NTX_ERR_EOF;
    }

    m_currentIndex++;
    m_currentKey = it->first;
    if (!it->second.empty()) {
        m_curDbfRecordNumber = it->second[0];
    }

    return NTX_OK;
}

int NtxIndex::GetPrevKey()
{
    if (!m_bIsOpen) {
        return NTX_ERR_NOT_OPEN;
    }

    if (m_indexTree.empty() || m_currentIndex == 0) {
        return NTX_ERR_BOF;
    }

    auto it = m_indexTree.begin();
    std::advance(it, m_currentIndex);

    if (it == m_indexTree.begin()) {
        return NTX_ERR_BOF;
    }

    --it;
    m_currentIndex--;
    m_currentKey = it->first;
    if (!it->second.empty()) {
        m_curDbfRecordNumber = it->second[0];
    }

    return NTX_OK;
}

int NtxIndex::GetFirstKey()
{
    if (!m_bIsOpen) {
        return NTX_ERR_NOT_OPEN;
    }

    if (m_indexTree.empty()) {
        return NTX_ERR_EOF;
    }

    auto it = m_indexTree.begin();
    m_currentIndex = 0;
    m_currentKey = it->first;
    if (!it->second.empty()) {
        m_curDbfRecordNumber = it->second[0];
    }

    return NTX_OK;
}

int NtxIndex::GetLastKey()
{
    if (!m_bIsOpen) {
        return NTX_ERR_NOT_OPEN;
    }

    if (m_indexTree.empty()) {
        return NTX_ERR_EOF;
    }

    auto it = m_indexTree.rbegin();
    m_currentIndex = m_indexTree.size() - 1;
    m_currentKey = it->first;
    if (!it->second.empty()) {
        m_curDbfRecordNumber = it->second[0];
    }

    return NTX_OK;
}

long NtxIndex::GetCurDbfRecordNumber()
{
    return m_curDbfRecordNumber;
}

char* NtxIndex::GetCurKeyValue()
{
    if (m_currentKey.empty()) {
        return nullptr;
    }

    if (m_curKeyValue) {
        delete[] m_curKeyValue;
        m_curKeyValue = nullptr;
    }

    m_curKeyValue = new char[m_currentKey.length() + 1];
    if (m_curKeyValue) {
        strcpy(m_curKeyValue, m_currentKey.c_str());
    }

    return m_curKeyValue;
}

const char* NtxIndex::GetKeyExpression()
{
    return m_keyExpression.c_str();
}

int NtxIndex::GetKeyLength()
{
    return m_keyLength;
}

int NtxIndex::TouchIndex()
{
    if (!m_bIsOpen) {
        return NTX_ERR_NOT_OPEN;
    }

    m_bModified = true;
    return NTX_OK;
}

int NtxIndex::LockIndex()
{
    if (!m_bIsOpen) {
        return NTX_ERR_NOT_OPEN;
    }

    if (m_bReadonly) {
        return NTX_ERR_READONLY;
    }

    // In a real implementation, use platform-specific file locking
    // For now, just set the flag
    m_bLocked = true;
    return NTX_OK;
}

int NtxIndex::UnLockIndex()
{
    if (!m_bIsOpen) {
        return NTX_ERR_NOT_OPEN;
    }

    m_bLocked = false;
    return NTX_OK;
}

void NtxIndex::FlushIndex()
{
    if (!m_bIsOpen || m_bReadonly || !m_hFile) {
        return;
    }

    // Write header
    WriteHeader();
    
    // Write index tree
    WriteIndexTree();
    
    // Flush file to disk
    fflush(m_hFile);
    m_bModified = false;
}

// Private methods

int NtxIndex::ReadHeader()
{
    if (!m_hFile) {
        return NTX_ERR_FILE_READ;
    }

    // Seek to beginning of file
    if (fseek(m_hFile, 0, SEEK_SET) != 0) {
        return NTX_ERR_FILE_READ;
    }

    // Read Clipper 5 header (512 bytes)
    if (fread(&m_header, sizeof(NtxHeader), 1, m_hFile) != 1) {
        return NTX_ERR_FILE_READ;
    }

    // Validate Clipper 5 .ntx signature
    if (m_header.signature != NTX_SIGNATURE) {
        return NTX_ERR_INVALID_FILE;
    }

    return NTX_OK;
}

int NtxIndex::WriteHeader()
{
    if (!m_hFile) {
        return NTX_ERR_FILE_WRITE;
    }

    // Seek to beginning of file
    if (fseek(m_hFile, 0, SEEK_SET) != 0) {
        return NTX_ERR_FILE_WRITE;
    }

    // Ensure signature is correct
    m_header.signature = NTX_SIGNATURE;
    m_header.version = NTX_VERSION;
    m_header.nodeSize = NTX_NODE_SIZE;
    
    // Write header
    if (fwrite(&m_header, sizeof(NtxHeader), 1, m_hFile) != 1) {
        return NTX_ERR_FILE_WRITE;
    }

    // Write key expression if it exists
    if (!m_keyExpression.empty()) {
        if (m_keyExpression.length() > NTX_MAX_KEY_EXPR_LEN) {
            return NTX_ERR_INVALID_PARAMS;
        }
        
        // Key expression data follows header
        if (fwrite(m_keyExpression.c_str(), 1, m_keyExpression.length(), m_hFile) != m_keyExpression.length()) {
            return NTX_ERR_FILE_WRITE;
        }
    }

    return NTX_OK;
}

int NtxIndex::ReadIndexTree()
{
    if (!m_hFile) {
        return NTX_ERR_FILE_READ;
    }

    m_indexTree.clear();

    // In a full Clipper 5 implementation, read B-tree nodes from disk
    // For now, we maintain index in memory only
    // When file is opened, index tree would be populated from stored nodes

    return NTX_OK;
}

int NtxIndex::WriteIndexTree()
{
    if (!m_hFile) {
        return NTX_ERR_FILE_WRITE;
    }

    // In a full Clipper 5 implementation, write B-tree nodes to disk
    // Update header with new positions and counts
    m_header.totalKeys = m_indexTree.size();

    // For now, index tree is maintained in memory
    // In production, would serialize B-tree to disk format

    return NTX_OK;
}

int NtxIndex::ValidateNtxFile()
{
    if (!m_hFile) {
        return NTX_ERR_FILE_READ;
    }

    // Validate file header and structure
    if (m_header.signature != NTX_SIGNATURE) {
        return NTX_ERR_INVALID_FILE;
    }

    if (m_header.keyLength <= 0 || m_header.keyLength > NTX_KEY_MAX_LENGTH) {
        return NTX_ERR_INVALID_FILE;
    }

    return NTX_OK;
}

int NtxIndex::InitializeHeader(const char* KeyExpression, int KeyLength, bool bUnique)
{
    memset(&m_header, 0, sizeof(NtxHeader));

    // Set Clipper 5 compatible header values
    m_header.signature = NTX_SIGNATURE;        // 0x0468
    m_header.version = NTX_VERSION;             // Clipper 5 version
    m_header.nodeSize = NTX_NODE_SIZE;          // 512 bytes
    m_header.keyLength = KeyLength;             // Key length 1-256
    m_header.keyDecimals = 0;                   // 0 for character keys
    m_header.keyType = 'C';                     // Character type
    m_header.unique = bUnique ? 1 : 0;          // Unique flag
    m_header.rootPage = 1;                      // Root page = 512 bytes offset
    m_header.nextPageNumber = 2;                // Next page = 1024 bytes offset
    m_header.totalKeys = 0;                     // Initially 0 keys
    m_header.keyExpressionOffset = NTX_HEADER_SIZE;  // Key expression after header
    m_header.keyExpressionLength = strlen(KeyExpression);

    if (m_header.keyExpressionLength > NTX_MAX_KEY_EXPR_LEN) {
        m_header.keyExpressionLength = NTX_MAX_KEY_EXPR_LEN;
    }

    return NTX_OK;
}

int NtxIndex::CompareKeys(const char* key1, int len1, const char* key2, int len2, bool bSoftSeek)
{
    if (bSoftSeek) {
        // Soft seek: compare only up to shorter length
        int minLen = (len1 < len2) ? len1 : len2;
        return strncmp(key1, key2, minLen);
    } else {
        // Exact comparison
        if (len1 != len2) {
            return len1 - len2;
        }
        return strncmp(key1, key2, len1);
    }
}

std::string NtxIndex::KeyToString(const char* KeyBuffer, int KeyLength)
{
    // Convert key buffer to string
    // Clipper typically pads keys with spaces
    std::string result(KeyBuffer, KeyLength);
    
    // Trim trailing spaces for storage
    size_t end = result.find_last_not_of(" ");
    if (end != std::string::npos) {
        result = result.substr(0, end + 1);
    }
    
    return result;
}

void NtxIndex::PadKeyWithSpaces(char* keyBuffer, int targetLength)
{
    if (!keyBuffer || targetLength <= 0) {
        return;
    }

    int currentLen = strlen(keyBuffer);
    if (currentLen < targetLength) {
        memset(keyBuffer + currentLen, ' ', targetLength - currentLen);
        keyBuffer[targetLength] = '\0';
    }
}

uint32_t NtxIndex::CalculateChecksum(const void* data, size_t size)
{
    // Simple checksum for Clipper 5 compatibility
    uint32_t checksum = 0;
    const uint8_t* bytes = static_cast<const uint8_t*>(data);
    
    for (size_t i = 0; i < size; ++i) {
        checksum += bytes[i];
        checksum = (checksum << 1) | (checksum >> 31);  // Rotate left
    }
    
    return checksum;
}
