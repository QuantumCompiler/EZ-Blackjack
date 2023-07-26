#include <gtest/gtest.h>
#include "../app/Assets/Game/HPP/Shoe.hpp"

class test_x : public ::testing::Test {};

/////////////////////////////////////////
// Test Helper Functions
/////////////////////////////////////////

class NullBuffer : public std::streambuf {
public:
    int overflow(int c) { return c; } // Discard the data
};

/////////////////////////////////////////
// Linked List Tests
/////////////////////////////////////////

// Linked list test, init node
TEST_F(test_x, LinkedListInitNode) {
    // Integer list
    std::shared_ptr<LinkedList<int>> intList(new LinkedList<int>);
    int intVal = 13;
    std::shared_ptr<node<int>> intNode = intList->InitNode(intVal);
    ASSERT_TRUE(typeid(intNode->data) == typeid(int));
    ASSERT_EQ(intNode->nextNode, nullptr);
    ASSERT_EQ(intNode->previousNode, nullptr);
    ASSERT_EQ(intNode->data, intVal);
    // Float list
    std::shared_ptr<LinkedList<float>> floatList(new LinkedList<float>);
    float floatVal = 3.14;
    std::shared_ptr<node<float>> floatNode = floatList->InitNode(floatVal);
    ASSERT_TRUE(typeid(floatNode->data) == typeid(float));
    ASSERT_EQ(floatNode->nextNode, nullptr);
    ASSERT_EQ(floatNode->previousNode, nullptr);
    ASSERT_EQ(floatNode->data, floatVal);
    // Double list
    std::shared_ptr<LinkedList<double>> doubleList(new LinkedList<double>);
    double doubleVal = 3.141592654;
    std::shared_ptr<node<double>> doubleNode = doubleList->InitNode(doubleVal);
    ASSERT_TRUE(typeid(doubleNode->data) == typeid(double));
    ASSERT_EQ(doubleNode->nextNode, nullptr);
    ASSERT_EQ(doubleNode->previousNode, nullptr);
    ASSERT_EQ(doubleNode->data, doubleVal);
    // Long list
    std::shared_ptr<LinkedList<long>> longList(new LinkedList<long>);
    long longVal = 2147483647;
    std::shared_ptr<node<long>> longNode = longList->InitNode(longVal);
    ASSERT_TRUE(typeid(longNode->data) == typeid(long));
    ASSERT_EQ(longNode->nextNode, nullptr);
    ASSERT_EQ(longNode->previousNode, nullptr);
    ASSERT_EQ(longNode->data, longVal);
    // String list
    std::shared_ptr<LinkedList<std::string>> stringList(new LinkedList<std::string>);
    std::string stringVal = "Hello World!";
    std::shared_ptr<node<std::string>> stringNode = stringList->InitNode(stringVal);
    ASSERT_TRUE(typeid(stringNode->data) == typeid(std::string));
    ASSERT_EQ(stringNode->nextNode, nullptr);
    ASSERT_EQ(stringNode->previousNode, nullptr);
    ASSERT_EQ(stringNode->data, stringVal);
    // Card list
    std::shared_ptr<LinkedList<Card>> cardList(new LinkedList<Card>);
    std::shared_ptr<Card> testCard(new Card(Ranks[0], Suits[0]));
    std::shared_ptr<node<Card>> cardNode = cardList->InitNode(testCard);
    ASSERT_TRUE(typeid(cardNode->data) == typeid(Card));
    ASSERT_EQ(cardNode->nextNode, nullptr);
    ASSERT_EQ(cardNode->previousNode, nullptr);
    ASSERT_EQ(cardNode->data.GetCardValue(), 11);
    ASSERT_EQ(cardNode->data.GetRank(), Ranks[0]);
    ASSERT_EQ(cardNode->data.GetSuit(), Suits[0]);
}

// Linked list test, set root
TEST_F(test_x, LinkedListRoot) {
    std::shared_ptr<LinkedList<float>> testList(new LinkedList<float>);
    float floatVal = 4.15;
    std::shared_ptr<node<float>> testRoot = testList->InitNode(floatVal);
    testList->SetRoot(testRoot);
    ASSERT_EQ(testList->GetRoot()->data, floatVal);
    ASSERT_EQ(testList->GetRoot()->previousNode, nullptr);
    ASSERT_EQ(testList->GetRoot()->nextNode, nullptr);
}

// Linked list test, set tail
TEST_F(test_x, LinkedListTail) {
    std::shared_ptr<LinkedList<float>> testList(new LinkedList<float>);
    float floatVal = 6.15;
    std::shared_ptr<node<float>> testTail = testList->InitNode(floatVal);
    testList->SetTail(testTail);
    ASSERT_EQ(testList->GetTail()->data, floatVal);
    ASSERT_EQ(testList->GetTail()->previousNode, nullptr);
    ASSERT_EQ(testList->GetTail()->nextNode, nullptr);
}

// Linked list test, size
TEST_F(test_x, LinkedListSize) {
    std::shared_ptr<LinkedList<int>> testList(new LinkedList<int>);
    ASSERT_EQ(testList->GetSize(), 0);
    int intVal = 123;
    std::shared_ptr<node<int>> testNode = testList->InitNode(intVal);
    ASSERT_EQ(testList->GetSize(), 0);
    testList->SetRoot(testNode);
    ASSERT_EQ(testList->GetSize(), 1);
}

// Linked list, append node
TEST_F(test_x, LinkedListAppend) {
    std::shared_ptr<LinkedList<float>> testList(new LinkedList<float>);
    float floatVal = 4.23;
    // Insert into empty list
    std::shared_ptr<node<float>> testNode1 = testList->InitNode(floatVal);
    testList->AppendNode(testNode1);
    EXPECT_EQ(testList->GetSize(), 1);
    EXPECT_EQ(testList->GetRoot(), testNode1);
    EXPECT_EQ(testList->GetRoot()->previousNode, nullptr);
    EXPECT_EQ(testList->GetRoot()->nextNode, nullptr);
    EXPECT_EQ(testList->GetTail(), testNode1);
    EXPECT_EQ(testList->GetTail()->previousNode, nullptr);
    EXPECT_EQ(testList->GetTail()->nextNode, nullptr);
    floatVal = 5.32;
    // Insert into list with one element
    std::shared_ptr<node<float>> testNode2 = testList->InitNode(floatVal);
    testList->AppendNode(testNode2);
    EXPECT_EQ(testList->GetSize(), 2);
    EXPECT_EQ(testList->GetRoot(), testNode1);
    EXPECT_EQ(testList->GetTail(), testNode2);
    EXPECT_EQ(testList->GetRoot()->previousNode, nullptr);
    EXPECT_EQ(testList->GetTail(), testList->GetRoot()->nextNode);
    EXPECT_EQ(testList->GetRoot(), testList->GetTail()->previousNode);
    EXPECT_EQ(testList->GetTail()->nextNode, nullptr);
    floatVal = 6.72;
    // Insert into list with two elements
    std::shared_ptr<node<float>> testNode3 = testList->InitNode(floatVal);
    testList->AppendNode(testNode3);
    EXPECT_EQ(testList->GetSize(), 3);
    EXPECT_EQ(testList->GetRoot(), testNode1);
    EXPECT_EQ(testList->GetTail(), testNode3);
    EXPECT_EQ(testList->GetRoot()->previousNode, nullptr);
    EXPECT_EQ(testList->GetRoot()->nextNode, testNode2);
    EXPECT_EQ(testList->GetRoot(), testNode2->previousNode);
    EXPECT_EQ(testList->GetTail(), testNode2->nextNode);
    EXPECT_EQ(testList->GetTail()->previousNode, testNode2);
    EXPECT_EQ(testList->GetTail()->nextNode, nullptr);
}

