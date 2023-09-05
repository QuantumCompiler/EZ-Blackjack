// ----- ----- ----- ----- ----- ----- ----- Includes ----- ----- ----- ----- ----- ----- ----- ----- ----- //
#include "../Headers/Player.h"

// ----- ----- ----- ----- ----- ----- ----- Class Functions ----- ----- ----- ----- ----- ----- ----- ----- ----- //

/*  Constructor for Player class
*   Input:
*       This constructor does not require and input for it
*   Initialization:
*       Initialize the "playerParameter" structure
*       Set all float and integer values to 0
*       Create list objects
*       Set all strings to empty
*/
Player::Player() {
    // playerParameter initialization
    playerParameters = std::make_shared<PlayerParameters>();
    // Float values
    playerParameters->bankTotal = 0;
    // Integer values
    playerParameters->blackjackHands = 0;
    playerParameters->currentHandsPossessed = 0;
    playerParameters->handsLost = 0;
    playerParameters->handsPlayed = 0;
    playerParameters->handsPushed = 0;
    playerParameters->handsWon = 0;
    // Lists
    playerParameters->CurrentHands = std::make_shared<LinkedList<std::shared_ptr<Hand>>>();
    playerParameters->HandBankTotals = std::make_shared<LinkedList<float>>();
    playerParameters->HandCardTotals = std::make_shared<LinkedList<int>>();
    playerParameters->HandNets = std::make_shared<LinkedList<float>>();
    playerParameters->HandsPlayed = std::make_shared<LinkedList<int>>();
    playerParameters->HandWagers = std::make_shared<LinkedList<float>>();
    // Strings
    playerParameters->displayBankTotal = "";
    playerParameters->displayName = "";
    playerParameters->name = "";
}

// Deconstructor for Player class
Player::~Player() {}

/*  BankDepositPrompt - Updates the private data member "bankTotal" to represent a players bank total
*   Input:
*       This function does not have any input parameters
*   Algorithm:
*       * First create a float value that represents the bank total of a player prior to depositing
*       * Check for valid input
*           * If the input is valid, set the input to the bank total
*           * If the input is not valid, restart the loop
*       * We then initialize some values for the statistics tracking of the player
*   Output:
*       This function returns a Hand object after depositing currency into a players bank
*/
Player Player::BankDepositPrompt() {
    while (true) {
        float input;
        // Prompt user for deposit
        std::cout << std::endl; animate_text("Please enter the amount you'd like to deposit into your bank: ", PRINT_LINE_SLEEP);
        std::cin >> input;
        // Check for valid input
        if (input_validation(input)) {
            this->SetBankTotal(input);
            break;
        }
        else {
            continue;
        }
    }
    std::cout << std::endl; animate_text(this->GetDisplayName() + " has decided to start with: " + this->GetDisplayBankTotal() + " in their bank.", PRINT_LINE_SLEEP); std::cout << std::endl;
    return *this;
}

/*  NamePrompt - Prompts a user to input a name for their player
*   Input:
*       This function does not have any input parameters
*   Algorithm:
*       * Create a string value "input" and prompt the user for what they want their name to be
*       * Call the "SetName" function to set the private data member "name" to "input"
*   Output:
*       This function returns a Player object after prompting the user about what their name will be
*/
Player Player::NamePrompt() {
    std::string input;
    // Prompt user for their name
    std::cout << std::endl; animate_text("Pleas enter a name for you player: ", PRINT_LINE_SLEEP);
    std::getline(std::cin, input);
    // Set the players name to "input"
    this->SetName(input);
    // std::cout << "\033[1A\r" << std::string(namePrompt.length() + input.length(), ' ') << "\r";
    return *this;
}

/*  ResetPlayer - Resets parameters for a player to continue playing in the game of blackjack
*   Input:
*       This function does not have any input parameters
*   Algorithm:
*       * Reset all the hands of the current player
*       * Remove all hands from the current player
*       * Set the number of hands that a player possesses to be zero
*   Output:
*       This function returns a Player object after clearing the current hands that they are playing with
*/
Player Player::ResetPlayer() {
    for (int i = 0; i < this->GetCurrentHands()->GetSize(); i++) {
        this->GetCurrentHands()->RetrieveNode(i)->data->ResetHand();
    }
    this->GetCurrentHands()->ClearList();
    this->GetCurrentHandsPossessed() = this->GetCurrentHands()->GetSize();
    return *this;
}

