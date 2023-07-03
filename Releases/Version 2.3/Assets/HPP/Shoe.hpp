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
    if (gameDeck.numOfDecks == 0) {
        needInput = true;
    }
    else {}
    while(needInput) {
        int input;
        std::cout << std::endl << "Please enter the number of decks you would like to play with: "; time_sleep(1000);
        std::cin >> input; time_sleep(1000);
        const std::type_info& result = typeid(input);
        std::string checkResult = result.name();
        if (checkResult != "i") {
            std::cout << std::endl << color_text(31, "Invalid Response") << " of " << color_text(31, std::to_string(input)) << ". Please re-enter your submission." << std::endl; time_sleep(1000);
            clear_terminal();
            checkResult.clear();
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        else if (checkResult == "i") {
            if (input <= 0) {
                std::cout << std::endl << color_text(31, "Invalid Response") << " of " << color_text(31, std::to_string(input)) << ". Please re-enter a positive value." << std::endl; time_sleep(1000);
                clear_terminal();
                checkResult.clear();
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                continue;
            }
            else { 
                gameDeck.numOfDecks = input; 
                std::cout << std::endl << "This shoe will be comprised of " << color_text(31, std::to_string(input)) << " decks of cards." << std::endl; time_sleep(1000);
                break;
            }
        }
        else {}
    }
    for (int i = 1; i <= gameDeck.numOfDecks; i++) {
        for (const auto& rank : Ranks) {
            for (const auto& suit : Suits) {
                SetCardsInShoe(Card(rank, suit));
            }
        }
    }
    this->Shuffle();
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
    if (gameDeck.riggedCards.empty()) {
        Card cardDrawn = gameDeck.cardsInShoe.back();
        gameDeck.cardsInShoe.pop_back();
        return cardDrawn;
    }
    else if (gameDeck.riggedCards.size() > 0) {
        Card cardDrawn = gameDeck.riggedCards.back();
        gameDeck.riggedCards.pop_back();
        return cardDrawn;
    }
    else {}
}

