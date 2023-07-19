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
std::tuple<std::vector<Hand>, Hand, Hand, Shoe, int> same_rank_check(Hand& playerHand, Hand& dealerHand, Shoe& shoe) {
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
                }
                // Player has chosen to not split aces
                else if (aces_response == "n") {
                    playerHand.SetChoseSplitAces(false);
                    playerHand.SetSplitAcesResponse(true);
                    std::cout << playerHand.GetDisplayName() << " has chosen not to split their " << playerHand.GetCards().at(0).GetDisplayRank() << "'s." << std::endl; time_sleep(3000);
                    std::cout << std::endl << "Here are the current hands of both players: " << std::endl; time_sleep(1000);
                    playerHand.ShowHand();
                    dealerHand.ShowHand();
                    new_hand.push_back(playerHand);
                    playerHand.CopyVariables(new_hand.back());
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
                    playerHand.SetSplitHandResponse(true);
                    std::cout << playerHand.GetDisplayName() << " has chosen to split their " << playerHand.GetCards().at(0).GetDisplayRank() << "'s." << std::endl; time_sleep(3000);
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
                                if (split_counter < 4) {
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
                                // Player cannot split their hand again due to max splits
                                else if (split_counter == 4) {
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
                                        dealerHand.ShowHand();
                                    }
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
                                        std::cout << std::endl << "You pulled the same rank of " << checkingHand.GetCards().at(0).GetDisplayRank() << " again but you do not have enough currency to continue splitting. You can no longer split your hands." << std::endl; time_sleep(1000);
                                        std::cout << std::endl << "Total times split: " << color_text(31, std::to_string(split_counter)) << ". The current hands of each player are:" << std::endl; time_sleep(1000);
                                    }
                                    // Player did not pull the same rank again
                                    else if (!checkingHand.GetSameParamInHand()) {
                                        std::cout << std::endl << "You did not pull the same rank of " << checkingHand.GetCards().at(0).GetDisplayRank() << " again. You can no longer split your hands." << std::endl; time_sleep(1000);
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
                        // Assign new_hand to splitHands
                        new_hand = splitHands;
                    }
                    // Player can't split hand again
                    else if (!checkingHand.GetCanSplitHand()) {
                        checkingHand.CheckSameParamInHand("R");
                        // Player doesn't have the currency to split again
                        if (checkingHand.GetSameParamInHand()) {
                            std::cout << std::endl << "You pulled the same rank of " << checkingHand.GetCards().at(0).GetDisplayRank() << " again but you do not have enough currency to continue splitting. You can no longer split your hands." << std::endl; time_sleep(1000);
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
                        }
                        // Player did not pull the same card again
                        else {
                            std::cout << std::endl << "You did not pull the same rank of " << checkingHand.GetCards().at(0).GetDisplayRank() << " again. You can no longer split your hands." << std::endl; time_sleep(1000);
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
                        }
                        // Assign new_hand to tempHands
                        new_hand = tempHands;
                    }
                    else {}
                    playerHand.CopyVariables(new_hand.back());
                }
                // Player has chosen to not split their hand
                else if (same_rank_response == "n") {
                    playerHand.SetChoseSplitHand(false);
                    playerHand.SetSplitHandResponse(true);
                    std::cout << playerHand.GetDisplayName() << " has chosen not to split their " << playerHand.GetCards().at(0).GetDisplayRank() << "'s." << std::endl; time_sleep(3000);
                    std::cout << std::endl << "Here are the current hands of both players: " << std::endl; time_sleep(1000);
                    playerHand.ShowHand();
                    dealerHand.ShowHand();
                    new_hand.push_back(playerHand);
                    playerHand.CopyVariables(new_hand.back());
                }
                // Player has entered an invalid response
                else {
                    std::cout << color_text(31, "Invalid choice") + " of " + color_text(31, same_rank_response) + ". Please re-enter your decision." << std::endl; time_sleep(1000);
                    same_rank_response.clear();
                }
            }
        }
        else {}
    }
    else {
        new_hand.push_back(playerHand);
        playerHand.CopyVariables(new_hand.back());
    }
    return std::make_tuple(new_hand, playerHand, dealerHand, shoe, hand_count);
}