/*  ShowHand - This function displays the cards that are present in a players hand
*   Input:
*       inputHand - Hand object that is passed by reference that represents the hand that is to be shown
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
*       This function returns a Player object after displaying what cards they have
*/
Player Player::ShowCurrentHand(std::shared_ptr<Hand>& inputHand, std::string option, const std::string dealerShow) {
    // Test to see if the option value is empty
    if (option.empty()) {
        option = "current";
    }
    // Get wager without insurance
    float origWager = inputHand->GetWager() - inputHand->GetInsuranceWager();
    std::string origWagerVal = color_text(31, round_to_string(origWager));
    // Modify the string values
    std::string finalHandTotal (color_text(35, "Final Hand Total"));
    std::string handTotal = color_text(35, "Current Hand Total");
    std::string optionMod = color_text(34, option);
    // The player is not the dealer
    if (this->GetName() != "Dealer") {
        this->SetBankTotal(this->GetBankTotal());
        // Modify more string values
        std::string bankTotal = color_text(33, "Current Bank Total");
        std::string finalBankTotal = color_text(33, "Final Bank Total");
        std::string handWager = color_text(31, "Hand Wager");
        std::string handNet = color_text(31, "Hand Net");
        std::string insuranceWager = color_text(31, "Insurance Wager");
        animate_text(this->GetDisplayName() + "'s " + optionMod + " hand: [", PRINT_LINE_SLEEP / 2);
        // Iterate through the cards in players hand
        for (int i = 0; i < inputHand->GetPlayerCards()->GetSize(); i++) {
            if (i == inputHand->GetPlayerCards()->GetSize() - 1) {
                animate_text(inputHand->GetPlayerCards()->RetrieveNode(i)->data.PrintCard() + "] ", PRINT_LINE_SLEEP / 2);
            }
            else {
                animate_text(inputHand->GetPlayerCards()->RetrieveNode(i)->data.PrintCard() + " , ", PRINT_LINE_SLEEP / 2);
            }
        }
        // Add hand total and display players hand parameters
        inputHand->AddHandTotal();
        if (option == "Final") {
            if (inputHand->GetInsuranceWager() > 0) {
                animate_text(finalHandTotal + ": " + inputHand->GetDisplayCardsTotal() + " , " + handWager + ": " + origWagerVal + " , " + insuranceWager + ": " + inputHand->GetDisplayInsuranceWager() + " , " + handNet + ": " + inputHand->GetDisplayNet() 
                + " , " + finalBankTotal + ": " + this->GetDisplayBankTotal(), PRINT_LINE_SLEEP / 2); std::cout << std::endl;
            }
            else {
                animate_text(finalHandTotal + ": " + inputHand->GetDisplayCardsTotal() + " , " + handWager + ": " + inputHand->GetDisplayWager() + " , " + handNet + ": " + inputHand->GetDisplayNet() + " , " + finalBankTotal + ": " + this->GetDisplayBankTotal(), PRINT_LINE_SLEEP / 2); std::cout << std::endl;
            }
        }
        else {
            if (inputHand->GetInsuranceWager() > 0) {
                animate_text(handTotal + ": " + inputHand->GetDisplayCardsTotal() + " , " + handWager + ": " + inputHand->GetDisplayWager() + " , " + insuranceWager + ": " + inputHand->GetDisplayInsuranceWager() + " , " + bankTotal + ": " + this->GetDisplayBankTotal(), PRINT_LINE_SLEEP / 2); std::cout << std::endl;
            }
            else {
                animate_text(handTotal + ": " + inputHand->GetDisplayCardsTotal() + " , " + handWager + ": " + inputHand->GetDisplayWager() + " , " + bankTotal + ": " + this->GetDisplayBankTotal(), PRINT_LINE_SLEEP / 2); std::cout << std::endl;
            }
        }
    }
    // The player is the dealer
    else if (this->GetName() == "Dealer") {
        // Dealer is hiding a card
        if (dealerShow.empty()) {
            std::string backCard = color_text(35, std::to_string(inputHand->GetPlayerCards()->RetrieveNode(-1)->data.GetCardValue()));
            animate_text(this->GetDisplayName() + "'s " + optionMod + " hand : [Hidden, " + inputHand->GetPlayerCards()->RetrieveNode(-1)->data.PrintCard() + "] " + handTotal + ": " + backCard, PRINT_LINE_SLEEP / 2); std::cout << std::endl;
        }
        // Dealer is showing both cards
        else {
            if (dealerShow != "cards") {
                animate_text(this->GetDisplayName() + "'s " + optionMod + " hand: [", PRINT_LINE_SLEEP / 2);
            }
            // Specialized display of cards
            else {
                animate_text("[", PRINT_LINE_SLEEP / 2);
            }
            // Iterate through the cards in dealers hand
            for (int i = 0; i < inputHand->GetPlayerCards()->GetSize(); i++) {
                if (i == inputHand->GetPlayerCards()->GetSize() - 1) {
                    animate_text(inputHand->GetPlayerCards()->RetrieveNode(i)->data.PrintCard() + "] ", PRINT_LINE_SLEEP / 2);
                }
                else {
                    animate_text(inputHand->GetPlayerCards()->RetrieveNode(i)->data.PrintCard() + " , ", PRINT_LINE_SLEEP / 2);
                }
            }
            // Add hand total and display players hand parameters
            inputHand->AddHandTotal();
            if (option == "Final") {
                animate_text(finalHandTotal + ": " + inputHand->GetDisplayCardsTotal(), PRINT_LINE_SLEEP / 2); std::cout << std::endl;
            }
            else {
                animate_text(handTotal + ": " + inputHand->GetDisplayCardsTotal(), PRINT_LINE_SLEEP / 2); std::cout << std::endl;
            }
        }
    }
    return *this;
}