// Linked list, pop node
TEST_F(test_x, LinkedListPop) {
    std::shared_ptr<LinkedList<int>> testList(new LinkedList<int>);
    int intVal = 3;
    // Check on empty list
    std::shared_ptr<node<int>> emptyNode = testList->PopNode();
    EXPECT_EQ(testList->GetSize(), 0);
    EXPECT_EQ(emptyNode, nullptr);
    EXPECT_EQ(testList->GetRoot(), emptyNode);
    // Test on list with one element
    std::shared_ptr<node<int>> testNode1 = testList->InitNode(intVal);
    testList->AppendNode(testNode1);
    std::shared_ptr<node<int>> poppedNode = testList->PopNode();
    EXPECT_EQ(testList->GetSize(), 0);
    EXPECT_EQ(testList->GetRoot(), nullptr);
    EXPECT_EQ(testList->GetTail(), nullptr);
    EXPECT_EQ(poppedNode, testNode1);
    EXPECT_EQ(poppedNode->previousNode, nullptr);
    EXPECT_EQ(poppedNode->nextNode, nullptr);
    // Test on list with two elements
    intVal = 4;
    std::shared_ptr<node<int>> testNode2 = testList->InitNode(intVal);
    intVal = 5;
    std::shared_ptr<node<int>> testNode3 = testList->InitNode(intVal);
    // Add test nodes
    testList->AppendNode(testNode2);
    testList->AppendNode(testNode3);
    // Pop node
    poppedNode = testList->PopNode();
    EXPECT_EQ(testList->GetSize(), 1);
    EXPECT_EQ(testList->GetRoot(), testNode2);
    EXPECT_EQ(testList->GetTail(), testNode2);
    EXPECT_EQ(poppedNode, testNode3);
    // Pop node again
    poppedNode = testList->PopNode();
    EXPECT_EQ(testList->GetSize(), 0);
    EXPECT_EQ(testList->GetRoot(), nullptr);
    EXPECT_EQ(testList->GetTail(), nullptr);
    EXPECT_EQ(poppedNode, testNode2);
    // Attempt to pop node again (empty list now)
    poppedNode = testList->PopNode();
    EXPECT_EQ(testList->GetRoot(), nullptr);
    EXPECT_EQ(testList->GetTail(), nullptr);
    EXPECT_EQ(poppedNode, nullptr);
}

// Linked list, clear list
TEST_F(test_x, LinkedListClear) {
    std::shared_ptr<LinkedList<double>> testList(new LinkedList<double>);
    double doubleVal = 3.141592654;
    // Insert into empty list
    std::shared_ptr<node<double>> testNode1 = testList->InitNode(doubleVal);
    testList->AppendNode(testNode1);
    EXPECT_EQ(testList->GetSize(), 1);
    EXPECT_EQ(testList->GetRoot(), testNode1);
    EXPECT_EQ(testList->GetRoot()->previousNode, nullptr);
    EXPECT_EQ(testList->GetRoot()->nextNode, nullptr);
    EXPECT_EQ(testList->GetTail(), testNode1);
    EXPECT_EQ(testList->GetTail()->previousNode, nullptr);
    EXPECT_EQ(testList->GetTail()->nextNode, nullptr);
    testList->ClearList();
    EXPECT_EQ(testList->GetSize(), 0);
    EXPECT_EQ(testList->GetRoot(), nullptr);
    EXPECT_EQ(testList->GetTail(), nullptr);
}

// Linked list, insert into list
TEST_F(test_x, LinkedListInsert) {
    std::shared_ptr<LinkedList<int>> testList(new LinkedList<int>);
    int intVal = 8;
    // Insert into empty list (testNode1)
    std::shared_ptr<node<int>> testNode1 = testList->InitNode(intVal);
    testList->InsertNode(testNode1, 0);
    EXPECT_EQ(testList->GetRoot(), testNode1);
    EXPECT_EQ(testList->GetTail(), testNode1);
    EXPECT_EQ(testNode1->nextNode, nullptr);
    EXPECT_EQ(testNode1->previousNode, nullptr);
    EXPECT_EQ(testList->GetSize(), 1);
    intVal = 10;
    // Insert at tail (testNode1, testNode2)
    std::shared_ptr<node<int>> testNode2 = testList->InitNode(intVal);
    testList->InsertNode(testNode2, 1);
    EXPECT_EQ(testList->GetRoot(), testNode1);
    EXPECT_EQ(testList->GetTail(), testNode2);
    EXPECT_EQ(testNode1->nextNode, testNode2);
    EXPECT_EQ(testNode2->previousNode, testNode1);
    EXPECT_EQ(testList->GetSize(), 2);
    intVal = 20;
    // Insert at root (testNode3, testNode1, testNode2)
    std::shared_ptr<node<int>> testNode3 = testList->InitNode(intVal);
    testList->InsertNode(testNode3, 0);
    EXPECT_EQ(testList->GetRoot()->nextNode, testNode1);
    EXPECT_EQ(testList->GetRoot()->nextNode->nextNode, testNode2);
    EXPECT_EQ(testNode1->previousNode, testNode3);
    EXPECT_EQ(testNode1->nextNode, testNode2);
    EXPECT_EQ(testList->GetSize(), 3);
    intVal = 30;
    // Insert in between (testNode3, testNode1, testNode4, testNode2)
    std::shared_ptr<node<int>> testNode4 = testList->InitNode(intVal);
    testList->InsertNode(testNode4, 2);
    EXPECT_EQ(testList->GetRoot()->nextNode->nextNode, testNode4);
    EXPECT_EQ(testList->GetTail()->previousNode, testNode4);
    EXPECT_EQ(testNode4->previousNode, testNode1);
    EXPECT_EQ(testNode4->nextNode, testNode2);
    EXPECT_EQ(testList->GetSize(), 4);
    intVal = 40;
    // Insert immediately after root (testNode3, testNode5, testNode1, testNode4, testNode2)
    std::shared_ptr<node<int>> testNode5 = testList->InitNode(intVal);
    testList->InsertNode(testNode5, 1);
    EXPECT_EQ(testList->GetRoot()->nextNode, testNode5);
    EXPECT_EQ(testList->GetTail()->previousNode->previousNode->previousNode, testNode5);
    EXPECT_EQ(testNode5->nextNode, testNode1);
    EXPECT_EQ(testNode5->previousNode, testNode3);
    EXPECT_EQ(testList->GetSize(), 5);
}

