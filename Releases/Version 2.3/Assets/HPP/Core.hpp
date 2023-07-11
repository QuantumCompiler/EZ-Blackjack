// ----- ----- ----- ----- ----- ----- ----- Includes ----- ----- ----- ----- ----- ----- ----- ----- ----- //
#include "../Headers/Core.h"

/*  Importance of order implementation
*   1 - deal_hand
*   2 - dealer_showing_ace
*   3 - split_hand
*   4 - same_rank_check
*   5 - player_hand_logic
*   6 - dealer_hand_logic
*   7 - hand_comparison_logic
*   8 - game_logic
*   9 - play_game
*   10 - update_stats
*   11 - csv_stats
*   12 - blackjack_strategy
*/

/*  deal_hand - Deals cards to players and shows the hands of each player after the deal
*   Input:
*       playerHand - Hand object passed by reference that represents the users hand
*       dealerHand - Hand object passed by reference that represents the dealers hand
*       inputShoe - Shoe object passed by reference that represents the show of of the game
*   Algorithm:
*       * Request the player place a wager for the hand
*       * Deal cards to a player and dealer
*       * Show the hands of the player and the dealer off of deal
*       * Return the Hand objects and the Shoe object
*   Output:
*       playerHand - Hand object that is modified after having cards added to it
*       dealerHand - Hand object that is modified after having cards added to it
*       inputShoe - Shoe object that is changed after having cards dealt from it
*/
std::tuple<Hand, Hand, Shoe> deal_hand(Hand& playerHand, Hand& dealerHand, Shoe& inputShoe) {
    // Have player place wager
    playerHand.PlaceWager();
    // Deal cards to players
    for (int i = 0; i < 4; i++) {
        if (i % 2 == 0) {
            playerHand.HitHand(inputShoe);
        }
        else if (i % 2 == 1) {
            dealerHand.HitHand(inputShoe);
        }
        else {}
    }
    // Show hands of player
    std::cout << std::endl << "Here are the initial hands of each player: " << std::endl << std::endl; time_sleep(1000);
    playerHand.ShowHand("initial");
    dealerHand.ShowHand("initial","");
    playerHand.ParametersCheck(playerHand, dealerHand);
    return std::make_tuple(playerHand, dealerHand, inputShoe);
}

