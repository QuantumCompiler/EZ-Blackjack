// ----- ----- ----- ----- ----- ----- ----- Includes ----- ----- ----- ----- ----- ----- ----- ----- ----- //
#include "../Headers/Shoe.h"
// ----- ----- ----- ----- ----- ----- ----- Class Functions ----- ----- ----- ----- ----- ----- ----- ----- ----- //
/*  Constructor for Shoe Class
*   Initialization:
*       gameDeck.numOfDecks is initialized to be zero
*       gameDeck.cardsInShoe is initialized to be empty
*       gameDeck.returnedCards is initialized to be empty
*       gameDeck.riggedCards is initialized to be empty
*/
Shoe::Shoe() {
    gameDeck.numOfDecks = 0;
    gameDeck.cardsInShoe = {};
    gameDeck.returnedCards = {};
    gameDeck.riggedCards = {};
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
Shoe& Shoe::CreateShoe() {
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
                SetCardsInShoe(Card(rank, suit));
            }
        }
    }
    // Shuffle the shoe of cards
    this->Shuffle();
    // Return the shoe of cards
    return *this;
}

/*  Draw - Function that removes a card from a vector and returns that Card object
*   Input:
*       This function does not have any input parameters
*   Algorithm:
*       * This function first checks to see if the "gameDeck.riggedCards" vector is empty
*           * If this vector is empty, then we remove a card from the back of the "gameDeck.cardsInShoe"
*             and return that Card object
*           * If this vector is not empty, we remove a card from the back of the "gameDeck.riggedCards"
*             and return that Card object
*   Output:
*       This function returns a Card object that is pulled from one of two possible vectors
*/
Card Shoe::Draw() {
    // Remove card for back of "cardsInShoe"
    if (gameDeck.riggedCards.empty()) {
        Card cardDrawn = gameDeck.cardsInShoe.back();
        gameDeck.cardsInShoe.pop_back();
        return cardDrawn;
    }
    // Remove card from back of "riggedCards"
    else if (gameDeck.riggedCards.size() > 0) {
        Card cardDrawn = gameDeck.riggedCards.back();
        gameDeck.riggedCards.pop_back();
        return cardDrawn;
    }
    // Default to removing from "cardsInShoe"
    else {
        Card cardDrawn = gameDeck.cardsInShoe.back();
        gameDeck.cardsInShoe.pop_back();
        return cardDrawn;
    }
}

/*  EmptyShoe - Empties the shoe that is in question
*   Input:
*       This function does not have any input parameters
*   Algorithm:
*       * Set all struct data members to empty or zero
*   Output:
*       This function does not return a value, but it modifies the data structure elements
*/
void Shoe::EmptyShoe() {
    // Clear all vectors of cards
    gameDeck.cardsInShoe.clear();
    gameDeck.returnedCards.clear();
    gameDeck.riggedCards.clear();
}

/*  Shuffle - This function shuffles the "gameDeck.cardsInShoe" vector
*   Input:
*       This function does not have any input parameters
*   Algorithm:
*       * We first create an object "random" of type "std::random_device" to generate a hardware-based random number
*       * We then create an object "g" of type "std::mt19936" to generate a random number with seed "random()"
*       * We then invoke the "shuffle" function to shuffle our "gameDeck.cardsInShoe" vector with our random number "g"
*   Output:
*       This function does not return a value
*/
void Shoe::Shuffle() {
    // Choose random number
    std::random_device random;
    std::mt19937 g(random());
    shuffle(gameDeck.cardsInShoe.begin(), gameDeck.cardsInShoe.end(), g);
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
    gameDeck.numOfDecks = input;
}

/*
*   SetCardsInShoe - Function that adds a Card object to the private data member "gameDeck.cardsInShoe"
*   Input:
*       inputCard - Card object that is to be pushed to the back of the private data member "gameDeck.cardsInShoe"
*   Algorithm:
*       * We use the "push_back" function to insert the input parameter to the back of the aforementioned private data member
*   Output:
*       This function does not return a value
*/
void Shoe::SetCardsInShoe(const Card inputCard) {
    gameDeck.cardsInShoe.push_back(inputCard);
}

/*
*   SetRiggedCards - Function that adds a Card object to the private data member "gameDeck.riggedCards"
*   Input:
*       inputCard - Card object that is to be pushed to the back of the private data member "gameDeck.riggedCards"
*   Algorithm:
*       * We use the "push_back" function to insert the input parameter to the back of the aforementioned private data member
*   Output:
*       This function does not return a value
*/
void Shoe::SetRiggedCards(const Card inputCard) {
    gameDeck.riggedCards.push_back(inputCard);
}

// ----- ----- ----- ----- ----- ----- ----- Getter Functions ----- ----- ----- ----- ----- ----- ----- ----- ----- //

// GetNumOfDecks - Retrieves the private data member "numOfDecks"
int Shoe::GetNumOfDecks() const {
    return gameDeck.numOfDecks;
}

// GetCardsInShoe - Retrieves the private data member "cardsInShoe"
std::vector<Card> Shoe::GetCardsInShoe() const {
    return gameDeck.cardsInShoe;
}

// GetRiggedCards - Retrieves the private data member "riggedCards"
std::vector<Card> Shoe::GetRiggedCards() const {
    return gameDeck.riggedCards;
}