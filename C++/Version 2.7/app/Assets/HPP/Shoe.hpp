// ----- ----- ----- ----- ----- ----- ----- Includes ----- ----- ----- ----- ----- ----- ----- ----- ----- //
#include "../Headers/Shoe.h"
// ----- ----- ----- ----- ----- ----- ----- Class Functions ----- ----- ----- ----- ----- ----- ----- ----- ----- //
/*  Constructor for Shoe Class
*   Initialization:
*       numOfDecks is initialized to be zero
*       cards is initialized to be empty
*/
Shoe::Shoe() {
    // Create objects on the heap
    deck = std::make_shared<Deck>();
    deck->cards = std::make_shared<LinkedList<Card>>();
    deck->numOfDecks = 0;
    deck->cards->ClearList();
}

// De-Constructor
Shoe::~Shoe() {}

/*  CopyShoe - Copies the cards of one shoe to another
*   Input:
*       input - Constant smart pointer of object type Shoe that represents the shoe being copied
*   Algorithm:
*       * Get the root of the shoe
*       * Copy cards from input to the shoe that is being copied
*       * Return the shoe
*   Output:
*       This function returns a copied shoe object
*/
Shoe Shoe::CopyShoe(const std::shared_ptr<Shoe> input) {
    // Get root of input shoe
    std::shared_ptr<node<Card>> current = input->GetCardsInShoe()->GetRoot();
    // Add cards to current shoe being copied
    while (current != nullptr) {
        std::shared_ptr<Card> currentCard(new Card(current->data.GetRank(), current->data.GetSuit()));
        std::shared_ptr<node<Card>> currentNode = this->GetCardsInShoe()->InitNode(currentCard);
        this->GetCardsInShoe()->AppendNode(currentNode);
        current = current->nextNode;
    }
    // Copy the number of decks value
    this->SetNumOfDecks(input->GetNumOfDecks());
    this->GetRunningCount() = input->GetRunningCount();
    // Return the shoe
    return *this;
}

/*  CreateShoe - Function that is responsible for creating the shoe that is to be played with
*   Input:
*       This function does not have input parameters
*   Algorithm:
*       * We first check to see if gameDeck.numOfDecks is zero, if it is, we then require an input from the player
*       * We then prompt the user to enter the number of decks they would like to play with
*       * Check for valid input
*           * If the input is valid, correctly output the prompt for the number of decks and cards
*           * If the input is invalid, restart the loop
*       * If the previous checks pass, we exit the while loop and then assemble the shoe with the double nested for-loop
*       * After the deck has been assembled, we invoke the "Shuffle" function to shuffle the deck
*   Output:
*       This function returns a shoe object by referencing the shoe object that is being assembled
*/
Shoe Shoe::CreateShoePrompt() {
    bool needInput = false;
    // If "numOfDecks" is greater than zero, no need to prompt for how many decks to play with
    if (this->GetNumOfDecks() == 0) {
        needInput = true;
    }
    // Continue to prompt for the number of decks if it "numOfDecks" has not been set
    while(needInput) {
        int input;
        // Prompt player for the number of decks that they would like to play with
        std::cout << std::endl; rolling_text("Please enter the number of decks you would like to play with: ", printLineSleep);
        std::cin >> input;
        // Check for a valid input
        if (input_validation(input)) {
            // Result is a positive integer, set "input" to "numOfDecks"
            this->SetNumOfDecks(input);
            // Prompt for multiple decks
            if (this->GetNumOfDecks() > 1) {
                std::cout << std::endl; rolling_text("This shoe will be comprised of " + color_text(31, std::to_string(input)) + " decks, " + color_text(31, std::to_string(input * 52)) + " cards total.", printLineSleep); std::cout << std::endl;
            }
            // Prompt for singular deck
            else {
                std::cout << std::endl; rolling_text("This shoe will be comprised of " + color_text(31, std::to_string(input)) + " deck of cards, " + color_text(31, std::to_string(input * 52)) + " cards total.", printLineSleep); std::cout << std::endl;
            }
            break;
        }
        else {
            continue;
        }
    }
    // Construct the deck of cards
    for (int i = 1; i <= this->GetNumOfDecks(); i++) {
        for (const auto& rank : Ranks) {
            for (const auto& suit : Suits) {
                std::shared_ptr<Card> card(new Card(rank, suit));
                std::shared_ptr<node<Card>> node = this->GetCardsInShoe()->InitNode(card);
                SetCardsInShoe(node);
            }
        }
    }
    // Shuffle the shoe of cards
    this->Shuffle();
    // Return the shoe of cards
    return *this;
}