/*  dealer_showing_ace - Checks to see if the dealer is showing an Ace and if a player has blackjack or not
*   Input:
*       playerHand - Hand object passed by reference that represents the user's hand
*       dealerHand - Hand object passed by reference that represents the dealer's hand
*       inputShoe - Shoe object passed by reference that represents the shoe that is being played with
*   Algorithm:
*       * Deal hands to the players with the "deal_hand" function
*       * Create a boolean value "hand_continue" that keeps track if a hand is to be continued
*       * Proceed to check if the player is able to buy insurance (This is done with the "ParametersCheck" function in "deal_hand")
*       * For each instance, we check if the following is true:
*           * If both players have blackjack, if this is true, payout insurance bets if placed, otherwise just push bets
*           * If dealer has blackjack and player does not, payout insurance bets if placed, otherwise just take bets
*           * If dealer does not have blackjack and player does, take insurance bet, and payout blackjack to player
*           * If neither player has blackjack, take insurance bet if placed, continue hand
*       * In each instance above, we output messages that pertain to each instance and update the player bank accordingly
*       * The "hand_continue" boolean value is updated for each case, depending on what the scenario is
*       * Return values at the end of the if else statements
*   Output:
*       playerHand - Modified Hand object after checking for below cases that represents the players hand
*       dealerHand - Hand object that represents the dealers hand after checking cases
*       inputShoe - Shoe object that represents the game shoe that is being played with
*/
std::tuple<Hand, Hand, Shoe, bool> dealer_showing_ace(Hand& playerHand, Hand& dealerHand, Shoe& inputShoe) {
    // Deal hands to player
    deal_hand(playerHand, dealerHand, inputShoe);
    // Define "hand_continue" boolean value to true
    bool hand_continue = true;
    // Player can buy insruance
    if (playerHand.GetCanBuyInsurance()) {
        // Tell user that the dealer is showing an Ace and ask them if they would like to buy insurance
        std::cout << std::endl << "The " << dealerHand.GetDisplayName() << " is showing an " << dealerHand.GetCards().at(1).GetDisplayRank() << ". " << std::endl; time_sleep(1000);
        playerHand.InsurancePrompt();
        // Output a message telling the user they bought insurance
        if (playerHand.GetChoseBuyInsurance()) {
            std::cout << std::endl << playerHand.GetDisplayName() << " has chosen to buy insurance. Your insurance wager is " << playerHand.GetDisplayInsuranceWager() << "." << std::endl; time_sleep(1000);
        }
        // Output a message telling the user they refused to buy insurance
        else {
            std::cout << std::endl << playerHand.GetDisplayName() << " has chosen to not buy insurance." << std::endl; time_sleep(1000);
        }
        // Both players have blackjack, hand ends
        if (dealerHand.GetHasBlackJack() && playerHand.GetHasBlackJack()) {
            if (playerHand.GetChoseBuyInsurance()) {
                std::cout << std::endl << "Both players have blackjack. " << playerHand.GetDisplayName() << " wins insurance and pushes their original wager. ";
                playerHand.UpdateBank(3, playerHand.GetWager());
                playerHand.UpdateBank(5, playerHand.GetInsuranceWager());
            }
            else {
                std::cout << std::endl << "Both players have blackjack. " << playerHand.GetDisplayName() << " pushes their original wager. ";
                playerHand.UpdateBank(3, playerHand.GetWager());
            }
            std::cout << playerHand.GetDisplayName() << " nets " << playerHand.GetDisplayNet() << " this hand." << std::endl << std::endl; time_sleep(1000);
            std::cout << "Here are the final hands of the players:" << std::endl; time_sleep(1000);
            playerHand.ShowHand("final");
            dealerHand.ShowHand("final", "show");
            hand_continue = false;
            // Update Stats Here
        }
        // Dealer has blackjack, player does not, hand ends
        else if (dealerHand.GetHasBlackJack() && !playerHand.GetHasBlackJack()) {
            if (playerHand.GetChoseBuyInsurance()) {
                std::cout << std::endl << dealerHand.GetDisplayName() << " has blackjack but " << playerHand.GetDisplayName() << " does not. " << playerHand.GetDisplayName()
                << " wins insurance but loses their original wager. ";
                playerHand.UpdateBank(2, playerHand.GetWager());
                playerHand.UpdateBank(5, playerHand.GetInsuranceWager());
            }
            else {
                std::cout << std::endl << dealerHand.GetDisplayName() << " has blackjack but " << playerHand.GetDisplayName() << " does not. " << playerHand.GetDisplayName()
                << " loses their original wager. ";
                playerHand.UpdateBank(2, playerHand.GetWager());
            }
            std::cout << playerHand.GetDisplayName() << " nets " << playerHand.GetDisplayNet() << " this hand." << std::endl << std::endl; time_sleep(1000);
            std::cout << "Here are the final hands of the players:" << std::endl; time_sleep(1000);
            playerHand.ShowHand("final");
            dealerHand.ShowHand("final", "show");
            hand_continue = false;
            // Update Stats Here
        }
        // Dealer does not have blackjack, player does, hand ends
        else if (!dealerHand.GetHasBlackJack() && playerHand.GetHasBlackJack()) {
            if (playerHand.GetChoseBuyInsurance()) {
                std::cout << std::endl << playerHand.GetDisplayName() << " has blackjack and " << dealerHand.GetDisplayName() << " does not. " << playerHand.GetDisplayName()
                << " loses insurance but wins their original wager. ";
                playerHand.UpdateBank(4, playerHand.GetWager());
                playerHand.UpdateBank(2, playerHand.GetInsuranceWager());
            }
            else {
                std::cout << std::endl << playerHand.GetDisplayName() << " has blackjack and " << dealerHand.GetDisplayName() << " does not. " << playerHand.GetDisplayName()
                << " wins their original wager. ";
                playerHand.UpdateBank(4, playerHand.GetWager());
            }
            std::cout << playerHand.GetDisplayName() << " nets " << playerHand.GetDisplayNet() << " this hand." << std::endl << std::endl; time_sleep(1000);
            std::cout << "Here are the final hands of the players:" << std::endl; time_sleep(1000);
            playerHand.ShowHand("final");
            dealerHand.ShowHand("final", "show");
            hand_continue = false;
            // Update Stats Here
        }
        // Neither player has blackjack, hand continues
        else {
            if (playerHand.GetChoseBuyInsurance()) {
                std::cout << std::endl << "Neither player has blackjack. " << playerHand.GetDisplayName() << " loses their insurance wager. The hand will continue." << std::endl << std::endl;
                playerHand.UpdateBank(2, playerHand.GetInsuranceWager());
            }
            else {
                std::cout << std::endl << "Neither player has blackjack. The hand will continue." << std::endl << std::endl; time_sleep(1000);
            }
            std::cout << "Here are the current hands of the players:" << std::endl; time_sleep(1000);
            playerHand.ShowHand("initial");
            dealerHand.ShowHand("initial");
            hand_continue = true;
        }
    }
    // Player is not able to buy insurance
    else {
        // Dealer is showing an Ace but the player does not have enough currency to buy insurance
        if (dealerHand.GetCards().at(1).CheckCardParam(dealerHand.GetCards().at(1).GetRank(), Ranks[0])) {
            if (playerHand.GetBankTotal() < 0.5*playerHand.GetWager()) {
                std::cout << std::endl << "The " << dealerHand.GetDisplayName() << " is showing an " << dealerHand.GetCards().at(1).GetDisplayRank() << " but " << playerHand.GetDisplayName()
                << " does not have enough currency in their bank to purchase insurance." << std::endl; time_sleep(1000);
            }
            else {}
        }
        else {}
        // Both players have blackjack, hand ends
        if (dealerHand.GetHasBlackJack() && playerHand.GetHasBlackJack()) {
            std::cout << std::endl << "Both players have blackjack. " << playerHand.GetDisplayName() << " pushes their original wager. ";
            playerHand.UpdateBank(3, playerHand.GetWager());
            std::cout << playerHand.GetDisplayName() << " nets " << playerHand.GetDisplayNet() << " this hand." << std::endl << std::endl; time_sleep(1000);
            std::cout << "Here are the final hands of the players:" << std::endl; time_sleep(1000);
            playerHand.ShowHand("final");
            dealerHand.ShowHand("final", "show");
            hand_continue = false;
            // Update Stats Here
        }
        // Dealer has blackjack, player does not, hand ends
        else if (dealerHand.GetHasBlackJack() && !playerHand.GetHasBlackJack()) {
            std::cout << std::endl << dealerHand.GetDisplayName() << " has blackjack but " << playerHand.GetDisplayName() << " does not. " << playerHand.GetDisplayName()
            << " loses their original wager. ";
            playerHand.UpdateBank(2, playerHand.GetWager());
            std::cout << playerHand.GetDisplayName() << " nets " << playerHand.GetDisplayNet() << " this hand." << std::endl << std::endl; time_sleep(1000);
            std::cout << "Here are the final hands of the players:" << std::endl; time_sleep(1000);
            playerHand.ShowHand("final");
            dealerHand.ShowHand("final", "show");
            hand_continue = false;
            // Update Stats Here
        }
        // Dealer does not have blackjack, player does, hand ends
        else if (!dealerHand.GetHasBlackJack() && playerHand.GetHasBlackJack()) {
            std::cout << std::endl << playerHand.GetDisplayName() << " has blackjack and " << dealerHand.GetDisplayName() << " does not. " << playerHand.GetDisplayName()
            << " wins their original wager. ";
            playerHand.UpdateBank(4, playerHand.GetWager());
            std::cout << playerHand.GetDisplayName() << " nets " << playerHand.GetDisplayNet() << " this hand." << std::endl << std::endl; time_sleep(1000);
            std::cout << "Here are the final hands of the players:" << std::endl; time_sleep(1000);
            playerHand.ShowHand("final");
            dealerHand.ShowHand("final", "show");
            hand_continue = false;
            // Update Stats Here
        }
        // Neither player has blackjack, hand continues
        else {
            std::cout << std::endl << "Neither player has blackjack. The hand will continue." << std::endl << std::endl; time_sleep(1000);
            std::cout << "Here are the current hands of the players:" << std::endl; time_sleep(1000);
            playerHand.ShowHand("initial");
            dealerHand.ShowHand("initial");
            hand_continue = true;
        }
    }
    return std::make_tuple(playerHand, dealerHand, inputShoe, hand_continue);
}