// Linked list, remove list
TEST_F(test_x, LinkedListRemove) {
    std::shared_ptr<LinkedList<int>> testList(new LinkedList<int>);
    int intVal = 12;
    // Create nodes
    std::shared_ptr<node<int>> testNode1 = testList->InitNode(intVal);
    intVal = 13;
    std::shared_ptr<node<int>> testNode2 = testList->InitNode(intVal);
    intVal = 14;
    std::shared_ptr<node<int>> testNode3 = testList->InitNode(intVal);
    intVal = 15;
    std::shared_ptr<node<int>> testNode4 = testList->InitNode(intVal);
    // Insert nodes (testNode1, testNode2, testNode3, testNode4)
    testList->AppendNode(testNode1);
    testList->AppendNode(testNode2);
    testList->AppendNode(testNode3);
    testList->AppendNode(testNode4);
    // Remove root (testNode2, testNode3, testNode4)
    testList->RemoveNode(0);
    EXPECT_EQ(testList->GetSize(), 3);
    EXPECT_EQ(testList->GetRoot(), testNode2);
    EXPECT_EQ(testList->GetTail(), testNode4);
    EXPECT_EQ(testNode2->nextNode, testNode3);;
    EXPECT_EQ(testNode3->previousNode, testNode2);
    EXPECT_EQ(testNode3->nextNode, testNode4);
    EXPECT_EQ(testNode4->previousNode, testNode3);
    // Remove tail (testNode2, testNode3)
    testList->RemoveNode(2);
    EXPECT_EQ(testList->GetSize(), 2);
    EXPECT_EQ(testList->GetRoot(), testNode2);
    EXPECT_EQ(testList->GetTail(), testNode3);
    EXPECT_EQ(testNode2->nextNode, testNode3);
    EXPECT_EQ(testNode3->previousNode, testNode2);
    // Clear list and repopulate (testNode1, testNode2, testNode3, testNode4)
    testList->ClearList();
    testList->AppendNode(testNode1);
    testList->AppendNode(testNode2);
    testList->AppendNode(testNode3);
    testList->AppendNode(testNode4);
    // Remove element 1 (testNode1, testNode3, testNode4)
    testList->RemoveNode(1);
    EXPECT_EQ(testList->GetSize(), 3);
    EXPECT_EQ(testList->GetRoot(), testNode1);
    EXPECT_EQ(testList->GetTail(), testNode4);
    EXPECT_EQ(testNode1->nextNode, testNode3);
    EXPECT_EQ(testNode3->previousNode, testNode1);
    EXPECT_EQ(testNode3->nextNode, testNode4);
    EXPECT_EQ(testNode4->previousNode, testNode3);
    // Remove element 1 again (testNode1, testNode4)
    testList->RemoveNode(1);
    EXPECT_EQ(testList->GetSize(), 2);
    EXPECT_EQ(testList->GetRoot(), testNode1);
    EXPECT_EQ(testList->GetTail(), testNode4);
    EXPECT_EQ(testNode1->nextNode, testNode4);
    EXPECT_EQ(testNode4->previousNode, testNode1);
    // Remove tail with out of bounds iterator (testNode1)
    testList->RemoveNode(123);
    EXPECT_EQ(testList->GetSize(), 1);
    EXPECT_EQ(testList->GetRoot(), testNode1);
    EXPECT_EQ(testList->GetTail(), testNode1);
    // Empty list
    testList->RemoveNode(124);
    EXPECT_EQ(testList->GetSize(), 0);
    EXPECT_EQ(testList->GetRoot(), nullptr);
    EXPECT_EQ(testList->GetTail(), nullptr);
    // Repopulate with just two elements, remove root (testNode1, testNode2)
    testList->AppendNode(testNode1);
    testList->AppendNode(testNode2);
    testList->RemoveNode(0);
    EXPECT_EQ(testList->GetSize(), 1);
    EXPECT_EQ(testList->GetRoot(), testNode2);
    EXPECT_EQ(testList->GetTail(), testNode2);
}

/////////////////////////////////////////
// Card Class Tests
/////////////////////////////////////////

// Card class test
TEST_F(test_x, CardClassConst) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 13; j++) {
            std::shared_ptr<Card> testCard(new Card(Ranks[j], Suits[i]));
            ASSERT_EQ(testCard->GetRank(), Ranks[j]);
            ASSERT_EQ(testCard->GetSuit(), Suits[i]);
            if (j == 0) {
                ASSERT_EQ(testCard->GetCardValue(), 11);
            }
            else if (j >= 1 && j <= 8) {
                ASSERT_EQ(testCard->GetCardValue(), j+1);
            }
            else {
                ASSERT_EQ(testCard->GetCardValue(), 10);
            }
        }
    }
    std::shared_ptr<Card> testCard(new Card(Ranks[0], Suits[0]));
    ASSERT_EQ(testCard->GetCardValue(), 11);
    testCard->SetNewCardValue(123);
    ASSERT_EQ(testCard->GetCardValue(), 123);
}

/////////////////////////////////////////
// Shoe Class Tests
/////////////////////////////////////////
// Shoe class constructor test
TEST_F(test_x, ShoeClassConst) {
    std::shared_ptr<Shoe> testShoe(new Shoe());
    EXPECT_EQ(testShoe->GetNumOfDecks(), 0);
    EXPECT_EQ(testShoe->GetCardsInShoe()->GetSize(), 0);
}

// Shoe class setter test
TEST_F(test_x, ShoeClassSet) {
    std::shared_ptr<Shoe> testShoe(new Shoe());
    // Set deck count
    int deckCount = 13;
    testShoe->SetNumOfDecks(deckCount);
    EXPECT_EQ(testShoe->GetNumOfDecks(), deckCount);
    // Append a card to the shoe of cards
    std::shared_ptr<Card> testCard1(new Card(Ranks[0], Suits[0]));
    std::shared_ptr<node<Card>> testNode1 = testShoe->GetCardsInShoe()->InitNode(testCard1);
    testShoe->SetCardsInShoe(testNode1);
    EXPECT_EQ(testShoe->GetCardsInShoe()->GetSize(), 1);
}

// Shoe class create shoe test
TEST_F(test_x, ShoeClassCreate) {
    std::shared_ptr<Shoe> testShoe(new Shoe());
    // Set deck count
    for (int i = 1; i <= 10; i++) {
        testShoe->SetNumOfDecks(i);
        testShoe->CreateShoe();
        EXPECT_EQ(testShoe->GetCardsInShoe()->GetSize(), testShoe->GetNumOfDecks()*52);
        testShoe->EmptyShoe();
        EXPECT_EQ(testShoe->GetCardsInShoe()->GetSize(), 0);
    }
}

// Shoe class, draw test
TEST_F(test_x, ShoeClassDraw) {
    std::shared_ptr<Shoe> testShoe(new Shoe());
    testShoe->SetNumOfDecks(1);
    testShoe->CreateShoe();
    EXPECT_EQ(testShoe->GetCardsInShoe()->GetSize(), testShoe->GetNumOfDecks()*52);
    for (int i = testShoe->GetNumOfDecks()*52; i > 0; i--) {
        std::shared_ptr<Card> poppedCard = testShoe->Draw();
        EXPECT_EQ(testShoe->GetCardsInShoe()->GetSize(), i - 1);
    }
}

/////////////////////////////////////////
// Blackjack Strategy Test
/////////////////////////////////////////

