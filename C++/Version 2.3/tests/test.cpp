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

// Linked list, retrieve test
TEST_F(test_x, LinkedListRetrieve) {
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
    // Test retrieving nodes
    EXPECT_EQ(testList->GetRoot(), testNode1);
    EXPECT_EQ(testList->GetTail(), testNode4);
    EXPECT_EQ(testList->RetrieveNode(0), testNode1);
    EXPECT_EQ(testList->RetrieveNode(1), testNode2);
    EXPECT_EQ(testList->RetrieveNode(2), testNode3);
    EXPECT_EQ(testList->RetrieveNode(3), testNode4);
    EXPECT_EQ(testList->RetrieveNode(-1), testNode4);
    EXPECT_EQ(testList->RetrieveNode(4), testNode4);
    EXPECT_EQ(testList->GetSize(), 4);
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
    testList->RemoveNode(-1);
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
    // Empty list, remove tail
    testList->RemoveNode(-1);
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
    // Empty list, remove root
    testList->RemoveNode(0);
    EXPECT_EQ(testList->GetSize(), 0);
    EXPECT_EQ(testList->GetRoot(), nullptr);
    EXPECT_EQ(testList->GetTail(), nullptr);
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
// Hand Class Test
/////////////////////////////////////////

// Hand class, constructor test
TEST_F(test_x, HandClassConst) {
    std::shared_ptr<Hand> testHand(new Hand);
    // Test initial boolean values
    EXPECT_FALSE(testHand->GetCanBuyInsurance());
    EXPECT_FALSE(testHand->GetCanDoubleDown());
    EXPECT_FALSE(testHand->GetCanSplitAces());
    EXPECT_FALSE(testHand->GetCanSplitHand());
    EXPECT_FALSE(testHand->GetChoseBuyInsurance());
    EXPECT_FALSE(testHand->GetChoseDoubleDown());
    EXPECT_FALSE(testHand->GetChoseSplitAces());
    EXPECT_FALSE(testHand->GetChoseSplitHand());
    EXPECT_FALSE(testHand->GetDoubleDownResponse());
    EXPECT_FALSE(testHand->GetHasBlackJack());
    EXPECT_FALSE(testHand->GetHasHit());
    EXPECT_FALSE(testHand->GetParamInHand());
    EXPECT_FALSE(testHand->GetSameParamInHand());
    EXPECT_FALSE(testHand->GetShouldDoubleDown());
    EXPECT_FALSE(testHand->GetShouldHit());
    EXPECT_FALSE(testHand->GetShouldSplit());
    EXPECT_FALSE(testHand->GetShouldStand());
    EXPECT_FALSE(testHand->GetSoftSeventeen());
    EXPECT_FALSE(testHand->GetSplitAcesResponse());
    EXPECT_FALSE(testHand->GetSplitHandResponse());
    // Test initial float values
    EXPECT_EQ(testHand->GetBankTotal(), 0);
    EXPECT_EQ(testHand->GetInsuranceWager(), 0);
    EXPECT_EQ(testHand->GetNet(), 0);
    EXPECT_EQ(testHand->GetWager(), 0);
    // Test initial integer values
    EXPECT_EQ(testHand->GetCardsTotal(), 0);
    EXPECT_EQ(testHand->GetHandsBlackjack(), 0);
    EXPECT_EQ(testHand->GetHandsLost(), 0);
    EXPECT_EQ(testHand->GetHandsPlayed(), 0);
    EXPECT_EQ(testHand->GetHandsPushed(), 0);
    EXPECT_EQ(testHand->GetHandsWon(), 0);
    // Test initial string values
    EXPECT_EQ(testHand->GetDisplayBankTotal(), "");
    EXPECT_EQ(testHand->GetDisplayCardsTotal(), "");
    EXPECT_EQ(testHand->GetDisplayInsuranceWager(), "");
    EXPECT_EQ(testHand->GetDisplayName(), "");
    EXPECT_EQ(testHand->GetDisplayNet(), "");
    EXPECT_EQ(testHand->GetDisplayWager(), "");
    EXPECT_EQ(testHand->GetName(), "");
    // Test linked list sizes
    EXPECT_EQ(testHand->GetHandBankTotals()->GetSize(), 0);
    EXPECT_EQ(testHand->GetHandCardTotals()->GetSize(), 0);
    EXPECT_EQ(testHand->GetHandNets()->GetSize(), 0);
    EXPECT_EQ(testHand->GetHandPlayed()->GetSize(), 0);
    EXPECT_EQ(testHand->GetHandWagers()->GetSize(), 0);
    EXPECT_EQ(testHand->GetPlayerCards()->GetSize(), 0);
}

// Hand class, add card to hand test
TEST_F(test_x, HandClassAdd) {
    // Create test hand, shoe, and card
    std::shared_ptr<Hand> testHand(new Hand);
    std::shared_ptr<Shoe> testShoe(new Shoe);
    std::shared_ptr<Card> testCard(new Card);
    std::shared_ptr<node<Card>> testNode;
    // Add Ace to hand
    testCard = std::make_shared<Card>(Ranks[0], Suits[0]);
    testNode = testShoe->GetCardsInShoe()->InitNode(testCard);
    testHand->AddCardToHand(testNode);
    EXPECT_EQ(testHand->GetPlayerCards()->GetSize(), 1);
    EXPECT_EQ(testHand->GetCardsTotal(), 11);
    // Add King to hand
    testCard = std::make_shared<Card>(Ranks[12], Suits[0]);
    testNode = testShoe->GetCardsInShoe()->InitNode(testCard);
    testHand->AddCardToHand(testNode);
    EXPECT_EQ(testHand->GetPlayerCards()->GetSize(), 2);
    EXPECT_EQ(testHand->GetCardsTotal(), 21);
    // Add another Ace to hand
    testCard = std::make_shared<Card>(Ranks[0], Suits[0]);
    testNode = testShoe->GetCardsInShoe()->InitNode(testCard);
    testHand->AddCardToHand(testNode);
    EXPECT_EQ(testHand->GetPlayerCards()->GetSize(), 3);
    EXPECT_EQ(testHand->GetCardsTotal(), 12);
    // Add a Nine to hand
    testCard = std::make_shared<Card>(Ranks[8], Suits[0]);
    testNode = testShoe->GetCardsInShoe()->InitNode(testCard);
    testHand->AddCardToHand(testNode);
    EXPECT_EQ(testHand->GetPlayerCards()->GetSize(), 4);
    EXPECT_EQ(testHand->GetCardsTotal(), 21);
    // Add a Nine to hand
    testCard = std::make_shared<Card>(Ranks[8], Suits[0]);
    testNode = testShoe->GetCardsInShoe()->InitNode(testCard);
    testHand->AddCardToHand(testNode);
    EXPECT_EQ(testHand->GetPlayerCards()->GetSize(), 5);
    EXPECT_EQ(testHand->GetCardsTotal(), 30);
}

// Hand class, check parameter test
TEST_F(test_x, HandClassCheckParam) {
    // Create test hand, shoe, and card
    std::shared_ptr<Hand> testHand(new Hand);
    std::shared_ptr<Shoe> testShoe(new Shoe);
    std::shared_ptr<Card> testCard(new Card);
    std::shared_ptr<node<Card>> testNode;
    // Iterate over all possibilities
    for (int i = 0; i < 13; i++) {
        for (int j = 0; j < 4; j++) {
            testCard = std::make_shared<Card>(Ranks[i], Suits[j]);
            testNode = testShoe->GetCardsInShoe()->InitNode(testCard);
            testHand->AddCardToHand(testNode);
            testHand->CheckParamInHand("R", Ranks[i]);
            EXPECT_TRUE(testHand->GetParamInHand());
            testHand->CheckParamInHand("S", Suits[j]);
            EXPECT_TRUE(testHand->GetParamInHand());
            testHand->GetPlayerCards()->RemoveNode(-1);
        }
    }
}

// Hand class, check same parameter test
TEST_F(test_x, HandClassCheckSameParam) {
    // Create test hand, shoe, and card
    std::shared_ptr<Hand> testHand(new Hand);
    std::shared_ptr<Shoe> testShoe(new Shoe);
    std::shared_ptr<Card> testCard1(new Card);
    std::shared_ptr<Card> testCard2(new Card);
    std::shared_ptr<node<Card>> testNode1;
    std::shared_ptr<node<Card>> testNode2;
    // Iterate over all possibilities, checking random ranks
    for (int i = 0; i < 13; i++) {
        testCard1 = std::make_shared<Card>(Ranks[i], Suits[0]);
        testNode1 = testShoe->GetCardsInShoe()->InitNode(testCard1);
        testHand->AddCardToHand(testNode1);
        for (int j = 0; j < 13; j++) {
            testCard2 = std::make_shared<Card>(Ranks[j], Suits[3]);
            testNode2 = testShoe->GetCardsInShoe()->InitNode(testCard2);
            testHand->AddCardToHand(testNode2);
            testHand->CheckSameParamInHand("R");
            if (i == j) {
                ASSERT_TRUE(testHand->GetSameParamInHand());
            }
            else {
                ASSERT_FALSE(testHand->GetSameParamInHand());
            }
            testHand->CheckSameParamInHand("S");
            ASSERT_FALSE(testHand->GetSameParamInHand());
            testHand->GetPlayerCards()->RemoveNode(-1);
        }
        testHand->GetPlayerCards()->RemoveNode(0);
    }
    // Iterate over all possibilities, checking random suits
    for (int i = 0; i < 4; i++) {
        testCard1 = std::make_shared<Card>(Ranks[0], Suits[i]);
        testNode1 = testShoe->GetCardsInShoe()->InitNode(testCard1);
        testHand->AddCardToHand(testNode1);
        for (int j = 0; j < 4; j++) {
            testCard2 = std::make_shared<Card>(Ranks[12], Suits[j]);
            testNode2 = testShoe->GetCardsInShoe()->InitNode(testCard2);
            testHand->AddCardToHand(testNode2);
            testHand->CheckSameParamInHand("S");
            if (i == j) {
                ASSERT_TRUE(testHand->GetSameParamInHand());
            }
            else {
                ASSERT_FALSE(testHand->GetSameParamInHand());
            }
            testHand->CheckSameParamInHand("R");
            ASSERT_FALSE(testHand->GetSameParamInHand());
            testHand->GetPlayerCards()->RemoveNode(-1);
        }
        testHand->GetPlayerCards()->RemoveNode(0);
    }
}

// Hand class, check for blackjack
TEST_F(test_x, HandClassCheckBlackjack) {
    // Create test hand, shoe, and card
    std::shared_ptr<Hand> testHand(new Hand);
    std::shared_ptr<Shoe> testShoe(new Shoe);
    std::shared_ptr<Card> testCard1(new Card);
    std::shared_ptr<Card> testCard2(new Card);
    std::shared_ptr<Card> testCard3(new Card);
    std::shared_ptr<node<Card>> testNode1;
    std::shared_ptr<node<Card>> testNode2;
    std::shared_ptr<node<Card>> testNode3;
    // First card is an Ace
    testCard1 = std::make_shared<Card>(Card(Ranks[0], Suits[0]));
    testNode1 = testShoe->GetCardsInShoe()->InitNode(testCard1);
    testHand->AddCardToHand(testNode1);
    // Test for false cases
    for (int i = 0; i < 9; i++) {
        testCard2 = std::make_shared<Card>(Card(Ranks[i], Suits[0]));
        testNode2 = testShoe->GetCardsInShoe()->InitNode(testCard2);
        testHand->AddCardToHand(testNode2);
        testHand->CheckBlackJack();
        ASSERT_FALSE(testHand->GetHasBlackJack());
        ASSERT_EQ(testHand->GetPlayerCards()->GetSize(), 2);
        testHand->GetPlayerCards()->RemoveNode(-1);
    }
    // Test for true cases
    for (int i = 9; i < 13; i++) {
        testCard2 = std::make_shared<Card>(Card(Ranks[i], Suits[0]));
        testNode2 = testShoe->GetCardsInShoe()->InitNode(testCard2);
        testHand->AddCardToHand(testNode2);
        testHand->CheckBlackJack();
        ASSERT_TRUE(testHand->GetHasBlackJack());
        ASSERT_EQ(testHand->GetPlayerCards()->GetSize(), 2);
        testHand->GetPlayerCards()->RemoveNode(-1);
    }
    // Add second card to player hand
    testCard3 = std::make_shared<Card>(Card(Ranks[1], Suits[0]));
    testNode3 = testShoe->GetCardsInShoe()->InitNode(testCard3);
    testHand->AddCardToHand(testNode3);
    // Test for false case
    for (int i = 0; i < 13; i++) {
        testCard2 = std::make_shared<Card>(Card(Ranks[i], Suits[0]));
        testNode2 = testShoe->GetCardsInShoe()->InitNode(testCard2);
        testHand->AddCardToHand(testNode2);
        testHand->CheckBlackJack();
        ASSERT_FALSE(testHand->GetHasBlackJack());
        ASSERT_EQ(testHand->GetPlayerCards()->GetSize(), 3);
        testHand->GetPlayerCards()->RemoveNode(-1);
    }
}

// Hand class, hit hand test
TEST_F(test_x, HandClassHitHand) {
    // Create test hand, shoe, and card
    std::shared_ptr<Hand> testHand(new Hand);
    std::shared_ptr<Shoe> testShoe(new Shoe);
    testShoe->SetNumOfDecks(1);
    testShoe->CreateShoe();
    int handCardCounter = 0;
    for (int i = 52; i > 0; i--) {
        handCardCounter++;
        EXPECT_EQ(testShoe->GetCardsInShoe()->GetSize(), i);
        testHand->HitHand(testShoe);
        EXPECT_EQ(testHand->GetPlayerCards()->GetSize(), handCardCounter);
    }
}

// Hand class, update hand test
TEST_F(test_x, HandClassUpdate) {
    std::shared_ptr<Hand> testHand(new Hand);
    int bankValue = 100;
    int loopValue = 1;
    int wagerValue = loopValue;
    testHand->SetBankTotal(bankValue);
    // Test deposit
    while (testHand->GetBankTotal() > 0) {
        testHand->SetWager(wagerValue);
        testHand->UpdateBank(0, testHand->GetWager());
        EXPECT_EQ(testHand->GetBankTotal(), bankValue - loopValue);
        loopValue++;
    }
    testHand->SetBankTotal(bankValue);
    loopValue = 1;
    wagerValue = loopValue;
    // Test win
    while (testHand->GetBankTotal() < 200) {
        testHand->SetWager(wagerValue);
        testHand->UpdateBank(0, testHand->GetWager());
        testHand->UpdateBank(1, testHand->GetWager());
        EXPECT_EQ(testHand->GetBankTotal(), bankValue + loopValue);
        loopValue++;
    }
    testHand->SetBankTotal(bankValue);
    loopValue = 1;
    wagerValue = loopValue;
    // Test loss
    while(testHand->GetBankTotal() > 0) {
        testHand->SetWager(wagerValue);
        testHand->UpdateBank(0, testHand->GetWager());
        testHand->UpdateBank(2, testHand->GetWager());
        EXPECT_EQ(testHand->GetBankTotal(), bankValue - loopValue);
        loopValue++;
    }
    testHand->SetBankTotal(bankValue);
    loopValue = 1;
    wagerValue = loopValue;
    // Test push
    while (loopValue < 100) {
        testHand->SetWager(wagerValue);
        testHand->UpdateBank(0, testHand->GetWager());
        testHand->UpdateBank(3, testHand->GetWager());
        EXPECT_EQ(testHand->GetBankTotal(), bankValue);
        loopValue++;
    }
    testHand->SetBankTotal(bankValue);
    loopValue = 1;
    wagerValue = loopValue;
    // Test blackjack
    while (testHand->GetBankTotal() < 250) {
        testHand->SetWager(wagerValue);
        testHand->UpdateBank(0, testHand->GetWager());
        testHand->UpdateBank(4, testHand->GetWager());
        EXPECT_EQ(testHand->GetBankTotal(), bankValue + 1.5*loopValue);
        loopValue++;
    }
    testHand->SetBankTotal(bankValue);
    loopValue = 1;
    wagerValue = loopValue;
    // Test insurance
    while (testHand->GetBankTotal() < 200) {
        testHand->SetWager(wagerValue);
        testHand->SetInsuranceWager(testHand->GetWager());
        testHand->UpdateBank(0, testHand->GetWager());
        testHand->UpdateBank(5, testHand->GetInsuranceWager());
        EXPECT_EQ(testHand->GetBankTotal(), bankValue + 2.0*loopValue);
        loopValue++;
    }  
}

// Hand class, parameters check test
TEST_F(test_x, HandClassParameterCheck) {
    // Create objects
    std::shared_ptr<Hand> testHand(new Hand);
    std::shared_ptr<Hand> dealerHand(new Hand);
    std::shared_ptr<Shoe> testShoe(new Shoe);
    std::shared_ptr<Card> testCard(new Card);
    std::shared_ptr<node<Card>> testNode;
    testCard = std::make_shared<Card>(Ranks[0], Suits[0]);
    testNode = testShoe->GetCardsInShoe()->InitNode(testCard);
    dealerHand->AddCardToHand(testNode);
    dealerHand->AddCardToHand(testNode);
    testHand->AddCardToHand(testNode);
    testHand->AddCardToHand(testNode);
    testHand->SetBankTotal(100);
    testHand->SetName("Borby");
    // Test can double down
    for (int i = 1; i <= 200; i++) {
        testHand->SetWager(i);
        testHand->SetHasHit(false);
        {
            testHand->SetChoseDoubleDown(false);
            {
                testHand->ParametersCheck(dealerHand);
                if (testHand->GetWager() <= testHand->GetBankTotal()) {
                    EXPECT_TRUE(testHand->GetCanDoubleDown());
                }
                else {
                    EXPECT_FALSE(testHand->GetCanDoubleDown());
                }
            }
            testHand->SetChoseDoubleDown(true);
            {
                testHand->ParametersCheck(dealerHand);
                EXPECT_FALSE(testHand->GetCanDoubleDown());
            }
        }
        testHand->SetHasHit(true);
        testHand->ParametersCheck(dealerHand);
        EXPECT_FALSE(testHand->GetCanDoubleDown());
    }
    testHand->GetPlayerCards()->ClearList();
    // Soft seventeen check
    // (Ace, Ace, Ace, Ace, Ace, Ace, Ace)
    for (int i = 1; i <= 7; i++) {
        testCard = std::make_shared<Card>(Ranks[0], Suits[0]);
        testNode = testShoe->GetCardsInShoe()->InitNode(testCard);
        testHand->AddCardToHand(testNode);  
    }
    testHand->ParametersCheck(dealerHand);
    EXPECT_TRUE(testHand->GetSoftSeventeen());
    testHand->GetPlayerCards()->ClearList();
    // (King, 7)
    testCard = std::make_shared<Card>(Ranks[12], Suits[0]);
    testNode = testShoe->GetCardsInShoe()->InitNode(testCard);
    testHand->AddCardToHand(testNode);
    testCard = std::make_shared<Card>(Ranks[6], Suits[0]);
    testNode = testShoe->GetCardsInShoe()->InitNode(testCard);
    testHand->AddCardToHand(testNode);
    testHand->ParametersCheck(dealerHand);
    EXPECT_FALSE(testHand->GetSoftSeventeen());
    testHand->GetPlayerCards()->ClearList();
    // (Queen, Ace, Ace, Ace, Ace, Ace, Ace, Ace, Ace)
    testCard = std::make_shared<Card>(Ranks[11], Suits[0]);
    testNode = testShoe->GetCardsInShoe()->InitNode(testCard);
    testHand->AddCardToHand(testNode);
    for (int i = 1; i <= 7; i++) {
        testCard = std::make_shared<Card>(Ranks[0], Suits[0]);
        testNode = testShoe->GetCardsInShoe()->InitNode(testCard);
        testHand->AddCardToHand(testNode);  
    }
    testHand->ParametersCheck(dealerHand);
    EXPECT_FALSE(testHand->GetSoftSeventeen());
    testHand->GetPlayerCards()->ClearList();
    testHand->AddCardToHand(testNode);
    testHand->AddCardToHand(testNode);
    dealerHand->GetPlayerCards()->ClearList();
    // Insurance check
    for (int i = 0; i < 13; i++) {
        testCard = std::make_shared<Card>(Ranks[i], Suits[0]);
        testNode = testShoe->GetCardsInShoe()->InitNode(testCard);
        dealerHand->AddCardToHand(testNode);
        for (int j = 0; j < 13; j++) {
            testCard = std::make_shared<Card>(Ranks[j], Suits[0]);
            testNode = testShoe->GetCardsInShoe()->InitNode(testCard);
            dealerHand->AddCardToHand(testNode);
            dealerHand->CheckBlackJack();
            if (dealerHand->GetPlayerCards()->RetrieveNode(-1)->data.GetRank() == Ranks[0] && !dealerHand->GetHasBlackJack()) {
                for (int k = 1; k <= 400; k++) {
                    testHand->SetWager(k);
                    testHand->ParametersCheck(dealerHand);
                    if (k <= 200) {
                        EXPECT_TRUE(testHand->GetCanBuyInsurance());
                    }
                    else {
                        EXPECT_FALSE(testHand->GetCanBuyInsurance());
                    }
                }
            }
            else {
                testHand->ParametersCheck(dealerHand);
                EXPECT_FALSE(testHand->GetCanBuyInsurance());
            }
            dealerHand->GetPlayerCards()->RemoveNode(-1);
        }
        dealerHand->GetPlayerCards()->RemoveNode(0);
    }
    testHand->GetPlayerCards()->ClearList();
    dealerHand->AddCardToHand(testNode);
    dealerHand->AddCardToHand(testNode);
    // Can split hand check
    for (int i = 0; i < 13; i++) {
        testCard = std::make_shared<Card>(Ranks[i], Suits[0]);
        testNode = testShoe->GetCardsInShoe()->InitNode(testCard);
        testHand->AddCardToHand(testNode);
        for (int j = 0; j < 13; j++) {
            testCard = std::make_shared<Card>(Ranks[j], Suits[0]);
            testNode = testShoe->GetCardsInShoe()->InitNode(testCard);
            testHand->AddCardToHand(testNode);
            testHand->CheckSameParamInHand("R");
            if (testHand->GetSameParamInHand()) {
                for (int k = 1; k <= 200; k++) {
                    testHand->SetWager(k);
                    testHand->ParametersCheck(dealerHand);
                    testHand->CheckParamInHand("R", Ranks[0]);
                    if (k <= 100) {
                        if (testHand->GetParamInHand()) {
                            EXPECT_TRUE(testHand->GetCanSplitAces());
                            EXPECT_FALSE(testHand->GetCanSplitHand());
                        }
                        else {
                            EXPECT_FALSE(testHand->GetCanSplitAces());
                            EXPECT_TRUE(testHand->GetCanSplitHand());
                        }
                    }
                    else {
                        EXPECT_FALSE(testHand->GetCanSplitAces());
                        EXPECT_FALSE(testHand->GetCanSplitHand());
                    }
                }
            }
            else {
                testHand->ParametersCheck(dealerHand);
                EXPECT_FALSE(testHand->GetCanSplitAces());
                EXPECT_FALSE(testHand->GetCanSplitHand());
            }
            testHand->GetPlayerCards()->RemoveNode(-1);
        }
        testHand->GetPlayerCards()->RemoveNode(0);
    }
}

// Hand class, reset test
TEST_F(test_x, HandClassReset) {
    std::shared_ptr<Hand> testHand(new Hand);
    std::shared_ptr<Shoe> testShoe(new Shoe);
    testShoe->SetNumOfDecks(1);
    testShoe->CreateShoe();
    // Set dummy values
    testHand->SetName("Borby");
    testHand->SetBankTotal(100);
    testHand->SetWager(10);
    testHand->SetInsuranceWager(5);
    testHand->SetNet(5);
    testHand->HitHand(testShoe);
    testHand->HitHand(testShoe);
    EXPECT_EQ(testHand->GetName(), "Borby");
    EXPECT_EQ(testHand->GetPlayerCards()->GetSize(), 2);
    EXPECT_EQ(testHand->GetBankTotal(), 100);
    EXPECT_EQ(testHand->GetInsuranceWager(), 5);
    EXPECT_EQ(testHand->GetNet(), 5);
    EXPECT_EQ(testHand->GetWager(), 10);
    EXPECT_FALSE(testHand->GetCanBuyInsurance());
    EXPECT_FALSE(testHand->GetCanDoubleDown());
    EXPECT_FALSE(testHand->GetCanSplitAces());
    EXPECT_FALSE(testHand->GetCanSplitHand());
    EXPECT_FALSE(testHand->GetChoseBuyInsurance());
    EXPECT_FALSE(testHand->GetChoseDoubleDown());
    EXPECT_FALSE(testHand->GetChoseSplitAces());
    EXPECT_FALSE(testHand->GetChoseSplitHand());
    EXPECT_FALSE(testHand->GetDoubleDownResponse());
    EXPECT_FALSE(testHand->GetHasBlackJack());
    EXPECT_FALSE(testHand->GetHasHit());
    EXPECT_FALSE(testHand->GetParamInHand());
    EXPECT_FALSE(testHand->GetSameParamInHand());
    EXPECT_FALSE(testHand->GetShouldDoubleDown());
    EXPECT_FALSE(testHand->GetShouldHit());
    EXPECT_FALSE(testHand->GetShouldSplit());
    EXPECT_FALSE(testHand->GetShouldStand());
    EXPECT_FALSE(testHand->GetSoftSeventeen());
    EXPECT_FALSE(testHand->GetSplitAcesResponse());
    EXPECT_FALSE(testHand->GetSplitHandResponse());
    // Reset Hand
    testHand->ResetHand();
    EXPECT_EQ(testHand->GetPlayerCards()->GetSize(), 0);
    EXPECT_EQ(testHand->GetBankTotal(), 100);
    EXPECT_EQ(testHand->GetInsuranceWager(), 0);
    EXPECT_EQ(testHand->GetNet(), 0);
    EXPECT_EQ(testHand->GetWager(), 0);
    EXPECT_FALSE(testHand->GetCanBuyInsurance());
    EXPECT_FALSE(testHand->GetCanDoubleDown());
    EXPECT_FALSE(testHand->GetCanSplitAces());
    EXPECT_FALSE(testHand->GetCanSplitHand());
    EXPECT_FALSE(testHand->GetChoseBuyInsurance());
    EXPECT_FALSE(testHand->GetChoseDoubleDown());
    EXPECT_FALSE(testHand->GetChoseSplitAces());
    EXPECT_FALSE(testHand->GetChoseSplitHand());
    EXPECT_FALSE(testHand->GetDoubleDownResponse());
    EXPECT_FALSE(testHand->GetHasBlackJack());
    EXPECT_FALSE(testHand->GetHasHit());
    EXPECT_FALSE(testHand->GetParamInHand());
    EXPECT_FALSE(testHand->GetSameParamInHand());
    EXPECT_FALSE(testHand->GetShouldDoubleDown());
    EXPECT_FALSE(testHand->GetShouldHit());
    EXPECT_FALSE(testHand->GetShouldSplit());
    EXPECT_FALSE(testHand->GetShouldStand());
    EXPECT_FALSE(testHand->GetSoftSeventeen());
    EXPECT_FALSE(testHand->GetSplitAcesResponse());
    EXPECT_FALSE(testHand->GetSplitHandResponse());
}

// Hand class, copy variables test
TEST_F(test_x, HandClassCopy) {
    std::shared_ptr<Hand> hand1(new Hand);
    std::shared_ptr<Hand> hand1Copy(new Hand);
    hand1->SetName("Borby");
    hand1->SetBankTotal(100);
    hand1->SetWager(10);
    hand1Copy->CopyVariables(hand1);
    ASSERT_EQ(hand1->GetName(), "Borby");
    ASSERT_EQ(hand1->GetBankTotal(), 100);
    ASSERT_EQ(hand1->GetWager(), 10);
    ASSERT_EQ(hand1Copy->GetName(), "Borby");
    ASSERT_EQ(hand1Copy->GetBankTotal(), 100);
    ASSERT_EQ(hand1Copy->GetWager(), 10);
}

/////////////////////////////////////////
// Core Functions Tests
/////////////////////////////////////////

// Blackjack strategy test, no duplicate ranks, no ace in hand off deal
TEST_F(test_x, BlackjackStrat){
    // Suppress Cout's
    std::streambuf* oldCoutBuffer = std::cout.rdbuf();
    NullBuffer nullBuffer;
    std::cout.rdbuf(&nullBuffer);
    // Create hands and card objects
    std::shared_ptr<Hand> userHand(new Hand);
    std::shared_ptr<Hand> dealerHand(new Hand);
    std::shared_ptr<Card> testCard(new Card);
    std::shared_ptr<node<Card>> testNode;
    userHand->SetBankTotal(100);
    // Add first card to dealer
    testCard = std::make_shared<Card>(Ranks[0], Suits[0]);
    testNode = dealerHand->GetPlayerCards()->InitNode(testCard);
    dealerHand->SetPlayerCards(testNode);
    // Add dummy cards to user hand
    testCard = std::make_shared<Card>(Ranks[1], Suits[0]);
    testNode = userHand->GetPlayerCards()->InitNode(testCard);
    userHand->SetPlayerCards(testNode);
    testCard = std::make_shared<Card>(Ranks[12], Suits[0]);
    testNode = userHand->GetPlayerCards()->InitNode(testCard);
    userHand->SetPlayerCards(testNode);
    // Player has a card total of 4 through 8
    for (int i = 4; i <= 8; i++) {
        userHand->SetCardsTotal(i);
        userHand->SetWager(10);
        for (int j = 0; j < 13; j++) {
            // Add card to dealer hand
            testCard = std::make_shared<Card>(Ranks[j], Suits[0]);
            testNode = dealerHand->GetPlayerCards()->InitNode(testCard);
            dealerHand->SetPlayerCards(testNode);
            blackjack_strategy(userHand, dealerHand);
            ASSERT_FALSE(userHand->GetShouldDoubleDown());
            ASSERT_TRUE(userHand->GetShouldHit());
            ASSERT_FALSE(userHand->GetShouldSplit());
            ASSERT_FALSE(userHand->GetShouldStand());
            dealerHand->GetPlayerCards()->RemoveNode(-1);
        }
    }
    // Player has a card total of 9
    userHand->SetCardsTotal(9);
    for (int i = 0; i < 13; i++) {
        // Add card to dealer hand
        testCard = std::make_shared<Card>(Ranks[i], Suits[0]);
        testNode = dealerHand->GetPlayerCards()->InitNode(testCard);
        dealerHand->SetPlayerCards(testNode);
        // Dealer has a 2 - 6
        if (i != 0 && i < 6) {
            // Test strategy for if a player can double down
            {   
                // Set wager
                userHand->SetWager(10);
                // Test strategy
                blackjack_strategy(userHand, dealerHand);
                ASSERT_TRUE(userHand->GetShouldDoubleDown());
                ASSERT_TRUE(userHand->GetShouldHit());
                ASSERT_FALSE(userHand->GetShouldSplit());
                ASSERT_FALSE(userHand->GetShouldStand());
            }
            // Test strategy for if a player cannot double down
            {
                // Set wager
                userHand->SetWager(200);
                // Test strategy
                blackjack_strategy(userHand, dealerHand);
                ASSERT_FALSE(userHand->GetShouldDoubleDown());
                ASSERT_TRUE(userHand->GetShouldHit());
                ASSERT_FALSE(userHand->GetShouldSplit());
                ASSERT_FALSE(userHand->GetShouldStand());
            }
        }
        // Otherwise
        else {
            // Set wager
            userHand->SetWager(10);
            // Test strategy
            blackjack_strategy(userHand, dealerHand);
            ASSERT_FALSE(userHand->GetShouldDoubleDown());
            ASSERT_TRUE(userHand->GetShouldHit());
            ASSERT_FALSE(userHand->GetShouldSplit());
            ASSERT_FALSE(userHand->GetShouldStand());
        }    
        dealerHand->GetPlayerCards()->RemoveNode(-1);
    }
    // Player has a card total of 10
    userHand->SetCardsTotal(10);
    for (int i = 0; i < 13; i++) {
        // Add card to dealer hand
        testCard = std::make_shared<Card>(Ranks[i], Suits[0]);
        testNode = dealerHand->GetPlayerCards()->InitNode(testCard);
        dealerHand->SetPlayerCards(testNode);
        // Dealer has a 2 - 9
        if (i != 0 && i < 9) {
            // Test strategy for if a player can double down
            {
                // Set wager
                userHand->SetWager(10);
                // Test strategy
                blackjack_strategy(userHand, dealerHand);
                ASSERT_TRUE(userHand->GetShouldDoubleDown());
                ASSERT_TRUE(userHand->GetShouldHit());
                ASSERT_FALSE(userHand->GetShouldSplit());
                ASSERT_FALSE(userHand->GetShouldStand());
            }
            // Test strategy for if a player cannot double down
            {
                // Set wager
                userHand->SetWager(200);
                // Test strategy
                blackjack_strategy(userHand, dealerHand);
                ASSERT_FALSE(userHand->GetShouldDoubleDown());
                ASSERT_TRUE(userHand->GetShouldHit());
                ASSERT_FALSE(userHand->GetShouldSplit());
                ASSERT_FALSE(userHand->GetShouldStand());
            }
        }
        // Otherwise
        else {
            // Set wager
            userHand->SetWager(10);
            // Test strategy
            blackjack_strategy(userHand, dealerHand);
            ASSERT_FALSE(userHand->GetShouldDoubleDown());
            ASSERT_TRUE(userHand->GetShouldHit());
            ASSERT_FALSE(userHand->GetShouldSplit());
            ASSERT_FALSE(userHand->GetShouldStand());
        }
        dealerHand->GetPlayerCards()->RemoveNode(-1);
    }
    // Player has a hand card value of 11
    userHand->SetCardsTotal(11);
    for (int i = 0; i < 13; i++) {
        // Player can double down
        {
            userHand->SetWager(10);
            // Add card to dealer hand
            testCard = std::make_shared<Card>(Ranks[i], Suits[0]);
            testNode = dealerHand->GetPlayerCards()->InitNode(testCard);
            dealerHand->SetPlayerCards(testNode);
            // Test strategy - Can double down
            blackjack_strategy(userHand, dealerHand);
            ASSERT_TRUE(userHand->GetShouldDoubleDown());
            ASSERT_TRUE(userHand->GetShouldHit());
            ASSERT_FALSE(userHand->GetShouldSplit());
            ASSERT_FALSE(userHand->GetShouldStand());
            // Remove last card from dealer hand
            dealerHand->GetPlayerCards()->RemoveNode(-1);           
        }
        // Player cannot double down
        {
            userHand->SetWager(200);
            // Add card to dealer hand
            testCard = std::make_shared<Card>(Ranks[i], Suits[0]);
            testNode = dealerHand->GetPlayerCards()->InitNode(testCard);
            dealerHand->SetPlayerCards(testNode);
            // Test strategy - Can double down
            blackjack_strategy(userHand, dealerHand);
            ASSERT_FALSE(userHand->GetShouldDoubleDown());
            ASSERT_TRUE(userHand->GetShouldHit());
            ASSERT_FALSE(userHand->GetShouldSplit());
            ASSERT_FALSE(userHand->GetShouldStand());
            // Remove last card from dealer hand
            dealerHand->GetPlayerCards()->RemoveNode(-1);     
        }
    }
    // Player has a hand card value of 12
    userHand->SetCardsTotal(12);
    for (int i = 0; i < 13; i++) {
        userHand->SetWager(10);
        // Add card to dealer hand
        testCard = std::make_shared<Card>(Ranks[i], Suits[0]);
        testNode = dealerHand->GetPlayerCards()->InitNode(testCard);
        dealerHand->SetPlayerCards(testNode);
        blackjack_strategy(userHand, dealerHand);
        // Test strategy for 4, 5, and 6 cards
        if (i == 3 || i == 4 || i == 5) {
            ASSERT_FALSE(userHand->GetShouldDoubleDown());
            ASSERT_FALSE(userHand->GetShouldHit());
            ASSERT_FALSE(userHand->GetShouldSplit());
            ASSERT_TRUE(userHand->GetShouldStand());
        }
        // Test strategy for other cards
        else {
            ASSERT_FALSE(userHand->GetShouldDoubleDown());
            ASSERT_TRUE(userHand->GetShouldHit());
            ASSERT_FALSE(userHand->GetShouldSplit());
            ASSERT_FALSE(userHand->GetShouldStand());
        }
        dealerHand->GetPlayerCards()->RemoveNode(-1);  
    }
    // Player has a hand card value of 13 through 16
    for (int i = 13; i <= 16; i++) {
        userHand->SetCardsTotal(i);
        userHand->SetWager(10);
        for (int j = 0; j < 13; j++) {
            // Add card to dealer hand
            testCard = std::make_shared<Card>(Ranks[j], Suits[0]);
            testNode = dealerHand->GetPlayerCards()->InitNode(testCard);
            dealerHand->SetPlayerCards(testNode);
            blackjack_strategy(userHand, dealerHand);
            // Test strategy for 2 through 6
            if (j != 0 && j < 6) {
                ASSERT_FALSE(userHand->GetShouldDoubleDown());
                ASSERT_FALSE(userHand->GetShouldHit());
                ASSERT_FALSE(userHand->GetShouldSplit());
                ASSERT_TRUE(userHand->GetShouldStand());
            }
            // Test strategy otherwise
            else {
                ASSERT_FALSE(userHand->GetShouldDoubleDown());
                ASSERT_TRUE(userHand->GetShouldHit());
                ASSERT_FALSE(userHand->GetShouldSplit());
                ASSERT_FALSE(userHand->GetShouldStand());
            }
            dealerHand->GetPlayerCards()->RemoveNode(-1);
        }
    }
    // Player has a hand card value of 17 through 21
    for (int i = 17; i <= 21; i++) {
        userHand->SetCardsTotal(i);
        userHand->SetWager(10);
        for (int j = 0; j < 13; j++) {
            // Add card to dealer hand
            testCard = std::make_shared<Card>(Ranks[j], Suits[0]);
            testNode = dealerHand->GetPlayerCards()->InitNode(testCard);
            dealerHand->SetPlayerCards(testNode);
            blackjack_strategy(userHand, dealerHand);
            ASSERT_FALSE(userHand->GetShouldDoubleDown());
            ASSERT_FALSE(userHand->GetShouldHit());
            ASSERT_FALSE(userHand->GetShouldSplit());
            ASSERT_TRUE(userHand->GetShouldStand());
            dealerHand->GetPlayerCards()->RemoveNode(-1);
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
    std::shared_ptr<Hand> userHand(new Hand);
    std::shared_ptr<Hand> dealerHand(new Hand);
    std::shared_ptr<Card> testCard(new Card);
    std::shared_ptr<node<Card>> testNode;
    userHand->SetBankTotal(100);
    // Add first card to dealer
    testCard = std::make_shared<Card>(Ranks[0], Suits[0]);
    testNode = dealerHand->GetPlayerCards()->InitNode(testCard);
    dealerHand->SetPlayerCards(testNode);
    dealerHand->AddHandTotal();
    // Add first card to player - Ace
    testCard = std::make_shared<Card>(Ranks[0], Suits[0]);
    testNode = dealerHand->GetPlayerCards()->InitNode(testCard);
    userHand->SetPlayerCards(testNode);
    userHand->AddHandTotal();
    // Player has a card total of 13 or 14 (Ace, 2 || Ace, 3)
    for (int i = 1; i <= 2; i++) {
        testCard = std::make_shared<Card>(Ranks[i], Suits[0]);
        testNode = dealerHand->GetPlayerCards()->InitNode(testCard);
        userHand->SetPlayerCards(testNode);
        userHand->AddHandTotal();
        for (int j = 0; j < 13; j++) {
            // Add card to dealer hand
            testCard = std::make_shared<Card>(Ranks[j], Suits[0]);
            testNode = dealerHand->GetPlayerCards()->InitNode(testCard);
            dealerHand->SetPlayerCards(testNode);
            // Card being added is a 5 or 6
            if (j == 4 || j == 5) {
                // Player can double down
                {
                    // Set wager
                    userHand->SetWager(10);
                    // Test strategy - Can double down
                    blackjack_strategy(userHand, dealerHand);
                    ASSERT_TRUE(userHand->GetShouldDoubleDown());
                    ASSERT_TRUE(userHand->GetShouldHit());
                    ASSERT_FALSE(userHand->GetShouldSplit());
                    ASSERT_FALSE(userHand->GetShouldStand());
                }
                // Player can't double down
                {
                    // Set wager
                    userHand->SetWager(200);
                    // Test strategy - Can't double down
                    blackjack_strategy(userHand, dealerHand);
                    ASSERT_FALSE(userHand->GetShouldDoubleDown());
                    ASSERT_TRUE(userHand->GetShouldHit());
                    ASSERT_FALSE(userHand->GetShouldSplit());
                    ASSERT_FALSE(userHand->GetShouldStand());
                }
            }
            // Otherwise
            else {
                // Set wager
                userHand->SetWager(10);
                // Test strategy - Can't double down
                blackjack_strategy(userHand, dealerHand);
                ASSERT_FALSE(userHand->GetShouldDoubleDown());
                ASSERT_TRUE(userHand->GetShouldHit());
                ASSERT_FALSE(userHand->GetShouldSplit());
                ASSERT_FALSE(userHand->GetShouldStand());
            }
            dealerHand->GetPlayerCards()->RemoveNode(-1);
        }
        userHand->GetPlayerCards()->RemoveNode(-1);
        userHand->AddHandTotal();
    }
    // Player has a card total of 15 or 16 (Ace, 4 || Ace, 5)
    for (int i = 3; i <= 4; i++) {
        testCard = std::make_shared<Card>(Ranks[i], Suits[0]);
        testNode = dealerHand->GetPlayerCards()->InitNode(testCard);
        userHand->SetPlayerCards(testNode);
        userHand->AddHandTotal();
        for (int j = 0; j < 13; j++) {
            // Add card to dealer hand
            testCard = std::make_shared<Card>(Ranks[j], Suits[0]);
            testNode = dealerHand->GetPlayerCards()->InitNode(testCard);
            dealerHand->SetPlayerCards(testNode);
            // Card being added is a 4, 5, or 6
            if (j == 3 || j == 4 || j == 5) {
                // Player can double down
                {
                    // Set wager
                    userHand->SetWager(10);
                    // Test strategy - Can double down
                    blackjack_strategy(userHand, dealerHand);
                    ASSERT_TRUE(userHand->GetShouldDoubleDown());
                    ASSERT_TRUE(userHand->GetShouldHit());
                    ASSERT_FALSE(userHand->GetShouldSplit());
                    ASSERT_FALSE(userHand->GetShouldStand());
                }
                // Player can't double down
                {
                    // Set wager
                    userHand->SetWager(200);
                    // Test strategy - Can't double down
                    blackjack_strategy(userHand, dealerHand);
                    ASSERT_FALSE(userHand->GetShouldDoubleDown());
                    ASSERT_TRUE(userHand->GetShouldHit());
                    ASSERT_FALSE(userHand->GetShouldSplit());
                    ASSERT_FALSE(userHand->GetShouldStand());
                }
            }
            // Otherwise
            else {
                // Set wager
                userHand->SetWager(10);
                // Test strategy
                blackjack_strategy(userHand, dealerHand);
                ASSERT_FALSE(userHand->GetShouldDoubleDown());
                ASSERT_TRUE(userHand->GetShouldHit());
                ASSERT_FALSE(userHand->GetShouldSplit());
                ASSERT_FALSE(userHand->GetShouldStand());
            }
            dealerHand->GetPlayerCards()->RemoveNode(-1);
        }
        userHand->GetPlayerCards()->RemoveNode(-1);
        userHand->AddHandTotal();
    }
    // Player has a card total of 17 (Ace, 6)
    {
        testCard = std::make_shared<Card>(Ranks[5], Suits[0]);
        testNode = dealerHand->GetPlayerCards()->InitNode(testCard);
        userHand->SetPlayerCards(testNode);
        userHand->AddHandTotal();
        for (int i = 0; i < 13; i++) {
            // Add card to dealer hand
            testCard = std::make_shared<Card>(Ranks[i], Suits[0]);
            testNode = dealerHand->GetPlayerCards()->InitNode(testCard);
            dealerHand->SetPlayerCards(testNode);
            if (i >= 2 && i <= 5) {
                // Player can double down
                {
                    // Set wager
                    userHand->SetWager(10);
                    // Test strategy - Can double down
                    blackjack_strategy(userHand, dealerHand);
                    ASSERT_TRUE(userHand->GetShouldDoubleDown());
                    ASSERT_TRUE(userHand->GetShouldHit());
                    ASSERT_FALSE(userHand->GetShouldSplit());
                    ASSERT_FALSE(userHand->GetShouldStand());
                }
                // Player can't double down
                {
                    // Set wager
                    userHand->SetWager(200);
                    // Test strategy - Can't double down
                    blackjack_strategy(userHand, dealerHand);
                    ASSERT_FALSE(userHand->GetShouldDoubleDown());
                    ASSERT_TRUE(userHand->GetShouldHit());
                    ASSERT_FALSE(userHand->GetShouldSplit());
                    ASSERT_FALSE(userHand->GetShouldStand());
                }
            }
            // Otherwise
            else {
                // Set wager
                userHand->SetWager(10);
                // Test strategy
                blackjack_strategy(userHand, dealerHand);
                ASSERT_FALSE(userHand->GetShouldDoubleDown());
                ASSERT_TRUE(userHand->GetShouldHit());
                ASSERT_FALSE(userHand->GetShouldSplit());
                ASSERT_FALSE(userHand->GetShouldStand());
            }
            dealerHand->GetPlayerCards()->RemoveNode(-1);
        }
        userHand->GetPlayerCards()->RemoveNode(-1);
        userHand->AddHandTotal();
    }
    // Player card total is 18 (Ace, 7)
    {
        testCard = std::make_shared<Card>(Ranks[6], Suits[0]);
        testNode = dealerHand->GetPlayerCards()->InitNode(testCard);
        userHand->SetPlayerCards(testNode);
        userHand->AddHandTotal();
        for (int i = 0; i < 13; i++) {
            // Add card to dealer hand
            testCard = std::make_shared<Card>(Ranks[i], Suits[0]);
            testNode = dealerHand->GetPlayerCards()->InitNode(testCard);
            dealerHand->SetPlayerCards(testNode);
            if (i == 1 || i == 6 || i == 7) {
                // Set wager
                userHand->SetWager(10);
                // Test strategy
                blackjack_strategy(userHand, dealerHand);
                ASSERT_FALSE(userHand->GetShouldDoubleDown());
                ASSERT_FALSE(userHand->GetShouldHit());
                ASSERT_FALSE(userHand->GetShouldSplit());
                ASSERT_TRUE(userHand->GetShouldStand());
            }
            else if (i >= 2 && i <= 5) {
                // Player can double down
                {
                    // Set wager
                    userHand->SetWager(10);
                    // Test strategy - Can double down
                    blackjack_strategy(userHand, dealerHand);
                    ASSERT_TRUE(userHand->GetShouldDoubleDown());
                    ASSERT_FALSE(userHand->GetShouldHit());
                    ASSERT_FALSE(userHand->GetShouldSplit());
                    ASSERT_TRUE(userHand->GetShouldStand());
                }
                // Player can't double down
                {
                    // Set wager
                    userHand->SetWager(200);
                    // Test strategy - Can't double down
                    blackjack_strategy(userHand, dealerHand);
                    ASSERT_FALSE(userHand->GetShouldDoubleDown());
                    ASSERT_FALSE(userHand->GetShouldHit());
                    ASSERT_FALSE(userHand->GetShouldSplit());
                    ASSERT_TRUE(userHand->GetShouldStand());
                }
            }
            else {
                // Set wager
                userHand->SetWager(10);
                // Test strategy
                blackjack_strategy(userHand, dealerHand);
                ASSERT_FALSE(userHand->GetShouldDoubleDown());
                ASSERT_TRUE(userHand->GetShouldHit());
                ASSERT_FALSE(userHand->GetShouldSplit());
                ASSERT_FALSE(userHand->GetShouldStand());
            }
            dealerHand->GetPlayerCards()->RemoveNode(-1);
        }
        userHand->GetPlayerCards()->RemoveNode(-1);
        userHand->AddHandTotal();
    }
    // Player card total is 19, 20, or 21 (Ace, 8 || Ace, 9 || Ace, Ten)
    for (int i = 8; i <= 12; i++) {
        testCard = std::make_shared<Card>(Ranks[i], Suits[0]);
        testNode = dealerHand->GetPlayerCards()->InitNode(testCard);
        userHand->SetPlayerCards(testNode);
        userHand->AddHandTotal();
        for (int j = 0; j < 13; j++) {
            // Add card to dealer hand
            testCard = std::make_shared<Card>(Ranks[j], Suits[0]);
            testNode = dealerHand->GetPlayerCards()->InitNode(testCard);
            dealerHand->SetPlayerCards(testNode);
            // Set wager
            userHand->SetWager(200);
            // Test strategy
            blackjack_strategy(userHand, dealerHand);
            ASSERT_FALSE(userHand->GetShouldDoubleDown());
            ASSERT_FALSE(userHand->GetShouldHit());
            ASSERT_FALSE(userHand->GetShouldSplit());
            ASSERT_TRUE(userHand->GetShouldStand());
            dealerHand->GetPlayerCards()->RemoveNode(-1);
        }
        userHand->GetPlayerCards()->RemoveNode(-1);
        userHand->AddHandTotal();
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
    std::shared_ptr<Hand> userHand(new Hand);
    std::shared_ptr<Hand> dealerHand(new Hand);
    std::shared_ptr<Card> testCard(new Card);
    std::shared_ptr<node<Card>> testNode;
    userHand->SetBankTotal(100);
    // Add first card to dealer
    testCard = std::make_shared<Card>(Ranks[0], Suits[0]);
    testNode = dealerHand->GetPlayerCards()->InitNode(testCard);
    dealerHand->SetPlayerCards(testNode);
    // Player card total is 4 (two, two) or 6 (three, three)
    for (int i = 1; i <= 2; i++) {
        // Add cards to player hand
        testCard = std::make_shared<Card>(Ranks[i], Suits[0]);
        testNode = dealerHand->GetPlayerCards()->InitNode(testCard);
        userHand->AddCardToHand(testNode);
        testCard = std::make_shared<Card>(Ranks[i], Suits[0]);
        testNode = dealerHand->GetPlayerCards()->InitNode(testCard);
        userHand->AddCardToHand(testNode);
        for (int j = 0; j < 13; j++) {
            // Add card to dealer hand
            testCard = std::make_shared<Card>(Ranks[j], Suits[0]);
            testNode = dealerHand->GetPlayerCards()->InitNode(testCard);
            dealerHand->SetPlayerCards(testNode);
            userHand->SetWager(10);
            // Can split hand
            {
                // Test strategy
                blackjack_strategy(userHand, dealerHand);
                if (j == 1 || j == 2) {
                    ASSERT_FALSE(userHand->GetShouldDoubleDown());
                    ASSERT_TRUE(userHand->GetShouldHit());
                    ASSERT_TRUE(userHand->GetShouldSplit());
                    ASSERT_FALSE(userHand->GetShouldStand());
                }
                else if (j >= 3 && j <= 6) {
                    ASSERT_FALSE(userHand->GetShouldDoubleDown());
                    ASSERT_FALSE(userHand->GetShouldHit());
                    ASSERT_TRUE(userHand->GetShouldSplit());
                    ASSERT_FALSE(userHand->GetShouldStand());      
                }
                else {
                    ASSERT_FALSE(userHand->GetShouldDoubleDown());
                    ASSERT_TRUE(userHand->GetShouldHit());
                    ASSERT_FALSE(userHand->GetShouldSplit());
                    ASSERT_FALSE(userHand->GetShouldStand());
                }                
            }
            // Can't split hand
            {
                // Can't split
                userHand->SetSplitHandResponse(true);
                // Test strategy
                blackjack_strategy(userHand, dealerHand);
                ASSERT_FALSE(userHand->GetShouldDoubleDown());
                ASSERT_TRUE(userHand->GetShouldHit());
                ASSERT_FALSE(userHand->GetShouldSplit());
                ASSERT_FALSE(userHand->GetShouldStand());
                // Can split
                userHand->SetSplitHandResponse(false);
            }
            dealerHand->GetPlayerCards()->RemoveNode(-1);
        }
        userHand->GetPlayerCards()->RemoveNode(-1);
        userHand->GetPlayerCards()->RemoveNode(-1);
        userHand->AddHandTotal();
    }
    // Player card total is 8 (four, four)
    {
        // Add cards to player hand, set wager
        testCard = std::make_shared<Card>(Ranks[3], Suits[0]);
        testNode = dealerHand->GetPlayerCards()->InitNode(testCard);
        userHand->AddCardToHand(testNode);
        testCard = std::make_shared<Card>(Ranks[3], Suits[0]);
        testNode = dealerHand->GetPlayerCards()->InitNode(testCard);
        userHand->AddCardToHand(testNode);
        userHand->SetWager(10);
        for (int i = 0; i < 13; i++) {
            // Add card to dealer hand
            testCard = std::make_shared<Card>(Ranks[i], Suits[0]);
            testNode = dealerHand->GetPlayerCards()->InitNode(testCard);
            dealerHand->SetPlayerCards(testNode);
            // Can split hand
            {
                // Test strategy
                blackjack_strategy(userHand, dealerHand);
                if (i == 4 || i == 5) {
                    ASSERT_FALSE(userHand->GetShouldDoubleDown());
                    ASSERT_TRUE(userHand->GetShouldHit());
                    ASSERT_TRUE(userHand->GetShouldSplit());
                    ASSERT_FALSE(userHand->GetShouldStand());
                }
                else {
                    ASSERT_FALSE(userHand->GetShouldDoubleDown());
                    ASSERT_TRUE(userHand->GetShouldHit());
                    ASSERT_FALSE(userHand->GetShouldSplit());
                    ASSERT_FALSE(userHand->GetShouldStand());
                }
            }
            // Can't split hand
            {
                // Can't split
                userHand->SetSplitHandResponse(true);
                // Test strategy
                blackjack_strategy(userHand, dealerHand);
                ASSERT_FALSE(userHand->GetShouldDoubleDown());
                ASSERT_TRUE(userHand->GetShouldHit());
                ASSERT_FALSE(userHand->GetShouldSplit());
                ASSERT_FALSE(userHand->GetShouldStand());
                // Can split
                userHand->SetSplitHandResponse(false);
            }
            dealerHand->GetPlayerCards()->RemoveNode(-1);
        }
        userHand->GetPlayerCards()->RemoveNode(-1);
        userHand->GetPlayerCards()->RemoveNode(-1);
        userHand->AddHandTotal();        
    }
    // Player card total is 10 (five, five)
    {
        // Add cards to player hand, set wager
        testCard = std::make_shared<Card>(Ranks[4], Suits[0]);
        testNode = dealerHand->GetPlayerCards()->InitNode(testCard);
        userHand->AddCardToHand(testNode);
        testCard = std::make_shared<Card>(Ranks[4], Suits[0]);
        testNode = dealerHand->GetPlayerCards()->InitNode(testCard);
        userHand->AddCardToHand(testNode);
        for (int i = 0; i < 13; i++) {
            // Add card to dealer hand
            testCard = std::make_shared<Card>(Ranks[i], Suits[0]);
            testNode = dealerHand->GetPlayerCards()->InitNode(testCard);
            dealerHand->SetPlayerCards(testNode);
            if (i == 0 || i >= 9) {
                // Set wager
                userHand->SetWager(10);
                // Test strategy
                blackjack_strategy(userHand, dealerHand);
                ASSERT_FALSE(userHand->GetShouldDoubleDown());
                ASSERT_TRUE(userHand->GetShouldHit());
                ASSERT_FALSE(userHand->GetShouldSplit());
                ASSERT_FALSE(userHand->GetShouldStand());
            }
            else {
                // Can double down
                {
                    // Set wager
                    userHand->SetWager(10);
                    // Test strategy
                    blackjack_strategy(userHand, dealerHand);
                    ASSERT_TRUE(userHand->GetShouldDoubleDown());
                    ASSERT_TRUE(userHand->GetShouldHit());
                    ASSERT_FALSE(userHand->GetShouldSplit());
                    ASSERT_FALSE(userHand->GetShouldStand());
                }
                // Cannot double down
                {
                    // Set wager
                    userHand->SetWager(101);
                    // Test strategy
                    blackjack_strategy(userHand, dealerHand);
                    ASSERT_FALSE(userHand->GetShouldDoubleDown());
                    ASSERT_TRUE(userHand->GetShouldHit());
                    ASSERT_FALSE(userHand->GetShouldSplit());
                    ASSERT_FALSE(userHand->GetShouldStand());
                }
            }
            dealerHand->GetPlayerCards()->RemoveNode(-1);
        }
        userHand->GetPlayerCards()->RemoveNode(-1);
        userHand->GetPlayerCards()->RemoveNode(-1);
        userHand->AddHandTotal();
    }
    // Player card total is 12 (six, six || Ace, Ace) 
    {
        // Player has two sixes
        {
            // Add cards to player hand, set wager
            testCard = std::make_shared<Card>(Ranks[5], Suits[0]);
            testNode = dealerHand->GetPlayerCards()->InitNode(testCard);
            userHand->AddCardToHand(testNode);
            testCard = std::make_shared<Card>(Ranks[5], Suits[0]);
            testNode = dealerHand->GetPlayerCards()->InitNode(testCard);
            userHand->AddCardToHand(testNode);
            userHand->SetWager(10);
            for (int i = 0; i < 13; i++) {
                // Add card to dealer hand
                testCard = std::make_shared<Card>(Ranks[i], Suits[0]);
                testNode = dealerHand->GetPlayerCards()->InitNode(testCard);
                dealerHand->SetPlayerCards(testNode);
                // Can split
                {
                    // Test strategy
                    blackjack_strategy(userHand, dealerHand);
                    if (i >= 1 && i <= 5) {
                        ASSERT_FALSE(userHand->GetShouldDoubleDown());
                        ASSERT_FALSE(userHand->GetShouldHit());
                        ASSERT_TRUE(userHand->GetShouldSplit());
                        ASSERT_FALSE(userHand->GetShouldStand());
                    }
                    else if (i == 6) {
                        ASSERT_FALSE(userHand->GetShouldDoubleDown());
                        ASSERT_TRUE(userHand->GetShouldHit());
                        ASSERT_TRUE(userHand->GetShouldSplit());
                        ASSERT_FALSE(userHand->GetShouldStand());
                    }
                    else {
                        ASSERT_FALSE(userHand->GetShouldDoubleDown());
                        ASSERT_TRUE(userHand->GetShouldHit());
                        ASSERT_FALSE(userHand->GetShouldSplit());
                        ASSERT_FALSE(userHand->GetShouldStand());
                    }
                }
                // Can't split
                {
                    userHand->SetSplitHandResponse(true);
                    // Test strategy
                    blackjack_strategy(userHand, dealerHand);
                    if ((i >= 1 && i <= 2) || (i == 0 || i >= 6)) {
                        ASSERT_FALSE(userHand->GetShouldDoubleDown());
                        ASSERT_TRUE(userHand->GetShouldHit());
                        ASSERT_FALSE(userHand->GetShouldSplit());
                        ASSERT_FALSE(userHand->GetShouldStand());
                    }
                    else {
                        ASSERT_FALSE(userHand->GetShouldDoubleDown());
                        ASSERT_FALSE(userHand->GetShouldHit());
                        ASSERT_FALSE(userHand->GetShouldSplit());
                        ASSERT_TRUE(userHand->GetShouldStand());
                    }
                    userHand->SetSplitHandResponse(false);
                }
                dealerHand->GetPlayerCards()->RemoveNode(-1);
            }
            userHand->GetPlayerCards()->RemoveNode(-1);
            userHand->GetPlayerCards()->RemoveNode(-1);
            userHand->AddHandTotal();
        }
        // Player has two aces
        {
            // Add cards to player hand, set wager
            testCard = std::make_shared<Card>(Ranks[0], Suits[0]);
            testNode = dealerHand->GetPlayerCards()->InitNode(testCard);
            userHand->AddCardToHand(testNode);
            testCard = std::make_shared<Card>(Ranks[0], Suits[0]);
            testNode = dealerHand->GetPlayerCards()->InitNode(testCard);
            userHand->AddCardToHand(testNode);
            userHand->SetWager(10);
            for (int i = 0; i < 13; i++) {
                // Add card to dealer hand
                testCard = std::make_shared<Card>(Ranks[i], Suits[0]);
                testNode = dealerHand->GetPlayerCards()->InitNode(testCard);
                dealerHand->SetPlayerCards(testNode);
                // Can split
                {
                    // Test strategy
                    blackjack_strategy(userHand, dealerHand);
                    ASSERT_FALSE(userHand->GetShouldDoubleDown());
                    ASSERT_FALSE(userHand->GetShouldHit());
                    ASSERT_TRUE(userHand->GetShouldSplit());
                    ASSERT_FALSE(userHand->GetShouldStand());
                }
                // Can't split
                {
                    userHand->SetSplitAcesResponse(true);
                    // Test strategy
                    blackjack_strategy(userHand, dealerHand);
                    if ((i >= 1 && i <= 2) || (i == 0 || i >= 6)) {
                        ASSERT_FALSE(userHand->GetShouldDoubleDown());
                        ASSERT_TRUE(userHand->GetShouldHit());
                        ASSERT_FALSE(userHand->GetShouldSplit());
                        ASSERT_FALSE(userHand->GetShouldStand());
                    }
                    else {
                        ASSERT_FALSE(userHand->GetShouldDoubleDown());
                        ASSERT_FALSE(userHand->GetShouldHit());
                        ASSERT_FALSE(userHand->GetShouldSplit());
                        ASSERT_TRUE(userHand->GetShouldStand());
                    }
                    userHand->SetSplitAcesResponse(false);
                }
                dealerHand->GetPlayerCards()->RemoveNode(-1);
            }
            userHand->GetPlayerCards()->RemoveNode(-1);
            userHand->GetPlayerCards()->RemoveNode(-1);
            userHand->AddHandTotal();
        }
    }
    // Player card total is 14 (seven, seven) 
    {
        // Add cards to player hand, set wager
            testCard = std::make_shared<Card>(Ranks[6], Suits[0]);
            testNode = dealerHand->GetPlayerCards()->InitNode(testCard);
            userHand->AddCardToHand(testNode);
            testCard = std::make_shared<Card>(Ranks[6], Suits[0]);
            testNode = dealerHand->GetPlayerCards()->InitNode(testCard);
            userHand->AddCardToHand(testNode);
            userHand->SetWager(10);
        for (int i = 0; i < 13; i++) {
            // Add card to dealer hand
            testCard = std::make_shared<Card>(Ranks[i], Suits[0]);
            testNode = dealerHand->GetPlayerCards()->InitNode(testCard);
            dealerHand->SetPlayerCards(testNode);
            // Can split
            {
                // Test strategy
                blackjack_strategy(userHand, dealerHand);
                if (i >= 1 && i <= 6) {
                    ASSERT_FALSE(userHand->GetShouldDoubleDown());
                    ASSERT_FALSE(userHand->GetShouldHit());
                    ASSERT_TRUE(userHand->GetShouldSplit());
                    ASSERT_FALSE(userHand->GetShouldStand());
                }
                else if (i == 7) {
                    ASSERT_FALSE(userHand->GetShouldDoubleDown());
                    ASSERT_TRUE(userHand->GetShouldHit());
                    ASSERT_TRUE(userHand->GetShouldSplit());
                    ASSERT_FALSE(userHand->GetShouldStand());
                }
                else {
                    ASSERT_FALSE(userHand->GetShouldDoubleDown());
                    ASSERT_TRUE(userHand->GetShouldHit());
                    ASSERT_FALSE(userHand->GetShouldSplit());
                    ASSERT_FALSE(userHand->GetShouldStand());
                }
            }
            // Can't split
            {
                userHand->SetSplitHandResponse(true);
                // Test strategy
                blackjack_strategy(userHand, dealerHand);
                if (i >= 1 && i <= 5) {
                    ASSERT_FALSE(userHand->GetShouldDoubleDown());
                    ASSERT_FALSE(userHand->GetShouldHit());
                    ASSERT_FALSE(userHand->GetShouldSplit());
                    ASSERT_TRUE(userHand->GetShouldStand());
                }
                else {
                    ASSERT_FALSE(userHand->GetShouldDoubleDown());
                    ASSERT_TRUE(userHand->GetShouldHit());
                    ASSERT_FALSE(userHand->GetShouldSplit());
                    ASSERT_FALSE(userHand->GetShouldStand());
                }
                userHand->SetSplitHandResponse(false);
            }
            dealerHand->GetPlayerCards()->RemoveNode(-1);
        }
        userHand->GetPlayerCards()->RemoveNode(-1);
        userHand->GetPlayerCards()->RemoveNode(-1);
        userHand->AddHandTotal();
    }
    // Player card total is 16 (eight, eight)
    {
        // Add cards to player hand, set wager
        testCard = std::make_shared<Card>(Ranks[7], Suits[0]);
        testNode = dealerHand->GetPlayerCards()->InitNode(testCard);
        userHand->AddCardToHand(testNode);
        testCard = std::make_shared<Card>(Ranks[7], Suits[0]);
        testNode = dealerHand->GetPlayerCards()->InitNode(testCard);
        userHand->AddCardToHand(testNode);
        userHand->SetWager(10);
        for (int i = 0; i < 13; i++) {
            // Add card to dealer hand
            testCard = std::make_shared<Card>(Ranks[i], Suits[0]);
            testNode = dealerHand->GetPlayerCards()->InitNode(testCard);
            dealerHand->SetPlayerCards(testNode);
            // Can split
            {
                // Test strategy
                blackjack_strategy(userHand, dealerHand);
                ASSERT_FALSE(userHand->GetShouldDoubleDown());
                ASSERT_FALSE(userHand->GetShouldHit());
                ASSERT_TRUE(userHand->GetShouldSplit());
                ASSERT_FALSE(userHand->GetShouldStand());                
            }
            // Can't split
            {
                userHand->SetSplitHandResponse(true);
                // Test strategy
                blackjack_strategy(userHand, dealerHand);
                if (i >= 1 && i <= 5) {
                    ASSERT_FALSE(userHand->GetShouldDoubleDown());
                    ASSERT_FALSE(userHand->GetShouldHit());
                    ASSERT_FALSE(userHand->GetShouldSplit());
                    ASSERT_TRUE(userHand->GetShouldStand());
                }
                else {
                    ASSERT_FALSE(userHand->GetShouldDoubleDown());
                    ASSERT_TRUE(userHand->GetShouldHit());
                    ASSERT_FALSE(userHand->GetShouldSplit());
                    ASSERT_FALSE(userHand->GetShouldStand());
                }
                userHand->SetSplitHandResponse(false);
            }
            dealerHand->GetPlayerCards()->RemoveNode(-1);
        }
        userHand->GetPlayerCards()->RemoveNode(-1);
        userHand->GetPlayerCards()->RemoveNode(-1);
        userHand->AddHandTotal();
    }
    // Player card total is 18 (nine, nine)
    {
        // Add cards to player hand, set wager
        testCard = std::make_shared<Card>(Ranks[8], Suits[0]);
        testNode = dealerHand->GetPlayerCards()->InitNode(testCard);
        userHand->AddCardToHand(testNode);
        testCard = std::make_shared<Card>(Ranks[8], Suits[0]);
        testNode = dealerHand->GetPlayerCards()->InitNode(testCard);
        userHand->AddCardToHand(testNode);
        userHand->SetWager(10);
        for (int i = 0; i < 13; i++) {
            // Add card to dealer hand
            testCard = std::make_shared<Card>(Ranks[i], Suits[0]);
            testNode = dealerHand->GetPlayerCards()->InitNode(testCard);
            dealerHand->SetPlayerCards(testNode);
            // Can split
            {
                // Test strategy
                blackjack_strategy(userHand, dealerHand); 
                if (i == 0 || i == 6 || i >= 9) {
                    ASSERT_FALSE(userHand->GetShouldDoubleDown());
                    ASSERT_FALSE(userHand->GetShouldHit());
                    ASSERT_FALSE(userHand->GetShouldSplit());
                    ASSERT_TRUE(userHand->GetShouldStand());
                }
                else {
                    ASSERT_FALSE(userHand->GetShouldDoubleDown());
                    ASSERT_FALSE(userHand->GetShouldHit());
                    ASSERT_TRUE(userHand->GetShouldSplit());
                    ASSERT_FALSE(userHand->GetShouldStand());
                }
            }
            // Can't split
            {
                userHand->SetSplitHandResponse(true);
                // Test strategy
                blackjack_strategy(userHand, dealerHand);
                ASSERT_FALSE(userHand->GetShouldDoubleDown());
                ASSERT_FALSE(userHand->GetShouldHit());
                ASSERT_FALSE(userHand->GetShouldSplit());
                ASSERT_TRUE(userHand->GetShouldStand());                
                userHand->SetSplitHandResponse(false);
            }
            dealerHand->GetPlayerCards()->RemoveNode(-1);
        }
        userHand->GetPlayerCards()->RemoveNode(-1);
        userHand->GetPlayerCards()->RemoveNode(-1);
        userHand->AddHandTotal();
    }
    // Player card total is 20 (face, face)
    {
        // Add cards to player hand, set wager
        for (int i = 9; i <= 12; i++) {
            testCard = std::make_shared<Card>(Ranks[i], Suits[0]);
            testNode = dealerHand->GetPlayerCards()->InitNode(testCard);
            userHand->AddCardToHand(testNode);
            testCard = std::make_shared<Card>(Ranks[i], Suits[0]);
            testNode = dealerHand->GetPlayerCards()->InitNode(testCard);
            userHand->AddCardToHand(testNode);
            userHand->SetWager(10);
            for (int j = 0; j < 13; j++) {
                // Add card to dealer hand
                testCard = std::make_shared<Card>(Ranks[j], Suits[0]);
                testNode = dealerHand->GetPlayerCards()->InitNode(testCard);
                dealerHand->SetPlayerCards(testNode);
                // Can split
                {
                    // Test strategy
                    blackjack_strategy(userHand, dealerHand);
                    ASSERT_FALSE(userHand->GetShouldDoubleDown());
                    ASSERT_FALSE(userHand->GetShouldHit());
                    ASSERT_FALSE(userHand->GetShouldSplit());
                    ASSERT_TRUE(userHand->GetShouldStand()); 
                }
                // Can't split
                {
                    userHand->SetSplitHandResponse(true);
                    // Test strategy
                    blackjack_strategy(userHand, dealerHand);
                    ASSERT_FALSE(userHand->GetShouldDoubleDown());
                    ASSERT_FALSE(userHand->GetShouldHit());
                    ASSERT_FALSE(userHand->GetShouldSplit());
                    ASSERT_TRUE(userHand->GetShouldStand()); 
                    userHand->SetSplitHandResponse(false);                   
                }
                dealerHand->GetPlayerCards()->RemoveNode(-1);
            }
            userHand->GetPlayerCards()->RemoveNode(-1);
            userHand->GetPlayerCards()->RemoveNode(-1);
            userHand->AddHandTotal();
        }
    }
    std::cout.rdbuf(oldCoutBuffer);
}

// Deal hand test
TEST_F(test_x, DealHand) {
    // Suppress Cout's
    std::streambuf* oldCoutBuffer = std::cout.rdbuf();
    NullBuffer nullBuffer;
    std::cout.rdbuf(&nullBuffer);
    // Create hands and shoe
    std::shared_ptr<Hand> testHand(new Hand);
    std::shared_ptr<Hand> dealerHand(new Hand);
    std::shared_ptr<Shoe> testShoe(new Shoe);
    testHand->SetName("Borby");
    dealerHand->SetName("Dealer");
    testHand->SetBankTotal(100);
    testHand->SetWager(10);
    testShoe->SetNumOfDecks(1);
    testShoe->CreateShoe();
    // Test function
    deal_hand(testHand, dealerHand, testShoe);
    EXPECT_EQ(testHand->GetPlayerCards()->GetSize(), 2);
    EXPECT_EQ(dealerHand->GetPlayerCards()->GetSize(), 2);
    std::cout.rdbuf(oldCoutBuffer);
}

// Dealer showing Ace check
TEST_F(test_x, DealerShowingAce) {
    // Suppress Cout's
    std::streambuf* oldCoutBuffer = std::cout.rdbuf();
    NullBuffer nullBuffer;
    std::cout.rdbuf(&nullBuffer);
    // Create hands and shoe
    std::shared_ptr<Hand> testHand(new Hand);
    std::shared_ptr<Hand> dealerHand(new Hand);
    std::shared_ptr<Shoe> testShoe(new Shoe);
    std::shared_ptr<Card> testCard(new Card);
    std::shared_ptr<node<Card>> testNode;
    // Create dummy hand for player
    testCard = std::make_shared<Card>(Ranks[0], Suits[0]);
    testNode = testHand->GetPlayerCards()->InitNode(testCard);
    testHand->AddCardToHand(testNode);
    testCard = std::make_shared<Card>(Ranks[0], Suits[0]);
    testNode = testHand->GetPlayerCards()->InitNode(testCard);
    testHand->AddCardToHand(testNode);
    testHand->SetBankTotal(100);
    // Can buy insurance check
    for (int i = 0; i < 13; i++) {
        testCard = std::make_shared<Card>(Ranks[i], Suits[0]);
        testNode = dealerHand->GetPlayerCards()->InitNode(testCard);
        dealerHand->AddCardToHand(testNode);
        for (int j = 0; j < 13; j++) {
            testCard = std::make_shared<Card>(Ranks[i], Suits[0]);
            testNode = dealerHand->GetPlayerCards()->InitNode(testCard);
            dealerHand->AddCardToHand(testNode);
            if (dealerHand->GetPlayerCards()->RetrieveNode(-1)->data.GetRank() == Ranks[0]) {
                // Enough currency
                {
                    testHand->SetWager(200);
                    testHand->ParametersCheck(dealerHand);
                    EXPECT_TRUE(testHand->GetCanBuyInsurance());
                }
                // Not enough currency
                {
                    testHand->SetWager(400);
                    testHand->ParametersCheck(dealerHand);
                    EXPECT_FALSE(testHand->GetCanBuyInsurance());
                }
            }
            else {
                testHand->SetWager(200);
                testHand->ParametersCheck(dealerHand);
                EXPECT_FALSE(testHand->GetCanBuyInsurance());
            }
            dealerHand->GetPlayerCards()->RemoveNode(-1);
            dealerHand->AddHandTotal();
        }
        dealerHand->GetPlayerCards()->RemoveNode(-1);
        dealerHand->AddHandTotal();
    }
    std::cout.rdbuf(oldCoutBuffer);
}

// Split hand check
TEST_F(test_x, SplitHandCheck) {
    std::shared_ptr<Hand> testHand1(new Hand);
    std::shared_ptr<Hand> testHand2(new Hand);
    std::shared_ptr<Card> testCard(new Card);
    std::shared_ptr<node<Card>> testNode;
    testHand1->SetName("Borby");
    testHand1->SetBankTotal(100);
    testHand1->SetWager(10);
    testCard = std::make_shared<Card>(Ranks[0], Suits[0]);
    testNode = testHand1->GetPlayerCards()->InitNode(testCard);
    testHand1->SetPlayerCards(testNode);
    testCard = std::make_shared<Card>(Ranks[12], Suits[1]);
    testNode = testHand1->GetPlayerCards()->InitNode(testCard);
    testHand1->SetPlayerCards(testNode);
    EXPECT_EQ(testHand1->GetPlayerCards()->GetSize(), 2);
    std::vector<std::shared_ptr<Hand>> newHands = split_hand(testHand1);
    testHand1 = newHands.at(0);
    testHand2 = newHands.at(1);
    EXPECT_EQ(testHand1->GetPlayerCards()->GetSize(), 1);
    EXPECT_EQ(testHand1->GetPlayerCards()->RetrieveNode(0)->data.GetRank(), Ranks[0]);
    EXPECT_EQ(testHand1->GetPlayerCards()->RetrieveNode(0)->data.GetSuit(), Suits[0]);
    EXPECT_EQ(testHand2->GetPlayerCards()->GetSize(), 1);
    EXPECT_EQ(testHand2->GetPlayerCards()->RetrieveNode(0)->data.GetRank(), Ranks[12]);
    EXPECT_EQ(testHand2->GetPlayerCards()->RetrieveNode(0)->data.GetSuit(), Suits[1]);
}