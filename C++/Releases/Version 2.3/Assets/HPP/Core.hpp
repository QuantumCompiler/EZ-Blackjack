// ----- ----- ----- ----- ----- ----- ----- Includes ----- ----- ----- ----- ----- ----- ----- ----- ----- //
#include "../Headers/Core.h"

/*  check_parameter_in_hand - Checks to see if there is a specific parameter found in a players hand
*   Input:
*       input - Constant Hand object representing the hand we are looking at
*       referenceParameter - Constant string value that represents the type of parameter we are looking for
*                               "R" - This parameter represents rank
*                               "S" - This parameter represents suit
*       checkingParameter - Constant string value that represents the parameter that we are searching for in a players hand
*   Algorithm:
*       * Start iterating through the cards that are fed in as an input parameter "input"
*       * If the reference parameter that we are looking for is a rank
*           * We check to see if the current card matches the rank we are looking for by calling "check_card_parameter"
*           * Otherwise, we move on to the next card in the players hand
*       * If the reference parameter that we are looking for is a suit
*           * We check to see if the current card matches the suit we are looking for by calling "check_card_parameter"
*           * Otherwise, we move on to the next card in the players hand
*       * If neither of the reference parameters match "R" or "S", we automatically return false
*       * If we do not find the rank or suit in a players hand, then we return false by default
*   Output:
*       Boolean value that is returned representing if a specific parameter can be found in a players hand
*/
bool check_parameter_in_hand(const Hand& input, const std::string referenceParameter, const std::string checkingParameter) {
    for (Card current_card : input.GetCards()) {
        if (referenceParameter == "R") {
            if (check_card_parameter(current_card.GetRank(), checkingParameter)) {
                return true;
            }
            else {continue;}
        }
        else if (referenceParameter == "S") {
            if (check_card_parameter(current_card.GetSuit(), checkingParameter)) {
                return true;
            }
            else {continue;}
        }
        else {return false;}
    }
    return false;
}

bool check_same_parameter_in_hand(Hand& input, const std::string referenceParameter, const std::string checkingParameter) {
    std::vector<Card> oneOnward(input.GetCards().begin() + 1, input.GetCards().end());
    for (Card current_card : oneOnward) {
        if (referenceParameter == "R") {
            if (!check_card_parameter(current_card.GetRank(), input.GetCards().at(0).GetRank()) || (!checkingParameter.empty() && !check_card_parameter(current_card.GetRank(), checkingParameter))) {
                return false;
            }
            else {continue;}
        }
        else if (referenceParameter == "S") {
            if (!check_card_parameter(current_card.GetSuit(), input.GetCards().at(0).GetSuit()) || (!checkingParameter.empty()) && !check_card_parameter(current_card.GetSuit(), checkingParameter)) {
                return false;
            }
            else {continue;}
        }
        else {return false;}
    }
    return true;
}

void test_game() {
    Hand testHand;
    testHand.AddCardToHand(Card(Ranks[0], Suits[0]));
    testHand.AddCardToHand(Card(Ranks[0], Suits[1]));
    std::cout << check_same_parameter_in_hand(testHand, "R") << " " << check_same_parameter_in_hand(testHand, "S");
}