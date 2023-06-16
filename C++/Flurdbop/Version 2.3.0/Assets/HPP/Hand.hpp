// ----- ----- ----- ----- ----- ----- ----- Includes ----- ----- ----- ----- ----- ----- ----- ----- ----- //
#include "../Headers/Hand.h"

// ----- ----- ----- ----- ----- ----- ----- Class Functions ----- ----- ----- ----- ----- ----- ----- ----- ----- //
Hand::Hand() {
}

// ----- ----- ----- ----- ----- ----- ----- Setter Functions ----- ----- ----- ----- ----- ----- ----- ----- ----- //
/*  SetCanBuyInsurance - Sets the private data member "can_buy_insurance" to the input parameter "input"
*   Input:
*       input - Constant boolean value that is assigned to the private data member "can_buy_insurance"
*   Algorithm:
*       * Set the private data member "can_buy_insurance" to the input parameter "input"
*   Output:
*       This function does not return a value
*/
void Hand::SetCanBuyInsurance(const bool input) {
    currentPlayer.can_buy_insurance = input;
}

/*  SetCanDoubleDown - Sets the private data member "can_double_down" to the input parameter "input"
*   Input:
*       input - Constant boolean value that is assigned to the private data member "can_double_down"
*   Algorithm:
*       * Set the private data member "can_double_down" to the input parameter "input"
*   Output:
*       This function does not return a value
*/
void Hand::SetCanDoubleDown(const bool input) {
    currentPlayer.can_double_down = input;
}

/*  SetCanSplitAces - Sets the private data member "can_split_aces" to the input parameter "input"
*   Input:
*       input - Constant boolean value that is assigned to the private data member "can_split_aces"
*   Algorithm:
*       * Set the private data member "can_split_aces" to the input parameter "input"
*   Output:
*       This function does not return a value
*/
void Hand::SetCanSplitAces(const bool input) {
    currentPlayer.can_split_aces = input;
}

/*  SetCanSplitHand - Sets the private data member "can_split_hand" to the input parameter "input"
*   Input:
*       input - Constant boolean value that is assigned to the private data member "can_split_hand"
*   Algorithm:
*       * Set the private data member "can_split_hand" to the input parameter "input"
*   Output:
*       This function does not return a value
*/
void Hand::SetCanSplitHand(const bool input) {
    currentPlayer.can_split_hand = input;
}

/*  SetChoseBuyInsurace - Sets the private data member "chose_buy_insurance" to the input parameter "input"
*   Input:
*       input - Constant boolean value that is assigned to the private data member "chose_buy_insurance"
*   Algorithm:
*       * Set the private data member "chose_buy_insurance" to the input parameter "input"
*   Output:
*       This function does not return a value
*/
void Hand::SetChoseBuyInsurace(const bool input) {
    currentPlayer.chose_buy_insurance = input;
}

/*  SetChoseDoubleDown - Sets the private data member "chose_double_down" to the input parameter "input"
*   Input:
*       input - Constant boolean value that is assigned to the private data member "chose_double_down"
*   Algorithm:
*       * Set the private data member "chose_double_down" to the input parameter "input"
*   Output:
*       This function does not return a value
*/
void Hand::SetChoseDoubleDown(const bool input) {
    currentPlayer.chose_double_down = input;
}

/*  SetChoseSplitAces - Sets the private data member "chose_split_aces" to the input parameter "input"
*   Input:
*       input - Constant boolean value that is assigned to the private data member "chose_split_aces"
*   Algorithm:
*       * Set the private data member "chose_split_aces" to the input parameter "input"
*   Output:
*       This function does not return a value
*/
void Hand::SetChoseSplitAces(const bool input) {
    currentPlayer.chose_split_aces = input;
}

/*  SetChoseSplitHand - Sets the private data member "chose_split_hand" to the input parameter "input"
*   Input:
*       input - Constant boolean value that is assigned to the private data member "chose_split_hand"
*   Algorithm:
*       * Set the private data member "chose_split_hand" to the input parameter "input"
*   Output:
*       This function does not return a value
*/
void Hand::SetChoseSplitHand(const bool input) {
    currentPlayer.chose_split_hand = input;
}

