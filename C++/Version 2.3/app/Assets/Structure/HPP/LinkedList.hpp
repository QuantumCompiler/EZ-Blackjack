// ----- ----- ----- ----- ----- ----- ----- Includes ----- ----- ----- ----- ----- ----- ----- ----- ----- //
#include "../Headers/LinkedList.h"

// ----- ----- ----- ----- ----- ----- ----- Member Functions ----- ----- ----- ----- ----- ----- ----- ----- //
// Class constructor
LinkedList::LinkedList() {
    SetRoot(nullptr);
    SetTail(nullptr);
}

// Class de-constructor
LinkedList::~LinkedList() {}

/*  InitNode - Initializes a node that will belong to a linked list
*
*/
std::shared_ptr<LinkedListNode> LinkedList::InitNode(int intInput, float floatInput) {
    std::shared_ptr<LinkedListNode> retNode(new LinkedListNode);
    retNode->integerValue = intInput;
    retNode->floatValue = floatInput;
    retNode->previousNode = nullptr;
    retNode->nextNode = nullptr;
    return retNode;
}

// ----- ----- ----- ----- ----- ----- ----- Mutators ----- ----- ----- ----- ----- ----- ----- ----- ----- //
// ----- ----- ----- ----- Getter Functions ----- ----- ----- ----- //
/*  GetRoot - Retrieves the root node of a linked list
*
*/
std::shared_ptr<LinkedListNode> LinkedList::GetRoot() {
    return rootNode;
}

/*  GetTail - Retrieves the tail node of a linked list
*
*/
std::shared_ptr<LinkedListNode> LinkedList::GetTail() {
    return tailNode;
}

// ----- ----- ----- ----- Setter Functions ----- ----- ----- ----- //
/*  SetRoot - Sets the root node of a linked list
*
*/
void LinkedList::SetRoot(std::shared_ptr<LinkedListNode> input) {
    rootNode = input;
}

/*  SetTail - Sets the tail node of a linked list
*
*/
void LinkedList::SetTail(std::shared_ptr<LinkedListNode> input) {
    tailNode = input;
}