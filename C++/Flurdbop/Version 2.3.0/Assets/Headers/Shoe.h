// ----- ----- ----- ----- ----- ----- ----- Includes ----- ----- ----- ----- ----- ----- ----- ----- ----- //
#ifndef SHOE_H
#define SHOE_
#include "../HPP/Card.hpp"
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