// ----- ----- ----- ----- ----- ----- ----- Includes ----- ----- ----- ----- ----- ----- ----- ----- ----- //
#ifndef SHOE_H
#define SHOE_H
#include "../HPP/Card.hpp"
/*  Structure Deck - Struct that resembles a deck of cards
*   Data Members:
*       displayRunningCount - String value that represents the display value for the count of a shoe
*       numOfDecks - Integer value that represents the number of decks in a shoe
*       runningCount - Integer value that represents the count of a current shoe
*       cards - Vector of Card objects that represents the number of cards in a shoe / deck
*/
struct Deck {
    // Integers
    int numOfDecks;
    int runningCount;
    // Strings
    std::string displayRunningCount;
    // Linked Lists
    std::shared_ptr<LinkedList<Card>> cards;
};
class Shoe {
public:
    // Constructors
    Shoe(); // Constructor
    ~Shoe(); // De-Constructor
    // Class Functions
    Shoe CopyShoe(const std::shared_ptr<Shoe> input);
    Shoe CreateShoePrompt(); // Creates shoe of cards
    Shoe CreateShoeSim(); // Creates a shoe for a simulate game
    std::shared_ptr<Card> Draw(); // Removes last card from shoe
    void EmptyShoe(); // Empties a shoe of cards
    void Shuffle(); // Shuffles shoe of cards
    // Setter Functions
    void SetCardsInShoe(std::shared_ptr<node<Card>>& input); // Mutates "cards"
    void SetDisplayRunningCount(); // Mutates "displayRunningCount"
    void SetNumOfDecks(const int input); // Mutates "numOfDecks"
    void SetRunningCount(std::shared_ptr<Card> input);
    // Getter Functions
    std::string& GetDisplayRunningCount(); // Retrieves "displayRunningCount"
    int& GetNumOfDecks(); // Retrieves "numOfDecks"
    int& GetRunningCount(); // Retrieves "runningCount"
    std::shared_ptr<LinkedList<Card>>& GetCardsInShoe(); // Retrieves "cards"
private:
    std::shared_ptr<Deck> deck; // Private data member that encapsulates the Deck structure
};

#endif