/*  SetChoseSplitHand - Sets the private data member "has_hit" to the input parameter "input"
*   Input:
*       input - Constant boolean value that is assigned to the private data member "has_hit"
*   Algorithm:
*       * Set the private data member "has_hit" to the input parameter "input"
*   Output:
*       This function does not return a value
*/
void Hand::SetHasHit(const bool input) {
    currentPlayer.has_hit = input;
}

/*  SetBankTotal - Sets the private data member "bank_total" to the rounded input parameter "input"
*   Input:
*       input - Const float value passed by reference that is used to later be assigned to the private data member "bank_total"
*   Algorithm:
*       * Create a float value "rounded_input" that is set to the rounded value of "input"
*       * Set the private data member "bank_total" to the parameter "rounded_input"
*   Output:
*       This function does not return a value
*/
void Hand::SetBankTotal(const float& input) {
    float rounded_input = round_input(input);
    currentPlayer.bank_total = rounded_input;
    SetDisplayBankTotal();
}

/*  SetNet - Sets the private data member "net" to the rounded input parameter "input"
*   Input:
*       input - Constant float value passed by reference that is used to later be assigned to the private data member "net"
*   Algorithm:
*       * Create a float value "rounded_input" that is set to the rounded value of "input"
*       * Set the private data member "net" to the parameter "rounded_input"
*   Output:
*       This function does not return a value
*/
void Hand::SetNet(const float& input) {
    float rounded_input = round_input(input);
    currentPlayer.net = rounded_input;
    SetDisplayNet();
}

/*  SetWager - Sets the private data member "wager" to the rounded input parameter "input"
*   Input:
*       input - Constant float value passed by reference that is used to later be assigned to the private data member "wager"
*   Algorithm:
*       * Create a float value "rounded_input" that is set to the rounded value of "input"
*       * Set the private data member "wager" to the parameter "rounded_input"
*   Output:
*       This function does not return a value
*/
void Hand::SetWager(const float& input) {
    float rounded_input = round_input(input);
    currentPlayer.wager = rounded_input;
    SetDisplayWager();
}

/*  SetInsuranceWager - Sets the private data member "insurance_wager" to the rounded input parameter "input"
*   Input:
*       input - Constant float value passed by reference that is used to later be assigned to the private data member "insurance_wager"
*   Algorithm:
*       * Create a float value "rounded_input" that is set to the rounded value of "input"
*       * Set the private data member "insurance_wager" to the parameter "rounded_input"
*   Output:
*       This function does not return a value
*/
void Hand::SetInsuranceWager(const float& input) {
    float rounded_input = round_input(input);
    currentPlayer.insurance_wager = rounded_input;
    SetDisplayInsuranceWager();
}

/*  SetCardsTotal - Sets the private data member "cards_total" to the input parameter "input"
*   Input:
*       input - Constant integer value passed by reference that is assigned to the private data member "cards_total"
*   Algorithm:
*       * Set the private data member "cards_total" to the input parameter "input"
*   Output:
*       This function does not return a value
*/
void Hand::SetCardsTotal(const int& input) {
    currentPlayer.cards_total = input;
    SetDisplayCardsTotal();
}

/*  SetIndividualHands - Sets the private data member "individual_hands" to the input parameter "input"
*   Input:
*       input - Constant integer value passed by reference that is assigned to the private data member "individual_hands"
*   Algorithm:
*       * Set the private data member "individual_hands" to the input parameter "input"
*   Output:
*       This function does not return a value
*/
void Hand::SetIndividualHands(const int& input) {
    currentPlayer.individual_hands = input;
}

/*  SetHandsPlayed - Sets the private data member "hands_played" to the input parameter "input"
*   Input:
*       input - Constant integer value passed by reference that is assigned to the private data member "hands_played"
*   Algorithm:
*       * Set the private data member "hands_played" to the input parameter "input"
*   Output:
*       This function does not return a value
*/
void Hand::SetHandsPlayed(const int& input) {
    currentPlayer.hands_played = input;
    SetDisplayHandsPlayed();
}

