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
    SetChoseBuyInsurance(false);
    SetChoseDoubleDown(false);
    SetChoseSplitAces(false);
    SetChoseSplitHand(false);
    SetDoubleDownResponse(false);
    SetHasBlackJack(false);
    SetHasHit(false);
    SetParamInHand(false);
    SetSameParamInHand(false);
    SetSoftSeventeen(false);
    SetSplitAcesResponse(false);
    SetSplitHandResponse(false);
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
    GetDisplayHandsPlayed().clear();
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
*       * Create two integer values; ace_count (Represents the number of aces in a hand), running_hand_value (A running hand value)
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
    for (Card& current_card : currentPlayer.cards) {
        if (current_card.CheckCardParam(current_card.GetRank(), Ranks[0])) {
            ace_count += 1;
        }
        else {}
    }
    // Change Ace values
    for (Card& current_card : currentPlayer.cards) {
        if (ace_count == 1) {
            // Change Ace value to 11
            if (current_card.CheckCardParam(current_card.GetRank(), Ranks[0])) {
                current_card.SetNewCardValue(11);
            }
            else {}
        }
        else if (ace_count > 1) {
            // Change Ace value to 1
            if (current_card.CheckCardParam(current_card.GetRank(), Ranks[0])) {
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
        for (Card& current_card : currentPlayer.cards) {
            // If the card is an Ace, change the value of it to 1
            if (current_card.CheckCardParam(current_card.GetRank(), Ranks[0])) {
                current_card.SetNewCardValue(1);
                running_hand_value += current_card.GetCardValue();
            }
            // If the card is not an Ace, just add value to running_hand_value
            else if (!(current_card.CheckCardParam(current_card.GetRank(),Ranks[0]))) {
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
    float input;
    while (true) {
        // Prompt user for deposit
        std::cout << std::endl << "Please enter the amount you'd like to deposit into your bank: "; time_sleep(1000);
        std::cin >> input; time_sleep(1000);
        const std::type_info& result = typeid(input);
        std::string checkResult = result.name();
        // Check if value is not a float or integer
        if (checkResult != "f" && checkResult != "i") {
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

/*  CheckBlackJack - Checks to see if a player has blackjack
*   Input:
*       This function does not have any input parameters
*   Algorithm:
*       * Check to see if the player has an Ace in their hand first
*       * Begin by iterating through a hands cards
*       * First, check to see if the current card value in the hand has a value of 10
*           * If it does, proceed to return true if an Ace is also present and the hands size is only two
*           * Otherwise, continue through the hand
*       * Otherwise, proceed to check the next card in hand
*   Output:
*       This function returns a boolean value that determines if a player has a blackjack on deal
*/
Hand Hand::CheckBlackJack() {
    SetHasBlackJack(false);
    CheckParamInHand("R",Ranks[0]);
    for (Card current_card : GetCards()) {
        if (current_card.GetCardValue() == 10) {
            if (GetParamInHand() && GetCards().size() == 2) {
                SetHasBlackJack(true);
                break;
            }
            else {continue;}
        }
        else {continue;}
    }
    return *this;
}

/*  CheckParamInHand - Checks to see if there is a specific parameter found in a players hand
*   Input:
*       referenceParameter - Constant string value that represents the type of parameter we are looking for
*           "R" - This parameter represents rank
*           "S" - This parameter represents suit
*       checkingParameter - Constant string value that represents the parameter that we are searching for in a players hand
*   Algorithm:
*       * Start iterating through the cards of the player
*       * If the reference parameter that we are looking for is a rank
*           * We check to see if the current card matches the rank we are looking for by calling "CheckCardParam"
*           * Otherwise, we move on to the next card in the players hand
*       * If the reference parameter that we are looking for is a suit
*           * We check to see if the current card matches the suit we are looking for by calling "CheckCardParam"
*           * Otherwise, we move on to the next card in the players hand
*   Output:
*       This function returns a Hand object after checking if a specific parameter is present in a players hand
*/
Hand Hand::CheckParamInHand(const std::string referenceParameter, const std::string checkingParameter) {
    SetParamInHand(false);
    for (Card current_card : GetCards()) {
        if (referenceParameter == "R") {
            if (current_card.CheckCardParam(current_card.GetRank(), checkingParameter)) {
                SetParamInHand(true);
                break;
            }
            else {continue;}
        }
        else if (referenceParameter == "S") {
            if (current_card.CheckCardParam(current_card.GetSuit(), checkingParameter)) {
                SetParamInHand(true);
                break;
            }
            else {continue;}
        }
        else {}
    }
    return *this;
}

/*  CheckSameParamInHand - Checks to see if the same parameter is present in a players hand
*   Input:
*       referenceParameter - Constant string value that represents the type of parameter we are looking for
*           "R" - This parameter represents rank
*           "S" - This parameter represents suit
*       checkingParameter - Constant string value that represents the parameter that we are searching for in a players hand
*   Algorithm:
*       * Begin by iterating through the players hand, one card from the beginning of their hand
*       * Set the current card to the index of the vector
*       * If the "referenceParameter" is a Rank
*           * Return false if the current cards rank does not match the first cards rank or if the specific rank that is designated with "checkingParameter"
*             does not match that of the current card
*           * Otherwise, continue to the next card in the players hand
*       * If the "referenceParameter" is a Suit
*           * Return false if the current cards rank does not match the first cards suit or if the specific suit that is designated with "checkingParameter"
*             does not match that of the current card
*           * Otherwise, continue to the next card in the players hand
*       * Otherwise, if all the previous tests pass, then return true
*   Output:
*       This function returns a Hand object after checking if a specific parameter is the same in a players hand
*/
Hand Hand::CheckSameParamInHand(const std::string referenceParameter, const std::string checkingParameter) {
    SetSameParamInHand(true);
    for (int i = 1; i < GetCards().size(); ++i) {
        Card currentCard = GetCards().at(i);
        if (referenceParameter == "R") {
            if (!currentCard.CheckCardParam(currentCard.GetRank(), GetCards().at(0).GetRank()) || (!checkingParameter.empty() && !currentCard.CheckCardParam(currentCard.GetRank(), checkingParameter))) {
                SetSameParamInHand(false);
                break;
            }
            else {continue;}
        }
        else if (referenceParameter == "S") {
            if (!currentCard.CheckCardParam(currentCard.GetSuit(), GetCards().at(0).GetSuit()) || (!checkingParameter.empty() && !currentCard.CheckCardParam(currentCard.GetSuit(), checkingParameter))) {
                SetSameParamInHand(false);
                break;
            }
            else {continue;}
        }
        else {}
    }
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

/*  InsurancePrompt - Prompts a player if they would like to buy insurance
*   Input:
*       This function does not have any input parameters
*   Algorithm:
*       * Create a string and prompt the user if they would like to buy insurance
*       * Check to see if the input is yes or no
*           * If the input is yes, set the private data member "choseBuyInsurance" to true with "SetChoseBuyInsurance"
*           * If the input is no, set the private data member "choseBuyInsurance" to false with "SetChoseBuyInsurance"
*       * If the answer is not yes or no
*           * Through an output message
*           * Clear the inputs and go back to the beginning of the loop
*   Output:
*       This function returns a Hand object after prompting the user about buying insurance
*/
Hand Hand::InsurancePrompt() {
    std::string input;
    while (true) {
        // Prompt user for insurance
        std::cout << std::endl << "Would you like to buy insurance? Insurance pays (2:1). (y/n): "; time_sleep(1000);
        std::cin >> input; time_sleep(1000);
        // User has chosen to buy insurance, set insurance wager
        if (input == "y") {
            SetChoseBuyInsurance(true);
            SetInsuranceWager(round_input(0.5*GetWager()));
            UpdateBank(0,GetInsuranceWager());
            return *this;
        }
        // User has chosen to not buy insurance, do not take insurance wager
        else if (input == "n") {
            SetChoseBuyInsurance(false);
            return *this;
        }
        // Player did not enter a valid input for a response
        else {
            std::cout << std::endl << color_text(31, "Invalid Response") << ". Please re-enter your insurance decision." << std::endl;
            input.clear();
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
    }
}

/*  NamePrompt - Prompts a user to input a name for their player
*   Input:
*       This function does not have any input parameters
*   Algorithm:
*       * Create a string value "input" and prompt the user for what they want their name to be
*       * Call the "SetName" function to set the private data member "name" to "input"
*   Output:
*       This function returns a Hand object after prompting the user about what their name will be
*/
Hand Hand::NamePrompt() {
    std::string input;
    // Prompt user for their name
    std::cout << std::endl << "Please enter a name for your player: "; time_sleep(1000);
    std::getline(std::cin, input); time_sleep(1000);
    // Set the players name to "input"
    SetName(input);
    return *this;
}

/*  ParametersCheck - Checks to see if certain parameters in regards to wagering are met
*   Input:
*       checkingHand - Hand object passed by reference that represents the hand that is being examine
*       dealerHand - Hand object passed by reference that represents the dealer's hand
*   Algorithm:
*       * This algorithm checks for specific parameters that pertain to how the player can play their hand
*       * The parameters that are checked are the following:
*           * Blackjack Check - Checks to see if the players have blackjack or not
*           * Insurance Check - Checks to see if the player is able to buy insurance for their hand
*           * Double Down Check - Checks to see if the player is able to double down for their hand
*   Output:
*       This function returns a Hand object after checking the parameters in the current hand
*/
Hand Hand::ParametersCheck(Hand& checkingHand, Hand& dealerHand) {
    // Player Checks
    checkingHand.CheckSameParamInHand("R", "");
    checkingHand.CheckBlackJack();
    // Dealer Checks
    dealerHand.CheckBlackJack();
    // Can Split Hand Check
    if (checkingHand.GetSameParamInHand()) {
        // Player has enough money to split
        if (checkingHand.GetBankTotal() >= checkingHand.GetWager()) {
            // Checking if player has aces
            bool aces = checkingHand.GetCards().at(0).CheckCardParam(checkingHand.GetCards().at(0).GetRank(), Ranks[0]);
            // Player doesn't have Aces, can still split hand
            if (!aces) {
                checkingHand.SetCanSplitAces(false);
                checkingHand.SetCanSplitHand(true);
            }
            // Player has Aces, can split Aces, can't split regular hand
            else {
                checkingHand.SetCanSplitAces(true);
                checkingHand.SetCanSplitHand(false);
            }
        }
        // Player does not have enough money to split, can't split Aces or hand
        else {
            checkingHand.SetCanSplitAces(false);
            checkingHand.SetCanSplitHand(false);
        }
    }
    else {
        checkingHand.SetCanSplitAces(false);
        checkingHand.SetCanSplitHand(false);
    }
    // Insurance Check
    if (dealerHand.GetCards().at(1).CheckCardParam(dealerHand.GetCards().at(1).GetRank(), Ranks[0])) {
        // Player has enough money to buy insurance
        if (checkingHand.GetBankTotal() >= 0.5*checkingHand.GetWager()) {
            checkingHand.SetCanBuyInsurance(true);
        }
        // Player does not have enough money to buy insurance
        else {
            checkingHand.SetCanBuyInsurance(false);
        }
    }
    else {
        checkingHand.SetCanBuyInsurance(false);
    }
    // Can Double Down Check
    if (checkingHand.GetBankTotal() >= checkingHand.GetWager()) {
        if (!checkingHand.GetHasHit()) {
            checkingHand.SetCanDoubleDown(true);
        }
        else {
            checkingHand.SetCanDoubleDown(false);
        }
    }
    else {
        checkingHand.SetCanDoubleDown(false);
    }
    // Soft Seventeen Check
    if (checkingHand.GetCardsTotal() == 17) {
        checkingHand.CheckParamInHand("R", Ranks[0]);
        for (Card& current_card : checkingHand.GetCards()) {
            if (checkingHand.GetParamInHand() && current_card.GetCardValue() == 11) {
                checkingHand.SetSoftSeventeen(true);
                break;
            }
            else if (!checkingHand.GetParamInHand() || current_card.GetCardValue() == 1) {
                checkingHand.SetSoftSeventeen(false);
                continue;
            }
            else {}
        }
    }
    else {
        checkingHand.SetSoftSeventeen(false);
    }
    return *this;
}

/*  PlaceWager - Prompts the user to input a wager for their hand
*   Input:
*       This function does not have any input parameters
*   Algorithm:
*       * Create a float value "input" and prompt the user for their wager they would like to place
*       * Check to see if the input is valid
*       * If the input is not a float or an integer
*           * Throw an error, return to the beginning of the while loop while clearing inputs
*       * If the input is a float or an integer
*           * Check to see if the value entered is greater than zero
*               * If it is not, throw an error, return to the beginning of the while loop clearing inputs
*               * If it is, check to see if the input is greater than the bank total
*                   * If it is, then throw an error, return to the beginning of the while loop clearing inputs
*                   * If it is not, set the private data member "wager" to "input" with "SetWager"
*   Output:
*       This function returns a Hand object after setting the wager of a players hand
*/
Hand Hand::PlaceWager() {
    float input;
    while (true) {
        // Prompt user for the wager that they would like place for their hand
        std::cout << std::endl << "Please enter a wager for this hand. Current bank total: " << GetDisplayBankTotal() << ": "; time_sleep(1000);
        std::cin >> input; time_sleep(1000);
        const std::type_info& result = typeid(input);
        std::string checkResult = result.name();
        // Check if the input is not a float or integer
        if (checkResult != "f" && checkResult != "i") {
            std::cout << std::endl << color_text(31, "Invalid Response") << ". Please re-enter your submission." << std::endl; time_sleep(1000);
            clear_terminal();
            checkResult.clear();
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        // Check if a the input is a float or an integer
        else if (checkResult == "f" || checkResult == "i") {
            // User has entered a value that is less than zero, return to beginning of while loop
            if (input <= 0) {
                std::cout << std::endl << color_text(31, "Invalid Response") << " of " << color_text(31, std::to_string(round_input(input))) << ". Please re-enter a positive value." << std::endl; time_sleep(1000);
                clear_terminal();
                checkResult.clear();
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                continue;
            }
            // User has entered a value that is greater than zero
            else if (input > 0) {
                // User has entered a wager that is greater than their bank, return to beginning of while loop
                if (input > GetBankTotal()) {
                    std::cout << std::endl << color_text(31, "Invalid Response") << " of " << color_text(31, std::to_string(round_input(input))) << ". You must enter a wager that is less than or equal to your bank total "
                    << GetDisplayBankTotal() << ". Please re-enter your submission." << std::endl; time_sleep(1000);
                    clear_terminal();
                    checkResult.clear();
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    continue;
                }
                // User has entered a valid input for a wager, set the private data member "wager" to "input"
                else if (input <= GetBankTotal()) {
                    SetWager(input);
                    UpdateBank(0,GetWager());
                    std::cout << std::endl << GetDisplayName() << " has wagered: " << GetDisplayWager() << " with a current bank total " << GetDisplayBankTotal() << "." << std::endl; time_sleep(1000);
                    return *this;
                }
                else {}
            }
            else {}
        }
        else {}
    }
}

/*  ResetHand - Resets some private data members of a player
*   Input:
*       This function does not have any input parameters
*   Algorithm:
*       * Resets all boolean values to false
*       * Resets all float values to 0.00
*       * Resets all integer values to 0
*       * Clears all string values
*       * Clears all vector values
*   Output:
*       This function returns a Hand object after resetting select private data members
*/
Hand Hand::ResetHand() {
    // Boolean Values
    SetCanBuyInsurance(false);
    SetCanDoubleDown(false);
    SetCanSplitAces(false);
    SetCanSplitHand(false);
    SetChoseBuyInsurance(false);
    SetChoseDoubleDown(false);
    SetChoseSplitAces(false);
    SetChoseSplitHand(false);
    SetDoubleDownResponse(false);
    SetHasBlackJack(false);
    SetHasHit(false);
    SetParamInHand(false);
    SetSameParamInHand(false);
    SetSoftSeventeen(false);
    SetSplitAcesResponse(false);
    SetSplitHandResponse(false);
    // Float Values
    SetInsuranceWager(0.00);
    SetNet(0.00);
    SetWager(0.00);
    // Integer Values
    SetCardsTotal(0);
    SetIndividualHands(0);
    // String Values
    GetDisplayCardsTotal().clear();
    GetDisplayInsuranceWager().clear();
    GetDisplayNet().clear();
    GetDisplayWager().clear();
    // Vector Values
    GetCards().clear();
    return *this;
}

/*  ShowHand - This function displays the cards that are present in a players hand
*   Input:
*       option - String value that represents a custom hand tracker (e.g. First, Second, etc.)
*       dealerShow - Constant string value that determines if the dealer is to show both hands
*   Algorithm:
*       * Begin by checking to see if the "option" string is empty
*           * If it is, set it to current
*       * Create string objects that represent certain trackers for the output
*       * Check to see if the player is not the dealer
*           * If it is, create some more string objects to represent parameters
*           * Iterate through the cards in the players hand
*           * Add the hand total and display the other hand parameters
*       * If the player is the dealer
*           * If the dealer is hiding a card, output a special message to console
*           * If the dealer is showing both cards, do the same as a non dealer player
*   Output:
*       This function returns a Hand object after displaying what cards they have
*/
Hand Hand::ShowHand(std::string option, const std::string dealerShow) {
    // Test to see if the option value is empty
    if (option.empty()) {
        option = "current";
    }
    else {}
    // Modify the string values
    std::string optionMod = color_text(34, option);
    std::string handTotalMod = color_text(36, "Hand Total");
    // The player is not the dealer
    if (GetName() != "Dealer") {
        // Modify more string values
        std::string handWager = color_text(32, "Hand Wager");
        std::string bankTotal = color_text(33, "Bank Total");
        std::cout << GetDisplayName() << "'s " << optionMod << " hand: [";
        // Iterate through the cards in players hand
        for (int i = 0; i < GetCards().size(); i++) {
            if (i == GetCards().size() - 1) {
                std::cout << GetCards().at(i) << "] ";
            }
            else {
                std::cout << GetCards().at(i) << " , ";
            }
        }
        // Add hand total and display players hand parameters
        AddHandTotal();
        std::cout << handTotalMod << ": " << GetDisplayCardsTotal() << " , " << handWager << ": " << GetDisplayWager() << " , " << bankTotal << ": " << GetDisplayBankTotal() << std::endl; time_sleep(1000);
    }
    // The player is the dealer
    else if (GetName() == "Dealer") {
        // Dealer is hiding a card
        if (dealerShow.empty()) {
            std::string backCardMod = color_text(36, std::to_string(GetCards().back().GetCardValue()));
            std::cout << GetDisplayName() << "'s " << optionMod << " hand : [Hidden, " << GetCards().back() << "] " << handTotalMod << ": " << backCardMod << std::endl; time_sleep(1000);
        }
        // Dealer is showing both cards
        else {
            if (dealerShow != "cards") {
                std::cout << GetDisplayName() << "'s " << optionMod << " hand: [";
            }
            // Specialized display of cards
            else {
                std::cout << "[";
            }
            // Iterate through the cards in players hand
            for (int i = 0; i < GetCards().size(); i++) {
                if (i == GetCards().size() - 1) {
                    std::cout << GetCards().at(i) << "] ";
                }
                else {
                    std::cout << GetCards().at(i) << " , ";
                }
            }
            // Add hand total and display players hand parameters
            AddHandTotal();
            std::cout << handTotalMod << ": " << GetDisplayCardsTotal() << std::endl; time_sleep(1000);
        }
    }
    else {}
    return *this;
}

/*  UpdateBank - Updates the bank of a player
*   Input:
*       choice - Constant integer that is supposed to represent the outcome of a hand
*       wager - Constant float passed by reference that is the wager being used to update the bank
*   Algorithm:
*       * Grab the prior bank value with "prior_bank"
*       * The following codes represent what the choices mean
*           * 0 - Player withdraws money from bank (placing wager)
*           * 1 - Player wins hand
*           * 2 - Player loses hand
*           * 3 - Player pushes hand
*           * 4 - Player wins blackjack
*           * 5 - Player wins insurance
*   Output:
*       This function returns a Hand object after updating the players bank
*/
Hand Hand::UpdateBank(const int choice, const float& wager) {
    float prior_bank = GetBankTotal();
    switch (choice) {
    // 0 - Player withdraws money from bank (places wager)
    case 0:
        SetBankTotal(prior_bank - wager);
        return *this;
    // 1 - Player wins hand
    case 1:
        SetBankTotal(GetBankTotal() + (2.0 * wager));
        SetNet(GetNet() + (GetBankTotal() - (prior_bank + wager)));
        return *this;
    // 2 - Player loses hand
    case 2:
        SetBankTotal(prior_bank);
        SetNet(GetNet() + (GetBankTotal() - (prior_bank + wager)));
        return *this;
    // 3 - Player pushes hand
    case 3:
        SetBankTotal(GetBankTotal() + wager);
        SetNet(GetNet() + (GetBankTotal() - (prior_bank + wager)));
        return *this;
    // 4 - Player wins blackjack
    case 4:
        SetBankTotal(GetBankTotal() + wager + (1.5 * wager));
        SetNet(GetNet() + (GetBankTotal() - (prior_bank + wager)));
        return *this;
    // 5 - Player wins insurance
    case 5:
        SetBankTotal(GetBankTotal() + (3 * wager));
        SetNet(GetNet() + (GetBankTotal() - (prior_bank + wager)));
        return *this;
    default:
        return *this;
        break;
    }
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

/*  SetChoseBuyInsurance - Sets the private data member "choseBuyInsurance" to the input parameter "input"
*   Input:
*       input - Constant boolean value that is assigned to the private data member "choseBuyInsurance"
*   Algorithm:
*       * Set the private data member "choseBuyInsurance" to the input parameter "input"
*   Output:
*       This function does not return a value
*/
void Hand::SetChoseBuyInsurance(const bool input) {
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

/*  SetDoubleDownResponse - Sets the private data member "doubleDownResponse" to the input parameter "input"
*   Input:
*       input - Constant boolean value that is assigned to the private data member "doubleDownResponse"
*   Algorithm:
*       * Set the private data member "doubleDownResponse" to the input parameter "input"
*   Output:
*       This function does not return a value
*/
void Hand::SetDoubleDownResponse(const bool input) {
    currentPlayer.doubleDownResponse = input;
}

/*  SetHasBlackJack - Sets the private data member "hasBlackJack" to the input parameter "input"
*   Input:
*       input - Constant boolean value that is assigned to the private data member "hasBlackJack"
*   Algorithm:
*       * Set the private data member "hasBlackJack" to the input parameter "input"
*   Output:
*       This function does not return a value
*/
void Hand::SetHasBlackJack(const bool input) {
    currentPlayer.hasBlackJack = input;
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

/*  SetParamInHand - Sets the private data member "paramInHand" to the input parameter "input"
*   Input:
*       input - Constant boolean value that is assigned to the private data member "paramInHand"
*   Algorithm:
*       * Set the private data member "paramInHand" to the input parameter "input"
*   Output:
*       This function does not return a value
*/
void Hand::SetParamInHand(const bool input) {
    currentPlayer.paramInHand = input;
}

/*  SetSameParamInHand - Sets the private data member "sameParamInHand" to the input parameter "input"
*   Input:
*       input - Constant boolean value that is assigned to the private data member "sameParamInHand"
*   Algorithm:
*       * Set the private data member "sameParamInHand" to the input parameter "input"
*   Output:
*       This function does not return a value
*/
void Hand::SetSameParamInHand(const bool input) {
    currentPlayer.sameParamInHand = input;
}

/*  SetSoftSeventeen - Sets the private data member "softSeventeen" to the input parameter "input"
*   Input:
*       input - Constant boolean value that is assigned to the private data member "softSeventeen"
*   Algorithm:
*       * Set the private data member "softSeventeen" to the input parameter "input"
*   Output:
*       This function does not return a value
*/
void Hand::SetSoftSeventeen(const bool input) {
    currentPlayer.softSeventeen = input;
}

/*  SetSplitAcesResponse - Sets the private data member "splitAcesResponse" to the input parameter "input"
*   Input:
*       input - Constant boolean value that is assigned to the private data member "splitAcesResponse"
*   Algorithm:
*       * Set the private data member "splitAcesResponse" to the input parameter "input"
*   Output:
*       This function does not return a value
*/
void Hand::SetSplitAcesResponse(const bool input) {
    currentPlayer.splitAcesResponse = input;
}

/*  SetSplitHandResponse - Sets the private data member "splitHandResponse" to the input parameter "input"
*   Input:
*       input - Constant boolean value that is assigned to the private data member "splitHandResponse"
*   Algorithm:
*       * Set the private data member "splitHandResponse" to the input parameter "input"
*   Output:
*       This function does not return a value
*/
void Hand::SetSplitHandResponse(const bool input) {
    currentPlayer.splitHandResponse = input;
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

// GetDoubleDownResponse - Retrieves the private data member "doubleDownResponse"
bool Hand::GetDoubleDownResponse() const {
    return currentPlayer.doubleDownResponse;
}

// GetHasBlackJack - Retrieves the private data member "hasBlackJack"
bool Hand::GetHasBlackJack() const {
    return currentPlayer.hasBlackJack;
}

// GetHasHit - Retrieves the private data member "hasHit"
bool Hand::GetHasHit() const {
    return currentPlayer.hasHit;
}

// GetParamInHand - Retrieves the private data member "paramInHand"
bool Hand::GetParamInHand() const {
    return currentPlayer.paramInHand;
}

// GetSameParamInHand - Retrieves the private data member "sameParamInHand"
bool Hand::GetSameParamInHand() const {
    return currentPlayer.sameParamInHand;
}

// GetSoftSeventeen - Retrieves the private data member "softSeventeen"
bool Hand::GetSoftSeventeen() const {
    return currentPlayer.softSeventeen;
}

// GetSplitAcesResponse - Retrieves the private data member "splitAcesResponse"
bool Hand::GetSplitAcesResponse() const {
    return currentPlayer.splitAcesResponse;
}

// GetSplitHandResponse - Retrieves the private data member "splitHandResponse"
bool Hand::GetSplitHandResponse() const {
    return currentPlayer.splitHandResponse;
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

// GetDisplayHandsPlayed - Retrieves the private data member "displayHandsPlayed"
std::string Hand::GetDisplayHandsPlayed() const {
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