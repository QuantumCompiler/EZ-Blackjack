#include <gtest/gtest.h>
#include "../app/Assets/Game/HPP/Core.hpp"

class test_x : public ::testing::Test {};

/////////////////////////////////////////
// Test Helper Functions
/////////////////////////////////////////

class NullBuffer : public std::streambuf {
public:
    int overflow(int c) { return c; } // Discard the data
};

/////////////////////////////////////////
// Tests start here
/////////////////////////////////////////

// Linked list test, init node
TEST_F(test_x, LinkedListInitNode) {
    LinkedList testList;
    float floatVal = 3.14;
    std::shared_ptr<LinkedListNode> testNode = testList.InitNode(floatVal);
    ASSERT_EQ(floatVal, testNode->value);
    ASSERT_EQ(nullptr, testNode->previousNode);
    ASSERT_EQ(nullptr, testNode->nextNode);
}

// Linked list test, set root
TEST_F(test_x, LinkedListRoot) {
    LinkedList testList;
    float floatVal = 4.15;
    std::shared_ptr<LinkedListNode> testRoot = testList.InitNode(floatVal);
    testList.SetRoot(testRoot);
    ASSERT_EQ(floatVal, testList.GetRoot()->value);
    ASSERT_EQ(nullptr, testList.GetRoot()->previousNode);
    ASSERT_EQ(nullptr, testList.GetRoot()->nextNode);
}

// Linked list test, set tail
TEST_F(test_x, LinkedListTail) {
    LinkedList testList;
    float floatVal = 6.15;
    std::shared_ptr<LinkedListNode> testTail = testList.InitNode(floatVal);
    testList.SetTail(testTail);
    ASSERT_EQ(floatVal, testList.GetTail()->value);
    ASSERT_EQ(nullptr, testList.GetTail()->previousNode);
    ASSERT_EQ(nullptr, testList.GetTail()->nextNode);
}

// Linked list, append node
TEST_F(test_x, LinkedListAppend) {
    LinkedList testList;
    float floatVal = 4.23;
    // Insert into empty list
    std::shared_ptr<LinkedListNode> testNode1 = testList.InitNode(floatVal);
    testList.AppendNode(testNode1);
    EXPECT_EQ(1, testList.GetSize());
    EXPECT_EQ(testNode1, testList.GetRoot());
    EXPECT_EQ(nullptr, testList.GetRoot()->previousNode);
    EXPECT_EQ(nullptr, testList.GetRoot()->nextNode);
    EXPECT_EQ(testNode1, testList.GetTail());
    EXPECT_EQ(nullptr, testList.GetTail()->previousNode);
    EXPECT_EQ(nullptr, testList.GetTail()->nextNode);
    floatVal = 5.32;
    // Insert into list with one element
    std::shared_ptr<LinkedListNode> testNode2 = testList.InitNode(floatVal);
    testList.AppendNode(testNode2);
    EXPECT_EQ(2, testList.GetSize());
    EXPECT_EQ(testNode1, testList.GetRoot());
    EXPECT_EQ(testNode2, testList.GetTail());
    EXPECT_EQ(nullptr, testList.GetRoot()->previousNode);
    EXPECT_EQ(testList.GetTail(), testList.GetRoot()->nextNode);
    EXPECT_EQ(testList.GetRoot(), testList.GetTail()->previousNode);
    EXPECT_EQ(nullptr, testList.GetTail()->nextNode);
    floatVal = 6.72;
    // Insert into list with two elements
    std::shared_ptr<LinkedListNode> testNode3 = testList.InitNode(floatVal);
    testList.AppendNode(testNode3);
    EXPECT_EQ(3, testList.GetSize());
    EXPECT_EQ(testNode1, testList.GetRoot());
    EXPECT_EQ(testNode3, testList.GetTail());
    EXPECT_EQ(nullptr, testList.GetRoot()->previousNode);
    EXPECT_EQ(testNode2, testList.GetRoot()->nextNode);
    EXPECT_EQ(testList.GetRoot(), testNode2->previousNode);
    EXPECT_EQ(testList.GetTail(), testNode2->nextNode);
    EXPECT_EQ(testNode2, testList.GetTail()->previousNode);
    EXPECT_EQ(nullptr, testList.GetTail()->nextNode);
}

// Linked list, pop node
TEST_F(test_x, LinkedListPop) {
    LinkedList testList;
    float floatVal = 3.14;
    // Check on empty list
    std::shared_ptr<LinkedListNode> emptyNode = testList.PopNode();
    EXPECT_EQ(0, testList.GetSize());
    EXPECT_EQ(nullptr, emptyNode);
    EXPECT_EQ(emptyNode, testList.GetRoot());
    // Test on list with one element
    std::shared_ptr<LinkedListNode> testNode1 = testList.InitNode(floatVal);
    testList.AppendNode(testNode1);
    std::shared_ptr<LinkedListNode> poppedNode = testList.PopNode();
    EXPECT_EQ(0, testList.GetSize());
    EXPECT_EQ(nullptr, testList.GetRoot());
    EXPECT_EQ(nullptr, testList.GetTail());
    EXPECT_EQ(poppedNode, testNode1);
    EXPECT_EQ(nullptr, poppedNode->previousNode);
    EXPECT_EQ(nullptr, poppedNode->nextNode);
    // Test on list with two elements
    floatVal = 4.25;
    std::shared_ptr<LinkedListNode> testNode2 = testList.InitNode(floatVal);
    floatVal = 5.37;
    std::shared_ptr<LinkedListNode> testNode3 = testList.InitNode(floatVal);
    // Add test nodes
    testList.AppendNode(testNode2);
    testList.AppendNode(testNode3);
    // Pop node
    poppedNode = testList.PopNode();
    EXPECT_EQ(1, testList.GetSize());
    EXPECT_EQ(testNode2, testList.GetRoot());
    EXPECT_EQ(testNode2, testList.GetTail());
    EXPECT_EQ(poppedNode, testNode3);
    // Pop node again
    poppedNode = testList.PopNode();
    EXPECT_EQ(0, testList.GetSize());
    EXPECT_EQ(nullptr, testList.GetRoot());
    EXPECT_EQ(nullptr, testList.GetTail());
    EXPECT_EQ(poppedNode, testNode2);
    // Attempt to pop node again (empty list now)
    poppedNode = testList.PopNode();
    EXPECT_EQ(nullptr, testList.GetRoot());
    EXPECT_EQ(nullptr, testList.GetTail());
    EXPECT_EQ(nullptr, poppedNode);
}

