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

std::tuple<std::vector<Hand>, Hand, Hand, Shoe, int> same_rank_check(Hand& playerHand, Hand& dealerHand, Shoe& shoe)
{
    int hand_count = 1;
    std::vector<Hand> new_hand;
    // Check if player can split their hand
    if (playerHand.GetCanSplitAces() || playerHand.GetCanSplitHand()) {
        // Player can split aces
        if (playerHand.GetCanSplitAces() && !playerHand.GetCanSplitHand()) {
            std::string aces_response;
            while (aces_response.empty()) {
                // Prompt player to enter response to split aces
                std::cout << std::endl << "You have the same rank of " << playerHand.GetCards().at(0).GetDisplayRank() << " in your hand." << std::endl; time_sleep(1000);
                std::cout << std::endl << "Would you like to split your hand? You may only split your hand once." << std::endl; time_sleep(1000);
                // blackjack_strategy(playerHand, dealerHand, false);
                std::cout << std::endl << "Enter (y) for yes and (n) for no: "; time_sleep(1000);
                std::cin >> aces_response;
                std::cout << std::endl;
                // Player has chosen to split aces
                if (aces_response == "y") {
                    playerHand.SetChoseSplitAces(true);
                    playerHand.SetSplitAcesResponse(true);
                    std::cout << playerHand.GetDisplayName() << " has chosen to split their " << playerHand.GetCards().at(0).GetDisplayRank() << "'s." << std::endl; time_sleep(1000);
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
                    std::cout << playerHand.GetDisplayName() << " has chosen not to split their " << playerHand.GetCards().at(0).GetDisplayRank() << "'s." << std::endl; time_sleep(1000);
                    new_hand.push_back(playerHand);
                    playerHand.CopyVariables(new_hand.back());
                    return std::make_tuple(new_hand, playerHand, dealerHand, shoe, hand_count);
                }
                else {
                    std::cout << color_text(31, "Invalid choice") + " of " + color_text(31, aces_response) + ". Plese re-enter your decision." << std::endl << std::endl; time_sleep(1000);
                    aces_response.clear();
                }
            }
        }
        else if (!playerHand.GetCanSplitAces() && playerHand.GetCanSplitHand()) {

        }
        // if (check_same_parameter_in_hand(playerHand, "R", "Ace")) {
        // }
        // else if (check_same_parameter_in_hand(playerHand, "R") && !check_card_parameter(playerHand.player.cards[0].card.rank, "Ace"))
        // {
        //     std::string same_rank_response;
        //     while (same_rank_response.empty())
        //     {
        //         std::cout << std::endl << "You have the same rank of " << playerHand.player.cards[0].display_rank << " in your hand." << std::endl; 
        //         std::cout << std::endl << "Would you like to split your hand? You may split up to a total of four times." << std::endl; 
        //         blackjack_strategy(playerHand, dealerHand, false);
        //         std::cout << std::endl << "Enter (y) for yes and (n) for no: ";
        //         std::cin >> same_rank_response;
        //         if (same_rank_response == "y")
        //         {
        //             playerHand.player.chose_split_hand = true;
        //             playerHand.player.split_decision = true;
        //             std::cout << std::endl << playerHand.player.display_name << " has chosen to split their hand." << std::endl; 
        //             int split_counter = 1;
        //             hand_count++;
        //             std::vector<Hand> initial_split = split_hand(playerHand);
        //             std::vector<Hand> split_hands;
        //             std::vector<Hand> temp_hands;
        //             Hand player_hand_1 = initial_split.at(0);
        //             Hand player_hand_2 = initial_split.at(1);
        //             player_hand_2.Hit(shoe);
        //             temp_hands.push_back(player_hand_2);
        //             temp_hands.push_back(player_hand_1);
        //             Hand checking_hand;
        //             checking_hand = player_hand_2;
        //             checking_hand.Copy_Variables(player_hand_2);
        //             special_options(checking_hand, dealerHand, false);
        //             if (check_same_parameter_in_hand(checking_hand, "R"))
        //             {
        //                 if (checking_hand.player.can_split_hand)
        //                 {
        //                     std::cout << std::endl << "Total times split: " << color_text(31, std::to_string(split_counter)) << ". Your current hand(s) are:" << std::endl; 
        //                     int loop_counter = 1;
        //                     std::string hand_tracker;
        //                     for (Hand& current_hand : temp_hands)
        //                     {
        //                         if (loop_counter == 1)
        //                         {
        //                             hand_tracker = "first";
        //                         }
        //                         else if (loop_counter == 2)
        //                         {
        //                             hand_tracker = "second";
        //                         }
        //                         else {}
        //                         current_hand.Show_Hand(hand_tracker);
        //                         loop_counter++;
        //                     }
        //                     temp_hands.clear();
        //                     while (split_counter < 4 && checking_hand.player.can_split_hand)
        //                     {
        //                         std::string split_again;
        //                         while (split_again != "y" || split_again != "n")
        //                         {
        //                             std::cout << std::endl << std::endl << "You have pulled the same rank of " << checking_hand.player.cards[0].display_rank 
        //                             << " again." << std::endl; 
        //                             std::cout << std::endl << "Would you like to split your current hand again?" << std::endl; 
        //                             blackjack_strategy(checking_hand, dealerHand, false);
        //                             std::cout << std::endl << "Enter (y) for yes and (n) for no: ";
        //                             std::cin >> split_again;
        //                             std::cout << std::endl;
        //                             if (split_again == "y")
        //                             {
        //                                 split_counter++;
        //                                 hand_count++;
        //                                 std::vector<Hand> new_split = split_hand(checking_hand);
        //                                 Hand new_player_hand_1 = new_split.at(0);
        //                                 Hand new_player_hand_2 = new_split.at(1);
        //                                 new_player_hand_2.Hit(shoe);
        //                                 split_hands.insert(split_hands.begin(), new_player_hand_1);
        //                                 checking_hand = new_player_hand_2;
        //                                 checking_hand.Copy_Variables(new_player_hand_2);
        //                                 special_options(checking_hand, dealerHand, false);
        //                                 break;
        //                             }
        //                             else if (split_again == "n")
        //                             {
        //                                 break;
        //                             }
        //                             else
        //                             {
        //                                 std::cout << color_text(31, "Invalid Entry") << ". Please enter a valid choice." << std::endl; 
        //                                 split_again.clear();
        //                             }
        //                         }
        //                         split_hands.insert(split_hands.begin(), checking_hand);
        //                         split_hands.insert(split_hands.end(), player_hand_1);
        //                         for (int i = 0; i < split_hands.size(); i++)
        //                         {
        //                             split_hands.at(i).Copy_Variables(checking_hand);
        //                         }
        //                         if (checking_hand.player.can_split_hand && split_again == "y")
        //                         {
        //                             if (split_counter < 4 && checking_hand.player.can_split_hand)
        //                             {
        //                                 std::cout << playerHand.player.display_name << " has chosen to split their hand again." << std::endl; 
        //                                 std::cout << std::endl << "Total times split: " << color_text(31, std::to_string(split_counter)) << ". Your current hand(s) are:" << std::endl; 
        //                                 int loop_counter = 1;
        //                                 std::string hand_tracker;
        //                                 for (Hand& current_hand : split_hands)
        //                                 {
        //                                     if (loop_counter == 1)
        //                                     {
        //                                         hand_tracker = "first";
        //                                     }
        //                                     else if (loop_counter == 2)
        //                                     {
        //                                         hand_tracker = "second";
        //                                     }
        //                                     else if (loop_counter == 3)
        //                                     {
        //                                         hand_tracker = "third";
        //                                     }
        //                                     else if (loop_counter == 4)
        //                                     {
        //                                         hand_tracker = "fourth";
        //                                     }
        //                                     else
        //                                     {
        //                                         hand_tracker = "current";
        //                                     }
        //                                     current_hand.Show_Hand(hand_tracker);
        //                                     loop_counter++;
        //                                 }
        //                                 split_hands.erase(split_hands.begin());
        //                                 split_hands.pop_back();
        //                                 continue;
        //                             }
        //                             else if (split_counter == 4 || !checking_hand.player.can_split_hand)
        //                             {
        //                                 if (split_counter == 4)
        //                                 {
        //                                     std::cout << playerHand.player.display_name << " has reached the max amount of times to split." << std::endl; 
        //                                     std::cout << std::endl << "Total times split: " << color_text(31, std::to_string(split_counter)) << ". Your current hand(s) are:" << std::endl; 
        //                                     int loop_counter = 1;
        //                                     std::string hand_tracker;
        //                                     for (Hand& current_hand : split_hands)
        //                                     {
        //                                         if (loop_counter == 1)
        //                                         {
        //                                             hand_tracker = "first";
        //                                         }
        //                                         else if (loop_counter == 2)
        //                                         {
        //                                             hand_tracker = "second";
        //                                         }
        //                                         else if (loop_counter == 3)
        //                                         {
        //                                             hand_tracker = "third";
        //                                         }
        //                                         else if (loop_counter == 4)
        //                                         {
        //                                             hand_tracker = "fourth";
        //                                         }
        //                                         else if (loop_counter == 5)
        //                                         {
        //                                             hand_tracker = "fifth";
        //                                         }
        //                                         else
        //                                         {
        //                                             hand_tracker = "current";
        //                                         }
        //                                         current_hand.Show_Hand(hand_tracker);
        //                                         loop_counter++;
        //                                     }
        //                                     std::cout << std::endl << std::endl;
        //                                 }
        //                                 else if (!checking_hand.player.can_split_hand)
        //                                 {
        //                                     if (checking_hand.player.bank_total < checking_hand.player.wager) 
        //                                     {
        //                                         std::cout << "Your current bank balance of " << checking_hand.player.display_bank_total << " is not greater than"
        //                                         << " your wager of " << checking_hand.player.display_wager << ". You can no longer split your hands. Total times split: " 
        //                                         << color_text(31, std::to_string(split_counter)) << ". Your current hand(s) are:" << std::endl; 
        //                                     }
        //                                     else {}
        //                                     int loop_counter = 1;
        //                                     std::string hand_tracker;
        //                                     for (Hand& current_hand : split_hands)
        //                                     {
        //                                         if (loop_counter == 1)
        //                                         {
        //                                             hand_tracker = "first";
        //                                         }
        //                                         else if (loop_counter == 2)
        //                                         {
        //                                             hand_tracker = "second";
        //                                         }
        //                                         else if (loop_counter == 3)
        //                                         {
        //                                             hand_tracker = "third";
        //                                         }
        //                                         else if (loop_counter == 4)
        //                                         {
        //                                             hand_tracker = "fourth";
        //                                         }
        //                                         else
        //                                         {
        //                                             hand_tracker = "current";
        //                                         }
        //                                         current_hand.Show_Hand(hand_tracker);
        //                                         loop_counter++;
        //                                     }
        //                                     std::cout << std::endl << std::endl;
        //                                 }
        //                                 break;
        //                             }
        //                             else {}
        //                         }
        //                         else if (!checking_hand.player.can_split_hand || split_again == "n")
        //                         {
        //                             if (!checking_hand.player.can_split_hand)
        //                             {
        //                                 if (checking_hand.player.bank_total < checking_hand.player.wager) {
        //                                     std::cout << "You pulled the same rank of " << checking_hand.player.cards[0].display_rank << " again but you do not have enough currency to continue splitting. ";
        //                                     std::cout << std::endl << std::endl << "Total times split: " << color_text(31, std::to_string(split_counter)) << ". Your current hand(s) are: " << std::endl; 
        //                                 }
        //                                 else if (checking_hand.player.bank_total >= checking_hand.player.wager) {
        //                                     std::cout << "You did not pull the same rank of " << checking_hand.player.cards[0].display_rank << " again. You can no longer split your hands."; 
        //                                     std::cout << std::endl << std::endl << "Total times split: " << color_text(31, std::to_string(split_counter)) << ". Your current hand(s) are: " << std::endl; 
        //                                 }
        //                                 else {}
        //                                 int loop_counter = 1;
        //                                 std::string hand_tracker;
        //                                 for (Hand& current_hand : split_hands)
        //                                 {
        //                                     if (loop_counter == 1)
        //                                     {
        //                                         hand_tracker = "first";
        //                                     }
        //                                     else if (loop_counter == 2)
        //                                     {
        //                                         hand_tracker = "second";
        //                                     }
        //                                     else if (loop_counter == 3)
        //                                     {
        //                                         hand_tracker = "third";
        //                                     }
        //                                     else if (loop_counter == 4)
        //                                     {
        //                                         hand_tracker = "fourth";
        //                                     }
        //                                     else
        //                                     {
        //                                         hand_tracker = "current";
        //                                     }
        //                                     current_hand.Show_Hand(hand_tracker);
        //                                     loop_counter++;
        //                                 }
        //                                 std::cout << std::endl << std::endl;
        //                             }
        //                             else if (split_again == "n")
        //                             {
        //                                 std::cout << playerHand.player.display_name << " has chosen not to split their hand again." << std::endl << std::endl << "Total times split: " 
        //                                 << color_text(31, std::to_string(split_counter)) << ". Your current hand(s) are:" << std::endl; 
        //                                 int loop_counter = 1;
        //                                 std::string hand_tracker;
        //                                 for (Hand &current_hand : split_hands)
        //                                 {
        //                                     if (loop_counter == 1)
        //                                     {
        //                                         hand_tracker = "first";
        //                                     }
        //                                     else if (loop_counter == 2)
        //                                     {
        //                                         hand_tracker = "second";
        //                                     }
        //                                     else if (loop_counter == 3)
        //                                     {
        //                                         hand_tracker = "third";
        //                                     }
        //                                     else if (loop_counter == 4)
        //                                     {
        //                                         hand_tracker = "fourth";
        //                                     }
        //                                     else
        //                                     {
        //                                         hand_tracker = "current";
        //                                     }
        //                                     current_hand.Show_Hand(hand_tracker);
        //                                     loop_counter++;
        //                                 }
        //                                 std::cout << std::endl << std::endl;
        //                             }
        //                             else {}
        //                             break;
        //                         }
        //                     }
        //                     new_hand = split_hands;
        //                     playerHand.Copy_Variables(new_hand.back());
        //                     return std::make_tuple(new_hand, playerHand, dealerHand, shoe, hand_count);
        //                 }
        //                 else if (!checking_hand.player.can_split_hand)
        //                 {
        //                     std::cout << std::endl << "You have pulled the same rank of " << checking_hand.player.cards[0].display_rank << " again." << std::endl;
        //                     int loop_counter = 1;
        //                     std::string hand_tracker;
        //                     for (Hand& current_hand : temp_hands)
        //                     {
        //                         if (loop_counter == 1)
        //                         {
        //                             hand_tracker = "first";
        //                         }
        //                         else if (loop_counter == 2)
        //                         {
        //                             hand_tracker = "second";
        //                         }
        //                         else
        //                         {
        //                             hand_tracker = "current";
        //                         }
        //                         current_hand.Show_Hand(hand_tracker);
        //                         loop_counter++; 
        //                     }
        //                     std::cout << std::endl << "Your current bank balance of " << checking_hand.player.display_bank_total << " is not  greater than your wager of " 
        //                     << checking_hand.player.display_wager << ". You can no longer split your hands. Total times split: " << color_text(31, std::to_string(split_counter)) << std::endl;
        //                     new_hand = temp_hands;
        //                     playerHand.Copy_Variables(new_hand.back());
        //                     return std::make_tuple(new_hand, playerHand, dealerHand, shoe, hand_count);
        //                 }
        //                 else {}
        //             }
        //             else if (!check_same_parameter_in_hand(checking_hand, "R"))
        //             {
        //                 new_hand.insert(new_hand.begin(), checking_hand);
        //                 new_hand.push_back(player_hand_1);
        //                 std::cout << std::endl << "Total times split: " << color_text(31, std::to_string(split_counter)) << ". Your current hand(s) are:" << std::endl; 
        //                 int loop_counter = 1;
        //                 std::string hand_tracker;
        //                 for (Hand &current_hand : new_hand)
        //                 {
        //                     if (loop_counter == 1)
        //                     {
        //                         hand_tracker = "first";
        //                     }
        //                     else if (loop_counter == 2)
        //                     {
        //                         hand_tracker = "second";
        //                     }
        //                     else {}
        //                     current_hand.Show_Hand(hand_tracker);
        //                     loop_counter++;
        //                 }
        //                 std::cout << std::endl;
        //                 playerHand.Copy_Variables(new_hand.back());
        //                 return std::make_tuple(new_hand, playerHand, dealerHand, shoe, hand_count);
        //             }
        //             else {}
        //         }
        //         else if (same_rank_response == "n")
        //         {
        //             playerHand.player.chose_split_hand = false;
        //             playerHand.player.split_decision = true;
        //             new_hand.push_back(playerHand);
        //             std::cout << std::endl << playerHand.player.display_name << " has chosen not to split their hand." << std::endl; 
        //             playerHand.Copy_Variables(new_hand.back());
        //             return std::make_tuple(new_hand, playerHand, dealerHand, shoe, hand_count);
        //         }
        //         else
        //         {
        //             std::cout << std::endl << color_text(31, "Invalid choice") + " of " + color_text(31, same_rank_response) + ". Plese re-enter your decision." << std::endl; 
        //             same_rank_response.clear();
        //         }
        //     }
        // }
        // else if (!check_same_parameter_in_hand(playerHand, "R"))
        // {
        //     new_hand.push_back(playerHand);
        //     playerHand.Copy_Variables(new_hand.back());
        //     return std::make_tuple(new_hand, playerHand, dealerHand, shoe, hand_count);
        // }
        // else {}
    }
    // else if (!playerHand.player.can_split_hand)
    // {
    //     new_hand.push_back(playerHand);
    //     playerHand.Copy_Variables(new_hand.back());
    //     return std::make_tuple(new_hand, playerHand, dealerHand, shoe, hand_count);
    // }
    else {}
}

void test_game() {
    Hand playerTest;
    Hand dealerTest;
    Shoe testShoe;
    testShoe.SetRiggedCards(Card(Ranks[8], Suits[3]));
    testShoe.SetRiggedCards(Card(Ranks[0], Suits[2]));
    testShoe.SetRiggedCards(Card(Ranks[0], Suits[1]));
    testShoe.SetRiggedCards(Card(Ranks[0], Suits[0]));
    playerTest.SetName("Player 1");
    dealerTest.SetName("Dealer");
    playerTest.SetBankTotal(100);
    dealer_showing_ace(playerTest, dealerTest, testShoe);
    same_rank_check(playerTest, dealerTest, testShoe);
}