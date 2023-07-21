#include <gtest/gtest.h>
#include "../app/Assets/HPP/Core.hpp"

using namespace std;

class test_x : public ::testing::Test {};

/////////////////////////////////////////
// Test Helper Functions
/////////////////////////////////////////

std::tuple<Hand, Hand, Shoe> ObjectConstruct() {
    Hand userHand;
    userHand.SetName("Billy Bob");
    userHand.SetBankTotal(100);
    userHand.SetWager(10);
    Hand dealerHand;
    dealerHand.SetName("Dealer");
    Shoe testShoe;
    return std::make_tuple(userHand, dealerHand, testShoe);
}

/////////////////////////////////////////
// Tests start here
/////////////////////////////////////////

TEST_F(test_x, BlackjackStrat){
    // Test if a player has a card total of (5-8)
    for (int i = 4; i < 9; i++) {
        auto objects = ObjectConstruct();
        Hand userHand = std::get<0>(objects);
        Hand dealerHand = std::get<1>(objects);
        std::random_device rd;
        std::mt19937 gen(rd());
        int min = 0;
        int max = 12;
        std::uniform_int_distribution<int> dist(min, max);
        int randomRank = dist(gen);
        // Add random cards to dealer hand
        dealerHand.SetCards(Card(Ranks[randomRank], Suits[0]));
        dealerHand.SetCards(Card(Ranks[randomRank], Suits[0]));
        // Add dummy cards to user hand
        userHand.SetCards(Card(Ranks[1], Suits[0]));
        userHand.SetCards(Card(Ranks[2], Suits[0]));
        // Rig hand total
        userHand.SetCardsTotal(i);
        // Test strategy
        blackjack_strategy(userHand, dealerHand);
        ASSERT_FALSE(userHand.GetShouldDoubleDown());
        ASSERT_TRUE(userHand.GetShouldHit());
        ASSERT_FALSE(userHand.GetShouldSplit());
        ASSERT_FALSE(userHand.GetShouldStand());
    }
    // Testing for player hand equal to 9, dealer 2 through 6
    for (int i = 1; i < 6; i++) {
        auto objects = ObjectConstruct();
        Hand userHand = std::get<0>(objects);
        Hand dealerHand = std::get<1>(objects);
        // Add cards to dealer hand, 2 through 6
        dealerHand.SetCards(Card(Ranks[0], Suits[0]));
        dealerHand.SetCards(Card(Ranks[i], Suits[0]));
        // Add dummy cards to user hand
        userHand.SetCards(Card(Ranks[1], Suits[0]));
        userHand.SetCards(Card(Ranks[2], Suits[0]));
        // Rig hand total
        userHand.SetCardsTotal(9);
        // Test strategy
        blackjack_strategy(userHand, dealerHand);
        ASSERT_TRUE(userHand.GetShouldDoubleDown());
        ASSERT_TRUE(userHand.GetShouldHit());
        ASSERT_FALSE(userHand.GetShouldSplit());
        ASSERT_FALSE(userHand.GetShouldStand());
    }
    // Testing for player hand equal to 9, dealer 7 through Ace
    for (int i = 6; i < 13; i++) {
        auto objects = ObjectConstruct();
        Hand userHand = std::get<0>(objects);
        Hand dealerHand = std::get<1>(objects);
        // Add cards to dealer hand, 7 through king
        dealerHand.SetCards(Card(Ranks[0], Suits[0]));
        dealerHand.SetCards(Card(Ranks[i], Suits[0]));
        // Add dummy cards to user hand
        userHand.SetCards(Card(Ranks[1], Suits[0]));
        userHand.SetCards(Card(Ranks[2], Suits[0]));
        // Rig hand total
        userHand.SetCardsTotal(9);
        // Test strategy
        blackjack_strategy(userHand, dealerHand);
        ASSERT_FALSE(userHand.GetShouldDoubleDown());
        ASSERT_TRUE(userHand.GetShouldHit());
        ASSERT_FALSE(userHand.GetShouldSplit());
        ASSERT_FALSE(userHand.GetShouldStand());
        // Add cards to dealer hand, Ace in back
        dealerHand.ResetHand();
        dealerHand.SetCards(Card(Ranks[0], Suits[0]));
        dealerHand.SetCards(Card(Ranks[0], Suits[0]));
        // Test strategy
        blackjack_strategy(userHand, dealerHand);
        ASSERT_FALSE(userHand.GetShouldDoubleDown());
        ASSERT_TRUE(userHand.GetShouldHit());
        ASSERT_FALSE(userHand.GetShouldSplit());
        ASSERT_FALSE(userHand.GetShouldStand());    
    }
}