/*  split_hand - Splits the hand of a current player and produces two new hands for the player
*   Input:
*       input - Hand object passed by reference that represents the original hand of the user
*   Algorithm:
*       * Create a vector of hands that will represent the new hands of the player
*       * Update the bank of the player by withdrawing money from the bank of the player
*       * Append one of the cards from the players original hand, copy the variables, and append the hand to the vector
*   Output:
*       split_hands - This is a vector of hands that represents the new hands of the player
*/
std::vector<Hand> split_hand(Hand& input) {
    // Create a vector of hands for the player
    std::vector<Hand> split_hands;
    // Update the bank of the player
    input.UpdateBank(0, input.GetWager());
    // Append card from players original hand, copy the variables of the input hand, and then add the hand to the vector of new hands
    for (Card& current_card : input.GetCards()) {
        Hand new_hand;
        new_hand.SetCards(current_card);
        new_hand.CopyVariables(input);
        split_hands.push_back(new_hand);
    }
    return split_hands;
}

/*  same_rank_check - Checks to see if the player has the same rank in their hand and if they want to split their hand
*   Input:
*       playerHand - Hand object passed by reference that represents the players hand that is being checked for the below conditions
*       dealerHand - Hand object passed by reference that represents the dealers hand that is being checked against the players
*       shoe - Shoe object passed by reference that represents the shoe in the game that is being played with
*   Algorithm:
*       * First check if the player is able to split their hand or not
*           * Proceed to check if they can split aces, if they can, prompt them if they would like to and process the logic after that (See inline comments)
*           * Check if they can split other cards than aces, prompt them if they would like to and process the logic after that (See inline comments)
*       * Otherwise, return the values and continue with the logic of the game
*   Output:
*       new_hand - Vector of Hand objects, this can either be singular or multiple depending on the checks and choices of the players hand
*       playerHand - Hand object that represents the players hand and variables that originally were fed into the function that are now modified
*       dealerHand - Hand object that represents the dealers hand with all of their variables
*       shoe - Shoe object that represents the shoe that is being played with by the player and dealer
*       hand_count - Integer value that represents that number of individual hands that the player has after this function has completed
*/
std::tuple<std::vector<Hand>, Hand, Hand, Shoe, int> same_rank_check(Hand& playerHand, Hand& dealerHand, Shoe& shoe)
{
    int hand_count = 1;
    std::vector<Hand> new_hand;
    // Check if player can split their hand
    if (playerHand.GetCanSplitAces() || playerHand.GetCanSplitHand()) {
        // Player can split aces
        if (playerHand.GetCanSplitAces()) {
            std::string aces_response;
            while (aces_response.empty()) {
                // Prompt player to enter response to split aces
                std::cout << std::endl << "You have the same rank of " << playerHand.GetCards().at(0).GetDisplayRank() << " in your hand." << std::endl; time_sleep(1000);
                std::cout << std::endl << "Would you like to split your hand? You may only split your hand once." << std::endl; time_sleep(1000);
                // blackjack_strategy(playerHand, dealerHand, false);
                std::cout << std::endl << "Enter (y) for yes and (n) for no: "; time_sleep(1000);
                std::cin >> aces_response; std::cout << std::endl;
                // Player has chosen to split aces
                if (aces_response == "y") {
                    playerHand.SetChoseSplitAces(true);
                    playerHand.SetSplitAcesResponse(true);
                    std::cout << playerHand.GetDisplayName() << " has chosen to split their " << playerHand.GetCards().at(0).GetDisplayRank() << "'s." << std::endl; time_sleep(3000);
                    clear_terminal();
                    std::cout << std::endl << "Here are the current hands of both players: " << std::endl; time_sleep(1000);
                    std::vector<Hand> split_aces = split_hand(playerHand);
                    Hand player_hand_1 = split_aces.at(0);
                    Hand player_hand_2 = split_aces.at(1);
                    player_hand_1.HitHand(shoe);
                    player_hand_2.HitHand(shoe);
                    new_hand.push_back(player_hand_1);
                    new_hand.push_back(player_hand_2);
                    hand_count = 2;
                    int loop_counter = 1;
                    std::string hand_tracker;
                    for (Hand& current_hand : new_hand) {
                        if (loop_counter == 1) {
                            hand_tracker = "first";
                        }
                        else if (loop_counter == 2) {
                            hand_tracker = "second";
                        }
                        else {}
                        current_hand.ShowHand(hand_tracker);
                        loop_counter++;
                    }
                    dealerHand.ShowHand();
                    playerHand.CopyVariables(new_hand.back());
                    return std::make_tuple(new_hand, playerHand, dealerHand, shoe, hand_count);
                }
                // Player has chosen to not split aces
                else if (aces_response == "n") {
                    playerHand.SetChoseSplitAces(false);
                    playerHand.SetSplitAcesResponse(true);
                    std::cout << playerHand.GetDisplayName() << " has chosen not to split their " << playerHand.GetCards().at(0).GetDisplayRank() << "'s." << std::endl; time_sleep(3000);
                    clear_terminal();
                    std::cout << std::endl << "Here are the current hands of both players: " << std::endl; time_sleep(1000);
                    playerHand.ShowHand();
                    dealerHand.ShowHand();
                    new_hand.push_back(playerHand);
                    playerHand.CopyVariables(new_hand.back());
                    return std::make_tuple(new_hand, playerHand, dealerHand, shoe, hand_count);
                }
                // Player has entered an invalid response
                else {
                    std::cout << color_text(31, "Invalid choice") + " of " + color_text(31, aces_response) + ". Plese re-enter your decision." << std::endl; time_sleep(1000);
                    aces_response.clear();
                }
            }
        }
        // Player can split normal hand
        else if (playerHand.GetCanSplitHand()) {
            std::string same_rank_response;
            while (same_rank_response.empty()) {
                // Prompt player to enter response to split hand
                std::cout << std::endl << "You have the same rank of " << playerHand.GetCards().at(0).GetDisplayRank() << " in your hand." << std::endl; time_sleep(1000);
                std::cout << std::endl << "Would you like to split your hand? You can split up to four times." << std::endl; time_sleep(1000);
                // blackjack_strategy(playerHand, dealerHand, false);
                std::cout << std::endl << "Enter (y) for yes and (n) for no: "; time_sleep(1000);
                std::cin >> same_rank_response; std::cout << std::endl; 
                // Player has chosen to split their hand
                if (same_rank_response == "y") {
                    playerHand.SetChoseSplitHand(true);
                    playerHand.SetSplitHandResponse(false);
                    std::cout << playerHand.GetDisplayName() << " has chosen to split their " << playerHand.GetCards().at(0).GetDisplayRank() << "'s." << std::endl; time_sleep(3000);
                    clear_terminal();
                    std::cout << std::endl << "Here are the current hands of both players: " << std::endl; time_sleep(1000);
                    std::vector<Hand> splitHand = split_hand(playerHand);
                    std::vector<Hand> splitHands;
                    std::vector<Hand> tempHands;
                    Hand playerHand1 = splitHand.at(0);
                    Hand playerHand2 = splitHand.at(1);
                    Hand checkingHand;
                    playerHand2.HitHand(shoe);
                    tempHands.push_back(playerHand2);
                    tempHands.push_back(playerHand1);
                    checkingHand = playerHand2;
                    checkingHand.CopyVariables(playerHand2);
                    checkingHand.ParametersCheck(checkingHand, dealerHand);
                    int split_counter = 1;
                    hand_count++;
                    int loop_counter = 1;
                    std::string hand_tracker;
                    for (Hand& current_hand : tempHands) {
                        if (loop_counter == 1) {
                            hand_tracker = "first";
                        }
                        else if (loop_counter == 2) {
                            hand_tracker = "second";
                        }
                        else {}
                        current_hand.ShowHand(hand_tracker);
                        loop_counter++;
                    }
                    dealerHand.ShowHand();
                    // Player can split hand again
                    if (checkingHand.GetCanSplitHand()) {
                        while (split_counter < 4 && checkingHand.GetCanSplitHand()) {
                            std::string split_again;
                            // Prompt player if they want to split again
                            while (split_again != "y" || split_again != "n") {
                                std::cout << std::endl << "You have pulled the same rank of " << checkingHand.GetCards().at(0).GetDisplayRank() << " again." << std::endl; time_sleep(1000);
                                std::cout << std::endl << "Would you like to split your current hand again?" << std::endl; time_sleep(1000);
                                // blackjack_strategy(checking_hand, dealerHand, false);
                                std::cout << std::endl << "Enter (y) for yes and (n) for no: "; time_sleep(1000);
                                std::cin >> split_again; std::cout << std::endl;
                                if (split_again == "y") {
                                    split_counter++;
                                    hand_count++;
                                    std::vector<Hand> new_split = split_hand(checkingHand);
                                    Hand newPlayerHand1 = new_split.at(0);
                                    Hand newPlayerHand2 = new_split.at(1);
                                    newPlayerHand2.HitHand(shoe);
                                    splitHands.insert(splitHands.begin(), newPlayerHand1);
                                    checkingHand = newPlayerHand2;
                                    checkingHand.CopyVariables(newPlayerHand2);
                                    checkingHand.ParametersCheck(checkingHand, dealerHand);
                                    break;
                                }
                                else if (split_again == "n") {
                                    break;
                                }
                                else {
                                    std::cout << color_text(31, "Invalid Entry") << ". Please enter a valid choice." << std::endl; time_sleep(1000);
                                    split_again.clear();
                                }
                            }
                            splitHands.insert(splitHands.begin(), checkingHand);
                            splitHands.insert(splitHands.end(), playerHand1);
                            for (int i = 0; i < splitHands.size(); i++) {
                                splitHands.at(i).CopyVariables(checkingHand);
                            }
                            // Player has chosen to split their hand again
                            if (checkingHand.GetCanSplitHand() && split_again == "y") {
                                // Player is eligible to split their hand again
                                if (split_counter < 4 && checkingHand.GetCanSplitHand()) {
                                    std::cout << playerHand.GetDisplayName() << " has chosen to split their hand again." << std::endl; time_sleep(1000);
                                    std::cout << std::endl << "Total times split: " << color_text(31, std::to_string(split_counter)) << ". Your current hand(s) are:" << std::endl; time_sleep(1000);
                                    int loop_counter = 1;
                                    std::string hand_tracker;
                                    for (Hand& current_hand : splitHands) {
                                        if (loop_counter == 1) {
                                            hand_tracker = "first";
                                        }
                                        else if (loop_counter == 2) {
                                            hand_tracker = "second";
                                        }
                                        else if (loop_counter == 3) {
                                            hand_tracker = "third";
                                        }
                                        else if (loop_counter == 4) {
                                            hand_tracker = "fourth";
                                        }
                                        else {
                                            hand_tracker = "current";
                                        }
                                        current_hand.ShowHand(hand_tracker);
                                        loop_counter++;
                                    }
                                    splitHands.erase(splitHands.begin());
                                    splitHands.pop_back();
                                    continue;
                                }
                                // Player cannot split their hand again
                                else if (split_counter == 4 || !checkingHand.GetCanSplitHand()) {
                                    checkingHand.CheckSameParamInHand("R");
                                    // Max split count has occurred 
                                    if (split_counter == 4) {
                                        std::cout << playerHand.GetDisplayName() << " has reached the max amount of times to split. You can no longer split your hands." << std::endl; time_sleep(1000);
                                        std::cout << std::endl << "Total times split: " << color_text(31, std::to_string(split_counter)) << ". The current hands of each player are:" << std::endl; time_sleep(1000);
                                        int loop_counter = 1;
                                        std::string hand_tracker;
                                        for (Hand& current_hand : splitHands) {
                                            if (loop_counter == 1) {
                                                hand_tracker = "first";
                                            }
                                            else if (loop_counter == 2) {
                                                hand_tracker = "second";
                                            }
                                            else if (loop_counter == 3) {
                                                hand_tracker = "third";
                                            }
                                            else if (loop_counter == 4) {
                                                hand_tracker = "fourth";
                                            }
                                            else if (loop_counter == 5) {
                                                hand_tracker = "fifth";
                                            }
                                            else {
                                                hand_tracker = "current";
                                            }
                                            current_hand.ShowHand(hand_tracker);
                                            loop_counter++;
                                        }
                                        dealerHand.ShowHand();
                                    }
                                    // Player is ineligible to split hand again
                                    else if (!checkingHand.GetCanSplitHand()) {
                                        checkingHand.CheckSameParamInHand("R");
                                        // Player does not have the currency to split again
                                        if (checkingHand.GetBankTotal() < checkingHand.GetWager())  {
                                            std::cout << "You pulled the same rank of " << checkingHand.GetCards().at(0).GetDisplayRank() << " again but you do not have enough currency to continue splitting. You can no longer split your hands." << std::endl; time_sleep(1000);
                                            std::cout << std::endl << "Total times split: " << color_text(31, std::to_string(split_counter)) << ". The current hands of each player are:" << std::endl; time_sleep(1000);
                                        }
                                        // Player did not pull the same rank again
                                        else if (!checkingHand.GetSameParamInHand()) {
                                            std::cout << "You did not pull the same rank of " << checkingHand.GetCards().at(0).GetDisplayRank() << " again. You can no longer split your hands." << std::endl; time_sleep(1000);
                                            std::cout << std::endl << "Total times split: " << color_text(31, std::to_string(split_counter)) << ". The current hands of each player are:" << std::endl; time_sleep(1000);
                                        }
                                        else {}
                                        int loop_counter = 1;
                                        std::string hand_tracker;
                                        for (Hand& current_hand : splitHands) {
                                            if (loop_counter == 1) {
                                                hand_tracker = "first";
                                            }
                                            else if (loop_counter == 2) {
                                                hand_tracker = "second";
                                            }
                                            else if (loop_counter == 3) {
                                                hand_tracker = "third";
                                            }
                                            else if (loop_counter == 4) {
                                                hand_tracker = "fourth";
                                            }
                                            else {
                                                hand_tracker = "current";
                                            }
                                            current_hand.ShowHand(hand_tracker);
                                            loop_counter++;
                                        }
                                        dealerHand.ShowHand();
                                    }
                                    else {}
                                    break;
                                }
                                else {}
                            }
                            // Player has chosen to not split their hand again or can't
                            else if (!checkingHand.GetCanSplitHand() || split_again == "n") {
                                checkingHand.CheckSameParamInHand("R");
                                // Player cannot split their hand again
                                if (!checkingHand.GetCanSplitHand()) {
                                    // Player doesn't have the currency to split their hand again
                                    if (checkingHand.GetBankTotal() < checkingHand.GetWager()) {
                                        std::cout << "You pulled the same rank of " << checkingHand.GetCards().at(0).GetDisplayRank() << " again but you do not have enough currency to continue splitting. You can no longer split your hands." << std::endl; time_sleep(1000);
                                        std::cout << std::endl << "Total times split: " << color_text(31, std::to_string(split_counter)) << ". The current hands of each player are:" << std::endl; time_sleep(1000);
                                    }
                                    // Player did not pull the same rank again
                                    else if (!checkingHand.GetSameParamInHand()) {
                                        std::cout << "You did not pull the same rank of " << checkingHand.GetCards().at(0).GetDisplayRank() << " again. You can no longer split your hands." << std::endl; time_sleep(1000);
                                        std::cout << std::endl << "Total times split: " << color_text(31, std::to_string(split_counter)) << ". The current hands of each player are:" << std::endl; time_sleep(1000);
                                    }
                                    else {}
                                    int loop_counter = 1;
                                    std::string hand_tracker;
                                    for (Hand& current_hand : splitHands) {
                                        if (loop_counter == 1) {
                                            hand_tracker = "first";
                                        }
                                        else if (loop_counter == 2) {
                                            hand_tracker = "second";
                                        }
                                        else if (loop_counter == 3) {
                                            hand_tracker = "third";
                                        }
                                        else if (loop_counter == 4) {
                                            hand_tracker = "fourth";
                                        }
                                        else {
                                            hand_tracker = "current";
                                        }
                                        current_hand.ShowHand(hand_tracker);
                                        loop_counter++;
                                    }
                                    dealerHand.ShowHand();
                                }
                                // Player has chosen to not split their hand
                                else if (split_again == "n") {
                                    std::cout << playerHand.GetDisplayName() << " has chosen not to split their hand again." << std::endl; time_sleep(1000);
                                    std::cout << std::endl << "Total times split: " << color_text(31, std::to_string(split_counter)) << ". The current hands of each player are:" << std::endl; time_sleep(1000);
                                    int loop_counter = 1;
                                    std::string hand_tracker;
                                    for (Hand &current_hand : splitHands) {
                                        if (loop_counter == 1) {
                                            hand_tracker = "first";
                                        }
                                        else if (loop_counter == 2) {
                                            hand_tracker = "second";
                                        }
                                        else if (loop_counter == 3) {
                                            hand_tracker = "third";
                                        }
                                        else if (loop_counter == 4) {
                                            hand_tracker = "fourth";
                                        }
                                        else {
                                            hand_tracker = "current";
                                        }
                                        current_hand.ShowHand(hand_tracker);
                                        loop_counter++;
                                    }
                                    dealerHand.ShowHand();
                                }
                                else {}
                                break;
                            }
                        }                        
                    }
                    // Player can't split hand again
                    else if (!checkingHand.GetCanSplitHand()) {
                        checkingHand.CheckSameParamInHand("R");
                        // Player doesn't have the currency to split again
                        if (checkingHand.GetSameParamInHand()) {
                            std::cout << "You pulled the same rank of " << checkingHand.GetCards().at(0).GetDisplayRank() << " again but you do not have enough currency to continue splitting. You can no longer split your hands." << std::endl; time_sleep(1000);
                            std::cout << std::endl << "Total times split: " << color_text(31, std::to_string(split_counter)) << ". The current hands of each player are:" << std::endl; time_sleep(1000);
                            int loop_counter = 1;
                            std::string hand_tracker;
                            for (Hand& current_hand : tempHands)
                            {
                                if (loop_counter == 1) {
                                    hand_tracker = "first";
                                }
                                else if (loop_counter == 2) {
                                    hand_tracker = "second";
                                }
                                else {
                                    hand_tracker = "current";
                                }
                                current_hand.ShowHand(hand_tracker);
                                loop_counter++; 
                            }
                            dealerHand.ShowHand();
                            new_hand = tempHands;
                            playerHand.CopyVariables(new_hand.back());
                            return std::make_tuple(new_hand, playerHand, dealerHand, shoe, hand_count);
                        }
                        // Player did not pull the same card again
                        else {
                            std::cout << "You did not pull the same rank of " << checkingHand.GetCards().at(0).GetDisplayRank() << " again. You can no longer split your hands." << std::endl; time_sleep(1000);
                            std::cout << std::endl << "Total times split: " << color_text(31, std::to_string(split_counter)) << ". The current hands of each player are:" << std::endl; time_sleep(1000);
                            int loop_counter = 1;
                            std::string hand_tracker;
                            for (Hand& current_hand : tempHands) {
                                if (loop_counter == 1) {
                                    hand_tracker = "first";
                                }
                                else if (loop_counter == 2) {
                                    hand_tracker = "second";
                                }
                                else {
                                    hand_tracker = "current";
                                }
                                current_hand.ShowHand(hand_tracker);
                                loop_counter++; 
                            }
                            dealerHand.ShowHand();
                            new_hand = tempHands;
                            playerHand.CopyVariables(new_hand.back());
                            return std::make_tuple(new_hand, playerHand, dealerHand, shoe, hand_count);
                        }
                    }
                    else {}
                }
                // Player has chosen to not split their hand
                else if (same_rank_response == "n") {
                    playerHand.SetChoseSplitHand(false);
                    playerHand.SetSplitHandResponse(true);
                    std::cout << playerHand.GetDisplayName() << " has chosen not to split their " << playerHand.GetCards().at(0).GetDisplayRank() << "'s." << std::endl; time_sleep(3000);
                    clear_terminal();
                    std::cout << std::endl << "Here are the current hands of both players: " << std::endl; time_sleep(1000);
                    playerHand.ShowHand();
                    dealerHand.ShowHand();
                    new_hand.push_back(playerHand);
                    playerHand.CopyVariables(new_hand.back());
                    return std::make_tuple(new_hand, playerHand, dealerHand, shoe, hand_count);
                }
                // Player has entered an invalid response
                else {
                    std::cout << color_text(31, "Invalid choice") + " of " + color_text(31, same_rank_response) + ". Plese re-enter your decision." << std::endl; time_sleep(1000);
                    same_rank_response.clear();
                }
                return std::make_tuple(new_hand, playerHand, dealerHand, shoe, hand_count);
            }
        }
        else {}
    }
    else {
        new_hand.push_back(playerHand);
        playerHand.CopyVariables(new_hand.back());
        return std::make_tuple(new_hand, playerHand, dealerHand, shoe, hand_count);
    }
}

