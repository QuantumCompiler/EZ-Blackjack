// ----- ----- ----- ----- ----- ----- ----- Includes ----- ----- ----- ----- ----- ----- ----- ----- ----- //
#include "../Headers/Hand.h"

// ----- ----- ----- ----- ----- ----- ----- Class Functions ----- ----- ----- ----- ----- ----- ----- ----- ----- //
/*  Constructor for Hand Class
*   Input:
*       There is no input required for constructing this class
*   Initialization:
*       Create necessary objects in construction
*       Float Values - All float values set to zero
*       Integer Values - All integer values set to zero
*       String Values - All string values set to empty
*       Vector Values - All vector values set to empty
*/
Hand::Hand() {
    // Object construction
    individualHand = std::make_shared<IndividualHand>();
    individualHand->PlayerCards = std::make_shared<LinkedList<Card>>();
    individualHand->hashTable = std::make_shared<HashTable>(HASTABLESIZE, HASHTABLEITERATIONS);
    // Float Values Initialization
    this->SetInsuranceWager(0);
    this->SetNet(0);
    this->SetWager(0);
    // Integer Values Initialization
    this->SetCardsTotal(0);
    this->GetDisplayCardsTotal().clear();
    this->GetDisplayInsuranceWager().clear();
    this->GetDisplayNet().clear();
    this->GetDisplayWager().clear();
    // List Values Initialization
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
    this->CheckParamInHand("R", Ranks[0]);
    // Iterate over cards
    std::shared_ptr<node<Card>> currentCard = this->GetPlayerCards()->GetRoot();
    while (currentCard != nullptr) {
        // Check if there is a card in hand that has a value of 10
        if (currentCard->data.GetCardValue() == 10) {
            // Check if there is an Ace in the hand and the hand only has 2 cards
            if (this->GetHashTable()->Contains(this->GetValuesMatrix()[2][3]) && this->GetPlayerCards()->GetSize() == 2) {
                this->GetHashTable()->AddToTable(this->GetValuesMatrix()[2][1]);
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
    // Iterate over cards
    std::shared_ptr<node<Card>> currentCard = this->GetPlayerCards()->GetRoot();
    while (currentCard != nullptr) {
        // If the "referenceParameter" is a rank, check for a rank
        if (referenceParameter == "R") {
            if (currentCard->data.CheckCardParam(currentCard->data.GetRank(), checkingParameter)) {
                this->GetHashTable()->AddToTable(this->GetValuesMatrix()[2][3]);
                break;
            }
        }
        // If the "referenceParameter" is a suit, check for a suit
        else if (referenceParameter == "S") {
            if (currentCard->data.CheckCardParam(currentCard->data.GetSuit(), checkingParameter)) {
                this->GetHashTable()->AddToTable(this->GetValuesMatrix()[2][3]);
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
    std::vector<bool> tableCopy = this->GetHashTable()->GetTable();
    this->GetHashTable()->AddToTable(this->GetValuesMatrix()[2][4]);
    // Iterate over the cards in a players hand
    if (this->GetPlayerCards()->GetSize() > 1) {
        for (int i = 1; i < this->GetPlayerCards()->GetSize(); i++) {
            std::shared_ptr<node<Card>> currentCard = this->GetPlayerCards()->RetrieveNode(i);
            // If the "referenceParameter" is a rank, check for the same rank in a hand
            if (referenceParameter == "R") {
                if (!currentCard->data.CheckCardParam(currentCard->data.GetRank(), this->GetPlayerCards()->RetrieveNode(0)->data.GetRank()) || (!checkingParameter.empty() && !currentCard->data.CheckCardParam(currentCard->data.GetRank(), checkingParameter))) {
                    this->GetHashTable()->GetTable() = tableCopy;
                    break;
                }
            }
            // If the "referenceParameter" is a suit, check for the same suit in a hand
            if (referenceParameter == "S") {
                if (!currentCard->data.CheckCardParam(currentCard->data.GetSuit(), this->GetPlayerCards()->RetrieveNode(0)->data.GetSuit()) || (!checkingParameter.empty() && !currentCard->data.CheckCardParam(currentCard->data.GetSuit(), checkingParameter))) {
                    this->GetHashTable()->GetTable() = tableCopy;
                    break;
                }
            }
        }
    }
    return *this;
}

/*  CopyVariables - Copies select data members from one hand to the current hand
*   Input:
*       input - Hand object passed by reference that is used to copy data members from
*   Algorithm:
*       * Copy the wager of "input" for the current hand with SetWager
*   Output:
*       This function returns a Hand object after copying select variables
*/
Hand Hand::CopyVariables(std::shared_ptr<Hand>& input) {
    // Copy wager
    this->SetWager(input->GetWager());
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
Hand Hand::HitHand(std::shared_ptr<Shoe>& input) {
    // Add card to current hand
    std::shared_ptr<Card> drawnCard = input->Draw();
    std::shared_ptr<node<Card>> cardNode = this->GetPlayerCards()->InitNode(drawnCard);
    this->AddCardToHand(cardNode);
    return *this;
}

/*  InsurancePrompt - Prompts a player if they would like to buy insurance
*   Input:
*       bank - Float value that is passed by reference that represents a players bank
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
Hand Hand::InsurancePrompt(float& bank) {
    std::string input;
    while (true) {
        // Prompt user for insurance
        std::cout << std::endl << "Would you like to buy insurance? Insurance pays (2:1). (y/n): "; time_sleep(SHORT_TIME_SLEEP);
        std::cin >> input; time_sleep(SHORT_TIME_SLEEP);
        // User has chosen to buy insurance, set insurance wager
        if (input == "y") {
            this->GetHashTable()->AddToTable(this->GetValuesMatrix()[0][4]);
            this->SetInsuranceWager(round_input(0.5*this->GetWager()));
            bank -= this->GetInsuranceWager();
            return *this;
        }
        // User has chosen to not buy insurance, do not take insurance wager
        else if (input == "n") {
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

/*  InsuranceSim - Determines if a player is to place an insurance wager in a simulated hand
*   Input:
*       bank - Float value that is passed by reference that represents a players bank total
*       input - Constant boolean value that is passed by reference that indicates if a player is going to place an insurance wager or not
*   Algorithm:
*       * Update the players hash table to indicate that they have placed an insurance wager
*       * Set the insurance wager for a player
*       * Withdraw the currency from a players bank
*   Output:
*       This function returns a Hand object after prompting the user about buying insurance
*/
Hand Hand::InsuranceSim(float& bank, const bool& input) {
    if (input) {
        this->GetHashTable()->AddToTable(this->GetValuesMatrix()[0][4]);
        this->SetInsuranceWager(round_input(0.5*this->GetWager()));
        bank -= this->GetInsuranceWager();
        return *this;
    }
    else {
        return *this;
    }
}

/*  ParametersCheck - Checks to see if certain parameters in regards to wagering are met
*   Input:
*       dealerHand - Hand object passed by reference that represents the dealer's hand
*   Algorithm:
*       * This algorithm checks for specific parameters that pertain to how the player can play their hand
*       * The parameters that are checked are the following:
*           * Blackjack Check - Checks to see if the players have blackjack or not
*           * Insurance Check - Checks to see if the player is able to buy insurance for their hand
*           * Double Down Check - Checks to see if the player is able to double down for their hand
*           * Soft Seventeen Check - Checks to see if the player possesses a soft seventeen in their hand
*   Output:
*       This function returns a Hand object after checking the parameters in the current hand
*/
Hand Hand::ParametersCheck(std::shared_ptr<Hand>& dealerHand, const float& playerBank) {
    // Reset Parameters
    // Clear same parameter check
    if (this->GetHashTable()->Contains(this->GetValuesMatrix()[2][4])) {
        this->GetHashTable()->RemoveElement(this->GetValuesMatrix()[2][4]);
    }
    // Clear blackjack check
    if (this->GetHashTable()->Contains(this->GetValuesMatrix()[2][1])) {
        this->GetHashTable()->RemoveElement(this->GetValuesMatrix()[2][1]);
    }
    // Clear dealer blackjack
    if (dealerHand->GetHashTable()->Contains(dealerHand->GetValuesMatrix()[2][1])) {
        dealerHand->GetHashTable()->RemoveElement(dealerHand->GetValuesMatrix()[2][1]);
    }
    // Clear can split aces
    if (this->GetHashTable()->Contains(this->GetValuesMatrix()[0][2])) {
        this->GetHashTable()->RemoveElement(this->GetValuesMatrix()[0][2]);
    }
    // Clear can split hand
    if (this->GetHashTable()->Contains(this->GetValuesMatrix()[0][3])) {
        this->GetHashTable()->RemoveElement(this->GetValuesMatrix()[0][3]);
    }
    // Clear can buy insurance
    if (this->GetHashTable()->Contains(this->GetValuesMatrix()[0][0])) {
        this->GetHashTable()->RemoveElement(this->GetValuesMatrix()[0][0]);
    }
    // Clear can double down
    if (this->GetHashTable()->Contains(this->GetValuesMatrix()[0][1])) {
        this->GetHashTable()->RemoveElement(this->GetValuesMatrix()[0][1]);
    }
    // Clear soft seventeen
    if (this->GetHashTable()->Contains(this->GetValuesMatrix()[3][4])) {
        this->GetHashTable()->RemoveElement(this->GetValuesMatrix()[3][4]);
    }
    // Clear should double down
    if (this->GetHashTable()->Contains(this->GetValuesMatrix()[3][0])) {
        this->GetHashTable()->RemoveElement(this->GetValuesMatrix()[3][0]);
    }
    // Clear should hit
    if (this->GetHashTable()->Contains(this->GetValuesMatrix()[3][1])) {
        this->GetHashTable()->RemoveElement(this->GetValuesMatrix()[3][1]);
    }
    // Clear should split
    if (this->GetHashTable()->Contains(this->GetValuesMatrix()[3][2])) {
        this->GetHashTable()->RemoveElement(this->GetValuesMatrix()[3][2]);
    }
    // Clear should stand
    if (this->GetHashTable()->Contains(this->GetValuesMatrix()[3][3])) {
        this->GetHashTable()->RemoveElement(this->GetValuesMatrix()[3][3]);
    }
    this->CheckSameParamInHand("R");
    this->CheckBlackJack();
    // Dealer Checks
    dealerHand->CheckBlackJack();
    // Can Split Hand Check
    if (this->GetHashTable()->Contains(this->GetValuesMatrix()[2][4]) && this->GetPlayerCards()->GetSize() == 2) {
        // Player has enough money to split
        if (playerBank >= this->GetWager()) {
            // Checking if player has aces
            bool aces = this->GetPlayerCards()->RetrieveNode(0)->data.CheckCardParam(this->GetPlayerCards()->RetrieveNode(0)->data.GetRank(), Ranks[0]);
            // Player doesn't have Aces, can still split hand
            if (!aces) {
                this->GetHashTable()->AddToTable(this->GetValuesMatrix()[0][3]);
            }
            // Player has Aces, can split Aces, can't split regular hand
            else {
                this->GetHashTable()->AddToTable(this->GetValuesMatrix()[0][2]);
            }
        }
    }
    // Insurance Check
    if (dealerHand->GetPlayerCards()->RetrieveNode(-1)->data.GetRank() == Ranks[0] && !this->GetHashTable()->Contains(this->GetValuesMatrix()[1][1])) {
        // Player has enough money to buy insurance
        if (playerBank >= 0.5*this->GetWager()) {
            this->GetHashTable()->AddToTable(this->GetValuesMatrix()[0][0]);
        }
    }
    // Can Double Down Check
    if (!this->GetHashTable()->Contains(this->GetValuesMatrix()[1][1]) && !this->GetHashTable()->Contains(this->GetValuesMatrix()[2][0])) {
        if (playerBank >= this->GetWager() && this->GetPlayerCards()->GetSize() <= 2) {
            this->GetHashTable()->AddToTable(this->GetValuesMatrix()[0][1]);
        }
    }
    // Soft Seventeen Check
    if (this->GetCardsTotal() == 17) {
        std::shared_ptr<node<Card>> current = this->GetPlayerCards()->GetRoot();
        while (current != nullptr) {
            if (current->data.GetRank() == Ranks[0] && current->data.GetCardValue() == 11) {
                this->GetHashTable()->AddToTable(this->GetValuesMatrix()[3][4]);
                break;
            }
            current = current->nextNode;
        }
    }
    return *this;
}

/*  PlaceWagerPrompt - Prompts the user to input a wager for their hand
*   Input:
*       bank - Float value that is passed by reference that represents a players bank total
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
Hand Hand::PlaceWagerPrompt(float& bank) {
    float input;
    while (true) {
        // Prompt user for the wager that they would like place for their hand
        std::cout << std::endl << "Please enter a wager for this hand. Current bank total: " << color_text(33, std::to_string(round_input(bank))) << ": "; time_sleep(SHORT_TIME_SLEEP);
        std::cin >> input; time_sleep(SHORT_TIME_SLEEP);
        const std::type_info& result = typeid(input);
        std::string checkResult = result.name();
        // Check if the input is not a float or integer
        if (checkResult != "f" && checkResult != "i") {
            std::cout << std::endl << color_text(31, "Invalid Response") << ". Please re-enter your submission." << std::endl; time_sleep(SHORT_TIME_SLEEP);
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
                std::cout << std::endl << color_text(31, "Invalid Response") << " of " << color_text(31, std::to_string(round_input(input))) << ". Please re-enter a positive value." << std::endl; time_sleep(SHORT_TIME_SLEEP);
                clear_terminal();
                checkResult.clear();
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                continue;
            }
            // User has entered a value that is greater than zero
            else {
                // User has entered a wager that is greater than their bank, return to beginning of while loop
                if (input > bank) {
                    std::cout << std::endl << color_text(31, "Invalid Response") << " of " << color_text(31, std::to_string(round_input(input))) << ". You must enter a wager that is less than or equal to your bank total "
                    << color_text(33, std::to_string(round_input(bank))) << ". Please re-enter your submission." << std::endl; time_sleep(SHORT_TIME_SLEEP);
                    clear_terminal();
                    checkResult.clear();
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    continue;
                }
                // User has entered a valid input for a wager, set the private data member "wager" to "input"
                else {
                    this->SetWager(input);
                    bank -= this->GetWager();
                    std::cout << std::endl << "Player has wagered: " << this->GetDisplayWager() << " with a current bank total " << color_text(33, std::to_string(round_input(bank))) << "." << std::endl; time_sleep(SHORT_TIME_SLEEP);
                    return *this;
                }
            }
        }
    }
}

/*  PlaceWagerSim - Places a wager for a the hand of a simulated game
*   Input:
*       bank - Constant float passed by reference to represent the bank of a player
*       wager - Float passed by reference to represent the wager for a given hand
*   Algorithm:
*       * Set the wager for the current hand
*       * Update the bank total for the player
*       * Return the hand object
*   Output:
*       This function returns a Hand object after setting the wager of a players hand
*/
Hand Hand::PlaceWagerSim(float& bank, const float& wager) {
    this->SetWager(wager);
    bank -= wager;
    return *this;
}

/*  ResetHand - Resets some private data members of a player
*   Input:
*       This function does not have any input parameters
*   Algorithm:
*       * Resets hash table of player
*       * Resets all float values to 0.00
*       * Resets all integer values to 0
*       * Clears all string values
*       * Clears all list values
*   Output:
*       This function returns a Hand object after resetting select private data members
*/
Hand Hand::ResetHand() {
    // Table values
    this->GetHashTable()->ClearHashTable();
    // Float Values
    this->SetInsuranceWager(0.00);
    this->SetNet(0.00);
    this->SetWager(0.00);
    // Integer Values
    this->SetCardsTotal(0);
    // String Values
    this->GetDisplayCardsTotal().clear();
    this->GetDisplayInsuranceWager().clear();
    this->GetDisplayNet().clear();
    this->GetDisplayWager().clear();
    // List Values
    this->GetPlayerCards()->ClearList();
    return *this;
}

// ----- ----- ----- ----- ----- ----- ----- Setter Functions ----- ----- ----- ----- ----- ----- ----- ----- ----- //
// SetInsuranceWager - Mutates the private data member "insuranceWager" by assigning it to "input"
void Hand::SetInsuranceWager(const float& input) {
    float rounded_input = round_input(input);
    individualHand->insuranceWager = rounded_input;
    this->SetDisplayInsuranceWager();
}

// SetNet - Mutates the private data member "net" by assigning it to "input"
void Hand::SetNet(const float& input) {
    float rounded_input = round_input(input);
    individualHand->net = rounded_input;
    this->SetDisplayNet();
}

// SetWager - Mutates the private data member "wager" by assigning it to "input"
void Hand::SetWager(const float& input) {
    float rounded_input = round_input(input);
    individualHand->wager = rounded_input;
    this->SetDisplayWager();
}

// SetCardsTotal - Mutates the private data member "cardsTotal" by assigning it to "input"
void Hand::SetCardsTotal(const int& input) {
    individualHand->cardsTotal = input;
    this->SetDisplayCardsTotal();
}

// SetDisplayCardsTotal - Mutates the private data member "displayCardsTotal" by assigning it to "input"
void Hand::SetDisplayCardsTotal() {
    std::string modified_input = color_text(35, std::to_string(GetCardsTotal()));
    individualHand->displayCardsTotal = modified_input;
}

// SetDisplayInsuranceWager - Mutates the private data member "displayInsuranceWager" by assigning it to "input"
void Hand::SetDisplayInsuranceWager() {
    std::string modified_input = color_text(31, round_to_string(GetInsuranceWager()));
    individualHand->displayInsuranceWager = modified_input;
}

// SetDisplayNet - Mutates the private data member "displayNet" by assigning it to "input"
void Hand::SetDisplayNet() {
    std::string modified_input = color_text(33, round_to_string(GetNet()));
    individualHand->displayNet = modified_input;
}

// SetDisplayWager - Mutates the private data member "displayWager" bt assigning it to "input"
void Hand::SetDisplayWager() {
    std::string modified_input = color_text(31, round_to_string(GetWager()));
    individualHand->displayWager = modified_input;
}

// SetPlayerCards - Mutates the private data member "PlayerCards" bt assigning it to "input"
void Hand::SetPlayerCards(std::shared_ptr<node<Card>>& input) {
    individualHand->PlayerCards->AppendNode(input);
}

// ----- ----- ----- ----- ----- ----- ----- Getter Functions ----- ----- ----- ----- ----- ----- ----- ----- ----- //
// GetHashTable - Retrieves the private data member "hashTable"
std::shared_ptr<HashTable>& Hand::GetHashTable() {
    return individualHand->hashTable;
}

// GetValuesMatrix - Retrieves the private data member "valuesMatrix"
std::vector<std::vector<std::string>>& Hand::GetValuesMatrix() {
    return individualHand->valuesMatrix;
}

// GetInsuranceWager - Retrieves the private data member "insuranceWager"
float& Hand::GetInsuranceWager() {
    return individualHand->insuranceWager;
}

// GetNet - Retrieves the private data member "net"
float& Hand::GetNet() {
    return individualHand->net;
}

// GetWager - Retrieves the private data member "wager"
float& Hand::GetWager() {
    return individualHand->wager;
}

// GetCardsTotal - Retrieves the private data member "cardsTotal"
int& Hand::GetCardsTotal() {
    return individualHand->cardsTotal;
}

// GetDisplayCardsTotal - Retrieves the private data member "displayCardsTotal"
std::string& Hand::GetDisplayCardsTotal() {
    return individualHand->displayCardsTotal;
}

// GetDisplayInsuranceWager - Retrieves the private data member "displayInsuranceWager"
std::string& Hand::GetDisplayInsuranceWager() {
    return individualHand->displayInsuranceWager;
}

// GetDisplayNet - Retrieves the private data member "displayNet"
std::string& Hand::GetDisplayNet() {
    return individualHand->displayNet;
}

// GetDisplayWager - Retrieves the private data member "displayWager"
std::string& Hand::GetDisplayWager() {
    return individualHand->displayWager;
}

// GetPlayerCards - Retrieves the private data member "PlayerCards"
std::shared_ptr<LinkedList<Card>>& Hand::GetPlayerCards() {
    return individualHand->PlayerCards;
}