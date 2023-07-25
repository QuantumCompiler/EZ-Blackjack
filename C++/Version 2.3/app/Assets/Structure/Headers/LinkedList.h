// ----- ----- ----- ----- ----- ----- ----- Includes ----- ----- ----- ----- ----- ----- ----- ----- ----- //
#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include "Includes.h"

// Linked List Node
struct LinkedListNode {
    // Data members
    int integerValue;
    float floatValue;
    // Pointers
    std::shared_ptr<LinkedListNode> nextNode;
    std::shared_ptr<LinkedListNode> previousNode;
};

class LinkedList {
// Private data members and functions
private:
    // Root and tail nodes of list
    std::shared_ptr<LinkedListNode> rootNode;
    std::shared_ptr<LinkedListNode> tailNode;
public:
    // Constructor and de-constructor
    LinkedList();
    ~LinkedList();
    // Member functions
    void AppendNode(std::shared_ptr<LinkedListNode> input); // Append node
    std::shared_ptr<LinkedListNode> InitNode(int intInput, float floatInput); // Init node
    void InsertNode(std::shared_ptr<LinkedListNode> input, int offset); // Insert node
    std::shared_ptr<LinkedListNode> PopNode(std::shared_ptr<LinkedListNode> input); // Pop node
    void PrintList(); // Print list
    void RemoveNode(int offset); // Remove node
    // ---- ---- ---- Mutator Functions ---- ---- ---- //
    // Getter functions
    std::shared_ptr<LinkedListNode> GetRoot(); // Get root of list
    std::shared_ptr<LinkedListNode> GetTail(); // Get tail of list
    // Setter functions
    void SetRoot(std::shared_ptr<LinkedListNode> input); // Set root of list
    void SetTail(std::shared_ptr<LinkedListNode> input); // Set tail of list
};

#endif