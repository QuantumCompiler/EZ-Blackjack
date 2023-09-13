// ----- ----- ----- ----- ----- ----- ----- Includes ----- ----- ----- ----- ----- ----- ----- ----- ----- //
#include "../Headers/Core.h"

/*  blackjack_check - Checks to see if the dealer is showing an Ace and if a player has blackjack or not
*   Input:
*       humanPlayer - Player object that is passed by reference to resemble a non dealer player
*       dealer - Player object that is passed by reference to resemble a dealer
*       inputShoe - Shoe object passed by reference that represents the shoe that is being played with
*   Algorithm:
*       * Deal hands to the players with the "deal_hand" function
*       * Proceed to check if the player is able to buy insurance (This is done with the "ParametersCheck" function in "deal_hand")
*       * For each instance, we check if the following is true:
*           * If both players have blackjack, if this is true, payout insurance bets if placed, otherwise just push bets
*           * If dealer has blackjack and player does not, payout insurance bets if placed, otherwise just take bets
*           * If dealer does not have blackjack and player does, take insurance bet, and payout blackjack to player
*           * If neither player has blackjack, take insurance bet if placed, continue hand
*       * In each instance above, we output messages that pertain to each instance and update the player bank accordingly
*       * Return values at the end of the if else statements
*   Output:
*/
bool blackjack_check(std::shared_ptr<Player>& humanPlayer, std::shared_ptr<Player>& dealer, std::shared_ptr<Shoe>& inputShoe) {
    // Deal hands to player
    deal_hand(humanPlayer, dealer, inputShoe);
    // Define boolean values
    bool player_can_buy_insurance = humanPlayer->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(humanPlayer->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[0][0]);
    bool dealer_has_blackjack = dealer->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(dealer->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[2][1]);
    bool player_has_blackjack = humanPlayer->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(humanPlayer->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[2][1]);
    // Player can buy insurance
    if (player_can_buy_insurance) {
        // Tell user that the dealer is showing an Ace and ask them if they would like to buy insurance
        humanPlayer->GetCurrentHands()->RetrieveNode(0)->data->InsurancePrompt(humanPlayer->GetBankTotal(), humanPlayer->GetDisplayName());
        bool player_bought_insurance = humanPlayer->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(humanPlayer->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[0][4]);
        // Both players have blackjack, hand ends
        if (dealer_has_blackjack && player_has_blackjack) {
            if (player_bought_insurance) {
                std::cout << std::endl; rolling_text("Both players have blackjack. " + humanPlayer->GetDisplayName() + " wins insurance and pushes their original wager.", PRINT_LINE_SLEEP); std::cout << std::endl;
                humanPlayer->UpdateBank(humanPlayer->GetCurrentHands()->RetrieveNode(0)->data, 8);
            }
            else {
                std::cout << std::endl; rolling_text("Both players have blackjack. " + humanPlayer->GetDisplayName() + " pushes their original wager.", PRINT_LINE_SLEEP); std::cout << std::endl;
                humanPlayer->UpdateBank(humanPlayer->GetCurrentHands()->RetrieveNode(0)->data, 3);
            }
            std::cout << std::endl; rolling_text("Here are the final hands of the players:", PRINT_LINE_SLEEP); std::cout << std::endl;
            humanPlayer->ShowCurrentHand(humanPlayer->GetCurrentHands()->RetrieveNode(0)->data, "Final", "");
            dealer->ShowCurrentHand(dealer->GetCurrentHands()->RetrieveNode(0)->data, "Final", "Show");
            // Stat tracker
            std::string statTracker = color_text(36, "Hands Played: " + std::to_string(humanPlayer->GetHandsPlayed())) + " , " + color_text(32, "Hands Won: " + std::to_string(humanPlayer->GetHandsWon())) + " , " + color_text(31, "Hands Lost: " 
            + std::to_string(humanPlayer->GetHandsLost())) + " , " + color_text(33, "Hands Pushed: " + std::to_string(humanPlayer->GetHandsPushed())) + " , " + color_text(35, "Blackjacks: " + std::to_string(humanPlayer->GetBlackjackHands())) + ".";
            std::cout << std::endl; rolling_text(humanPlayer->GetDisplayName() + " has pushed this hand. " + statTracker, PRINT_LINE_SLEEP); std::cout << std::endl;
            return false;
        }
        // Dealer has blackjack, player does not, hand ends
        else if (dealer_has_blackjack && !player_has_blackjack) {
            if (player_bought_insurance) {
                std::cout << std::endl; rolling_text(dealer->GetDisplayName() + " has blackjack and " + humanPlayer->GetDisplayName() + " does not. " + humanPlayer->GetDisplayName() + " wins insurance and loses their original wager.", PRINT_LINE_SLEEP); std::cout << std::endl;
                humanPlayer->UpdateBank(humanPlayer->GetCurrentHands()->RetrieveNode(0)->data, 6);
            }
            else {
                std::cout << std::endl; rolling_text(dealer->GetDisplayName() + " has blackjack and " + humanPlayer->GetDisplayName() + " does not. " + humanPlayer->GetDisplayName() + " loses their original wager.", PRINT_LINE_SLEEP); std::cout << std::endl;
                humanPlayer->UpdateBank(humanPlayer->GetCurrentHands()->RetrieveNode(0)->data, 2);
            }
            std::cout << std::endl; rolling_text("Here are the final hands of the players:", PRINT_LINE_SLEEP); std::cout << std::endl;
            humanPlayer->ShowCurrentHand(humanPlayer->GetCurrentHands()->RetrieveNode(0)->data, "Final", "");
            dealer->ShowCurrentHand(dealer->GetCurrentHands()->RetrieveNode(0)->data, "Final", "Show");
            // Stat tracker
            std::string statTracker = color_text(36, "Hands Played: " + std::to_string(humanPlayer->GetHandsPlayed())) + " , " + color_text(32, "Hands Won: " + std::to_string(humanPlayer->GetHandsWon())) + " , " + color_text(31, "Hands Lost: " 
            + std::to_string(humanPlayer->GetHandsLost())) + " , " + color_text(33, "Hands Pushed: " + std::to_string(humanPlayer->GetHandsPushed())) + " , " + color_text(35, "Blackjacks: " + std::to_string(humanPlayer->GetBlackjackHands())) + ".";
            std::cout << std::endl; rolling_text(humanPlayer->GetDisplayName() + " has lost this hand. " + statTracker, PRINT_LINE_SLEEP); std::cout << std::endl;
            return false;
        }
        // Dealer does not have blackjack, player does, hand ends
        else if (!dealer_has_blackjack && player_has_blackjack) {
            if (player_bought_insurance) {
                std::cout << std::endl; rolling_text(humanPlayer->GetDisplayName() + " has blackjack and " + dealer->GetDisplayName() + " does not. " + humanPlayer->GetDisplayName() + " loses insurance and wins their original wager.", PRINT_LINE_SLEEP); std::cout << std::endl;
                humanPlayer->UpdateBank(humanPlayer->GetCurrentHands()->RetrieveNode(0)->data, 9);
            }
            else {
                std::cout << std::endl; rolling_text(humanPlayer->GetDisplayName() + " has blackjack and " + dealer->GetDisplayName() + " does not. " + humanPlayer->GetDisplayName() + " wins their original wager.", PRINT_LINE_SLEEP); std::cout << std::endl;
                humanPlayer->UpdateBank(humanPlayer->GetCurrentHands()->RetrieveNode(0)->data, 4);
            }
            std::cout << std::endl; rolling_text("Here are the final hands of the players:", PRINT_LINE_SLEEP); std::cout << std::endl;
            humanPlayer->ShowCurrentHand(humanPlayer->GetCurrentHands()->RetrieveNode(0)->data, "Final", "");
            dealer->ShowCurrentHand(dealer->GetCurrentHands()->RetrieveNode(0)->data, "Final", "Show");
            // Stat tracker
            std::string statTracker = color_text(36, "Hands Played: " + std::to_string(humanPlayer->GetHandsPlayed())) + " , " + color_text(32, "Hands Won: " + std::to_string(humanPlayer->GetHandsWon())) + " , " + color_text(31, "Hands Lost: " 
            + std::to_string(humanPlayer->GetHandsLost())) + " , " + color_text(33, "Hands Pushed: " + std::to_string(humanPlayer->GetHandsPushed())) + " , " + color_text(35, "Blackjacks: " + std::to_string(humanPlayer->GetBlackjackHands())) + ".";
            std::cout << std::endl; rolling_text(humanPlayer->GetDisplayName() + " has won this hand. " + statTracker, PRINT_LINE_SLEEP); std::cout << std::endl;
            return false;
        }
        // Neither player has blackjack, hand continues
        else {
            if (player_bought_insurance) {
                std::cout << std::endl; rolling_text("Neither player has blackjack. " + humanPlayer->GetDisplayName() + " loses insurance.", PRINT_LINE_SLEEP); std::cout << std::endl;
            }
            else {
                std::cout << std::endl; rolling_text("Neither player has blackjack.", PRINT_LINE_SLEEP); std::cout << std::endl;
            }
            return true;
        }
    }
    // Player is not able to buy insurance
    else {
        // Dealer is showing an Ace but the player does not have enough currency to buy insurance
        if (dealer->GetCurrentHands()->RetrieveNode(0)->data->GetPlayerCards()->RetrieveNode(-1)->data.CheckCardParam(dealer->GetCurrentHands()->RetrieveNode(0)->data->GetPlayerCards()->RetrieveNode(-1)->data.GetRank(), Ranks[0])) {
            std::cout << std::endl; rolling_text("The " + dealer->GetDisplayName() + " is showing an Ace but " + humanPlayer->GetDisplayName() + " does not have enough currency to purchase insurance.", PRINT_LINE_SLEEP); std::cout << std::endl;
        }
        // Both players have blackjack, hand ends
        if (dealer_has_blackjack && player_has_blackjack) {
            std::cout << std::endl; rolling_text("Both players have blackjack. " + humanPlayer->GetDisplayName() + " pushes their original wager.", PRINT_LINE_SLEEP); std::cout << std::endl;
            humanPlayer->UpdateBank(humanPlayer->GetCurrentHands()->RetrieveNode(0)->data, 3);
            std::cout << std::endl; rolling_text("Here are the final hands of the players:", PRINT_LINE_SLEEP); std::cout << std::endl;
            humanPlayer->ShowCurrentHand(humanPlayer->GetCurrentHands()->RetrieveNode(0)->data, "Final", "");
            dealer->ShowCurrentHand(dealer->GetCurrentHands()->RetrieveNode(0)->data, "Final", "Show");
            // Stat tracker
            std::string statTracker = color_text(36, "Hands Played: " + std::to_string(humanPlayer->GetHandsPlayed())) + " , " + color_text(32, "Hands Won: " + std::to_string(humanPlayer->GetHandsWon())) + " , " + color_text(31, "Hands Lost: " 
            + std::to_string(humanPlayer->GetHandsLost())) + " , " + color_text(33, "Hands Pushed: " + std::to_string(humanPlayer->GetHandsPushed())) + " , " + color_text(35, "Blackjacks: " + std::to_string(humanPlayer->GetBlackjackHands())) + ".";
            std::cout << std::endl; rolling_text(humanPlayer->GetDisplayName() + " has pushed this hand. " + statTracker, PRINT_LINE_SLEEP); std::cout << std::endl;
            return false;
        }
        // Dealer has blackjack, player does not, hand ends
        else if (dealer_has_blackjack && !player_has_blackjack) {
            std::cout << std::endl; rolling_text(dealer->GetDisplayName() + " has blackjack and " + humanPlayer->GetDisplayName() + " does not. " + humanPlayer->GetDisplayName() + " loses their original wager.", PRINT_LINE_SLEEP); std::cout << std::endl;
            humanPlayer->UpdateBank(humanPlayer->GetCurrentHands()->RetrieveNode(0)->data, 2);
            std::cout << std::endl; rolling_text("Here are the final hands of the players:", PRINT_LINE_SLEEP); std::cout << std::endl;
            humanPlayer->ShowCurrentHand(humanPlayer->GetCurrentHands()->RetrieveNode(0)->data, "Final", "");
            dealer->ShowCurrentHand(dealer->GetCurrentHands()->RetrieveNode(0)->data, "Final", "Show");
            // Stat tracker
            std::string statTracker = color_text(36, "Hands Played: " + std::to_string(humanPlayer->GetHandsPlayed())) + " , " + color_text(32, "Hands Won: " + std::to_string(humanPlayer->GetHandsWon())) + " , " + color_text(31, "Hands Lost: " 
            + std::to_string(humanPlayer->GetHandsLost())) + " , " + color_text(33, "Hands Pushed: " + std::to_string(humanPlayer->GetHandsPushed())) + " , " + color_text(35, "Blackjacks: " + std::to_string(humanPlayer->GetBlackjackHands())) + ".";
            std::cout << std::endl; rolling_text(humanPlayer->GetDisplayName() + " has lost this hand. " + statTracker, PRINT_LINE_SLEEP); std::cout << std::endl;
            return false;
        }
        // Dealer does not have blackjack, player does, hand ends
        else if (!dealer_has_blackjack && player_has_blackjack) {
            std::cout << std::endl; rolling_text(humanPlayer->GetDisplayName() + " has blackjack and " + dealer->GetDisplayName() + " does not. " + humanPlayer->GetDisplayName() + " wins their original wager.", PRINT_LINE_SLEEP); std::cout << std::endl;
            humanPlayer->UpdateBank(humanPlayer->GetCurrentHands()->RetrieveNode(0)->data, 4);
            std::cout << std::endl; rolling_text("Here are the final hands of the players:", PRINT_LINE_SLEEP); std::cout << std::endl;
            humanPlayer->ShowCurrentHand(humanPlayer->GetCurrentHands()->RetrieveNode(0)->data, "Final", "");
            dealer->ShowCurrentHand(dealer->GetCurrentHands()->RetrieveNode(0)->data, "Final", "Show");
            // Stat tracker
            std::string statTracker = color_text(36, "Hands Played: " + std::to_string(humanPlayer->GetHandsPlayed())) + " , " + color_text(32, "Hands Won: " + std::to_string(humanPlayer->GetHandsWon())) + " , " + color_text(31, "Hands Lost: " 
            + std::to_string(humanPlayer->GetHandsLost())) + " , " + color_text(33, "Hands Pushed: " + std::to_string(humanPlayer->GetHandsPushed())) + " , " + color_text(35, "Blackjacks: " + std::to_string(humanPlayer->GetBlackjackHands())) + ".";
            std::cout << std::endl; rolling_text(humanPlayer->GetDisplayName() + " has won this hand. " + statTracker, PRINT_LINE_SLEEP); std::cout << std::endl;
            return false;
        }
        // Neither player has blackjack, hand continues
        else {
            return true;
        }
    }
}

