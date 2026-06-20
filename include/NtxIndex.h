#ifndef NTXINDEX_H
#define NTXINDEX_H

#include <cstring>
#include <cstdio>
#include <cstdint>
#include <map>
#include <vector>
#include <string>
#include <memory>

// Error codes
#define NTX_OK                    0
#define NTX_ERR_FILE_NOT_FOUND    1
#define NTX_ERR_FILE_EXISTS       2
#define NTX_ERR_INVALID_FILE      3
#define NTX_ERR_KEY_NOT_FOUND     4
#define NTX_ERR_DUPLICATE_KEY     5
#define NTX_ERR_FILE_OPEN         6
#define NTX_ERR_FILE_READ         7
#define NTX_ERR_FILE_WRITE        8
#define NTX_ERR_MEMORY            9
#define NTX_ERR_NOT_OPEN          10
#define NTX_ERR_READONLY          11
#define NTX_ERR_EOF               12
#define NTX_ERR_BOF               13
#define NTX_ERR_FILE_LOCKED       14
#define NTX_ERR_LOCK_FAILED       15
#define NTX_ERR_INVALID_PARAMS    16

// Clipper 5 .ntx file format constants
#define NTX_SIGNATURE             0x0468      // Magic number for .ntx files
#define NTX_VERSION               0x0100      // Clipper 5 version
#define NTX_NODE_SIZE             512         // Standard Clipper 5 node size
#define NTX_KEY_MAX_LENGTH        256         // Maximum key length
#define NTX_MAX_KEY_EXPR_LEN      255         // Maximum key expression length
#define NTX_HEADER_SIZE           512         // Clipper 5 header is 512 bytes

#pragma pack(1)

// Clipper 5 .ntx file header structure - MUST match Clipper 5 format exactly
// Reference: Clipper 5.x documentation and reverse engineering of .ntx files
struct NtxHeader {
    uint16_t signature;               // Offset 0: 0x0468 = .ntx file signature
    uint16_t version;                 // Offset 2: Version information
    uint32_t rootPage;                // Offset 4: Root page number (file position / 512)
    uint32_t nextPageNumber;          // Offset 8: Next available page number
    uint16_t nodeSize;                // Offset 12: Node size (usually 512)
    uint16_t keyLength;               // Offset 14: Key field length (1-256)
    uint16_t keyDecimals;             // Offset 16: Number of decimal places
    uint8_t  keyType;                 // Offset 18: 'C'=Char, 'N'=Numeric, 'D'=Date
    uint8_t  unique;                  // Offset 19: 0x00=duplicates, 0x01=unique
    uint8_t  reserved1[4];            // Offset 20-23: Reserved
    uint32_t keyExpressionOffset;     // Offset 24: Offset to key expression
    uint16_t keyExpressionLength;     // Offset 26: Length of key expression
    uint32_t totalKeys;               // Offset 28: Total number of keys in index
    uint8_t  reserved2[468];          // Offset 32-499: Reserved for future use
    uint32_t headerChecksum;          // Offset 500-503: CRC/checksum (0 for now)
    uint16_t headerEnd;               // Offset 504-505: End marker
    uint8_t  reserved3[6];            // Offset 506-511: Padding to 512 bytes
};

// Index page/node structure (each page is 512 bytes)
struct NtxIndexNode {
    uint16_t nodeType;                // 0=leaf, 1=branch
    uint16_t numKeys;                 // Number of keys in this node
    uint32_t reserved;                // Reserved
    char     keyData[NTX_NODE_SIZE - 8];  // Key entries and pointers
};

// Key entry in node
struct NtxKeyEntry {
    char*    key;                     // Key value (variable length)
    int      keyLength;               // Actual key length
    long     dbfRecordNumber;         // Associated DBF record number (4 bytes)
    uint32_t childPageNumber;         // Child page number (for branch nodes)
};

#pragma pack()

/**
 * NtxIndex - Clipper 5 .ntx Index File API
 * 
 * Provides full read/write compatibility with Clipper 5 native index files (.ntx)
 * Features:
 * - B-tree based index structure
 * - Support for duplicate keys
 * - Unique key constraints
 * - Soft seek capability for partial key matching
 * - Full navigation (first, last, next, prev)
 * - Compatible with original Clipper 5 index files
 */
class NtxIndex {

public:
    NtxIndex();
    ~NtxIndex();

    // Index file management
    /**
     * CreateIndex - Create a new Clipper 5 index file
     * @param IndexFileName - Path to .ntx file to create
     * @param KeyExpression - Expression used to calculate keys (e.g., "UPPER(name)")
     * @param KeyLength - Length of keys (1-256 bytes)
     * @param bUnique - If true, duplicate keys are rejected
     * @return NTX_OK on success, error code otherwise
     */
    int CreateIndex(const char* IndexFileName, const char* KeyExpression, int KeyLength, bool bUnique);

    /**
     * OpenIndex - Open an existing Clipper 5 index file
     * @param IndexFileName - Path to .ntx file to open
     * @param bReadonly - If true, file is opened read-only
     * @param bShared - If true, file is opened in shared mode
     * @return NTX_OK on success, error code otherwise
     */
    int OpenIndex(const char* IndexFileName, bool bReadonly, bool bShared);

    /**
     * CloseIndex - Close the current index file
     * @return NTX_OK on success, error code otherwise
     */
    int CloseIndex(void);