/*  UpdateBank - Updates the bank of a player
*   Input:
*       inputHand - Hand object that is passed by reference
*       choice - Constant integer that is supposed to represent the outcome of a hand
*   Algorithm:
*       * Grab the current bank value with "current_bank"
*       * The following codes represent what the choices mean
*           * 0 - Player withdraws money from bank (placing wager)
*           * 1 - Player wins hand
*           * 2 - Player loses hand
*           * 3 - Player pushes hand
*           * 4 - Player wins blackjack
*           * 5 - Player wins hand, loses insurance
*           * 6 - Player loses hand, wins insurance
*           * 7 - Player loses hand, loses insurance
*           * 8 - Player has blackjack, wins insurance
*           * 9 - Player has blackjack, loses insurance
*   Output:
*       This function returns a Hand object after updating the players bank
*/
Player Player::UpdateBank(std::shared_ptr<Hand>& inputHand, const int choice) {
    // Update hand wager
    float total_wager = inputHand->GetWager() + inputHand->GetInsuranceWager();
    inputHand->SetWager(total_wager);
    // Choices of outcome
    switch (choice) {
    // 0 - Player withdraws money from bank (places wager)
    case 0:
        this->SetBankTotal(this->GetBankTotal() - (inputHand->GetWager() - inputHand->GetInsuranceWager()));
        return *this;
    // 1 - Player wins hand
    case 1:
        // Update hands won and hands played
        this->SetHandsWon();
        this->SetHandsPlayed();
        // Update net and bank total
        inputHand->SetNet(round_input(inputHand->GetWager()));
        this->SetBankTotal(round_input(this->GetBankTotal() + 2 * inputHand->GetNet()));
        // Update lists
        this->SetTotalHandBankTotals(this->GetBankTotal());
        this->SetTotalHandCardTotals(inputHand->GetCardsTotal());
        this->SetTotalHandNets(inputHand->GetNet());
        this->SetTotalHandsPlayed(this->GetHandsPlayed());
        this->SetTotalHandWagers(inputHand->GetWager());
        return *this;
    // 2 - Player loses hand
    case 2:
        // Update hands lost and hands played
        this->SetHandsLost();
        this->SetHandsPlayed();
        // Update net and bank total
        inputHand->SetNet(round_input(-inputHand->GetWager()));
        this->SetBankTotal(this->GetBankTotal());
        // Update lists
        this->SetTotalHandBankTotals(this->GetBankTotal());
        this->SetTotalHandCardTotals(inputHand->GetCardsTotal());
        this->SetTotalHandNets(inputHand->GetNet());
        this->SetTotalHandsPlayed(this->GetHandsPlayed());
        this->SetTotalHandWagers(inputHand->GetWager());
        return *this;
    // 3 - Player pushes hand
    case 3:
        // Update hands pushed and hands played
        this->SetHandsPushed();
        this->SetHandsPlayed();
        // Update net and bank total
        inputHand->SetNet(0);
        this->SetBankTotal(this->GetBankTotal() + inputHand->GetWager());
        // Update lists
        this->SetTotalHandBankTotals(this->GetBankTotal());
        this->SetTotalHandCardTotals(inputHand->GetCardsTotal());
        this->SetTotalHandNets(inputHand->GetNet());
        this->SetTotalHandsPlayed(this->GetHandsPlayed());
        this->SetTotalHandWagers(inputHand->GetWager());
        return *this;
    // 4 - Player wins blackjack
    case 4:
        // Update blackjack hands and hands played
        this->SetBlackjackHands();
        this->SetHandsPlayed();
        // Update net and bank total
        inputHand->SetNet(round_input(1.5 * inputHand->GetWager()));
        this->SetBankTotal(round_input(this->GetBankTotal() + round_input((5 * inputHand->GetNet()) / 3)));
        // Update lists
        this->SetTotalHandBankTotals(this->GetBankTotal());
        this->SetTotalHandCardTotals(inputHand->GetCardsTotal());
        this->SetTotalHandNets(inputHand->GetNet());
        this->SetTotalHandsPlayed(this->GetHandsPlayed());
        this->SetTotalHandWagers(inputHand->GetWager());
        return *this;
    // 5 - Player wins hand, loses insurance
    case 5:
        // Update hands won and hands played
        this->SetHandsWon();
        this->SetHandsPlayed();
        // Update net and bank total
        inputHand->SetNet(round_input(inputHand->GetWager() / 3));
        this->SetBankTotal(round_input(this->GetBankTotal() + 4 * inputHand->GetNet()));
        // Update lists
        this->SetTotalHandBankTotals(this->GetBankTotal());
        this->SetTotalHandCardTotals(inputHand->GetCardsTotal());
        this->SetTotalHandNets(inputHand->GetNet());
        this->SetTotalHandsPlayed(this->GetHandsPlayed());
        this->SetTotalHandWagers(inputHand->GetWager());
        return *this;
    // 6 - Player loses hand, wins insurance
    case 6:
        // Update hands lost and hands played
        this->SetHandsLost();
        this->SetHandsPlayed();
        // Update net and bank total
        inputHand->SetNet(0);
        this->SetBankTotal(round_input(this->GetBankTotal() + inputHand->GetWager()));
        // Update lists
        this->SetTotalHandBankTotals(this->GetBankTotal());
        this->SetTotalHandCardTotals(inputHand->GetCardsTotal());
        this->SetTotalHandNets(inputHand->GetNet());
        this->SetTotalHandsPlayed(this->GetHandsPlayed());
        this->SetTotalHandWagers(inputHand->GetWager());
        return *this;
    // 7 - Player loses hand, loses insurance
    case 7:
        // Update hands lost and hands played
        this->SetHandsLost();
        this->SetHandsPlayed();
        // Update net and bank total
        inputHand->SetNet(-round_input(inputHand->GetWager()));
        this->SetBankTotal(round_input(this->GetBankTotal()));
        // Update lists
        this->SetTotalHandBankTotals(this->GetBankTotal());
        this->SetTotalHandCardTotals(inputHand->GetCardsTotal());
        this->SetTotalHandNets(inputHand->GetNet());
        this->SetTotalHandsPlayed(this->GetHandsPlayed());
        this->SetTotalHandWagers(inputHand->GetWager());
        return *this;
    // 8 - Player has blackjack, wins insurance
    case 8:
        // Update hands pushed and hands played (this is not considered a win, since we are comparing dealer hand to player hand)
        this->SetHandsPushed();
        this->SetHandsPlayed();
        // Update net and bank total
        inputHand->SetNet(round_input((2 * inputHand->GetWager()) / 3));
        this->SetBankTotal(round_input(this->GetBankTotal() + 2.5 * inputHand->GetNet()));
        // Update lists
        this->SetTotalHandBankTotals(this->GetBankTotal());
        this->SetTotalHandCardTotals(inputHand->GetCardsTotal());
        this->SetTotalHandNets(inputHand->GetNet());
        this->SetTotalHandsPlayed(this->GetHandsPlayed());
        this->SetTotalHandWagers(inputHand->GetWager());
        return *this;
    // 9 - Player has blackjack, loses insurance
    case 9:
        // Update blackjack hands and hands played
        this->SetBlackjackHands();
        this->SetHandsPlayed();
        // Update net and bank total
        inputHand->SetNet(round_input((2 * inputHand->GetWager()) / 3));
        this->SetBankTotal(round_input(this->GetBankTotal() + 2.5 * inputHand->GetNet()));
        // Update lists
        this->SetTotalHandBankTotals(this->GetBankTotal());
        this->SetTotalHandCardTotals(inputHand->GetCardsTotal());
        this->SetTotalHandNets(inputHand->GetNet());
        this->SetTotalHandsPlayed(this->GetHandsPlayed());
        this->SetTotalHandWagers(inputHand->GetWager());
        return *this;
    default:
        return *this;
    }
}