/*  blackjack_check_sim - Checks to see if the dealer is showing an Ace and if a player has blackjack or not for a simulated hand
*   Input:
*       playerHand - Hand object passed by reference that represents the user's hand
*       dealerHand - Hand object passed by reference that represents the dealer's hand
*       inputShoe - Shoe object passed by reference that represents the shoe that is being played with
*       playerWager - Float value that represents the player wager that is to be placed
*       buyInsurance - Boolean value that represents if insurance is to be purchased if possible
*   Algorithm:
*       * Deal hands to the players with the "deal_hand_sim" function
*   Output:
*       hand_continue - Boolean value that represents if a hand is to be continued
*/
bool blackjack_check_sim(std::shared_ptr<Player>& humanPlayer, std::shared_ptr<Player>& dealer, std::shared_ptr<Shoe>& inputShoe, const float playerWager, const bool buyInsurance) {
    // Deal hands to player
    deal_hand_sim(humanPlayer, dealer, inputShoe, playerWager);
    // Define "hand_continue" boolean value to true
    bool hand_continue = true;
    // Define other boolean value
    bool player_can_buy_insurance = humanPlayer->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(humanPlayer->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[0][0]);
    bool dealer_has_blackjack = dealer->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(dealer->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[2][1]);
    bool player_has_blackjack = humanPlayer->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(humanPlayer->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[2][1]);
    bool player_bought_insurance = humanPlayer->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(humanPlayer->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[0][4]);
    // Player can buy insurance
    if (player_can_buy_insurance) {
        humanPlayer->GetCurrentHands()->RetrieveNode(0)->data->InsuranceSim(humanPlayer->GetBankTotal(), buyInsurance);
        player_bought_insurance = humanPlayer->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(humanPlayer->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[0][4]);
        // Both players have blackjack, hand ends
        if (dealer_has_blackjack && player_has_blackjack) { 
            // Player bought insurance
            if (player_bought_insurance) {
                humanPlayer->UpdateBank(humanPlayer->GetCurrentHands()->RetrieveNode(0)->data, 8);
            }
            // Player did not buy insurance
            else {
                humanPlayer->UpdateBank(humanPlayer->GetCurrentHands()->RetrieveNode(0)->data, 3);
            }
            // Hand continue false
            hand_continue = false;
        }
        // Dealer has blackjack, player does not, hand ends
        else if (dealer_has_blackjack && !player_has_blackjack) {
            // Player bought insurance
            if (player_bought_insurance) {
                humanPlayer->UpdateBank(humanPlayer->GetCurrentHands()->RetrieveNode(0)->data, 6);
            // Player did not buy insurance
            }
            else {
                humanPlayer->UpdateBank(humanPlayer->GetCurrentHands()->RetrieveNode(0)->data, 2);
            }
            hand_continue = false;
        }
        // Dealer does not have blackjack, player does, hand ends
        else if (!dealer_has_blackjack && player_has_blackjack) {
            // Player bought insurance
            if (player_bought_insurance) {
                humanPlayer->UpdateBank(humanPlayer->GetCurrentHands()->RetrieveNode(0)->data, 9);
            }
            // Player did not buy insurance
            else {
                humanPlayer->UpdateBank(humanPlayer->GetCurrentHands()->RetrieveNode(0)->data, 4);
            }
            hand_continue = false;
        }
        // Neither player has blackjack, hand continues
        else {
            hand_continue = true;
        }
    }
    // Player is not able to buy insurance
    else {
        // Both players have blackjack, hand ends
        if (dealer_has_blackjack && player_has_blackjack) {
            humanPlayer->UpdateBank(humanPlayer->GetCurrentHands()->RetrieveNode(0)->data, 3);
            hand_continue = false;
        }
        // Dealer has blackjack, player does not, hand ends
        else if (dealer_has_blackjack && !player_has_blackjack) {
            humanPlayer->UpdateBank(humanPlayer->GetCurrentHands()->RetrieveNode(0)->data, 2);
            hand_continue = false;
        }
        // Dealer does not have blackjack, player does, hand ends
        else if (!dealer_has_blackjack && player_has_blackjack) {
            humanPlayer->UpdateBank(humanPlayer->GetCurrentHands()->RetrieveNode(0)->data, 4);
            hand_continue = false;
        }
        // Neither player has blackjack, hand continues
        else {
            hand_continue = true;
        }
    }
    return hand_continue;
}