/*  DealCards - This function shows the cards that are presently in the shoe that is being played with
*   Input:
*       This function does not have any input parameters
*   Algorithm:
*       * We begin by initializing some parameters that will be used in the algorithm
*           * cardDealt - This is an integer that keeps track of the present card that is being dealt from the shoe
*           * deckCounter - This is an integer that represents the number of decks that are present in the shoe
*           * cardsInShoe - This is an integer that represents the number of cards that are in the shoe that is being played with
*           * riggedCards - This is an integer that represents the number of cards that are in the rigged shoe
*           * cardDealtDisplay - This is a string that represents the present card that has been dealt from the top of the shoe
*           * cardsInShoeDisplay - This is a string that represents the number of cards that are in the shoe that are being played with
*           * riggedCardsDisplay - This is a string that represents the number of cards that are in the rigged shoe
*           * deckCounterDisplay - This is a string that represents the number of decks that are in the game shoe
*       * We then check if the number of rigged cards is zero, if it is, then we do the following
*           * We first remove a card from the "gameDeck.cardsInShoe" vector
*           * Next we color the display values (cardDealtDisplay, cardsInShoeDisplay) and begin showing the cards that are in the game shoe
*           * We check to see if the current cardDealt number mods to zero, if it does, we increment deckCounter by one and output a special
*             console message
*           * If the current cardDealt number does not mod to zero, then we output a different console message
*           * We repeat this process until we have reached the end of the game shoe
*       * If the number of rigged cards is not zero, then we repeat the same process as above but with the rigged cards parameters
*   Output:
8       This function does not return a value
*/
void Shoe::DealCards() {
    std::cout << std::endl << "Here are the cards in the shoe:" << std::endl; time_sleep(1000);
    int cardDealt = 1;
    int deckCounter = 0;
    int cardsInShoe = gameDeck.cardsInShoe.size();
    int riggedCards = gameDeck.riggedCards.size();
    std::string cardDealtDisplay = color_text(33, std::to_string(cardDealt));
    std::string cardsInShoeDisplay = color_text(33, std::to_string(gameDeck.cardsInShoe.size()));
    std::string riggedCardsDisplay = color_text(33, std::to_string(gameDeck.riggedCards.size()));
    std::string deckCounterDisplay = color_text(33, std::to_string(deckCounter));
    if (riggedCards == 0) {
        gameDeck.returnedCards.clear();
        for (int i = 1; i <= cardsInShoe; i++) {
            if (i == 1) {
                std::cout << std::endl << "Dealing the deck(s):" << std::endl << std::endl; time_sleep(1000);
            }
            else {}
            Card drawnCard = Draw();
            gameDeck.returnedCards.push_back(drawnCard);
            cardDealtDisplay = color_text(33, std::to_string(cardDealt));
            cardsInShoeDisplay = color_text(33, std::to_string(gameDeck.cardsInShoe.size()));
            std::cout << "Card dealt number: " << cardDealtDisplay << " - " << drawnCard << std::endl; time_sleep(50);
            if (cardDealt % 52 == 0) {
                deckCounter++;
                deckCounterDisplay = color_text(33, std::to_string(deckCounter));
                if (gameDeck.cardsInShoe.size() > 0) {
                    std::cout << "End of remaining deck " << deckCounterDisplay << ". " << cardDealtDisplay << " cards dealt, " << cardsInShoeDisplay 
                    << " cards remaining in shoe." << std::endl << std::endl; time_sleep(2000);
                }
                else if (gameDeck.cardsInShoe.empty()) {
                    std::cout << std::endl << "End of shoe. Total cards dealt: " << cardDealtDisplay << "." << std::endl << std::endl; time_sleep(2000);
                }
                else {}
            }
            else if (cardDealt % 52 != 0) {
                if (gameDeck.cardsInShoe.empty()) {
                    std::cout << std::endl << "End of shoe. Total cards dealt: " << cardDealtDisplay << "." << std::endl << std::endl; time_sleep(2000);
                }
                else {}
            }
            else {}
            cardDealt += 1;
        }
        gameDeck.cardsInShoe = gameDeck.returnedCards;
        reverse(gameDeck.cardsInShoe.begin(), gameDeck.cardsInShoe.end());
        cardsInShoeDisplay = color_text(33, std::to_string(gameDeck.cardsInShoe.size()));
        std::cout << cardsInShoeDisplay << " cards left in shoe." << std::endl; time_sleep(1000);
    }
    else if (riggedCards > 0) {
        gameDeck.returnedCards.clear();
        for (int i = 1; i <= riggedCards; i++) {
            if (i == 1) {
                std::cout << std::endl << "Dealing the rigged deck:" << std::endl << std::endl; time_sleep(1000);
            }
            else {}
            Card drawnCard = Draw();
            gameDeck.returnedCards.push_back(drawnCard);
            cardDealtDisplay = color_text(33, std::to_string(cardDealt));
            riggedCardsDisplay = color_text(33, std::to_string(gameDeck.cardsInShoe.size()));
            std::cout << "Card dealt number: " << cardDealtDisplay << " - " << drawnCard << std::endl; time_sleep(50);
            if (cardDealt % 52 == 0) {
                deckCounter++;
                deckCounterDisplay = color_text(33, std::to_string(deckCounter));
                if (gameDeck.riggedCards.size() > 0) {
                    std::cout << "End of remaining deck " << deckCounterDisplay << ". " << cardDealtDisplay << " cards dealt, " << riggedCardsDisplay 
                    << " cards remaining in shoe." << std::endl << std::endl; time_sleep(2000);
                }
                else if (gameDeck.riggedCards.empty()) {
                    std::cout << std::endl << "End of shoe." << std::endl << std::endl; time_sleep(2000);
                }
                else {}
            }
            else if (cardDealt % 52 != 0) {
                if (gameDeck.riggedCards.empty()) {
                    std::cout << std::endl << "End of shoe." << std::endl << std::endl; time_sleep(2000);
                }
                else {}
            }
            else {}
            cardDealt += 1;
        }
        gameDeck.riggedCards = gameDeck.returnedCards;
        reverse(gameDeck.riggedCards.begin(), gameDeck.riggedCards.end());
        riggedCardsDisplay = color_text(33, std::to_string(gameDeck.riggedCards.size()));
        std::cout << riggedCardsDisplay << " cards left in shoe." << std::endl; time_sleep(1000);
    }
    else {}
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
    std::random_device random;
    std::mt19937 g(random());
    shuffle(gameDeck.cardsInShoe.begin(), gameDeck.cardsInShoe.end(), g);
}

// ----- ----- ----- ----- ----- ----- ----- Setter Functions ----- ----- ----- ----- ----- ----- ----- ----- ----- //

/*
*   SetNumOfDecks - Function that sets the private data member "gameDeck.numOfDecks" to the input parameter "input"
*                   to represent the number of decks that will be played with in the game
*   Input:
*       input - Integer value that is to be set to the afforementioned private data member of the current Shoe object
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
*       * We use the "push_back" function to insert the input parameter to the back of the afforementioned private data member
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
*       * We use the "push_back" function to insert the input parameter to the back of the afforementioned private data member
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