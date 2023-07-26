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

/*  CreateShoe - Function that is responsible for creating the shoe that is to be played with
*   Input:
*       This function does not have input parameters
*   Algorithm:
*       * We first check to see if gameDeck.numOfDecks is zero, if it is, we then require an input from the player
*       * We then prompt the user to enter the number of decks they would like to play with
*       * If the response is not an integer value (i.e. The first character is not a digit), then we prompt the player
*         and have them re-enter the number of decks that they would like to play with
*       * If the response is an integer, then we check for if it is greater than zero
*           * If the response is less than or equal to zero, we have the player re-enter their selection for the number
*             of decks that they would like to play with
*       * If the previous checks pass, we exit the while loop and then assemble the shoe with the double nested for-loop
*       * After the deck has been assembled, we invoke the "Shuffle" function to shuffle the deck
*   Output:
*       This function returns a shoe object by referencing the shoe object that is being assembled
*/
Shoe Shoe::CreateShoe() {
    bool needInput = false;
    // If "numOfDecks" is greater than zero, no need to prompt for how many decks to play with
    if (GetNumOfDecks() == 0) {
        needInput = true;
    }
    // Continue to prompt for the number of decks if it "numOfDecks" has not been set
    while(needInput) {
        int input;
        // Prompt player for the number of decks that they would like to play with
        std::cout << std::endl << "Please enter the number of decks you would like to play with: "; time_sleep(1000);
        std::cin >> input; time_sleep(1000);
        const std::type_info& result = typeid(input);
        std::string checkResult = result.name();
        // Check that the result is an integer, if it isn't, require a response again
        if (checkResult != "i") {
            std::cout << std::endl << color_text(31, "Invalid Response") << " of " << color_text(31, std::to_string(input)) << ". Please re-enter your submission." << std::endl; time_sleep(1000);
            clear_terminal();
            checkResult.clear();
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        // The result is an integer
        else if (checkResult == "i") {
            // Result is less than zero, require user to re-enter prompt
            if (input <= 0) {
                std::cout << std::endl << color_text(31, "Invalid Response") << " of " << color_text(31, std::to_string(input)) << ". Please re-enter a positive value." << std::endl; time_sleep(1000);
                clear_terminal();
                checkResult.clear();
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                continue;
            }
            // Result is a positive integer, set "input" to "numOfDecks"
            else {
                SetNumOfDecks(input);
                // Prompt for multiple decks
                if (GetNumOfDecks() > 1) {
                    std::cout << std::endl << "This shoe will be comprised of " << color_text(31, std::to_string(input)) << " decks of cards. " << color_text(31, std::to_string(input * 52))
                    << " cards total." << std::endl; time_sleep(1000);
                }
                // Prompt for singular deck
                else {
                    std::cout << std::endl << "This shoe will be comprised of " << color_text(31, std::to_string(input)) << " deck of cards. " << color_text(31, std::to_string(input * 52))
                    << " cards total." << std::endl; time_sleep(1000);
                }
                break;
            }
        }
    }
    // Construct the deck of cards
    for (int i = 1; i <= GetNumOfDecks(); i++) {
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

/*  Draw - Function that removes a card from a shoe and returns that Card object
*   Input:
*       This function does not have any input parameters
*   Algorithm:

*   Output:
*       This function returns a Card object that is pulled from one of two possible vectors
*/
std::shared_ptr<Card> Shoe::Draw() {
    if (this->GetCardsInShoe()->GetSize() > 0) {
        std::shared_ptr<node<Card>> card = this->GetCardsInShoe()->PopNode();
        std::shared_ptr<Card> ret(new Card(card->data.GetRank(), card->data.GetSuit()));
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
    GetCardsInShoe()->ClearList();
    SetNumOfDecks(0);
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

/*  SetNumOfDecks - Function that sets the private data member "gameDeck.numOfDecks" to the input parameter "input"
*                   to represent the number of decks that will be played with in the game
*   Input:
*       input - Integer value that is to be set to the aforementioned private data member of the current Shoe object
*   Algorithm:
*       * We set the private data member previously mentioned to the input parameter "input"
*   Output:
*       This function does not return a value
*/
void Shoe::SetNumOfDecks(const int input) {
    deck->numOfDecks = input;
}

/* SetCardsInShoe - Function that adds a Card object to the private data member "cards"
*   Input:
*       input - Smart pointer of Card object that is to be pushed to the back of the the "cards"
*   Algorithm:
*       * Append the card object as a node to the linked list "cards"
*   Output:
*       This function does not return a value
*/
void Shoe::SetCardsInShoe(std::shared_ptr<node<Card>>& input) {
    deck->cards->AppendNode(input);
}

// // ----- ----- ----- ----- ----- ----- ----- Getter Functions ----- ----- ----- ----- ----- ----- ----- ----- ----- //

// GetNumOfDecks - Retrieves the private data member "numOfDecks"
int& Shoe::GetNumOfDecks() {
    return deck->numOfDecks;
}

// GetCardsInShoe - Retrieves the private data member "cards"
std::shared_ptr<LinkedList<Card>>& Shoe::GetCardsInShoe() {
    return deck->cards;
}