/*  blackjack_strategy - Provides a strategy for players on what is the best way to play a given hand in blackjack
*   Input:
*       humanPlayer - Player object that is passed by reference that represents a non dealer player
*       playerHand - Hand object that represents the specific hand that is to be examined for the player
*       dealer - Player object that represents the dealer of the game that hands are to be checked against
*       showStrategy - Boolean value that represents if a the blackjack strategy is to be shown
*       splitOverride - Boolean value that represents if the split check is to be overriden
*   Algorithm:
*       * Check the parameters of the hand "playerHand"
*       * Check if the player has a an Ace in their hand and if they have duplicate ranks in their hand
*       * Create template `should' statements that are output to terminal for certain conditions
*       * Process the logical steps for the following three scenarios:
*           * Player has duplicate ranks in their hand, is able to split, and has not spoken on whether they want to split ye
*           * Player is dealt and Ace and currently has two cards
*           * Any other scenario that doesn't match the above two
*   Output:
*       This function does not output any values, in modifies specific boolean values of "playerHand" and outputs a message to terminal
*/
void blackjack_strategy(std::shared_ptr<Player>& humanPlayer, std::shared_ptr<Hand>& playerHand, std::shared_ptr<Player>& dealer, bool showStrategy, bool splitOverride) { 
    // Remove "paramInHand" if present
    if (playerHand->GetHashTable()->Contains(playerHand->GetValuesMatrix()[2][3])) {
        playerHand->GetHashTable()->RemoveElement(playerHand->GetValuesMatrix()[2][3]);
    }
    // Remove "sameParamInHand" if present
    if (playerHand->GetHashTable()->Contains(playerHand->GetValuesMatrix()[2][4])) {
        playerHand->GetHashTable()->RemoveElement(playerHand->GetValuesMatrix()[2][4]);
    }
    // Check the parameters of the player
    playerHand->ParametersCheck(dealer->GetCurrentHands()->RetrieveNode(0)->data, humanPlayer->GetBankTotal());
    // Check if "playerHand" has the same rank or if they have an Ace in their hand
    playerHand->CheckParamInHand("R", Ranks[0]);
    playerHand->CheckSameParamInHand("R");
    // Player `should' statements
    std::string should_double_down = "Blackjack strategy suggests that " + humanPlayer->GetDisplayName() + " should " + color_text(31, "double down") + ".";
    std::string should_double_down_or_hit = "Blackjack strategy suggests that " + humanPlayer->GetDisplayName() + " should " + color_text(31, "hit") + " or " + color_text(31, "double down") + ".";
    std::string should_double_down_or_stand = "Blackjack strategy suggests that " + humanPlayer->GetDisplayName() + " should " + color_text(31, "stand") + " or " + color_text(31, "double down") + ".";
    std::string should_hit = "Blackjack strategy suggests that " + humanPlayer->GetDisplayName() + " should " + color_text(31, "hit") + ".";
    std::string should_split = "Blackjack strategy suggests that " + humanPlayer->GetDisplayName() + " should " + color_text(31, "split") + ".";
    std::string should_split_or_hit = "Blackjack strategy suggests that " + humanPlayer->GetDisplayName() + " should " + color_text(31, "hit") + " or " + color_text(31, "split") + ".";
    std::string should_stand = "Blackjack strategy suggests that " + humanPlayer->GetDisplayName() + " should " + color_text(31, "stand") + ".";
    // Logic for if a player is dealt the same rank and only two cards are in the hand with them having not decided if they want to split or not
    if (((playerHand->GetHashTable()->Contains(playerHand->GetValuesMatrix()[0][3]) && !playerHand->GetHashTable()->Contains(playerHand->GetValuesMatrix()[4][1])) 
        || (playerHand->GetHashTable()->Contains(playerHand->GetValuesMatrix()[0][2]) && !playerHand->GetHashTable()->Contains(playerHand->GetValuesMatrix()[4][0]))) 
        && playerHand->GetPlayerCards()->GetSize() == 2 && !splitOverride && humanPlayer->GetCurrentHands()->GetSize() < 5) {
        // Check value of players cards
        switch (playerHand->GetCardsTotal()) {
            // Player card total is 4 (two, two) or 6 (three, three)
            case 4:
            case 6:
                // Checking the value of the card that is face up of the dealer
                switch (dealer->GetCurrentHands()->RetrieveNode(0)->data->GetPlayerCards()->RetrieveNode(-1)->data.GetCardValue()) {
                    // Dealer is showing a two or three
                    case 2:
                    case 3:
                        // Player should split or hit
                        playerHand->GetHashTable()->AddToTable(playerHand->GetValuesMatrix()[3][1]);
                        playerHand->GetHashTable()->AddToTable(playerHand->GetValuesMatrix()[3][2]);
                        if (showStrategy) {
                            std::cout << std::endl; rolling_text(should_split_or_hit, PRINT_LINE_SLEEP); std::cout << std::endl;
                        }
                        break;
                    // Dealer is showing a 4, 5, 6 or 7
                    case 4:
                    case 5:
                    case 6:
                    case 7:
                        // Player should split
                        playerHand->GetHashTable()->AddToTable(playerHand->GetValuesMatrix()[3][2]);
                        if (showStrategy) {
                            std::cout << std::endl; rolling_text(should_split, PRINT_LINE_SLEEP); std::cout << std::endl;
                        }
                        break;
                    case 8:
                    case 9:
                    case 10:
                    case 1:
                    case 11:
                        // Player should hit
                        playerHand->GetHashTable()->AddToTable(playerHand->GetValuesMatrix()[3][1]);
                        if (showStrategy) {
                            std::cout << std::endl; rolling_text(should_hit, PRINT_LINE_SLEEP); std::cout << std::endl;
                        }
                        break;
                    default:
                        break;
                }
                break;
            // Player card total is 8 (four, four)
            case 8:
                // Checking the value of the card that is face up of the dealer
                switch (dealer->GetCurrentHands()->RetrieveNode(0)->data->GetPlayerCards()->RetrieveNode(-1)->data.GetCardValue()) {
                    // Dealer is showing a 5 or 6
                    case 5:
                    case 6:
                        // Player should split or hit
                        playerHand->GetHashTable()->AddToTable(playerHand->GetValuesMatrix()[3][1]);
                        playerHand->GetHashTable()->AddToTable(playerHand->GetValuesMatrix()[3][2]);
                        if (showStrategy) {
                            std::cout << std::endl; rolling_text(should_split_or_hit, PRINT_LINE_SLEEP); std::cout << std::endl;
                        }
                        break;
                    case 2:
                    case 3:
                    case 4:
                    case 7:
                    case 8:
                    case 9:
                    case 10:
                    case 1:
                    case 11:
                        // Player should hit
                        playerHand->GetHashTable()->AddToTable(playerHand->GetValuesMatrix()[3][1]);
                        if (showStrategy) {
                            std::cout << std::endl; rolling_text(should_hit, PRINT_LINE_SLEEP); std::cout << std::endl;
                        }
                        break;
                    default:
                        break;
                }
                break;
            // Player card total is 10 (five, five)
            case 10:
                // Checking the value of the card that is face up of the dealer
                switch (dealer->GetCurrentHands()->RetrieveNode(0)->data->GetPlayerCards()->RetrieveNode(-1)->data.GetCardValue()) {
                    // Dealer is showing a Face or an Ace
                    case 10:
                    case 1:
                    case 11:
                        // Player should hit
                        playerHand->GetHashTable()->AddToTable(playerHand->GetValuesMatrix()[3][1]);
                        if (showStrategy) {
                            std::cout << std::endl; rolling_text(should_hit, PRINT_LINE_SLEEP); std::cout << std::endl;
                        }
                        break;
                    // Otherwise
                    case 2:
                    case 3:
                    case 4:
                    case 5:
                    case 6:
                    case 7:
                    case 8:
                    case 9:
                        // Player can double down
                        if (playerHand->GetHashTable()->Contains(playerHand->GetValuesMatrix()[0][1])) {
                            playerHand->GetHashTable()->AddToTable(playerHand->GetValuesMatrix()[3][0]);
                            playerHand->GetHashTable()->AddToTable(playerHand->GetValuesMatrix()[3][1]);
                            if (showStrategy) {
                                std::cout << std::endl; rolling_text(should_double_down_or_hit, PRINT_LINE_SLEEP); std::cout << std::endl;
                            }
                        }
                        // Player cannot double down
                        else {
                            playerHand->GetHashTable()->AddToTable(playerHand->GetValuesMatrix()[3][1]);
                            if (showStrategy) {
                                std::cout << std::endl; rolling_text(should_hit, PRINT_LINE_SLEEP); std::cout << std::endl;
                            }
                        }
                        break;
                    default:
                        break;
                }
                break;
            // Player card total is 12 (six, six || Ace, Ace) 
            case 12:
                // Player has Aces
                if (playerHand->GetHashTable()->Contains(playerHand->GetValuesMatrix()[2][3])) {
                    // Checking the value of the card that is face up of the dealer
                    switch (dealer->GetCurrentHands()->RetrieveNode(0)->data->GetPlayerCards()->RetrieveNode(-1)->data.GetCardValue()) {
                        // Dealer is showing any card
                        case 2:
                        case 3:
                        case 4:
                        case 5:
                        case 6:
                        case 7:
                        case 8:
                        case 9:
                        case 10:
                        case 1:
                        case 11:
                            // Player should split
                            playerHand->GetHashTable()->AddToTable(playerHand->GetValuesMatrix()[3][2]);
                            if (showStrategy) {
                                std::cout << std::endl; rolling_text(should_split, PRINT_LINE_SLEEP); std::cout << std::endl;
                            }
                            break;
                        default:
                            break;
                    }
                }
                // Player has sixes
                else {
                    // Checking the value of the card that is face up of the dealer
                    switch (dealer->GetCurrentHands()->RetrieveNode(0)->data->GetPlayerCards()->RetrieveNode(-1)->data.GetCardValue()) {
                        // Dealer is showing a 7
                        case 7:
                            // Player should split or hit
                            playerHand->GetHashTable()->AddToTable(playerHand->GetValuesMatrix()[3][1]);
                            playerHand->GetHashTable()->AddToTable(playerHand->GetValuesMatrix()[3][2]);
                            if (showStrategy) {
                                std::cout << std::endl; rolling_text(should_split_or_hit, PRINT_LINE_SLEEP); std::cout << std::endl;
                            }
                            break;
                        case 2:
                        case 3:
                        case 4:
                        case 5:
                        case 6:
                            // Player should split
                            playerHand->GetHashTable()->AddToTable(playerHand->GetValuesMatrix()[3][2]);
                            if (showStrategy) {
                                std::cout << std::endl; rolling_text(should_split, PRINT_LINE_SLEEP); std::cout << std::endl;
                            }
                            break;
                        case 8:
                        case 9:
                        case 10:
                        case 1:
                        case 11:
                            // Player should hit
                            playerHand->GetHashTable()->AddToTable(playerHand->GetValuesMatrix()[3][1]);
                            if (showStrategy) {
                                std::cout << std::endl; rolling_text(should_hit, PRINT_LINE_SLEEP); std::cout << std::endl;
                            }
                            break;
                        default:
                            break;
                    }
                }
                break;
            // Player has a 14
            case 14:
                // Checking the value of the card that is face up of the dealer
                switch (dealer->GetCurrentHands()->RetrieveNode(0)->data->GetPlayerCards()->RetrieveNode(-1)->data.GetCardValue()) {
                    // Dealer is showing an 8
                    case 8:
                        // Player should split or hit
                        playerHand->GetHashTable()->AddToTable(playerHand->GetValuesMatrix()[3][1]);
                        playerHand->GetHashTable()->AddToTable(playerHand->GetValuesMatrix()[3][2]);
                        if (showStrategy) {
                            std::cout << std::endl; rolling_text(should_split_or_hit, PRINT_LINE_SLEEP); std::cout << std::endl;
                        }
                        break;
                    // Dealer is showing a 2 - 7
                    case 2:
                    case 3:
                    case 4:
                    case 5:
                    case 6:
                    case 7:
                        // Player should split
                        playerHand->GetHashTable()->AddToTable(playerHand->GetValuesMatrix()[3][2]);
                        if (showStrategy) {
                            std::cout << std::endl; rolling_text(should_split, PRINT_LINE_SLEEP); std::cout << std::endl;
                        }
                        break;
                    // Otherwise
                    case 9:
                    case 10:
                    case 1:
                    case 11:
                        // Player should hit
                        playerHand->GetHashTable()->AddToTable(playerHand->GetValuesMatrix()[3][1]);
                        if (showStrategy) {
                            std::cout << std::endl; rolling_text(should_hit, PRINT_LINE_SLEEP); std::cout << std::endl;
                        }
                        break;
                    default:
                        break;
                }
                break;
            // Player card total is 16 (eight, eight)
            case 16:
                // Checking the value of the card that is face up of the dealer
                switch (dealer->GetCurrentHands()->RetrieveNode(0)->data->GetPlayerCards()->RetrieveNode(-1)->data.GetCardValue()) {
                    // Dealer is showing any card
                    case 2:
                    case 3:
                    case 4:
                    case 5:
                    case 6:
                    case 7:
                    case 8:
                    case 9:
                    case 10:
                    case 1:
                    case 11:
                        // Player should split
                        playerHand->GetHashTable()->AddToTable(playerHand->GetValuesMatrix()[3][2]);
                        if (showStrategy) {
                            std::cout << std::endl; rolling_text(should_split, PRINT_LINE_SLEEP); std::cout << std::endl;
                        }          
                        break;
                    default:
                        break;
                }
                break;
            // Player card total is 18 (nine, nine)
            case 18:
                // Checking the value of the card that is face up of the dealer
                switch (dealer->GetCurrentHands()->RetrieveNode(0)->data->GetPlayerCards()->RetrieveNode(-1)->data.GetCardValue()) {
                    // Dealer is showing a 7, Face, or Ace
                    case 7:
                    case 10:
                    case 1:
                    case 11:
                        // Player should stand
                        playerHand->GetHashTable()->AddToTable(playerHand->GetValuesMatrix()[3][3]);
                        if (showStrategy) {
                            std::cout << std::endl; rolling_text(should_stand, PRINT_LINE_SLEEP); std::cout << std::endl;
                        }
                        break;
                    // Otherwise
                    case 2:
                    case 3:
                    case 4:
                    case 5:
                    case 6:
                    case 8:
                    case 9:
                        // Player should split
                        playerHand->GetHashTable()->AddToTable(playerHand->GetValuesMatrix()[3][2]);
                        if (showStrategy) {
                            std::cout << std::endl; rolling_text(should_split, PRINT_LINE_SLEEP); std::cout << std::endl;
                        }
                        break;
                    default:
                        break;
                }
                break;
            // Player card total is 20 (face, face)
            case 20:
                // Checking the value of the card that is face up of the dealer
                switch (dealer->GetCurrentHands()->RetrieveNode(0)->data->GetPlayerCards()->RetrieveNode(-1)->data.GetCardValue()) {
                    // Dealer is showing any card
                    case 2:
                    case 3:
                    case 4:
                    case 5:
                    case 6:
                    case 7:
                    case 8:
                    case 9:
                    case 10:
                    case 1:
                    case 11:
                        // Player should stand
                        playerHand->GetHashTable()->AddToTable(playerHand->GetValuesMatrix()[3][3]);
                        if (showStrategy) {
                            std::cout << std::endl; rolling_text(should_stand, PRINT_LINE_SLEEP); std::cout << std::endl; 
                        }
                        break;
                    default:
                        break;
                }
                break;
            default:
                break;
        }
    }
    // Logic for if a player is dealt an Ace and only two cards are in the hand
    else if (playerHand->GetHashTable()->Contains(playerHand->GetValuesMatrix()[2][3]) && !playerHand->GetHashTable()->Contains(playerHand->GetValuesMatrix()[2][4]) && playerHand->GetPlayerCards()->GetSize() == 2) {
        // Check value of players cards
        switch (playerHand->GetCardsTotal()) {
            // Player card total is 13 or 14 (Ace, 2 || Ace, 3)
            case 13:
            case 14:
                // Checking the value of the card that is face up of the dealer
                switch (dealer->GetCurrentHands()->RetrieveNode(0)->data->GetPlayerCards()->RetrieveNode(-1)->data.GetCardValue()) {
                    // Dealer is showing 5 or 6
                    case 5:
                    case 6:
                        // Player can double down
                        if (playerHand->GetHashTable()->Contains(playerHand->GetValuesMatrix()[0][1])) {
                            // Player should double down or hit
                            playerHand->GetHashTable()->AddToTable(playerHand->GetValuesMatrix()[3][0]);
                            playerHand->GetHashTable()->AddToTable(playerHand->GetValuesMatrix()[3][1]);
                            if (showStrategy) {
                                std::cout << std::endl; rolling_text(should_double_down_or_hit, PRINT_LINE_SLEEP); std::cout << std::endl;
                            }
                        }
                        // Player cannot double down
                        else {
                            // Player should hit
                            playerHand->GetHashTable()->AddToTable(playerHand->GetValuesMatrix()[3][1]);
                            if (showStrategy) {
                                std::cout << std::endl; rolling_text(should_hit, PRINT_LINE_SLEEP); std::cout << std::endl;
                            }
                        }
                        break;
                    // Dealer is showing 2 - 4 or 7 - Face or Ace
                    case 2:
                    case 3:
                    case 4:
                    case 7:
                    case 8:
                    case 9:
                    case 10:
                    case 11:
                    case 1:
                        // Player should hit
                        playerHand->GetHashTable()->AddToTable(playerHand->GetValuesMatrix()[3][1]);
                        if (showStrategy) {
                            std::cout << std::endl; rolling_text(should_hit, PRINT_LINE_SLEEP); std::cout << std::endl;
                        }
                        break;
                    default:
                        break;
                }
                break;
            // Player card total is 15 or 16 (Ace, 4 || Ace, 5)
            case 15:
            case 16:
                // Checking the value of the card that is face up of the dealer
                switch (dealer->GetCurrentHands()->RetrieveNode(0)->data->GetPlayerCards()->RetrieveNode(-1)->data.GetCardValue()) {
                    // Dealer is showing a 4, 5, or 6
                    case 4:
                    case 5:
                    case 6:
                        // Player can double down
                        if (playerHand->GetHashTable()->Contains(playerHand->GetValuesMatrix()[0][1])) {
                            // Player should double down or hit
                            playerHand->GetHashTable()->AddToTable(playerHand->GetValuesMatrix()[3][0]);
                            playerHand->GetHashTable()->AddToTable(playerHand->GetValuesMatrix()[3][1]);
                            if (showStrategy) {
                                std::cout << std::endl; rolling_text(should_double_down_or_hit, PRINT_LINE_SLEEP); std::cout << std::endl;
                            }
                        }
                        // Player cannot double down
                        else {
                            // Player should hit
                            playerHand->GetHashTable()->AddToTable(playerHand->GetValuesMatrix()[3][1]);
                            if (showStrategy) {
                                std::cout << std::endl; rolling_text(should_hit, PRINT_LINE_SLEEP); std::cout << std::endl;
                            }
                        }              
                        break;
                    // Otherwise
                    case 2:
                    case 3:
                    case 7:
                    case 8:
                    case 9:
                    case 10:
                    case 1:
                    case 11:
                        // Player should hit
                        playerHand->GetHashTable()->AddToTable(playerHand->GetValuesMatrix()[3][1]);
                        if (showStrategy) {
                            std::cout << std::endl; rolling_text(should_hit, PRINT_LINE_SLEEP); std::cout << std::endl;
                        }
                        break;
                    default:
                        break;
                }
                break;
            // Player card total is 17 (Ace, 6)
            case 17:
                // Checking the value of the card that is face up of the dealer
                switch (dealer->GetCurrentHands()->RetrieveNode(0)->data->GetPlayerCards()->RetrieveNode(-1)->data.GetCardValue()) {
                    // Dealer is showing a 3, 4, 5, or 6
                    case 3:
                    case 4:
                    case 5:
                    case 6:
                        // Player can double down
                        if (playerHand->GetHashTable()->Contains(playerHand->GetValuesMatrix()[0][1])) {
                            // Player should double down or hit
                            playerHand->GetHashTable()->AddToTable(playerHand->GetValuesMatrix()[3][0]);
                            playerHand->GetHashTable()->AddToTable(playerHand->GetValuesMatrix()[3][1]);
                            if (showStrategy) {
                                std::cout << std::endl; rolling_text(should_double_down_or_hit, PRINT_LINE_SLEEP); std::cout << std::endl;
                            }
                        }
                        // Player cannot double down
                        else {
                            // Player should hit
                            playerHand->GetHashTable()->AddToTable(playerHand->GetValuesMatrix()[3][1]);
                            if (showStrategy) {
                                std::cout << std::endl; rolling_text(should_hit, PRINT_LINE_SLEEP); std::cout << std::endl;
                            }
                        }
                        break;
                    // Otherwise
                    case 2:
                    case 7:
                    case 8:
                    case 9:
                    case 10:
                    case 1:
                    case 11:
                        // Player should hit
                        playerHand->GetHashTable()->AddToTable(playerHand->GetValuesMatrix()[3][1]);
                        if (showStrategy) {
                            std::cout << std::endl; rolling_text(should_hit, PRINT_LINE_SLEEP); std::cout << std::endl;
                        }
                        break;
                    default:
                        break;
                }
                break;
            // Player card total is 18 (Ace, 7)
            case 18:
                // Checking the value of the card that is face up of the dealer
                switch (dealer->GetCurrentHands()->RetrieveNode(0)->data->GetPlayerCards()->RetrieveNode(-1)->data.GetCardValue()) {
                    // Dealer is showing a 2, 7, or 8
                    case 2:
                    case 7:
                    case 8:
                        // Player should stand
                        playerHand->GetHashTable()->AddToTable(playerHand->GetValuesMatrix()[3][3]);
                        if (showStrategy) {
                            std::cout << std::endl; rolling_text(should_stand, PRINT_LINE_SLEEP); std::cout << std::endl; 
                        }
                        break;
                    // Dealer is showing a 3, 4, 5, or 6
                    case 3:
                    case 4:
                    case 5:
                    case 6:
                        // Player can double down
                        if (playerHand->GetHashTable()->Contains(playerHand->GetValuesMatrix()[0][1])) {
                            // Player should double down or stand
                            playerHand->GetHashTable()->AddToTable(playerHand->GetValuesMatrix()[3][0]);
                            playerHand->GetHashTable()->AddToTable(playerHand->GetValuesMatrix()[3][3]);
                            if (showStrategy) {
                                std::cout << std::endl; rolling_text(should_double_down_or_stand, PRINT_LINE_SLEEP); std::cout << std::endl;
                            }
                        }
                        else {
                            // Player should stand
                            playerHand->GetHashTable()->AddToTable(playerHand->GetValuesMatrix()[3][3]);
                            if (showStrategy) {
                                std::cout << std::endl; rolling_text(should_stand, PRINT_LINE_SLEEP); std::cout << std::endl;
                            }
                        }
                        break;
                    // Dealer is showing 9, Face, or Ace
                    case 9:
                    case 10:
                    case 1:
                    case 11:
                        // Player should hit
                        playerHand->GetHashTable()->AddToTable(playerHand->GetValuesMatrix()[3][1]);
                        if (showStrategy) {
                            std::cout << std::endl; rolling_text(should_hit, PRINT_LINE_SLEEP); std::cout << std::endl;
                        }
                        break;
                    default:
                        break;
                }
                break;
            // Player card total is 19, 20, or 21 (Ace, 8 || Ace, 9 || Ace, Ten)
            case 19:
            case 20:
            case 21:
                // Checking the value of the card that is face up of the dealer
                switch (dealer->GetCurrentHands()->RetrieveNode(0)->data->GetPlayerCards()->RetrieveNode(-1)->data.GetCardValue()) {
                    // Dealer is showing any card
                    case 2:
                    case 3:
                    case 4:
                    case 5:
                    case 6:
                    case 7:
                    case 8:
                    case 9:
                    case 10:
                    case 1:
                    case 11:
                        // Player should stand
                        playerHand->GetHashTable()->AddToTable(playerHand->GetValuesMatrix()[3][3]);
                        if (showStrategy) {
                            std::cout << std::endl; rolling_text(should_stand, PRINT_LINE_SLEEP); std::cout << std::endl;
                        } 
                        break;
                    default:
                        break;
                }
                break;
            default:
                break;
        }
    }
    // Logic for all other scenarios
    else {
        // Check value of players cards
        switch (playerHand->GetCardsTotal()) {
            // Player card total is 4-8
            case 4:
            case 5:
            case 6:
            case 7:
            case 8:
                // Checking the value of the card that is face up of the dealer
                switch (dealer->GetCurrentHands()->RetrieveNode(0)->data->GetPlayerCards()->RetrieveNode(-1)->data.GetCardValue()) {
                    // Dealer is showing any card
                    case 1:
                    case 2:
                    case 3:
                    case 4:
                    case 5:
                    case 6:
                    case 7:
                    case 8:
                    case 9:
                    case 10:
                    case 11:
                        // Player should hit
                        playerHand->GetHashTable()->AddToTable(playerHand->GetValuesMatrix()[3][1]);
                        if (showStrategy) {
                            std::cout << std::endl; rolling_text(should_hit, PRINT_LINE_SLEEP); std::cout << std::endl;
                        }
                        break;
                    default:
                        break;
                }
                break;
            // Player card total is 9
            case 9:
                // Checking the value of the card that is face up of the dealer
                switch (dealer->GetCurrentHands()->RetrieveNode(0)->data->GetPlayerCards()->RetrieveNode(-1)->data.GetCardValue()) {
                    // Dealer is showing 2-6
                    case 2:
                    case 3:
                    case 4:
                    case 5:
                    case 6:
                        // Player can double down
                        if (playerHand->GetHashTable()->Contains(playerHand->GetValuesMatrix()[0][1])) {
                            // Player should double down or hit
                            playerHand->GetHashTable()->AddToTable(playerHand->GetValuesMatrix()[3][0]);
                            playerHand->GetHashTable()->AddToTable(playerHand->GetValuesMatrix()[3][1]);
                            if (showStrategy) {
                                std::cout << std::endl; rolling_text(should_double_down_or_hit, PRINT_LINE_SLEEP); std::cout << std::endl;
                            }
                        }
                        // Player cannot double down
                        else {
                            // Player should hit
                            playerHand->GetHashTable()->AddToTable(playerHand->GetValuesMatrix()[3][1]);
                            if (showStrategy) {
                                std::cout << std::endl; rolling_text(should_hit, PRINT_LINE_SLEEP); std::cout << std::endl;
                            }
                        }
                        break;
                    // Dealer is showing 7-Face or Ace
                    case 7:
                    case 8:
                    case 9:
                    case 10:
                    case 11:
                    case 1:
                        // Player should hit
                        playerHand->GetHashTable()->AddToTable(playerHand->GetValuesMatrix()[3][1]);
                        if (showStrategy) {
                            std::cout << std::endl; rolling_text(should_hit, PRINT_LINE_SLEEP); std::cout << std::endl;
                        }
                        break;
                    default:
                        break;
                }
                break;
            // Player card total is 10
            case 10:
                // Checking the value of the card that is face up of the dealer
                switch (dealer->GetCurrentHands()->RetrieveNode(0)->data->GetPlayerCards()->RetrieveNode(-1)->data.GetCardValue()) {
                    // Dealer is showing 2-9
                    case 2:
                    case 3:
                    case 4:
                    case 5:
                    case 6:
                    case 7:
                    case 8:
                    case 9:
                        // Player can double down
                        if (playerHand->GetHashTable()->Contains(playerHand->GetValuesMatrix()[0][1])) {
                            // Player should double down or hit
                            playerHand->GetHashTable()->AddToTable(playerHand->GetValuesMatrix()[3][0]);
                            playerHand->GetHashTable()->AddToTable(playerHand->GetValuesMatrix()[3][1]);
                            if (showStrategy) {
                                std::cout << std::endl; rolling_text(should_double_down_or_hit, PRINT_LINE_SLEEP); std::cout << std::endl;
                            }
                        }
                        // Player cannot double down
                        else {
                            // Player should hit
                            playerHand->GetHashTable()->AddToTable(playerHand->GetValuesMatrix()[3][1]);
                            if (showStrategy) {
                                std::cout << std::endl; rolling_text(should_hit, PRINT_LINE_SLEEP); std::cout << std::endl;
                            }
                        }
                        break;
                    // Dealer is showing a face card or Ace
                    case 10:
                    case 11:
                    case 1:
                        // Player should hit
                        playerHand->GetHashTable()->AddToTable(playerHand->GetValuesMatrix()[3][1]);
                        if (showStrategy) {
                            std::cout << std::endl; rolling_text(should_hit, PRINT_LINE_SLEEP); std::cout << std::endl;
                        }
                        break;
                    default:
                        break;
                }
                break;
            // Player card total is 11
            case 11:
                // Checking the value of the card that is face up of the dealer
                switch (dealer->GetCurrentHands()->RetrieveNode(0)->data->GetPlayerCards()->RetrieveNode(-1)->data.GetCardValue()) {
                    // Dealer is showing any card
                    case 1:
                    case 2:
                    case 3:
                    case 4:
                    case 5:
                    case 6:
                    case 7:
                    case 8:
                    case 9:
                    case 10:
                    case 11:
                        // Player can double down
                        if (playerHand->GetHashTable()->Contains(playerHand->GetValuesMatrix()[0][1])) {
                            // Player should double down or hit
                            playerHand->GetHashTable()->AddToTable(playerHand->GetValuesMatrix()[3][0]);
                            playerHand->GetHashTable()->AddToTable(playerHand->GetValuesMatrix()[3][1]);
                            if (showStrategy) {
                                std::cout << std::endl; rolling_text(should_double_down_or_hit, PRINT_LINE_SLEEP); std::cout << std::endl;
                            }
                        }
                        // Player cannot double down
                        else {
                            // Player should hit
                            playerHand->GetHashTable()->AddToTable(playerHand->GetValuesMatrix()[3][1]);
                            if (showStrategy) {
                                std::cout << std::endl; rolling_text(should_hit, PRINT_LINE_SLEEP); std::cout << std::endl;
                            }
                        }
                        break;
                    default:
                        break;
                }
                break;
            // Player card total is 12
            case 12:
                // Checking the value of the card that is face up of the dealer
                switch (dealer->GetCurrentHands()->RetrieveNode(0)->data->GetPlayerCards()->RetrieveNode(-1)->data.GetCardValue()) {
                    // Dealer is showing a 2,3 or 7-Face or Ace
                    case 2:
                    case 3:
                    case 7:
                    case 8:
                    case 9:
                    case 10:
                    case 1:
                    case 11:
                        // Player should hit
                        playerHand->GetHashTable()->AddToTable(playerHand->GetValuesMatrix()[3][1]);
                        if (showStrategy) {
                            std::cout << std::endl; rolling_text(should_hit, PRINT_LINE_SLEEP); std::cout << std::endl;
                        }
                        break;
                    // Dealer is showing a 4-6
                    case 4:
                    case 5:
                    case 6:
                        // Player should stand
                        playerHand->GetHashTable()->AddToTable(playerHand->GetValuesMatrix()[3][3]);
                        if (showStrategy) {
                            std::cout << std::endl; rolling_text(should_stand, PRINT_LINE_SLEEP); std::cout << std::endl;
                        }
                        break;
                    default:
                        break;
                }
                break;
            // Player card total is 13 through 16
            case 13:
            case 14:
            case 15:
            case 16:
                // Checking the value of the card that is face up of the dealer
                switch (dealer->GetCurrentHands()->RetrieveNode(0)->data->GetPlayerCards()->RetrieveNode(-1)->data.GetCardValue()) {
                    // Dealer is showing 2-6
                    case 2:
                    case 3:
                    case 4:
                    case 5:
                    case 6:
                        // Player should stand
                        playerHand->GetHashTable()->AddToTable(playerHand->GetValuesMatrix()[3][3]);
                        if (showStrategy) {
                            std::cout << std::endl; rolling_text(should_stand, PRINT_LINE_SLEEP); std::cout << std::endl;
                        }
                        break;
                    // Dealer is showing 7-Face or Ace
                    case 7:
                    case 8:
                    case 9:
                    case 10:
                    case 1:
                    case 11:
                        // Player should hit
                        playerHand->GetHashTable()->AddToTable(playerHand->GetValuesMatrix()[3][1]);
                        if (showStrategy) {
                            std::cout << std::endl; rolling_text(should_hit, PRINT_LINE_SLEEP); std::cout << std::endl;
                        }
                        break;
                    default:
                        break;
                }
                break;
            // Player card total is 17 through 21
            case 17:
            case 18:
            case 19:
            case 20:
            case 21:
                // Checking the value of the card that is face up of the dealer
                switch (dealer->GetCurrentHands()->RetrieveNode(0)->data->GetPlayerCards()->RetrieveNode(-1)->data.GetCardValue()) {
                    // Dealer is showing any card
                    case 2:
                    case 3:
                    case 4:
                    case 5:
                    case 6:
                    case 7:
                    case 8:
                    case 9:
                    case 10:
                    case 1:
                    case 11:
                        // Player should stand
                        playerHand->GetHashTable()->AddToTable(playerHand->GetValuesMatrix()[3][3]);
                        if (showStrategy) {
                            std::cout << std::endl; rolling_text(should_stand, PRINT_LINE_SLEEP); std::cout << std::endl; 
                        }
                        break;
                    default:
                        break;
                }
                break;
            default:
                break;
        }
    }
}

