// // ----- ----- ----- ----- ----- ----- ----- Includes ----- ----- ----- ----- ----- ----- ----- ----- ----- //
#include "../Headers/HandC.h"

// ----- ----- ----- ----- ----- ----- ----- Class Functions ----- ----- ----- ----- ----- ----- ----- ----- ----- //
/*  Constructor for Hand Class
*   Input:
*       There is no input required for constructing this class
*   Initialization:
*       Create necessary objects in construction
*       Boolean Values - All boolean values set to false
*       Float Values - All float values set to zero
*       Integer Values - All integer values set to zero
*       String Values - All string values set to empty
*       Vector Values - All vector values set to empty
*/
Hand::Hand() {
    // Object construction
    player = std::make_shared<Player>();
    player->handBankTotals = std::make_shared<LinkedList<float>>();
    player->handCardTotals = std::make_shared<LinkedList<int>>();
    player->handNets = std::make_shared<LinkedList<float>>();
    player->handPlayed = std::make_shared<LinkedList<int>>();
    player->handWagers = std::make_shared<LinkedList<float>>();
    player->playerCards = std::make_shared<LinkedList<Card>>();
    // Boolean Values Initialization
    this->SetCanBuyInsurance(false);
    this->SetCanDoubleDown(false);
    this->SetCanSplitAces(false);
    this->SetCanSplitHand(false);
    this->SetChoseBuyInsurance(false);
    this->SetShouldDoubleDown(false);
    this->SetChoseSplitAces(false);
    this->SetChoseSplitHand(false);
    this->SetDoubleDownResponse(false);
    this->SetHasBlackJack(false);
    this->SetHasHit(false);
    this->SetParamInHand(false);
    this->SetSameParamInHand(false);
    this->SetShouldDoubleDown(false);
    this->SetShouldHit(false);
    this->SetShouldSplit(false);
    this->SetShouldStand(false);
    this->SetSoftSeventeen(false);
    this->SetSplitAcesResponse(false);
    this->SetSplitHandResponse(false);
    // Float Values Initialization
    this->SetBankTotal(0);
    this->SetInsuranceWager(0);
    this->SetNet(0);
    this->SetWager(0);
    // Integer Values Initialization
    this->SetCardsTotal(0);
    this->SetHandsPlayed(0);
    // String Values Initialization
    this->GetDisplayBankTotal().clear();
    this->GetDisplayCardsTotal().clear();
    this->GetDisplayInsuranceWager().clear();
    this->GetDisplayName().clear();
    this->GetDisplayNet().clear();
    this->GetDisplayWager().clear();
    this->GetName().clear();
    // List Values Initialization
    this->GetHandBankTotals()->ClearList();
    this->GetHandCardTotals()->ClearList();
    this->GetHandNets()->ClearList();
    this->GetHandPlayed()->ClearList();
    this->GetHandWagers()->ClearList();
    this->GetPlayerCards()->ClearList();
}

// De-Constructor
Hand::~Hand() {}