/*  player_hand_logic - Processes the possible options of what a player can do on their current hand
*   Input:
*       currentPlayerHand - Hand object that is passed by reference to be the current hand that is being played with
*       dealerHand - Hand object that is passed by reference that resembles the dealers hand
*       masterPlayerHand - Hand object that is passed by reference that resembles the players original hand
*       shoe - Shoe object that is passed by reference that resembles the current game shoe that is being played with
*       hand_counter - Integer value that represents the current hand of a player out of their total hands
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
*       currentPlayerHand - Returns the current player hand that is being played with
*       dealerHand - Returns the dealers hand
*       shoe - Returns the modified shoe object that is being used for the players to play with
*/
std::tuple<Hand, Hand, Shoe> player_hand_logic(Hand& currentPlayerHand, Hand& dealerHand, Hand& masterPlayerHand, Shoe& shoe, int& hand_counter) {
    // Check the parameters of the given hand
    currentPlayerHand.ParametersCheck(currentPlayerHand, dealerHand);
    // Player did not split Aces
    if (!masterPlayerHand.GetChoseSplitAces()) {
        // Correctly label the current hand of the player
        std::string response;
        std::string hand_tracker;
        if (hand_counter == 1) {
            hand_tracker = "first";
        }
        else if (hand_counter == 2) {
            hand_tracker = "second";
        }
        else if (hand_counter == 3) {
            hand_tracker = "third";
        }
        else if (hand_counter == 4) {
            hand_tracker = "fourth";
        }
        else if (hand_counter == 5) {
            hand_tracker = "fifth";
        }
        else {
            hand_tracker = "current";
        }
        if (hand_counter > 1) {
            currentPlayerHand.HitHand(shoe);
        }
        else {}
        // Process the logic of if a player needs to be prompted for what they should do in a hand
        while ((response != "h" && response != "s" && response != "d") && currentPlayerHand.GetCardsTotal() < 21) {
            // Prompts for if the player has not hit their current hand yet
            if (!currentPlayerHand.GetHasHit()) {
                // Player is playing a split hand
                if (masterPlayerHand.GetChoseSplitHand()) {
                    // Show current hand of player and dealer hand
                    std::cout << std::endl << "Here are the initial hands of each player for hand " << std::to_string(hand_counter) << ":" << std::endl; time_sleep(1000);
                    currentPlayerHand.ShowHand("initial " + hand_tracker);
                    dealerHand.ShowHand("initial");
                    // Player can double down their current split hand
                    if (currentPlayerHand.GetCanDoubleDown()) {
                        // Prompt player what they would like to do
                        std::cout << std::endl << "Would you like to hit, stand, or double down for hand " << std::to_string(hand_counter) << "?" << std::endl; time_sleep(1000);
                        // blackjack_strategy(playerHand, dealerHand, true);
                        std::cout << std::endl << "Enter (h) to hit, (s) to stand, and (d) to double down for " << std::to_string(hand_counter) << ": "; time_sleep(1000);
                    }
                    // Player can't double down their current split hand
                    else {
                        // Prompt player what they would like to do
                        std::cout << std::endl << "Would you like to hit or stand for hand " << std::to_string(hand_counter) << "?" << std::endl; time_sleep(1000);
                        // blackjack_strategy(playerHand, dealerHand, true);
                        std::cout << std::endl << "Enter (h) to hit and (s) to stand for " << std::to_string(hand_counter) << ": "; time_sleep(1000);
                    }
                    std::cin >> response;
                    std::cout << std::endl; time_sleep(1000);
                }
                // Player is not playing a split hand
                else if (!masterPlayerHand.GetChoseSplitHand()) {
                    // Player can double down their current hand
                    if (currentPlayerHand.GetCanDoubleDown()) {
                        // Prompt player what they would like to do
                        std::cout << std::endl << "Would you like to hit, stand, or double down?" << std::endl; time_sleep(1000);
                        // blackjack_strategy(playerHand, dealerHand, true);
                        std::cout << std::endl << "Enter (h) to hit, (s) to stand, and (d) to double down: "; time_sleep(1000);
                    }
                    // Player can't double down their current hand
                    else {
                        // Prompt player what they would like to do
                        std::cout << std::endl << "Would you like to hit or stand?" << std::endl; time_sleep(1000);
                        // blackjack_strategy(playerHand, dealerHand, true);
                        std::cout << std::endl << "Enter (h) to hit and (s) to stand: "; time_sleep(1000);
                    }
                    std::cin >> response;
                    std::cout << std::endl; time_sleep(1000);
                }
                else {}            
            }
            // Player has hit their current hand
            else if (currentPlayerHand.GetHasHit()) {
                // Show hand of current player in their split hands
                if (masterPlayerHand.GetChoseSplitHand()) {
                    currentPlayerHand.ShowHand("current " + hand_tracker);
                }
                // Show hand of current player
                else if (!masterPlayerHand.GetChoseSplitHand()) {
                    currentPlayerHand.ShowHand("current");
                }
                else {}
                // Show dealer hand
                dealerHand.ShowHand("initial");
                // Prompt player what they would like to do
                std::cout << std::endl << "Would you like to hit (h) or stand (s)?" << std::endl; time_sleep(1000);
                // blackjack_strategy(playerHand, dealerHand, true);
                std::cout << std::endl << "Enter (h) to hit and (s) to stand: "; time_sleep(1000);
                std::cin >> response;
                std::cout << std::endl; time_sleep(1000);
            }
            else {}
            // Player has chosen to hit their hand
            if (response == "h") {
                // Set has hit to be true and hit the current hand
                currentPlayerHand.SetHasHit(true);
                currentPlayerHand.HitHand(shoe);
                // Player has busted their current hand
                if (currentPlayerHand.GetCardsTotal() > 21) {
                    // Tell player they have busted on their current hand
                    std::cout << currentPlayerHand.GetDisplayName() << " has chosen to hit and busted. Final hand total: " << currentPlayerHand.GetDisplayCardsTotal() << "." << std::endl; time_sleep(1000);
                    // Show hand of current split hand and hide dealers hand
                    if (masterPlayerHand.GetChoseSplitHand()) {
                        std::cout << std::endl << "Here is " << currentPlayerHand.GetDisplayName() << "'s final hand for hand " << std::to_string(hand_counter)
                        << " and the " << dealerHand.GetDisplayName() << "'s current hand:" << std::endl; time_sleep(1000);
                        currentPlayerHand.ShowHand("final " + hand_tracker);
                        dealerHand.ShowHand("current");
                    }
                    // Show hand of current hand and show dealer hand
                    else if (!masterPlayerHand.GetChoseSplitHand()) {
                        std::cout << std::endl << "Here is the final hand for " << currentPlayerHand.GetDisplayName() << " and the final hand of the " << dealerHand.GetDisplayName() << ":" << std::endl; time_sleep(1000);
                        currentPlayerHand.ShowHand("initial");
                        dealerHand.ShowHand("final", "show");
                    }
                    else {}
                    break;
                }
                // Player has a hand total of less than 21
                else if (currentPlayerHand.GetCardsTotal() < 21) {
                    // Tell player they have hit their current hand
                    std::cout << currentPlayerHand.GetDisplayName() << " has chosen to hit. Current hand total: " << currentPlayerHand.GetDisplayCardsTotal() << "." << std::endl; time_sleep(1000);
                    // Prompt for if this is a split hand
                    if (masterPlayerHand.GetChoseSplitHand()) {
                        std::cout << std::endl << "Here are the current hands of each player for hand " << std::to_string(hand_counter) << ":" << std::endl; time_sleep(1000);
                    }
                    // Prompt for if this is a singular hand
                    else if (!masterPlayerHand.GetChoseSplitHand()) {
                        std::cout << std::endl << "Here are the current hands of each player:" << std::endl; time_sleep(1000);
                    }
                    else {}
                }
                // Players current hand is 21
                else if (currentPlayerHand.GetCardsTotal() == 21) {
                    // Tell player they have achieved 21
                    std::cout << currentPlayerHand.GetDisplayName() << " has chosen to hit. Final hand total: " << currentPlayerHand.GetDisplayCardsTotal() << "." << std::endl; time_sleep(1000);
                    // Show hand of current split hand
                    if (masterPlayerHand.GetChoseSplitHand()) {
                        std::cout << std::endl << "Here is " << masterPlayerHand.GetDisplayName() << "'s final hand for hand " << std::to_string(hand_counter) << " and the " 
                        << dealerHand.GetDisplayName() << "'s current hand:" << std::endl; time_sleep(1000);
                        currentPlayerHand.ShowHand("final " + hand_tracker);
                        dealerHand.ShowHand("current", "");
                    }
                    // Show hand of singular hand
                    else if (!masterPlayerHand.GetChoseSplitHand()) {
                        std::cout << std::endl << "Here is the final hand for " << currentPlayerHand.GetDisplayName() << " and the initial hand of the " 
                        << dealerHand.GetDisplayName() << ":" << std::endl; time_sleep(1000);
                        currentPlayerHand.ShowHand("final");
                        dealerHand.ShowHand("initial", "show");
                    }
                    else {}
                }
                else {}
                response.clear();
            }
            // Player has chosen to stay on their current hand
            else if (response == "s") {
                // Tell player they have chosen to stay
                std::cout << currentPlayerHand.GetDisplayName() << " has chosen to stand. Final hand total: " << currentPlayerHand.GetDisplayCardsTotal() << "." << std::endl; time_sleep(1000);
                // Show hands of current hand in split hands
                if (masterPlayerHand.GetChoseSplitHand()) {
                    std::cout << std::endl << "Here is " << currentPlayerHand.GetDisplayName() << "'s final hand for hand " << std::to_string(hand_counter)
                    << " and the " << dealerHand.GetDisplayName() << "'s current hand:" << std::endl; time_sleep(1000);
                    currentPlayerHand.ShowHand("final " + hand_tracker);
                    dealerHand.ShowHand("current" , "");
                }
                // Show hand of singular hand
                else if (!masterPlayerHand.GetChoseSplitHand()) {
                    std::cout << std::endl << "Here is the final hand for " << currentPlayerHand.GetDisplayName() << " and the initial hand of the " 
                    << dealerHand.GetDisplayName() << ":" << std::endl; time_sleep(1000);
                    currentPlayerHand.ShowHand("final");
                    dealerHand.ShowHand("initial" , "show");
                }
                else {}
                break;
            }
            // Player has chosen to double down
            else if (response == "d") {
                // Player can double down
                if (currentPlayerHand.GetCanDoubleDown()) {
                    // Update bank totals of player and hit hand
                    currentPlayerHand.UpdateBank(0, currentPlayerHand.GetWager());
                    currentPlayerHand.SetWager(2 * currentPlayerHand.GetWager());
                    currentPlayerHand.HitHand(shoe);
                    // Player has busted
                    if (currentPlayerHand.GetCardsTotal() > 21) {
                        // Tell player they have busted on their current hand
                        std::cout << currentPlayerHand.GetDisplayName() << " has doubled down and busted. Final hand total: " << currentPlayerHand.GetDisplayCardsTotal() << "." << std::endl; time_sleep(1000);
                        // Show current hand of split hand
                        if (masterPlayerHand.GetChoseSplitHand()) {
                            std::cout << std::endl << "Here is " << currentPlayerHand.GetDisplayName() << "'s final hand for hand " << std::to_string(hand_counter)
                            << " and the " << dealerHand.GetDisplayName() << "'s current hand:" << std::endl; time_sleep(1000);
                            currentPlayerHand.ShowHand("final " + hand_tracker);
                            dealerHand.ShowHand("current");
                        }
                        // Show singular hand
                        else if (!masterPlayerHand.GetChoseSplitHand()) {
                            std::cout << std::endl << "Here is the final hand for " << currentPlayerHand.GetDisplayName() << " and the final hand of the " 
                            << dealerHand.GetDisplayName() << ":" << std::endl; time_sleep(1000);
                            currentPlayerHand.ShowHand("final");
                            dealerHand.ShowHand("final", "show");
                        }
                        else
                        break;
                    }
                    // Player has reached 21
                    else if (currentPlayerHand.GetCardsTotal() <= 21) {
                        // Tell player they have reached 21
                        std::cout << currentPlayerHand.GetDisplayName() << " has doubled down. Final hand total: " << currentPlayerHand.GetDisplayCardsTotal() << "." << std::endl; 
                        // Show current hand of split hand
                        if (masterPlayerHand.GetChoseSplitHand()) {
                            std::cout << std::endl << "Here is " << currentPlayerHand.GetDisplayName() << "'s final hand for hand " << std::to_string(hand_counter) << " and the " 
                            << dealerHand.GetDisplayName() << "'s current hand:" << std::endl; time_sleep(1000);
                            currentPlayerHand.ShowHand("final " + hand_tracker);
                            dealerHand.ShowHand("current");
                        }
                        // Show singular hand
                        else if (!masterPlayerHand.GetChoseSplitHand()) {
                            std::cout << std::endl << "Here is the final hand for " << currentPlayerHand.GetDisplayName() << " and the initial hand of the " 
                            << dealerHand.GetDisplayName() << ":" << std::endl; time_sleep(1000);
                            currentPlayerHand.ShowHand("final");
                            dealerHand.ShowHand("initial", "show");
                        }
                        else {}
                        break;
                    }
                    else {}
                }
                // Player cannot double down
                else {
                    // Tell player they cannot double down, return to choices for player
                    std::cout << "Your current bank total of " << currentPlayerHand.GetDisplayBankTotal() << " is not greater than your wager of "
                    << currentPlayerHand.GetDisplayWager() << ". You cannot double down." << std::endl; time_sleep(1000);
                    response.clear();
                    continue;
                }
            }
            // Player has entered and incorrect value for a choice
            else if (response != "h" && response != "s" && response != "d") {
                if (!masterPlayerHand.GetChoseSplitHand()) {
                    std::cout << color_text(31, "Invalid choice") << "." << std::endl; 
                }
                else if (masterPlayerHand.GetChoseSplitHand()) {
                    std::cout << color_text(31, "Invalid choice") << "." << std::endl << std::endl; 
                }
                else {}            
                response.clear();
                continue;
            }
            else {}
        }
        if (currentPlayerHand.GetCardsTotal() == 21 && masterPlayerHand.GetChoseSplitHand()) {
            std::cout << std::endl << currentPlayerHand.GetDisplayName() << " has gotten " << currentPlayerHand.GetDisplayCardsTotal() << "! You no longer need to play this hand: Your final hand is:" << std::endl; time_sleep(1000);
            currentPlayerHand.ShowHand("final " + hand_tracker);
        }
        else {}
        // Copy variables of current hand to master hand
        masterPlayerHand.CopyVariables(currentPlayerHand);
    }
    // Player has chosen to split aces
    else if (masterPlayerHand.GetChoseSplitAces()) {
        masterPlayerHand.CopyVariables(currentPlayerHand);
    }
    else {}
    // Return hands of player
    return std::make_tuple(currentPlayerHand, dealerHand, shoe);
}

