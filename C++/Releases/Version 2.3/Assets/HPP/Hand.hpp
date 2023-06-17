// ----- ----- ----- ----- ----- ----- ----- Includes ----- ----- ----- ----- ----- ----- ----- ----- ----- //
#include "../Headers/Hand.h"

// ----- ----- ----- ----- ----- ----- ----- Class Functions ----- ----- ----- ----- ----- ----- ----- ----- ----- //
/*  Constructor for Hand Class
*   Input:
*       There is no input required for constructing this class
*   Initialization:
*       Boolean Values - All boolean values set to false
*       Float Values - All float values set to zero
*       Integer Values - All integer values set to zero
*       String Values - All string values set to empty
*       Vector Values - All vector values set to empty
*/
Hand::Hand() {
    // Boolean Values Initialization
    SetCanBuyInsurance(false);
    SetCanDoubleDown(false);
    SetCanSplitAces(false);
    SetCanSplitHand(false);
    SetChoseBuyInsurace(false);
    SetChoseDoubleDown(false);
    SetChoseSplitAces(false);
    SetChoseSplitHand(false);
    SetHasHit(false);
    // Float Values Initialization
    SetBankTotal(0.00);
    SetInsuranceWager(0.00);
    SetNet(0.00);
    SetWager(0.00);
    // Intever Values Initialization
    SetCardsTotal(0);
    SetHandsPlayed(0);
    SetIndividualHands(0);
    // String Values Initialization
    GetDisplayBankTotal().clear();
    GetDisplayCardsTotal().clear();
    GetDisplayHandsplayed().clear();
    GetDisplayInsuranceWager().clear();
    GetDisplayName().clear();
    GetDisplayNet().clear();
    GetDisplayWager().clear();
    GetName().clear();
    // Vector Values Initialization
    GetCards().clear();
    GetHandBankTotals().clear();
    GetHandCardTotals().clear();
    GetHandNets().clear();
    GetHandPlayed().clear();
    GetHandWagers().clear();
}

/*  AddCardToHand - Adds a card to a players hand
*   Input:
*       input - Constant card passed by reference that is to be added to a players hand
*   Algorithm:
*       * Calls the "SetCards" function and adds the input parameter "input" to the private data member "cards"
*       * Call "AddHandTotal" function to add up the total in the hand of the player
*   Output:
*       This function returns a Hand object
*/
Hand Hand::AddCardToHand(const Card& input) {
    // Add card to players hand and update hand total
    SetCards(input);
    AddHandTotal();
    return *this;
}

/*  AddHandTotal - Adds the hand total of a current player
*   Input:
*       This function does not have any input parameters
*   Algorithm:
*       * Create two integer vaues; ace_count (Represents the number of aces in a hand), running_hand_value (A running hand value)
*       * Iterate through the cards in a players hand and count how many Aces are present in a players hand
*       * Iterate through the cards in a players hand and do the following:
*           * If the number of Aces in the hand is 1, then set the value of the Ace to 11
*           * If the number of Aces in the hand is greater than 1, then set the current value of the Ace to 1
*           * Update the "running_hand_value" by adding the current cards value to it
*           * Decrease the value of "ace_count" by one, then repeat the loop
*       * Iterate through the cards in a players hand if the "running_hand_value" is greater than 21
*           * If the current card is an Ace, set its value to 1, and add that card value to "running_hand_value"
*           * If the current card is not an Ace, then just add its value to "running_hand_value"
*       * Set the private data member "cardsTotal" to "running_hand_value" using SetCardsTotal
*   Output:
*       This function returns a Hand object after iterating through all the cards in a hand
*/
Hand Hand::AddHandTotal() {
    int ace_count = 0;
    int running_hand_value = 0;
    // Count number of Aces in hand
    for (const Card& current_card : currentPlayer.cards) {
        if (check_card_parameter(current_card.GetRank(), "Ace")) {
            ace_count += 1;
        }
        else {}
    }
    // Change Ace values
    for (Card& current_card : currentPlayer.cards) {
        if (ace_count == 1) {
            // Change Ace value to 11
            if (check_card_parameter(current_card.GetRank(), "Ace")) {
                current_card.SetNewCardValue(11);
            }
            else {}
        }
        else if (ace_count > 1) {
            // Change Ace value to 1
            if (check_card_parameter(current_card.GetRank(), "Ace")) {
                current_card.SetNewCardValue(1);
            }
            else {}
        }
        else {}
        running_hand_value += current_card.GetCardValue();
        ace_count -= 1;
    }
    // Check if current hand is over 21
    if (running_hand_value > 21) {
        running_hand_value = 0;
        for (Card& current_card : currentPlayer.cards)
        {
            // If the card is an Ace, change the value of it to 1
            if (check_card_parameter(current_card.GetRank(), "Ace")) {
                current_card.SetNewCardValue(1);
                running_hand_value += current_card.GetCardValue();
            }
            // If the card is not an Ace, just add value to running_hand_value
            else if (!(check_card_parameter(current_card.GetRank(), "Ace"))) {
                running_hand_value += current_card.GetCardValue();
            }
            else {}
        }
    }
    else {}
    SetCardsTotal(running_hand_value);
    return *this;
}