// Linked list, clear list
TEST_F(test_x, LinkedListClear) {
    LinkedList testList;
    float floatVal = 4.23;
    // Insert into empty list
    std::shared_ptr<LinkedListNode> testNode1 = testList.InitNode(floatVal);
    testList.AppendNode(testNode1);
    EXPECT_EQ(1, testList.GetSize());
    EXPECT_EQ(testNode1, testList.GetRoot());
    EXPECT_EQ(nullptr, testList.GetRoot()->previousNode);
    EXPECT_EQ(nullptr, testList.GetRoot()->nextNode);
    EXPECT_EQ(testNode1, testList.GetTail());
    EXPECT_EQ(nullptr, testList.GetTail()->previousNode);
    EXPECT_EQ(nullptr, testList.GetTail()->nextNode);
    testList.ClearList();
    EXPECT_EQ(0, testList.GetSize());
    EXPECT_EQ(nullptr, testList.GetRoot());
    EXPECT_EQ(nullptr, testList.GetTail());
}

// Blackjack strategy test, no duplicate ranks, no ace in hand off deal
TEST_F(test_x, BlackjackStrat){
    // Suppress Cout's
    std::streambuf* oldCoutBuffer = std::cout.rdbuf();
    NullBuffer nullBuffer;
    std::cout.rdbuf(&nullBuffer);
    // Create hands
    Hand userHand;
    Hand dealerHand;
    userHand.SetBankTotal(100);
    // Add first card to dealer
    dealerHand.SetCards(Card(Ranks[0], Suits[0]));
    // Add dummy cards to user hand
    userHand.SetCards(Card(Ranks[1], Suits[0]));
    userHand.SetCards(Card(Ranks[12], Suits[0]));
    // Player has a card total of 4 through 8
    for (int i = 4; i <= 8; i++) {
        userHand.SetCardsTotal(i);
        userHand.SetWager(10);
        for (int j = 0; j < 13; j++) {
            // Add card to dealer hand
            dealerHand.SetCards(Card(Ranks[j], Suits[0]));
            blackjack_strategy(userHand, dealerHand);
            ASSERT_FALSE(userHand.GetShouldDoubleDown());
            ASSERT_TRUE(userHand.GetShouldHit());
            ASSERT_FALSE(userHand.GetShouldSplit());
            ASSERT_FALSE(userHand.GetShouldStand());
            dealerHand.GetCards().pop_back();
        }
    }
    // Player has a card total of 9
    userHand.SetCardsTotal(9);
    for (int i = 0; i < 13; i++) {
        // Add card to dealer hand
        dealerHand.SetCards(Card(Ranks[i], Suits[0]));
        // Dealer has a 2 - 6
        if (i != 0 && i < 6) {
            // Test strategy for if a player can double down
            {   
                // Set wager
                userHand.SetWager(10);
                // Test strategy
                blackjack_strategy(userHand, dealerHand);
                ASSERT_TRUE(userHand.GetShouldDoubleDown());
                ASSERT_TRUE(userHand.GetShouldHit());
                ASSERT_FALSE(userHand.GetShouldSplit());
                ASSERT_FALSE(userHand.GetShouldStand());
            }
            // Test strategy for if a player cannot double down
            {
                // Set wager
                userHand.SetWager(200);
                // Test strategy
                blackjack_strategy(userHand, dealerHand);
                ASSERT_FALSE(userHand.GetShouldDoubleDown());
                ASSERT_TRUE(userHand.GetShouldHit());
                ASSERT_FALSE(userHand.GetShouldSplit());
                ASSERT_FALSE(userHand.GetShouldStand());
            }
        }
        // Otherwise
        else {
            // Set wager
            userHand.SetWager(10);
            // Test strategy
            blackjack_strategy(userHand, dealerHand);
            ASSERT_FALSE(userHand.GetShouldDoubleDown());
            ASSERT_TRUE(userHand.GetShouldHit());
            ASSERT_FALSE(userHand.GetShouldSplit());
            ASSERT_FALSE(userHand.GetShouldStand());
        }    
        dealerHand.GetCards().pop_back();
    }
    // Player has a card total of 10
    userHand.SetCardsTotal(10);
    for (int i = 0; i < 13; i++) {
        // Add card to dealer hand
        dealerHand.SetCards(Card(Ranks[i], Suits[0]));
        // Dealer has a 2 - 9
        if (i != 0 && i < 9) {
            // Test strategy for if a player can double down
            {
                // Set wager
                userHand.SetWager(10);
                // Test strategy
                blackjack_strategy(userHand, dealerHand);
                ASSERT_TRUE(userHand.GetShouldDoubleDown());
                ASSERT_TRUE(userHand.GetShouldHit());
                ASSERT_FALSE(userHand.GetShouldSplit());
                ASSERT_FALSE(userHand.GetShouldStand());
            }
            // Test strategy for if a player cannot double down
            {
                // Set wager
                userHand.SetWager(200);
                // Test strategy
                blackjack_strategy(userHand, dealerHand);
                ASSERT_FALSE(userHand.GetShouldDoubleDown());
                ASSERT_TRUE(userHand.GetShouldHit());
                ASSERT_FALSE(userHand.GetShouldSplit());
                ASSERT_FALSE(userHand.GetShouldStand());
            }
        }
        // Otherwise
        else {
            // Set wager
            userHand.SetWager(10);
            // Test strategy
            blackjack_strategy(userHand, dealerHand);
            ASSERT_FALSE(userHand.GetShouldDoubleDown());
            ASSERT_TRUE(userHand.GetShouldHit());
            ASSERT_FALSE(userHand.GetShouldSplit());
            ASSERT_FALSE(userHand.GetShouldStand());
        }
        dealerHand.GetCards().pop_back();
    }
    // Player has a hand card value of 11
    userHand.SetCardsTotal(11);
    for (int i = 0; i < 13; i++) {
        // Player can double down
        {
            userHand.SetWager(10);
            // Add card to dealer hand
            dealerHand.SetCards(Card(Ranks[i], Suits[0]));
            // Test strategy - Can double down
            blackjack_strategy(userHand, dealerHand);
            ASSERT_TRUE(userHand.GetShouldDoubleDown());
            ASSERT_TRUE(userHand.GetShouldHit());
            ASSERT_FALSE(userHand.GetShouldSplit());
            ASSERT_FALSE(userHand.GetShouldStand());
            // Remove last card from dealer hand
            dealerHand.GetCards().pop_back();                  
        }
        // Player cannot double down
        {
            userHand.SetWager(200);
            // Add card to dealer hand
            dealerHand.SetCards(Card(Ranks[i], Suits[0]));
            // Test strategy - Can double down
            blackjack_strategy(userHand, dealerHand);
            ASSERT_FALSE(userHand.GetShouldDoubleDown());
            ASSERT_TRUE(userHand.GetShouldHit());
            ASSERT_FALSE(userHand.GetShouldSplit());
            ASSERT_FALSE(userHand.GetShouldStand());
            // Remove last card from dealer hand
            dealerHand.GetCards().pop_back();         
        }
    }
    // Player has a hand card value of 12
    userHand.SetCardsTotal(12);
    for (int i = 0; i < 13; i++) {
        userHand.SetWager(10);
        // Add card to dealer hand
        dealerHand.SetCards(Card(Ranks[i], Suits[0]));
        blackjack_strategy(userHand, dealerHand);
        // Test strategy for 4, 5, and 6 cards
        if (i == 3 || i == 4 || i == 5) {
            ASSERT_FALSE(userHand.GetShouldDoubleDown());
            ASSERT_FALSE(userHand.GetShouldHit());
            ASSERT_FALSE(userHand.GetShouldSplit());
            ASSERT_TRUE(userHand.GetShouldStand());
        }
        // Test strategy for other cards
        else {
            ASSERT_FALSE(userHand.GetShouldDoubleDown());
            ASSERT_TRUE(userHand.GetShouldHit());
            ASSERT_FALSE(userHand.GetShouldSplit());
            ASSERT_FALSE(userHand.GetShouldStand());
        }
        dealerHand.GetCards().pop_back();
    }
    // Player has a hand card value of 13 through 16
    for (int i = 13; i <= 16; i++) {
        userHand.SetCardsTotal(i);
        userHand.SetWager(10);
        for (int j = 0; j < 13; j++) {
            // Add card to dealer hand
            dealerHand.SetCards(Card(Ranks[j], Suits[0]));
            blackjack_strategy(userHand, dealerHand);
            // Test strategy for 2 through 6
            if (j != 0 && j < 6) {
                ASSERT_FALSE(userHand.GetShouldDoubleDown());
                ASSERT_FALSE(userHand.GetShouldHit());
                ASSERT_FALSE(userHand.GetShouldSplit());
                ASSERT_TRUE(userHand.GetShouldStand());
            }
            // Test strategy otherwise
            else {
                ASSERT_FALSE(userHand.GetShouldDoubleDown());
                ASSERT_TRUE(userHand.GetShouldHit());
                ASSERT_FALSE(userHand.GetShouldSplit());
                ASSERT_FALSE(userHand.GetShouldStand());
            }
            dealerHand.GetCards().pop_back();
        }
    }
    // Player has a hand card value of 17 through 21
    for (int i = 17; i <= 21; i++) {
        userHand.SetCardsTotal(i);
        userHand.SetWager(10);
        for (int j = 0; j < 13; j++) {
            // Add card to dealer hand
            dealerHand.SetCards(Card(Ranks[j], Suits[0]));
            blackjack_strategy(userHand, dealerHand);
            ASSERT_FALSE(userHand.GetShouldDoubleDown());
            ASSERT_FALSE(userHand.GetShouldHit());
            ASSERT_FALSE(userHand.GetShouldSplit());
            ASSERT_TRUE(userHand.GetShouldStand());
            dealerHand.GetCards().pop_back();
        }
    }
    std::cout.rdbuf(oldCoutBuffer);
}

