// ----- ----- ----- ----- ----- ----- ----- Includes ----- ----- ----- ----- ----- ----- ----- ----- ----- //
#ifndef CARD_H
#define CARD_H
#include "../HPP/Utility.hpp"
/*  Structure PlayingCard - Struct to resemble a playing card
*   Data Members:
*       rank - String value that represents a cards rank
*       suit - String value that represents a cards suit
*       displayCardValue - String value that represents a modified version of the "cardValue" data member
*       displayRank - String value that represents a modified version of the "rank" data member
*       displaySuit - String value that represents a modified version of the "suit" data member
*/
struct PlayingCard {
    std::string rank;
    std::string suit;
    std::string displayCardValue;
    std::string displayRank;
    std::string displaySuit;
    int cardValue;
};
class Card {
public:
    // Constructor
    Card(const std::string inputRank, const std::string inputSuit);
    // Class methods
    friend std::ostream &operator<<(std::ostream &os, const Card& currentCard) {
        os << currentCard.GetDisplayRank() << " of " << currentCard.GetDisplaySuit() << ": " << currentCard.GetDisplayCardValue() << std::endl;
        return os;
    }
    // Setter Functions
    void SetDisplayRank(PlayingCard& inputCard);
    void SetDisplaySuit(PlayingCard& inputCard);
    void SetDisplayCardValue(PlayingCard& inputCard);
    void SetCardValue(PlayingCard& inputCard);
    void SetNewCardValue(const int input);
    // Getter Functions
    std::string GetDisplayRank() const;
    std::string GetRank() const;
    std::string GetDisplaySuit() const;
    std::string GetSuit() const;
    std::string GetDisplayCardValue() const;
    int GetCardValue() const;
private:
    PlayingCard card;
};
#endif