/*  AddCardToHand - Adds a card to a players hand
*   Input:
*       input - Card node passed by reference that represents the card being inserted into a hand
*   Algorithm:
*       * Calls the "SetCards" function and adds the input parameter "input" to the private data member ""
*       * Call "AddHandTotal" function to add up the total in the hand of the player
*   Output:
*       This function returns a Hand object
*/
Hand Hand::AddCardToHand(std::shared_ptr<node<Card>>& input) {
    // Add card to players hand and update hand total
    this->SetPlayerCards(input);
    this->AddHandTotal();
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
    std::shared_ptr<node<Card>> currentCard = this->GetPlayerCards()->GetRoot();
    while (currentCard != nullptr) {
        if (currentCard->data.CheckCardParam(currentCard->data.GetRank(), Ranks[0])) {
            ace_count += 1;
        }
        currentCard = currentCard->nextNode;
    }
    currentCard = this->GetPlayerCards()->GetRoot();
    // Change Ace values
    while (currentCard != nullptr) {
        if (currentCard->data.CheckCardParam(currentCard->data.GetRank(), Ranks[0])) {
            // Change Ace value to 11
            if (ace_count == 1) {
                currentCard->data.SetNewCardValue(11);
            }
            // Change Ace value to 1
            else if (ace_count > 1) {
                currentCard->data.SetNewCardValue(1);
            }
        }
        ace_count -= 1;
        running_hand_value += currentCard->data.GetCardValue();
        currentCard = currentCard->nextNode;
    }
    currentCard = this->GetPlayerCards()->GetRoot();
    if (running_hand_value > 21) {
        running_hand_value = 0;
        while (currentCard != nullptr) {
            // If the card is an Ace, change the value of it to 1
            if (currentCard->data.CheckCardParam(currentCard->data.GetRank(), Ranks[0])) {
                currentCard->data.SetNewCardValue(1);
                running_hand_value += currentCard->data.GetCardValue();
            }
            // If the card is not an Ace, just add value to running_hand_value
            else {
                running_hand_value += currentCard->data.GetCardValue();
            }
            currentCard = currentCard->nextNode;
        }
    }
    currentCard = this->GetPlayerCards()->GetRoot();
    this->SetCardsTotal(running_hand_value);
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
                this->SetBankTotal(input);
                break;
            }
        }
    }
    std::cout << std::endl << this->GetDisplayName() << " has decided to start with: " << this->GetDisplayBankTotal() << std::endl; time_sleep(1000);
    // Update stats of player
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
    this->SetHasBlackJack(false);
    this->CheckParamInHand("R",Ranks[0]);
    // Iterate over cards
    std::shared_ptr<node<Card>> currentCard = this->GetPlayerCards()->GetRoot();
    while (currentCard != nullptr) {
        // Check if there is a card in hand that has a value of 10
        if (currentCard->data.GetCardValue() == 10) {
            // Check if there is an Ace in the hand and the hand only has 2 cards
            if (this->GetParamInHand() && this->GetPlayerCards()->GetSize() == 2) {
                this->SetHasBlackJack(true);
                break;
            }
        }
        currentCard = currentCard->nextNode;
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
    this->SetParamInHand(false);
    // Iterate over cards
    std::shared_ptr<node<Card>> currentCard = this->GetPlayerCards()->GetRoot();
    while (currentCard != nullptr) {
        // If the "referenceParameter" is a rank, check for a rank
        if (referenceParameter == "R") {
            if (currentCard->data.CheckCardParam(currentCard->data.GetRank(), checkingParameter)) {
                this->SetParamInHand(true);
                break;
            }
        }
        // If the "referenceParameter" is a suit, check for a suit
        else if (referenceParameter == "S") {
            if (currentCard->data.CheckCardParam(currentCard->data.GetSuit(), checkingParameter)) {
                this->SetParamInHand(true);
                break;
            }
        }
        currentCard = currentCard->nextNode;
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
    this->SetSameParamInHand(true);
    // Iterate over the cards in a players hand
    for (int i = 1; i < this->GetPlayerCards()->GetSize(); i++) {
        std::shared_ptr<node<Card>> currentCard = this->GetPlayerCards()->RetrieveNode(i);
        // If the "referenceParameter" is a rank, check for the same rank in a hand
        if (referenceParameter == "R") {
            if (!currentCard->data.CheckCardParam(currentCard->data.GetRank(), this->GetPlayerCards()->RetrieveNode(0)->data.GetRank()) || (!checkingParameter.empty() && !currentCard->data.CheckCardParam(currentCard->data.GetRank(), checkingParameter))) {
                this->SetSameParamInHand(false);
                break;
            }
        }
        // If the "referenceParameter" is a suit, check for the same suit in a hand
        if (referenceParameter == "S") {
            if (!currentCard->data.CheckCardParam(currentCard->data.GetSuit(), this->GetPlayerCards()->RetrieveNode(0)->data.GetSuit()) || (!checkingParameter.empty() && !currentCard->data.CheckCardParam(currentCard->data.GetSuit(), checkingParameter))) {
                this->SetSameParamInHand(false);
                break;
            }
        }
    }
    return *this;
}

// /*  CopyVariables - Copies select data members from one hand to the current hand
// *   Input:
// *       input - Hand object passed by reference that is used to copy data members from
// *   Algorithm:
// *       * Copy the name of "input" for the current hand with SetName
// *       * Copy the bank total of "input" for the current hand with SetBankTotal
// *       * Copy the wager of "input" for the current hand with SetWager
// *   Output:
// *       This function returns a Hand object after copying select variables
// */
// Hand Hand::CopyVariables(Hand& input) {
//     // Copy name, bank total, and wager to respective hand
//     SetName(input.GetName());
//     SetBankTotal(input.GetBankTotal());
//     SetWager(input.GetWager());
//     return *this;
// }

// /*  HitHand - Removes a hand from a given show and adds it a players hand
// *   Input:
// *       input - Shoe object that is passed by reference where a Card object is being pulled from
// *   Algorithm:
// *       * Call AddCardToHand() to add a card to the current players hand
// *   Output:
// *       This function returns a Hand object after adding a card to it
// */
// Hand Hand::HitHand(Shoe& input) {
//     // Add card to current hand
//     AddCardToHand(input.Draw());
//     return *this;
// }

// /*  InsurancePrompt - Prompts a player if they would like to buy insurance
// *   Input:
// *       This function does not have any input parameters
// *   Algorithm:
// *       * Create a string and prompt the user if they would like to buy insurance
// *       * Check to see if the input is yes or no
// *           * If the input is yes, set the private data member "choseBuyInsurance" to true with "SetChoseBuyInsurance"
// *           * If the input is no, set the private data member "choseBuyInsurance" to false with "SetChoseBuyInsurance"
// *       * If the answer is not yes or no
// *           * Through an output message
// *           * Clear the inputs and go back to the beginning of the loop
// *   Output:
// *       This function returns a Hand object after prompting the user about buying insurance
// */
// Hand Hand::InsurancePrompt() {
//     std::string input;
//     while (true) {
//         // Prompt user for insurance
//         std::cout << std::endl << "Would you like to buy insurance? Insurance pays (2:1). (y/n): "; time_sleep(1000);
//         std::cin >> input; time_sleep(1000);
//         // User has chosen to buy insurance, set insurance wager
//         if (input == "y") {
//             SetChoseBuyInsurance(true);
//             SetInsuranceWager(round_input(0.5*GetWager()));
//             UpdateBank(0,GetInsuranceWager());
//             return *this;
//         }
//         // User has chosen to not buy insurance, do not take insurance wager
//         else if (input == "n") {
//             SetChoseBuyInsurance(false);
//             return *this;
//         }
//         // Player did not enter a valid input for a response
//         else {
//             std::cout << std::endl << color_text(31, "Invalid Response") << ". Please re-enter your insurance decision." << std::endl;
//             input.clear();
//             std::cin.clear();
//             std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
//             continue;
//         }
//     }
// }

// /*  NamePrompt - Prompts a user to input a name for their player
// *   Input:
// *       This function does not have any input parameters
// *   Algorithm:
// *       * Create a string value "input" and prompt the user for what they want their name to be
// *       * Call the "SetName" function to set the private data member "name" to "input"
// *   Output:
// *       This function returns a Hand object after prompting the user about what their name will be
// */
// Hand Hand::NamePrompt() {
//     std::string input;
//     // Prompt user for their name
//     std::cout << std::endl << "Please enter a name for your player: "; time_sleep(1000);
//     std::getline(std::cin, input); time_sleep(1000);
//     // Set the players name to "input"
//     SetName(input);
//     return *this;
// }

// /*  ParametersCheck - Checks to see if certain parameters in regards to wagering are met
// *   Input:
// *       checkingHand - Hand object passed by reference that represents the hand that is being examine
// *       dealerHand - Hand object passed by reference that represents the dealer's hand
// *   Algorithm:
// *       * This algorithm checks for specific parameters that pertain to how the player can play their hand
// *       * The parameters that are checked are the following:
// *           * Blackjack Check - Checks to see if the players have blackjack or not
// *           * Insurance Check - Checks to see if the player is able to buy insurance for their hand
// *           * Double Down Check - Checks to see if the player is able to double down for their hand
// *           * Soft Seventeen Check - Checks to see if the player possesses a soft seventeen in their hand
// *   Output:
// *       This function returns a Hand object after checking the parameters in the current hand
// */
// Hand Hand::ParametersCheck(Hand& checkingHand, Hand& dealerHand) {
//     // Player Checks
//     checkingHand.CheckSameParamInHand("R", "");
//     checkingHand.CheckBlackJack();
//     // Dealer Checks
//     dealerHand.CheckBlackJack();
//     // Can Split Hand Check
//     if (checkingHand.GetSameParamInHand()) {
//         // Player has enough money to split
//         if (checkingHand.GetBankTotal() >= checkingHand.GetWager()) {
//             // Checking if player has aces
//             bool aces = checkingHand.GetCards().at(0).CheckCardParam(checkingHand.GetCards().at(0).GetRank(), Ranks[0]);
//             // Player doesn't have Aces, can still split hand
//             if (!aces) {
//                 checkingHand.SetCanSplitAces(false);
//                 checkingHand.SetCanSplitHand(true);
//             }
//             // Player has Aces, can split Aces, can't split regular hand
//             else {
//                 checkingHand.SetCanSplitAces(true);
//                 checkingHand.SetCanSplitHand(false);
//             }
//         }
//         // Player does not have enough money to split, can't split Aces or hand
//         else {
//             checkingHand.SetCanSplitAces(false);
//             checkingHand.SetCanSplitHand(false);
//         }
//     }
//     else {
//         checkingHand.SetCanSplitAces(false);
//         checkingHand.SetCanSplitHand(false);
//     }
//     // Insurance Check
//     if (dealerHand.GetCards().at(1).CheckCardParam(dealerHand.GetCards().at(1).GetRank(), Ranks[0])) {
//         // Player has enough money to buy insurance
//         if (checkingHand.GetBankTotal() >= 0.5*checkingHand.GetWager()) {
//             checkingHand.SetCanBuyInsurance(true);
//         }
//         // Player does not have enough money to buy insurance
//         else {
//             checkingHand.SetCanBuyInsurance(false);
//         }
//     }
//     else {
//         checkingHand.SetCanBuyInsurance(false);
//     }
//     // Can Double Down Check
//     if (checkingHand.GetBankTotal() >= checkingHand.GetWager() && !checkingHand.GetChoseDoubleDown()) {
//         if (!checkingHand.GetHasHit()) {
//             checkingHand.SetCanDoubleDown(true);
//         }
//         else {
//             checkingHand.SetCanDoubleDown(false);
//         }
//     }
//     else {
//         checkingHand.SetCanDoubleDown(false);
//     }
//     // Soft Seventeen Check
//     if (checkingHand.GetCardsTotal() == 17) {
//         checkingHand.CheckParamInHand("R", Ranks[0]);
//         for (Card& current_card : checkingHand.GetCards()) {
//             if (checkingHand.GetParamInHand() && current_card.GetCardValue() == 11) {
//                 checkingHand.SetSoftSeventeen(true);
//                 break;
//             }
//             else if (!checkingHand.GetParamInHand() || current_card.GetCardValue() == 1) {
//                 checkingHand.SetSoftSeventeen(false);
//                 continue;
//             }
//         }
//     }
//     else {
//         checkingHand.SetSoftSeventeen(false);
//     }
//     return *this;
// }

// /*  PlaceWager - Prompts the user to input a wager for their hand
// *   Input:
// *       This function does not have any input parameters
// *   Algorithm:
// *       * Create a float value "input" and prompt the user for their wager they would like to place
// *       * Check to see if the input is valid
// *       * If the input is not a float or an integer
// *           * Throw an error, return to the beginning of the while loop while clearing inputs
// *       * If the input is a float or an integer
// *           * Check to see if the value entered is greater than zero
// *               * If it is not, throw an error, return to the beginning of the while loop clearing inputs
// *               * If it is, check to see if the input is greater than the bank total
// *                   * If it is, then throw an error, return to the beginning of the while loop clearing inputs
// *                   * If it is not, set the private data member "wager" to "input" with "SetWager"
// *   Output:
// *       This function returns a Hand object after setting the wager of a players hand
// */
// Hand Hand::PlaceWager() {
//     float input;
//     while (true) {
//         // Prompt user for the wager that they would like place for their hand
//         std::cout << std::endl << "Please enter a wager for this hand. Current bank total: " << GetDisplayBankTotal() << ": "; time_sleep(1000);
//         std::cin >> input; time_sleep(1000);
//         const std::type_info& result = typeid(input);
//         std::string checkResult = result.name();
//         // Check if the input is not a float or integer
//         if (checkResult != "f" && checkResult != "i") {
//             std::cout << std::endl << color_text(31, "Invalid Response") << ". Please re-enter your submission." << std::endl; time_sleep(1000);
//             clear_terminal();
//             checkResult.clear();
//             std::cin.clear();
//             std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
//             continue;
//         }
//         // Check if a the input is a float or an integer
//         else if (checkResult == "f" || checkResult == "i") {
//             // User has entered a value that is less than zero, return to beginning of while loop
//             if (input <= 0) {
//                 std::cout << std::endl << color_text(31, "Invalid Response") << " of " << color_text(31, std::to_string(round_input(input))) << ". Please re-enter a positive value." << std::endl; time_sleep(1000);
//                 clear_terminal();
//                 checkResult.clear();
//                 std::cin.clear();
//                 std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
//                 continue;
//             }
//             // User has entered a value that is greater than zero
//             else {
//                 // User has entered a wager that is greater than their bank, return to beginning of while loop
//                 if (input > GetBankTotal()) {
//                     std::cout << std::endl << color_text(31, "Invalid Response") << " of " << color_text(31, std::to_string(round_input(input))) << ". You must enter a wager that is less than or equal to your bank total "
//                     << GetDisplayBankTotal() << ". Please re-enter your submission." << std::endl; time_sleep(1000);
//                     clear_terminal();
//                     checkResult.clear();
//                     std::cin.clear();
//                     std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
//                     continue;
//                 }
//                 // User has entered a valid input for a wager, set the private data member "wager" to "input"
//                 else {
//                     SetWager(input);
//                     UpdateBank(0,GetWager());
//                     std::cout << std::endl << GetDisplayName() << " has wagered: " << GetDisplayWager() << " with a current bank total " << GetDisplayBankTotal() << "." << std::endl; time_sleep(1000);
//                     return *this;
//                 }
//             }
//         }
//     }
// }

// /*  ResetHand - Resets some private data members of a player
// *   Input:
// *       This function does not have any input parameters
// *   Algorithm:
// *       * Resets all boolean values to false
// *       * Resets all float values to 0.00
// *       * Resets all integer values to 0
// *       * Clears all string values
// *       * Clears all vector values
// *   Output:
// *       This function returns a Hand object after resetting select private data members
// */
// Hand Hand::ResetHand() {
//     // Boolean Values
//     SetCanBuyInsurance(false);
//     SetCanDoubleDown(false);
//     SetCanSplitAces(false);
//     SetCanSplitHand(false);
//     SetChoseBuyInsurance(false);
//     SetChoseDoubleDown(false);
//     SetChoseSplitAces(false);
//     SetChoseSplitHand(false);
//     SetDoubleDownResponse(false);
//     SetHasBlackJack(false);
//     SetHasHit(false);
//     SetParamInHand(false);
//     SetSameParamInHand(false);
//     SetShouldDoubleDown(false);
//     SetShouldHit(false);
//     SetShouldSplit(false);
//     SetShouldStand(false);
//     SetSoftSeventeen(false);
//     SetSplitAcesResponse(false);
//     SetSplitHandResponse(false);
//     // Float Values
//     SetInsuranceWager(0.00);
//     SetNet(0.00);
//     SetWager(0.00);
//     // Integer Values
//     SetCardsTotal(0);
//     SetIndividualHands(0);
//     // String Values
//     GetDisplayCardsTotal().clear();
//     GetDisplayInsuranceWager().clear();
//     GetDisplayNet().clear();
//     GetDisplayWager().clear();
//     // Vector Values
//     GetCards().clear();
//     return *this;
// }

// /*  ShowHand - This function displays the cards that are present in a players hand
// *   Input:
// *       option - String value that represents a custom hand tracker (e.g. First, Second, etc.)
// *       dealerShow - Constant string value that determines if the dealer is to show both hands
// *   Algorithm:
// *       * Begin by checking to see if the "option" string is empty
// *           * If it is, set it to current
// *       * Create string objects that represent certain trackers for the output
// *       * Check to see if the player is not the dealer
// *           * If it is, create some more string objects to represent parameters
// *           * Iterate through the cards in the players hand
// *           * Add the hand total and display the other hand parameters
// *       * If the player is the dealer
// *           * If the dealer is hiding a card, output a special message to console
// *           * If the dealer is showing both cards, do the same as a non dealer player
// *   Output:
// *       This function returns a Hand object after displaying what cards they have
// */
// Hand Hand::ShowHand(std::string option, const std::string dealerShow) {
//     // Test to see if the option value is empty
//     if (option.empty()) {
//         option = "current";
//     }
//     // Modify the string values
//     std::string optionMod = color_text(34, option);
//     std::string handTotalMod = color_text(36, "Hand Total");
//     // The player is not the dealer
//     if (GetName() != "Dealer") {
//         // Modify more string values
//         std::string handWager = color_text(32, "Hand Wager");
//         std::string bankTotal = color_text(33, "Bank Total");
//         std::cout << GetDisplayName() << "'s " << optionMod << " hand: [";
//         // Iterate through the cards in players hand
//         for (int i = 0; i < GetCards().size(); i++) {
//             if (i == GetCards().size() - 1) {
//                 std::cout << GetCards().at(i) << "] ";
//             }
//             else {
//                 std::cout << GetCards().at(i) << " , ";
//             }
//         }
//         // Add hand total and display players hand parameters
//         AddHandTotal();
//         std::cout << handTotalMod << ": " << GetDisplayCardsTotal() << " , " << handWager << ": " << GetDisplayWager() << " , " << bankTotal << ": " << GetDisplayBankTotal() << std::endl; time_sleep(1000);
//     }
//     // The player is the dealer
//     else if (GetName() == "Dealer") {
//         // Dealer is hiding a card
//         if (dealerShow.empty()) {
//             std::string backCardMod = color_text(36, std::to_string(GetCards().back().GetCardValue()));
//             std::cout << GetDisplayName() << "'s " << optionMod << " hand : [Hidden, " << GetCards().back() << "] " << handTotalMod << ": " << backCardMod << std::endl; time_sleep(1000);
//         }
//         // Dealer is showing both cards
//         else {
//             if (dealerShow != "cards") {
//                 std::cout << GetDisplayName() << "'s " << optionMod << " hand: [";
//             }
//             // Specialized display of cards
//             else {
//                 std::cout << "[";
//             }
//             // Iterate through the cards in players hand
//             for (int i = 0; i < GetCards().size(); i++) {
//                 if (i == GetCards().size() - 1) {
//                     std::cout << GetCards().at(i) << "] ";
//                 }
//                 else {
//                     std::cout << GetCards().at(i) << " , ";
//                 }
//             }
//             // Add hand total and display players hand parameters
//             AddHandTotal();
//             std::cout << handTotalMod << ": " << GetDisplayCardsTotal() << std::endl; time_sleep(1000);
//         }
//     }
//     return *this;
// }

// /*  UpdateBank - Updates the bank of a player
// *   Input:
// *       choice - Constant integer that is supposed to represent the outcome of a hand
// *       wager - Constant float passed by reference that is the wager being used to update the bank
// *   Algorithm:
// *       * Grab the prior bank value with "prior_bank"
// *       * The following codes represent what the choices mean
// *           * 0 - Player withdraws money from bank (placing wager)
// *           * 1 - Player wins hand
// *           * 2 - Player loses hand
// *           * 3 - Player pushes hand
// *           * 4 - Player wins blackjack
// *           * 5 - Player wins insurance
// *   Output:
// *       This function returns a Hand object after updating the players bank
// */
// Hand Hand::UpdateBank(const int choice, const float& wager) {
//     float prior_bank = GetBankTotal();
//     switch (choice) {
//     // 0 - Player withdraws money from bank (places wager)
//     case 0:
//         SetBankTotal(prior_bank - wager);
//         return *this;
//     // 1 - Player wins hand
//     case 1:
//         SetBankTotal(GetBankTotal() + (2.0 * wager));
//         SetNet(GetNet() + (GetBankTotal() - (prior_bank + wager)));
//         return *this;
//     // 2 - Player loses hand
//     case 2:
//         SetBankTotal(prior_bank);
//         SetNet(GetNet() + (GetBankTotal() - (prior_bank + wager)));
//         return *this;
//     // 3 - Player pushes hand
//     case 3:
//         SetBankTotal(GetBankTotal() + wager);
//         SetNet(GetNet() + (GetBankTotal() - (prior_bank + wager)));
//         return *this;
//     // 4 - Player wins blackjack
//     case 4:
//         SetBankTotal(GetBankTotal() + wager + (1.5 * wager));
//         SetNet(GetNet() + (GetBankTotal() - (prior_bank + wager)));
//         return *this;
//     // 5 - Player wins insurance
//     case 5:
//         SetBankTotal(GetBankTotal() + (3 * wager));
//         SetNet(GetNet() + (GetBankTotal() - (prior_bank + wager)));
//         return *this;
//     default:
//         return *this;
//         break;
//     }
// }

// ----- ----- ----- ----- ----- ----- ----- Setter Functions ----- ----- ----- ----- ----- ----- ----- ----- ----- //
// SetCanBuyInsurance - Mutates the private data member "canBuyInsurance" by assigning it to "input"
void Hand::SetCanBuyInsurance(const bool input) {
    player->canBuyInsurance = input;
}

// SetCanDoubleDown - Mutates the private data member "canDoubleDown" by assigning it to "input"
void Hand::SetCanDoubleDown(const bool input) {
    player->canDoubleDown = input;
}

// SetCanSplitAces - Mutates the private data member "canSplitAces" by assigning it to "input"
void Hand::SetCanSplitAces(const bool input) {
    player->canSplitAces = input;
}

// SetCanSplitHand - Mutates the private data member "canSplitHand" by assigning it to "input"
void Hand::SetCanSplitHand(const bool input) {
    player->canSplitHand = input;
}

// SetChoseBuyInsurance - Mutates the private data member "choseBuyInsurance" by assigning it to "input"
void Hand::SetChoseBuyInsurance(const bool input) {
    player->choseBuyInsurance = input;
}

// SetChoseDoubleDown - Mutates the private data member "choseDoubleDown" by assigning it to "input"
void Hand::SetChoseDoubleDown(const bool input) {
    player->choseDoubleDown = input;
}

// SetChoseSplitAces - Mutates the private data member "choseSplitAces" by assigning it to "input"
void Hand::SetChoseSplitAces(const bool input) {
    player->choseSplitAces = input;
}

// SetChoseSplitHand - Mutates the private data member "choseSplitHand" by assigning it to "input"
void Hand::SetChoseSplitHand(const bool input) {
    player->choseSplitHand = input;
}

// SetDoubleDownResponse - Mutates the private data member "doubleDownResponse" by assigning it to "input"
void Hand::SetDoubleDownResponse(const bool input) {
    player->doubleDownResponse = input;
}

// SetHasBlackJack - Mutates the private data member "hasBlackJack" by assigning it to "input"
void Hand::SetHasBlackJack(const bool input) {
    player->hasBlackJack = input;
}

// SetHasHit - Mutates the private data member "hasHit" by assigning it to "input"
void Hand::SetHasHit(const bool input) {
    player->hasHit = input;
}

// SetParamInHand - Mutates the private data member "paramInHand" by assigning it to "input"
void Hand::SetParamInHand(const bool input) {
    player->paramInHand = input;
}

// SetSameParamInHand - Mutates the private data member "sameParamInHand" by assigning it to "input"
void Hand::SetSameParamInHand(const bool input) {
    player->sameParamInHand = input;
}

// SetShouldDoubleDown - Mutates the private data member "shouldDoubleDown" by assigning it to "input"
void Hand::SetShouldDoubleDown(const bool input) {
    player->shouldDoubleDown = input;
}

// SetShouldHit - Mutates the private data member "shouldHit" by assigning it to "input"
void Hand::SetShouldHit(const bool input) {
    player->shouldHit = input;
}

// SetShouldSplit - Mutates the private data member "shouldSplit" by assigning it to "input"
void Hand::SetShouldSplit(const bool input) {
    player->shouldSplit = input;
}

// SetShouldStand - Mutates the private data member "shouldStand" by assigning it to "input"
void Hand::SetShouldStand(const bool input) {
    player->shouldStand = input;
}

// SetSoftSeventeen - Mutates the private data member "softSeventeen" by assigning it to "input"
void Hand::SetSoftSeventeen(const bool input) {
    player->softSeventeen = input;
}

// SetSplitAcesResponse - Mutates the private data member "splitAcesResponse" by assigning it to "input"
void Hand::SetSplitAcesResponse(const bool input) {
    player->splitAcesResponse = input;
}

// SetSplitHandResponse - Mutates the private data member "splitHandResponse" by assigning it to "input"
void Hand::SetSplitHandResponse(const bool input) {
    player->splitHandResponse = input;
}

// SetBankTotal - Mutates the private data member "bankTotal" by assigning it to "input"
void Hand::SetBankTotal(const float& input) {
    float rounded_input = round_input(input);
    player->bankTotal = rounded_input;
    this->SetDisplayBankTotal();
}

// SetInsuranceWager - Mutates the private data member "insuranceWager" by assigning it to "input"
void Hand::SetInsuranceWager(const float& input) {
    float rounded_input = round_input(input);
    player->insuranceWager = rounded_input;
    this->SetDisplayInsuranceWager();
}

// SetNet - Mutates the private data member "net" by assigning it to "input"
void Hand::SetNet(const float& input) {
    float rounded_input = round_input(input);
    player->net = rounded_input;
    this->SetDisplayNet();
}

// SetWager - Mutates the private data member "wager" by assigning it to "input"
void Hand::SetWager(const float& input) {
    float rounded_input = round_input(input);
    player->wager = rounded_input;
    this->SetDisplayWager();
}

// SetCardsTotal - Mutates the private data member "cardsTotal" by assigning it to "input"
void Hand::SetCardsTotal(const int& input) {
    player->cardsTotal = input;
}

// SetHandsPlayed - Mutates the private data member "handsPlayed" by assigning it to "input"
void Hand::SetHandsPlayed(const int& input) {
    player->handsPlayed = input;
}

// SetDisplayBankTotal - Mutates the private data member "displayBankTotal" by assigning it to "input"
void Hand::SetDisplayBankTotal() {
    std::string modified_input = color_text(33, round_to_string(GetBankTotal()));
    player->displayBankTotal = modified_input;
}

// SetDisplayCardsTotal - Mutates the private data member "displayCardsTotal" by assigning it to "input"
void Hand::SetDisplayCardsTotal() {
    std::string modified_input = color_text(35, std::to_string(GetCardsTotal()));
    player->displayCardsTotal = modified_input;
}

// SetDisplayInsuranceWager - Mutates the private data member "displayInsuranceWager" by assigning it to "input"
void Hand::SetDisplayInsuranceWager() {
    std::string modified_input = color_text(31, round_to_string(GetInsuranceWager()));
    player->displayInsuranceWager = modified_input;
}

// SetDisplayName - Mutates the private data member "displayName" by assigning it to "input"
void Hand::SetDisplayName() {
    std::string modified_input;
    if (GetName() != "Dealer") {
        modified_input = color_text(34, GetName());
    }
    else {
        modified_input = color_text(31, GetName());
    }
    player->displayName = modified_input;
}

// SetDisplayNet - Mutates the private data member "displayNet" by assigning it to "input"
void Hand::SetDisplayNet() {
    std::string modified_input = color_text(33, round_to_string(GetNet()));
    player->displayNet = modified_input;
}

// SetDisplayWager - Mutates the private data member "displayWager" bt assigning it to "input"
void Hand::SetDisplayWager() {
    std::string modified_input = color_text(31, round_to_string(GetWager()));
    player->displayWager = modified_input;
}

// SetName - Mutates the private data member "name" bt assigning it to "input"
void Hand::SetName(const std::string& input) {
    player->name = input;
    this->SetDisplayName();
}

// SetHandBankTotals - Mutates the private data member "handBankTotals" bt assigning it to "input"
void Hand::SetHandBankTotals(std::shared_ptr<node<float>>& input) {
    player->handBankTotals->AppendNode(input);
}

// SetHandCardTotals - Mutates the private data member "handCardTotals" bt assigning it to "input"
void Hand::SetHandCardTotals(std::shared_ptr<node<int>>& input) {
    player->handCardTotals->AppendNode(input);
}

// SetHandNets - Mutates the private data member "handNets" bt assigning it to "input"
void Hand::SetHandNets(std::shared_ptr<node<float>>& input) {
    player->handNets->AppendNode(input);
}

// SetHandPlayed - Mutates the private data member "handPlayed" bt assigning it to "input"
void Hand::SetHandPlayed(std::shared_ptr<node<int>>& input) {
    player->handPlayed->AppendNode(input);
}

// SetHandWagers - Mutates the private data member "handWagers" bt assigning it to "input"
void Hand::SetHandWagers(std::shared_ptr<node<float>>& input) {
    player->handWagers->AppendNode(input);
}

// SetPlayerCards - Mutates the private data member "playerCards" bt assigning it to "input"
void Hand::SetPlayerCards(std::shared_ptr<node<Card>>& input) {
    player->playerCards->AppendNode(input);
}

// ----- ----- ----- ----- ----- ----- ----- Getter Functions ----- ----- ----- ----- ----- ----- ----- ----- ----- //
// GetCanBuyInsurance - Retrieves the private data member "canBuyInsurance"
bool& Hand::GetCanBuyInsurance() {
    return player->canBuyInsurance;
}

// GetCanDoubleDown - Retrieves the private data member "canDoubleDown"
bool& Hand::GetCanDoubleDown() {
    return player->canDoubleDown;
}

// GetCanSplitAces - Retrieves the private data member "canSplitAces"
bool& Hand::GetCanSplitAces() {
    return player->canSplitAces;
}

// GetCanSplitHand - Retrieves the private data member "canSplitHand"
bool& Hand::GetCanSplitHand() {
    return player->canSplitHand;
}

// GetChoseBuyInsurance - Retrieves the private data member "choseBuyInsurance"
bool& Hand::GetChoseBuyInsurance() {
    return player->choseBuyInsurance;
}

// GetChoseDoubleDown - Retrieves the private data member "choseDoubleDown"
bool& Hand::GetChoseDoubleDown() {
    return player->choseDoubleDown;
}

// GetChoseSplitAces - Retrieves the private data member "choseSplitAces"
bool& Hand::GetChoseSplitAces() {
    return player->choseSplitAces;
}

// GetChoseSplitHand - Retrieves the private data member "choseSplitHand"
bool& Hand::GetChoseSplitHand() {
    return player->choseSplitHand;
}

// GetDoubleDownResponse - Retrieves the private data member "doubleDownResponse"
bool& Hand::GetDoubleDownResponse() {
    return player->doubleDownResponse;
}

// GetHasBlackJack - Retrieves the private data member "hasBlackJack"
bool& Hand::GetHasBlackJack() {
    return player->hasBlackJack;
}

// GetHasHit - Retrieves the private data member "hasHit"
bool& Hand::GetHasHit() {
    return player->hasHit;
}

// GetParamInHand - Retrieves the private data member "paramInHand"
bool& Hand::GetParamInHand() {
    return player->paramInHand;
}

// GetSameParamInHand - Retrieves the private data member "sameParamInHand"
bool& Hand::GetSameParamInHand() {
    return player->sameParamInHand;
}

// GetShouldDoubleDown - Retrieves the private data member "shouldDoubleDown"
bool& Hand::GetShouldDoubleDown() {
    return player->shouldDoubleDown;
}

// GetShouldHit - Retrieves the private data member "shouldHit"
bool& Hand::GetShouldHit() {
    return player->shouldHit;
}

// GetShouldSplit - Retrieves the private data member "shouldSplit"
bool& Hand::GetShouldSplit() {
    return player->shouldSplit;
}

// GetShouldStand - Retrieves the private data member "shouldStand"
bool& Hand::GetShouldStand() {
    return player->shouldStand;
}

// GetSoftSeventeen - Retrieves the private data member "softSeventeen"
bool& Hand::GetSoftSeventeen() {
    return player->softSeventeen;
}

// GetSplitAcesResponse - Retrieves the private data member "splitAcesResponse"
bool& Hand::GetSplitAcesResponse() {
    return player->splitAcesResponse;
}

// GetSplitHandResponse - Retrieves the private data member "splitHandResponse"
bool& Hand::GetSplitHandResponse() {
    return player->splitHandResponse;
}

// GetBankTotal - Retrieves the private data member "bankTotal"
float& Hand::GetBankTotal() {
    return player->bankTotal;
}

// GetInsuranceWager - Retrieves the private data member "insuranceWager"
float& Hand::GetInsuranceWager() {
    return player->insuranceWager;
}

// GetNet - Retrieves the private data member "net"
float& Hand::GetNet() {
    return player->net;
}

// GetWager - Retrieves the private data member "wager"
float& Hand::GetWager() {
    return player->wager;
}

// GetCardsTotal - Retrieves the private data member "cardsTotal"
int& Hand::GetCardsTotal() {
    return player->cardsTotal;
}

// GetHandsPlayed - Retrieves the private data member "handsPlayed"
int& Hand::GetHandsPlayed() {
    return player->handsPlayed;
}

// GetDisplayBankTotal - Retrieves the private data member "displayBankTotal"
std::string& Hand::GetDisplayBankTotal() {
    return player->displayBankTotal;
}

// GetDisplayCardsTotal - Retrieves the private data member "displayCardsTotal"
std::string& Hand::GetDisplayCardsTotal() {
    return player->displayCardsTotal;
}

// GetDisplayInsuranceWager - Retrieves the private data member "displayInsuranceWager"
std::string& Hand::GetDisplayInsuranceWager() {
    return player->displayInsuranceWager;
}

// GetDisplayName - Retrieves the private data member "displayName"
std::string& Hand::GetDisplayName() {
    return player->displayName;
}

// GetDisplayNet - Retrieves the private data member "displayNet"
std::string& Hand::GetDisplayNet() {
    return player->displayNet;
}

// GetDisplayWager - Retrieves the private data member "displayWager"
std::string& Hand::GetDisplayWager() {
    return player->displayWager;
}

// GetName - Retrieves the private data member "name"
std::string& Hand::GetName() {
    return player->name;
}

// GetHandBankTotals - Retrieves the private data member "handBankTotals"
std::shared_ptr<LinkedList<float>>& Hand::GetHandBankTotals() {
    return player->handBankTotals;
}

// GetHandCardTotals - Retrieves the private data member "handCardTotals"
std::shared_ptr<LinkedList<int>>& Hand::GetHandCardTotals() {
    return player->handCardTotals;
}

// GetHandNets - Retrieves the private data member "handNets"
std::shared_ptr<LinkedList<float>>& Hand::GetHandNets() {
    return player->handNets;
}

// GetHandPlayed - Retrieves the private data member "handPlayed"
std::shared_ptr<LinkedList<int>>& Hand::GetHandPlayed() {
    return player->handPlayed;
}

// GetHandWagers - Retrieves the private data member "handWagers"
std::shared_ptr<LinkedList<float>>& Hand::GetHandWagers() {
    return player->handWagers;
}

// GetPlayerCards - Retrieves the private data member "playerCards"
std::shared_ptr<LinkedList<Card>>& Hand::GetPlayerCards() {
    return player->playerCards;
}