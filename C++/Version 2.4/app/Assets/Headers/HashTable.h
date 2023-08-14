// ----- ----- ----- ----- ----- ----- ----- Includes ----- ----- ----- ----- ----- ----- ----- ----- ----- //
#ifndef HASHTABLE_H
#define HASHTABLE_H
#include "Includes.h"

// ----- ----- ----- ----- ----- ----- ----- References ----- ----- ----- ----- ----- ----- ----- ----- ----- //
// https://www.geeksforgeeks.org/stdhash-class-in-c-stl/
// https://cplusplus.com/reference/functional/hash/
// https://en.cppreference.com/w/cpp/utility/hash

/*  Structure Table - Table elements for a hash table
*   Data Members:
*       bucketIndex - Non negative integer value that represents the bucket index of an element in the hash table
*       table - Vector of boolean values where hashed elements are stored in a hash table
*       hashCode - Non negative integer value that represents the container for the hash table
*       hashFunctionIterations - Non negative integer value that represents the number of iterations for creating a hash code
*/
struct Table {
    unsigned int bucketIndex; // Bucket index for a given hash code
    std::vector<bool> table; // Vector of boolean values to represent a table
    unsigned int hashCode; // Final hash value for a given string
    unsigned int hashFunctionIterations; // Number of hash functions used to create a final hash value
};

// HashTable class
class HashTable {
public:
    // ---- ---- ---- Constructors ---- ---- ---- //
    HashTable(int bitSize, int numHashIterations); // Constructor
    ~HashTable(); // De-Constructor
    // ---- ---- ---- Member Functions ---- ---- ---- //
    void AddToFilter(const std::string& input); // Add element to table
    unsigned int CalculateBucketIndex(const unsigned int& input); // Calculates the bucket index of a hash code
    unsigned int CalculateHashCode(const std::string& input); // Calculates the hash code for the table
    void ClearHashTable(); // Clear table
    bool Contains(const std::string& input); // Check if element exists in table
    void RemoveElement(const std::string& input); // Removes an element from the table
    // ---- ---- ---- Mutator Functions ---- ---- ---- //
    // Getter functions
    unsigned int& GetBucket(); // Retrieves "bucketIndex"
    std::vector<bool>& GetTable(); // Retrieves "table"
    unsigned int& GetHashCode(); // Retrieves "finalHash"
    unsigned int& GetHashFuncIterations(); // Retrieves "hashFunctionIterations"
    // Setter functions
    void SetBucket(const unsigned int& input); // Mutates "bucketIndex"
    void SetTable(const unsigned int& input); // Mutates "table"
    void SetHashCode(const std::string& input); // Mutates "hashCode"
    void SetNumHashFunctions(const unsigned int& input); // Mutates "hashFunctionIterations"
private:
    std::shared_ptr<Table> hashTable; // Table struct
};

#endif