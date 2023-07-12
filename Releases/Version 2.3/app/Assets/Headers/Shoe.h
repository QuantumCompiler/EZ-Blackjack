// ----- ----- ----- ----- ----- ----- ----- Includes ----- ----- ----- ----- ----- ----- ----- ----- ----- //
#ifndef SHOE_H
#define SHOE_H
#include "../HPP/Card.hpp"
/*  Structure Deck - Struct that resembles a deck of cards
*   Data Members:
*       numOfDecks - Integer value that represents the number of decks in a shoe
*       cardsInShoe - Vector of Card objects that represents the number of cards in a shoe / deck
*       returnedCards - Vector of Card objects that represents the number of cards in a shoe / deck
*       riggedCards - Vector of Card objects that represents the number of cards in a rigged shoe / deck
*/
struct Deck {
    int numOfDecks;
    std::vector<Card> cardsInShoe;
    std::vector<Card> returnedCards;
    std::vector<Card> riggedCards;
};
class Shoe {
public:
    // Constructor
    Shoe();
    // Class Functions
    Shoe& CreateShoe();
    Card Draw();
    void DealCards();
    void EmptyShoe();
    void Shuffle();
    // Setter Functions
    void SetNumOfDecks(const int input);
    void SetCardsInShoe(const Card inputCard);
    void SetRiggedCards(const Card inputCard);
    // Getter Functions
    int GetNumOfDecks() const;
    std::vector<Card> GetCardsInShoe() const;
    std::vector<Card> GetRiggedCards() const;
private:
    Deck gameDeck;
};

#endif