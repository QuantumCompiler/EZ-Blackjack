#include <gtest/gtest.h>
#include "../app/Assets/HPP/Core.hpp"

using namespace std;

class test_x : public ::testing::Test {};

/////////////////////////////////////////
// Test Helper Functions
/////////////////////////////////////////

/////////////////////////////////////////
// Tests start here
/////////////////////////////////////////

TEST_F(test_x, BlackjackStrat){
    // Test if a player has a card total of (5-8)
    Hand userHand;
    Hand dealerHand;
    userHand.SetBankTotal(100);
    userHand.SetWager(10);
    // Add first card to dealer
    dealerHand.SetCards(Card(Ranks[0], Suits[0]));
    // Add dummy cards to user hand
    userHand.SetCards(Card(Ranks[1], Suits[0]));
    userHand.SetCards(Card(Ranks[12], Suits[0]));
    // Player has a card total of 4 through 8
    for (int i = 4; i < 9; i++) {
        // Calculate random number
        std::random_device rd;
        std::mt19937 gen(rd());
        int min = 0;
        int max = 12;
        std::uniform_int_distribution<int> dist(min, max);
        int randomRank = dist(gen);
        // Add random cards to dealer hand
        dealerHand.SetCards(Card(Ranks[randomRank], Suits[0]));
        // Rig hand total
        userHand.SetCardsTotal(i);
        // Test strategy
        blackjack_strategy(userHand, dealerHand);
        ASSERT_FALSE(userHand.GetShouldDoubleDown());
        ASSERT_TRUE(userHand.GetShouldHit());
        ASSERT_FALSE(userHand.GetShouldSplit());
        ASSERT_FALSE(userHand.GetShouldStand());
        // Remove last card from dealer hand
        dealerHand.GetCards().pop_back();
    }
    // Player has a card total of 9
    userHand.SetCardsTotal(9);
    // Dealer has a face up card value of 2 through 6
    for (int i = 1; i < 6; i++) {
        // Add card to dealer hand
        dealerHand.SetCards(Card(Ranks[i], Suits[0]));
        // Test strategy - Can double down
        userHand.SetWager(10);
        blackjack_strategy(userHand, dealerHand);
        ASSERT_TRUE(userHand.GetShouldDoubleDown());
        ASSERT_TRUE(userHand.GetShouldHit());
        ASSERT_FALSE(userHand.GetShouldSplit());
        ASSERT_FALSE(userHand.GetShouldStand());
        // Test strategy - Can't double down
        userHand.SetWager(200);
        blackjack_strategy(userHand, dealerHand);
        ASSERT_FALSE(userHand.GetShouldDoubleDown());
        ASSERT_TRUE(userHand.GetShouldHit());
        ASSERT_FALSE(userHand.GetShouldSplit());
        ASSERT_FALSE(userHand.GetShouldStand());
        // Remove last card from dealer hand
        dealerHand.GetCards().pop_back();        
    }
    // Dealer has a face up card value of 7 through Ace
    for (int i = 7; i < 12; i++) {
        userHand.SetWager(10);
        // Add card to dealer hand
        dealerHand.SetCards(Card(Ranks[i], Suits[0]));
        // Test strategy - Can double down
        blackjack_strategy(userHand, dealerHand);
        ASSERT_FALSE(userHand.GetShouldDoubleDown());
        ASSERT_TRUE(userHand.GetShouldHit());
        ASSERT_FALSE(userHand.GetShouldSplit());
        ASSERT_FALSE(userHand.GetShouldStand());
        // Test strategy - For Ace in dealer hand
        dealerHand.GetCards().pop_back();
        dealerHand.SetCards(Card(Ranks[0], Suits[0]));
        blackjack_strategy(userHand, dealerHand);
        ASSERT_FALSE(userHand.GetShouldDoubleDown());
        ASSERT_TRUE(userHand.GetShouldHit());
        ASSERT_FALSE(userHand.GetShouldSplit());
        ASSERT_FALSE(userHand.GetShouldStand());
        // Remove last card from dealer hand
        dealerHand.GetCards().pop_back();          
    }
    // Player has a card total of 10
    userHand.SetCardsTotal(10);
    // Dealer has a face up card value of 2 through 9
    for (int i = 1; i < 9; i++) {
        // Add card to dealer hand
        dealerHand.SetCards(Card(Ranks[i], Suits[0]));
        // Test strategy - Can double down
        userHand.SetWager(10);
        blackjack_strategy(userHand, dealerHand);
        ASSERT_TRUE(userHand.GetShouldDoubleDown());
        ASSERT_TRUE(userHand.GetShouldHit());
        ASSERT_FALSE(userHand.GetShouldSplit());
        ASSERT_FALSE(userHand.GetShouldStand());
        // Test strategy - Can't double down
        userHand.SetWager(200);
        blackjack_strategy(userHand, dealerHand);
        ASSERT_FALSE(userHand.GetShouldDoubleDown());
        ASSERT_TRUE(userHand.GetShouldHit());
        ASSERT_FALSE(userHand.GetShouldSplit());
        ASSERT_FALSE(userHand.GetShouldStand());
        // Remove last card from dealer hand
        dealerHand.GetCards().pop_back(); 
    }
    // Dealer has a face up card value of 10 or Ace
    for (int i = 9; i < 13; i++) {
        userHand.SetWager(10);
        // Add card to dealer hand
        dealerHand.SetCards(Card(Ranks[i], Suits[0]));
        // Test strategy - Can double down
        blackjack_strategy(userHand, dealerHand);
        ASSERT_FALSE(userHand.GetShouldDoubleDown());
        ASSERT_TRUE(userHand.GetShouldHit());
        ASSERT_FALSE(userHand.GetShouldSplit());
        ASSERT_FALSE(userHand.GetShouldStand());
        // Test strategy - For Ace in dealer hand
        dealerHand.GetCards().pop_back();
        dealerHand.SetCards(Card(Ranks[0], Suits[0]));
        blackjack_strategy(userHand, dealerHand);
        ASSERT_FALSE(userHand.GetShouldDoubleDown());
        ASSERT_TRUE(userHand.GetShouldHit());
        ASSERT_FALSE(userHand.GetShouldSplit());
        ASSERT_FALSE(userHand.GetShouldStand());
        // Remove last card from dealer hand
        dealerHand.GetCards().pop_back();  
    }
}