// Blackjack strategy test, no duplicate ranks, Ace in hand off deal
TEST_F(test_x, BlackjackStratAces) {
    // Suppress Cout's
    std::streambuf* oldCoutBuffer = std::cout.rdbuf();
    NullBuffer nullBuffer;
    std::cout.rdbuf(&nullBuffer);
    // Create hands
    Hand userHand;
    Hand dealerHand;
    userHand.SetBankTotal(100);
    // Add first card to dealer
    dealerHand.SetCards(Card(Ranks[0], Suits[0]));
    dealerHand.AddHandTotal();
    // Add first card to player - Ace
    userHand.SetCards(Card(Ranks[0], Suits[0]));
    userHand.AddHandTotal();
    // Player has a card total of 13 or 14 (Ace, 2 || Ace, 3)
    for (int i = 1; i <= 2; i++) {
        userHand.SetCards(Card(Ranks[i], Suits[0]));
        userHand.AddHandTotal();
        for (int j = 0; j < 13; j++) {
            // Add card to dealer hand
            dealerHand.SetCards(Card(Ranks[j], Suits[0]));
            // Card being added is a 5 or 6
            if (j == 4 || j == 5) {
                // Player can double down
                {
                    // Set wager
                    userHand.SetWager(10);
                    // Test strategy - Can double down
                    blackjack_strategy(userHand, dealerHand);
                    ASSERT_TRUE(userHand.GetShouldDoubleDown());
                    ASSERT_TRUE(userHand.GetShouldHit());
                    ASSERT_FALSE(userHand.GetShouldSplit());
                    ASSERT_FALSE(userHand.GetShouldStand());
                }
                // Player can't double down
                {
                    // Set wager
                    userHand.SetWager(200);
                    // Test strategy - Can't double down
                    blackjack_strategy(userHand, dealerHand);
                    ASSERT_FALSE(userHand.GetShouldDoubleDown());
                    ASSERT_TRUE(userHand.GetShouldHit());
                    ASSERT_FALSE(userHand.GetShouldSplit());
                    ASSERT_FALSE(userHand.GetShouldStand());
                }
            }
            // Otherwise
            else {
                // Set wager
                userHand.SetWager(10);
                // Test strategy - Can't double down
                blackjack_strategy(userHand, dealerHand);
                ASSERT_FALSE(userHand.GetShouldDoubleDown());
                ASSERT_TRUE(userHand.GetShouldHit());
                ASSERT_FALSE(userHand.GetShouldSplit());
                ASSERT_FALSE(userHand.GetShouldStand());
            }
            dealerHand.GetCards().pop_back();
        }
        userHand.GetCards().pop_back();
        userHand.AddHandTotal();
    }
    // Player has a card total of 15 or 16 (Ace, 4 || Ace, 5)
    for (int i = 3; i <= 4; i++) {
        userHand.SetCards(Card(Ranks[i], Suits[0]));
        userHand.AddHandTotal();
        for (int j = 0; j < 13; j++) {
            // Add card to dealer hand
            dealerHand.SetCards(Card(Ranks[j], Suits[0]));
            // Card being added is a 4, 5, or 6
            if (j == 3 || j == 4 || j == 5) {
                // Player can double down
                {
                    // Set wager
                    userHand.SetWager(10);
                    // Test strategy - Can double down
                    blackjack_strategy(userHand, dealerHand);
                    ASSERT_TRUE(userHand.GetShouldDoubleDown());
                    ASSERT_TRUE(userHand.GetShouldHit());
                    ASSERT_FALSE(userHand.GetShouldSplit());
                    ASSERT_FALSE(userHand.GetShouldStand());
                }
                // Player can't double down
                {
                    // Set wager
                    userHand.SetWager(200);
                    // Test strategy - Can't double down
                    blackjack_strategy(userHand, dealerHand);
                    ASSERT_FALSE(userHand.GetShouldDoubleDown());
                    ASSERT_TRUE(userHand.GetShouldHit());
                    ASSERT_FALSE(userHand.GetShouldSplit());
                    ASSERT_FALSE(userHand.GetShouldStand());
                }
            }
            // Otherwise
            else {
                // Set wager
                userHand.SetWager(10);
                // Test strategy
                blackjack_strategy(userHand, dealerHand);
                ASSERT_FALSE(userHand.GetShouldDoubleDown());
                ASSERT_TRUE(userHand.GetShouldHit());
                ASSERT_FALSE(userHand.GetShouldSplit());
                ASSERT_FALSE(userHand.GetShouldStand());
            }
            dealerHand.GetCards().pop_back();
        }
        userHand.GetCards().pop_back();
        userHand.AddHandTotal();
    }
    // Player has a card total of 17 (Ace, 6)
    {
        userHand.SetCards(Card(Ranks[5], Suits[0]));
        userHand.AddHandTotal();
        for (int i = 0; i < 13; i++) {
            // Add card to dealer hand
            dealerHand.SetCards(Card(Ranks[i], Suits[0]));
            if (i >= 2 && i <= 5) {
                // Player can double down
                {
                    // Set wager
                    userHand.SetWager(10);
                    // Test strategy - Can double down
                    blackjack_strategy(userHand, dealerHand);
                    ASSERT_TRUE(userHand.GetShouldDoubleDown());
                    ASSERT_TRUE(userHand.GetShouldHit());
                    ASSERT_FALSE(userHand.GetShouldSplit());
                    ASSERT_FALSE(userHand.GetShouldStand());
                }
                // Player can't double down
                {
                    // Set wager
                    userHand.SetWager(200);
                    // Test strategy - Can't double down
                    blackjack_strategy(userHand, dealerHand);
                    ASSERT_FALSE(userHand.GetShouldDoubleDown());
                    ASSERT_TRUE(userHand.GetShouldHit());
                    ASSERT_FALSE(userHand.GetShouldSplit());
                    ASSERT_FALSE(userHand.GetShouldStand());
                }
            }
            // Otherwise
            else {
                // Set wager
                userHand.SetWager(10);
                // Test strategy
                blackjack_strategy(userHand, dealerHand);
                ASSERT_FALSE(userHand.GetShouldDoubleDown());
                ASSERT_TRUE(userHand.GetShouldHit());
                ASSERT_FALSE(userHand.GetShouldSplit());
                ASSERT_FALSE(userHand.GetShouldStand());
            }
            dealerHand.GetCards().pop_back();
        }
        userHand.GetCards().pop_back();
        userHand.AddHandTotal();
    }
    // Player card total is 18 (Ace, 7)
    {
        userHand.SetCards(Card(Ranks[6], Suits[0]));
        userHand.AddHandTotal();
        for (int i = 0; i < 13; i++) {
            // Add card to dealer hand
            dealerHand.SetCards(Card(Ranks[i], Suits[0]));
            if (i == 1 || i == 6 || i == 7) {
                // Set wager
                userHand.SetWager(10);
                // Test strategy
                blackjack_strategy(userHand, dealerHand);
                ASSERT_FALSE(userHand.GetShouldDoubleDown());
                ASSERT_FALSE(userHand.GetShouldHit());
                ASSERT_FALSE(userHand.GetShouldSplit());
                ASSERT_TRUE(userHand.GetShouldStand());
            }
            else if (i >= 2 && i <= 5) {
                // Player can double down
                {
                    // Set wager
                    userHand.SetWager(10);
                    // Test strategy - Can double down
                    blackjack_strategy(userHand, dealerHand);
                    ASSERT_TRUE(userHand.GetShouldDoubleDown());
                    ASSERT_FALSE(userHand.GetShouldHit());
                    ASSERT_FALSE(userHand.GetShouldSplit());
                    ASSERT_TRUE(userHand.GetShouldStand());
                }
                // Player can't double down
                {
                    // Set wager
                    userHand.SetWager(200);
                    // Test strategy - Can't double down
                    blackjack_strategy(userHand, dealerHand);
                    ASSERT_FALSE(userHand.GetShouldDoubleDown());
                    ASSERT_FALSE(userHand.GetShouldHit());
                    ASSERT_FALSE(userHand.GetShouldSplit());
                    ASSERT_TRUE(userHand.GetShouldStand());
                }
            }
            else {
                // Set wager
                userHand.SetWager(10);
                // Test strategy
                blackjack_strategy(userHand, dealerHand);
                ASSERT_FALSE(userHand.GetShouldDoubleDown());
                ASSERT_TRUE(userHand.GetShouldHit());
                ASSERT_FALSE(userHand.GetShouldSplit());
                ASSERT_FALSE(userHand.GetShouldStand());
            }
            dealerHand.GetCards().pop_back();
        }
        userHand.GetCards().pop_back();
        userHand.AddHandTotal();
    }
    // Player card total is 19, 20, or 21 (Ace, 8 || Ace, 9 || Ace, Ten)
    for (int i = 8; i <= 12; i++) {
        userHand.SetCards(Card(Ranks[i], Suits[0]));
        userHand.AddHandTotal();
        for (int j = 0; j < 13; j++) {
            // Add card to dealer hand
            dealerHand.SetCards(Card(Ranks[j], Suits[0]));
            // Set wager
            userHand.SetWager(200);
            // Test strategy
            blackjack_strategy(userHand, dealerHand);
            ASSERT_FALSE(userHand.GetShouldDoubleDown());
            ASSERT_FALSE(userHand.GetShouldHit());
            ASSERT_FALSE(userHand.GetShouldSplit());
            ASSERT_TRUE(userHand.GetShouldStand());
            dealerHand.GetCards().pop_back();
        }
        userHand.GetCards().pop_back();
        userHand.AddHandTotal();
    }
    std::cout.rdbuf(oldCoutBuffer);
}