/*  dealer_hand_logic - Processes the logic for how the dealer should play their current hands
*   Input:
*       playerHands - Vector of Hand objects that are passed by reference that represent all of the hands of a player
*       dealerHand - Hand object passed by reference that represents the dealers hand
*       Shoe - Shoe object passed by reference that represents the shoe in the game that is being played with
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
*       * Return the dealers hand and the game shoe
*   Output:
*       dealerHand - Hand object that represents the modified hand of the dealer after being played with
*       shoe - Shoe object that represents the modified shoe in the game
*/
std::tuple<Hand, Shoe> dealer_hand_logic(std::vector<Hand>& playerHands, Hand& dealerHand, Shoe& shoe) {
    // Check the parameters of the dealers hand
    dealerHand.ParametersCheck(dealerHand, dealerHand);
    // Check if all hands of the player are over 21
    bool all_over_21 = true;
    for (Hand current_hand : playerHands) {
        if (current_hand.GetCardsTotal() <= 21) {
            all_over_21 = false;
            break;
        }
        else if (current_hand.GetCardsTotal() > 21) {
            all_over_21 = true;
            continue;
        }
        else {}
    }
    // Not all hands of player are over 21
    if (!all_over_21) {
        // Check if the dealer has an Ace in their hand
        dealerHand.CheckParamInHand("R", Ranks[0]);
        // Dealer has a hand total of seventeen or greater with no Ace in hand
        if (dealerHand.GetCardsTotal() >= 17 && !dealerHand.GetParamInHand()) {
            int total_hands = playerHands.size();
            // Display all the hands of the player that they have split and played
            if (total_hands > 1) {
                int hand_counter = 0;
                std::string hand_tracker;
                std::cout << std::endl << "Here are the final hand(s) of " << playerHands.at(0).GetDisplayName() << " and the " << dealerHand.GetDisplayName() << ":" << std::endl; time_sleep(1000);
                for (Hand current_hand : playerHands) {
                    hand_counter++;
                    if (hand_counter == 1) {
                        hand_tracker = "first";
                    }
                    else if (hand_counter == 2) {
                        hand_tracker = "second";
                    }
                    else if (hand_counter == 3) {
                        hand_tracker = "third";
                    }
                    else if (hand_counter == 4) {
                        hand_tracker = "fourth";
                    }
                    else if (hand_counter == 5) {
                        hand_tracker = "fifth";
                    }
                    else {}
                    current_hand.ShowHand("final " + hand_tracker);
                }
            }
            // Display the singular hand of the player
            else {
                playerHands.at(0).ShowHand("final");
            }
            // Show the hand of the dealer
            dealerHand.ShowHand("final", "show");
            std::cout << std::endl << "The " << dealerHand.GetDisplayName() << " does not need to play their hand with a final total of " << dealerHand.GetDisplayCardsTotal() << "." << std::endl; time_sleep(1000);
        }
        // Dealer has less than 17 or has a soft 17
        else if (dealerHand.GetCardsTotal() < 17 || dealerHand.GetSoftSeventeen()) {
            int total_hands = playerHands.size();
            // Display all the hands of the player that they have split and played
            if (total_hands > 1) {
                int hand_counter = 0;
                std::string hand_tracker;
                std::cout << std::endl << "Here are the final hand(s) of " << playerHands.at(0).GetDisplayName() << " and the initial hand of the " << dealerHand.GetDisplayName() << ":" << std::endl; time_sleep(1000);
                for (Hand current_hand : playerHands) {
                    hand_counter++;
                    if (hand_counter == 1) {
                        hand_tracker = " first";
                    }
                    else if (hand_counter == 2) {
                        hand_tracker = " second";
                    }
                    else if (hand_counter == 3) {
                        hand_tracker = " third";
                    }
                    else if (hand_counter == 4) {
                        hand_tracker = " fourth";
                    }
                    else if (hand_counter == 5) {
                        hand_tracker = " fifth";
                    }
                    else {}
                    current_hand.ShowHand("final " + hand_tracker);
                }
            }
            // Display the singular hand of the player
            else {
                playerHands.at(0).ShowHand("final");
            }
            // Show the hand of the dealer
            dealerHand.ShowHand("initial", "show");
            std::cout << std::endl << "The " << dealerHand.GetDisplayName() << " will now play their hand." << std::endl; time_sleep(1000);
            // Dealer must continue to play and will hit on soft seventeen
            while ((dealerHand.GetCardsTotal() < 17 || dealerHand.GetSoftSeventeen())) {
                // Dealer still has less than seventeen or possesses a soft seventeen
                if (dealerHand.GetCardsTotal() < 17 || dealerHand.GetSoftSeventeen()) {
                    dealerHand.HitHand(shoe);
                    std::cout << dealerHand.GetDisplayName() << " hits hand: ";
                    dealerHand.ShowHand("", "cards");
                    dealerHand.ParametersCheck(dealerHand, dealerHand);
                    continue;
                }
                // Dealer has 17 or higher and does not have a soft seventeen
                else if (dealerHand.GetCardsTotal() >= 17 && !dealerHand.GetSoftSeventeen()) {
                    break;
                }
                else {}
            }
        }
        else {}
        // Show the final hand of the dealer after playing
        std::cout << std::endl << "The " << dealerHand.GetDisplayName() << "'s final hand is:"; time_sleep(1000);
        std::cout << std::endl << dealerHand.GetDisplayName() << " final hand "; dealerHand.ShowHand("", "cards"); std::cout << std::endl; time_sleep(1000);
    }
    // All hands of player are over 21
    else if (all_over_21) {
        std::cout << std::endl << playerHands.at(0).GetDisplayName() << " has busted on all of their hands. " << dealerHand.GetDisplayName() << " does not need to play their hand." << std::endl; time_sleep(1000);
        std::cout << std::endl << "The final hands of " << playerHands.at(0).GetDisplayName() << " and the " << dealerHand.GetDisplayName() << " are:" << std::endl; time_sleep(1000);
        int total_hands = playerHands.size();
        // Display all the hands of the player that they have split and played
        if (total_hands > 1) {
            int hand_counter = 0;
            std::string hand_tracker;
            for (Hand current_hand : playerHands) {
                hand_counter++;
                if (hand_counter == 1) {
                    hand_tracker = "first";
                }
                else if (hand_counter == 2) {
                    hand_tracker = "second";
                }
                else if (hand_counter == 3) {
                    hand_tracker = "third";
                }
                else if (hand_counter == 4) {
                    hand_tracker = "fourth";
                }
                else if (hand_counter == 5) {
                    hand_tracker = "fifth";
                }
                else {}
                current_hand.ShowHand("final " + hand_tracker);
            }
        }
        // Display the singular hand of the player
        else {
            playerHands.at(0).ShowHand("final");
        }
        // Show the final hand of the dealer
        dealerHand.ShowHand("final", "show");
    }
    else {}
    // Return the dealer hand and the modified shoe
    return std::make_tuple(dealerHand, shoe);
}