/*  csv_generator - Generates a CSV file for the game of a player
*   Input:
*       input - Player object passed by reference that represents the player that is going to have a csv made of it
*   Algorithm:
*       * Create a file name for the CSV file
*       * Generate a file with the contents of the players hand
*       * Close the file
*   Output:
*       fileName - After creating the csv file, this function returns the name of the file that has been created
*/
std::string csv_generator(std::shared_ptr<Player>& input) {
    // Create string for filename of csv
    std::string fileName = input->GetName() + " Results.csv";
    // Generate file object
    std::ofstream file(fileName);
    // File has successfully opened
    if (file) {
        // Set headers of csv file
        file << "Hand Number, Hand Wager, Hand Net, Hand Total, Bank Total" << std::endl;
        for (int i = 0; i < input->GetTotalHandsPlayed()->GetSize(); i++) {
            file << input->GetTotalHandsPlayed()->RetrieveNode(i)->data << "," << input->GetTotalHandWagers()->RetrieveNode(i)->data << "," << input->GetTotalHandNets()->RetrieveNode(i)->data << ","
            << input->GetTotalHandCardTotals()->RetrieveNode(i)->data << "," << input->GetTotalHandBankTotals()->RetrieveNode(i)->data << std::endl;
        }
        // Close file
        file.close();
        // Output message that file has been successfully created
        progress_bar(LONG_TIME_SLEEP, "Creating CSV ", fileName + " has been successfully created.");
        time_sleep(MEDIUM_TIME_SLEEP); 
        clear_terminal();
    }
    // File failed to open
    else {
        std::cout << "Error creating CSV File: " << fileName << std::endl;
    }
    return fileName;
}

/*  deal_hand - Deals cards to players and shows the hands of each player after the deal
*   Input:
*       humanPlayer - Player object that is passed by reference that resembles a non dealer player
*       dealer - Player object that resembles a dealer in a blackjack game
*       inputShoe - Shoe object that is passed by reference that resembles a shoe used in game
*   Algorithm:
*       * Request the player place a wager for the hand
*       * Deal cards to a player and dealer
*       * Show the hands of the player and the dealer off of deal
*       * Return the Hand objects and the Shoe object
*   Output:
*       This function does not return any values, it modifies input parameters
*/
void deal_hand(std::shared_ptr<Player>& humanPlayer, std::shared_ptr<Player>& dealer, std::shared_ptr<Shoe>& inputShoe) {
    // Create hands for players
    std::shared_ptr<Hand> humanHand(new Hand());
    std::shared_ptr<Hand> dealerHand(new Hand());
    // Add hands to players
    humanPlayer->SetCurrentHands(humanHand);
    dealer->SetCurrentHands(dealerHand);
    // Have player place wager
    humanPlayer->GetCurrentHands()->RetrieveNode(0)->data->PlaceWagerPrompt(humanPlayer->GetBankTotal(), humanPlayer->GetDisplayName());
    // Deal cards to players
    for (int i = 0; i < 4; i++) {
        if (i % 2 == 0) {
            humanPlayer->GetCurrentHands()->RetrieveNode(0)->data->HitHand(inputShoe);
        }
        else if (i % 2 == 1) {
            dealer->GetCurrentHands()->RetrieveNode(0)->data->HitHand(inputShoe);
        }
    }
    // Show hands of player
    std::cout << std::endl; rolling_text("Here are the initial hands of each player: ", PRINT_LINE_SLEEP); std::cout << std::endl;
    humanPlayer->ShowCurrentHand(humanHand, "Initial", "");
    dealer->ShowCurrentHand(dealerHand, "Initial", "");
    humanPlayer->GetCurrentHands()->RetrieveNode(0)->data->ParametersCheck(dealerHand, humanPlayer->GetBankTotal());
    dealer->GetCurrentHands()->RetrieveNode(0)->data->ParametersCheck(dealerHand, 0);
}


/*  deal_hand_sim - Deals cards to players and shows the hands of each player after the deal for a simulated game
*   Input:
*       humanPlayer - Player object that is passed by reference that represents a human player in a simulated game
*       dealer - Player object that is passed by reference that represents a dealer in a simulated game
*       inputShoe - Shoe object passed by reference that represents the show of of the game
*       playerWager - Wafer that is to be placed for the player
*   Algorithm:
*       * Create hands for the players
*       * Add the hands to the player objects
*       * Place the wager for the player
*       * Deal cards to the players
*       * Check for parameters in the players hand's
*   Output:
*       This function does not return any values
*/
void deal_hand_sim(std::shared_ptr<Player>& humanPlayer, std::shared_ptr<Player>& dealer, std::shared_ptr<Shoe>& inputShoe, const float& playerWager) {
    // Create hands for players
    std::shared_ptr<Hand> humanHand(new Hand());
    std::shared_ptr<Hand> dealerHand(new Hand());
    // Add hands to players
    humanPlayer->SetCurrentHands(humanHand);
    dealer->SetCurrentHands(dealerHand);
    // Place wager for player
    humanPlayer->GetCurrentHands()->RetrieveNode(0)->data->PlaceWagerSim(humanPlayer->GetBankTotal(), playerWager);
    // Deal cards to players
    for (int i = 0; i < 4; i++) {
        if (i % 2 == 0) {
            humanPlayer->GetCurrentHands()->RetrieveNode(0)->data->HitHand(inputShoe);
        }
        else if (i % 2 == 1) {
            dealer->GetCurrentHands()->RetrieveNode(0)->data->HitHand(inputShoe);
        }
    }
    // Check parameters of players
    humanPlayer->GetCurrentHands()->RetrieveNode(0)->data->ParametersCheck(dealerHand, humanPlayer->GetBankTotal());
    dealer->GetCurrentHands()->RetrieveNode(0)->data->ParametersCheck(dealerHand, 0);
}

/*  dealer_logic - Processes the logic for how the dealer should play their current hands
*   Input:
*       humanPlayer - Player object that is passed by reference that resembles a non dealer player
*       dealer - Player object that resembles a dealer in a blackjack game
*       shoe - Shoe object passed by reference that represents the shoe in the game that is being played with
*   Algorithm:
*       * Check the parameters of the dealers hand
*       * Check if all of the hands of the player are over 21
*       * If all the hands of the player are not over 21
*           * Check if the dealer needs to play (i.e. The have 17 or less or they have a soft 17)
*               * If they don't need to play, show the hands of the player and the dealer
*               * If they do need to play, proceed to have the dealer play until they reach a count of 17 or greater (dealer hits on all soft 17)
*           * Show the hands of the player and the dealer after they have finished playing their hand
*       * If all the hands of the player are over 21
*           * Show the hands of the player and the dealer
*   Output:
*       This function does not return a value, it modifies input parameters
*/
void dealer_logic(std::shared_ptr<Player>& humanPlayer, std::shared_ptr<Player>& dealer, std::shared_ptr<Shoe>& shoe) {
    // Check the parameters of the dealers hand
    dealer->GetCurrentHands()->RetrieveNode(0)->data->ParametersCheck(dealer->GetCurrentHands()->RetrieveNode(0)->data, humanPlayer->GetBankTotal());
    // Check if all hands of the player are over 21
    bool all_over_21 = true;
    for (int i = 0; i < humanPlayer->GetCurrentHands()->GetSize(); i++) {
        if (humanPlayer->GetCurrentHands()->RetrieveNode(i)->data->GetCardsTotal() <= 21) {
            all_over_21 = false;
            break;
        }
    }
    // Not all hands of player are over 21
    if (!all_over_21) {
        // Check if the dealer has an Ace in their hand
        dealer->GetCurrentHands()->RetrieveNode(0)->data->CheckParamInHand("R", Ranks[0]);
        bool hasAceInHand = dealer->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(dealer->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[2][3]);
        bool hasSoftSeventeen = dealer->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(dealer->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][4]);
        // Dealer has a hand total of seventeen or greater with no Ace in hand
        if ((dealer->GetCurrentHands()->RetrieveNode(0)->data->GetCardsTotal() >= 17 && !hasAceInHand) || (dealer->GetCurrentHands()->RetrieveNode(0)->data->GetCardsTotal() > 17)) {
            std::cout << std::endl; rolling_text("The " + dealer->GetDisplayName() + " does not need to play their hand with a final hand total of " + dealer->GetCurrentHands()->RetrieveNode(0)->data->GetDisplayCardsTotal() + ".", PRINT_LINE_SLEEP); std::cout << std::endl;
        }
        // Dealer has less than 17 or has a soft 17
        else if (dealer->GetCurrentHands()->RetrieveNode(0)->data->GetCardsTotal() < 17 || hasSoftSeventeen) {
            std::cout << std::endl; rolling_text("The " + dealer->GetDisplayName() + " will now play their hand.",PRINT_LINE_SLEEP); std::cout << std::endl;
            // Dealer must continue to play and will hit on soft seventeen
            while (dealer->GetCurrentHands()->RetrieveNode(0)->data->GetCardsTotal() < 17 || hasSoftSeventeen) {
                hasSoftSeventeen = dealer->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(dealer->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][4]);
                // Dealer still has less than seventeen or possesses a soft seventeen
                if (dealer->GetCurrentHands()->RetrieveNode(0)->data->GetCardsTotal() < 17 || hasSoftSeventeen) {
                    dealer->GetCurrentHands()->RetrieveNode(0)->data->HitHand(shoe);
                    rolling_text(dealer->GetDisplayName() + " hits hand: ",SPRINT_LINE_SLEEP); dealer->ShowCurrentHand(dealer->GetCurrentHands()->RetrieveNode(0)->data, "current", "cards"); std::cout << std::endl;
                    dealer->GetCurrentHands()->RetrieveNode(0)->data->ParametersCheck(dealer->GetCurrentHands()->RetrieveNode(0)->data, humanPlayer->GetBankTotal());
                    continue;
                }
                // Dealer has 17 or higher and does not have a soft seventeen
                else if (dealer->GetCurrentHands()->RetrieveNode(0)->data->GetCardsTotal() >= 17 && !hasSoftSeventeen) {
                    break;
                }
            }
            // Show final hand of dealer
            dealer->ShowCurrentHand(dealer->GetCurrentHands()->RetrieveNode(0)->data, "Final", "Show");
        }
    }
    // All hands are over 21
    else {
        std::cout << std::endl; rolling_text("The " + humanPlayer->GetDisplayName() + " has busted on all of their hands. " + dealer->GetDisplayName() + " does not need to play their hand.", PRINT_LINE_SLEEP); std::cout << std::endl;
    }
}

