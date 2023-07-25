// ----- ----- ----- ----- ----- ----- ----- Includes ----- ----- ----- ----- ----- ----- ----- ----- ----- //
#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include "Includes.h"

// Linked List Node
struct LinkedListNode {
    // Data members
    float value;
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
    // Size of list
    int listSize = 0;
public:
    // Constructor and de-constructor
    LinkedList();
    ~LinkedList();
    // Member functions
    void AppendNode(std::shared_ptr<LinkedListNode>& input); // Append node
    void ClearList(); // Clear a linked list
    std::shared_ptr<LinkedListNode> InitNode(float input); // Init node
    std::shared_ptr<LinkedListNode> PopNode(); // Pop node
    void PrintList(); // Print list
    // ---- ---- ---- Mutator Functions ---- ---- ---- //
    // Getter functions
    std::shared_ptr<LinkedListNode>& GetRoot(); // Get root of list
    int& GetSize(); // Get size of list
    std::shared_ptr<LinkedListNode>& GetTail(); // Get tail of list
    // Setter functions
    void SetRoot(std::shared_ptr<LinkedListNode> input); // Set root of list
    void SetSize(); // Set size of list
    void SetTail(std::shared_ptr<LinkedListNode> input); // Set tail of list
};

#endif