void test_game() {
    Hand playerTest;
    Hand dealerTest;
    Shoe testShoe;
    testShoe.SetNumOfDecks(1);
    testShoe.CreateShoe();
    testShoe.SetRiggedCards(Card(Ranks[0], Suits[0]));
    testShoe.SetRiggedCards(Card(Ranks[0], Suits[0]));
    testShoe.SetRiggedCards(Card(Ranks[0], Suits[0]));
    testShoe.SetRiggedCards(Card(Ranks[0], Suits[0]));
    testShoe.SetRiggedCards(Card(Ranks[0], Suits[0]));
    testShoe.SetRiggedCards(Card(Ranks[0], Suits[0]));
    testShoe.SetRiggedCards(Card(Ranks[0], Suits[0]));
    testShoe.SetRiggedCards(Card(Ranks[0], Suits[0]));
    testShoe.SetRiggedCards(Card(Ranks[0], Suits[0]));
    testShoe.SetRiggedCards(Card(Ranks[0], Suits[0]));
    testShoe.SetRiggedCards(Card(Ranks[0], Suits[0]));
    testShoe.SetRiggedCards(Card(Ranks[0], Suits[0]));
    testShoe.SetRiggedCards(Card(Ranks[0], Suits[0]));
    testShoe.SetRiggedCards(Card(Ranks[0], Suits[0]));
    testShoe.SetRiggedCards(Card(Ranks[0], Suits[0]));
    testShoe.SetRiggedCards(Card(Ranks[0], Suits[0]));
    testShoe.SetRiggedCards(Card(Ranks[0], Suits[0]));
    testShoe.SetRiggedCards(Card(Ranks[0], Suits[0]));
    testShoe.SetRiggedCards(Card(Ranks[11], Suits[0]));
    testShoe.SetRiggedCards(Card(Ranks[11], Suits[0]));
    testShoe.SetRiggedCards(Card(Ranks[5], Suits[0]));
    testShoe.SetRiggedCards(Card(Ranks[12], Suits[0]));
    testShoe.SetRiggedCards(Card(Ranks[0], Suits[0]));
    testShoe.SetRiggedCards(Card(Ranks[12], Suits[0]));
    playerTest.SetName("Player 1");
    dealerTest.SetName("Dealer");
    playerTest.SetBankTotal(100);
    auto dealerAce = dealer_showing_ace(playerTest, dealerTest, testShoe);
    if (std::get<3>(dealerAce)) {
        auto sameRank = same_rank_check(std::get<0>(dealerAce), std::get<1>(dealerAce), std::get<2>(dealerAce));
        int hand_counter = 0;
        std::vector<Hand> playerHandsPL;
        for (Hand& current_hand : std::get<0>(sameRank)) {
            hand_counter++;
            auto playerHandLogic = player_hand_logic(current_hand, std::get<2>(sameRank), std::get<1>(sameRank), std::get<3>(sameRank), hand_counter);
            playerHandsPL.insert(playerHandsPL.begin(), std::get<0>(playerHandLogic));
            playerTest = std::get<0>(playerHandLogic);
            dealerTest = std::get<1>(playerHandLogic);
            testShoe = std::get<2>(playerHandLogic);
        }
        std::reverse(playerHandsPL.begin(), playerHandsPL.end());
        auto dealerHandLogic = dealer_hand_logic(playerHandsPL, dealerTest, testShoe);
    }
    else {

    }
}

// Finish dealer hand logic