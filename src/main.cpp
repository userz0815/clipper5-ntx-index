#include "../include/NtxIndex.h"
#include <iostream>
#include <iomanip>
#include <cstring>

// Error message helper
const char* GetErrorMessage(int errorCode)
{
    switch (errorCode) {
        case NTX_OK:                  return "OK";
        case NTX_ERR_FILE_NOT_FOUND:  return "File not found";
        case NTX_ERR_FILE_EXISTS:     return "File already exists";
        case NTX_ERR_INVALID_FILE:    return "Invalid file format";
        case NTX_ERR_KEY_NOT_FOUND:   return "Key not found";
        case NTX_ERR_DUPLICATE_KEY:   return "Duplicate key (unique constraint)";
        case NTX_ERR_FILE_OPEN:       return "Cannot open file";
        case NTX_ERR_FILE_READ:       return "Cannot read file";
        case NTX_ERR_FILE_WRITE:      return "Cannot write file";
        case NTX_ERR_MEMORY:          return "Memory error";
        case NTX_ERR_NOT_OPEN:        return "Index file not open";
        case NTX_ERR_READONLY:        return "File is read-only";
        case NTX_ERR_EOF:             return "End of file";
        case NTX_ERR_BOF:             return "Beginning of file";
        case NTX_ERR_FILE_LOCKED:     return "File is locked";
        case NTX_ERR_LOCK_FAILED:     return "Cannot lock file";
        case NTX_ERR_INVALID_PARAMS:  return "Invalid parameters";
        default:                      return "Unknown error";
    }
}

// Example 1: Create and populate a simple index
void Example_CreateSimpleIndex()
{
    std::cout << "\n=== Example 1: Create Simple Index ===\n";

    NtxIndex idx;

    // Create index file
    int result = idx.CreateIndex("test_names.ntx", "UPPER(name)", 30, false);
    if (result != NTX_OK) {
        std::cout << "Error creating index: " << GetErrorMessage(result) << std::endl;
        return;
    }
    std::cout << "Index created: test_names.ntx\n";
    std::cout << "Key Expression: " << idx.GetKeyExpression() << std::endl;
    std::cout << "Key Length: " << idx.GetKeyLength() << std::endl;

    // Add some keys
    struct {
        const char* key;
        long recNum;
    } testData[] = {
        { "SMITH", 1 },
        { "JOHNSON", 2 },
        { "WILLIAMS", 3 },
        { "BROWN", 4 },
        { "DAVIS", 5 },
        { nullptr, 0 }
    };

    std::cout << "\nAdding keys:\n";
    for (int i = 0; testData[i].key != nullptr; i++) {
        result = idx.AddKey(testData[i].key, strlen(testData[i].key), testData[i].recNum);
        if (result != NTX_OK) {
            std::cout << "Error adding key '" << testData[i].key << "': " 
                      << GetErrorMessage(result) << std::endl;
        } else {
            std::cout << "Added: '" << testData[i].key << "' -> Record " 
                      << testData[i].recNum << std::endl;
        }
    }

    // Navigate through index
    std::cout << "\nNavigating from first key:\n";
    if (idx.GetFirstKey() == NTX_OK) {
        int count = 0;
        do {
            char* key = idx.GetCurKeyValue();
            long recNum = idx.GetCurDbfRecordNumber();
            std::cout << "Key: '" << key << "' -> Record " << recNum << std::endl;
            count++;
        } while (idx.GetNextKey() == NTX_OK && count < 10);
    }

    idx.CloseIndex();
    std::cout << "Index closed and saved.\n";
}

// Example 2: Create index with unique constraint
void Example_UniqueIndex()
{
    std::cout << "\n=== Example 2: Unique Index Constraint ===\n";

    NtxIndex idx;

    // Create unique index
    int result = idx.CreateIndex("test_unique.ntx", "email", 50, true);
    if (result != NTX_OK) {
        std::cout << "Error creating index: " << GetErrorMessage(result) << std::endl;
        return;
    }
    std::cout << "Unique index created\n";

    // Try adding duplicate keys
    std::cout << "\nTesting unique constraint:\n";
    
    result = idx.AddKey("john@example.com", 16, 100);
    std::cout << "Add 'john@example.com' (Record 100): " << GetErrorMessage(result) << std::endl;

    result = idx.AddKey("jane@example.com", 16, 101);
    std::cout << "Add 'jane@example.com' (Record 101): " << GetErrorMessage(result) << std::endl;

    // Try adding duplicate
    result = idx.AddKey("john@example.com", 16, 200);
    std::cout << "Add 'john@example.com' (Record 200): " << GetErrorMessage(result) 
              << " [Expected: Duplicate key error]" << std::endl;

    idx.CloseIndex();
}

