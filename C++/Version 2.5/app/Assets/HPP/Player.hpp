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
*       * Enter an error catching block that will help us determine if a player has entered a correct value for a bank total
*           * If the value entered is not a float, then we output an error message and clear the inputs
*           * If the value entered is a float or an integer
*               * We check to see if it is less than or equal to zero, if it is, we output an error message and require another input
*               * If it is greater than zero, then we set the private data member "bankTotal" to the "input" with SetBankTotal
*       * We then initialize some values for the statistics tracking of the player
*   Output:
*       This function returns a Hand object after depositing currency into a players bank
*/
Player Player::BankDepositPrompt() {
    float input;
    while (true) {
        // Prompt user for deposit
        std::cout << std::endl << "Please enter the amount you'd like to deposit into your bank: "; time_sleep(SHORT_TIME_SLEEP);
        std::cin >> input; time_sleep(SHORT_TIME_SLEEP);
        const std::type_info& result = typeid(input);
        std::string checkResult = result.name();
        // Check if value is not a float or integer
        if (checkResult != "f" && checkResult != "i") {
            std::cout << std::endl << color_text(31, "Invalid Response") << ". Please re-enter your submission." << std::endl; time_sleep(SHORT_TIME_SLEEP);
            clear_terminal();
            checkResult.clear();
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        // Check if value is a float or integer
        else if (checkResult == "f" || checkResult == "i") {
            if (input <= 0) {
                std::cout << std::endl << color_text(31, "Invalid Response") << " of " << color_text(31, std::to_string(round_input(input))) << ". Please re-enter a positive value." << std::endl; time_sleep(SHORT_TIME_SLEEP);
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
    std::cout << std::endl << this->GetDisplayName() << " has decided to start with: " << this->GetDisplayBankTotal() << std::endl; time_sleep(SHORT_TIME_SLEEP);
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
    std::cout << std::endl << "Please enter a name for your player: "; time_sleep(SHORT_TIME_SLEEP);
    std::getline(std::cin, input); time_sleep(SHORT_TIME_SLEEP);
    // Set the players name to "input"
    this->SetName(input);
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
    // Modify the string values
    std::string optionMod = color_text(34, option);
    std::string handTotalMod = color_text(36, "Hand Total");
    // The player is not the dealer
    if (this->GetName() != "Dealer") {
        this->SetBankTotal(this->GetBankTotal());
        // Modify more string values
        std::string handWager = color_text(32, "Hand Wager");
        std::string bankTotal = color_text(33, "Bank Total");
        std::cout << this->GetDisplayName() << "'s " << optionMod << " hand: [";
        // Iterate through the cards in players hand
        for (int i = 0; i < inputHand->GetPlayerCards()->GetSize(); i++) {
            if (i == inputHand->GetPlayerCards()->GetSize() - 1) {
                std::cout << inputHand->GetPlayerCards()->RetrieveNode(i)->data << "] ";
            }
            else {
                std::cout << inputHand->GetPlayerCards()->RetrieveNode(i)->data << " , ";
            }
        }
        // Add hand total and display players hand parameters
        inputHand->AddHandTotal();
        std::cout << handTotalMod << ": " << inputHand->GetDisplayCardsTotal() << " , " << handWager << ": " << inputHand->GetDisplayWager() << " , " << bankTotal << ": " << this->GetDisplayBankTotal() << std::endl; time_sleep(SHORT_TIME_SLEEP);
    }
    // The player is the dealer
    else if (this->GetName() == "Dealer") {
        // Dealer is hiding a card
        if (dealerShow.empty()) {
            std::string backCardMod = color_text(36, std::to_string(inputHand->GetPlayerCards()->RetrieveNode(-1)->data.GetCardValue()));
            std::cout << this->GetDisplayName() << "'s " << optionMod << " hand : [Hidden, " << inputHand->GetPlayerCards()->RetrieveNode(-1)->data << "] " << handTotalMod << ": " << backCardMod << std::endl; time_sleep(SHORT_TIME_SLEEP);
        }
        // Dealer is showing both cards
        else {
            if (dealerShow != "cards") {
                std::cout << this->GetDisplayName() << "'s " << optionMod << " hand: [";
            }
            // Specialized display of cards
            else {
                std::cout << "[";
            }
            // Iterate through the cards in dealers hand
            for (int i = 0; i < inputHand->GetPlayerCards()->GetSize(); i++) {
                if (i == inputHand->GetPlayerCards()->GetSize() - 1) {
                    std::cout << inputHand->GetPlayerCards()->RetrieveNode(i)->data << "] ";
                }
                else {
                    std::cout << inputHand->GetPlayerCards()->RetrieveNode(i)->data << " , ";
                }
            }
            // Add hand total and display players hand parameters
            inputHand->AddHandTotal();
            std::cout << handTotalMod << ": " << inputHand->GetDisplayCardsTotal() << std::endl; time_sleep(SHORT_TIME_SLEEP);
        }
    }
    return *this;
}

/*  UpdateBank - Updates the bank of a player
*   Input:
*       inputHand - Hand object that is passed by reference
*       choice - Constant integer that is supposed to represent the outcome of a hand
*   Algorithm:
*       * Grab the prior bank value with "prior_bank"
*       * The following codes represent what the choices mean
*           * 0 - Player withdraws money from bank (placing wager)
*           * 1 - Player wins hand
*           * 2 - Player loses hand
*           * 3 - Player pushes hand
*           * 4 - Player wins blackjack
*           * 5 - Player wins insurance
*           * 6 - Player loses insurance
*   Output:
*       This function returns a Hand object after updating the players bank
*/
Player Player::UpdateBank(std::shared_ptr<Hand>& inputHand, const int choice) {
    float prior_bank = this->GetBankTotal();
    // Only necessary if a player previously won insurance bet
    float insurance_net = inputHand->GetNet();
    switch (choice) {
    // 0 - Player withdraws money from bank (places wager)
    case 0:
        this->SetBankTotal(prior_bank - inputHand->GetWager());
        return *this;
    // 1 - Player wins hand
    case 1:
        // Update hands won and hands played
        this->SetHandsWon();
        this->SetHandsPlayed();
        // Player loses insurance, update net and bank
        if (insurance_net < 0) {
            inputHand->SetNet(inputHand->GetWager() + insurance_net);
            this->SetBankTotal(prior_bank + 2 * inputHand->GetWager());
        }
        // Player did not place insurance, update net and bank
        else {
            inputHand->SetNet(inputHand->GetWager());
            this->SetBankTotal(prior_bank + 2 * inputHand->GetWager());
        }
        // Update lists
        this->SetTotalHandsPlayed(this->GetHandsPlayed());
        this->SetTotalHandNets(inputHand->GetNet());
        this->SetTotalHandBankTotals(this->GetBankTotal());
        return *this;
    // 2 - Player loses hand
    case 2:
        // Update hands lost and hands played
        this->SetHandsLost();
        this->SetHandsPlayed();
        // Player has won insurance, update net and bank
        if (insurance_net > 0) {
            inputHand->SetNet(0);
            this->SetBankTotal(prior_bank);
        }
        // Player did not place insurance or has lost insurance, update net and bank
        else {
            inputHand->SetNet(insurance_net - inputHand->GetWager());
            this->SetBankTotal(prior_bank);
        }
        this->SetTotalHandsPlayed(this->GetHandsPlayed());
        this->SetTotalHandNets(inputHand->GetNet());
        this->SetTotalHandBankTotals(this->GetBankTotal());
        return *this;
    // 3 - Player pushes hand
    case 3:
        // Update hands pushed and hands played
        this->SetHandsPushed();
        this->SetHandsPlayed();
        // Player has won insurance, update net and bank
        if (insurance_net > 0) {
            inputHand->SetNet(inputHand->GetWager());
            this->SetBankTotal(prior_bank + inputHand->GetWager());
        }
        // Player did not place insurance or has lost insurance, update net and bank
        else {
            inputHand->SetNet(insurance_net);
            this->SetBankTotal(prior_bank + inputHand->GetWager());
        }
        this->SetTotalHandsPlayed(this->GetHandsPlayed());
        this->SetTotalHandNets(inputHand->GetNet());
        this->SetTotalHandBankTotals(this->GetBankTotal());
        return *this;
    // 4 - Player wins blackjack
    case 4:
        this->SetBlackjackHands();
        this->SetHandsPlayed();
        // Player loses insurance, update net and bank
        if (insurance_net < 0) {
            inputHand->SetNet(0);
            this->SetBankTotal(prior_bank + 1.5 * inputHand->GetWager());
        }
        // Player did not place insurance, update net and bank
        else {
            inputHand->SetNet(1.5 * inputHand->GetWager());
            this->SetBankTotal(prior_bank + 2.5 * inputHand->GetWager());
        }
        this->SetTotalHandsPlayed(this->GetHandsPlayed());
        this->SetTotalHandNets(inputHand->GetNet());
        this->SetTotalHandBankTotals(this->GetBankTotal());
        return *this;
    // 5 - Player wins insurance
    case 5:
        // Update net and bank
        inputHand->SetNet(3 * inputHand->GetInsuranceWager());
        this->SetBankTotal(prior_bank + (3 * inputHand->GetInsuranceWager()));
        return *this;
    // 6 - Player loses insurance
    case 6:
        // Update net and bank
        inputHand->SetNet(-inputHand->GetInsuranceWager());
        this->SetBankTotal(prior_bank);
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