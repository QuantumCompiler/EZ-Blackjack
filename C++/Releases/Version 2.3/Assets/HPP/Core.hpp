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

void test_game() {
    Hand playerTest;
    Hand dealerTest;
    Shoe testShoe;
    testShoe.SetRiggedCards(Card(Ranks[8], Suits[3]));
    testShoe.SetRiggedCards(Card(Ranks[8], Suits[2]));
    testShoe.SetRiggedCards(Card(Ranks[0], Suits[1]));
    testShoe.SetRiggedCards(Card(Ranks[0], Suits[0]));
    playerTest.SetName("Player 1");
    dealerTest.SetName("Dealer");
    playerTest.SetBankTotal(100);
    dealer_showing_ace(playerTest, dealerTest, testShoe);
}