std::tuple<Hand, Hand, Shoe> player_hand_logic(Hand& playerHand, Hand& dealerHand, Hand& referenceHand, Shoe& shoe, int& hand_counter) {

}
// {
//     if (!referenceHand.player.chose_split_aces) 
//     {
//         std::string response;
//         std::string hand_tracker;
//         if (hand_counter == 1)
//         {
//             hand_tracker = "first";
//         }
//         else if (hand_counter == 2)
//         {
//             hand_tracker = "second";
//         }
//         else if (hand_counter == 3)
//         {
//             hand_tracker = "third";
//         }
//         else if (hand_counter == 4)
//         {
//             hand_tracker = "fourth";
//         }
//         else if (hand_counter == 5)
//         {
//             hand_tracker = "fifth";
//         }
//         else
//         {
//             hand_tracker = "current";
//         }
//         if (hand_counter > 1)
//         {
//             playerHand.Hit(shoe);
//         }
//         else {}
//         while ((response != "h" && response != "s" && response != "d") && playerHand.player.cards_total < 21)
//         {
//             if (!playerHand.player.has_hit)
//             {
//                 if (referenceHand.player.chose_split_hand)
//                 {
//                     std::cout << std::endl << "Here are the initial hands of each player for hand " << std::to_string(hand_counter) << ":" << std::endl; 
//                     playerHand.Show_Hand("initial " + hand_tracker);
//                     dealerHand.Show_Hand("initial");
//                     std::cout << std::endl << "Would you like to hit, stand, or double down for hand " << std::to_string(hand_counter) << "?" << std::endl; 
//                     blackjack_strategy(playerHand, dealerHand, true);
//                     std::cout << std::endl << "Enter (h) to hit, (s) to stand, and (d) to double down for " << std::to_string(hand_counter) << ": ";
//                     std::cin >> response;
//                     std::cout << std::endl;
//                 }
//                 else if (!referenceHand.player.chose_split_hand)
//                 {
//                     std::cout << std::endl << "Would you like to hit, stand, or double down?" << std::endl; 
//                     blackjack_strategy(playerHand, dealerHand, true);
//                     std::cout << std::endl << "Enter (h) to hit, (s) to stand, and (d) to double down: ";
//                     std::cin >> response;
//                     std::cout << std::endl;
//                 }
//                 else {}            
//             }
//             else if (playerHand.player.has_hit)
//             {
                