// Example 3: Find and search operations
void Example_FindOperations()
{
    std::cout << "\n=== Example 3: Find and Search ===\n";

    NtxIndex idx;

    // Create index
    idx.CreateIndex("test_find.ntx", "code", 10, false);
    std::cout << "Index created\n";

    // Add test data
    std::cout << "\nAdding test keys:\n";
    idx.AddKey("ABC001", 6, 10);
    std::cout << "Added: ABC001\n";
    idx.AddKey("ABC002", 6, 11);
    std::cout << "Added: ABC002\n";
    idx.AddKey("ABC003", 6, 12);
    std::cout << "Added: ABC003\n";
    idx.AddKey("XYZ001", 6, 20);
    std::cout << "Added: XYZ001\n";

    // Exact find
    std::cout << "\nExact find 'ABC002':\n";
    int result = idx.FindKey("ABC002", 6, false);
    if (result == NTX_OK) {
        std::cout << "Found: '" << idx.GetCurKeyValue() << "' -> Record " 
                  << idx.GetCurDbfRecordNumber() << std::endl;
    } else {
        std::cout << "Not found: " << GetErrorMessage(result) << std::endl;
    }

    // Soft seek
    std::cout << "\nSoft seek for 'ABC' (first key starting with ABC):\n";
    result = idx.FindKey("ABC", 3, true);
    if (result == NTX_OK) {
        std::cout << "Found: '" << idx.GetCurKeyValue() << "' -> Record " 
                  << idx.GetCurDbfRecordNumber() << std::endl;
    } else {
        std::cout << "Not found: " << GetErrorMessage(result) << std::endl;
    }

    idx.CloseIndex();
}

// Example 4: Delete operations
void Example_DeleteOperations()
{
    std::cout << "\n=== Example 4: Delete Operations ===\n";

    NtxIndex idx;

    // Create index
    idx.CreateIndex("test_delete.ntx", "item", 20, false);
    std::cout << "Index created\n";

    // Add test data
    std::cout << "\nAdding test keys:\n";
    idx.AddKey("ITEM001", 7, 1);
    idx.AddKey("ITEM002", 7, 2);
    idx.AddKey("ITEM003", 7, 3);
    std::cout << "Added 3 items\n";

    // Show before delete
    std::cout << "\nBefore delete - First key:\n";
    if (idx.GetFirstKey() == NTX_OK) {
        std::cout << "Key: '" << idx.GetCurKeyValue() << "' -> Record " 
                  << idx.GetCurDbfRecordNumber() << std::endl;
    }

    // Delete key
    std::cout << "\nDeleting 'ITEM002'\n";
    int result = idx.DeleteKey("ITEM002", 7, 2);
    std::cout << "Delete result: " << GetErrorMessage(result) << std::endl;

    // Navigate to show item was deleted
    std::cout << "\nNavigating after delete:\n";
    if (idx.GetFirstKey() == NTX_OK) {
        int count = 0;
        do {
            std::cout << "Key: '" << idx.GetCurKeyValue() << "' -> Record " 
                      << idx.GetCurDbfRecordNumber() << std::endl;
            count++;
        } while (idx.GetNextKey() == NTX_OK && count < 10);
    }

    idx.CloseIndex();
}

// Example 5: Navigation (backward)
void Example_BackwardNavigation()
{
    std::cout << "\n=== Example 5: Backward Navigation ===\n";

    NtxIndex idx;

    idx.CreateIndex("test_nav.ntx", "num", 10, false);
    std::cout << "Index created\n";

    // Add test data
    std::cout << "\nAdding test keys: 10, 20, 30, 40, 50\n";
    idx.AddKey("10", 2, 1);
    idx.AddKey("20", 2, 2);
    idx.AddKey("30", 2, 3);
    idx.AddKey("40", 2, 4);
    idx.AddKey("50", 2, 5);

    // Go to last key and navigate backward
    std::cout << "\nNavigating backward from last key:\n";
    if (idx.GetLastKey() == NTX_OK) {
        int count = 0;
        do {
            std::cout << "Key: '" << idx.GetCurKeyValue() << "' -> Record " 
                      << idx.GetCurDbfRecordNumber() << std::endl;
            count++;
        } while (idx.GetPrevKey() == NTX_OK && count < 10);
    }

    idx.CloseIndex();
}

int main()
{
    std::cout << "Clipper 5 .ntx Index File API - Examples\n";
    std::cout << "========================================\n";

    try {
        Example_CreateSimpleIndex();
        Example_UniqueIndex();
        Example_FindOperations();
        Example_DeleteOperations();
        Example_BackwardNavigation();

        std::cout << "\n\nAll examples completed successfully!\n";
    }
    catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