// Blackjack strategy test, duplicate ranks
TEST_F(test_x, BlackjackStratDuplicates) {
    // Suppress Cout's
    std::streambuf* oldCoutBuffer = std::cout.rdbuf();
    NullBuffer nullBuffer;
    std::cout.rdbuf(&nullBuffer);
    // Create hands
    Hand userHand;
    Hand dealerHand;
    userHand.SetBankTotal(100);
    // Add first card to dealer
    dealerHand.SetCards(Card(Ranks[0], Suits[0]));
    dealerHand.AddHandTotal();
    // Player card total is 4 (two, two) or 6 (three, three)
    for (int i = 1; i <= 2; i++) {
        // Add cards to player hand
        userHand.AddCardToHand(Card(Ranks[i], Suits[0]));
        userHand.AddCardToHand(Card(Ranks[i], Suits[0]));
        for (int j = 0; j < 13; j++) {
            // Add card to dealer hand
            dealerHand.SetCards(Card(Ranks[j], Suits[0]));
            userHand.SetWager(10);
            // Can split hand
            {
                // Test strategy
                blackjack_strategy(userHand, dealerHand);
                if (j == 1 || j == 2) {
                    ASSERT_FALSE(userHand.GetShouldDoubleDown());
                    ASSERT_TRUE(userHand.GetShouldHit());
                    ASSERT_TRUE(userHand.GetShouldSplit());
                    ASSERT_FALSE(userHand.GetShouldStand());
                }
                else if (j >= 3 && j <= 6) {
                    ASSERT_FALSE(userHand.GetShouldDoubleDown());
                    ASSERT_FALSE(userHand.GetShouldHit());
                    ASSERT_TRUE(userHand.GetShouldSplit());
                    ASSERT_FALSE(userHand.GetShouldStand());      
                }
                else {
                    ASSERT_FALSE(userHand.GetShouldDoubleDown());
                    ASSERT_TRUE(userHand.GetShouldHit());
                    ASSERT_FALSE(userHand.GetShouldSplit());
                    ASSERT_FALSE(userHand.GetShouldStand());
                }                
            }
            // Can't split hand
            {
                // Can't split
                userHand.SetSplitHandResponse(true);
                // Test strategy
                blackjack_strategy(userHand, dealerHand);
                ASSERT_FALSE(userHand.GetShouldDoubleDown());
                ASSERT_TRUE(userHand.GetShouldHit());
                ASSERT_FALSE(userHand.GetShouldSplit());
                ASSERT_FALSE(userHand.GetShouldStand());
                // Can split
                userHand.SetSplitHandResponse(false);
            }
            dealerHand.GetCards().pop_back();
        }
        userHand.GetCards().pop_back();
        userHand.GetCards().pop_back();
        userHand.AddHandTotal();
    }
    // Player card total is 8 (four, four)
    {
        // Add cards to player hand, set wager
        userHand.AddCardToHand(Card(Ranks[3], Suits[0]));
        userHand.AddCardToHand(Card(Ranks[3], Suits[0]));
        userHand.SetWager(10);
        for (int i = 0; i < 13; i++) {
            // Add card to dealer hand
            dealerHand.SetCards(Card(Ranks[i], Suits[0]));
            // Can split hand
            {
                // Test strategy
                blackjack_strategy(userHand, dealerHand);
                if (i == 4 || i == 5) {
                    ASSERT_FALSE(userHand.GetShouldDoubleDown());
                    ASSERT_TRUE(userHand.GetShouldHit());
                    ASSERT_TRUE(userHand.GetShouldSplit());
                    ASSERT_FALSE(userHand.GetShouldStand());
                }
                else {
                    ASSERT_FALSE(userHand.GetShouldDoubleDown());
                    ASSERT_TRUE(userHand.GetShouldHit());
                    ASSERT_FALSE(userHand.GetShouldSplit());
                    ASSERT_FALSE(userHand.GetShouldStand());
                }
            }
            // Can't split hand
            {
                // Can't split
                userHand.SetSplitHandResponse(true);
                // Test strategy
                blackjack_strategy(userHand, dealerHand);
                ASSERT_FALSE(userHand.GetShouldDoubleDown());
                ASSERT_TRUE(userHand.GetShouldHit());
                ASSERT_FALSE(userHand.GetShouldSplit());
                ASSERT_FALSE(userHand.GetShouldStand());
                // Can split
                userHand.SetSplitHandResponse(false);
            }
            dealerHand.GetCards().pop_back();
        }
        userHand.GetCards().pop_back();
        userHand.GetCards().pop_back();
        userHand.AddHandTotal();        
    }
    // Player card total is 10 (five, five)
    {
        // Add cards to player hand, set wager
        userHand.AddCardToHand(Card(Ranks[4], Suits[0]));
        userHand.AddCardToHand(Card(Ranks[4], Suits[0]));
        for (int i = 0; i < 13; i++) {
            // Add card to dealer hand
            dealerHand.SetCards(Card(Ranks[i], Suits[0]));
            if (i == 0 || i >= 9) {
                // Set wager
                userHand.SetWager(10);
                // Test strategy
                blackjack_strategy(userHand, dealerHand);
                ASSERT_FALSE(userHand.GetShouldDoubleDown());
                ASSERT_TRUE(userHand.GetShouldHit());
                ASSERT_FALSE(userHand.GetShouldSplit());
                ASSERT_FALSE(userHand.GetShouldStand());
            }
            else {
                // Can double down
                {
                    // Set wager
                    userHand.SetWager(10);
                    // Test strategy
                    blackjack_strategy(userHand, dealerHand);
                    ASSERT_TRUE(userHand.GetShouldDoubleDown());
                    ASSERT_TRUE(userHand.GetShouldHit());
                    ASSERT_FALSE(userHand.GetShouldSplit());
                    ASSERT_FALSE(userHand.GetShouldStand());
                }
                // Cannot double down
                {
                    // Set wager
                    userHand.SetWager(101);
                    // Test strategy
                    blackjack_strategy(userHand, dealerHand);
                    ASSERT_FALSE(userHand.GetShouldDoubleDown());
                    ASSERT_TRUE(userHand.GetShouldHit());
                    ASSERT_FALSE(userHand.GetShouldSplit());
                    ASSERT_FALSE(userHand.GetShouldStand());
                }
            }
            dealerHand.GetCards().pop_back();
        }
        userHand.GetCards().pop_back();
        userHand.GetCards().pop_back();
        userHand.AddHandTotal();
    }
    // Player card total is 12 (six, six || Ace, Ace) 
    {
        // Player has two sixes
        {
            // Add cards to player hand, set wager
            userHand.AddCardToHand(Card(Ranks[5], Suits[0]));
            userHand.AddCardToHand(Card(Ranks[5], Suits[0]));
            userHand.SetWager(10);
            for (int i = 0; i < 13; i++) {
                // Add card to dealer hand
                dealerHand.SetCards(Card(Ranks[i], Suits[0]));
                // Can split
                {
                    // Test strategy
                    blackjack_strategy(userHand, dealerHand);
                    if (i >= 1 && i <= 5) {
                        ASSERT_FALSE(userHand.GetShouldDoubleDown());
                        ASSERT_FALSE(userHand.GetShouldHit());
                        ASSERT_TRUE(userHand.GetShouldSplit());
                        ASSERT_FALSE(userHand.GetShouldStand());
                    }
                    else if (i == 6) {
                        ASSERT_FALSE(userHand.GetShouldDoubleDown());
                        ASSERT_TRUE(userHand.GetShouldHit());
                        ASSERT_TRUE(userHand.GetShouldSplit());
                        ASSERT_FALSE(userHand.GetShouldStand());
                    }
                    else {
                        ASSERT_FALSE(userHand.GetShouldDoubleDown());
                        ASSERT_TRUE(userHand.GetShouldHit());
                        ASSERT_FALSE(userHand.GetShouldSplit());
                        ASSERT_FALSE(userHand.GetShouldStand());
                    }
                }
                // Can't split
                {
                    userHand.SetSplitHandResponse(true);
                    // Test strategy
                    blackjack_strategy(userHand, dealerHand);
                    if ((i >= 1 && i <= 2) || (i == 0 || i >= 6)) {
                        ASSERT_FALSE(userHand.GetShouldDoubleDown());
                        ASSERT_TRUE(userHand.GetShouldHit());
                        ASSERT_FALSE(userHand.GetShouldSplit());
                        ASSERT_FALSE(userHand.GetShouldStand());
                    }
                    else {
                        ASSERT_FALSE(userHand.GetShouldDoubleDown());
                        ASSERT_FALSE(userHand.GetShouldHit());
                        ASSERT_FALSE(userHand.GetShouldSplit());
                        ASSERT_TRUE(userHand.GetShouldStand());
                    }
                    userHand.SetSplitHandResponse(false);
                }
                dealerHand.GetCards().pop_back();
            }
            userHand.GetCards().pop_back();
            userHand.GetCards().pop_back();
            userHand.AddHandTotal();
        }
        // Player has two aces
        {
            // Add cards to player hand, set wager
            userHand.AddCardToHand(Card(Ranks[0], Suits[0]));
            userHand.AddCardToHand(Card(Ranks[0], Suits[0]));
            userHand.SetWager(10);
            for (int i = 0; i < 13; i++) {
                // Add card to dealer hand
                dealerHand.SetCards(Card(Ranks[i], Suits[0]));
                // Can split
                {
                    // Test strategy
                    blackjack_strategy(userHand, dealerHand);
                    ASSERT_FALSE(userHand.GetShouldDoubleDown());
                    ASSERT_FALSE(userHand.GetShouldHit());
                    ASSERT_TRUE(userHand.GetShouldSplit());
                    ASSERT_FALSE(userHand.GetShouldStand());
                }
                // Can't split
                {
                    userHand.SetSplitAcesResponse(true);
                    // Test strategy
                    blackjack_strategy(userHand, dealerHand);
                    if ((i >= 1 && i <= 2) || (i == 0 || i >= 6)) {
                        ASSERT_FALSE(userHand.GetShouldDoubleDown());
                        ASSERT_TRUE(userHand.GetShouldHit());
                        ASSERT_FALSE(userHand.GetShouldSplit());
                        ASSERT_FALSE(userHand.GetShouldStand());
                    }
                    else {
                        ASSERT_FALSE(userHand.GetShouldDoubleDown());
                        ASSERT_FALSE(userHand.GetShouldHit());
                        ASSERT_FALSE(userHand.GetShouldSplit());
                        ASSERT_TRUE(userHand.GetShouldStand());
                    }
                    userHand.SetSplitAcesResponse(false);
                }
                dealerHand.GetCards().pop_back();
            }
            userHand.GetCards().pop_back();
            userHand.GetCards().pop_back();
            userHand.AddHandTotal();
        }
    }
    // Player card total is 14 (seven, seven) 
    {
        // Add cards to player hand, set wager
        userHand.AddCardToHand(Card(Ranks[6], Suits[0]));
        userHand.AddCardToHand(Card(Ranks[6], Suits[0]));
        userHand.SetWager(10);
        for (int i = 0; i < 13; i++) {
            // Add card to dealer hand
            dealerHand.SetCards(Card(Ranks[i], Suits[0]));
            // Can split
            {
                // Test strategy
                blackjack_strategy(userHand, dealerHand);
                if (i >= 1 && i <= 6) {
                    ASSERT_FALSE(userHand.GetShouldDoubleDown());
                    ASSERT_FALSE(userHand.GetShouldHit());
                    ASSERT_TRUE(userHand.GetShouldSplit());
                    ASSERT_FALSE(userHand.GetShouldStand());
                }
                else if (i == 7) {
                    ASSERT_FALSE(userHand.GetShouldDoubleDown());
                    ASSERT_TRUE(userHand.GetShouldHit());
                    ASSERT_TRUE(userHand.GetShouldSplit());
                    ASSERT_FALSE(userHand.GetShouldStand());
                }
                else {
                    ASSERT_FALSE(userHand.GetShouldDoubleDown());
                    ASSERT_TRUE(userHand.GetShouldHit());
                    ASSERT_FALSE(userHand.GetShouldSplit());
                    ASSERT_FALSE(userHand.GetShouldStand());
                }
            }
            // Can't split
            {
                userHand.SetSplitHandResponse(true);
                // Test strategy
                blackjack_strategy(userHand, dealerHand);
                if (i >= 1 && i <= 5) {
                    ASSERT_FALSE(userHand.GetShouldDoubleDown());
                    ASSERT_FALSE(userHand.GetShouldHit());
                    ASSERT_FALSE(userHand.GetShouldSplit());
                    ASSERT_TRUE(userHand.GetShouldStand());
                }
                else {
                    ASSERT_FALSE(userHand.GetShouldDoubleDown());
                    ASSERT_TRUE(userHand.GetShouldHit());
                    ASSERT_FALSE(userHand.GetShouldSplit());
                    ASSERT_FALSE(userHand.GetShouldStand());
                }
                userHand.SetSplitHandResponse(false);
            }
            dealerHand.GetCards().pop_back();
        }
        userHand.GetCards().pop_back();
        userHand.GetCards().pop_back();
        userHand.AddHandTotal();
    }
    // Player card total is 16 (eight, eight)
    {
        // Add cards to player hand, set wager
        userHand.AddCardToHand(Card(Ranks[7], Suits[0]));
        userHand.AddCardToHand(Card(Ranks[7], Suits[0]));
        userHand.SetWager(10);
        for (int i = 0; i < 13; i++) {
            // Add card to dealer hand
            dealerHand.SetCards(Card(Ranks[i], Suits[0]));
            // Can split
            {
                // Test strategy
                blackjack_strategy(userHand, dealerHand);
                ASSERT_FALSE(userHand.GetShouldDoubleDown());
                ASSERT_FALSE(userHand.GetShouldHit());
                ASSERT_TRUE(userHand.GetShouldSplit());
                ASSERT_FALSE(userHand.GetShouldStand());                
            }
            // Can't split
            {
                userHand.SetSplitHandResponse(true);
                // Test strategy
                blackjack_strategy(userHand, dealerHand);
                if (i >= 1 && i <= 5) {
                    ASSERT_FALSE(userHand.GetShouldDoubleDown());
                    ASSERT_FALSE(userHand.GetShouldHit());
                    ASSERT_FALSE(userHand.GetShouldSplit());
                    ASSERT_TRUE(userHand.GetShouldStand());
                }
                else {
                    ASSERT_FALSE(userHand.GetShouldDoubleDown());
                    ASSERT_TRUE(userHand.GetShouldHit());
                    ASSERT_FALSE(userHand.GetShouldSplit());
                    ASSERT_FALSE(userHand.GetShouldStand());
                }
                userHand.SetSplitHandResponse(false);
            }
            dealerHand.GetCards().pop_back();
        }
        userHand.GetCards().pop_back();
        userHand.GetCards().pop_back();
        userHand.AddHandTotal();
    }
    // Player card total is 18 (nine, nine)
    {
        // Add cards to player hand, set wager
        userHand.AddCardToHand(Card(Ranks[8], Suits[0]));
        userHand.AddCardToHand(Card(Ranks[8], Suits[0]));
        userHand.SetWager(10);
        for (int i = 0; i < 13; i++) {
            // Add card to dealer hand
            dealerHand.SetCards(Card(Ranks[i], Suits[0]));
            // Can split
            {
                // Test strategy
                blackjack_strategy(userHand, dealerHand); 
                if (i == 0 || i == 6 || i >= 9) {
                    ASSERT_FALSE(userHand.GetShouldDoubleDown());
                    ASSERT_FALSE(userHand.GetShouldHit());
                    ASSERT_FALSE(userHand.GetShouldSplit());
                    ASSERT_TRUE(userHand.GetShouldStand());
                }
                else {
                    ASSERT_FALSE(userHand.GetShouldDoubleDown());
                    ASSERT_FALSE(userHand.GetShouldHit());
                    ASSERT_TRUE(userHand.GetShouldSplit());
                    ASSERT_FALSE(userHand.GetShouldStand());
                }
            }
            // Can't split
            {
                userHand.SetSplitHandResponse(true);
                // Test strategy
                blackjack_strategy(userHand, dealerHand);
                ASSERT_FALSE(userHand.GetShouldDoubleDown());
                ASSERT_FALSE(userHand.GetShouldHit());
                ASSERT_FALSE(userHand.GetShouldSplit());
                ASSERT_TRUE(userHand.GetShouldStand());                
                userHand.SetSplitHandResponse(false);
            }
            dealerHand.GetCards().pop_back();
        }
        userHand.GetCards().pop_back();
        userHand.GetCards().pop_back();
        userHand.AddHandTotal();
    }
    // Player card total is 20 (face, face)
    {
        // Add cards to player hand, set wager
        for (int i = 9; i <= 12; i++) {
            userHand.AddCardToHand(Card(Ranks[i], Suits[0]));
            userHand.AddCardToHand(Card(Ranks[i], Suits[0]));
            userHand.SetWager(10);
            for (int j = 0; j < 13; j++) {
                // Add card to dealer hand
                dealerHand.SetCards(Card(Ranks[j], Suits[0]));
                // Can split
                {
                    // Test strategy
                    blackjack_strategy(userHand, dealerHand);
                    ASSERT_FALSE(userHand.GetShouldDoubleDown());
                    ASSERT_FALSE(userHand.GetShouldHit());
                    ASSERT_FALSE(userHand.GetShouldSplit());
                    ASSERT_TRUE(userHand.GetShouldStand()); 
                }
                // Can't split
                {
                    userHand.SetSplitHandResponse(true);
                    // Test strategy
                    blackjack_strategy(userHand, dealerHand);
                    ASSERT_FALSE(userHand.GetShouldDoubleDown());
                    ASSERT_FALSE(userHand.GetShouldHit());
                    ASSERT_FALSE(userHand.GetShouldSplit());
                    ASSERT_TRUE(userHand.GetShouldStand()); 
                    userHand.SetSplitHandResponse(false);                   
                }
                dealerHand.GetCards().pop_back(); 
            }
            userHand.GetCards().pop_back();
            userHand.GetCards().pop_back();
            userHand.AddHandTotal();
        }
    }
    std::cout.rdbuf(oldCoutBuffer);
}