// // Blackjack strategy test, no duplicate ranks, no ace in hand off deal
// TEST_F(test_x, BlackjackStrat){
//     // Suppress Cout's
//     std::streambuf* oldCoutBuffer = std::cout.rdbuf();
//     NullBuffer nullBuffer;
//     std::cout.rdbuf(&nullBuffer);
//     // Create hands
//     Hand userHand;
//     Hand dealerHand;
//     userHand.SetBankTotal(100);
//     // Add first card to dealer
//     dealerHand.SetCards(Card(Ranks[0], Suits[0]));
//     // Add dummy cards to user hand
//     userHand.SetCards(Card(Ranks[1], Suits[0]));
//     userHand.SetCards(Card(Ranks[12], Suits[0]));
//     // Player has a card total of 4 through 8
//     for (int i = 4; i <= 8; i++) {
//         userHand.SetCardsTotal(i);
//         userHand.SetWager(10);
//         for (int j = 0; j < 13; j++) {
//             // Add card to dealer hand
//             dealerHand.SetCards(Card(Ranks[j], Suits[0]));
//             blackjack_strategy(userHand, dealerHand);
//             ASSERT_FALSE(userHand.GetShouldDoubleDown());
//             ASSERT_TRUE(userHand.GetShouldHit());
//             ASSERT_FALSE(userHand.GetShouldSplit());
//             ASSERT_FALSE(userHand.GetShouldStand());
//             dealerHand.GetCards().pop_back();
//         }
//     }
//     // Player has a card total of 9
//     userHand.SetCardsTotal(9);
//     for (int i = 0; i < 13; i++) {
//         // Add card to dealer hand
//         dealerHand.SetCards(Card(Ranks[i], Suits[0]));
//         // Dealer has a 2 - 6
//         if (i != 0 && i < 6) {
//             // Test strategy for if a player can double down
//             {   
//                 // Set wager
//                 userHand.SetWager(10);
//                 // Test strategy
//                 blackjack_strategy(userHand, dealerHand);
//                 ASSERT_TRUE(userHand.GetShouldDoubleDown());
//                 ASSERT_TRUE(userHand.GetShouldHit());
//                 ASSERT_FALSE(userHand.GetShouldSplit());
//                 ASSERT_FALSE(userHand.GetShouldStand());
//             }
//             // Test strategy for if a player cannot double down
//             {
//                 // Set wager
//                 userHand.SetWager(200);
//                 // Test strategy
//                 blackjack_strategy(userHand, dealerHand);
//                 ASSERT_FALSE(userHand.GetShouldDoubleDown());
//                 ASSERT_TRUE(userHand.GetShouldHit());
//                 ASSERT_FALSE(userHand.GetShouldSplit());
//                 ASSERT_FALSE(userHand.GetShouldStand());
//             }
//         }
//         // Otherwise
//         else {
//             // Set wager
//             userHand.SetWager(10);
//             // Test strategy
//             blackjack_strategy(userHand, dealerHand);
//             ASSERT_FALSE(userHand.GetShouldDoubleDown());
//             ASSERT_TRUE(userHand.GetShouldHit());
//             ASSERT_FALSE(userHand.GetShouldSplit());
//             ASSERT_FALSE(userHand.GetShouldStand());
//         }    
//         dealerHand.GetCards().pop_back();
//     }
//     // Player has a card total of 10
//     userHand.SetCardsTotal(10);
//     for (int i = 0; i < 13; i++) {
//         // Add card to dealer hand
//         dealerHand.SetCards(Card(Ranks[i], Suits[0]));
//         // Dealer has a 2 - 9
//         if (i != 0 && i < 9) {
//             // Test strategy for if a player can double down
//             {
//                 // Set wager
//                 userHand.SetWager(10);
//                 // Test strategy
//                 blackjack_strategy(userHand, dealerHand);
//                 ASSERT_TRUE(userHand.GetShouldDoubleDown());
//                 ASSERT_TRUE(userHand.GetShouldHit());
//                 ASSERT_FALSE(userHand.GetShouldSplit());
//                 ASSERT_FALSE(userHand.GetShouldStand());
//             }
//             // Test strategy for if a player cannot double down
//             {
//                 // Set wager
//                 userHand.SetWager(200);
//                 // Test strategy
//                 blackjack_strategy(userHand, dealerHand);
//                 ASSERT_FALSE(userHand.GetShouldDoubleDown());
//                 ASSERT_TRUE(userHand.GetShouldHit());
//                 ASSERT_FALSE(userHand.GetShouldSplit());
//                 ASSERT_FALSE(userHand.GetShouldStand());
//             }
//         }
//         // Otherwise
//         else {
//             // Set wager
//             userHand.SetWager(10);
//             // Test strategy
//             blackjack_strategy(userHand, dealerHand);
//             ASSERT_FALSE(userHand.GetShouldDoubleDown());
//             ASSERT_TRUE(userHand.GetShouldHit());
//             ASSERT_FALSE(userHand.GetShouldSplit());
//             ASSERT_FALSE(userHand.GetShouldStand());
//         }
//         dealerHand.GetCards().pop_back();
//     }
//     // Player has a hand card value of 11
//     userHand.SetCardsTotal(11);
//     for (int i = 0; i < 13; i++) {
//         // Player can double down
//         {
//             userHand.SetWager(10);
//             // Add card to dealer hand
//             dealerHand.SetCards(Card(Ranks[i], Suits[0]));
//             // Test strategy - Can double down
//             blackjack_strategy(userHand, dealerHand);
//             ASSERT_TRUE(userHand.GetShouldDoubleDown());
//             ASSERT_TRUE(userHand.GetShouldHit());
//             ASSERT_FALSE(userHand.GetShouldSplit());
//             ASSERT_FALSE(userHand.GetShouldStand());
//             // Remove last card from dealer hand
//             dealerHand.GetCards().pop_back();                  
//         }
//         // Player cannot double down
//         {
//             userHand.SetWager(200);
//             // Add card to dealer hand
//             dealerHand.SetCards(Card(Ranks[i], Suits[0]));
//             // Test strategy - Can double down
//             blackjack_strategy(userHand, dealerHand);
//             ASSERT_FALSE(userHand.GetShouldDoubleDown());
//             ASSERT_TRUE(userHand.GetShouldHit());
//             ASSERT_FALSE(userHand.GetShouldSplit());
//             ASSERT_FALSE(userHand.GetShouldStand());
//             // Remove last card from dealer hand
//             dealerHand.GetCards().pop_back();         
//         }
//     }
//     // Player has a hand card value of 12
//     userHand.SetCardsTotal(12);
//     for (int i = 0; i < 13; i++) {
//         userHand.SetWager(10);
//         // Add card to dealer hand
//         dealerHand.SetCards(Card(Ranks[i], Suits[0]));
//         blackjack_strategy(userHand, dealerHand);
//         // Test strategy for 4, 5, and 6 cards
//         if (i == 3 || i == 4 || i == 5) {
//             ASSERT_FALSE(userHand.GetShouldDoubleDown());
//             ASSERT_FALSE(userHand.GetShouldHit());
//             ASSERT_FALSE(userHand.GetShouldSplit());
//             ASSERT_TRUE(userHand.GetShouldStand());
//         }
//         // Test strategy for other cards
//         else {
//             ASSERT_FALSE(userHand.GetShouldDoubleDown());
//             ASSERT_TRUE(userHand.GetShouldHit());
//             ASSERT_FALSE(userHand.GetShouldSplit());
//             ASSERT_FALSE(userHand.GetShouldStand());
//         }
//         dealerHand.GetCards().pop_back();
//     }
//     // Player has a hand card value of 13 through 16
//     for (int i = 13; i <= 16; i++) {
//         userHand.SetCardsTotal(i);
//         userHand.SetWager(10);
//         for (int j = 0; j < 13; j++) {
//             // Add card to dealer hand
//             dealerHand.SetCards(Card(Ranks[j], Suits[0]));
//             blackjack_strategy(userHand, dealerHand);
//             // Test strategy for 2 through 6
//             if (j != 0 && j < 6) {
//                 ASSERT_FALSE(userHand.GetShouldDoubleDown());
//                 ASSERT_FALSE(userHand.GetShouldHit());
//                 ASSERT_FALSE(userHand.GetShouldSplit());
//                 ASSERT_TRUE(userHand.GetShouldStand());
//             }
//             // Test strategy otherwise
//             else {
//                 ASSERT_FALSE(userHand.GetShouldDoubleDown());
//                 ASSERT_TRUE(userHand.GetShouldHit());
//                 ASSERT_FALSE(userHand.GetShouldSplit());
//                 ASSERT_FALSE(userHand.GetShouldStand());
//             }
//             dealerHand.GetCards().pop_back();
//         }
//     }
//     // Player has a hand card value of 17 through 21
//     for (int i = 17; i <= 21; i++) {
//         userHand.SetCardsTotal(i);
//         userHand.SetWager(10);
//         for (int j = 0; j < 13; j++) {
//             // Add card to dealer hand
//             dealerHand.SetCards(Card(Ranks[j], Suits[0]));
//             blackjack_strategy(userHand, dealerHand);
//             ASSERT_FALSE(userHand.GetShouldDoubleDown());
//             ASSERT_FALSE(userHand.GetShouldHit());
//             ASSERT_FALSE(userHand.GetShouldSplit());
//             ASSERT_TRUE(userHand.GetShouldStand());
//             dealerHand.GetCards().pop_back();
//         }
//     }
//     std::cout.rdbuf(oldCoutBuffer);
// }

