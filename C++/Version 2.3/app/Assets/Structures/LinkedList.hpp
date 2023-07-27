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
    void InsertNode(std::shared_ptr<node<customType>> input, int index); // Insert node 
    std::shared_ptr<node<customType>> PopNode(); // Pop node
    void PrintList(); // Print list
    void RemoveNode(int index); // Removes node
    std::shared_ptr<node<customType>> RetrieveNode(int index); // Retrieves node
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
    this->SetRoot(initRoot);
    this->SetTail(initTail);
    this->SetSize();
}

// Class de-constructor
template <typename customType>
LinkedList<customType>::~LinkedList() {}

// AppendNode - Adds a node to the end of the linked list
template <typename customType>
void LinkedList<customType>::AppendNode(std::shared_ptr<node<customType>>& input) {
    if (this->GetRoot() == nullptr) {
        input->previousNode = nullptr;
        input->nextNode = nullptr;
        this->SetRoot(input);
        this->SetTail(input);
    }
    else {
        std::shared_ptr<node<customType>> current = this->GetRoot();
        while (current->nextNode != nullptr) {
            current = current->nextNode;
        }
        current->nextNode = input;
        input->previousNode = current;
        input->nextNode = nullptr;
        this->SetTail(input);
    }
    this->SetSize();
}

// ClearList - Clears a linked list
template <typename customType>
void LinkedList<customType>::ClearList() {
    std::shared_ptr<node<customType>> current = this->GetRoot();
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

// InsertNode - Inserts a node into a linked list at a given index
template <typename customType>
void LinkedList<customType>::InsertNode(std::shared_ptr<node<customType>> input, int index) {
    if (index == 0) {
        if (this->GetRoot() == nullptr) {
            this->SetRoot(input);
            this->SetTail(input);
        }
        else {
            this->GetRoot()->previousNode = input;
            input->nextNode = this->GetRoot();
            input->previousNode = nullptr;
            this->SetRoot(input);
        }
    }
    else if (index <= GetSize()) {
        std::shared_ptr<node<customType>> current = this->GetRoot();
        std::vector<std::shared_ptr<node<customType>>> nodes;
        while (current != nullptr) {
            nodes.push_back(current);
            current = current->nextNode;
        }
        current = this->GetRoot();
        for (int i = 0; i < nodes.size(); i++) {
            if (i == index - 1) {
                input->nextNode = current->nextNode;
                input->previousNode = current;
                if (current->nextNode) {
                    current->nextNode->previousNode = input;
                }
                current->nextNode = input;
                if (input->nextNode == nullptr) {
                    this->SetTail(input);
                }
                break;
            }
            current = current->nextNode;
        }
        this->SetSize();
    }
    else {
        this->AppendNode(input);
    }
}

// PopNode - Removes the last node of the linked list and returns it
template <typename customType>
std::shared_ptr<node<customType>> LinkedList<customType>::PopNode() {
    std::shared_ptr<node<customType>> returnNode(new node<customType>);
    if (this->GetRoot() == nullptr) {
        this->SetSize();
        return nullptr;
    }
    else if (GetRoot()->previousNode == nullptr && this->GetRoot()->nextNode == nullptr) {
        returnNode = GetRoot();
        this->SetRoot(nullptr);
        this->SetTail(nullptr);
    }
    else {
        std::shared_ptr<node<customType>> current = this->GetRoot();
        while (current->nextNode != nullptr) {
            current = current->nextNode;
        }
        returnNode = current;
        current->previousNode->nextNode = nullptr;
        if (current->previousNode->previousNode == nullptr) {
            this->SetRoot(current->previousNode);
        }
        this->SetTail(current->previousNode);
    }
    this->SetSize();
    return returnNode;
}

// PrintList - Prints the contents in a linked list
template <typename customType>
void LinkedList<customType>::PrintList() {
    std::shared_ptr<node<customType>> current = this->GetRoot();
    if (current == nullptr) {
        std::cout << "Empty list." << std::endl;
    }
    while (current != nullptr) {
        std::cout << "Previous: " << current->previousNode << ", Current: " << current << ", Next: " << current->nextNode << " | ";
        current = current->nextNode;
    }
    std::cout << " Size: " << this->GetSize() << std::endl;
}

// RemoveNode - Removes a node at a given index
template <typename customType>
void LinkedList<customType>::RemoveNode(int index) {
    std::shared_ptr<node<customType>> foundNode = this->RetrieveNode(index);
    if (foundNode == this->GetRoot()) {
        if (this->GetRoot() != nullptr) {
            if (foundNode->nextNode) {
                this->SetRoot(foundNode->nextNode);
                this->GetRoot()->previousNode = nullptr;
                if (this->GetRoot()->nextNode == nullptr) {
                    this->SetTail(this->GetRoot());
                }
            }
            else {
                this->SetRoot(nullptr);
                this->SetTail(nullptr);
            }
        }
        else {
            this->SetRoot(foundNode);
            this->SetTail(foundNode);
        }
    }
    else if (foundNode == this->GetTail()) {
        if (this->GetTail()->previousNode) {
            this->GetTail()->previousNode->nextNode = nullptr;
            this->SetTail(this->GetTail()->previousNode);
            if (GetTail()->previousNode == nullptr && GetTail()->nextNode == nullptr) {
                this->SetRoot(this->GetTail());
            }
        }
        else {
            this->SetTail(nullptr);
            this->SetRoot(nullptr);
        }
    }
    else {
        if (foundNode->nextNode) {
            foundNode->previousNode->nextNode = foundNode->nextNode;
            foundNode->nextNode->previousNode = foundNode->previousNode;
            this->SetSize();
        }
        else {
            this->SetTail(foundNode);
        }
    }
}

// RetrieveNode - Retrieves a node at a given index
template <typename customType>
std::shared_ptr<node<customType>> LinkedList<customType>::RetrieveNode(int index) {
    std::shared_ptr<node<customType>> ret(new node<customType>);
    if (index == 0) {
        ret = this->GetRoot();
    }
    else if (index == -1 || index >= this->GetSize()) {
        ret = this->GetTail();
    }
    else {
        std::shared_ptr<node<customType>> current = this->GetRoot();
        int indexTracker = 0;
        while (current != nullptr && indexTracker < index) {
            current = current->nextNode;
            indexTracker++;
        }
        ret = current;
    }
    return ret;
}

// ----- ----- ----- ----- ----- ----- ----- Mutators ----- ----- ----- ----- ----- ----- ----- ----- ----- //
// ----- ----- ----- ----- Getter Functions ----- ----- ----- ----- //
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
    this->SetSize();
}

// SetSize - Sets the size of the linked list
template <typename customType>
void LinkedList<customType>::SetSize() {
    listSize = 0;
    std::shared_ptr<node<customType>> current = this->GetRoot();
    while (current != nullptr) {
        listSize++;
        current = current->nextNode;
    }
}

// SetTail - Sets the tail node of a linked list
template <typename customType>
void LinkedList<customType>::SetTail(std::shared_ptr<node<customType>> input) {
    tailNode = input;
    this->SetSize();
}