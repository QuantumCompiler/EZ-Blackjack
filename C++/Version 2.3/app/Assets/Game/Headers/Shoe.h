// ----- ----- ----- ----- ----- ----- ----- Includes ----- ----- ----- ----- ----- ----- ----- ----- ----- //
#ifndef SHOE_H
#define SHOE_H
#include "../HPP/Card.hpp"
/*  Structure Deck - Struct that resembles a deck of cards
*   Data Members:
*       numOfDecks - Integer value that represents the number of decks in a shoe
*       cardsInShoe - Vector of Card objects that represents the number of cards in a shoe / deck
*       riggedCards - Vector of Card objects that represents the number of cards in a rigged shoe / deck
*/
struct Deck {
    int numOfDecks;
    std::shared_ptr<LinkedList<Card>> cards;
};
class Shoe {
public:
    // Constructor
    Shoe();
    // Class Functions
    Shoe CreateShoe();
    std::shared_ptr<Card> Draw();
    void EmptyShoe();
    void Shuffle();
    // Setter Functions
    void SetNumOfDecks(const int input);
    void SetCardsInShoe(std::shared_ptr<node<Card>>& input);
    // Getter Functions
    int& GetNumOfDecks();
    std::shared_ptr<LinkedList<Card>>& GetCardsInShoe();
private:
    std::shared_ptr<Deck> deck;
};

#endif