// // Blackjack strategy test, no duplicate ranks, Ace in hand off deal
// TEST_F(test_x, BlackjackStratAces) {
//     // Suppress Cout's
//     std::streambuf* oldCoutBuffer = std::cout.rdbuf();
//     NullBuffer nullBuffer;
//     std::cout.rdbuf(&nullBuffer);
//     // Create hands
//     Hand userHand;
//     Hand dealerHand;
//     userHand.SetBankTotal(100);
//     // Add first card to dealer
//     dealerHand.SetCards(Card(Ranks[0], Suits[0]));
//     dealerHand.AddHandTotal();
//     // Add first card to player - Ace
//     userHand.SetCards(Card(Ranks[0], Suits[0]));
//     userHand.AddHandTotal();
//     // Player has a card total of 13 or 14 (Ace, 2 || Ace, 3)
//     for (int i = 1; i <= 2; i++) {
//         userHand.SetCards(Card(Ranks[i], Suits[0]));
//         userHand.AddHandTotal();
//         for (int j = 0; j < 13; j++) {
//             // Add card to dealer hand
//             dealerHand.SetCards(Card(Ranks[j], Suits[0]));
//             // Card being added is a 5 or 6
//             if (j == 4 || j == 5) {
//                 // Player can double down
//                 {
//                     // Set wager
//                     userHand.SetWager(10);
//                     // Test strategy - Can double down
//                     blackjack_strategy(userHand, dealerHand);
//                     ASSERT_TRUE(userHand.GetShouldDoubleDown());
//                     ASSERT_TRUE(userHand.GetShouldHit());
//                     ASSERT_FALSE(userHand.GetShouldSplit());
//                     ASSERT_FALSE(userHand.GetShouldStand());
//                 }
//                 // Player can't double down
//                 {
//                     // Set wager
//                     userHand.SetWager(200);
//                     // Test strategy - Can't double down
//                     blackjack_strategy(userHand, dealerHand);
//                     ASSERT_FALSE(userHand.GetShouldDoubleDown());
//                     ASSERT_TRUE(userHand.GetShouldHit());
//                     ASSERT_FALSE(userHand.GetShouldSplit());
//                     ASSERT_FALSE(userHand.GetShouldStand());
//                 }
//             }
//             // Otherwise
//             else {
//                 // Set wager
//                 userHand.SetWager(10);
//                 // Test strategy - Can't double down
//                 blackjack_strategy(userHand, dealerHand);
//                 ASSERT_FALSE(userHand.GetShouldDoubleDown());
//                 ASSERT_TRUE(userHand.GetShouldHit());
//                 ASSERT_FALSE(userHand.GetShouldSplit());
//                 ASSERT_FALSE(userHand.GetShouldStand());
//             }
//             dealerHand.GetCards().pop_back();
//         }
//         userHand.GetCards().pop_back();
//         userHand.AddHandTotal();
//     }
//     // Player has a card total of 15 or 16 (Ace, 4 || Ace, 5)
//     for (int i = 3; i <= 4; i++) {
//         userHand.SetCards(Card(Ranks[i], Suits[0]));
//         userHand.AddHandTotal();
//         for (int j = 0; j < 13; j++) {
//             // Add card to dealer hand
//             dealerHand.SetCards(Card(Ranks[j], Suits[0]));
//             // Card being added is a 4, 5, or 6
//             if (j == 3 || j == 4 || j == 5) {
//                 // Player can double down
//                 {
//                     // Set wager
//                     userHand.SetWager(10);
//                     // Test strategy - Can double down
//                     blackjack_strategy(userHand, dealerHand);
//                     ASSERT_TRUE(userHand.GetShouldDoubleDown());
//                     ASSERT_TRUE(userHand.GetShouldHit());
//                     ASSERT_FALSE(userHand.GetShouldSplit());
//                     ASSERT_FALSE(userHand.GetShouldStand());
//                 }
//                 // Player can't double down
//                 {
//                     // Set wager
//                     userHand.SetWager(200);
//                     // Test strategy - Can't double down
//                     blackjack_strategy(userHand, dealerHand);
//                     ASSERT_FALSE(userHand.GetShouldDoubleDown());
//                     ASSERT_TRUE(userHand.GetShouldHit());
//                     ASSERT_FALSE(userHand.GetShouldSplit());
//                     ASSERT_FALSE(userHand.GetShouldStand());
//                 }
//             }
//             // Otherwise
//             else {
//                 // Set wager
//                 userHand.SetWager(10);
//                 // Test strategy
//                 blackjack_strategy(userHand, dealerHand);
//                 ASSERT_FALSE(userHand.GetShouldDoubleDown());
//                 ASSERT_TRUE(userHand.GetShouldHit());
//                 ASSERT_FALSE(userHand.GetShouldSplit());
//                 ASSERT_FALSE(userHand.GetShouldStand());
//             }
//             dealerHand.GetCards().pop_back();
//         }
//         userHand.GetCards().pop_back();
//         userHand.AddHandTotal();
//     }
//     // Player has a card total of 17 (Ace, 6)
//     {
//         userHand.SetCards(Card(Ranks[5], Suits[0]));
//         userHand.AddHandTotal();
//         for (int i = 0; i < 13; i++) {
//             // Add card to dealer hand
//             dealerHand.SetCards(Card(Ranks[i], Suits[0]));
//             if (i >= 2 && i <= 5) {
//                 // Player can double down
//                 {
//                     // Set wager
//                     userHand.SetWager(10);
//                     // Test strategy - Can double down
//                     blackjack_strategy(userHand, dealerHand);
//                     ASSERT_TRUE(userHand.GetShouldDoubleDown());
//                     ASSERT_TRUE(userHand.GetShouldHit());
//                     ASSERT_FALSE(userHand.GetShouldSplit());
//                     ASSERT_FALSE(userHand.GetShouldStand());
//                 }
//                 // Player can't double down
//                 {
//                     // Set wager
//                     userHand.SetWager(200);
//                     // Test strategy - Can't double down
//                     blackjack_strategy(userHand, dealerHand);
//                     ASSERT_FALSE(userHand.GetShouldDoubleDown());
//                     ASSERT_TRUE(userHand.GetShouldHit());
//                     ASSERT_FALSE(userHand.GetShouldSplit());
//                     ASSERT_FALSE(userHand.GetShouldStand());
//                 }
//             }
//             // Otherwise
//             else {
//                 // Set wager
//                 userHand.SetWager(10);
//                 // Test strategy
//                 blackjack_strategy(userHand, dealerHand);
//                 ASSERT_FALSE(userHand.GetShouldDoubleDown());
//                 ASSERT_TRUE(userHand.GetShouldHit());
//                 ASSERT_FALSE(userHand.GetShouldSplit());
//                 ASSERT_FALSE(userHand.GetShouldStand());
//             }
//             dealerHand.GetCards().pop_back();
//         }
//         userHand.GetCards().pop_back();
//         userHand.AddHandTotal();
//     }
//     // Player card total is 18 (Ace, 7)
//     {
//         userHand.SetCards(Card(Ranks[6], Suits[0]));
//         userHand.AddHandTotal();
//         for (int i = 0; i < 13; i++) {
//             // Add card to dealer hand
//             dealerHand.SetCards(Card(Ranks[i], Suits[0]));
//             if (i == 1 || i == 6 || i == 7) {
//                 // Set wager
//                 userHand.SetWager(10);
//                 // Test strategy
//                 blackjack_strategy(userHand, dealerHand);
//                 ASSERT_FALSE(userHand.GetShouldDoubleDown());
//                 ASSERT_FALSE(userHand.GetShouldHit());
//                 ASSERT_FALSE(userHand.GetShouldSplit());
//                 ASSERT_TRUE(userHand.GetShouldStand());
//             }
//             else if (i >= 2 && i <= 5) {
//                 // Player can double down
//                 {
//                     // Set wager
//                     userHand.SetWager(10);
//                     // Test strategy - Can double down
//                     blackjack_strategy(userHand, dealerHand);
//                     ASSERT_TRUE(userHand.GetShouldDoubleDown());
//                     ASSERT_FALSE(userHand.GetShouldHit());
//                     ASSERT_FALSE(userHand.GetShouldSplit());
//                     ASSERT_TRUE(userHand.GetShouldStand());
//                 }
//                 // Player can't double down
//                 {
//                     // Set wager
//                     userHand.SetWager(200);
//                     // Test strategy - Can't double down
//                     blackjack_strategy(userHand, dealerHand);
//                     ASSERT_FALSE(userHand.GetShouldDoubleDown());
//                     ASSERT_FALSE(userHand.GetShouldHit());
//                     ASSERT_FALSE(userHand.GetShouldSplit());
//                     ASSERT_TRUE(userHand.GetShouldStand());
//                 }
//             }
//             else {
//                 // Set wager
//                 userHand.SetWager(10);
//                 // Test strategy
//                 blackjack_strategy(userHand, dealerHand);
//                 ASSERT_FALSE(userHand.GetShouldDoubleDown());
//                 ASSERT_TRUE(userHand.GetShouldHit());
//                 ASSERT_FALSE(userHand.GetShouldSplit());
//                 ASSERT_FALSE(userHand.GetShouldStand());
//             }
//             dealerHand.GetCards().pop_back();
//         }
//         userHand.GetCards().pop_back();
//         userHand.AddHandTotal();
//     }
//     // Player card total is 19, 20, or 21 (Ace, 8 || Ace, 9 || Ace, Ten)
//     for (int i = 8; i <= 12; i++) {
//         userHand.SetCards(Card(Ranks[i], Suits[0]));
//         userHand.AddHandTotal();
//         for (int j = 0; j < 13; j++) {
//             // Add card to dealer hand
//             dealerHand.SetCards(Card(Ranks[j], Suits[0]));
//             // Set wager
//             userHand.SetWager(200);
//             // Test strategy
//             blackjack_strategy(userHand, dealerHand);
//             ASSERT_FALSE(userHand.GetShouldDoubleDown());
//             ASSERT_FALSE(userHand.GetShouldHit());
//             ASSERT_FALSE(userHand.GetShouldSplit());
//             ASSERT_TRUE(userHand.GetShouldStand());
//             dealerHand.GetCards().pop_back();
//         }
//         userHand.GetCards().pop_back();
//         userHand.AddHandTotal();
//     }
//     std::cout.rdbuf(oldCoutBuffer);
// }

