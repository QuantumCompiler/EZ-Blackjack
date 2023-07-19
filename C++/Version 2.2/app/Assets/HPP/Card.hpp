// ----- ----- ----- ----- ----- ----- ----- Includes ----- ----- ----- ----- ----- ----- ----- ----- ----- //
#include "../Headers/Card.h"
// ----- ----- ----- ----- ----- ----- ----- Class Functions ----- ----- ----- ----- ----- ----- ----- ----- ----- //
/*  Constructor for Card class
*   Input:
*       inputRank - Constant string value that represents a cards rank
*       inputSuit - Constant string value that represents a cards suit
*   Initialization:
*       card.rank is set to inputRank
*       card.suit is set to inputSuit
*       SetCardValue, SetDisplayRank, SetDisplaySuit, SetDisplayCardValue functions are called to mutate private
*       data members
*/
Card::Card(const std::string inputRank, const std::string inputSuit) {
    card.rank = inputRank;
    card.suit = inputSuit;
    SetCardValue(card);
    SetDisplayRank(card);
    SetDisplaySuit(card);
    SetDisplayCardValue(card);
}

/*  CheckCardParam - Checks to see if a specific parameter is present for a card
*   Input:
*       checkingParam - Constant string value that is being fed into function to check if it matches another
*       feedingParam - Constant string value that is being checked against the feeding parameter
*   Algorithm:
*       * Check to see if the "checkingParam" matches with the "checkingParam"
*   Output:
*       This function returns a boolean value indicating if the two parameters match
*/
bool Card::CheckCardParam(const std::string checkingParam, const std::string feedingParam) {
    return checkingParam == feedingParam;
}

// ----- ----- ----- ----- ----- ----- ----- Setter Functions ----- ----- ----- ----- ----- ----- ----- ----- ----- //
/*  SetDisplayRank - Sets the display value of a cards rank
*   Input:
*       inputCard: PlayingCard struct passed by reference to make changes to private data member "displayRank"
*   Algorithm:
*       * Set the private data member "displayRank" equal to the modified version of "rank"
*   Output:
*       This function does not return a value
*/
void Card::SetDisplayRank(PlayingCard& inputCard) {
    card.displayRank = color_text(32, inputCard.rank);
}

/*  SetDisplaySuit - Sets the display value of a cards suit
*   Input:
*       inputCard: PlayingCard struct passed by reference to make changes to private data member "displaySuit"
*   Algorithm:
*       * Function checks for it a suit is a of a specific kind:
*           * (0,3): Card is a Club or Spade - Console output is changed to purple
*           * (1,2): Card is a Diamond or Heart - Console output is changed to red
*           * Other: Card is an undefined suit - Console output is white
*   Output:
*       This function does not return a value
*/
void Card::SetDisplaySuit(PlayingCard& inputCard) {
    for (int i = 0; i < 4; i++) {
        if (CheckCardParam(inputCard.suit, Suits[i])) {
            switch (i) {
            case 0:
            case 3:
                card.displaySuit = color_text(35, inputCard.suit);
                break;
            case 1:
            case 2:
                card.displaySuit = color_text(31, inputCard.suit);
                break;
            default:
                card.displaySuit = color_text(37, inputCard.suit);
                break;
            }
        }
        else {}
    }
}

/*  SetDisplayCardValue - Sets the display value of a cards value
*   Input:
*       inputCard: PlayingCard struct passed by reference to make changes to the private data member "displayCardValue"
*   Algorithm:
*       * Set the private data member "displayCardValue" to the modified version of "cardValue"
*   Output:
*       This function does not return a value
*/
void Card::SetDisplayCardValue(PlayingCard& inputCard) {
    card.displayCardValue = color_text(31, std::to_string(inputCard.cardValue));
}

/*  SetCardValue - Sets the value of a playing card based off of its rank
*   Input:
*       inputCard: PlayingCard struct passed by reference to make changes to private data member "cardValue"
*   Algorithm:
*       * Function checks for what rank a card is:
*           * Ace: Card value is defaulted to a value of (11) - This can be mutated with another function
*           * (2,3,4,5,6,7,8,9): Card value is defaulted to the integer value of the card
*           * (10,Jack,Queen,King): Card value is defaulted to a value of (10)
*   Output:
*       This function does not return a value
*/
void Card::SetCardValue(PlayingCard& inputCard) {
    for (int i = 0; i < 13; i++) {
        if (CheckCardParam(inputCard.rank, Ranks[i])) {
            switch (i)
            {
            case 0:
                card.cardValue = 11;
                break;
            case 1:
            case 2:
            case 3:
            case 4:
            case 5:
            case 6:
            case 7:
            case 8:
                card.cardValue = std::stoi(Ranks[i]);
                break;
            case 9:
            case 10:
            case 11:
            case 12:
                card.cardValue = 10;
            default:
                break;
            }
        }
        else {}
    }
}

/*  SetNewCardValue - Mutates the private data member "cardValue" to a new integer value
*   Input:
*       input: Integer value that private data member "cardValue" is to be changed to
*   Algorithm:
*       * Set the private data member "cardValue" equal to the input parameter "input"
*       * Set the display card value with the function "SetDisplayCardValue"
*   Output:
*       This function does not return a value
*/
void Card::SetNewCardValue(const int input) {
    card.cardValue = input;
    SetDisplayCardValue(card);
}

// ----- ----- ----- ----- ----- ----- ----- Getter Functions ----- ----- ----- ----- ----- ----- ----- ----- ----- //

// GetRank - Retrieves the private data member "rank"
std::string Card::GetRank() const {
    return card.rank;
}

// GetDisplayRank - Retrieves the private data member "displayRank"
std::string Card::GetDisplayRank() const {
    return card.displayRank;
}

// GetSuit - Retrieves the private data member "suit"
std::string Card::GetSuit() const {
    return card.suit;
}

// GetDisplaySuit - Retrieves the private data member "displaySuit"
std::string Card::GetDisplaySuit() const {
    return card.displaySuit;
}

// GetCardValue - Retrieves the private data member "cardValue"
int Card::GetCardValue() const {
    return card.cardValue;
}

// GetDisplayCardValue - Retrieves the private data member "displayCardValue"
std::string Card::GetDisplayCardValue() const {
    return card.displayCardValue;
}