/*  dealer_logic_sim - Processes the logic for how the dealer should play their current hands for a simulated hand
*   Input:
*       humanPlayer - Player object that is passed by reference that represents a non dealer player
*       dealer - Player object that is passed by reference that represents a dealer
*       shoe - Shoe object passed by reference that represents the shoe in the game that is being played with
*   Algorithm:
*       * Check the parameters of the dealers hand
*       * Check if the player's hands are all over 21
*           * If they aren't process the logic of a dealer playing (see inline comments)
*           * If they are all over 21, do not make the dealer play their hand
*   Output:
*       This function does not return a value, it modifies a dealer players hand and shoe after logical checks
*/
void dealer_logic_sim(std::shared_ptr<Player>& humanPlayer, std::shared_ptr<Player>& dealer, std::shared_ptr<Shoe>& shoe) {
    // Check the parameters of the dealers hand
    dealer->GetCurrentHands()->RetrieveNode(0)->data->ParametersCheck(dealer->GetCurrentHands()->RetrieveNode(0)->data, humanPlayer->GetBankTotal());
    // Check if all hands of the player are over 21
    bool all_over_21 = true;
    for (int i = 0; i < humanPlayer->GetCurrentHands()->GetSize(); i++) {
        if (humanPlayer->GetCurrentHands()->RetrieveNode(i)->data->GetCardsTotal() <= 21) {
            all_over_21 = false;
            break;
        }
    }
    // Not all hands of player are over 21
    if (!all_over_21) {
        // Check if the dealer has an Ace in their hand
        dealer->GetCurrentHands()->RetrieveNode(0)->data->CheckParamInHand("R", Ranks[0]);
        bool hasAceInHand = dealer->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(dealer->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[2][3]);
        bool hasSoftSeventeen = dealer->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(dealer->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][4]);
        // Dealer has a hand total of seventeen or greater with no Ace in hand
        if ((dealer->GetCurrentHands()->RetrieveNode(0)->data->GetCardsTotal() >= 17 && !hasAceInHand) || (dealer->GetCurrentHands()->RetrieveNode(0)->data->GetCardsTotal() > 17)) {}
        // Dealer has less than 17 or has a soft 17
        else if (dealer->GetCurrentHands()->RetrieveNode(0)->data->GetCardsTotal() < 17 || hasSoftSeventeen) {
            // Dealer must continue to play and will hit on soft seventeen
            while (dealer->GetCurrentHands()->RetrieveNode(0)->data->GetCardsTotal() < 17 || hasSoftSeventeen) {
                hasSoftSeventeen = dealer->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(dealer->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][4]);
                // Dealer still has less than seventeen or possesses a soft seventeen
                if (dealer->GetCurrentHands()->RetrieveNode(0)->data->GetCardsTotal() < 17 || hasSoftSeventeen) {
                    dealer->GetCurrentHands()->RetrieveNode(0)->data->HitHand(shoe);
                    dealer->GetCurrentHands()->RetrieveNode(0)->data->ParametersCheck(dealer->GetCurrentHands()->RetrieveNode(0)->data, humanPlayer->GetBankTotal());
                    continue;
                }
                // Dealer has 17 or higher and does not have a soft seventeen
                else if (dealer->GetCurrentHands()->RetrieveNode(0)->data->GetCardsTotal() >= 17 && !hasSoftSeventeen) {
                    break;
                }
            }
        }
    }
}

/*  game_logic - Processes the logic required for a single hand of blackjack amongst players and dealer
*   Input:
*       humanPlayer - Player object that is passed by reference that resembles a non dealer player
*       dealer - Player object that resembles a dealer in a blackjack game
*       shoe - Shoe object passed by reference that represents the shoe in the game that is being played with
*   Algorithm:
*       * Process the blackjack_check function and return its values
*       * Determine if the hand must continue after blackjack_check
*           * If it continues, process the following functions: same_rank_check, player_logic, dealer_logic, hand_comparison_logic
*           * If it does not continue, proceed to return the objects that have been modified
*       * Return the playerHand, dealerHand, and shoe objects
*   Output:
*       This function does not return a value, it modifies input parameters
*/
void game_logic(std::shared_ptr<Player>& humanPlayer, std::shared_ptr<Player>& dealer, std::shared_ptr<Shoe>& shoe) {
    // Process the blackjack_check_sim function
    auto dealerAce = blackjack_check(humanPlayer, dealer, shoe);
    // If neither player has blackjack, continue
    if (dealerAce) {
        // Process the player_logic function
        player_logic(humanPlayer, dealer, shoe);
        // Process the dealer_logic function
        dealer_logic(humanPlayer, dealer, shoe);
        // Process the hand_comparison_logic function
        hand_comparison_logic(humanPlayer, dealer);
    }
    humanPlayer->ResetPlayer();
    dealer->ResetPlayer();
}

/*  game_logic_sim - Processes the logic required for a single hand of blackjack amongst players and dealer
*   Input:
*       humanPlayer - Player object that is passed by reference that represents the user
*       dealer - Player object that is passed by reference that represents the dealer
*       shoe - Shoe object that is passed by reference that represents the game shoe that is being played with
*       handWager - Float value that represents the wager that is to be placed for a given players hand
*   Algorithm:
*       * Process the blackjack_check function and return its values
*       * Determine if the hand must continue after blackjack_check
*           * If it continues, process the following functions: same_rank_check, player_logic, dealer_logic, hand_comparison_logic
*           * If it does not continue, proceed to return the objects that have been modified
*       * Return the playerHand, dealerHand, and shoe objects
*   Output:
*       This function does not return a value, it modifies the input parameters for a given simulated game
*/
void game_logic_sim(std::shared_ptr<Player>& humanPlayer, std::shared_ptr<Player>& dealer, std::shared_ptr<Shoe>& shoe, float handWager) {
    // Process the blackjack_check_sim function
    auto dealerAce = blackjack_check_sim(humanPlayer, dealer, shoe, handWager, false);
    // If neither player has blackjack, continue
    if (dealerAce) {
        // Process the player_logic_sim function
        player_logic_sim(humanPlayer, dealer, shoe, true);
        // Process the dealer_logic_sim function
        dealer_logic_sim(humanPlayer, dealer, shoe);
        // Process the hand_comparison_logic_sim function
        hand_comparison_logic_sim(humanPlayer, dealer);
    }
    humanPlayer->ResetPlayer();
    dealer->ResetPlayer();
}

/*  hand_comparison_logic - Compares the hand of a player to that of the dealer and determines if they push, win, or lose
*   Input:
*       humanPlayer - Player object that is passed by reference that resembles a non dealer player
*       dealer - Player object that resembles a dealer in a blackjack game
*       shoe - Shoe object passed by reference that represents the shoe in the game that is being played with
*   Algorithm:
*       * Create a "hand_tracker" string value that keeps track of the current hand that is being examined
*       * Check to first see if players current hand is less than or equal to 21
*           * If it is less than or equal to 21, check to see if the players hand is equal to that of the dealers
*               * If it is, then update the players bank so that it is a push for the player
*               * Show the final hand of the player (or current hand if multiple) and output a message showing the result of the hand
*           * Check to see if the dealers hand is greater than the players and less than or equal to 21
*               * If it is, then update the players bank so that it is a loss for the player
*               * Show the final hand of the player (or current hand if multiple) and output a message showing the result of the hand
*           * Check to see if the players hand is greater than that of the dealers
*               * If it is, then update the players bank so that it is a win for the player
*               * Show the final hand of the player (or current hand if multiple) and output a message showing the result of the hand
*       * Check to see if the players current hand is greater than 21
*           * If it is, then update the players bank so that it is a loss for the player
*           * Show the final hand of the player (or current hand if multiple) and output a message showing the result of the hand
*   Output:
*       This function does not return a value, it modifies input parameters
*/
void hand_comparison_logic(std::shared_ptr<Player>& humanPlayer, std::shared_ptr<Player>& dealer) {
    for (int i = 0; i < humanPlayer->GetCurrentHands()->GetSize(); i++) {
        // Player has a hand total of less than or equal to 21
        if (humanPlayer->GetCurrentHands()->RetrieveNode(i)->data->GetCardsTotal() <= 21) {
            // Player and dealer have the same hand total
            if (humanPlayer->GetCurrentHands()->RetrieveNode(i)->data->GetCardsTotal() == dealer->GetCurrentHands()->RetrieveNode(0)->data->GetCardsTotal()) {
                // Player pushes their current hand
                humanPlayer->UpdateBank(humanPlayer->GetCurrentHands()->RetrieveNode(i)->data, 3);
                std::cout << std::endl; rolling_text("Both players have the same final hand total of " + humanPlayer->GetCurrentHands()->RetrieveNode(i)->data->GetDisplayCardsTotal() + ". ",PRINT_LINE_SLEEP); std::cout << std::endl;
                std::cout << std::endl; rolling_text("Here are the final hands of each player:", PRINT_LINE_SLEEP); std::cout << std::endl;
                humanPlayer->ShowCurrentHand(humanPlayer->GetCurrentHands()->RetrieveNode(i)->data, "Final", "");
                dealer->ShowCurrentHand(dealer->GetCurrentHands()->RetrieveNode(0)->data, "Final", "Show");
                std::string statTracker = color_text(36, "Hands Played: " + std::to_string(humanPlayer->GetHandsPlayed())) + " , " + color_text(32, "Hands Won: " + std::to_string(humanPlayer->GetHandsWon())) + " , " + color_text(31, "Hands Lost: " 
                + std::to_string(humanPlayer->GetHandsLost())) + " , " + color_text(33, "Hands Pushed: " + std::to_string(humanPlayer->GetHandsPushed())) + " , " + color_text(35, "Blackjacks: " + std::to_string(humanPlayer->GetBlackjackHands())) + ".";
                std::cout << std::endl; rolling_text(humanPlayer->GetDisplayName() + " has pushed this hand. " + statTracker, PRINT_LINE_SLEEP); std::cout << std::endl;
            }
            // Dealer wins
            else if (dealer->GetCurrentHands()->RetrieveNode(0)->data->GetCardsTotal() > humanPlayer->GetCurrentHands()->RetrieveNode(i)->data->GetCardsTotal() && dealer->GetCurrentHands()->RetrieveNode(0)->data->GetCardsTotal() <= 21) {
                // Player loses their current hand
                humanPlayer->UpdateBank(humanPlayer->GetCurrentHands()->RetrieveNode(i)->data, 2);
                std::cout << std::endl; rolling_text(humanPlayer->GetDisplayName() + " has a lesser final hand total of " + humanPlayer->GetCurrentHands()->RetrieveNode(i)->data->GetDisplayCardsTotal() + " compared to that of the " 
                + dealer->GetDisplayName() + "'s final hand total of " + dealer->GetCurrentHands()->RetrieveNode(0)->data->GetDisplayCardsTotal() + ".",PRINT_LINE_SLEEP); std::cout << std::endl;
                std::cout << std::endl; rolling_text("Here are the final hands of each player:", PRINT_LINE_SLEEP); std::cout << std::endl;
                humanPlayer->ShowCurrentHand(humanPlayer->GetCurrentHands()->RetrieveNode(i)->data, "Final", "");
                dealer->ShowCurrentHand(dealer->GetCurrentHands()->RetrieveNode(0)->data, "Final", "Show");
                std::string statTracker = color_text(36, "Hands Played: " + std::to_string(humanPlayer->GetHandsPlayed())) + " , " + color_text(32, "Hands Won: " + std::to_string(humanPlayer->GetHandsWon())) + " , " + color_text(31, "Hands Lost: " 
                + std::to_string(humanPlayer->GetHandsLost())) + " , " + color_text(33, "Hands Pushed: " + std::to_string(humanPlayer->GetHandsPushed())) + " , " + color_text(35, "Blackjacks: " + std::to_string(humanPlayer->GetBlackjackHands())) + ".";
                std::cout << std::endl; rolling_text(humanPlayer->GetDisplayName() + " has lost this hand. " + statTracker, PRINT_LINE_SLEEP); std::cout << std::endl;
            }
            // Player wins
            else if (dealer->GetCurrentHands()->RetrieveNode(0)->data->GetCardsTotal() < humanPlayer->GetCurrentHands()->RetrieveNode(i)->data->GetCardsTotal() || dealer->GetCurrentHands()->RetrieveNode(0)->data->GetCardsTotal() > 21) {
                // Player wins their current hand
                humanPlayer->UpdateBank(humanPlayer->GetCurrentHands()->RetrieveNode(i)->data, 1);
                if (dealer->GetCurrentHands()->RetrieveNode(0)->data->GetCardsTotal() > 21) {
                    std::cout << std::endl; rolling_text("The " + dealer->GetDisplayName() + " has busted and " + humanPlayer->GetDisplayName() + " did not.",PRINT_LINE_SLEEP); std::cout << std::endl;
                }
                else {
                    std::cout << std::endl; rolling_text(humanPlayer->GetDisplayName() + " has a greater final hand total of " + humanPlayer->GetCurrentHands()->RetrieveNode(i)->data->GetDisplayCardsTotal() + " compared to that of the " 
                    + dealer->GetDisplayName() + "'s final hand total of " + dealer->GetCurrentHands()->RetrieveNode(0)->data->GetDisplayCardsTotal() + ".",PRINT_LINE_SLEEP); std::cout << std::endl;
                }
                std::cout << std::endl; rolling_text("Here are the final hands of each player:", PRINT_LINE_SLEEP); std::cout << std::endl;
                humanPlayer->ShowCurrentHand(humanPlayer->GetCurrentHands()->RetrieveNode(i)->data, "Final", "");
                dealer->ShowCurrentHand(dealer->GetCurrentHands()->RetrieveNode(0)->data, "Final", "Show");
                std::string statTracker = color_text(36, "Hands Played: " + std::to_string(humanPlayer->GetHandsPlayed())) + " , " + color_text(32, "Hands Won: " + std::to_string(humanPlayer->GetHandsWon())) + " , " + color_text(31, "Hands Lost: " 
                + std::to_string(humanPlayer->GetHandsLost())) + " , " + color_text(33, "Hands Pushed: " + std::to_string(humanPlayer->GetHandsPushed())) + " , " + color_text(35, "Blackjacks: " + std::to_string(humanPlayer->GetBlackjackHands())) + ".";
                std::cout << std::endl; rolling_text(humanPlayer->GetDisplayName() + " has won this hand. " + statTracker, PRINT_LINE_SLEEP); std::cout << std::endl;
            }
        }
        // Player has a hand total of 21 or greater
        else {
            // Player loses their current hand
            humanPlayer->UpdateBank(humanPlayer->GetCurrentHands()->RetrieveNode(i)->data, 2);
            std::cout << std::endl; rolling_text(humanPlayer->GetDisplayName() + " has busted with a final hand total of " + humanPlayer->GetCurrentHands()->RetrieveNode(i)->data->GetDisplayCardsTotal() + ".",PRINT_LINE_SLEEP); std::cout << std::endl;
            std::cout << std::endl; rolling_text("Here are the final hands of each player:", PRINT_LINE_SLEEP); std::cout << std::endl;
            humanPlayer->ShowCurrentHand(humanPlayer->GetCurrentHands()->RetrieveNode(i)->data, "Final", "");
            dealer->ShowCurrentHand(dealer->GetCurrentHands()->RetrieveNode(0)->data, "Final", "Show");
            std::string statTracker = color_text(36, "Hands Played: " + std::to_string(humanPlayer->GetHandsPlayed())) + " , " + color_text(32, "Hands Won: " + std::to_string(humanPlayer->GetHandsWon())) + " , " + color_text(31, "Hands Lost: " 
            + std::to_string(humanPlayer->GetHandsLost())) + " , " + color_text(33, "Hands Pushed: " + std::to_string(humanPlayer->GetHandsPushed())) + " , " + color_text(35, "Blackjacks: " + std::to_string(humanPlayer->GetBlackjackHands())) + ".";
            std::cout << std::endl; rolling_text(humanPlayer->GetDisplayName() + " has lost this hand. " + statTracker, PRINT_LINE_SLEEP); std::cout << std::endl;
        }
    }
}

