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

// Card Class Test
TEST_F(test_x, TestCardClass){
    // Create Card
    shared_ptr<Card> testAce(new Card(Ranks[0], Suits[0]));
    // Test For Correct Rank
    EXPECT_TRUE(testAce->CheckCardParam(testAce->GetRank(), Ranks[0]));
    // Test For Incorrect Rank
    for (int i = 1; i < 13; i++) {
        EXPECT_FALSE(testAce->CheckCardParam(testAce->GetRank(), Ranks[i]));
    }
    // Test For Correct Suit
    EXPECT_TRUE(testAce->CheckCardParam(testAce->GetSuit(), Suits[0]));
    // Test For Incorrect Suit
    for (int i = 1; i < 4; i++) {
        EXPECT_FALSE(testAce->CheckCardParam(testAce->GetSuit(), Suits[i]));
    }
    // Test For Correct Card Value
    EXPECT_EQ(11, testAce->GetCardValue());
    // Test For Incorrect Card Value
    for (int i = 1; i < 11; i++) {
        EXPECT_NE(i, testAce->GetCardValue());
    }
    // Test For Changing of Value
    for (int i = 1; i < 11; i++) {
        testAce->SetNewCardValue(i);
        EXPECT_EQ(i, testAce->GetCardValue());
    }
}

// Shoe Class Test
TEST_F(test_x, TestShoeClass) {
    // Create Shoe
    shared_ptr<Shoe> testShoe(new Shoe);
    // Test For Empty Shoe
    EXPECT_TRUE(testShoe->GetNumOfDecks() == 0);
    EXPECT_TRUE(testShoe->GetCardsInShoe().size() == 0);
    EXPECT_TRUE(testShoe->GetRiggedCards().size() == 0);
    // Test For Different Sizes of Shoe
    for (int i = 1; i <= 50; i++) {
        testShoe->SetNumOfDecks(i);
        testShoe->CreateShoe();
        EXPECT_EQ(52 * i, testShoe->GetCardsInShoe().size());
        testShoe->EmptyShoe();
        EXPECT_EQ(0, testShoe->GetCardsInShoe().size());
    }
}

// Hand Class Test
TEST_F(test_x, TestHandClass) {
    // Create Hand Object
    Hand testHand;
    Hand dealerHand;
    // Test For Default Values Off Initializing
    // Boolean Values
    EXPECT_FALSE(testHand.GetCanBuyInsurance());
    EXPECT_FALSE(testHand.GetCanDoubleDown());
    EXPECT_FALSE(testHand.GetCanSplitAces());
    EXPECT_FALSE(testHand.GetCanSplitHand());
    EXPECT_FALSE(testHand.GetChoseBuyInsurance());
    EXPECT_FALSE(testHand.GetChoseDoubleDown());
    EXPECT_FALSE(testHand.GetChoseSplitAces());
    EXPECT_FALSE(testHand.GetChoseSplitHand());
    EXPECT_FALSE(testHand.GetDoubleDownResponse());
    EXPECT_FALSE(testHand.GetHasBlackJack());
    EXPECT_FALSE(testHand.GetHasHit());
    EXPECT_FALSE(testHand.GetParamInHand());
    EXPECT_FALSE(testHand.GetSameParamInHand());
    EXPECT_FALSE(testHand.GetSplitAcesResponse());
    EXPECT_FALSE(testHand.GetSplitHandResponse());
    // Float Values
    EXPECT_EQ(0, testHand.GetBankTotal());
    EXPECT_EQ(0, testHand.GetInsuranceWager());
    EXPECT_EQ(0, testHand.GetNet());
    EXPECT_EQ(0, testHand.GetWager());
    // Integer Values
    EXPECT_EQ(0, testHand.GetCardsTotal());
    EXPECT_EQ(0, testHand.GetHandsPlayed());
    EXPECT_EQ(0, testHand.GetIndividualHands());
    // Strings - Excluding Display Strings
    EXPECT_EQ("", testHand.GetName());
    // Vectors
    EXPECT_EQ(0, testHand.GetCards().size());
    EXPECT_EQ(0, testHand.GetHandBankTotals().size());
    EXPECT_EQ(0, testHand.GetHandCardTotals().size());
    EXPECT_EQ(0, testHand.GetHandNets().size());
    EXPECT_EQ(0, testHand.GetHandPlayed().size());
    EXPECT_EQ(0, testHand.GetHandWagers().size());
    // Check Name Set Method
    std::string name = "FlurdBop";
    testHand.SetName(name);
    EXPECT_EQ(name, testHand.GetName());
    // Test Bank Total Set
    float testBank = 100.00;
    testHand.SetBankTotal(testBank);
    EXPECT_EQ(testBank, testHand.GetBankTotal());
    // Test Wager Set
    float testWager = 40;
    testHand.SetWager(testWager);
    testHand.UpdateBank(0, testWager);
    EXPECT_EQ(testWager, testHand.GetWager());
    EXPECT_EQ(testBank - testWager, testHand.GetBankTotal());
    // Check Add Card To Hand, Has Blackjack, Can Buy Insurance, Can Double Down, Can Split Hand And Aces
    Card testAce(Ranks[0], Suits[1]);
    Card testKing(Ranks[12], Suits[1]);
    Card dealerAce(Ranks[0], Suits[2]);
    Card dealerNine(Ranks[8], Suits[2]);
    testHand.AddCardToHand(testAce);
    testHand.AddCardToHand(testKing);
    dealerHand.AddCardToHand(dealerNine);
    dealerHand.AddCardToHand(dealerAce);
    testHand.ParametersCheck(testHand, dealerHand);
    dealerHand.ParametersCheck(dealerHand, dealerHand);
    EXPECT_TRUE(testHand.GetHasBlackJack());
    EXPECT_FALSE(dealerHand.GetHasBlackJack());
    EXPECT_TRUE(testHand.GetCanBuyInsurance());
    EXPECT_TRUE(testHand.GetCanDoubleDown());
    EXPECT_FALSE(testHand.GetCanSplitAces());
    EXPECT_FALSE(testHand.GetCanSplitHand());
}