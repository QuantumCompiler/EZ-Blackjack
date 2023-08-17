// ----- ----- ----- ----- ----- ----- ----- Includes ----- ----- ----- ----- ----- ----- ----- ----- ----- //
#include "../Headers/HashTable.h"

/*  HashTable - Bloom table constructor
*   Input:
*       bitSize - Integer value that represents the number of bits in the hash table
*       numHashIterations - Integer value that represents the number of hash function iterations for calculating a hash value
*   Algorithm:
*       * Allocate the "table" structure on the heap
*       * Assign default values to data members of the aforementioned table
*/
HashTable::HashTable(int bitSize, int numHashIterations) {
    // Allocate "hashTable" structure on the heap
    this->hashTable = std::make_shared<Table>();
    // Assign default values to data members of "hashTable"
    this->hashTable->bucketIndex = 0;
    this->hashTable->table.resize(bitSize, false);
    this->hashTable->hashCode = 0;
    this->hashTable->hashFunctionIterations = numHashIterations;
}

// ~HashTable - Bloom table deconstructor
HashTable::~HashTable() {}

/*  AddToTable - Adds element to hash table
*   Input:
*       input - Constant string value that is passed by reference to represent the element that will be added to a table
*   Algorithm:
*       * Calculate the hash code of the input parameter
*       * Calculate the bucket of the given input parameter
*       * Add the element to the container of the table
*   Output:
*       This function does not return a value, it adds an element to the container in the hash table
*/
void HashTable::AddToTable(const std::string& input) {
    // Calculate hash code and bucket index of input value
    this->SetHashCode(input);
    this->SetBucket(this->GetHashCode());
    // Add element to table
    this->SetTable(this->GetBucket());
}

/*  CalculateBucketIndex - Calculates the bucket index for a given input parameter
*   Input:
*       input - Constant non-negative integer that is passed by reference that represents a hash code
*   Algorithm
*       * Calculate the bucket value with the modulus of the size of the container in the table
*   Output:
*       bucketVal - Non-negative integer that represents the bucket index of the corresponding hash code
*/
unsigned int HashTable::CalculateBucketIndex(const unsigned int& input) {
    // Calculate the modulus of the input parameter with the size of the container in the table
    unsigned int bucketVal = input % this->GetTable().size();
    return bucketVal;
}

/*  CalculateHashCode - Calculates the hash code of a given input string
*   Input:
*       input - Constant string value that is passed by reference that represents the object being inserted into the table
*   Algorithm:
*       * Create necessary hash objects for types "string" and "unsigned int"
*       * Update the hash code "finalHashVal" for a given number of iterations retrieved with "GetHashFuncIterations"
*       * Calculate "firstHash" and "secondHash" inside the for loop
*       * Return the hash value after the for loop
*   Output:
*       finalHashVal - Non-negative integer value that represents the hash code of a string value
*/
unsigned int HashTable::CalculateHashCode(const std::string& input) {
    // Create a hash object of object type "string"
    std::hash<std::string> stringHash;
    // Create a hash object of object type "unsigned int"
    std::hash<unsigned int> longHash;
    // Create a value for the final hash value 
    unsigned int finalHashVal = 0;
    // Add to "finalHashVal" with the hashed values of "firstHash" and "secondHash"
    unsigned int firstHash = stringHash(input);
    for (int i = 0; i < this->GetHashFuncIterations(); ++i) {
        // Calculate "firstHash" and "secondHash"
        unsigned int secondHash = longHash(i * firstHash);
        finalHashVal += (firstHash + i * secondHash);
    }
    // Return the final hash value
    return finalHashVal;
}

/*  ClearHashTable - Clears the container of a table
*   Input:
*       This function does not have any input parameters
*   Algorithm:
*       * Reset all values of "table" to false
*   Output:
*       This function does not return a value, it resets the data member "table" so that all its elements are false
*/
void HashTable::ClearHashTable() {
    std::fill(this->hashTable->table.begin(), this->hashTable->table.end(), false);
}

/*  Contains - Checks if a specific element is present inside a hash table
*   Input:
*       input - Constant string value that is passed by reference that represents the element that is being searched for
*   Algorithm:
*       * Calculate the hash code and bucket index of "input"
*       * Return the boolean value of that element in the container of the table
*   Output:
*       This function returns a boolean value that represents if an element is present in a table
*/
bool HashTable::Contains(const std::string& input) {
    // Calculate the hash code and bucket index of "input"
    unsigned int tempHash = this->CalculateHashCode(input);
    unsigned int tempBucket = this->CalculateBucketIndex(tempHash);
    // Return boolean value at the index of the container in the table
    return this->GetTable()[tempBucket];
}

/*  RemoveElement - "Removes" an element from a table
*   Input:
*       input - Constant string value that is passed by reference that represents the element that is to be removed from a table
*   Algorithm:
*       * Calculate the hash code and bucket index of "input"
*       * Change the elements boolean value to false
*   Output:
*       This function does not return a value, it sets a specific index of the table to be false for a given input
*/
void HashTable::RemoveElement(const std::string& input) {
    // Calculate the hash code and bucket index of "input"
    unsigned int tempHash = this->CalculateHashCode(input);
    unsigned int tempBucket = this->CalculateBucketIndex(tempHash);
    // Change the boolean value at the index of the container in the table to false
    this->GetTable()[tempBucket] = false;
}

// ----- ----- ----- ----- ----- ----- ----- Mutators ----- ----- ----- ----- ----- ----- ----- ----- ----- //
// GetBucket - Retrieves the private data member "bucketIndex"
unsigned int& HashTable::GetBucket() {
    return this->hashTable->bucketIndex;
}

// GetTable - Retrieves the private data member "table"
std::vector<bool>& HashTable::GetTable() {
    return this->hashTable->table;
}

// GetHashCode - Retrieves the private data member "hashCode"
unsigned int& HashTable::GetHashCode() {
    return this->hashTable->hashCode;
}

// GetHashFuncIterations - Retrieves the private data member "hashFunctionIterations"
unsigned int& HashTable::GetHashFuncIterations() {
    return this->hashTable->hashFunctionIterations;
}

// SetBucket - Mutates the private data member "bucketIndex" to that of "input"
void HashTable::SetBucket(const unsigned int& input) {
    this->hashTable->bucketIndex = this->CalculateBucketIndex(input);
}

// SetTable - Mutates the private data member "table" to that of "input"
void HashTable::SetTable(const unsigned int& input) {
    this->hashTable->table[input] = true;
}

// SetHashCode - Mutates the private data member "hashCode" to that of "input"
void HashTable::SetHashCode(const std::string& input) {
    this->hashTable->hashCode = this->CalculateHashCode(input);
}

// SetNumHashFunctions - Mutates the private data member "hashFunctionIterations" to that of "input"
void HashTable::SetNumHashFunctions(const unsigned int& input) {
    this->hashTable->hashFunctionIterations = input;
}