/*  hand_comparison_logic_sim - Compares the hand of a player to that of the dealer and determines if they push, win, or lose
*   Input:
*       humanPlayer - Player object that is passed by reference that resembles a non dealer player
*       dealer - Player object that is passed by reference that resembles a dealer
*   Algorithm:
*       * Iterate all of the players current hands
*       * Process the logic of the individual hand for what the outcome of the current hand is (see inline comments)
*   Output:
*       This function does not return a value, it modifies parameters pertaining to a player
*/
void hand_comparison_logic_sim(std::shared_ptr<Player>& humanPlayer, std::shared_ptr<Player>& dealer) {
    for (int i = 0; i < humanPlayer->GetCurrentHands()->GetSize(); i++) {
        // Player has a hand total of less than or equal to 21
        if (humanPlayer->GetCurrentHands()->RetrieveNode(i)->data->GetCardsTotal() <= 21) {
            // Player and dealer have the same hand total
            if (humanPlayer->GetCurrentHands()->RetrieveNode(i)->data->GetCardsTotal() == dealer->GetCurrentHands()->RetrieveNode(0)->data->GetCardsTotal()) {
                // Player pushes their current hand
                humanPlayer->UpdateBank(humanPlayer->GetCurrentHands()->RetrieveNode(i)->data, 3);
            }
            // Dealer wins
            else if (dealer->GetCurrentHands()->RetrieveNode(0)->data->GetCardsTotal() > humanPlayer->GetCurrentHands()->RetrieveNode(i)->data->GetCardsTotal() && dealer->GetCurrentHands()->RetrieveNode(0)->data->GetCardsTotal() <= 21) {
                // Player loses their current hand
                humanPlayer->UpdateBank(humanPlayer->GetCurrentHands()->RetrieveNode(i)->data, 2);
            }
            // Player wins
            else if (dealer->GetCurrentHands()->RetrieveNode(0)->data->GetCardsTotal() < humanPlayer->GetCurrentHands()->RetrieveNode(i)->data->GetCardsTotal() || dealer->GetCurrentHands()->RetrieveNode(0)->data->GetCardsTotal() > 21) {
                humanPlayer->UpdateBank(humanPlayer->GetCurrentHands()->RetrieveNode(i)->data, 1);
            }
        }
        // Player has a hand total of 21 or greater
        else {
            // Player loses their current hand
            humanPlayer->UpdateBank(humanPlayer->GetCurrentHands()->RetrieveNode(i)->data, 2);
        }
    }
}

/*  player_logic - Processes the possible options of what a player can do on their current hand
*   Input:
*       humanPlayer - Player object that is passed by reference to resemble a non dealer player
*       dealer - Player object that is passed by reference to resemble a dealer
*       shoe - Shoe object that is passed by reference that resembles the current game shoe that is being played with
*   Algorithm:
*       * Check the parameters of the current hand
*       * If the player has not split aces
*           * Create a label indicating what hand is being played with
*           * Process the logic of what a player can do with their hand
*           * Prompt the player if they would like to hit, stand, or double down, given that they can double down
*           * Proceed to process the logic of how the player has played and if they can continue to play their current hand
*           * See individual line comments for more detail
*       * If the player has split aces, simply bypass all options of hitting, standing, and doubling down
*       * Return all hand objects and shoe
*   Output:
*       This function does not return a value, it modifies input parameters
*/
void player_logic(std::shared_ptr<Player>& humanPlayer, std::shared_ptr<Player>& dealer, std::shared_ptr<Shoe>& shoe) {
    // Process the same rank test
    same_rank_check(humanPlayer, dealer, shoe);
    // Player did not split aces
    if (!humanPlayer->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(humanPlayer->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[1][3])) {
        // Iterate over the hands of the player
        for (int i = 0; i < humanPlayer->GetCurrentHands()->GetSize(); i++) {
            // Hit the current hand of the player if it only has one card present
            if (humanPlayer->GetCurrentHands()->RetrieveNode(i)->data->GetPlayerCards()->GetSize() == 1) {
                humanPlayer->GetCurrentHands()->RetrieveNode(i)->data->HitHand(shoe);
            }
            // Clear hash table
            humanPlayer->GetCurrentHands()->RetrieveNode(i)->data->GetHashTable()->ClearHashTable();
            bool invalidInput = false;
            while (humanPlayer->GetCurrentHands()->RetrieveNode(i)->data->GetCardsTotal() < 21) {
                // Check parameters
                humanPlayer->GetCurrentHands()->RetrieveNode(i)->data->ParametersCheck(dealer->GetCurrentHands()->RetrieveNode(0)->data, humanPlayer->GetBankTotal());
                bool canDoubleDown = humanPlayer->GetCurrentHands()->RetrieveNode(i)->data->GetHashTable()->Contains(humanPlayer->GetCurrentHands()->RetrieveNode(i)->data->GetValuesMatrix()[0][1]);
                bool hasHit = humanPlayer->GetCurrentHands()->RetrieveNode(i)->data->GetHashTable()->Contains(humanPlayer->GetCurrentHands()->RetrieveNode(i)->data->GetValuesMatrix()[1][1]);
                // Show current hand if multiple hands or if player has hit
                if (humanPlayer->GetCurrentHands()->GetSize() > 1 || hasHit || invalidInput) {
                    std::cout << std::endl; rolling_text("Here is your current hand and the " + dealer->GetDisplayName() + "'s current hand:", PRINT_LINE_SLEEP); std::cout << std::endl;
                    humanPlayer->ShowCurrentHand(humanPlayer->GetCurrentHands()->RetrieveNode(i)->data, "current", "");
                    dealer->ShowCurrentHand(dealer->GetCurrentHands()->RetrieveNode(0)->data, "initial", "");
                }
                // Prompt player for what they would like to do
                std::string response;
                // Player can double down
                if (canDoubleDown) {
                    std::cout << std::endl; rolling_text("Would you like to " + color_text(32, "Hit") + ", " + color_text(32, "Stand") + ", or " + color_text(32, "Double Down") + " on your current hand?", PRINT_LINE_SLEEP); std::cout << std::endl;
                    blackjack_strategy(humanPlayer, humanPlayer->GetCurrentHands()->RetrieveNode(i)->data, dealer, true, true);
                    std::cout << std::endl; rolling_text("Enter " + color_text(32, "(h)") + " to " + color_text(32, "hit") + ", " + color_text(32, "(s)") + " to " + color_text(32, "stand") + ", or " + color_text(32, "(d)") + " to " + color_text(32, "double down") + ": ", PRINT_LINE_SLEEP);
                }
                // Player cannot double down
                else {
                    std::cout << std::endl; rolling_text("Would you like to " + color_text(32, "Hit") + " or " + color_text(32, "Stand") + " on your current hand?", PRINT_LINE_SLEEP); std::cout << std::endl;
                    blackjack_strategy(humanPlayer, humanPlayer->GetCurrentHands()->RetrieveNode(i)->data, dealer, true, true);
                    std::cout << std::endl; rolling_text("Enter " + color_text(32, "(h)") + " to " + color_text(32, "hit") + " or " + color_text(32, "(s)") + " to " + color_text(32, "stand") + ": ", PRINT_LINE_SLEEP);
                }
                std::cin >> response;
                // Player chose to stand
                if (response == "s") {
                    humanPlayer->GetCurrentHands()->RetrieveNode(i)->data->GetHashTable()->AddToTable(humanPlayer->GetCurrentHands()->RetrieveNode(i)->data->GetValuesMatrix()[1][2]);
                    std::cout << std::endl; rolling_text("You have chosen to " + color_text(32, "stand") + " on your current hand. Here is your final hand and the " + dealer->GetDisplayName() + "'s current hand:", PRINT_LINE_SLEEP); std::cout << std::endl;
                    // Multiple hands
                    humanPlayer->ShowCurrentHand(humanPlayer->GetCurrentHands()->RetrieveNode(i)->data, "final", "");
                    if (humanPlayer->GetCurrentHands()->GetSize() > 1) {
                        dealer->ShowCurrentHand(dealer->GetCurrentHands()->RetrieveNode(0)->data, "initial", "");
                    }
                    // Single hand
                    else {
                        dealer->ShowCurrentHand(dealer->GetCurrentHands()->RetrieveNode(0)->data, "initial", "Show");
                    }
                    break;
                }
                else if (response == "h") {
                    humanPlayer->GetCurrentHands()->RetrieveNode(i)->data->GetHashTable()->AddToTable(humanPlayer->GetCurrentHands()->RetrieveNode(i)->data->GetValuesMatrix()[1][1]);
                    std::cout << std::endl; rolling_text("You have chosen to " + color_text(32, "hit") + " your current hand.", PRINT_LINE_SLEEP); std::cout << std::endl;
                    humanPlayer->GetCurrentHands()->RetrieveNode(i)->data->HitHand(shoe);
                    invalidInput = false;
                    continue;
                }
                else if (response == "d" && canDoubleDown) {
                    humanPlayer->GetCurrentHands()->RetrieveNode(i)->data->GetHashTable()->AddToTable(humanPlayer->GetCurrentHands()->RetrieveNode(i)->data->GetValuesMatrix()[1][0]);
                    humanPlayer->GetCurrentHands()->RetrieveNode(i)->data->GetHashTable()->AddToTable(humanPlayer->GetCurrentHands()->RetrieveNode(i)->data->GetValuesMatrix()[2][0]);
                    std::cout << std::endl; rolling_text("You have chosen to " + color_text(32, "double down") + " on your current hand.", PRINT_LINE_SLEEP); std::cout << std::endl;
                    humanPlayer->UpdateBank(humanPlayer->GetCurrentHands()->RetrieveNode(i)->data, 0);
                    humanPlayer->GetCurrentHands()->RetrieveNode(i)->data->SetWager(2 * (humanPlayer->GetCurrentHands()->RetrieveNode(i)->data->GetWager() - humanPlayer->GetCurrentHands()->RetrieveNode(i)->data->GetInsuranceWager()));
                    humanPlayer->GetCurrentHands()->RetrieveNode(i)->data->HitHand(shoe);
                    break;
                }
                else if (response == "d" && !canDoubleDown) {
                    std::cout << std::endl; rolling_text("You " + color_text(31, "cannot double down") + " on your current hand. Please re-enter a valid choice.", PRINT_LINE_SLEEP); time_sleep(MEDIUM_TIME_SLEEP);
                    invalidInput = true;
                    clear_terminal();
                    continue;
                }
                else {
                    std::cout << std::endl; rolling_text("Please re-enter a valid choice.", PRINT_LINE_SLEEP); time_sleep(MEDIUM_TIME_SLEEP);
                    invalidInput = true;
                    clear_terminal();
                    continue;
                }
            }
            bool hitHand = humanPlayer->GetCurrentHands()->RetrieveNode(i)->data->GetHashTable()->Contains(humanPlayer->GetCurrentHands()->RetrieveNode(i)->data->GetValuesMatrix()[1][1]);
            bool doubledDown = humanPlayer->GetCurrentHands()->RetrieveNode(i)->data->GetHashTable()->Contains(humanPlayer->GetCurrentHands()->RetrieveNode(i)->data->GetValuesMatrix()[2][0]);
            // Display results if player busts or if they hit 21
            if (humanPlayer->GetCurrentHands()->RetrieveNode(i)->data->GetCardsTotal() >= 21) {
                // Player has 21
                if (humanPlayer->GetCurrentHands()->RetrieveNode(i)->data->GetCardsTotal() == 21) {
                    if (hitHand) {
                        std::cout << std::endl; rolling_text("You have " + color_text(32, "hit") + " your current hand and obtained " + color_text(35, "21") + ".", PRINT_LINE_SLEEP); std::cout << std::endl;
                    }
                    else if (doubledDown) {
                        std::cout << std::endl; rolling_text("You have " + color_text(32, "doubled down") + " on your current hand and obtained " + color_text(35, "21") + ".", PRINT_LINE_SLEEP); std::cout << std::endl;
                    }
                }
                // Player busted
                else {
                    if (hitHand) {
                        std::cout << std::endl; rolling_text("You have " + color_text(32, "hit") + " your current hand and " + color_text(35, "busted") + " with a final value of " + humanPlayer->GetCurrentHands()->RetrieveNode(i)->data->GetDisplayCardsTotal() 
                        + ".", PRINT_LINE_SLEEP); std::cout << std::endl;
                    }
                    else if (doubledDown) {
                        std::cout << std::endl; rolling_text("You have " + color_text(32, "doubled down") + " on your current hand and " + color_text(35, "busted") + " with a final value of " + humanPlayer->GetCurrentHands()->RetrieveNode(i)->data->GetDisplayCardsTotal() 
                        + ".", PRINT_LINE_SLEEP); std::cout << std::endl;
                    }
                }
                std::cout << std::endl; rolling_text("Here is your final hand and the " + dealer->GetDisplayName() + "'s current hand:", PRINT_LINE_SLEEP); std::cout << std::endl;
                humanPlayer->ShowCurrentHand(humanPlayer->GetCurrentHands()->RetrieveNode(i)->data, "final", "");
                // Multiple hands
                if (humanPlayer->GetCurrentHands()->GetSize() > 1) {
                    dealer->ShowCurrentHand(dealer->GetCurrentHands()->RetrieveNode(0)->data, "initial", "");
                }
                // Single hand
                else {
                    dealer->ShowCurrentHand(dealer->GetCurrentHands()->RetrieveNode(0)->data, "initial", "Show");
                }
            }
            // Player doubled down and had less than 21
            if (humanPlayer->GetCurrentHands()->RetrieveNode(i)->data->GetCardsTotal() < 21 && doubledDown) {
                std::cout << std::endl; rolling_text("You have " + color_text(32, "doubled down") + " on your current hand and obtained " + humanPlayer->GetCurrentHands()->RetrieveNode(i)->data->GetDisplayCardsTotal() + ".", PRINT_LINE_SLEEP); std::cout << std::endl;
                std::cout << std::endl; rolling_text("Here is your final hand and the " + dealer->GetDisplayName() + "'s current hand:", PRINT_LINE_SLEEP); std::cout << std::endl;
                humanPlayer->ShowCurrentHand(humanPlayer->GetCurrentHands()->RetrieveNode(i)->data, "final", "");
                // Multiple hands
                if (humanPlayer->GetCurrentHands()->GetSize() > 1) {
                    dealer->ShowCurrentHand(dealer->GetCurrentHands()->RetrieveNode(0)->data, "initial", "");
                }
                // Single hand
                else {
                    dealer->ShowCurrentHand(dealer->GetCurrentHands()->RetrieveNode(0)->data, "initial", "Show");
                }
            }
        }
    }
}