// ----- ----- ----- ----- ----- ----- ----- Mutator Functions ----- ----- ----- ----- ----- ----- ----- ----- ----- //
// Setters
// SetBankTotal - Mutates the private data member "bankTotal" with that of "input"
void Player::SetBankTotal(const float& input) {
    float modInput = round_input(input);
    playerParameters->bankTotal = modInput;
    this->SetDisplayBankTotal();
}

// SetBlackjackHands - Mutates the private data member "blackjackHands" with that of "input"
void Player::SetBlackjackHands() {
    playerParameters->blackjackHands++;
}

// SetCurrentHandsPossessed - Mutates the private data member "currentHandsPossessed" with that of "input"
void Player::SetCurrentHandsPossessed() {
    playerParameters->currentHandsPossessed++;
}

// SetHandsLost - Mutates the private data member "handsLost" with that of "input"
void Player::SetHandsLost() {
    playerParameters->handsLost++;
}

// SetHandsPlayed - Mutates the private data member "handsPlayed" with that of "input"
void Player::SetHandsPlayed() {
    playerParameters->handsPlayed++;
}

// SetHandsPushed - Mutates the private data member "handsPushed" with that of "input"
void Player::SetHandsPushed() {
    playerParameters->handsPushed++;
}

// SetHandsWon - Mutates the private data member "handsWon" with that of "input"
void Player::SetHandsWon() {
    playerParameters->handsWon++;
}