//                 if (referenceHand.player.chose_split_hand)
//                 {
//                     playerHand.Show_Hand("current " + hand_tracker);
//                 }
//                 else if (!referenceHand.player.chose_split_hand)
//                 {
//                     playerHand.Show_Hand("current");
//                 }
//                 else {}
//                 dealerHand.Show_Hand("initial");
//                 std::cout << std::endl << "Would you like to hit (h) or stand (s)?" << std::endl; 
//                 blackjack_strategy(playerHand, dealerHand, true);
//                 std::cout << std::endl << "Enter (h) to hit and (s) to stand: ";
//                 std::cin >> response;
//                 std::cout << std::endl;
//             }
//             else {}
//             if (response == "h")
//             {
//                 playerHand.player.has_hit = true;
//                 playerHand.Hit(shoe);
//                 if (playerHand.player.cards_total > 21)
//                 {
//                     std::cout << playerHand.player.display_name << " has chosen to hit and busted. Final hand total: " << playerHand.player.display_cards_total << "." << std::endl; 
//                     if (referenceHand.player.chose_split_hand)
//                     {
//                         std::cout << std::endl << "Here is " << playerHand.player.display_name << "'s final hand for hand " << std::to_string(hand_counter)
//                         << " and the " << dealerHand.player.display_name << "'s current hand:" << std::endl; 
//                         playerHand.Show_Hand("final " + hand_tracker);
//                         dealerHand.Show_Hand("current");
//                     }
//                     else if (!referenceHand.player.chose_split_hand)
//                     {
//                         std::cout << std::endl << "Here is the final hand for " << playerHand.player.display_name << " and the final hand of the " << dealerHand.player.display_name << ":" << std::endl; 
//                         playerHand.Show_Hand("final");
//                         dealerHand.Show_Hand("final", "show");
//                     }
//                     else {}
//                     std::cout << std::endl;
                    