/*  player_logic_sim - Processes the possible options of what a player can do on their current hand for a simulated hand
*   Input:
*       humanPlayer - Player object that is passed by reference that resembles a non dealer player
*       dealer - Player object that is passed by reference that resembles a dealer
*       shoe - Shoe object that is passed by reference that resembles the current game shoe that is being played with
*       splitChoice - Boolean value that determines if a player should
*   Algorithm:
*       * Process the logic of the same rank test
*       * If the player has not split aces
*           * Iterate over the hands of the player
*           * Process the logic of what a player can do with their hand
*           * See individual line comments for more detail
*       * If the player has split aces, simply bypass all options of hitting, standing, and doubling down
*   Output:
*       This function does not return a value, it modifies a Player and Shoe object after processing logic
*/
void player_logic_sim(std::shared_ptr<Player>& humanPlayer, std::shared_ptr<Player>& dealer, std::shared_ptr<Shoe>& shoe, bool splitChoice) {
    // Process the same rank test
    same_rank_check_sim(humanPlayer, dealer, shoe, splitChoice);
    // Player did not split aces
    if (!humanPlayer->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(humanPlayer->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[1][3])) {
        // Iterate over the hands of the player
        for (int i = 0; i < humanPlayer->GetCurrentHands()->GetSize(); i++) {
            // Hit the current hand of the player if it only has one card present
            if (humanPlayer->GetCurrentHands()->RetrieveNode(i)->data->GetPlayerCards()->GetSize() == 1) {
                humanPlayer->GetCurrentHands()->RetrieveNode(i)->data->HitHand(shoe);
            }
            while (humanPlayer->GetCurrentHands()->RetrieveNode(i)->data->GetCardsTotal() < 21) {
                humanPlayer->GetCurrentHands()->RetrieveNode(i)->data->GetHashTable()->ClearHashTable();
                // Check the strategy of the current hand for the player
                blackjack_strategy(humanPlayer, humanPlayer->GetCurrentHands()->RetrieveNode(i)->data, dealer, false, true);
                // Player should double down
                if (humanPlayer->GetCurrentHands()->RetrieveNode(i)->data->GetHashTable()->Contains(humanPlayer->GetCurrentHands()->RetrieveNode(i)->data->GetValuesMatrix()[3][0])) {
                    // Add parameters to hash table
                    humanPlayer->GetCurrentHands()->RetrieveNode(i)->data->GetHashTable()->AddToTable(humanPlayer->GetCurrentHands()->RetrieveNode(i)->data->GetValuesMatrix()[1][0]);
                    humanPlayer->GetCurrentHands()->RetrieveNode(i)->data->GetHashTable()->AddToTable(humanPlayer->GetCurrentHands()->RetrieveNode(i)->data->GetValuesMatrix()[2][0]);
                    // Update player bank and wager
                    humanPlayer->UpdateBank(humanPlayer->GetCurrentHands()->RetrieveNode(i)->data, 0);
                    humanPlayer->GetCurrentHands()->RetrieveNode(i)->data->SetWager(2 * (humanPlayer->GetCurrentHands()->RetrieveNode(i)->data->GetWager() - humanPlayer->GetCurrentHands()->RetrieveNode(i)->data->GetInsuranceWager()));
                    humanPlayer->GetCurrentHands()->RetrieveNode(i)->data->HitHand(shoe);
                    break;
                }
                // Player should hit their hand
                if (humanPlayer->GetCurrentHands()->RetrieveNode(i)->data->GetHashTable()->Contains(humanPlayer->GetCurrentHands()->RetrieveNode(i)->data->GetValuesMatrix()[3][1])) {
                    // Add parameters to hash table and hit hand
                    humanPlayer->GetCurrentHands()->RetrieveNode(i)->data->GetHashTable()->AddToTable(humanPlayer->GetCurrentHands()->RetrieveNode(i)->data->GetValuesMatrix()[1][1]);
                    humanPlayer->GetCurrentHands()->RetrieveNode(i)->data->HitHand(shoe);
                    continue;
                }
                // Player should stand their hand
                if (humanPlayer->GetCurrentHands()->RetrieveNode(i)->data->GetHashTable()->Contains(humanPlayer->GetCurrentHands()->RetrieveNode(i)->data->GetValuesMatrix()[3][3])) {
                    // Add parameters to hash table
                    humanPlayer->GetCurrentHands()->RetrieveNode(i)->data->GetHashTable()->AddToTable(humanPlayer->GetCurrentHands()->RetrieveNode(i)->data->GetValuesMatrix()[1][2]);
                    break;
                }
            }
        }
    }
}

/*  plot - Creates a bar chart of data from a csv for a given column in the csv file
*   Input:
*       file - Constant string value that is passed by reference that represents the csv file that is to be plotted
*       yColumn - Integer value that represents the column in the csv file that is to be plotted against 
*   Algorithm:
*       * Create plot titles
*       * Modify the plot titles for the respective column that is being plotted
*       * Create gnuplot object
*       * Process the logic if the file is unable to open
*       * Count the max number of rows in the file
*       * Set the plot properties
*       * Set the axis properties
*       * Send the plot command
*       * Read the data from the csv file
*       * Parse the csv file
*       * Skip the header of the file
*           * Get the corresponding x value (hand number)
*           * Get the corresponding y value (from specified column)
*       * End the data signal from gnuplot
*       * Close the file
*       * Close gnuplot
*   Output:
*       This function does not return a value, it produces a plot of values for a given
*/
void plot(const std::string& file, int yColumn) {
    // Plot titles
    std::string plotTitle;
    std::string xAxisLabel = "Hand Number of Player";
    std::string yAxisLabel;
    std::string legendName;
    // Change plot titles
    if (yColumn == 1) {
        plotTitle = "Individual Hand Wagers of Player";
        legendName = "Hand Wager";
        yAxisLabel = "Hand Wager of Player";
    }
    else if (yColumn == 2) {
        plotTitle = "Individual Hand Nets of Player";
        legendName = "Hand Net";
        yAxisLabel = "Hand Net of Player";
    }
    else if (yColumn == 3) {
        plotTitle = "Individual Cards Total of Player";
        legendName = "Cards Total";
        yAxisLabel = "Hand Cards Total of Player";
    }
    else if (yColumn == 4) {
        plotTitle = "Individual Bank Totals of Player";
        legendName = "Bank Total";
        yAxisLabel = "Hand Bank Totals of Player";
    }
    const char* fileName = file.c_str();
    // Create gnuplot object
    FILE* plt = popen("gnuplot -persist", "w");
    // File failed to open
    if (plt == NULL) {
        std::cerr << "Failed to open a pipe to Gnuplot." << std::endl;
        return;
    }
    // Get max row value
    size_t xMax = row_counter(file);
    // Set plot properties
    fprintf(plt, "set boxwidth 0.25 relative\n");
    fprintf(plt, "set style fill solid\n");
    fprintf(plt, "set grid\n");
    fprintf(plt, "set title \"%s\"\n", plotTitle.c_str());
    // Set axis properties
    fprintf(plt, "set xlabel \"%s\"\n", xAxisLabel.c_str());
    fprintf(plt, "set xrange [0:%lu]\n", xMax);
    fprintf(plt, "set ylabel \"%s\"\n", yAxisLabel.c_str());
    fprintf(plt, "set yrange [0:*]\n");
    // Send the plot command right before sending the data
    fprintf(plt, "plot '-' using 1:2 with boxes title \"%s\"\n", legendName.c_str());
    // Read data from CSV file
    std::ifstream inputFile(fileName);
    if (!inputFile.is_open()) {
        std::cerr << "Failed to open the file." << std::endl;
        pclose(plt);
        return;
    }
    std::string line;
    int lineNumber = 0;
    // Parse the csv file
    while (std::getline(inputFile, line)) {
        lineNumber++;
        // Skip the header of the file
        if (lineNumber > 1) {
            std::istringstream iss(line);
            std::string value;
            double x, y;
            // Get x value (always from first column)
            std::getline(iss, value, ',');
            x = std::stod(value);
            // Get y value (from yColumn)
            for (int i = 1; i < yColumn; i++) {
                std::getline(iss, value, ',');
            }
            if (std::getline(iss, value, ',')) {
                y = std::stod(value);
                fprintf(plt, "%f %f\n", x, y);
            }
        }
    }
    // End of data signal for Gnuplot
    fprintf(plt, "e\n");
    // Close file
    inputFile.close();
    // Close gnuplot
    pclose(plt);
}

/*  row_counter - Counts the number of rows for a given column in a csv file
*   Input:
*       file - Constant string value that is passed by reference that represents the csv file that is going to be parsed
*   Algorithm:
*       * Create the return value for the number of rows that are to be counted
*       * Open the file, output an error if it is unable to open
*       * Parse the csv and count the number of rows in the file
*       * Close the file, return the number of rows that have been calculated
*/
size_t row_counter(const std::string& file) {
    // Create row count variable
    int rowCount = 0;
    // Open the file
    std::ifstream inputFile(file);
    if (!inputFile.is_open()) {
        std::cerr << "Failed to open the file." << std::endl;
        return 1;
    }
    // Parse the csv and count the number of rows
    std::string line;
    while (std::getline(inputFile, line)) {
        rowCount++;
    }
    // Close the file
    inputFile.close();
    // Return the "rowCount" variable
    return rowCount;
}