/*  SetName - Sets the private data member "name" to the input parameter "input"
*   Input:
*       input - Constant string value passed by reference that is assigned to the private data member "name"
*   Algorithm:
*       * Set the private data member "name" to the input parameter "input"
*   Output:
*       This function does not return a value
*/
void Hand::SetName(const std::string& input) {
    currentPlayer.name = input;
    SetDisplayName();
}

/*  SetDisplayName - Sets the private data member "display_name" to a modified version of "name"
*   Input:
*       This function does not require an input
*   Algorithm:
*       * Create a string value "modified_input" that is used to change the private data member "display_name"
*           * If the players name is not "Dealer", the color is set to blue
*           * If the players name is "Dealer", the color is set to red
*       * Set the private data member "display_name" to the parameter "modified_input"
*   Output:
*       This function does not return a value
*/
void Hand::SetDisplayName() {
    std::string modified_input;
    if (GetName() != "Dealer") {
        modified_input = color_text(34, GetName());
    }
    else {
        modified_input = color_text(31, GetName());
    }
    currentPlayer.display_name = modified_input;
}

/*  SetDisplayBankTotal - Sets the private data member "display_bank_total" to a modified version of "bank_total"
*   Input:
*       This function does not require an input
*   Algorithm:
*       * Create a string value "modified_input" that is used to change the private data member "display_bank_total"
*       * Set the private data member "display_bank_total" to the parameter "modified_input"
*   Output:
*       This function does not return a value
*/
void Hand::SetDisplayBankTotal() {
    std::string modified_input = color_text(33, round_to_string(GetBankTotal()));
    currentPlayer.display_bank_total = modified_input;
}

/*  SetDisplayNet - Sets the private data member "display_net" to a modified version of "net"
*   Input:
*       This function does not require an input
*   Algorithm:
*       * Create a string value "modified_input" that is used to change the private data member "display_net"
*       * Set the private data member "display_net" to the parameter "modified_input"
*   Output:
*       This function does not return a value
*/
void Hand::SetDisplayNet() {
    std::string modified_input = color_text(33, round_to_string(GetNet()));
    currentPlayer.display_net = modified_input;
}

/*  SetDisplayWager - Sets the private data member "display_wager" to a modified version of "wager"
*   Input:
*       This function does not require an input
*   Algorithm:
*       * Create a string value "modified_input" that is used to change the private data member "display_wager"
*       * Set the private data member "display_wager" to the parameter "modified_input"
*   Output:
*       This function does not return a value
*/
void Hand::SetDisplayWager() {
    std::string modified_input = color_text(31, round_to_string(GetWager()));
    currentPlayer.display_wager = modified_input;
}

/*  SetDisplayInsuranceWager - Sets the private data member "display_insurance_wager" to a modified version of "insurance_wager"
*   Input:
*       This function does not require an input
*   Algorithm:
*       * Create a string value "modified_input" that is used to change the private data member "display_insurance_wager"
*       * Set the private data member "display_insurance_wager" to the parameter "modified_input"
*   Output:
*       This function does not return a value
*/
void Hand::SetDisplayInsuranceWager() {
    std::string modified_input = color_text(31, round_to_string(GetInsuranceWager()));
    currentPlayer.display_insurance_wager = modified_input;
}

/*  SetDisplayCardsTotal - Sets the private data member "display_cards_total" to a modified version of "cards_total"
*   Input:
*       This function does not require an input
*   Algorithm:
*       * Create a string value "modified_input" that is used to change the private data member "display_cards_total"
*       * Set the private data member "display_cards_total" to the parameter "modified_input"
*   Output:
*       This function does not return a value
*/
void Hand::SetDisplayCardsTotal() {
    std::string modified_input = color_text(35, std::to_string(GetCardsTotal()));
    currentPlayer.display_cards_total = modified_input;
}

/*  SetDisplayHandsPlayed - Sets the private data member "display_hands_played" to a modified version of "hands_played"
*   Input:
*       This function does not require an input
*   Algorithm:
*       * Create a string value "modified_input" that is used to change the private data member "display_hands_played"
*       * Set the private data member "display_hands_played" to the parameter "modified_input"
*   Output:
*       This function does not return a value
*/
void Hand::SetDisplayHandsPlayed() {
    std::string modified_input = color_text(35, std::to_string(GetHandsPlayed()));
    currentPlayer.display_hands_played = modified_input;
}