//                     break;
//                 }
//                 else if (playerHand.player.cards_total < 21)
//                 {
//                     std::cout << playerHand.player.display_name << " has chosen to hit. Current hand total: " << playerHand.player.display_cards_total << "." << std::endl; 
//                     if (referenceHand.player.chose_split_hand)
//                     {
//                         std::cout << std::endl << "Here are the current hands of each player for hand " << std::to_string(hand_counter) << ":" << std::endl;
//                     }
//                     else if (!referenceHand.player.chose_split_hand)
//                     {
//                         std::cout << std::endl << "Here are the current hands of each player:" << std::endl;
//                     }
//                     else {}
//                 }
//                 else if (playerHand.player.cards_total == 21)
//                 {
//                     std::cout << playerHand.player.display_name << " has chosen to hit. Final hand total: " << playerHand.player.display_cards_total << "." << std::endl; 
//                     if (referenceHand.player.chose_split_hand)
//                     {
//                         std::cout << std::endl << "Here is " << playerHand.player.display_name << "'s final hand for hand " << std::to_string(hand_counter) << " and the " 
//                         << dealerHand.player.display_name << "'s current hand:" << std::endl; 
//                         playerHand.Show_Hand("final " + hand_tracker);
//                         dealerHand.Show_Hand("current", "");
//                     }
//                     else if (!referenceHand.player.chose_split_hand)
//                     {
//                         std::cout << std::endl << "Here is the final hand for " << playerHand.player.display_name << " and the initial hand of the " 
//                         << dealerHand.player.display_name << ":" << std::endl; 
//                         playerHand.Show_Hand("final");
//                         dealerHand.Show_Hand("initial", "show");
//                     }
//                     else
//                     std::cout << std::endl;
                    