// SetCurrentHands - Mutates the private data member "CurrentHands" with that of "input"
void Player::SetCurrentHands(const std::shared_ptr<Hand>& input) {
    std::shared_ptr<node<std::shared_ptr<Hand>>> inputNode = playerParameters->CurrentHands->InitNode(input);
    playerParameters->CurrentHands->AppendNode(inputNode);
    this->SetCurrentHandsPossessed();
}

// SetTotalHandBankTotals - Mutates the private data member "HandBankTotals" with that of "input"
void Player::SetTotalHandBankTotals(const float& input) {
    std::shared_ptr<node<float>> inputNode = playerParameters->HandBankTotals->InitNode(input);
    playerParameters->HandBankTotals->AppendNode(inputNode);
}

// SetTotalHandCardTotals - Mutates the private data member "HandCardTotals" with that of "input"
void Player::SetTotalHandCardTotals(const int& input) {
    std::shared_ptr<node<int>> inputNode = playerParameters->HandCardTotals->InitNode(input);
    playerParameters->HandCardTotals->AppendNode(inputNode);
}

// SetTotalHandNets - Mutates the private data member "HandNets" with that of "input"
void Player::SetTotalHandNets(const float& input) {
    std::shared_ptr<node<float>> inputNode = playerParameters->HandNets->InitNode(input);
    playerParameters->HandNets->AppendNode(inputNode);
}