/*  CreateShoeSim - Function that is responsible for creating the shoe that is to be played with in a simulated game
*   Input:
*       This function does not have input parameters
*   Algorithm:
*       * Construct the shoe of cards for the given number of decks
*   Output:
*       This function returns a shoe object by referencing the shoe object that is being assembled
*/
Shoe Shoe::CreateShoeSim() {
    // Construct the deck of cards
    for (int i = 1; i <= this->GetNumOfDecks(); i++) {
        for (const auto& rank : Ranks) {
            for (const auto& suit : Suits) {
                std::shared_ptr<Card> card(new Card(rank, suit));
                std::shared_ptr<node<Card>> node = this->GetCardsInShoe()->InitNode(card);
                this->SetCardsInShoe(node);
            }
        }
    }
    // Shuffle the shoe of cards
    this->Shuffle();
    // Return the shoe of cards
    return *this;
}

/*  Draw - Function that removes a card from a shoe and returns that Card object
*   Input:
*       This function does not have any input parameters
*   Algorithm:
*       * Pop a node from the linked list using "PopNode()"
*       * Create a card object with the information from this node
*       * Update the running count of the shoe
*       * Return the card object
*   Output:
*       This function returns a Card object that is pulled from one of two possible vectors
*/
std::shared_ptr<Card> Shoe::Draw() {
    if (this->GetCardsInShoe()->GetSize() > 0) {
        std::shared_ptr<node<Card>> card = this->GetCardsInShoe()->PopNode();
        std::shared_ptr<Card> ret(new Card(card->data.GetRank(), card->data.GetSuit()));
        this->SetRunningCount(ret);
        return ret;
    }
    else {
        return nullptr;
    }
}

/*  ResetShoe - Empties the shoe that is in question and sets the number of decks to zero
*   Input:
*       This function does not have any input parameters
*   Algorithm:
*       * Set all struct data members to empty or zero
*   Output:
*       This function does not return a value, but it modifies the data structure elements
*/
void Shoe::EmptyShoe() {
    this->GetCardsInShoe()->ClearList();
    this->GetRunningCount() = 0;
}

/*  Shuffle - This function shuffles the cards that are in a shoe
*   Input:
*       This function does not have any input parameters
*   Algorithm:
*       * Create temporary card at root of list and a vector to hold cards
*       * Copy the cards in the list to the vector
*       * Clear the original list of cards
*       * Shuffle the vector of cards
*       * Copy the cards from the vector to the linked list
*   Output:
*       This function does not return a value
*/
void Shoe::Shuffle() {
    // Create temp cards and vector to hold cards
    std::shared_ptr<node<Card>> current = deck->cards->GetRoot();
    std::vector<std::shared_ptr<node<Card>>> cardVector(0);
    // Copy cards to vector
    while (current != nullptr) {
        cardVector.push_back(current);
        current = current->nextNode;
    }
    // Clear the original list of cards
    deck->cards->ClearList();
    // Shuffle cards with "shuffle"
    std::random_device random;
    std::mt19937 g(random());
    shuffle(cardVector.begin(), cardVector.end(), g);
    // Copy all cards to deck of cards
    for (int i = 0; i < cardVector.size(); i++) {
        deck->cards->AppendNode(cardVector.at(i));
    }
}

// ----- ----- ----- ----- ----- ----- ----- Setter Functions ----- ----- ----- ----- ----- ----- ----- ----- ----- //
// SetCardsInShoe - Mutates the private data member "cards" by adding a Card node to a linked list
void Shoe::SetCardsInShoe(std::shared_ptr<node<Card>>& input) {
    deck->cards->AppendNode(input);
}

// SetNumOfDecks - Mutates the private data member "numOfDecks" by assigning it to "input"
void Shoe::SetNumOfDecks(const int input) {
    deck->numOfDecks = input;
}

// SetRunningCount - Mutates the private data member "runningCount" by assigning it to "input"
void Shoe::SetRunningCount(std::shared_ptr<Card> input) {
    deck->runningCount += input->GetCountValue();
    this->SetDisplayRunningCount();
}

void Shoe::SetDisplayRunningCount() {
    deck->displayRunningCount = color_text(31, std::to_string(deck->runningCount));
}

// ----- ----- ----- ----- ----- ----- ----- Getter Functions ----- ----- ----- ----- ----- ----- ----- ----- ----- //
// GetDisplayRunningCount - Retrieves the private data member "displayRunningCount"
std::string& Shoe::GetDisplayRunningCount() {
    return deck->displayRunningCount;
}

// GetNumOfDecks - Retrieves the private data member "numOfDecks"
int& Shoe::GetNumOfDecks() {
    return deck->numOfDecks;
}

// GetRunningCount - Retrieves the private data member "runningCount"
int& Shoe::GetRunningCount() {
    return deck->runningCount;
}

// GetCardsInShoe - Retrieves the private data member "cards"
std::shared_ptr<LinkedList<Card>>& Shoe::GetCardsInShoe() {
    return deck->cards;
}