/*  BankDeposit - Updates the private data member "bankTotal" to represent a players bank total
*   Input:
*       This function does not have any input parameters
*   Algorithm:
*       * First create a float value that represents the bank total of a player prior to depositing
*       * Enter an error catching block that will help us determine if a player has entered a correct value for a bank total
*           * If the value entered is not a float, then we output an error message and clear the inputs
*           * If the value entered is a float or an integer
*               * We check to see if it is less than or equal to zero, if it is, we output an error message and require another input
*               * If it is greater than zero, then we set the private data member "bankTotal" to the "input" with SetBankTotal
*       * We then initialize some values for the statistics tracking of the player
*   Output:
*       This function returns a Hand object after depositing currency into a players bank
*/
Hand Hand::BankDeposit() {
    while (true) {
        float input;
        // Prompt user for deposit
        std::cout << std::endl << "Please enter the amount you'd like to deposit into your bank: "; time_sleep(1000);
        std::cin >> input; time_sleep(1000);
        const std::type_info& result = typeid(input);
        std::string checkResult = result.name();
        // Check if value is not a float or integer
        if (checkResult != "f" || checkResult != "i") {
            std::cout << std::endl << color_text(31, "Invalid Response") << ". Please re-enter your submission." << std::endl; time_sleep(1000);
            clear_terminal();
            checkResult.clear();
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        // Check if value is a float or integer
        else if (checkResult == "f" || checkResult == "i") {
            if (input <= 0) {
                std::cout << std::endl << color_text(31, "Invalid Response") << " of " << color_text(31, std::to_string(round_input(input))) << ". Please re-enter a positive value." << std::endl; time_sleep(1000);
                clear_terminal();
                checkResult.clear();
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                continue;
            }
            else {
                SetBankTotal(input);
                break;
            }
        }
        else {}
    }
    std::cout << std::endl << GetDisplayName() << " has decided to start with: " << GetDisplayBankTotal() << std::endl; time_sleep(1000);
    // Add handsPlayed value to handPlayed
    if (GetHandsPlayed() == 0) {
        SetHandPlayed(GetHandsPlayed());
    }
    else if (GetHandsPlayed() > 0) {
        SetHandPlayed(GetHandsPlayed()+1);
    }
    else {}
    // Add other statistics to their respective vectors
    SetHandWagers(GetWager());
    SetHandNets(GetNet());
    SetHandCardTotals(GetCardsTotal());
    SetHandBankTotals(GetBankTotal());
    return *this;
}

/*  CopyVariables - Copies select data members from one hand to the current hand
*   Input:
*       input - Hand object passed by reference that is used to copy data members from
*   Algorithm:
*       * Copy the name of "input" for the current hand with SetName
*       * Copy the bank total of "input" for the current hand with SetBankTotal
*       * Copy the wager of "input" for the current hand with SetWager
*   Output:
*       This function returns a Hand object after copying select variables
*/
Hand Hand::CopyVariables(Hand& input) {
    SetName(input.GetName());
    SetBankTotal(input.GetBankTotal());
    SetWager(input.GetWager());
    return *this;
}

/*  HitHand - Removes a hand from a given show and adds it a players hand
*   Input:
*       input - Shoe object that is passed by reference where a Card object is being pulled from
*   Algorithm:
*       * Call AddCardToHand() to add a card to the current players hand
*   Output:
*       This function returns a Hand object after adding a card to it
*/
Hand Hand::HitHand(Shoe& input) {
    AddCardToHand(input.Draw());
    return *this;
}

// ----- ----- ----- ----- ----- ----- ----- Setter Functions ----- ----- ----- ----- ----- ----- ----- ----- ----- //
/*  SetCanBuyInsurance - Sets the private data member "canBuyInsurance" to the input parameter "input"
*   Input:
*       input - Constant boolean value that is assigned to the private data member "canBuyInsurance"
*   Algorithm:
*       * Set the private data member "canBuyInsurance" to the input parameter "input"
*   Output:
*       This function does not return a value
*/
void Hand::SetCanBuyInsurance(const bool input) {
    currentPlayer.canBuyInsurance = input;
}

/*  SetCanDoubleDown - Sets the private data member "canDoubleDown" to the input parameter "input"
*   Input:
*       input - Constant boolean value that is assigned to the private data member "canDoubleDown"
*   Algorithm:
*       * Set the private data member "canDoubleDown" to the input parameter "input"
*   Output:
*       This function does not return a value
*/
void Hand::SetCanDoubleDown(const bool input) {
    currentPlayer.canDoubleDown = input;
}

/*  SetCanSplitAces - Sets the private data member "canSplitAces" to the input parameter "input"
*   Input:
*       input - Constant boolean value that is assigned to the private data member "canSplitAces"
*   Algorithm:
*       * Set the private data member "canSplitAces" to the input parameter "input"
*   Output:
*       This function does not return a value
*/
void Hand::SetCanSplitAces(const bool input) {
    currentPlayer.canSplitAces = input;
}

/*  SetCanSplitHand - Sets the private data member "canSplitHand" to the input parameter "input"
*   Input:
*       input - Constant boolean value that is assigned to the private data member "canSplitHand"
*   Algorithm:
*       * Set the private data member "canSplitHand" to the input parameter "input"
*   Output:
*       This function does not return a value
*/
void Hand::SetCanSplitHand(const bool input) {
    currentPlayer.canSplitHand = input;
}

/*  SetChoseBuyInsurace - Sets the private data member "choseBuyInsurance" to the input parameter "input"
*   Input:
*       input - Constant boolean value that is assigned to the private data member "choseBuyInsurance"
*   Algorithm:
*       * Set the private data member "choseBuyInsurance" to the input parameter "input"
*   Output:
*       This function does not return a value
*/
void Hand::SetChoseBuyInsurace(const bool input) {
    currentPlayer.choseBuyInsurance = input;
}

/*  SetChoseDoubleDown - Sets the private data member "choseDoubleDown" to the input parameter "input"
*   Input:
*       input - Constant boolean value that is assigned to the private data member "choseDoubleDown"
*   Algorithm:
*       * Set the private data member "choseDoubleDown" to the input parameter "input"
*   Output:
*       This function does not return a value
*/
void Hand::SetChoseDoubleDown(const bool input) {
    currentPlayer.choseDoubleDown = input;
}

/*  SetChoseSplitAces - Sets the private data member "choseSplitAces" to the input parameter "input"
*   Input:
*       input - Constant boolean value that is assigned to the private data member "choseSplitAces"
*   Algorithm:
*       * Set the private data member "choseSplitAces" to the input parameter "input"
*   Output:
*       This function does not return a value
*/
void Hand::SetChoseSplitAces(const bool input) {
    currentPlayer.choseSplitAces = input;
}

/*  SetChoseSplitHand - Sets the private data member "choseSplitHand" to the input parameter "input"
*   Input:
*       input - Constant boolean value that is assigned to the private data member "choseSplitHand"
*   Algorithm:
*       * Set the private data member "choseSplitHand" to the input parameter "input"
*   Output:
*       This function does not return a value
*/
void Hand::SetChoseSplitHand(const bool input) {
    currentPlayer.choseSplitHand = input;
}

/*  SetChoseSplitHand - Sets the private data member "hasHit" to the input parameter "input"
*   Input:
*       input - Constant boolean value that is assigned to the private data member "hasHit"
*   Algorithm:
*       * Set the private data member "hasHit" to the input parameter "input"
*   Output:
*       This function does not return a value
*/
void Hand::SetHasHit(const bool input) {
    currentPlayer.hasHit = input;
}

/*  SetBankTotal - Sets the private data member "bankTotal" to the rounded input parameter "input"
*   Input:
*       input - Const float value passed by reference that is used to later be assigned to the private data member "bankTotal"
*   Algorithm:
*       * Create a float value "rounded_input" that is set to the rounded value of "input"
*       * Set the private data member "bankTotal" to the parameter "rounded_input"
*   Output:
*       This function does not return a value
*/
void Hand::SetBankTotal(const float& input) {
    float rounded_input = round_input(input);
    currentPlayer.bankTotal = rounded_input;
    SetDisplayBankTotal();
}

/*  SetInsuranceWager - Sets the private data member "insuranceWager" to the rounded input parameter "input"
*   Input:
*       input - Constant float value passed by reference that is used to later be assigned to the private data member "insuranceWager"
*   Algorithm:
*       * Create a float value "rounded_input" that is set to the rounded value of "input"
*       * Set the private data member "insuranceWager" to the parameter "rounded_input"
*   Output:
*       This function does not return a value
*/
void Hand::SetInsuranceWager(const float& input) {
    float rounded_input = round_input(input);
    currentPlayer.insuranceWager = rounded_input;
    SetDisplayInsuranceWager();
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

/*  SetCardsTotal - Sets the private data member "cardsTotal" to the input parameter "input"
*   Input:
*       input - Constant integer value passed by reference that is assigned to the private data member "cardsTotal"
*   Algorithm:
*       * Set the private data member "cardsTotal" to the input parameter "input"
*   Output:
*       This function does not return a value
*/
void Hand::SetCardsTotal(const int& input) {
    currentPlayer.cardsTotal = input;
    SetDisplayCardsTotal();
}

/*  SetHandsPlayed - Sets the private data member "handsPlayed" to the input parameter "input"
*   Input:
*       input - Constant integer value passed by reference that is assigned to the private data member "handsPlayed"
*   Algorithm:
*       * Set the private data member "handsPlayed" to the input parameter "input"
*   Output:
*       This function does not return a value
*/
void Hand::SetHandsPlayed(const int& input) {
    currentPlayer.handsPlayed = input;
    SetDisplayHandsPlayed();
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

/*  SetDisplayName - Sets the private data member "displayName" to a modified version of "name"
*   Input:
*       This function does not require an input
*   Algorithm:
*       * Create a string value "modified_input" that is used to change the private data member "displayName"
*           * If the players name is not "Dealer", the color is set to blue
*           * If the players name is "Dealer", the color is set to red
*       * Set the private data member "displayName" to the parameter "modified_input"
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
    currentPlayer.displayName = modified_input;
}

/*  SetDisplayBankTotal - Sets the private data member "displayBankTotal" to a modified version of "bankTotal"
*   Input:
*       This function does not require an input
*   Algorithm:
*       * Create a string value "modified_input" that is used to change the private data member "displayBankTotal"
*       * Set the private data member "displayBankTotal" to the parameter "modified_input"
*   Output:
*       This function does not return a value
*/
void Hand::SetDisplayBankTotal() {
    std::string modified_input = color_text(33, round_to_string(GetBankTotal()));
    currentPlayer.displayBankTotal = modified_input;
}

/*  SetDisplayNet - Sets the private data member "displayNet" to a modified version of "net"
*   Input:
*       This function does not require an input
*   Algorithm:
*       * Create a string value "modified_input" that is used to change the private data member "displayNet"
*       * Set the private data member "displayNet" to the parameter "modified_input"
*   Output:
*       This function does not return a value
*/
void Hand::SetDisplayNet() {
    std::string modified_input = color_text(33, round_to_string(GetNet()));
    currentPlayer.displayNet = modified_input;
}

/*  SetDisplayWager - Sets the private data member "displayWager" to a modified version of "wager"
*   Input:
*       This function does not require an input
*   Algorithm:
*       * Create a string value "modified_input" that is used to change the private data member "displayWager"
*       * Set the private data member "displayWager" to the parameter "modified_input"
*   Output:
*       This function does not return a value
*/
void Hand::SetDisplayWager() {
    std::string modified_input = color_text(31, round_to_string(GetWager()));
    currentPlayer.displayWager = modified_input;
}

/*  SetDisplayInsuranceWager - Sets the private data member "displayInsuranceWager" to a modified version of "insuranceWager"
*   Input:
*       This function does not require an input
*   Algorithm:
*       * Create a string value "modified_input" that is used to change the private data member "displayInsuranceWager"
*       * Set the private data member "displayInsuranceWager" to the parameter "modified_input"
*   Output:
*       This function does not return a value
*/
void Hand::SetDisplayInsuranceWager() {
    std::string modified_input = color_text(31, round_to_string(GetInsuranceWager()));
    currentPlayer.displayInsuranceWager = modified_input;
}

/*  SetDisplayCardsTotal - Sets the private data member "displayCardsTotal" to a modified version of "cardsTotal"
*   Input:
*       This function does not require an input
*   Algorithm:
*       * Create a string value "modified_input" that is used to change the private data member "displayCardsTotal"
*       * Set the private data member "displayCardsTotal" to the parameter "modified_input"
*   Output:
*       This function does not return a value
*/
void Hand::SetDisplayCardsTotal() {
    std::string modified_input = color_text(35, std::to_string(GetCardsTotal()));
    currentPlayer.displayCardsTotal = modified_input;
}

/*  SetDisplayHandsPlayed - Sets the private data member "displayHandsPlayed" to a modified version of "handsPlayed"
*   Input:
*       This function does not require an input
*   Algorithm:
*       * Create a string value "modified_input" that is used to change the private data member "displayHandsPlayed"
*       * Set the private data member "displayHandsPlayed" to the parameter "modified_input"
*   Output:
*       This function does not return a value
*/
void Hand::SetDisplayHandsPlayed() {
    std::string modified_input = color_text(35, std::to_string(GetHandsPlayed()));
    currentPlayer.displayHandsPlayed = modified_input;
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

/*  SetCards - Adds a Card object to the private data member "cards" using the push_back function
*   Input:
*       input - Constant Card object passed by reference that is to be added to the private data member "cards"
*   Algorithm:
*       * Add the input Card, "input", to the private data member "cards" using the push_back function
*   Output:
*       This function does not return a value
*/
void Hand::SetCards(const Card& input) {
    currentPlayer.cards.push_back(input);
}

/*  SetHandBankTotals - Adds a float value to the private data member "handBankTotals" using the push_back function
*   Input:
*       input - Constant float value passed by reference that is to be added to the private data member "handBankTotals"
*   Algorithm:
*       * Add the input float, "input", to the private data member "handBankTotals" using the push_back function
*   Output:
*       This function does not return a value
*/
void Hand::SetHandBankTotals(const float& input) {
    currentPlayer.handBankTotals.push_back(input);
}

/*  SetHandCardTotals - Adds an integer value to the private data member "handCardTotals" using the push_back function
*   Input:
*       input - Constant integer value passed by reference that is to be added to the private data member "handCardTotals"
*   Algorithm:
*       * Add the input integer, "input", to the private data member "handCardTotals" using the push_back function
*   Output:
*       This function does not return a value
*/
void Hand::SetHandCardTotals(const int& input) {
    currentPlayer.handCardTotals.push_back(input);
}

/*  SetHandNets - Adds a float value to the private data member "handNets" using the push_back function
*   Input:
*       input - Constant float value passed by reference that is to be added to the private data member "handNets"
*   Algorithm:
*       * Add the input float, "input", to the private data member "handNets" using the push_back function
*   Output:
*       This function does not return a value
*/
void Hand::SetHandNets(const float& input) {
    currentPlayer.handNets.push_back(input);
}

/*  SetHandPlayed - Adds an integer value to the private data member "handPlayed" using the push_back function
*   Input:
*       input - Constant integer value passed by reference that is to be added to the private data member "handPlayed"
*   Algorithm:
*       * Add the input integer, "input", to the private data member "handPlayed" using the push_back function
*   Output:
*       This function does not return a value
*/
void Hand::SetHandPlayed(const int& input) {
    currentPlayer.handPlayed.push_back(input);
}

/*  SetHandWagers - Adds a float value to the private data member "handWagers" using the push_back function
*   Input:
*       input - Constant float value passed by reference that is to be added to the private data member "handWagers"
*   Algorithm:
*       * Add the input float, "input", to the private data member "handWagers" using the push_back function
*   Output:
*       This function does not return a value
*/
void Hand::SetHandWagers(const float& input) {
    currentPlayer.handWagers.push_back(input);
}


// ----- ----- ----- ----- ----- ----- ----- Getter Functions ----- ----- ----- ----- ----- ----- ----- ----- ----- //
// GetCanBuyInsurance - Retrieves the private data member "canBuyInsurance"
bool Hand::GetCanBuyInsurance() const {
    return currentPlayer.canBuyInsurance;
}

// GetCanDoubleDown - Retrieves the private data member "canDoubleDown"
bool Hand::GetCanDoubleDown() const {
    return currentPlayer.canDoubleDown;
}

// GetCanSplitAces - Retrieves the private data member "canSplitAces"
bool Hand::GetCanSplitAces() const {
    return currentPlayer.canSplitAces;
}

// GetCanSplitHand - Retrieves the private data member "canSplitHand"
bool Hand::GetCanSplitHand() const {
    return currentPlayer.canSplitHand;
}

// GetChoseBuyInsurance - Retrieves the private data member "choseBuyInsurance"
bool Hand::GetChoseBuyInsurance() const {
    return currentPlayer.choseBuyInsurance;
}

// GetChoseDoubleDown - Retrieves the private data member "choseDoubleDown"
bool Hand::GetChoseDoubleDown() const {
    return currentPlayer.choseDoubleDown;
}

// GetChoseSplitAces - Retrieves the private data member "choseSplitAces"
bool Hand::GetChoseSplitAces() const {
    return currentPlayer.choseSplitAces;
}

// GetChoseSplitHand - Retrieves the private data member "choseSplitHand"
bool Hand::GetChoseSplitHand() const {
    return currentPlayer.choseSplitHand;
}

// GetHasHit - Retrieves the private data member "hasHit"
bool Hand::GetHasHit() const {
    return currentPlayer.hasHit;
}

// GetBankTotal - Retrieves the private data member "bankTotal"
float Hand::GetBankTotal() const {
    return currentPlayer.bankTotal;
}

// GetInsuranceWager - Retrieves the private data member "insuranceWager"
float Hand::GetInsuranceWager() const {
    return currentPlayer.insuranceWager;
}

// GetNet - Retrieves the private data member "net"
float Hand::GetNet() const {
    return currentPlayer.net;
}

// GetWager - Retrieves the private data member "wager"
float Hand::GetWager() const {
    return currentPlayer.wager;
}

// GetCardsTotal - Retrieves the private data member "cardsTotal"
int Hand::GetCardsTotal() const {
    return currentPlayer.cardsTotal;
}

// GetHandsPlayed - Retrieves the private data member "handsPlayed"
int Hand::GetHandsPlayed() const {
    return currentPlayer.handsPlayed;
}

// GetIndividualHands - Retrieves the private data member "individual_hands"
int Hand::GetIndividualHands() const {
    return currentPlayer.individual_hands;
}

// GetDisplayBankTotal - Retrieves the private data member "displayBankTotal"
std::string Hand::GetDisplayBankTotal() const {
    return currentPlayer.displayBankTotal;
}

// GetDisplayCardsTotal - Retrieves the private data member "displayCardsTotal"
std::string Hand::GetDisplayCardsTotal() const {
    return currentPlayer.displayCardsTotal;
}

// GetDisplayHandsplayed - Retrieves the private data member "displayHandsPlayed"
std::string Hand::GetDisplayHandsplayed() const {
    return currentPlayer.displayHandsPlayed;
}

// GetDisplayInsuranceWager - Retrieves the private data member "displayInsuranceWager"
std::string Hand::GetDisplayInsuranceWager() const {
    return currentPlayer.displayInsuranceWager;
}

// GetDisplayName - Retrieves the private data member "displayName"
std::string Hand::GetDisplayName() const {
    return currentPlayer.displayName;
}

// GetDisplayNet - Retrieves the private data member "displayNet"
std::string Hand::GetDisplayNet() const {
    return currentPlayer.displayNet;
}

// GetDisplayWager - Retrieves the private data member "displayWager"
std::string Hand::GetDisplayWager() const {
    return currentPlayer.displayWager;
}

// GetName - Retrieves the private data member "name"
std::string Hand::GetName() const {
    return currentPlayer.name;
}

// GetCards - Retrieves the private data member "cards"
std::vector<Card> Hand::GetCards() const {
    return currentPlayer.cards;
}

// GetHandBankTotals - Retrieves the private data member "handBankTotals"
std::vector<float> Hand::GetHandBankTotals() const {
    return currentPlayer.handBankTotals;
}

// GetHandCardTotals - Retrieves the private data member "handCardTotals"
std::vector<int> Hand::GetHandCardTotals() const {
    return currentPlayer.handCardTotals;
}

// GetHandNets - Retrieves the private data member "handNets"
std::vector<float> Hand::GetHandNets() const {
    return currentPlayer.handNets;
}

// GetHandPlayed - Retrieves the private data member "handPlayed"
std::vector<int> Hand::GetHandPlayed() const {
    return currentPlayer.handPlayed;
}

// GetHandWagers - Retrieves the private data member "handWagers"
std::vector<float> Hand::GetHandWagers() const {
    return currentPlayer.handWagers;
}