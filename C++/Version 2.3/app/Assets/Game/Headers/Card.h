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
    Card(const std::string inputRank, const std::string inputSuit); // Constructor
    Card() : card(std::make_shared<PlayingCard>()) {} // Default constructor
    // Class methods
    bool CheckCardParam(const std::string checking, const std::string feeding);
    friend std::ostream &operator<<(std::ostream &os, Card& currentCard) {
        os << currentCard.GetDisplayRank() << " of " << currentCard.GetDisplaySuit();
        return os;
    }
    // Setter Functions
    void SetCardValue(std::shared_ptr<PlayingCard> inputCard); // Sets card value
    void SetDisplayRank(std::shared_ptr<PlayingCard> inputCard); // Sets display rank
    void SetDisplaySuit(std::shared_ptr<PlayingCard> inputCard); // Sets display suit
    void SetDisplayCardValue(std::shared_ptr<PlayingCard> inputCard); // Sets a display card value
    void SetNewCardValue(const int input); // Sets a new card value
    // Getter Functions
    int& GetCardValue(); // Retrieves a cards value
    std::string& GetDisplayRank(); // Retrieves a cards display rank
    std::string& GetDisplaySuit(); // Retrieves a cards display suit
    std::string& GetDisplayCardValue(); // Retrieves a cards display card value
    std::string& GetRank(); // Retrieves a cards rank
    std::string& GetSuit(); // Retrieves a cards suit
private:
    std::shared_ptr<PlayingCard> card;
};
#endif