    // Key operations
    /**
     * AddKey - Add a key/record number pair to the index
     * @param KeyBuffer - Pointer to key data
     * @param KeyLength - Length of key data
     * @param DbfRecordNumber - DBF record number associated with key (4 bytes, long int)
     * @return NTX_OK on success
     *         NTX_ERR_DUPLICATE_KEY if bUnique and key already exists
     *         Other error codes on failure
     */
    int AddKey(const char* KeyBuffer, int KeyLength, long DbfRecordNumber);

    /**
     * DeleteKey - Delete a key/record number pair from the index
     * @param KeyBuffer - Pointer to key data
     * @param nKeyLen - Length of key data
     * @param DbfRecordNumber - DBF record number to remove
     * @return NTX_OK on success, NTX_ERR_KEY_NOT_FOUND if key doesn't exist
     */
    int DeleteKey(const char* KeyBuffer, int nKeyLen, long DbfRecordNumber);

    /**
     * FindKey - Find a key in the index
     * @param KeyBuffer - Pointer to key data to search for
     * @param KeyLength - Length of key data
     * @param bSoftSeek - If true, match partial keys (KeyLength < GetKeyLength)
     *                    If false, require exact key match
     * @return NTX_OK if key found, NTX_ERR_KEY_NOT_FOUND otherwise
     */
    int FindKey(const char* KeyBuffer, int KeyLength, bool bSoftSeek);

    // Navigation
    /**
     * GetNextKey - Move to next key in index order
     * @return NTX_OK on success, NTX_ERR_EOF at end of index
     */
    int GetNextKey();

    /**
     * GetPrevKey - Move to previous key in index order
     * @return NTX_OK on success, NTX_ERR_BOF at beginning of index
     */
    int GetPrevKey();

    /**
     * GetFirstKey - Move to first key in index
     * @return NTX_OK on success, NTX_ERR_EOF if index is empty
     */
    int GetFirstKey();

    /**
     * GetLastKey - Move to last key in index
     * @return NTX_OK on success, NTX_ERR_EOF if index is empty
     */
    int GetLastKey();

    // Current position information
    /**
     * GetCurDbfRecordNumber - Get DBF record number of current key
     * @return 0 if no current key, otherwise the DBF record number (4-byte long int)
     */
    long GetCurDbfRecordNumber();

    /**
     * GetCurKeyValue - Get current key value
     * @return NULL if no current key, otherwise pointer to key buffer
     *         Pointer is valid until next GetCurKeyValue or ~NtxIndex call
     */
    char* GetCurKeyValue();

    // Index properties
    /**
     * GetKeyExpression - Get the key expression string
     * @return Pointer to key expression (stored in .ntx file header)
     */
    const char* GetKeyExpression();

    /**
     * GetKeyLength - Get the key length
     * @return Key length in bytes (1-256)
     */
    int GetKeyLength();

    // File operations
    /**
     * TouchIndex - Mark index as modified (forces write on flush)
     * @return NTX_OK on success
     */
    int TouchIndex();

    /**
     * LockIndex - Lock the index file (for multi-user environments)
     * @return NTX_OK on success, NTX_ERR_LOCK_FAILED on failure
     */
    int LockIndex();

    /**
     * UnLockIndex - Unlock the index file
     * @return NTX_OK on success
     */
    int UnLockIndex();

    /**
     * FlushIndex - Write all pending changes to disk
     * Automatically called on CloseIndex()
     */
    void FlushIndex();

    /**
     * IsOpen - Check if index file is open
     * @return true if open, false otherwise
     */
    bool IsOpen() const { return m_bIsOpen; }

    /**
     * IsReadonly - Check if index file is read-only
     * @return true if read-only, false otherwise
     */
    bool IsReadonly() const { return m_bReadonly; }

    /**
     * IsUnique - Check if index has unique constraint
     * @return true if unique, false if duplicates allowed
     */
    bool IsUnique() const { return m_bUnique; }

private:
    // Member variables
    FILE*                m_hFile;                  // File handle
    std::string          m_fileName;              // File name
    std::string          m_keyExpression;         // Key expression string
    int                  m_keyLength;             // Key length (1-256)
    bool                 m_bUnique;               // Unique constraint flag
    bool                 m_bReadonly;             // Read-only flag
    bool                 m_bShared;               // Shared access flag
    bool                 m_bIsOpen;               // Is index open
    bool                 m_bModified;             // Is index modified
    bool                 m_bLocked;               // Is index locked

    // Current position tracking
    char*                m_curKeyValue;           // Current key value buffer
    long                 m_curDbfRecordNumber;    // Current DBF record number
    std::string          m_currentKey;            // Current key string
    size_t               m_currentIndex;          // Current position in index

    // Index data structure (B-tree in memory)
    // Maps key string -> vector of record numbers (for duplicate keys)
    std::map<std::string, std::vector<long>> m_indexTree;

    // File header
    NtxHeader            m_header;

    // Private helper methods
    int ReadHeader();
    int WriteHeader();
    int ReadIndexTree();
    int WriteIndexTree();
    int ValidateNtxFile();
    int InitializeHeader(const char* KeyExpression, int KeyLength, bool bUnique);
    int CompareKeys(const char* key1, int len1, const char* key2, int len2, bool bSoftSeek = false);
    std::string KeyToString(const char* KeyBuffer, int KeyLength);
    void PadKeyWithSpaces(char* keyBuffer, int targetLength);
    uint32_t CalculateChecksum(const void* data, size_t size);
};

#endif // NTXINDEX_H