// SetTotalHandsPlayed - Mutates the private data member "HandsPlayed" with that of "input"
void Player::SetTotalHandsPlayed(const int& input) {
    std::shared_ptr<node<int>> inputNode = playerParameters->HandsPlayed->InitNode(input);
    playerParameters->HandsPlayed->AppendNode(inputNode);
}

// SetTotalHandWagers - Mutates the private data member "HandWagers" with that of "input"
void Player::SetTotalHandWagers(const float& input) {
    std::shared_ptr<node<float>> inputNode = playerParameters->HandWagers->InitNode(input);
    playerParameters->HandWagers->AppendNode(inputNode);
}

// SetDisplayBankTotal - Mutates the private data member "displayBankTotal" with that of "playerParameters->bankTotal"
void Player::SetDisplayBankTotal() {
    playerParameters->displayBankTotal = color_text(33, round_to_string(this->GetBankTotal()));
}

// SetDisplayName - Mutates the private data member "displayName" with that of "playerParameters->name"
void Player::SetDisplayName() {
    if (this->GetName() != "Dealer") {
        playerParameters->displayName = color_text(random_int(32, 36), this->GetName());
    }
    else {
        playerParameters->displayName = color_text(31, this->GetName());
    }
}

// SetName - Mutates the private data member "name" with that of "input"
void Player::SetName(const std::string& input) {
    playerParameters->name = input;
    this->SetDisplayName();
}

// Getters
// GetBankTotal - Retrieves the private data member "bankTotal"
float& Player::GetBankTotal() {
    return playerParameters->bankTotal;
}

// GetBlackjackHands - Retrieves the private data member "blackjackHands"
int& Player::GetBlackjackHands() {
    return playerParameters->blackjackHands;
}

// GetCurrentHandsPossessed - Retrieves the private data member "currentHandsPossessed"
int& Player::GetCurrentHandsPossessed() {
    return playerParameters->currentHandsPossessed;
}

// GetHandsLost - Retrieves the private data member "handsLost"
int& Player::GetHandsLost() {
    return playerParameters->handsLost;
}

// GetHandsPlayed - Retrieves the private data member "handsPlayed"
int& Player::GetHandsPlayed() {
    return playerParameters->handsPlayed;
}

// GetHandsPushed - Retrieves the private data member "handsPushed"
int& Player::GetHandsPushed() {
    return playerParameters->handsPushed;
}

// GetHandsWon - Retrieves the private data member "handsWon"
int& Player::GetHandsWon() {
    return playerParameters->handsWon;
}

// GetCurrentHands - Retrieves the private data member "CurrentHands"
std::shared_ptr<LinkedList<std::shared_ptr<Hand>>>& Player::GetCurrentHands() {
    return playerParameters->CurrentHands;
}

// GetTotalHandBankTotals - Retrieves the private data member "HandBankTotals"
std::shared_ptr<LinkedList<float>>& Player::GetTotalHandBankTotals() {
    return playerParameters->HandBankTotals;
}

// GetTotalHandCardTotals - Retrieves the private data member "HandCardTotals"
std::shared_ptr<LinkedList<int>>& Player::GetTotalHandCardTotals() {
    return playerParameters->HandCardTotals;
}

// GetTotalHandNets - Retrieves the private data member "HandNets"
std::shared_ptr<LinkedList<float>>& Player::GetTotalHandNets() {
    return playerParameters->HandNets;
}

// GetTotalHandsPlayed - Retrieves the private data member "HandsPlayed"
std::shared_ptr<LinkedList<int>>& Player::GetTotalHandsPlayed() {
    return playerParameters->HandsPlayed;
}

// GetTotalHandWagers - Retrieves the private data member "HandWagers"
std::shared_ptr<LinkedList<float>>& Player::GetTotalHandWagers() {
    return playerParameters->HandWagers;
}

// GetDisplayBankTotal - Retrieves the private data member "displayBankTotal"
std::string& Player::GetDisplayBankTotal() {
    return playerParameters->displayBankTotal;
}

// GetDisplayName - Retrieves the private data member "displayName"
std::string& Player::GetDisplayName() {
    return playerParameters->displayName;
}

// GetName - Retrieves the private data member "name"
std::string& Player::GetName() {
    return playerParameters->name;
}