// // Blackjack strategy test, duplicate ranks
// TEST_F(test_x, BlackjackStratDuplicates) {
//     // Suppress Cout's
//     std::streambuf* oldCoutBuffer = std::cout.rdbuf();
//     NullBuffer nullBuffer;
//     std::cout.rdbuf(&nullBuffer);
//     // Create hands
//     Hand userHand;
//     Hand dealerHand;
//     userHand.SetBankTotal(100);
//     // Add first card to dealer
//     dealerHand.SetCards(Card(Ranks[0], Suits[0]));
//     dealerHand.AddHandTotal();
//     // Player card total is 4 (two, two) or 6 (three, three)
//     for (int i = 1; i <= 2; i++) {
//         // Add cards to player hand
//         userHand.AddCardToHand(Card(Ranks[i], Suits[0]));
//         userHand.AddCardToHand(Card(Ranks[i], Suits[0]));
//         for (int j = 0; j < 13; j++) {
//             // Add card to dealer hand
//             dealerHand.SetCards(Card(Ranks[j], Suits[0]));
//             userHand.SetWager(10);
//             // Can split hand
//             {
//                 // Test strategy
//                 blackjack_strategy(userHand, dealerHand);
//                 if (j == 1 || j == 2) {
//                     ASSERT_FALSE(userHand.GetShouldDoubleDown());
//                     ASSERT_TRUE(userHand.GetShouldHit());
//                     ASSERT_TRUE(userHand.GetShouldSplit());
//                     ASSERT_FALSE(userHand.GetShouldStand());
//                 }
//                 else if (j >= 3 && j <= 6) {
//                     ASSERT_FALSE(userHand.GetShouldDoubleDown());
//                     ASSERT_FALSE(userHand.GetShouldHit());
//                     ASSERT_TRUE(userHand.GetShouldSplit());
//                     ASSERT_FALSE(userHand.GetShouldStand());      
//                 }
//                 else {
//                     ASSERT_FALSE(userHand.GetShouldDoubleDown());
//                     ASSERT_TRUE(userHand.GetShouldHit());
//                     ASSERT_FALSE(userHand.GetShouldSplit());
//                     ASSERT_FALSE(userHand.GetShouldStand());
//                 }                
//             }
//             // Can't split hand
//             {
//                 // Can't split
//                 userHand.SetSplitHandResponse(true);
//                 // Test strategy
//                 blackjack_strategy(userHand, dealerHand);
//                 ASSERT_FALSE(userHand.GetShouldDoubleDown());
//                 ASSERT_TRUE(userHand.GetShouldHit());
//                 ASSERT_FALSE(userHand.GetShouldSplit());
//                 ASSERT_FALSE(userHand.GetShouldStand());
//                 // Can split
//                 userHand.SetSplitHandResponse(false);
//             }
//             dealerHand.GetCards().pop_back();
//         }
//         userHand.GetCards().pop_back();
//         userHand.GetCards().pop_back();
//         userHand.AddHandTotal();
//     }
//     // Player card total is 8 (four, four)
//     {
//         // Add cards to player hand, set wager
//         userHand.AddCardToHand(Card(Ranks[3], Suits[0]));
//         userHand.AddCardToHand(Card(Ranks[3], Suits[0]));
//         userHand.SetWager(10);
//         for (int i = 0; i < 13; i++) {
//             // Add card to dealer hand
//             dealerHand.SetCards(Card(Ranks[i], Suits[0]));
//             // Can split hand
//             {
//                 // Test strategy
//                 blackjack_strategy(userHand, dealerHand);
//                 if (i == 4 || i == 5) {
//                     ASSERT_FALSE(userHand.GetShouldDoubleDown());
//                     ASSERT_TRUE(userHand.GetShouldHit());
//                     ASSERT_TRUE(userHand.GetShouldSplit());
//                     ASSERT_FALSE(userHand.GetShouldStand());
//                 }
//                 else {
//                     ASSERT_FALSE(userHand.GetShouldDoubleDown());
//                     ASSERT_TRUE(userHand.GetShouldHit());
//                     ASSERT_FALSE(userHand.GetShouldSplit());
//                     ASSERT_FALSE(userHand.GetShouldStand());
//                 }
//             }
//             // Can't split hand
//             {
//                 // Can't split
//                 userHand.SetSplitHandResponse(true);
//                 // Test strategy
//                 blackjack_strategy(userHand, dealerHand);
//                 ASSERT_FALSE(userHand.GetShouldDoubleDown());
//                 ASSERT_TRUE(userHand.GetShouldHit());
//                 ASSERT_FALSE(userHand.GetShouldSplit());
//                 ASSERT_FALSE(userHand.GetShouldStand());
//                 // Can split
//                 userHand.SetSplitHandResponse(false);
//             }
//             dealerHand.GetCards().pop_back();
//         }
//         userHand.GetCards().pop_back();
//         userHand.GetCards().pop_back();
//         userHand.AddHandTotal();        
//     }
//     // Player card total is 10 (five, five)
//     {
//         // Add cards to player hand, set wager
//         userHand.AddCardToHand(Card(Ranks[4], Suits[0]));
//         userHand.AddCardToHand(Card(Ranks[4], Suits[0]));
//         for (int i = 0; i < 13; i++) {
//             // Add card to dealer hand
//             dealerHand.SetCards(Card(Ranks[i], Suits[0]));
//             if (i == 0 || i >= 9) {
//                 // Set wager
//                 userHand.SetWager(10);
//                 // Test strategy
//                 blackjack_strategy(userHand, dealerHand);
//                 ASSERT_FALSE(userHand.GetShouldDoubleDown());
//                 ASSERT_TRUE(userHand.GetShouldHit());
//                 ASSERT_FALSE(userHand.GetShouldSplit());
//                 ASSERT_FALSE(userHand.GetShouldStand());
//             }
//             else {
//                 // Can double down
//                 {
//                     // Set wager
//                     userHand.SetWager(10);
//                     // Test strategy
//                     blackjack_strategy(userHand, dealerHand);
//                     ASSERT_TRUE(userHand.GetShouldDoubleDown());
//                     ASSERT_TRUE(userHand.GetShouldHit());
//                     ASSERT_FALSE(userHand.GetShouldSplit());
//                     ASSERT_FALSE(userHand.GetShouldStand());
//                 }
//                 // Cannot double down
//                 {
//                     // Set wager
//                     userHand.SetWager(101);
//                     // Test strategy
//                     blackjack_strategy(userHand, dealerHand);
//                     ASSERT_FALSE(userHand.GetShouldDoubleDown());
//                     ASSERT_TRUE(userHand.GetShouldHit());
//                     ASSERT_FALSE(userHand.GetShouldSplit());
//                     ASSERT_FALSE(userHand.GetShouldStand());
//                 }
//             }
//             dealerHand.GetCards().pop_back();
//         }
//         userHand.GetCards().pop_back();
//         userHand.GetCards().pop_back();
//         userHand.AddHandTotal();
//     }
//     // Player card total is 12 (six, six || Ace, Ace) 
//     {
//         // Player has two sixes
//         {
//             // Add cards to player hand, set wager
//             userHand.AddCardToHand(Card(Ranks[5], Suits[0]));
//             userHand.AddCardToHand(Card(Ranks[5], Suits[0]));
//             userHand.SetWager(10);
//             for (int i = 0; i < 13; i++) {
//                 // Add card to dealer hand
//                 dealerHand.SetCards(Card(Ranks[i], Suits[0]));
//                 // Can split
//                 {
//                     // Test strategy
//                     blackjack_strategy(userHand, dealerHand);
//                     if (i >= 1 && i <= 5) {
//                         ASSERT_FALSE(userHand.GetShouldDoubleDown());
//                         ASSERT_FALSE(userHand.GetShouldHit());
//                         ASSERT_TRUE(userHand.GetShouldSplit());
//                         ASSERT_FALSE(userHand.GetShouldStand());
//                     }
//                     else if (i == 6) {
//                         ASSERT_FALSE(userHand.GetShouldDoubleDown());
//                         ASSERT_TRUE(userHand.GetShouldHit());
//                         ASSERT_TRUE(userHand.GetShouldSplit());
//                         ASSERT_FALSE(userHand.GetShouldStand());
//                     }
//                     else {
//                         ASSERT_FALSE(userHand.GetShouldDoubleDown());
//                         ASSERT_TRUE(userHand.GetShouldHit());
//                         ASSERT_FALSE(userHand.GetShouldSplit());
//                         ASSERT_FALSE(userHand.GetShouldStand());
//                     }
//                 }
//                 // Can't split
//                 {
//                     userHand.SetSplitHandResponse(true);
//                     // Test strategy
//                     blackjack_strategy(userHand, dealerHand);
//                     if ((i >= 1 && i <= 2) || (i == 0 || i >= 6)) {
//                         ASSERT_FALSE(userHand.GetShouldDoubleDown());
//                         ASSERT_TRUE(userHand.GetShouldHit());
//                         ASSERT_FALSE(userHand.GetShouldSplit());
//                         ASSERT_FALSE(userHand.GetShouldStand());
//                     }
//                     else {
//                         ASSERT_FALSE(userHand.GetShouldDoubleDown());
//                         ASSERT_FALSE(userHand.GetShouldHit());
//                         ASSERT_FALSE(userHand.GetShouldSplit());
//                         ASSERT_TRUE(userHand.GetShouldStand());
//                     }
//                     userHand.SetSplitHandResponse(false);
//                 }
//                 dealerHand.GetCards().pop_back();
//             }
//             userHand.GetCards().pop_back();
//             userHand.GetCards().pop_back();
//             userHand.AddHandTotal();
//         }
//         // Player has two aces
//         {
//             // Add cards to player hand, set wager
//             userHand.AddCardToHand(Card(Ranks[0], Suits[0]));
//             userHand.AddCardToHand(Card(Ranks[0], Suits[0]));
//             userHand.SetWager(10);
//             for (int i = 0; i < 13; i++) {
//                 // Add card to dealer hand
//                 dealerHand.SetCards(Card(Ranks[i], Suits[0]));
//                 // Can split
//                 {
//                     // Test strategy
//                     blackjack_strategy(userHand, dealerHand);
//                     ASSERT_FALSE(userHand.GetShouldDoubleDown());
//                     ASSERT_FALSE(userHand.GetShouldHit());
//                     ASSERT_TRUE(userHand.GetShouldSplit());
//                     ASSERT_FALSE(userHand.GetShouldStand());
//                 }
//                 // Can't split
//                 {
//                     userHand.SetSplitAcesResponse(true);
//                     // Test strategy
//                     blackjack_strategy(userHand, dealerHand);
//                     if ((i >= 1 && i <= 2) || (i == 0 || i >= 6)) {
//                         ASSERT_FALSE(userHand.GetShouldDoubleDown());
//                         ASSERT_TRUE(userHand.GetShouldHit());
//                         ASSERT_FALSE(userHand.GetShouldSplit());
//                         ASSERT_FALSE(userHand.GetShouldStand());
//                     }
//                     else {
//                         ASSERT_FALSE(userHand.GetShouldDoubleDown());
//                         ASSERT_FALSE(userHand.GetShouldHit());
//                         ASSERT_FALSE(userHand.GetShouldSplit());
//                         ASSERT_TRUE(userHand.GetShouldStand());
//                     }
//                     userHand.SetSplitAcesResponse(false);
//                 }
//                 dealerHand.GetCards().pop_back();
//             }
//             userHand.GetCards().pop_back();
//             userHand.GetCards().pop_back();
//             userHand.AddHandTotal();
//         }
//     }
//     // Player card total is 14 (seven, seven) 
//     {
//         // Add cards to player hand, set wager
//         userHand.AddCardToHand(Card(Ranks[6], Suits[0]));
//         userHand.AddCardToHand(Card(Ranks[6], Suits[0]));
//         userHand.SetWager(10);
//         for (int i = 0; i < 13; i++) {
//             // Add card to dealer hand
//             dealerHand.SetCards(Card(Ranks[i], Suits[0]));
//             // Can split
//             {
//                 // Test strategy
//                 blackjack_strategy(userHand, dealerHand);
//                 if (i >= 1 && i <= 6) {
//                     ASSERT_FALSE(userHand.GetShouldDoubleDown());
//                     ASSERT_FALSE(userHand.GetShouldHit());
//                     ASSERT_TRUE(userHand.GetShouldSplit());
//                     ASSERT_FALSE(userHand.GetShouldStand());
//                 }
//                 else if (i == 7) {
//                     ASSERT_FALSE(userHand.GetShouldDoubleDown());
//                     ASSERT_TRUE(userHand.GetShouldHit());
//                     ASSERT_TRUE(userHand.GetShouldSplit());
//                     ASSERT_FALSE(userHand.GetShouldStand());
//                 }
//                 else {
//                     ASSERT_FALSE(userHand.GetShouldDoubleDown());
//                     ASSERT_TRUE(userHand.GetShouldHit());
//                     ASSERT_FALSE(userHand.GetShouldSplit());
//                     ASSERT_FALSE(userHand.GetShouldStand());
//                 }
//             }
//             // Can't split
//             {
//                 userHand.SetSplitHandResponse(true);
//                 // Test strategy
//                 blackjack_strategy(userHand, dealerHand);
//                 if (i >= 1 && i <= 5) {
//                     ASSERT_FALSE(userHand.GetShouldDoubleDown());
//                     ASSERT_FALSE(userHand.GetShouldHit());
//                     ASSERT_FALSE(userHand.GetShouldSplit());
//                     ASSERT_TRUE(userHand.GetShouldStand());
//                 }
//                 else {
//                     ASSERT_FALSE(userHand.GetShouldDoubleDown());
//                     ASSERT_TRUE(userHand.GetShouldHit());
//                     ASSERT_FALSE(userHand.GetShouldSplit());
//                     ASSERT_FALSE(userHand.GetShouldStand());
//                 }
//                 userHand.SetSplitHandResponse(false);
//             }
//             dealerHand.GetCards().pop_back();
//         }
//         userHand.GetCards().pop_back();
//         userHand.GetCards().pop_back();
//         userHand.AddHandTotal();
//     }
//     // Player card total is 16 (eight, eight)
//     {
//         // Add cards to player hand, set wager
//         userHand.AddCardToHand(Card(Ranks[7], Suits[0]));
//         userHand.AddCardToHand(Card(Ranks[7], Suits[0]));
//         userHand.SetWager(10);
//         for (int i = 0; i < 13; i++) {
//             // Add card to dealer hand
//             dealerHand.SetCards(Card(Ranks[i], Suits[0]));
//             // Can split
//             {
//                 // Test strategy
//                 blackjack_strategy(userHand, dealerHand);
//                 ASSERT_FALSE(userHand.GetShouldDoubleDown());
//                 ASSERT_FALSE(userHand.GetShouldHit());
//                 ASSERT_TRUE(userHand.GetShouldSplit());
//                 ASSERT_FALSE(userHand.GetShouldStand());                
//             }
//             // Can't split
//             {
//                 userHand.SetSplitHandResponse(true);
//                 // Test strategy
//                 blackjack_strategy(userHand, dealerHand);
//                 if (i >= 1 && i <= 5) {
//                     ASSERT_FALSE(userHand.GetShouldDoubleDown());
//                     ASSERT_FALSE(userHand.GetShouldHit());
//                     ASSERT_FALSE(userHand.GetShouldSplit());
//                     ASSERT_TRUE(userHand.GetShouldStand());
//                 }
//                 else {
//                     ASSERT_FALSE(userHand.GetShouldDoubleDown());
//                     ASSERT_TRUE(userHand.GetShouldHit());
//                     ASSERT_FALSE(userHand.GetShouldSplit());
//                     ASSERT_FALSE(userHand.GetShouldStand());
//                 }
//                 userHand.SetSplitHandResponse(false);
//             }
//             dealerHand.GetCards().pop_back();
//         }
//         userHand.GetCards().pop_back();
//         userHand.GetCards().pop_back();
//         userHand.AddHandTotal();
//     }
//     // Player card total is 18 (nine, nine)
//     {
//         // Add cards to player hand, set wager
//         userHand.AddCardToHand(Card(Ranks[8], Suits[0]));
//         userHand.AddCardToHand(Card(Ranks[8], Suits[0]));
//         userHand.SetWager(10);
//         for (int i = 0; i < 13; i++) {
//             // Add card to dealer hand
//             dealerHand.SetCards(Card(Ranks[i], Suits[0]));
//             // Can split
//             {
//                 // Test strategy
//                 blackjack_strategy(userHand, dealerHand); 
//                 if (i == 0 || i == 6 || i >= 9) {
//                     ASSERT_FALSE(userHand.GetShouldDoubleDown());
//                     ASSERT_FALSE(userHand.GetShouldHit());
//                     ASSERT_FALSE(userHand.GetShouldSplit());
//                     ASSERT_TRUE(userHand.GetShouldStand());
//                 }
//                 else {
//                     ASSERT_FALSE(userHand.GetShouldDoubleDown());
//                     ASSERT_FALSE(userHand.GetShouldHit());
//                     ASSERT_TRUE(userHand.GetShouldSplit());
//                     ASSERT_FALSE(userHand.GetShouldStand());
//                 }
//             }
//             // Can't split
//             {
//                 userHand.SetSplitHandResponse(true);
//                 // Test strategy
//                 blackjack_strategy(userHand, dealerHand);
//                 ASSERT_FALSE(userHand.GetShouldDoubleDown());
//                 ASSERT_FALSE(userHand.GetShouldHit());
//                 ASSERT_FALSE(userHand.GetShouldSplit());
//                 ASSERT_TRUE(userHand.GetShouldStand());                
//                 userHand.SetSplitHandResponse(false);
//             }
//             dealerHand.GetCards().pop_back();
//         }
//         userHand.GetCards().pop_back();
//         userHand.GetCards().pop_back();
//         userHand.AddHandTotal();
//     }
//     // Player card total is 20 (face, face)
//     {
//         // Add cards to player hand, set wager
//         for (int i = 9; i <= 12; i++) {
//             userHand.AddCardToHand(Card(Ranks[i], Suits[0]));
//             userHand.AddCardToHand(Card(Ranks[i], Suits[0]));
//             userHand.SetWager(10);
//             for (int j = 0; j < 13; j++) {
//                 // Add card to dealer hand
//                 dealerHand.SetCards(Card(Ranks[j], Suits[0]));
//                 // Can split
//                 {
//                     // Test strategy
//                     blackjack_strategy(userHand, dealerHand);
//                     ASSERT_FALSE(userHand.GetShouldDoubleDown());
//                     ASSERT_FALSE(userHand.GetShouldHit());
//                     ASSERT_FALSE(userHand.GetShouldSplit());
//                     ASSERT_TRUE(userHand.GetShouldStand()); 
//                 }
//                 // Can't split
//                 {
//                     userHand.SetSplitHandResponse(true);
//                     // Test strategy
//                     blackjack_strategy(userHand, dealerHand);
//                     ASSERT_FALSE(userHand.GetShouldDoubleDown());
//                     ASSERT_FALSE(userHand.GetShouldHit());
//                     ASSERT_FALSE(userHand.GetShouldSplit());
//                     ASSERT_TRUE(userHand.GetShouldStand()); 
//                     userHand.SetSplitHandResponse(false);                   
//                 }
//                 dealerHand.GetCards().pop_back(); 
//             }
//             userHand.GetCards().pop_back();
//             userHand.GetCards().pop_back();
//             userHand.AddHandTotal();
//         }
//     }
//     std::cout.rdbuf(oldCoutBuffer);
// }