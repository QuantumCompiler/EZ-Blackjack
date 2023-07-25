// ----- ----- ----- ----- ----- ----- ----- Includes ----- ----- ----- ----- ----- ----- ----- ----- ----- //
#include "../Headers/LinkedList.h"

// ----- ----- ----- ----- ----- ----- ----- Member Functions ----- ----- ----- ----- ----- ----- ----- ----- //
// Class constructor
LinkedList::LinkedList() {
    std::shared_ptr<LinkedListNode> initRoot = nullptr;
    std::shared_ptr<LinkedListNode> initTail = nullptr;
    SetRoot(initRoot);
    SetTail(initTail);
    SetSize();
}

// Class de-constructor
LinkedList::~LinkedList() {}

// AppendNode - Adds a node to the end of the linked list
void LinkedList::AppendNode(std::shared_ptr<LinkedListNode>& input) {
    if (GetRoot() == nullptr) {
        input->previousNode = nullptr;
        input->nextNode = nullptr;
        SetRoot(input);
        SetTail(input);
    }
    else {
        std::shared_ptr<LinkedListNode> current = GetRoot();
        while (current->nextNode != nullptr) {
            current = current->nextNode;
        }
        current->nextNode = input;
        input->previousNode = current;
        input->nextNode = nullptr;
        SetTail(input);
    }
    SetSize();
}

// ClearList - Clears a linked list
void LinkedList::ClearList() {
    std::shared_ptr<LinkedListNode> current = GetRoot();
    while (current != nullptr) {
        std::shared_ptr<LinkedListNode> temp = current;
        current = current->nextNode;
        temp->nextNode = nullptr;
        temp->previousNode = nullptr;
    }
    this->SetRoot(nullptr);
    this->SetTail(nullptr);
    this->SetSize();
}

// InitNode - Initializes a node that will belong to a linked list
std::shared_ptr<LinkedListNode> LinkedList::InitNode(float input) {
    std::shared_ptr<LinkedListNode> retNode(new LinkedListNode);
    retNode->value = input;
    retNode->previousNode = nullptr;
    retNode->nextNode = nullptr;
    return retNode;
}

// PopNode - Removes the last node of the linked list and returns it
std::shared_ptr<LinkedListNode> LinkedList::PopNode() {
    std::shared_ptr<LinkedListNode> returnNode(new LinkedListNode);
    if (GetRoot() == nullptr) {
        SetSize();
        return nullptr;
    }
    else if (GetRoot()->previousNode == nullptr && GetRoot()->nextNode == nullptr) {
        returnNode = GetRoot();
        SetRoot(nullptr);
        SetTail(nullptr);
    }
    else {
        std::shared_ptr<LinkedListNode> current = GetRoot();
        while (current->nextNode != nullptr) {
            current = current->nextNode;
        }
        returnNode = current;
        current->previousNode->nextNode = nullptr;
        if (current->previousNode->previousNode == nullptr) {
            SetRoot(current->previousNode);
        }
        SetTail(current->previousNode);
    }
    SetSize();
    return returnNode;
}

// PrintList - Prints the contents in a linked list
void LinkedList::PrintList() {
    std::shared_ptr<LinkedListNode> current = GetRoot();
    if (current == nullptr) {
        std::cout << "Empty list." << std::endl;
    }
    while (current != nullptr) {
        std::cout << "Address: " << current << ", Value: " << current->value << ", Previous: " << current->previousNode << ", Next: " << current->nextNode << ", Size: " << GetSize() << " | ";
        current = current->nextNode;
    }
    std::cout << std::endl;
}

// ----- ----- ----- ----- ----- ----- ----- Mutators ----- ----- ----- ----- ----- ----- ----- ----- ----- //
// ----- ----- ----- ----- Getter Functions ----- ----- ----- ----- //
// GetRoot - Retrieves the root node of a linked list
std::shared_ptr<LinkedListNode>& LinkedList::GetRoot() {
    return rootNode;
}

// GetSize - Retrieves the size of the linked list
int& LinkedList::GetSize() {
    return listSize;
}

// GetTail - Retrieves the tail node of a linked list
std::shared_ptr<LinkedListNode>& LinkedList::GetTail() {
    return tailNode;
}

// ----- ----- ----- ----- Setter Functions ----- ----- ----- ----- //
// SetRoot - Sets the root node of a linked list
void LinkedList::SetRoot(std::shared_ptr<LinkedListNode> input) {
    rootNode = input;
}

// SetSize - Sets the size of the linked list
void LinkedList::SetSize() {
    listSize = 0;
    std::shared_ptr<LinkedListNode> current = GetRoot();
    while (current != nullptr) {
        listSize++;
        current = current->nextNode;
    }
}

// SetTail - Sets the tail node of a linked list
void LinkedList::SetTail(std::shared_ptr<LinkedListNode> input) {
    tailNode = input;
}