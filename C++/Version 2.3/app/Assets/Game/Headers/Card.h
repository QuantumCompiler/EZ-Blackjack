// ----- ----- ----- ----- ----- ----- ----- Includes ----- ----- ----- ----- ----- ----- ----- ----- ----- //
#ifndef CARD_H
#define CARD_H
#include "../HPP/Utility.hpp"
#include "../../Structure/HPP/LinkedList.hpp"
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
    bool CheckCardParam(const std::string checking, const std::string feeding);
    friend std::ostream &operator<<(std::ostream &os, Card& currentCard) {
        os << currentCard.GetDisplayRank() << " of " << currentCard.GetDisplaySuit();
        return os;
    }
    // Setter Functions
    void SetCardValue(std::shared_ptr<PlayingCard> inputCard);
    void SetDisplayRank(std::shared_ptr<PlayingCard> inputCard);
    void SetDisplaySuit(std::shared_ptr<PlayingCard> inputCard);
    void SetDisplayCardValue(std::shared_ptr<PlayingCard> inputCard);
    void SetNewCardValue(const int input);
    // Getter Functions
    int& GetCardValue();
    std::string& GetDisplayRank();
    std::string& GetDisplaySuit();
    std::string& GetDisplayCardValue();
    std::string& GetRank();
    std::string& GetSuit();
private:
    std::shared_ptr<PlayingCard> card;
};
#endif