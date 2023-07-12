// Chekout TEST_F functions bellow to learn what is being tested.
#include <gtest/gtest.h>
// #include "../code_1/<HEADER FILE>.hpp"
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