// ----- ----- ----- ----- ----- ----- ----- Getter Functions ----- ----- ----- ----- ----- ----- ----- ----- ----- //
// GetCanBuyInsurance - Retrieves the private data member "can_buy_insurance"
bool Hand::GetCanBuyInsurance() const {
    return currentPlayer.can_buy_insurance;
}

// GetCanDoubleDown - Retrieves the private data member "can_double_down"
bool Hand::GetCanDoubleDown() const {
    return currentPlayer.can_double_down;
}

// GetCanSplitAces - Retrieves the private data member "can_split_aces"
bool Hand::GetCanSplitAces() const {
    return currentPlayer.can_split_aces;
}

// GetCanSplitHand - Retrieves the private data member "can_split_hand"
bool Hand::GetCanSplitHand() const {
    return currentPlayer.can_split_hand;
}

// GetChoseBuyInsurance - Retrieves the private data member "chose_buy_insurance"
bool Hand::GetChoseBuyInsurance() const {
    return currentPlayer.chose_buy_insurance;
}

// GetChoseDoubleDown - Retrieves the private data member "chose_double_down"
bool Hand::GetChoseDoubleDown() const {
    return currentPlayer.chose_double_down;
}

// GetChoseSplitAces - Retrieves the private data member "chose_split_aces"
bool Hand::GetChoseSplitAces() const {
    return currentPlayer.chose_split_aces;
}

// GetChoseSplitHand - Retrieves the private data member "chose_split_hand"
bool Hand::GetChoseSplitHand() const {
    return currentPlayer.chose_split_hand;
}

// GetHasHit - Retrieves the private data member "has_hit"
bool Hand::GetHasHit() const {
    return currentPlayer.has_hit;
}

// GetBankTotal - Retrieves the private data member "bank_total"
float Hand::GetBankTotal() const {
    return currentPlayer.bank_total;
}

// GetNet - Retrieves the private data member "net"
float Hand::GetNet() const {
    return currentPlayer.net;
}

// GetWager - Retrieves the private data member "wager"
float Hand::GetWager() const {
    return currentPlayer.wager;
}

// GetInsuranceWager - Retrieves the private data member "insurance_wager"
float Hand::GetInsuranceWager() const {
    return currentPlayer.insurance_wager;
}

// GetCardsTotal - Retrieves the private data member "cards_total"
int Hand::GetCardsTotal() const {
    return currentPlayer.cards_total;
}

// GetIndividualHands - Retrieves the private data member "individual_hands"
int Hand::GetIndividualHands() const {
    return currentPlayer.individual_hands;
}

// GetHandsPlayed - Retrieves the private data member "hands_played"
int Hand::GetHandsPlayed() const {
    return currentPlayer.hands_played;
}

// GetName - Retrieves the private data member "name"
std::string Hand::GetName() const {
    return currentPlayer.name;
}

// GetDisplayName - Retrieves the private data member "display_name"
std::string Hand::GetDisplayName() const {
    return currentPlayer.display_name;
}

// GetDisplayBankTotal - Retrieves the private data member "display_bank_total"
std::string Hand::GetDisplayBankTotal() const {
    return currentPlayer.display_bank_total;
}

// GetDisplayNet - Retrieves the private data member "display_net"
std::string Hand::GetDisplayNet() const {
    return currentPlayer.display_net;
}

// GetDisplayWager - Retrieves the private data member "display_wager"
std::string Hand::GetDisplayWager() const {
    return currentPlayer.display_wager;
}

// GetDisplayInsuranceWager - Retrieves the private data member "display_insurance_wager"
std::string Hand::GetDisplayInsuranceWager() const {
    return currentPlayer.display_insurance_wager;
}

// GetDisplayCardsTotal - Retrieves the private data member "display_cards_total"
std::string Hand::GetDisplayCardsTotal() const {
    return currentPlayer.display_cards_total;
}

// GetDisplayHandsplayed - Retrieves the private data member "display_hands_played"
std::string Hand::GetDisplayHandsplayed() const {
    return currentPlayer.display_hands_played;
}