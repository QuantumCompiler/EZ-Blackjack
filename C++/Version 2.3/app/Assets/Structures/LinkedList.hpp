// ----- ----- ----- ----- ----- ----- ----- Includes ----- ----- ----- ----- ----- ----- ----- ----- ----- //
#include "../Game/Headers/Includes.h"

// Linked List Node
template <typename customType>
struct node {
    // Data members
    customType data;
    // Pointers
    std::shared_ptr<node<customType>> nextNode;
    std::shared_ptr<node<customType>> previousNode;
};

template <typename customType>
class LinkedList {
// Private data members and functions
private:
    // Root and tail nodes of list
    std::shared_ptr<node<customType>> rootNode;
    std::shared_ptr<node<customType>> tailNode;
    // Size of list
    int listSize = 0;
public:
    // Constructor and de-constructor
    LinkedList();
    ~LinkedList();
    // Member functions
    void AppendNode(std::shared_ptr<node<customType>>& input); // Append node
    void ClearList(); // Clear a linked list
    std::shared_ptr<node<customType>> InitNode(const customType& input); // Init node
    std::shared_ptr<node<customType>> InitNode(std::shared_ptr<customType> input); // Init node overload
    std::shared_ptr<node<customType>> PopNode(); // Pop node
    void PrintList(); // Print list
    // ---- ---- ---- Mutator Functions ---- ---- ---- //
    // Getter functions
    std::shared_ptr<node<customType>>& GetRoot(); // Get root of list
    int& GetSize(); // Get size of list
    std::shared_ptr<node<customType>>& GetTail(); // Get tail of list
    // Setter functions
    void SetRoot(std::shared_ptr<node<customType>> input); // Set root of list
    void SetSize(); // Set size of list
    void SetTail(std::shared_ptr<node<customType>> input); // Set tail of list
};

// ----- ----- ----- ----- ----- ----- ----- Member Functions ----- ----- ----- ----- ----- ----- ----- ----- //
// Class constructor
template <typename customType>
LinkedList<customType>::LinkedList() {
    std::shared_ptr<node<customType>> initRoot = nullptr;
    std::shared_ptr<node<customType>> initTail = nullptr;
    SetRoot(initRoot);
    SetTail(initTail);
    SetSize();
}

// Class de-constructor
template <typename customType>
LinkedList<customType>::~LinkedList() {}

// AppendNode - Adds a node to the end of the linked list
template <typename customType>
void LinkedList<customType>::AppendNode(std::shared_ptr<node<customType>>& input) {
    if (GetRoot() == nullptr) {
        input->previousNode = nullptr;
        input->nextNode = nullptr;
        SetRoot(input);
        SetTail(input);
    }
    else {
        std::shared_ptr<node<customType>> current = GetRoot();
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
template <typename customType>
void LinkedList<customType>::ClearList() {
    std::shared_ptr<node<customType>> current = GetRoot();
    while (current != nullptr) {
        std::shared_ptr<node<customType>> temp = current;
        current = current->nextNode;
        temp->nextNode = nullptr;
        temp->previousNode = nullptr;
    }
    this->SetRoot(nullptr);
    this->SetTail(nullptr);
    this->SetSize();
}

// InitNode - Initializes a node that will belong to a linked list
template <typename customType>
std::shared_ptr<node<customType>> LinkedList<customType>::InitNode(const customType& input) {
    std::shared_ptr<node<customType>> ret(new node<customType>{input, nullptr, nullptr});
    return ret;
}
// InitNode - Overload
template <typename customType>
std::shared_ptr<node<customType>> LinkedList<customType>::InitNode(std::shared_ptr<customType> input) {
    std::shared_ptr<node<customType>> ret(new node<customType>{*input, nullptr, nullptr});
    return ret;
}

// PopNode - Removes the last node of the linked list and returns it
template <typename customType>
std::shared_ptr<node<customType>> LinkedList<customType>::PopNode() {
    std::shared_ptr<node<customType>> returnNode(new node<customType>);
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
        std::shared_ptr<node<customType>> current = GetRoot();
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
template <typename customType>
void LinkedList<customType>::PrintList() {
    std::shared_ptr<node<customType>> current = GetRoot();
    if (current == nullptr) {
        std::cout << "Empty list." << std::endl;
    }
    while (current != nullptr) {
        std::cout << "Address: " << current << ", Previous: " << current->previousNode << ", Next: " << current->nextNode << ", Size: " << GetSize() << " | ";
        current = current->nextNode;
    }
    std::cout << std::endl;
}

// // ----- ----- ----- ----- ----- ----- ----- Mutators ----- ----- ----- ----- ----- ----- ----- ----- ----- //
// // ----- ----- ----- ----- Getter Functions ----- ----- ----- ----- //
// GetRoot - Retrieves the root node of a linked list
template <typename customType>
std::shared_ptr<node<customType>>& LinkedList<customType>::GetRoot() {
    return rootNode;
}

// GetSize - Retrieves the size of the linked list
template <typename customType>
int& LinkedList<customType>::GetSize() {
    return listSize;
}

// GetTail - Retrieves the tail node of a linked list
template <typename customType>
std::shared_ptr<node<customType>>& LinkedList<customType>::GetTail() {
    return tailNode;
}

// ----- ----- ----- ----- Setter Functions ----- ----- ----- ----- //
// SetRoot - Sets the root node of a linked list
template <typename customType>
void LinkedList<customType>::SetRoot(std::shared_ptr<node<customType>> input) {
    rootNode = input;
    SetSize();
}

// SetSize - Sets the size of the linked list
template <typename customType>
void LinkedList<customType>::SetSize() {
    listSize = 0;
    std::shared_ptr<node<customType>> current = GetRoot();
    while (current != nullptr) {
        listSize++;
        current = current->nextNode;
    }
}

// SetTail - Sets the tail node of a linked list
template <typename customType>
void LinkedList<customType>::SetTail(std::shared_ptr<node<customType>> input) {
    tailNode = input;
    SetSize();
}