//                 }
//                 else {}
//                 response.clear();
//             }
//             else if (response == "s")
//             {
//                 std::cout << playerHand.player.display_name << " has chosen to stand. Final hand total: " << playerHand.player.display_cards_total << "." << std::endl; 
//                 if (referenceHand.player.chose_split_hand)
//                 {
//                     std::cout << std::endl << "Here is " << playerHand.player.display_name << "'s final hand for hand " << std::to_string(hand_counter)
//                     << " and the " << dealerHand.player.display_name << "'s current hand:" << std::endl; 
//                     playerHand.Show_Hand("final " + hand_tracker);
//                     dealerHand.Show_Hand("current", "");
//                 }
//                 else if (!referenceHand.player.chose_split_hand)
//                 {
//                     std::cout << std::endl << "Here is the final hand for " << playerHand.player.display_name << " and the initial hand of the " 
//                     << dealerHand.player.display_name << ":" << std::endl; 
//                     playerHand.Show_Hand("final");
//                     dealerHand.Show_Hand("initial", "show");
//                 }
//                 else
//                 std::cout << std::endl;
                
//                 break;
//             }
//             else if (response == "d" && !playerHand.player.has_hit)
//             {
//                 if (playerHand.player.bank_total >= playerHand.player.wager)
//                 {
//                     playerHand.player.bank_total -= playerHand.player.wager;
//                     playerHand.player.wager *= 2;
//                     playerHand.Hit(shoe);
//                     if (playerHand.player.cards_total > 21)
//                     {
//                         playerHand.Update_Bank("L", playerHand, playerHand.player.wager);
//                         std::cout << playerHand.player.display_name << " has doubled down and busted. Final hand total: " 
//                         << playerHand.player.display_cards_total << "." << std::endl; 
//                         if (referenceHand.player.chose_split_hand)
//                         {
//                             std::cout << std::endl << "Here is " << playerHand.player.display_name << "'s final hand for hand " << std::to_string(hand_counter)
//                             << " and the " << dealerHand.player.display_name << "'s current hand:" << std::endl; 
//                             playerHand.Show_Hand("final " + hand_tracker);
//                             dealerHand.Show_Hand("current");
//                         }
//                         else if (!referenceHand.player.chose_split_hand)
//                         {
//                             std::cout << std::endl << "Here is the final hand for " << playerHand.player.display_name << " and the final hand of the " 
//                             << dealerHand.player.display_name << ":" << std::endl; 
//                             playerHand.Show_Hand("final");
//                             dealerHand.Show_Hand("final", "show");
//                         }
//                         else
//                         std::cout << std::endl;
                        