/*  same_rank_check - Checks to see if the player has the same rank in their hand and if they want to split their hand
*   Input:
*       humanPlayer - Player object that is passed by reference that represents a non dealer player
*       dealer - Player object that represents the hand of a dealer
*       shoe - Shoe object passed by reference that represents the shoe in the game that is being played with
*   Algorithm:
*       * First check if the player is able to split their hand or not
*           * Proceed to check if they can split aces, if they can, prompt them if they would like to and process the logic after that (See inline comments)
*           * Check if they can split other cards than aces, prompt them if they would like to and process the logic after that (See inline comments)
*       * Otherwise, return the values and continue with the logic of the game
*   Output:
*       This function does not return a value
*/
void same_rank_check(std::shared_ptr<Player>& humanPlayer, std::shared_ptr<Player>& dealer, std::shared_ptr<Shoe>& shoe) {
    int maxSplitHands = 5;
    // Check if top hand can be split
    blackjack_strategy(humanPlayer, humanPlayer->GetCurrentHands()->RetrieveNode(0)->data, dealer, false, false);
    // Out of currency check
    bool notEnoughBank = false;
    if (humanPlayer->GetBankTotal() < humanPlayer->GetCurrentHands()->RetrieveNode(0)->data->GetWager()) {
        notEnoughBank = true;
    }
    // Player hand total is less than five total hands
    if (humanPlayer->GetCurrentHands()->GetSize() <= maxSplitHands) {
        bool player_can_split_aces = humanPlayer->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(humanPlayer->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[0][2]);
        bool player_can_split_hand = humanPlayer->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(humanPlayer->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[0][3]);
        bool same_rank_in_hand = humanPlayer->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(humanPlayer->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[2][4]);
        // Player is eligible to split aces
        if (player_can_split_aces && humanPlayer->GetCurrentHandsPossessed() == 1) {
            // Prompt player if they would like to split their hand
            std::cout << std::endl; rolling_text("You currently have the same rank of " + humanPlayer->GetCurrentHands()->RetrieveNode(0)->data->GetPlayerCards()->RetrieveNode(0)->data.GetDisplayRank() + " in your hand. You may only split Ace's once.", PRINT_LINE_SLEEP); std::cout << std::endl;
            blackjack_strategy(humanPlayer, humanPlayer->GetCurrentHands()->RetrieveNode(0)->data, dealer, true, false);
            std::cout << std::endl; rolling_text("Would you like to split your hand? " + color_text(32, "Yes (y)") + " or " + color_text(32, "no (n)") + "? ", PRINT_LINE_SLEEP);
            std::string response;
            std::cin >> response;
            // Player has chosen to split
            if (response == "y") {
                std::cout << std::endl; rolling_text("You have chosen to split your Aces.", PRINT_LINE_SLEEP); std::cout << std::endl;
                // Split hand
                split_hand(humanPlayer);
                humanPlayer->GetCurrentHands()->RetrieveNode(0)->data->HitHand(shoe);
                humanPlayer->GetCurrentHands()->RetrieveNode(0)->data->ParametersCheck(dealer->GetCurrentHands()->RetrieveNode(0)->data, humanPlayer->GetBankTotal());
                humanPlayer->GetCurrentHands()->RetrieveNode(-1)->data->HitHand(shoe);
                humanPlayer->GetCurrentHands()->RetrieveNode(-1)->data->ParametersCheck(dealer->GetCurrentHands()->RetrieveNode(0)->data, humanPlayer->GetBankTotal());
                // Acknowledge that both hands have been split and that they answered yes to splitting hands
                for (int i = 0; i < humanPlayer->GetCurrentHands()->GetSize(); i++) {
                    humanPlayer->GetCurrentHands()->RetrieveNode(i)->data->GetHashTable()->AddToTable(humanPlayer->GetCurrentHands()->RetrieveNode(i)->data->GetValuesMatrix()[4][0]);
                    humanPlayer->GetCurrentHands()->RetrieveNode(i)->data->GetHashTable()->AddToTable(humanPlayer->GetCurrentHands()->RetrieveNode(i)->data->GetValuesMatrix()[1][3]);
                }
                // Display hands of players
                std::cout << std::endl; rolling_text("Here are the current hands of each player.", PRINT_LINE_SLEEP); std::cout << std::endl;
                for (int i = 0; i < humanPlayer->GetCurrentHands()->GetSize(); i++) {
                    humanPlayer->ShowCurrentHand(humanPlayer->GetCurrentHands()->RetrieveNode(i)->data, "Final", "");
                }
                dealer->ShowCurrentHand(dealer->GetCurrentHands()->RetrieveNode(0)->data, "initial", "Show");
                return;
            }
            // Player has chosen to not split
            else {
                std::cout << std::endl; rolling_text("You have chosen to not split your Aces. The hand will continue.", PRINT_LINE_SLEEP); std::cout << std::endl;
                humanPlayer->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->AddToTable(humanPlayer->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[4][0]);
                // Display hands of players
                std::cout << std::endl; rolling_text("Here are the current hands of each player.", PRINT_LINE_SLEEP); std::cout << std::endl;
                for (int i = 0; i < humanPlayer->GetCurrentHands()->GetSize(); i++) {
                    humanPlayer->ShowCurrentHand(humanPlayer->GetCurrentHands()->RetrieveNode(i)->data, "initial", "");
                }
                dealer->ShowCurrentHand(dealer->GetCurrentHands()->RetrieveNode(0)->data, "initial", "");
                return;
            }
        }
        // Player can split normal hand
        else if (player_can_split_hand && humanPlayer->GetCurrentHands()->GetSize() < maxSplitHands) {
            std::string response;
            // This the original hand dealt to player
            if (humanPlayer->GetCurrentHands()->GetSize() == 1) {
                // Prompt player
                std::cout << std::endl; rolling_text("You have the same rank of " + humanPlayer->GetCurrentHands()->RetrieveNode(0)->data->GetPlayerCards()->RetrieveNode(0)->data.GetDisplayRank() 
                + " in your hand. You can split up to " + std::to_string(maxSplitHands - 1) + " times.", PRINT_LINE_SLEEP); std::cout << std::endl;
                blackjack_strategy(humanPlayer, humanPlayer->GetCurrentHands()->RetrieveNode(0)->data, dealer, true, false);
                std::cout << std::endl; rolling_text("Would you like to split your hand? " + color_text(32, "Yes (y)") + " or " + color_text(32, "no (n)") + "? ", PRINT_LINE_SLEEP);
            }
            // This is another hand where they have pulled the same rank
            else {
                // Prompt player
                std::cout << std::endl; rolling_text("You have the same rank of " + humanPlayer->GetCurrentHands()->RetrieveNode(0)->data->GetPlayerCards()->RetrieveNode(0)->data.GetDisplayRank() + " again in your current hand. Total times split: " 
                + std::to_string(humanPlayer->GetCurrentHands()->GetSize() - 1), PRINT_LINE_SLEEP); std::cout << std::endl;
                blackjack_strategy(humanPlayer, humanPlayer->GetCurrentHands()->RetrieveNode(0)->data, dealer, true, false);
                std::cout << std::endl; rolling_text("Would you like to split your hand again? " + color_text(32, "Yes (y)") + " or " + color_text(32, "no (n)") + "? ", PRINT_LINE_SLEEP);
            }
            std::cin >> response;
            // Player has chosen to split
            if (response == "y") {
                // For single hand
                if (humanPlayer->GetCurrentHands()->GetSize() == 1) {
                    std::cout << std::endl; rolling_text("You have chosen to split your hand.", PRINT_LINE_SLEEP); std::cout << std::endl;
                }
                // This is for another hand
                else {
                    std::cout << std::endl; rolling_text("You have chosen to split your current hand again.", PRINT_LINE_SLEEP); std::cout << std::endl;
                }
                // Split hand
                split_hand(humanPlayer);
                // Hit top hand
                humanPlayer->GetCurrentHands()->RetrieveNode(0)->data->HitHand(shoe);
                // Display hands of players
                std::cout << std::endl; rolling_text("Here are the current hands of each player.", PRINT_LINE_SLEEP); std::cout << std::endl;
                for (int i = 0; i < humanPlayer->GetCurrentHands()->GetSize(); i++) {
                    humanPlayer->ShowCurrentHand(humanPlayer->GetCurrentHands()->RetrieveNode(i)->data, "current", "");
                }
                dealer->ShowCurrentHand(dealer->GetCurrentHands()->RetrieveNode(0)->data, "initial", "");
                same_rank_check(humanPlayer, dealer, shoe);
            }
            // Player has chosen to not split their hand
            else {
                // For single hand
                if (humanPlayer->GetCurrentHands()->GetSize() == 1) {
                    std::cout << std::endl; rolling_text("You have chosen to not split your hand.", PRINT_LINE_SLEEP); std::cout << std::endl;
                }
                // This is for another hand
                else {
                    std::cout << std::endl; rolling_text("You have chosen to not split your current hand again.", PRINT_LINE_SLEEP); std::cout << std::endl;
                }
            }
        }
        else {
            // Player has reached max hand count
            if (humanPlayer->GetCurrentHands()->GetSize() == maxSplitHands) {
                std::cout << std::endl; rolling_text("You have reached the max number of hands. You cannot split again.", PRINT_LINE_SLEEP); std::cout << std::endl;
            }
            // Player does not have enough currency in bank left to split again
            else if (humanPlayer->GetCurrentHands()->GetSize() < maxSplitHands && notEnoughBank) {
                if (same_rank_in_hand && humanPlayer->GetCurrentHands()->GetSize() > 1) {
                    std::cout << std::endl; rolling_text("Your current bank total of " + humanPlayer->GetDisplayBankTotal() + " is not greater than the required wager of " 
                    + humanPlayer->GetCurrentHands()->RetrieveNode(0)->data->GetDisplayWager() + " to split again. You cannot split again.", PRINT_LINE_SLEEP); std::cout << std::endl;
                }
                else if (same_rank_in_hand) {
                    std::cout << std::endl; rolling_text("Your current bank total of " + humanPlayer->GetDisplayBankTotal() + " is not greater than the required wager of " 
                    + humanPlayer->GetCurrentHands()->RetrieveNode(0)->data->GetDisplayWager() + " to split. You cannot split.", PRINT_LINE_SLEEP); std::cout << std::endl;
                }
            }
            // Player did not pull the same rank again
            else if ((humanPlayer->GetCurrentHands()->GetSize() > 1) && (humanPlayer->GetCurrentHands()->GetSize() < maxSplitHands) && !notEnoughBank)  {
                std::cout << std::endl; rolling_text("You did not pull the same rank of " + humanPlayer->GetCurrentHands()->RetrieveNode(0)->data->GetPlayerCards()->RetrieveNode(0)->data.GetDisplayRank() + " again. You cannot split your hand again.", PRINT_LINE_SLEEP); std::cout << std::endl;
            }
        }
    }
    // Check parameters of all hands
    if (humanPlayer->GetCurrentHands()->GetSize() > 1) {
        for (int i = 0; i < humanPlayer->GetCurrentHands()->GetSize(); i++) {
            humanPlayer->GetCurrentHands()->RetrieveNode(i)->data->ParametersCheck(humanPlayer->GetCurrentHands()->RetrieveNode(i)->data, humanPlayer->GetBankTotal());
            // Update table of all hands
            humanPlayer->GetCurrentHands()->RetrieveNode(i)->data->GetHashTable()->AddToTable(humanPlayer->GetCurrentHands()->RetrieveNode(i)->data->GetValuesMatrix()[4][1]);
            if (i > 0) {
                humanPlayer->GetCurrentHands()->RetrieveNode(i)->data->GetHashTable()->AddToTable(humanPlayer->GetCurrentHands()->RetrieveNode(i)->data->GetValuesMatrix()[1][4]);
            }
        }
    }
}

/*  same_rank_check_sim - Checks to see if the player has the same rank in their hand and if they want to split their hand
*   Input:
*       humanPlayer - Player object that is passed by reference that represents a non dealer player
*       dealer - Player object that is passed by reference that represents the dealer
*       shoe - Shoe object that is passed by reference that represents the game shoe
*       splitChoice - Boolean value that represents if a player is to split their hand
*   Algorithm:
*       * First check if the player is able to split their hand or not
*       * If player is eligible to split hand, continue to split until they are no longer eligible (see inline comments for more details)
*       * Otherwise, return the values and continue with the logic of the game
*   Output:
*       This function does not return any values, it modifies input parameters after logical checks for it a player can split their hand
*/
void same_rank_check_sim(std::shared_ptr<Player>& humanPlayer, std::shared_ptr<Player>& dealer, std::shared_ptr<Shoe>& shoe, bool splitChoice) {
    int maxSplitHands = 5;
    // Check if top hand can be split
    blackjack_strategy(humanPlayer, humanPlayer->GetCurrentHands()->RetrieveNode(0)->data, dealer, false, false);
    // Player hand total is less than five total hands
    if (humanPlayer->GetCurrentHands()->GetSize() < maxSplitHands) {
        bool player_can_split_aces = humanPlayer->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(humanPlayer->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[0][2]);
        bool player_can_split_hand = humanPlayer->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(humanPlayer->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[0][3]);
        bool player_should_split = humanPlayer->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(humanPlayer->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][2]);
        // Player is eligible to split aces
        if (player_can_split_aces && humanPlayer->GetCurrentHandsPossessed() == 1) {
            // Player has chosen to split
            if (player_should_split) {
                // Split hand
                split_hand(humanPlayer);
                humanPlayer->GetCurrentHands()->RetrieveNode(0)->data->HitHand(shoe);
                humanPlayer->GetCurrentHands()->RetrieveNode(0)->data->ParametersCheck(dealer->GetCurrentHands()->RetrieveNode(0)->data, humanPlayer->GetBankTotal());
                humanPlayer->GetCurrentHands()->RetrieveNode(-1)->data->HitHand(shoe);
                humanPlayer->GetCurrentHands()->RetrieveNode(-1)->data->ParametersCheck(dealer->GetCurrentHands()->RetrieveNode(0)->data, humanPlayer->GetBankTotal());
                // Acknowledge that both hands have been split and that they answered yes to splitting hands
                for (int i = 0; i < humanPlayer->GetCurrentHands()->GetSize(); i++) {
                    humanPlayer->GetCurrentHands()->RetrieveNode(i)->data->GetHashTable()->AddToTable(humanPlayer->GetCurrentHands()->RetrieveNode(i)->data->GetValuesMatrix()[4][0]);
                    humanPlayer->GetCurrentHands()->RetrieveNode(i)->data->GetHashTable()->AddToTable(humanPlayer->GetCurrentHands()->RetrieveNode(i)->data->GetValuesMatrix()[1][3]);
                }
                return;
            }
        }
        // Player can split normal hand
        else if (player_can_split_hand) {
            // Player has chosen to split
            if (player_should_split) {
                // Split hand
                split_hand(humanPlayer);
                // Hit top hand
                humanPlayer->GetCurrentHands()->RetrieveNode(0)->data->HitHand(shoe);
                // Recursive call to function
                same_rank_check_sim(humanPlayer, dealer, shoe, true);
            }
        }
    }
    // Check parameters of all hands
    for (int i = 0; i < humanPlayer->GetCurrentHands()->GetSize(); i++) {
        humanPlayer->GetCurrentHands()->RetrieveNode(i)->data->ParametersCheck(humanPlayer->GetCurrentHands()->RetrieveNode(i)->data, humanPlayer->GetBankTotal());
        humanPlayer->GetCurrentHands()->RetrieveNode(i)->data->GetHashTable()->AddToTable(humanPlayer->GetCurrentHands()->RetrieveNode(i)->data->GetValuesMatrix()[4][1]);
        if (i > 0) {
            humanPlayer->GetCurrentHands()->RetrieveNode(i)->data->GetHashTable()->AddToTable(humanPlayer->GetCurrentHands()->RetrieveNode(i)->data->GetValuesMatrix()[1][4]);
        }
    }
}


/*  split_hand_sim - Splits the current hand of a player and appends the hands to the players private data member "hands"
*   Input:
*       humanPlayer - Player object that represents the players top hand that will be split
*   Algorithm:
*       * Increment the hands currently held variable by one
*       * Update the bank total
*       * Determine how the hand will be split (see inline comments)
*       * Copy variables of each individual hand 
*   Output:
*       This function does not return a value, it appends hands to a current hand's linked list
*/
void split_hand(std::shared_ptr<Player>& humanPlayer) {
    // Get current hands total and increment by 1
    humanPlayer->SetCurrentHandsPossessed();
    // Update the hands bank total
    humanPlayer->UpdateBank(humanPlayer->GetCurrentHands()->RetrieveNode(0)->data, 0);
    // Create new hand object
    std::shared_ptr<Hand> newHand(new Hand);
    // Copy variables of top hand to new hand
    newHand->CopyVariables(humanPlayer->GetCurrentHands()->RetrieveNode(0)->data);
    // Create copy of second card in players current hand to be split
    Card copyCard = humanPlayer->GetCurrentHands()->RetrieveNode(0)->data->GetPlayerCards()->RetrieveNode(-1)->data;
    // Remove the end card of the players current hand
    humanPlayer->GetCurrentHands()->RetrieveNode(0)->data->GetPlayerCards()->RemoveNode(-1);
    // Add removed card to new hand
    std::shared_ptr<Card> tempCard(new Card(copyCard));
    std::shared_ptr<node<Card>> tempCardNode = newHand->GetPlayerCards()->InitNode(tempCard);
    newHand->AddCardToHand(tempCardNode);
    // Add new hand to players hands
    std::shared_ptr<node<std::shared_ptr<Hand>>> newHandNode = humanPlayer->GetCurrentHands()->InitNode(newHand);
    humanPlayer->GetCurrentHands()->InsertNode(newHandNode, 0);
}

// /*  stats_tracker - Updates the stat trackers of a current hand
// *   Input:
// *       input - Hand object passed by reference who's stats are being updated
// *   Algorithm:
// *       * Update hands bank total
// *       * Update hands cards total
// *       * Update hands nets total
// *       * Update hands played total
// *       * Update hands wagers total
// *   Output:
// *       This function does not return a value
// */
// void stats_tracker(std::shared_ptr<Hand>& input) {
//     // Update hands bank total
//     std::shared_ptr<node<float>> bankNode = input->GetHandBankTotals()->InitNode(input->GetBankTotal());
//     input->SetHandBankTotals(bankNode);
//     // Update hands cards total
//     std::shared_ptr<node<int>> cardsTotalNode = input->GetHandCardTotals()->InitNode(input->GetCardsTotal());
//     input->SetHandCardTotals(cardsTotalNode);
//     // Update hands nets total
//     std::shared_ptr<node<float>> netsTotalNode = input->GetHandNets()->InitNode(input->GetNet());
//     input->SetHandNets(netsTotalNode);
//     // Update hands played total
//     std::shared_ptr<node<int>> handsPlayedNode = input->GetHandPlayed()->InitNode(input->GetHandsPlayed());
//     input->SetHandPlayed(handsPlayedNode);
//     // Update hands wagers total
//     std::shared_ptr<node<float>> handWagerNode = input->GetHandWagers()->InitNode(input->GetWager());
//     input->SetHandWagers(handWagerNode);
// }