//                         break;
//                     }
//                     else if (playerHand.player.cards_total <= 21)
//                     {
//                         std::cout << playerHand.player.display_name << " has doubled down. Final hand total: " << playerHand.player.display_cards_total << "." << std::endl; 
//                         if (referenceHand.player.chose_split_hand)
//                         {
//                             std::cout << std::endl << "Here is " << playerHand.player.display_name << "'s final hand for hand " << std::to_string(hand_counter) << " and the " 
//                             << dealerHand.player.display_name << "'s current hand:" << std::endl; 
//                             playerHand.Show_Hand("final " + hand_tracker);
//                             dealerHand.Show_Hand("current");
//                         }
//                         else if (!referenceHand.player.chose_split_hand)
//                         {
//                             std::cout << std::endl << "Here is the final hand for " << playerHand.player.display_name << " and the initial hand of the " 
//                             << dealerHand.player.display_name << ":" << std::endl; 
//                             playerHand.Show_Hand("final");
//                             dealerHand.Show_Hand("initial", "show");
//                         }
//                         else {}
//                         std::cout << std::endl;
                        
//                         break;
//                     }
//                     else {}
//                 }
//                 else if (playerHand.player.bank_total < playerHand.player.wager)
//                 {
//                     std::cout << "Your current bank total of " << playerHand.player.display_bank_total << " is not greater than your wager of "
//                     << playerHand.player.display_wager << ". You cannot double down." << std::endl;
//                     response.clear();
//                     continue;
//                 }
//                 else {}
//             }
//             else if (response != "h" && response != "s" && response != "d")
//             {
//                 if (!referenceHand.player.chose_split_hand)
//                 {
//                     std::cout << color_text(31, "Invalid choice") << "." << std::endl; 
//                 }
//                 else if (referenceHand.player.chose_split_hand)
//                 {
//                     std::cout << color_text(31, "Invalid choice") << "." << std::endl << std::endl; 
//                 }
//                 else {}            
//                 response.clear();
//                 continue;
//             }
//             else {}
//         }
//         referenceHand.Copy_Variables(playerHand);
//         return std::make_tuple(playerHand, dealerHand, referenceHand, shoe);
//     }
//     else if (referenceHand.player.chose_split_aces) {
//         referenceHand.Copy_Variables(playerHand);
//         return std::make_tuple(playerHand, dealerHand, referenceHand, shoe);
//     }
//     else {}
// }

void test_game() {
    Hand playerTest;
    Hand dealerTest;
    Shoe testShoe;
    playerTest.SetName("Player 1");
    dealerTest.SetName("Dealer");
}