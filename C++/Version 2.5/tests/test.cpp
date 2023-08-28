#include <gtest/gtest.h>
#include "../app/Assets/HPP/Game.hpp"

class test_x : public ::testing::Test {};

/////////////////////////////////////////
// HashTable Table Tests
/////////////////////////////////////////

// HashTable table initialize test
TEST_F(test_x, HashTableInitTest) {
    // Create table
    std::shared_ptr<HashTable> testFilter;
    // Change bit size
    for (int i = 1; i < random_int(900, 1000); i++) {
        // Change hash function iterations
        for (int j = 1; j < random_int(20, 40); j++) {
            testFilter = std::make_shared<HashTable>(i, j);
            EXPECT_EQ(testFilter->GetTable().size(), i);
            EXPECT_EQ(testFilter->GetHashFuncIterations(), j);
        }
    }
}

// HashTable table hash calc test
TEST_F(test_x, HashTableHashCalc) {
    // Create test variables
    std::string testString = "Hello World!";
    // Create table
    std::shared_ptr<HashTable> testFilter(new HashTable(1000, 12));
    unsigned int tempHash = testFilter->CalculateHashCode(testString); 
    EXPECT_TRUE(tempHash > 0);
}

// HashTable table bucket calc test
TEST_F(test_x, HashTableBucketCalc) {
    // Create test variables
    std::string testString = "Goodbye World!";
    // Create table
    std::shared_ptr<HashTable> testFilter(new HashTable(1000, 12));
    testFilter->SetHashCode(testString);
    testFilter->SetBucket(testFilter->GetHashCode());
    EXPECT_TRUE(testFilter->GetBucket() >= 0 && testFilter->GetBucket() < 1000);
}

// HashTable table add element test
TEST_F(test_x, HashTableAdd) {
    // Create test variables
    std::string testString = "What world?";
    // Create table
    std::shared_ptr<HashTable> testFilter;
    for (int i = 1; i < random_int(80, 100); i++) {
        testFilter = std::make_shared<HashTable>(random_int(1000, 2000), i);
        testFilter->AddToTable(testString);
        EXPECT_TRUE(testFilter->GetBucket() >= 0);
        EXPECT_TRUE(testFilter->GetBucket() < testFilter->GetTable().size());
    }
}

// HashTable table clear test
TEST_F(test_x, HashTableClear) {
    // Create test variables
    std::string testString = "What is this world?";
    // Create table
    std::shared_ptr<HashTable> testFilter;
    for (int i = 1; i < random_int(80, 100); i++) {
        testFilter = std::make_shared<HashTable>(random_int(1000, 2000), i);
        testFilter->AddToTable(testString);
        testFilter->ClearHashTable();
        for (int i = 0; i < testFilter->GetTable().size(); i++) {
            EXPECT_FALSE(testFilter->GetTable().at(i));
        }
    }
}

// HashTable table contains test
TEST_F(test_x, HashTableContains) {
    // Create table
    std::shared_ptr<HashTable> testFilter(new HashTable(1000, 12));
    std::vector<std::string> testTrueVector = {"This", "is", "a", "test", "of", "bloom", "filters", "efficiency"};
    std::vector<std::string> testFalseVector = {"On", "the", "other", "hand", "I'm", "mister", "negative", "examination"};
    for (int i = 0; i < testTrueVector.size(); i++) {
        testFilter->AddToTable(testTrueVector.at(i));
        EXPECT_TRUE(testFilter->Contains(testTrueVector.at(i)));
        EXPECT_FALSE(testFilter->Contains(testFalseVector.at(i)));
    }
}

// HashTable table remove test
TEST_F(test_x, HashTableRemove) {
    // Create table
    std::shared_ptr<HashTable> testFilter(new HashTable(1000, 12));
    std::vector<std::string> testTrueVector = {"This", "is", "a", "test", "of", "bloom", "filters", "efficiency"};
    for (int i = 0; i < testTrueVector.size(); i++) {
        testFilter->AddToTable(testTrueVector.at(i));
    }
    while (!testTrueVector.empty()) {
        testFilter->RemoveElement(testTrueVector.at(testTrueVector.size() - 1));
        EXPECT_FALSE(testFilter->Contains(testTrueVector.at(testTrueVector.size() - 1)));
        testTrueVector.pop_back();
    }
}

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
        testShoe->CreateShoeSim();
        EXPECT_EQ(testShoe->GetCardsInShoe()->GetSize(), testShoe->GetNumOfDecks()*52);
        testShoe->EmptyShoe();
        EXPECT_EQ(testShoe->GetCardsInShoe()->GetSize(), 0);
    }
}

// Shoe class, draw test
TEST_F(test_x, ShoeClassDraw) {
    std::shared_ptr<Shoe> testShoe(new Shoe());
    testShoe->SetNumOfDecks(1);
    testShoe->CreateShoeSim();
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
    // Test initial table values
    EXPECT_EQ(testHand->GetHashTable()->GetTable().size(), HASTABLESIZE);
    EXPECT_EQ(testHand->GetHashTable()->GetHashFuncIterations(), HASHTABLEITERATIONS);
    for (int i = 0; i < testHand->GetHashTable()->GetTable().size(); i++) {
        EXPECT_FALSE(testHand->GetHashTable()->GetTable().at(i));
    }
    // Test initial float values
    EXPECT_EQ(testHand->GetInsuranceWager(), 0);
    EXPECT_EQ(testHand->GetNet(), 0);
    EXPECT_EQ(testHand->GetWager(), 0);
    // Test initial integer values
    EXPECT_EQ(testHand->GetCardsTotal(), 0);
    // Test initial string values
    EXPECT_EQ(testHand->GetDisplayCardsTotal(), "");
    EXPECT_EQ(testHand->GetDisplayInsuranceWager(), "");
    EXPECT_EQ(testHand->GetDisplayNet(), "");
    EXPECT_EQ(testHand->GetDisplayWager(), "");
    // Test linked list sizes
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
            EXPECT_TRUE(testHand->GetHashTable()->Contains("ParamInHand"));
            testHand->GetHashTable()->ClearHashTable();
            testHand->CheckParamInHand("S", Suits[j]);
            EXPECT_TRUE(testHand->GetHashTable()->Contains("ParamInHand"));
            testHand->GetHashTable()->ClearHashTable();
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
                ASSERT_TRUE(testHand->GetHashTable()->Contains("SameParamInHand"));
            }
            else {
                ASSERT_FALSE(testHand->GetHashTable()->Contains("SameParamInHand"));
            }
            testHand->GetHashTable()->ClearHashTable();
            testHand->CheckSameParamInHand("S");
            ASSERT_FALSE(testHand->GetHashTable()->Contains("SameParamInHand"));
            testHand->GetHashTable()->ClearHashTable();
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
                ASSERT_TRUE(testHand->GetHashTable()->Contains("SameParamInHand"));
            }
            else {
                ASSERT_FALSE(testHand->GetHashTable()->Contains("SameParamInHand"));
            }
            testHand->GetHashTable()->ClearHashTable();
            testHand->CheckSameParamInHand("R");
            ASSERT_FALSE(testHand->GetHashTable()->Contains("SameParamInHand"));
            testHand->GetHashTable()->ClearHashTable();
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
        ASSERT_FALSE(testHand->GetHashTable()->Contains("HasBlackjack"));
        ASSERT_EQ(testHand->GetPlayerCards()->GetSize(), 2);
        testHand->GetPlayerCards()->RemoveNode(-1);
        testHand->GetHashTable()->ClearHashTable();
    }
    // Test for true cases
    for (int i = 9; i < 13; i++) {
        testCard2 = std::make_shared<Card>(Card(Ranks[i], Suits[0]));
        testNode2 = testShoe->GetCardsInShoe()->InitNode(testCard2);
        testHand->AddCardToHand(testNode2);
        testHand->CheckBlackJack();
        ASSERT_TRUE(testHand->GetHashTable()->Contains("HasBlackjack"));
        ASSERT_EQ(testHand->GetPlayerCards()->GetSize(), 2);
        testHand->GetPlayerCards()->RemoveNode(-1);
        testHand->GetHashTable()->ClearHashTable();
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
        ASSERT_FALSE(testHand->GetHashTable()->Contains("HasBlackjack"));
        ASSERT_EQ(testHand->GetPlayerCards()->GetSize(), 3);
        testHand->GetPlayerCards()->RemoveNode(-1);
        testHand->GetHashTable()->ClearHashTable();
    }
}

// Hand class, hit hand test
TEST_F(test_x, HandClassHitHand) {
    // Create test hand, shoe, and card
    std::shared_ptr<Hand> testHand(new Hand);
    std::shared_ptr<Shoe> testShoe(new Shoe);
    testShoe->SetNumOfDecks(1);
    testShoe->CreateShoeSim();
    int handCardCounter = 0;
    for (int i = 52; i > 0; i--) {
        handCardCounter++;
        EXPECT_EQ(testShoe->GetCardsInShoe()->GetSize(), i);
        testHand->HitHand(testShoe);
        EXPECT_EQ(testHand->GetPlayerCards()->GetSize(), handCardCounter);
    }
}

// Hand class, place wager
TEST_F(test_x, HandClassPlaceWager) {
    // Create objects
    std::shared_ptr<Hand> testHand(new Hand);
    float wager = 5;
    float bank = 100;
    float priorBank = bank;
    int loopCounter = 0;
    while (bank >= 0) {
        loopCounter++;
        testHand->PlaceWagerSim(bank, wager);
        EXPECT_EQ(bank, priorBank - loopCounter * testHand->GetWager());
    }
}

// Hand class, copy variables test
TEST_F(test_x, HandClassCopy) {
    std::shared_ptr<Hand> hand1(new Hand);
    std::shared_ptr<Hand> hand1Copy(new Hand);
    hand1->SetWager(10);
    hand1Copy->CopyVariables(hand1);
    ASSERT_EQ(hand1->GetWager(), 10);
    ASSERT_EQ(hand1Copy->GetWager(), 10);
}

// Hand class, create an insurance wager for a player
TEST_F(test_x, HandClassInsuranceDeposit) {
    // Create objects
    std::shared_ptr<Hand> testHand(new Hand);
    float wager = 5;
    float bank = 100;
    float priorBank = 0;
    while (bank > wager) {
        priorBank = bank;
        // No insurance check
        testHand->PlaceWagerSim(bank, wager);
        {
            testHand->InsuranceSim(bank, false);
            EXPECT_EQ(bank, priorBank - testHand->GetWager());
        }
        // Insurance check
        {
            testHand->InsuranceSim(bank, true);
            EXPECT_EQ(bank, priorBank - wager - testHand->GetInsuranceWager());
        }
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
    float bank = 100;
    // Test can double down
    for (int i = 1; i <= 200; i++) {
        testHand->SetWager(i);
        {
            {
                testHand->ParametersCheck(dealerHand, bank);
                if (bank >= testHand->GetWager()) {
                    EXPECT_TRUE(testHand->GetHashTable()->Contains("CanDoubleDown"));
                }
                else {
                    EXPECT_FALSE(testHand->GetHashTable()->Contains("CanDoubleDown"));
                }
            }
            testHand->GetHashTable()->ClearHashTable();
            testHand->GetHashTable()->AddToTable("DoubleDownResponse");
            {
                testHand->GetHashTable()->AddToTable("CanDoubleDown");
                testHand->ParametersCheck(dealerHand, bank);
                EXPECT_FALSE(testHand->GetHashTable()->Contains("CanDoubleDown"));
            }
            testHand->GetHashTable()->ClearHashTable();
        }
        testHand->GetHashTable()->AddToTable("ChoseHitHand");
        testHand->ParametersCheck(dealerHand, bank);
        EXPECT_FALSE(testHand->GetHashTable()->Contains("CanDoubleDown"));
        testHand->GetHashTable()->ClearHashTable();
    }
    testHand->GetPlayerCards()->ClearList();
    // Soft seventeen check
    // (Ace, Ace, Ace, Ace, Ace, Ace, Ace)
    for (int i = 1; i <= 7; i++) {
        testCard = std::make_shared<Card>(Ranks[0], Suits[0]);
        testNode = testShoe->GetCardsInShoe()->InitNode(testCard);
        testHand->AddCardToHand(testNode);  
    }
    testHand->GetHashTable()->AddToTable("SoftSevenTeen");
    testHand->ParametersCheck(dealerHand, bank);
    EXPECT_TRUE(testHand->GetHashTable()->Contains("SoftSevenTeen"));
    testHand->GetPlayerCards()->ClearList();
    testHand->GetHashTable()->ClearHashTable();
    // (King, 7)
    testCard = std::make_shared<Card>(Ranks[12], Suits[0]);
    testNode = testShoe->GetCardsInShoe()->InitNode(testCard);
    testHand->AddCardToHand(testNode);
    testCard = std::make_shared<Card>(Ranks[6], Suits[0]);
    testNode = testShoe->GetCardsInShoe()->InitNode(testCard);
    testHand->AddCardToHand(testNode);
    testHand->GetHashTable()->AddToTable("SoftSevenTeen");
    testHand->ParametersCheck(dealerHand, bank);
    EXPECT_FALSE(testHand->GetHashTable()->Contains("SoftSevenTeen"));
    testHand->GetPlayerCards()->ClearList();
    testHand->GetHashTable()->ClearHashTable();
    // (Queen, Ace, Ace, Ace, Ace, Ace, Ace, Ace, Ace)
    testCard = std::make_shared<Card>(Ranks[11], Suits[0]);
    testNode = testShoe->GetCardsInShoe()->InitNode(testCard);
    testHand->AddCardToHand(testNode);
    for (int i = 1; i <= 7; i++) {
        testCard = std::make_shared<Card>(Ranks[0], Suits[0]);
        testNode = testShoe->GetCardsInShoe()->InitNode(testCard);
        testHand->AddCardToHand(testNode);  
    }
    testHand->GetHashTable()->AddToTable("SoftSevenTeen");
    testHand->ParametersCheck(dealerHand, bank);
    EXPECT_FALSE(testHand->GetHashTable()->Contains("SoftSevenTeen"));
    testHand->GetPlayerCards()->ClearList();
    testHand->AddCardToHand(testNode);
    testHand->AddCardToHand(testNode);
    dealerHand->GetPlayerCards()->ClearList();
    testHand->GetHashTable()->ClearHashTable();
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
            if (dealerHand->GetPlayerCards()->RetrieveNode(-1)->data.GetRank() == Ranks[0] && !dealerHand->GetHashTable()->Contains("HasBlackjack")) {
                for (int k = 1; k <= 400; k++) {
                    testHand->SetWager(k);
                    testHand->GetHashTable()->AddToTable("CanBuyInsurance");
                    testHand->ParametersCheck(dealerHand, bank);
                    if (k <= 200) {
                        EXPECT_TRUE(testHand->GetHashTable()->Contains("CanBuyInsurance"));
                    }
                    else {
                        EXPECT_FALSE(testHand->GetHashTable()->Contains("CanBuyInsurance"));
                    }
                    testHand->GetHashTable()->ClearHashTable();
                }
            }
            else {
                testHand->GetHashTable()->AddToTable("CanBuyInsurance");
                testHand->ParametersCheck(dealerHand, bank);
                EXPECT_FALSE(testHand->GetHashTable()->Contains("CanBuyInsurance"));
            }
            dealerHand->GetPlayerCards()->RemoveNode(-1);
            testHand->GetHashTable()->ClearHashTable();
            dealerHand->GetHashTable()->ClearHashTable();
        }
        dealerHand->GetPlayerCards()->RemoveNode(0);
        dealerHand->GetHashTable()->ClearHashTable();
    }
    testHand->GetPlayerCards()->ClearList();
    testHand->GetHashTable()->ClearHashTable();
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
            if (testHand->GetHashTable()->Contains("SameParamInHand")) {
                for (int k = 1; k <= 200; k++) {
                    testHand->SetWager(k);
                    testHand->GetHashTable()->AddToTable("CanSplitAces");
                    testHand->GetHashTable()->AddToTable("CanSplitHand");
                    testHand->ParametersCheck(dealerHand, bank);
                    testHand->CheckParamInHand("R", Ranks[0]);
                    if (k <= 100) {
                        if (testHand->GetHashTable()->Contains("ParamInHand")) {
                            EXPECT_TRUE(testHand->GetHashTable()->Contains("CanSplitAces"));
                            EXPECT_FALSE(testHand->GetHashTable()->Contains("CanSplitHand"));
                        }
                        else {
                            EXPECT_FALSE(testHand->GetHashTable()->Contains("CanSplitAces"));
                            EXPECT_TRUE(testHand->GetHashTable()->Contains("CanSplitHand"));
                        }
                    }
                    else {
                        EXPECT_FALSE(testHand->GetHashTable()->Contains("CanSplitAces"));
                        EXPECT_FALSE(testHand->GetHashTable()->Contains("CanSplitHand"));
                    }
                    testHand->GetHashTable()->ClearHashTable();
                }
            }
            else {
                testHand->GetHashTable()->AddToTable("CanSplitAces");
                testHand->GetHashTable()->AddToTable("CanSplitHand");
                testHand->ParametersCheck(dealerHand, bank);
                EXPECT_FALSE(testHand->GetHashTable()->Contains("CanSplitAces"));
                EXPECT_FALSE(testHand->GetHashTable()->Contains("CanSplitHand"));
            }
            testHand->GetPlayerCards()->RemoveNode(-1);
            testHand->GetHashTable()->ClearHashTable();
        }
        testHand->GetPlayerCards()->RemoveNode(0);
        testHand->GetHashTable()->ClearHashTable();
    }
}

// Hand class, reset test
TEST_F(test_x, HandClassReset) {
    std::shared_ptr<Hand> testHand(new Hand);
    std::shared_ptr<Shoe> testShoe(new Shoe);
    testShoe->SetNumOfDecks(1);
    testShoe->CreateShoeSim();
    // Set dummy values
    testHand->SetWager(10);
    testHand->SetInsuranceWager(5);
    testHand->SetNet(5);
    testHand->HitHand(testShoe);
    testHand->HitHand(testShoe);
    EXPECT_EQ(testHand->GetPlayerCards()->GetSize(), 2);
    EXPECT_EQ(testHand->GetInsuranceWager(), 5);
    EXPECT_EQ(testHand->GetNet(), 5);
    EXPECT_EQ(testHand->GetWager(), 10);
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 5; j++) {
            testHand->GetHashTable()->AddToTable(testHand->GetValuesMatrix()[i][j]);
            EXPECT_TRUE(testHand->GetHashTable()->Contains(testHand->GetValuesMatrix()[i][j]));
        }
    }
    // Reset Hand
    testHand->ResetHand();
    EXPECT_EQ(testHand->GetPlayerCards()->GetSize(), 0);
    EXPECT_EQ(testHand->GetInsuranceWager(), 0);
    EXPECT_EQ(testHand->GetNet(), 0);
    EXPECT_EQ(testHand->GetWager(), 0);
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 5; j++) {
            EXPECT_FALSE(testHand->GetHashTable()->Contains(testHand->GetValuesMatrix()[i][j]));
        }
    }
}

/////////////////////////////////////////
// Player Class Tests
/////////////////////////////////////////

// Player class initialization
TEST_F(test_x, PlayerClassInit) {
    std::shared_ptr<Player> testPlayer(new Player());
    EXPECT_EQ(testPlayer->GetBankTotal(), 0);
    EXPECT_EQ(testPlayer->GetBlackjackHands(), 0);
    EXPECT_EQ(testPlayer->GetCurrentHandsPossessed(), 0);
    EXPECT_EQ(testPlayer->GetHandsLost(), 0);
    EXPECT_EQ(testPlayer->GetHandsPlayed(), 0);
    EXPECT_EQ(testPlayer->GetHandsPushed(), 0);
    EXPECT_EQ(testPlayer->GetHandsWon(), 0);
    EXPECT_EQ(testPlayer->GetCurrentHands()->GetSize(), 0);
    EXPECT_EQ(testPlayer->GetTotalHandBankTotals()->GetSize(), 0);
    EXPECT_EQ(testPlayer->GetTotalHandCardTotals()->GetSize(), 0);
    EXPECT_EQ(testPlayer->GetTotalHandNets()->GetSize(), 0);
    EXPECT_EQ(testPlayer->GetTotalHandsPlayed()->GetSize(), 0);
    EXPECT_EQ(testPlayer->GetTotalHandWagers()->GetSize(), 0);
    EXPECT_EQ(testPlayer->GetDisplayBankTotal(), "");
    EXPECT_EQ(testPlayer->GetDisplayName(), "");
    EXPECT_EQ(testPlayer->GetName(), "");
}

// Player class setter functions test
TEST_F(test_x, PlayerClassSetters) {
    // Test player
    std::shared_ptr<Player> testPlayer(new Player());
    // Float value tests
    float bank = 1;
    while (bank <= 100) {
        testPlayer->SetBankTotal(bank);
        EXPECT_EQ(testPlayer->GetBankTotal(), bank);
        bank++;
    }
    // Integer value tests
    for (int i = 1; i < random_int(100, 200); i++) {
        testPlayer->SetBlackjackHands();
        testPlayer->SetCurrentHandsPossessed();
        testPlayer->SetHandsLost();
        testPlayer->SetHandsPlayed();
        testPlayer->SetHandsWon();
        EXPECT_EQ(testPlayer->GetBlackjackHands(), i);
        EXPECT_EQ(testPlayer->GetCurrentHandsPossessed(), i);
        EXPECT_EQ(testPlayer->GetHandsLost(), i);
        EXPECT_EQ(testPlayer->GetHandsPlayed(), i);
        EXPECT_EQ(testPlayer->GetHandsWon(), i);
    }
    testPlayer->GetBlackjackHands() = 0;
    testPlayer->GetCurrentHandsPossessed() = 0;
    testPlayer->GetHandsLost() = 0;
    testPlayer->GetHandsPlayed() = 0;
    testPlayer->GetHandsWon() = 0;
    // List tests
    // Create shoe of cards
    std::shared_ptr<Shoe> testShoe(new Shoe());
    testShoe->SetNumOfDecks(1);
    testShoe->CreateShoeSim();
    // Create dummy hand
    std::shared_ptr<Hand> testHand(new Hand());
    testHand->HitHand(testShoe);
    testHand->HitHand(testShoe);
    // Add Hand to current hands
    for (int i = 1; i <= random_int(500, 1000); i++) {
        // Player hand tests
        testPlayer->SetBankTotal(1000);
        testHand->PlaceWagerSim(testPlayer->GetBankTotal(), i);
        testHand->SetNet(testPlayer->GetBankTotal() + testHand->GetWager());
        testPlayer->SetCurrentHands(testHand);
        EXPECT_EQ(testPlayer->GetCurrentHands()->GetSize(), testPlayer->GetCurrentHandsPossessed());
        EXPECT_EQ(testPlayer->GetCurrentHands()->RetrieveNode(i - 1)->data->GetPlayerCards()->GetSize(), 2);
        EXPECT_EQ(testPlayer->GetCurrentHands()->RetrieveNode(i - 1)->data->GetWager(), i);
        EXPECT_EQ(testPlayer->GetCurrentHands()->RetrieveNode(i - 1)->data->GetNet(), testHand->GetNet());
        // Total hand bank totals
        testPlayer->SetTotalHandBankTotals(testPlayer->GetBankTotal());
        EXPECT_EQ(testPlayer->GetTotalHandBankTotals()->GetSize(), i);
        EXPECT_EQ(testPlayer->GetTotalHandBankTotals()->RetrieveNode(i - 1)->data, testPlayer->GetBankTotal());
        // Total hand card totals
        testPlayer->SetTotalHandCardTotals(testHand->GetCardsTotal());
        EXPECT_EQ(testPlayer->GetTotalHandCardTotals()->GetSize(), i);
        EXPECT_EQ(testPlayer->GetTotalHandCardTotals()->RetrieveNode(i - 1)->data, testPlayer->GetCurrentHands()->RetrieveNode(i - 1)->data->GetCardsTotal());
        // Total hands played totals
        testPlayer->SetTotalHandsPlayed(testPlayer->GetCurrentHands()->GetSize());
        EXPECT_EQ(testPlayer->GetTotalHandsPlayed()->GetSize(), i);
        EXPECT_EQ(testPlayer->GetTotalHandsPlayed()->RetrieveNode(i - 1)->data, testPlayer->GetTotalHandsPlayed()->GetSize());
        // Total hand wager total
        testPlayer->SetTotalHandWagers(testPlayer->GetCurrentHands()->RetrieveNode(i - 1)->data->GetWager());
        EXPECT_EQ(testPlayer->GetTotalHandWagers()->GetSize(), i);
        EXPECT_EQ(testPlayer->GetTotalHandWagers()->RetrieveNode(i - 1)->data, testPlayer->GetCurrentHands()->RetrieveNode(i - 1)->data->GetWager());
    }
    // String tests
    std::string testName = "Borby";
    for (int i = 0; i < random_int(500, 1000); i++) {
        testPlayer->SetName(testName);
        testName += 'y';
    }
}

// Update bank check test
TEST_F(test_x, PlayerClassUpdateBank) {
    // Test player
    std::shared_ptr<Player> testPlayer(new Player());
    testPlayer->SetName("Borby");
    testPlayer->SetBankTotal(200);
    float prior_bank = testPlayer->GetBankTotal();
    // Creat shoe
    std::shared_ptr<Shoe> testShoe(new Shoe());
    testShoe->SetNumOfDecks(1);
    testShoe->CreateShoeSim();
    // Create dummy hand
    std::shared_ptr<Hand> testHand(new Hand());
    // Test deposit
    for (int i = 1; i <= 100; i++) {
        testHand->SetWager(i);
        testPlayer->SetBankTotal(prior_bank);
        testPlayer->UpdateBank(testHand, 0);
        EXPECT_EQ(testPlayer->GetBankTotal(), prior_bank - testHand->GetWager());
    }
    // Test Win
    for (int i = 1; i <= 100; i++) {
        testPlayer->SetBankTotal(prior_bank);
        testHand->PlaceWagerSim(testPlayer->GetBankTotal(), i);
        testHand->SetNet(0);
        testPlayer->UpdateBank(testHand, 1);
        EXPECT_EQ(testHand->GetWager(), i);
        EXPECT_EQ(testHand->GetInsuranceWager(), 0);
        EXPECT_EQ(testHand->GetNet(), i);
        EXPECT_EQ(testPlayer->GetBankTotal(), prior_bank + i);
        EXPECT_EQ(testPlayer->GetTotalHandBankTotals()->GetSize(), i);
        EXPECT_EQ(testPlayer->GetTotalHandBankTotals()->RetrieveNode(i - 1)->data, prior_bank + i);
        EXPECT_EQ(testPlayer->GetTotalHandCardTotals()->GetSize(), i);
        EXPECT_EQ(testPlayer->GetTotalHandCardTotals()->RetrieveNode(i - 1)->data, testHand->GetCardsTotal());
        EXPECT_EQ(testPlayer->GetHandsPlayed(), i);
        EXPECT_EQ(testPlayer->GetTotalHandsPlayed()->GetSize(), i);
        EXPECT_EQ(testPlayer->GetTotalHandsPlayed()->RetrieveNode(i - 1)->data, i);
        EXPECT_EQ(testPlayer->GetTotalHandNets()->GetSize(), i);
        EXPECT_EQ(testPlayer->GetTotalHandNets()->RetrieveNode(i - 1)->data, i);
        EXPECT_EQ(testPlayer->GetTotalHandWagers()->GetSize(), i);
        EXPECT_EQ(testPlayer->GetTotalHandWagers()->RetrieveNode(i - 1)->data, i);
        EXPECT_EQ(testPlayer->GetHandsWon(), i);
        EXPECT_EQ(testPlayer->GetHandsLost(), 0);
        EXPECT_EQ(testPlayer->GetHandsPushed(), 0);
        EXPECT_EQ(testPlayer->GetBlackjackHands(), 0);
    }
    testPlayer->SetBankTotal(prior_bank);
    testPlayer->GetTotalHandBankTotals()->ClearList();
    testPlayer->GetTotalHandCardTotals()->ClearList();
    testPlayer->GetTotalHandsPlayed()->ClearList();
    testPlayer->GetTotalHandNets()->ClearList();
    testPlayer->GetTotalHandWagers()->ClearList();
    testPlayer->GetHandsPlayed() = 0;
    testPlayer->GetBlackjackHands() = 0;
    testPlayer->GetHandsWon() = 0;
    testPlayer->GetHandsLost() = 0;
    testPlayer->GetHandsPushed() = 0;
    // Test Lose
    for (int i = 1; i <= 100; i++) {
        testPlayer->SetBankTotal(prior_bank);
        testHand->PlaceWagerSim(testPlayer->GetBankTotal(), i);
        testHand->SetNet(0);
        testPlayer->UpdateBank(testHand, 2);
        EXPECT_EQ(testHand->GetWager(), i);
        EXPECT_EQ(testHand->GetInsuranceWager(), 0);
        EXPECT_EQ(testHand->GetNet(), -i);
        EXPECT_EQ(testPlayer->GetBankTotal(), prior_bank - i);
        EXPECT_EQ(testPlayer->GetTotalHandBankTotals()->GetSize(), i);
        EXPECT_EQ(testPlayer->GetTotalHandBankTotals()->RetrieveNode(i - 1)->data, prior_bank - i);
        EXPECT_EQ(testPlayer->GetTotalHandCardTotals()->GetSize(), i);
        EXPECT_EQ(testPlayer->GetTotalHandCardTotals()->RetrieveNode(i - 1)->data, testHand->GetCardsTotal());
        EXPECT_EQ(testPlayer->GetHandsPlayed(), i);
        EXPECT_EQ(testPlayer->GetTotalHandsPlayed()->GetSize(), i);
        EXPECT_EQ(testPlayer->GetTotalHandsPlayed()->RetrieveNode(i - 1)->data, i);
        EXPECT_EQ(testPlayer->GetTotalHandNets()->GetSize(), i);
        EXPECT_EQ(testPlayer->GetTotalHandNets()->RetrieveNode(i - 1)->data, -i);
        EXPECT_EQ(testPlayer->GetTotalHandWagers()->GetSize(), i);
        EXPECT_EQ(testPlayer->GetTotalHandWagers()->RetrieveNode(i - 1)->data, i);
        EXPECT_EQ(testPlayer->GetHandsWon(), 0);
        EXPECT_EQ(testPlayer->GetHandsLost(), i);
        EXPECT_EQ(testPlayer->GetHandsPushed(), 0);
        EXPECT_EQ(testPlayer->GetBlackjackHands(), 0);
    }
    // Test Push
    testPlayer->SetBankTotal(prior_bank);
    testPlayer->GetTotalHandBankTotals()->ClearList();
    testPlayer->GetTotalHandCardTotals()->ClearList();
    testPlayer->GetTotalHandsPlayed()->ClearList();
    testPlayer->GetTotalHandNets()->ClearList();
    testPlayer->GetTotalHandWagers()->ClearList();
    testPlayer->GetHandsPlayed() = 0;
    testPlayer->GetBlackjackHands() = 0;
    testPlayer->GetHandsWon() = 0;
    testPlayer->GetHandsLost() = 0;
    testPlayer->GetHandsPushed() = 0;
    for (int i = 1; i <= 100; i++) {
        testPlayer->SetBankTotal(prior_bank);
        testHand->PlaceWagerSim(testPlayer->GetBankTotal(), i);
        testHand->SetNet(0);
        testPlayer->UpdateBank(testHand, 3);
        EXPECT_EQ(testHand->GetWager(), i);
        EXPECT_EQ(testHand->GetInsuranceWager(), 0);
        EXPECT_EQ(testHand->GetNet(), 0);
        EXPECT_EQ(testPlayer->GetBankTotal(), prior_bank);
        EXPECT_EQ(testPlayer->GetTotalHandBankTotals()->GetSize(), i);
        EXPECT_EQ(testPlayer->GetTotalHandBankTotals()->RetrieveNode(i - 1)->data, prior_bank);
        EXPECT_EQ(testPlayer->GetTotalHandCardTotals()->GetSize(), i);
        EXPECT_EQ(testPlayer->GetTotalHandCardTotals()->RetrieveNode(i - 1)->data, testHand->GetCardsTotal());
        EXPECT_EQ(testPlayer->GetHandsPlayed(), i);
        EXPECT_EQ(testPlayer->GetTotalHandsPlayed()->GetSize(), i);
        EXPECT_EQ(testPlayer->GetTotalHandsPlayed()->RetrieveNode(i - 1)->data, i);
        EXPECT_EQ(testPlayer->GetTotalHandNets()->GetSize(), i);
        EXPECT_EQ(testPlayer->GetTotalHandNets()->RetrieveNode(i - 1)->data, 0);
        EXPECT_EQ(testPlayer->GetTotalHandWagers()->GetSize(), i);
        EXPECT_EQ(testPlayer->GetTotalHandWagers()->RetrieveNode(i - 1)->data, i);
        EXPECT_EQ(testPlayer->GetHandsWon(), 0);
        EXPECT_EQ(testPlayer->GetHandsLost(), 0);
        EXPECT_EQ(testPlayer->GetHandsPushed(), i);
        EXPECT_EQ(testPlayer->GetBlackjackHands(), 0);
    }
    // Test Blackjack
    testPlayer->SetBankTotal(prior_bank);
    testPlayer->GetTotalHandBankTotals()->ClearList();
    testPlayer->GetTotalHandCardTotals()->ClearList();
    testPlayer->GetTotalHandsPlayed()->ClearList();
    testPlayer->GetTotalHandNets()->ClearList();
    testPlayer->GetTotalHandWagers()->ClearList();
    testPlayer->GetHandsPlayed() = 0;
    testPlayer->GetBlackjackHands() = 0;
    testPlayer->GetHandsWon() = 0;
    testPlayer->GetHandsLost() = 0;
    testPlayer->GetHandsPushed() = 0;
    for (int i = 1; i <= 100; i++) {
        testPlayer->SetBankTotal(prior_bank);
        testHand->PlaceWagerSim(testPlayer->GetBankTotal(), i);
        testHand->SetNet(0);
        testPlayer->UpdateBank(testHand, 4);
        EXPECT_EQ(testHand->GetWager(), i);
        EXPECT_EQ(testHand->GetInsuranceWager(), 0);
        EXPECT_EQ(testHand->GetNet(), 1.5 * i);
        EXPECT_EQ(testPlayer->GetBankTotal(), prior_bank + 1.5 * i);
        EXPECT_EQ(testPlayer->GetTotalHandBankTotals()->GetSize(), i);
        EXPECT_EQ(testPlayer->GetTotalHandBankTotals()->RetrieveNode(i - 1)->data, prior_bank + 1.5 * i);
        EXPECT_EQ(testPlayer->GetTotalHandCardTotals()->GetSize(), i);
        EXPECT_EQ(testPlayer->GetTotalHandCardTotals()->RetrieveNode(i - 1)->data, testHand->GetCardsTotal());
        EXPECT_EQ(testPlayer->GetHandsPlayed(), i);
        EXPECT_EQ(testPlayer->GetTotalHandsPlayed()->GetSize(), i);
        EXPECT_EQ(testPlayer->GetTotalHandsPlayed()->RetrieveNode(i - 1)->data, i);
        EXPECT_EQ(testPlayer->GetTotalHandNets()->GetSize(), i);
        EXPECT_EQ(testPlayer->GetTotalHandNets()->RetrieveNode(i - 1)->data, 1.5 * i);
        EXPECT_EQ(testPlayer->GetTotalHandWagers()->GetSize(), i);
        EXPECT_EQ(testPlayer->GetTotalHandWagers()->RetrieveNode(i - 1)->data, i);
        EXPECT_EQ(testPlayer->GetHandsWon(), 0);
        EXPECT_EQ(testPlayer->GetHandsLost(), 0);
        EXPECT_EQ(testPlayer->GetHandsPushed(), 0);
        EXPECT_EQ(testPlayer->GetBlackjackHands(), i);
    }
    // Test player wins hand, loses insurance
    testPlayer->SetBankTotal(prior_bank);
    testPlayer->GetTotalHandBankTotals()->ClearList();
    testPlayer->GetTotalHandCardTotals()->ClearList();
    testPlayer->GetTotalHandsPlayed()->ClearList();
    testPlayer->GetTotalHandNets()->ClearList();
    testPlayer->GetTotalHandWagers()->ClearList();
    testPlayer->GetHandsPlayed() = 0;
    testPlayer->GetBlackjackHands() = 0;
    testPlayer->GetHandsWon() = 0;
    testPlayer->GetHandsLost() = 0;
    testPlayer->GetHandsPushed() = 0;
    for (int i = 1; i <= 100; i++) {
        testPlayer->SetBankTotal(prior_bank);
        testHand->PlaceWagerSim(testPlayer->GetBankTotal(), i);
        testHand->InsuranceSim(testPlayer->GetBankTotal(), true);
        testHand->SetNet(0);
        testPlayer->UpdateBank(testHand, 5);
        EXPECT_EQ(testHand->GetWager(), 1.5 * i);
        EXPECT_EQ(testHand->GetInsuranceWager(), 0.5 * i);
        EXPECT_EQ(testHand->GetNet(), (i + testHand->GetInsuranceWager()) / 3);
        EXPECT_EQ(testPlayer->GetBankTotal(), prior_bank + (i + testHand->GetInsuranceWager()) / 3);
        EXPECT_EQ(testPlayer->GetTotalHandBankTotals()->GetSize(), i);
        EXPECT_EQ(testPlayer->GetTotalHandBankTotals()->RetrieveNode(i - 1)->data, prior_bank + (i + testHand->GetInsuranceWager()) / 3);
        EXPECT_EQ(testPlayer->GetTotalHandCardTotals()->GetSize(), i);
        EXPECT_EQ(testPlayer->GetTotalHandCardTotals()->RetrieveNode(i - 1)->data, testHand->GetCardsTotal());
        EXPECT_EQ(testPlayer->GetHandsPlayed(), i);
        EXPECT_EQ(testPlayer->GetTotalHandsPlayed()->GetSize(), i);
        EXPECT_EQ(testPlayer->GetTotalHandsPlayed()->RetrieveNode(i - 1)->data, i);
        EXPECT_EQ(testPlayer->GetTotalHandNets()->GetSize(), i);
        EXPECT_EQ(testPlayer->GetTotalHandNets()->RetrieveNode(i - 1)->data, (i + testHand->GetInsuranceWager()) / 3);
        EXPECT_EQ(testPlayer->GetTotalHandWagers()->GetSize(), i);
        EXPECT_EQ(testPlayer->GetTotalHandWagers()->RetrieveNode(i - 1)->data, 1.5 * i);
        EXPECT_EQ(testPlayer->GetHandsWon(), i);
        EXPECT_EQ(testPlayer->GetHandsLost(), 0);
        EXPECT_EQ(testPlayer->GetHandsPushed(), 0);
        EXPECT_EQ(testPlayer->GetBlackjackHands(), 0);
    }
    // Test player loses hand, wins insurance
    testPlayer->SetBankTotal(prior_bank);
    testPlayer->GetTotalHandBankTotals()->ClearList();
    testPlayer->GetTotalHandCardTotals()->ClearList();
    testPlayer->GetTotalHandsPlayed()->ClearList();
    testPlayer->GetTotalHandNets()->ClearList();
    testPlayer->GetTotalHandWagers()->ClearList();
    testPlayer->GetHandsPlayed() = 0;
    testPlayer->GetBlackjackHands() = 0;
    testPlayer->GetHandsWon() = 0;
    testPlayer->GetHandsLost() = 0;
    testPlayer->GetHandsPushed() = 0;
    for (int i = 1; i <= 100; i++) {
        testPlayer->SetBankTotal(prior_bank);
        testHand->PlaceWagerSim(testPlayer->GetBankTotal(), i);
        testHand->InsuranceSim(testPlayer->GetBankTotal(), true);
        testHand->SetNet(0);
        testPlayer->UpdateBank(testHand, 6);
        EXPECT_EQ(testHand->GetWager(), 1.5 * i);
        EXPECT_EQ(testHand->GetInsuranceWager(), 0.5 * i);
        EXPECT_EQ(testHand->GetNet(), 0);
        EXPECT_EQ(testPlayer->GetBankTotal(), prior_bank);
        EXPECT_EQ(testPlayer->GetTotalHandBankTotals()->GetSize(), i);
        EXPECT_EQ(testPlayer->GetTotalHandBankTotals()->RetrieveNode(i - 1)->data, prior_bank);
        EXPECT_EQ(testPlayer->GetTotalHandCardTotals()->GetSize(), i);
        EXPECT_EQ(testPlayer->GetTotalHandCardTotals()->RetrieveNode(i - 1)->data, testHand->GetCardsTotal());
        EXPECT_EQ(testPlayer->GetHandsPlayed(), i);
        EXPECT_EQ(testPlayer->GetTotalHandsPlayed()->GetSize(), i);
        EXPECT_EQ(testPlayer->GetTotalHandsPlayed()->RetrieveNode(i - 1)->data, i);
        EXPECT_EQ(testPlayer->GetTotalHandNets()->GetSize(), i);
        EXPECT_EQ(testPlayer->GetTotalHandNets()->RetrieveNode(i - 1)->data, 0);
        EXPECT_EQ(testPlayer->GetTotalHandWagers()->GetSize(), i);
        EXPECT_EQ(testPlayer->GetTotalHandWagers()->RetrieveNode(i - 1)->data, 1.5 * i);
        EXPECT_EQ(testPlayer->GetHandsWon(), 0);
        EXPECT_EQ(testPlayer->GetHandsLost(), i);
        EXPECT_EQ(testPlayer->GetHandsPushed(), 0);
        EXPECT_EQ(testPlayer->GetBlackjackHands(), 0);
    }
    // Test player loses hand, loses insurance
    testPlayer->SetBankTotal(prior_bank);
    testPlayer->GetTotalHandBankTotals()->ClearList();
    testPlayer->GetTotalHandCardTotals()->ClearList();
    testPlayer->GetTotalHandsPlayed()->ClearList();
    testPlayer->GetTotalHandNets()->ClearList();
    testPlayer->GetTotalHandWagers()->ClearList();
    testPlayer->GetHandsPlayed() = 0;
    testPlayer->GetBlackjackHands() = 0;
    testPlayer->GetHandsWon() = 0;
    testPlayer->GetHandsLost() = 0;
    testPlayer->GetHandsPushed() = 0;
    for (int i = 1; i <= 100; i++) {
        testPlayer->SetBankTotal(prior_bank);
        testHand->PlaceWagerSim(testPlayer->GetBankTotal(), i);
        testHand->InsuranceSim(testPlayer->GetBankTotal(), true);
        testHand->SetNet(0);
        testPlayer->UpdateBank(testHand, 7);
        EXPECT_EQ(testHand->GetWager(), 1.5 * i);
        EXPECT_EQ(testHand->GetInsuranceWager(), 0.5 * i);
        EXPECT_EQ(testHand->GetNet(), -1.5 * i);
        EXPECT_EQ(testPlayer->GetBankTotal(), prior_bank - 1.5 * i);
        EXPECT_EQ(testPlayer->GetTotalHandBankTotals()->GetSize(), i);
        EXPECT_EQ(testPlayer->GetTotalHandBankTotals()->RetrieveNode(i - 1)->data, prior_bank - 1.5 * i);
        EXPECT_EQ(testPlayer->GetTotalHandCardTotals()->GetSize(), i);
        EXPECT_EQ(testPlayer->GetTotalHandCardTotals()->RetrieveNode(i - 1)->data, testHand->GetCardsTotal());
        EXPECT_EQ(testPlayer->GetHandsPlayed(), i);
        EXPECT_EQ(testPlayer->GetTotalHandsPlayed()->GetSize(), i);
        EXPECT_EQ(testPlayer->GetTotalHandsPlayed()->RetrieveNode(i - 1)->data, i);
        EXPECT_EQ(testPlayer->GetTotalHandNets()->GetSize(), i);
        EXPECT_EQ(testPlayer->GetTotalHandNets()->RetrieveNode(i - 1)->data, -1.5 * i);
        EXPECT_EQ(testPlayer->GetTotalHandWagers()->GetSize(), i);
        EXPECT_EQ(testPlayer->GetTotalHandWagers()->RetrieveNode(i - 1)->data, 1.5 * i);
        EXPECT_EQ(testPlayer->GetHandsWon(), 0);
        EXPECT_EQ(testPlayer->GetHandsLost(), i);
        EXPECT_EQ(testPlayer->GetHandsPushed(), 0);
        EXPECT_EQ(testPlayer->GetBlackjackHands(), 0);
    }
    // Test player has blackjack, wins insurance
    testPlayer->SetBankTotal(prior_bank);
    testPlayer->GetTotalHandBankTotals()->ClearList();
    testPlayer->GetTotalHandCardTotals()->ClearList();
    testPlayer->GetTotalHandsPlayed()->ClearList();
    testPlayer->GetTotalHandNets()->ClearList();
    testPlayer->GetTotalHandWagers()->ClearList();
    testPlayer->GetHandsPlayed() = 0;
    testPlayer->GetBlackjackHands() = 0;
    testPlayer->GetHandsWon() = 0;
    testPlayer->GetHandsLost() = 0;
    testPlayer->GetHandsPushed() = 0;
    for (int i = 1; i <= 100; i++) {
        testPlayer->SetBankTotal(prior_bank);
        testHand->PlaceWagerSim(testPlayer->GetBankTotal(), i);
        testHand->InsuranceSim(testPlayer->GetBankTotal(), true);
        testHand->SetNet(0);
        testPlayer->UpdateBank(testHand, 8);
        EXPECT_EQ(testHand->GetWager(), 1.5 * i);
        EXPECT_EQ(testHand->GetInsuranceWager(), 0.5 * i);
        EXPECT_EQ(testHand->GetNet(), i);
        EXPECT_EQ(testPlayer->GetBankTotal(), prior_bank + i);
        EXPECT_EQ(testPlayer->GetTotalHandBankTotals()->GetSize(), i);
        EXPECT_EQ(testPlayer->GetTotalHandBankTotals()->RetrieveNode(i - 1)->data, prior_bank + i);
        EXPECT_EQ(testPlayer->GetTotalHandCardTotals()->GetSize(), i);
        EXPECT_EQ(testPlayer->GetTotalHandCardTotals()->RetrieveNode(i - 1)->data, testHand->GetCardsTotal());
        EXPECT_EQ(testPlayer->GetHandsPlayed(), i);
        EXPECT_EQ(testPlayer->GetTotalHandsPlayed()->GetSize(), i);
        EXPECT_EQ(testPlayer->GetTotalHandsPlayed()->RetrieveNode(i - 1)->data, i);
        EXPECT_EQ(testPlayer->GetTotalHandNets()->GetSize(), i);
        EXPECT_EQ(testPlayer->GetTotalHandNets()->RetrieveNode(i - 1)->data, i);
        EXPECT_EQ(testPlayer->GetTotalHandWagers()->GetSize(), i);
        EXPECT_EQ(testPlayer->GetTotalHandWagers()->RetrieveNode(i - 1)->data, 1.5 * i);
        EXPECT_EQ(testPlayer->GetHandsWon(), 0);
        EXPECT_EQ(testPlayer->GetHandsLost(), 0);
        EXPECT_EQ(testPlayer->GetHandsPushed(), i);
        EXPECT_EQ(testPlayer->GetBlackjackHands(), 0);
    }
    // Test player has blackjack, loses insurance
    testPlayer->SetBankTotal(prior_bank);
    testPlayer->GetTotalHandBankTotals()->ClearList();
    testPlayer->GetTotalHandCardTotals()->ClearList();
    testPlayer->GetTotalHandsPlayed()->ClearList();
    testPlayer->GetTotalHandNets()->ClearList();
    testPlayer->GetTotalHandWagers()->ClearList();
    testPlayer->GetHandsPlayed() = 0;
    testPlayer->GetBlackjackHands() = 0;
    testPlayer->GetHandsWon() = 0;
    testPlayer->GetHandsLost() = 0;
    testPlayer->GetHandsPushed() = 0;
    for (int i = 1; i <= 100; i++) {
        testPlayer->SetBankTotal(prior_bank);
        testHand->PlaceWagerSim(testPlayer->GetBankTotal(), i);
        testHand->InsuranceSim(testPlayer->GetBankTotal(), true);
        testHand->SetNet(0);
        testPlayer->UpdateBank(testHand, 9);
        EXPECT_EQ(testHand->GetWager(), 1.5 * i);
        EXPECT_EQ(testHand->GetInsuranceWager(), 0.5 * i);
        EXPECT_EQ(testHand->GetNet(), i);
        EXPECT_EQ(testPlayer->GetBankTotal(), prior_bank + i);
        EXPECT_EQ(testPlayer->GetTotalHandBankTotals()->GetSize(), i);
        EXPECT_EQ(testPlayer->GetTotalHandBankTotals()->RetrieveNode(i - 1)->data, prior_bank + i);
        EXPECT_EQ(testPlayer->GetTotalHandCardTotals()->GetSize(), i);
        EXPECT_EQ(testPlayer->GetTotalHandCardTotals()->RetrieveNode(i - 1)->data, testHand->GetCardsTotal());
        EXPECT_EQ(testPlayer->GetHandsPlayed(), i);
        EXPECT_EQ(testPlayer->GetTotalHandsPlayed()->GetSize(), i);
        EXPECT_EQ(testPlayer->GetTotalHandsPlayed()->RetrieveNode(i - 1)->data, i);
        EXPECT_EQ(testPlayer->GetTotalHandNets()->GetSize(), i);
        EXPECT_EQ(testPlayer->GetTotalHandNets()->RetrieveNode(i - 1)->data, i);
        EXPECT_EQ(testPlayer->GetTotalHandWagers()->GetSize(), i);
        EXPECT_EQ(testPlayer->GetTotalHandWagers()->RetrieveNode(i - 1)->data, 1.5 * i);
        EXPECT_EQ(testPlayer->GetHandsWon(), 0);
        EXPECT_EQ(testPlayer->GetHandsLost(), 0);
        EXPECT_EQ(testPlayer->GetHandsPushed(), 0);
        EXPECT_EQ(testPlayer->GetBlackjackHands(), i);
    }
}

/////////////////////////////////////////
// Core Functions Tests
/////////////////////////////////////////

// Deal hand test
TEST_F(test_x, DealHand) {
    // Create hands and shoe
    std::shared_ptr<Player> testPlayer(new Player());
    std::shared_ptr<Player> testDealer(new Player());
    std::shared_ptr<Shoe> testShoe(new Shoe);
    testPlayer->SetName("Borby");
    testDealer->SetName("Dealer");
    testPlayer->SetBankTotal(100);
    float previousBank = testPlayer->GetBankTotal();
    testShoe->SetNumOfDecks(1);
    testShoe->CreateShoeSim();
    int random_wager = random_int(1, 100);
    // Test function
    deal_hand_sim(testPlayer, testDealer, testShoe, random_wager);
    EXPECT_EQ(testShoe->GetCardsInShoe()->GetSize(), 48);
    EXPECT_EQ(testPlayer->GetCurrentHands()->GetSize(), 1);
    EXPECT_EQ(testPlayer->GetCurrentHands()->RetrieveNode(0)->data->GetPlayerCards()->GetSize(), 2);
    EXPECT_EQ(testDealer->GetCurrentHands()->GetSize(), 1);
    EXPECT_EQ(testDealer->GetCurrentHands()->RetrieveNode(0)->data->GetPlayerCards()->GetSize(), 2);
    EXPECT_EQ(testPlayer->GetBankTotal(), previousBank - random_wager);
    EXPECT_EQ(testPlayer->GetCurrentHands()->RetrieveNode(0)->data->GetWager(), random_wager);
}

// Dealer showing Ace check
TEST_F(test_x, DealerShowingAce) {
    std::shared_ptr<Player> testPlayer(new Player());
    std::shared_ptr<Player> testDealer(new Player());
    std::shared_ptr<Shoe> testShoe(new Shoe);
    std::shared_ptr<Shoe> copyShoe(new Shoe);
    std::shared_ptr<Card> testCard(new Card);
    std::shared_ptr<node<Card>> testNode;
    float priorBank = 0;
    float playerWager = 10;
    float playerBank = 100;
    testPlayer->SetBankTotal(playerBank);
    priorBank = testPlayer->GetBankTotal();
    // Both players have blackjack
    for (int i = 9; i <= 12; i++) {
        testCard = std::make_shared<Card>(Ranks[0], Suits[3]);
        testNode = testShoe->GetCardsInShoe()->InitNode(testCard);
        testShoe->GetCardsInShoe()->AppendNode(testNode);
        testCard = std::make_shared<Card>(Ranks[0], Suits[2]);
        testNode = testShoe->GetCardsInShoe()->InitNode(testCard);
        testShoe->GetCardsInShoe()->AppendNode(testNode);
        testCard = std::make_shared<Card>(Ranks[i], Suits[1]);
        testNode = testShoe->GetCardsInShoe()->InitNode(testCard);
        testShoe->GetCardsInShoe()->AppendNode(testNode);
        testCard = std::make_shared<Card>(Ranks[i], Suits[0]);
        testNode = testShoe->GetCardsInShoe()->InitNode(testCard);
        testShoe->GetCardsInShoe()->AppendNode(testNode);
        EXPECT_EQ(testPlayer->GetBankTotal(), priorBank);
        copyShoe->CopyShoe(testShoe);
        // Player can buy insurance
        {
            // Player chose to buy insurance
            {
                auto result = blackjack_check_sim(testPlayer, testDealer, testShoe, playerWager, true);
                EXPECT_EQ(testPlayer->GetTotalHandWagers()->RetrieveNode(0)->data, playerWager + testPlayer->GetCurrentHands()->RetrieveNode(0)->data->GetInsuranceWager());
                EXPECT_EQ(testPlayer->GetCurrentHands()->RetrieveNode(0)->data->GetInsuranceWager(), 0.5 * playerWager);
                EXPECT_EQ(testPlayer->GetCurrentHands()->RetrieveNode(0)->data->GetNet(), playerWager);
                EXPECT_EQ(testPlayer->GetBankTotal(), priorBank + testPlayer->GetCurrentHands()->RetrieveNode(0)->data->GetNet());
                EXPECT_FALSE(result);
                testPlayer->SetBankTotal(priorBank);
                testPlayer->GetCurrentHands()->ClearList();
                testPlayer->GetTotalHandBankTotals()->ClearList();
                testPlayer->GetTotalHandCardTotals()->ClearList();
                testPlayer->GetTotalHandNets()->ClearList();
                testPlayer->GetTotalHandsPlayed()->ClearList();
                testPlayer->GetTotalHandWagers()->ClearList();
                testDealer->GetCurrentHands()->ClearList();
            }
            // Player chose to not buy insurance
            testShoe->CopyShoe(copyShoe);
            {
                auto result = blackjack_check_sim(testPlayer, testDealer, testShoe, playerWager, false);
                EXPECT_EQ(testPlayer->GetTotalHandWagers()->RetrieveNode(0)->data, playerWager);
                EXPECT_EQ(testPlayer->GetCurrentHands()->RetrieveNode(0)->data->GetInsuranceWager(), 0);
                EXPECT_EQ(testPlayer->GetCurrentHands()->RetrieveNode(0)->data->GetNet(), 0);
                EXPECT_EQ(testPlayer->GetBankTotal(), priorBank + testPlayer->GetCurrentHands()->RetrieveNode(0)->data->GetNet());
                EXPECT_FALSE(result);
                testPlayer->SetBankTotal(priorBank);
                testPlayer->GetCurrentHands()->ClearList();
                testDealer->GetCurrentHands()->ClearList();
                testPlayer->SetBankTotal(priorBank);
                testPlayer->GetCurrentHands()->ClearList();
                testPlayer->GetTotalHandBankTotals()->ClearList();
                testPlayer->GetTotalHandCardTotals()->ClearList();
                testPlayer->GetTotalHandNets()->ClearList();
                testPlayer->GetTotalHandsPlayed()->ClearList();
                testPlayer->GetTotalHandWagers()->ClearList();
                testDealer->GetCurrentHands()->ClearList();
            }
            testShoe->GetCardsInShoe()->ClearList();
        }
        // Player cannot buy insurance
        {
            // Testing with true
            {
                playerWager = 70;
                while (playerWager <= priorBank) {
                    testShoe->CopyShoe(copyShoe);
                    auto result = blackjack_check_sim(testPlayer, testDealer, testShoe, playerWager, true);
                    EXPECT_EQ(testPlayer->GetCurrentHands()->RetrieveNode(0)->data->GetWager(), playerWager);
                    EXPECT_EQ(testPlayer->GetCurrentHands()->RetrieveNode(0)->data->GetInsuranceWager(), 0);
                    EXPECT_EQ(testPlayer->GetCurrentHands()->RetrieveNode(0)->data->GetNet(), 0);
                    EXPECT_EQ(testPlayer->GetBankTotal(), priorBank + testPlayer->GetCurrentHands()->RetrieveNode(0)->data->GetNet());
                    EXPECT_FALSE(result);
                    testPlayer->SetBankTotal(priorBank);
                    testPlayer->GetCurrentHands()->ClearList();
                    testDealer->GetCurrentHands()->ClearList();
                    testPlayer->GetTotalHandBankTotals()->ClearList();
                    testPlayer->GetTotalHandCardTotals()->ClearList();
                    testPlayer->GetTotalHandNets()->ClearList();
                    testPlayer->GetTotalHandsPlayed()->ClearList();
                    testPlayer->GetTotalHandWagers()->ClearList();
                    testShoe->GetCardsInShoe()->ClearList();
                    playerWager++;
                }
            }
            // Testing with false
            {
                playerWager = 70;
                while (playerWager <= priorBank) {
                    testShoe->CopyShoe(copyShoe);
                    auto result = blackjack_check_sim(testPlayer, testDealer, testShoe, playerWager, false);
                    EXPECT_EQ(testPlayer->GetCurrentHands()->RetrieveNode(0)->data->GetWager(), playerWager);
                    EXPECT_EQ(testPlayer->GetCurrentHands()->RetrieveNode(0)->data->GetInsuranceWager(), 0);
                    EXPECT_EQ(testPlayer->GetCurrentHands()->RetrieveNode(0)->data->GetNet(), 0);
                    EXPECT_EQ(testPlayer->GetBankTotal(), priorBank + testPlayer->GetCurrentHands()->RetrieveNode(0)->data->GetNet());
                    EXPECT_FALSE(result);
                    testPlayer->SetBankTotal(priorBank);
                    testPlayer->GetCurrentHands()->ClearList();
                    testDealer->GetCurrentHands()->ClearList();
                    testPlayer->GetTotalHandBankTotals()->ClearList();
                    testPlayer->GetTotalHandCardTotals()->ClearList();
                    testPlayer->GetTotalHandNets()->ClearList();
                    testPlayer->GetTotalHandsPlayed()->ClearList();
                    testPlayer->GetTotalHandWagers()->ClearList();
                    testShoe->GetCardsInShoe()->ClearList();
                    playerWager++;
                }
            }
        }
        playerWager = 10;
    }
    testShoe->GetCardsInShoe()->ClearList();
    // Dealer has blackjack, player does not
    for (int i = 9; i <= 12; i++) {
        testCard = std::make_shared<Card>(Ranks[0], Suits[3]);
        testNode = testShoe->GetCardsInShoe()->InitNode(testCard);
        testShoe->GetCardsInShoe()->AppendNode(testNode);
        testCard = std::make_shared<Card>(Ranks[0], Suits[2]);
        testNode = testShoe->GetCardsInShoe()->InitNode(testCard);
        testShoe->GetCardsInShoe()->AppendNode(testNode);
        testCard = std::make_shared<Card>(Ranks[i], Suits[1]);
        testNode = testShoe->GetCardsInShoe()->InitNode(testCard);
        testShoe->GetCardsInShoe()->AppendNode(testNode);
        testCard = std::make_shared<Card>(Ranks[8], Suits[0]);
        testNode = testShoe->GetCardsInShoe()->InitNode(testCard);
        testShoe->GetCardsInShoe()->AppendNode(testNode);
        EXPECT_EQ(testPlayer->GetBankTotal(), priorBank);
        copyShoe->CopyShoe(testShoe);
        // Player can buy insurance
        {
            // Player chose to buy insurance
            {
                auto result = blackjack_check_sim(testPlayer, testDealer, testShoe, playerWager, true);
                EXPECT_EQ(testPlayer->GetTotalHandWagers()->RetrieveNode(0)->data, playerWager + testPlayer->GetCurrentHands()->RetrieveNode(0)->data->GetInsuranceWager());
                EXPECT_EQ(testPlayer->GetCurrentHands()->RetrieveNode(0)->data->GetInsuranceWager(), 0.5 * playerWager);
                EXPECT_EQ(testPlayer->GetCurrentHands()->RetrieveNode(0)->data->GetNet(), 0);
                EXPECT_EQ(testPlayer->GetBankTotal(), priorBank + testPlayer->GetCurrentHands()->RetrieveNode(0)->data->GetNet());
                EXPECT_FALSE(result);
                testPlayer->SetBankTotal(priorBank);
                testPlayer->GetCurrentHands()->ClearList();
                testPlayer->GetTotalHandBankTotals()->ClearList();
                testPlayer->GetTotalHandCardTotals()->ClearList();
                testPlayer->GetTotalHandNets()->ClearList();
                testPlayer->GetTotalHandsPlayed()->ClearList();
                testPlayer->GetTotalHandWagers()->ClearList();
                testDealer->GetCurrentHands()->ClearList();
            }
            // Player chose to not buy insurance
            testShoe->CopyShoe(copyShoe);
            {
                auto result = blackjack_check_sim(testPlayer, testDealer, testShoe, playerWager, false);
                EXPECT_EQ(testPlayer->GetTotalHandWagers()->RetrieveNode(0)->data, playerWager + testPlayer->GetCurrentHands()->RetrieveNode(0)->data->GetInsuranceWager());
                EXPECT_EQ(testPlayer->GetCurrentHands()->RetrieveNode(0)->data->GetInsuranceWager(), 0);
                EXPECT_EQ(testPlayer->GetCurrentHands()->RetrieveNode(0)->data->GetNet(), -testPlayer->GetCurrentHands()->RetrieveNode(0)->data->GetWager());
                EXPECT_EQ(testPlayer->GetBankTotal(), priorBank + testPlayer->GetCurrentHands()->RetrieveNode(0)->data->GetNet());
                EXPECT_FALSE(result);
                testPlayer->SetBankTotal(priorBank);
                testPlayer->GetCurrentHands()->ClearList();
                testPlayer->GetTotalHandBankTotals()->ClearList();
                testPlayer->GetTotalHandCardTotals()->ClearList();
                testPlayer->GetTotalHandNets()->ClearList();
                testPlayer->GetTotalHandsPlayed()->ClearList();
                testPlayer->GetTotalHandWagers()->ClearList();
                testDealer->GetCurrentHands()->ClearList();
            }
            testShoe->GetCardsInShoe()->ClearList();
        }
        // Player cannot buy insurance
        {
            // Testing with true
            {
                playerWager = 70;
                while (playerWager <= priorBank) {
                    testShoe->CopyShoe(copyShoe);
                    auto result = blackjack_check_sim(testPlayer, testDealer, testShoe, playerWager, true);
                    EXPECT_EQ(testPlayer->GetTotalHandWagers()->RetrieveNode(0)->data, playerWager + testPlayer->GetCurrentHands()->RetrieveNode(0)->data->GetInsuranceWager());
                    EXPECT_EQ(testPlayer->GetCurrentHands()->RetrieveNode(0)->data->GetInsuranceWager(), 0);
                    EXPECT_EQ(testPlayer->GetCurrentHands()->RetrieveNode(0)->data->GetNet(), -testPlayer->GetCurrentHands()->RetrieveNode(0)->data->GetWager());
                    EXPECT_EQ(testPlayer->GetBankTotal(), priorBank + testPlayer->GetCurrentHands()->RetrieveNode(0)->data->GetNet());
                    EXPECT_FALSE(result);
                    testPlayer->SetBankTotal(priorBank);
                    testPlayer->GetCurrentHands()->ClearList();
                    testPlayer->GetTotalHandBankTotals()->ClearList();
                    testPlayer->GetTotalHandCardTotals()->ClearList();
                    testPlayer->GetTotalHandNets()->ClearList();
                    testPlayer->GetTotalHandsPlayed()->ClearList();
                    testPlayer->GetTotalHandWagers()->ClearList();
                    testDealer->GetCurrentHands()->ClearList();
                    playerWager++;
                    testShoe->GetCardsInShoe()->ClearList();
                }
            }
            // Testing with false
            {
                playerWager = 70;
                while (playerWager <= priorBank) {
                    testShoe->CopyShoe(copyShoe);
                    auto result = blackjack_check_sim(testPlayer, testDealer, testShoe, playerWager, false);
                    EXPECT_EQ(testPlayer->GetTotalHandWagers()->RetrieveNode(0)->data, playerWager + testPlayer->GetCurrentHands()->RetrieveNode(0)->data->GetInsuranceWager());
                    EXPECT_EQ(testPlayer->GetCurrentHands()->RetrieveNode(0)->data->GetInsuranceWager(), 0);
                    EXPECT_EQ(testPlayer->GetCurrentHands()->RetrieveNode(0)->data->GetNet(), -testPlayer->GetCurrentHands()->RetrieveNode(0)->data->GetWager());
                    EXPECT_EQ(testPlayer->GetBankTotal(), priorBank + testPlayer->GetCurrentHands()->RetrieveNode(0)->data->GetNet());
                    EXPECT_FALSE(result);
                    testPlayer->SetBankTotal(priorBank);
                    testPlayer->GetCurrentHands()->ClearList();
                    testPlayer->GetTotalHandBankTotals()->ClearList();
                    testPlayer->GetTotalHandCardTotals()->ClearList();
                    testPlayer->GetTotalHandNets()->ClearList();
                    testPlayer->GetTotalHandsPlayed()->ClearList();
                    testPlayer->GetTotalHandWagers()->ClearList();
                    testDealer->GetCurrentHands()->ClearList();
                    playerWager++;
                    testShoe->GetCardsInShoe()->ClearList();
                }
            }
        }
        playerWager = 10;
    }
    testShoe->GetCardsInShoe()->ClearList();
    // Player has blackjack, dealer does not
    for (int i = 9; i <= 12; i++) {
        testCard = std::make_shared<Card>(Ranks[0], Suits[3]);
        testNode = testShoe->GetCardsInShoe()->InitNode(testCard);
        testShoe->GetCardsInShoe()->AppendNode(testNode);
        testCard = std::make_shared<Card>(Ranks[0], Suits[2]);
        testNode = testShoe->GetCardsInShoe()->InitNode(testCard);
        testShoe->GetCardsInShoe()->AppendNode(testNode);
        testCard = std::make_shared<Card>(Ranks[8], Suits[1]);
        testNode = testShoe->GetCardsInShoe()->InitNode(testCard);
        testShoe->GetCardsInShoe()->AppendNode(testNode);
        testCard = std::make_shared<Card>(Ranks[i], Suits[0]);
        testNode = testShoe->GetCardsInShoe()->InitNode(testCard);
        testShoe->GetCardsInShoe()->AppendNode(testNode);
        EXPECT_EQ(testPlayer->GetBankTotal(), priorBank);
        copyShoe->CopyShoe(testShoe);
        // Player can buy insurance
        {
            // Player chose to buy insurance
            {
                auto result = blackjack_check_sim(testPlayer, testDealer, testShoe, playerWager, true);
                EXPECT_EQ(testPlayer->GetTotalHandWagers()->RetrieveNode(0)->data, playerWager + testPlayer->GetCurrentHands()->RetrieveNode(0)->data->GetInsuranceWager());
                EXPECT_EQ(testPlayer->GetCurrentHands()->RetrieveNode(0)->data->GetInsuranceWager(), 0.5 * playerWager);
                EXPECT_EQ(testPlayer->GetCurrentHands()->RetrieveNode(0)->data->GetNet(), testPlayer->GetCurrentHands()->RetrieveNode(0)->data->GetWager() - testPlayer->GetCurrentHands()->RetrieveNode(0)->data->GetInsuranceWager());
                EXPECT_EQ(testPlayer->GetBankTotal(), priorBank + testPlayer->GetCurrentHands()->RetrieveNode(0)->data->GetNet());
                EXPECT_FALSE(result);
                testPlayer->SetBankTotal(priorBank);
                testPlayer->GetCurrentHands()->ClearList();
                testPlayer->GetTotalHandBankTotals()->ClearList();
                testPlayer->GetTotalHandCardTotals()->ClearList();
                testPlayer->GetTotalHandNets()->ClearList();
                testPlayer->GetTotalHandsPlayed()->ClearList();
                testPlayer->GetTotalHandWagers()->ClearList();
                testDealer->GetCurrentHands()->ClearList();
            }
            // Player chose to not buy insurance
            testShoe->CopyShoe(copyShoe);
            {
                auto result = blackjack_check_sim(testPlayer, testDealer, testShoe, playerWager, false);
                EXPECT_EQ(testPlayer->GetTotalHandWagers()->RetrieveNode(0)->data, playerWager + testPlayer->GetCurrentHands()->RetrieveNode(0)->data->GetInsuranceWager());
                EXPECT_EQ(testPlayer->GetCurrentHands()->RetrieveNode(0)->data->GetInsuranceWager(), 0);
                EXPECT_EQ(testPlayer->GetCurrentHands()->RetrieveNode(0)->data->GetNet(), 1.5 * testPlayer->GetCurrentHands()->RetrieveNode(0)->data->GetWager());
                EXPECT_EQ(testPlayer->GetBankTotal(), priorBank + testPlayer->GetCurrentHands()->RetrieveNode(0)->data->GetNet());
                EXPECT_FALSE(result);
                testPlayer->SetBankTotal(priorBank);
                testPlayer->GetCurrentHands()->ClearList();
                testPlayer->GetTotalHandBankTotals()->ClearList();
                testPlayer->GetTotalHandCardTotals()->ClearList();
                testPlayer->GetTotalHandNets()->ClearList();
                testPlayer->GetTotalHandsPlayed()->ClearList();
                testPlayer->GetTotalHandWagers()->ClearList();
                testDealer->GetCurrentHands()->ClearList();
            }
            testShoe->GetCardsInShoe()->ClearList();
        }
        // Player cannot buy insurance
        {
            // Testing with true
            {
                playerWager = 70;
                while (playerWager <= priorBank) {
                    testShoe->CopyShoe(copyShoe);
                    auto result = blackjack_check_sim(testPlayer, testDealer, testShoe, playerWager, true);
                    EXPECT_EQ(testPlayer->GetTotalHandWagers()->RetrieveNode(0)->data, playerWager + testPlayer->GetCurrentHands()->RetrieveNode(0)->data->GetInsuranceWager());
                    EXPECT_EQ(testPlayer->GetCurrentHands()->RetrieveNode(0)->data->GetInsuranceWager(), 0);
                    EXPECT_EQ(testPlayer->GetCurrentHands()->RetrieveNode(0)->data->GetNet(), 1.5 * testPlayer->GetCurrentHands()->RetrieveNode(0)->data->GetWager());
                    EXPECT_EQ(testPlayer->GetBankTotal(), priorBank + testPlayer->GetCurrentHands()->RetrieveNode(0)->data->GetNet());
                    EXPECT_FALSE(result);
                    testPlayer->SetBankTotal(priorBank);
                    testPlayer->GetCurrentHands()->ClearList();
                    testPlayer->GetTotalHandBankTotals()->ClearList();
                    testPlayer->GetTotalHandCardTotals()->ClearList();
                    testPlayer->GetTotalHandNets()->ClearList();
                    testPlayer->GetTotalHandsPlayed()->ClearList();
                    testPlayer->GetTotalHandWagers()->ClearList();
                    testDealer->GetCurrentHands()->ClearList();
                    playerWager++;
                    testShoe->GetCardsInShoe()->ClearList();
                }
            }
            // Testing with false
            {
                playerWager = 70;
                while (playerWager <= priorBank) {
                    testShoe->CopyShoe(copyShoe);
                    auto result = blackjack_check_sim(testPlayer, testDealer, testShoe, playerWager, false);
                    EXPECT_EQ(testPlayer->GetTotalHandWagers()->RetrieveNode(0)->data, playerWager + testPlayer->GetCurrentHands()->RetrieveNode(0)->data->GetInsuranceWager());
                    EXPECT_EQ(testPlayer->GetCurrentHands()->RetrieveNode(0)->data->GetInsuranceWager(), 0);
                    EXPECT_EQ(testPlayer->GetCurrentHands()->RetrieveNode(0)->data->GetNet(), 1.5 * testPlayer->GetCurrentHands()->RetrieveNode(0)->data->GetWager());
                    EXPECT_EQ(testPlayer->GetBankTotal(), priorBank + testPlayer->GetCurrentHands()->RetrieveNode(0)->data->GetNet());
                    EXPECT_FALSE(result);
                    testPlayer->SetBankTotal(priorBank);
                    testPlayer->GetCurrentHands()->ClearList();
                    testPlayer->GetTotalHandBankTotals()->ClearList();
                    testPlayer->GetTotalHandCardTotals()->ClearList();
                    testPlayer->GetTotalHandNets()->ClearList();
                    testPlayer->GetTotalHandsPlayed()->ClearList();
                    testPlayer->GetTotalHandWagers()->ClearList();
                    testDealer->GetCurrentHands()->ClearList();
                    playerWager++;
                    testShoe->GetCardsInShoe()->ClearList();
                }
            }
        }
        playerWager = 10;
    }
    testShoe->GetCardsInShoe()->ClearList();
    // Neither player has blackjack
    for (int i = 0; i <= 8; i++) {
        testCard = std::make_shared<Card>(Ranks[0], Suits[3]);
        testNode = testShoe->GetCardsInShoe()->InitNode(testCard);
        testShoe->GetCardsInShoe()->AppendNode(testNode);
        testCard = std::make_shared<Card>(Ranks[0], Suits[2]);
        testNode = testShoe->GetCardsInShoe()->InitNode(testCard);
        testShoe->GetCardsInShoe()->AppendNode(testNode);
        testCard = std::make_shared<Card>(Ranks[i], Suits[1]);
        testNode = testShoe->GetCardsInShoe()->InitNode(testCard);
        testShoe->GetCardsInShoe()->AppendNode(testNode);
        testCard = std::make_shared<Card>(Ranks[i], Suits[0]);
        testNode = testShoe->GetCardsInShoe()->InitNode(testCard);
        testShoe->GetCardsInShoe()->AppendNode(testNode);
        EXPECT_EQ(testPlayer->GetBankTotal(), priorBank);
        copyShoe->CopyShoe(testShoe);
        // Player can buy insurance
        {
            // Player chose to buy insurance
            {
                auto result = blackjack_check_sim(testPlayer, testDealer, testShoe, playerWager, true);
                EXPECT_EQ(testPlayer->GetCurrentHands()->RetrieveNode(0)->data->GetWager(), playerWager);
                EXPECT_EQ(testPlayer->GetCurrentHands()->RetrieveNode(0)->data->GetInsuranceWager(), 0.5 * playerWager);
                EXPECT_TRUE(result);
                testPlayer->SetBankTotal(priorBank);
                testPlayer->GetCurrentHands()->ClearList();
                testPlayer->GetTotalHandBankTotals()->ClearList();
                testPlayer->GetTotalHandCardTotals()->ClearList();
                testPlayer->GetTotalHandNets()->ClearList();
                testPlayer->GetTotalHandsPlayed()->ClearList();
                testPlayer->GetTotalHandWagers()->ClearList();
                testDealer->GetCurrentHands()->ClearList();
            }
            // Player chose to not buy insurance
            testShoe->CopyShoe(copyShoe);
            {
                auto result = blackjack_check_sim(testPlayer, testDealer, testShoe, playerWager, false);
                EXPECT_EQ(testPlayer->GetCurrentHands()->RetrieveNode(0)->data->GetWager(), playerWager);
                EXPECT_EQ(testPlayer->GetCurrentHands()->RetrieveNode(0)->data->GetInsuranceWager(), 0);
                EXPECT_TRUE(result);
                testPlayer->SetBankTotal(priorBank);
                testPlayer->GetCurrentHands()->ClearList();
                testPlayer->GetTotalHandBankTotals()->ClearList();
                testPlayer->GetTotalHandCardTotals()->ClearList();
                testPlayer->GetTotalHandNets()->ClearList();
                testPlayer->GetTotalHandsPlayed()->ClearList();
                testPlayer->GetTotalHandWagers()->ClearList();
                testDealer->GetCurrentHands()->ClearList();
            }
            testShoe->GetCardsInShoe()->ClearList();
        }
        // Player cannot buy insurance
        {
            // Testing with true
            {
                playerWager = 70;
                while (playerWager <= priorBank) {
                    testShoe->CopyShoe(copyShoe);
                    auto result = blackjack_check_sim(testPlayer, testDealer, testShoe, playerWager, true);
                    EXPECT_EQ(testPlayer->GetCurrentHands()->RetrieveNode(0)->data->GetWager(), playerWager);
                    EXPECT_EQ(testPlayer->GetCurrentHands()->RetrieveNode(0)->data->GetInsuranceWager(), 0);
                    EXPECT_TRUE(result);
                    testPlayer->SetBankTotal(priorBank);
                    testPlayer->GetCurrentHands()->ClearList();
                    testPlayer->GetTotalHandBankTotals()->ClearList();
                    testPlayer->GetTotalHandCardTotals()->ClearList();
                    testPlayer->GetTotalHandNets()->ClearList();
                    testPlayer->GetTotalHandsPlayed()->ClearList();
                    testPlayer->GetTotalHandWagers()->ClearList();
                    testDealer->GetCurrentHands()->ClearList();
                    playerWager++;
                    testShoe->GetCardsInShoe()->ClearList();
                }
            }
            // Testing with false
            {
                playerWager = 70;
                while (playerWager <= priorBank) {
                    testShoe->CopyShoe(copyShoe);
                    auto result = blackjack_check_sim(testPlayer, testDealer, testShoe, playerWager, false);
                    EXPECT_EQ(testPlayer->GetCurrentHands()->RetrieveNode(0)->data->GetWager(), playerWager);
                    EXPECT_EQ(testPlayer->GetCurrentHands()->RetrieveNode(0)->data->GetInsuranceWager(), 0);
                    EXPECT_TRUE(result);
                    testPlayer->SetBankTotal(priorBank);
                    testPlayer->GetCurrentHands()->ClearList();
                    testPlayer->GetTotalHandBankTotals()->ClearList();
                    testPlayer->GetTotalHandCardTotals()->ClearList();
                    testPlayer->GetTotalHandNets()->ClearList();
                    testPlayer->GetTotalHandsPlayed()->ClearList();
                    testPlayer->GetTotalHandWagers()->ClearList();
                    testDealer->GetCurrentHands()->ClearList();
                    playerWager++;
                    testShoe->GetCardsInShoe()->ClearList();
                }
            }
        }
        playerWager = 10;
    }
    testShoe->GetCardsInShoe()->ClearList();
    // Dealer is not showing an Ace, player cannot buy insurance no matter what
    // Both players have blackjack
    for (int i = 9; i <= 12; i++) {
        testCard = std::make_shared<Card>(Ranks[i], Suits[3]);
        testNode = testShoe->GetCardsInShoe()->InitNode(testCard);
        testShoe->GetCardsInShoe()->AppendNode(testNode);
        testCard = std::make_shared<Card>(Ranks[0], Suits[2]);
        testNode = testShoe->GetCardsInShoe()->InitNode(testCard);
        testShoe->GetCardsInShoe()->AppendNode(testNode);
        testCard = std::make_shared<Card>(Ranks[0], Suits[1]);
        testNode = testShoe->GetCardsInShoe()->InitNode(testCard);
        testShoe->GetCardsInShoe()->AppendNode(testNode);
        testCard = std::make_shared<Card>(Ranks[i], Suits[0]);
        testNode = testShoe->GetCardsInShoe()->InitNode(testCard);
        testShoe->GetCardsInShoe()->AppendNode(testNode);
        EXPECT_EQ(testPlayer->GetBankTotal(), priorBank);
        copyShoe->CopyShoe(testShoe);
        // Player cannot buy insurance
        {
            // Testing with true
            {
                playerWager = 10;
                while (playerWager <= priorBank) {
                    testShoe->CopyShoe(copyShoe);
                    auto result = blackjack_check_sim(testPlayer, testDealer, testShoe, playerWager, true);
                    EXPECT_EQ(testPlayer->GetCurrentHands()->RetrieveNode(0)->data->GetWager(), playerWager);
                    EXPECT_EQ(testPlayer->GetCurrentHands()->RetrieveNode(0)->data->GetInsuranceWager(), 0);
                    EXPECT_EQ(testPlayer->GetCurrentHands()->RetrieveNode(0)->data->GetNet(), 0);
                    EXPECT_FALSE(result);
                    testPlayer->SetBankTotal(priorBank);
                    testPlayer->GetCurrentHands()->ClearList();
                    testPlayer->GetTotalHandBankTotals()->ClearList();
                    testPlayer->GetTotalHandCardTotals()->ClearList();
                    testPlayer->GetTotalHandNets()->ClearList();
                    testPlayer->GetTotalHandsPlayed()->ClearList();
                    testPlayer->GetTotalHandWagers()->ClearList();
                    testDealer->GetCurrentHands()->ClearList();
                    playerWager++;
                    testShoe->GetCardsInShoe()->ClearList();
                }
            }
            // Testing with false
            {
                playerWager = 10;
                while (playerWager <= priorBank) {
                    testShoe->CopyShoe(copyShoe);
                    auto result = blackjack_check_sim(testPlayer, testDealer, testShoe, playerWager, false);
                    EXPECT_EQ(testPlayer->GetCurrentHands()->RetrieveNode(0)->data->GetWager(), playerWager);
                    EXPECT_EQ(testPlayer->GetCurrentHands()->RetrieveNode(0)->data->GetInsuranceWager(), 0);
                    EXPECT_EQ(testPlayer->GetCurrentHands()->RetrieveNode(0)->data->GetNet(), 0);
                    EXPECT_FALSE(result);
                    testPlayer->SetBankTotal(priorBank);
                    testPlayer->GetCurrentHands()->ClearList();
                    testPlayer->GetTotalHandBankTotals()->ClearList();
                    testPlayer->GetTotalHandCardTotals()->ClearList();
                    testPlayer->GetTotalHandNets()->ClearList();
                    testPlayer->GetTotalHandsPlayed()->ClearList();
                    testPlayer->GetTotalHandWagers()->ClearList();
                    testDealer->GetCurrentHands()->ClearList();
                    playerWager++;
                    testShoe->GetCardsInShoe()->ClearList();
                }
            }
        }
        playerWager = 10;
    }
    testShoe->GetCardsInShoe()->ClearList();
    // Dealer has blackjack, player does not
    for (int i = 9; i <= 12; i++) {
        testCard = std::make_shared<Card>(Ranks[i], Suits[3]);
        testNode = testShoe->GetCardsInShoe()->InitNode(testCard);
        testShoe->GetCardsInShoe()->AppendNode(testNode);
        testCard = std::make_shared<Card>(Ranks[1], Suits[2]);
        testNode = testShoe->GetCardsInShoe()->InitNode(testCard);
        testShoe->GetCardsInShoe()->AppendNode(testNode);
        testCard = std::make_shared<Card>(Ranks[0], Suits[1]);
        testNode = testShoe->GetCardsInShoe()->InitNode(testCard);
        testShoe->GetCardsInShoe()->AppendNode(testNode);
        testCard = std::make_shared<Card>(Ranks[i], Suits[0]);
        testNode = testShoe->GetCardsInShoe()->InitNode(testCard);
        testShoe->GetCardsInShoe()->AppendNode(testNode);
        EXPECT_EQ(testPlayer->GetBankTotal(), priorBank);
        copyShoe->CopyShoe(testShoe);
        // Player cannot buy insurance
        {
            // Testing with true
            {
                playerWager = 10;
                while (playerWager <= priorBank) {
                    testShoe->CopyShoe(copyShoe);
                    auto result = blackjack_check_sim(testPlayer, testDealer, testShoe, playerWager, true);
                    EXPECT_EQ(testPlayer->GetCurrentHands()->RetrieveNode(0)->data->GetWager(), playerWager);
                    EXPECT_EQ(testPlayer->GetCurrentHands()->RetrieveNode(0)->data->GetInsuranceWager(), 0);
                    EXPECT_EQ(testPlayer->GetCurrentHands()->RetrieveNode(0)->data->GetNet(), -testPlayer->GetCurrentHands()->RetrieveNode(0)->data->GetWager());
                    EXPECT_FALSE(result);
                    testPlayer->SetBankTotal(priorBank);
                    testPlayer->GetCurrentHands()->ClearList();
                    testPlayer->GetTotalHandBankTotals()->ClearList();
                    testPlayer->GetTotalHandCardTotals()->ClearList();
                    testPlayer->GetTotalHandNets()->ClearList();
                    testPlayer->GetTotalHandsPlayed()->ClearList();
                    testPlayer->GetTotalHandWagers()->ClearList();
                    testDealer->GetCurrentHands()->ClearList();
                    playerWager++;
                    testShoe->GetCardsInShoe()->ClearList();
                }
            }
            // Testing with false
            {
                playerWager = 10;
                while (playerWager <= priorBank) {
                    testShoe->CopyShoe(copyShoe);
                    auto result = blackjack_check_sim(testPlayer, testDealer, testShoe, playerWager, false);
                    EXPECT_EQ(testPlayer->GetCurrentHands()->RetrieveNode(0)->data->GetWager(), playerWager);
                    EXPECT_EQ(testPlayer->GetCurrentHands()->RetrieveNode(0)->data->GetInsuranceWager(), 0);
                    EXPECT_EQ(testPlayer->GetCurrentHands()->RetrieveNode(0)->data->GetNet(), -testPlayer->GetCurrentHands()->RetrieveNode(0)->data->GetWager());
                    EXPECT_FALSE(result);
                    testPlayer->SetBankTotal(priorBank);
                    testPlayer->GetCurrentHands()->ClearList();
                    testPlayer->GetTotalHandBankTotals()->ClearList();
                    testPlayer->GetTotalHandCardTotals()->ClearList();
                    testPlayer->GetTotalHandNets()->ClearList();
                    testPlayer->GetTotalHandsPlayed()->ClearList();
                    testPlayer->GetTotalHandWagers()->ClearList();
                    testDealer->GetCurrentHands()->ClearList();
                    playerWager++;
                    testShoe->GetCardsInShoe()->ClearList();
                }
            }
        }
        playerWager = 10;
    }
    testShoe->GetCardsInShoe()->ClearList();
    // Player has blackjack, dealer does not
    for (int i = 9; i <= 12; i++) {
        testCard = std::make_shared<Card>(Ranks[8], Suits[3]);
        testNode = testShoe->GetCardsInShoe()->InitNode(testCard);
        testShoe->GetCardsInShoe()->AppendNode(testNode);
        testCard = std::make_shared<Card>(Ranks[i], Suits[2]);
        testNode = testShoe->GetCardsInShoe()->InitNode(testCard);
        testShoe->GetCardsInShoe()->AppendNode(testNode);
        testCard = std::make_shared<Card>(Ranks[0], Suits[1]);
        testNode = testShoe->GetCardsInShoe()->InitNode(testCard);
        testShoe->GetCardsInShoe()->AppendNode(testNode);
        testCard = std::make_shared<Card>(Ranks[0], Suits[0]);
        testNode = testShoe->GetCardsInShoe()->InitNode(testCard);
        testShoe->GetCardsInShoe()->AppendNode(testNode);
        EXPECT_EQ(testPlayer->GetBankTotal(), priorBank);
        copyShoe->CopyShoe(testShoe);
        // Player cannot buy insurance
        {
            // Testing with true
            {
                playerWager = 10;
                while (playerWager <= priorBank) {
                    testShoe->CopyShoe(copyShoe);
                    auto result = blackjack_check_sim(testPlayer, testDealer, testShoe, playerWager, true);
                    EXPECT_EQ(testPlayer->GetCurrentHands()->RetrieveNode(0)->data->GetWager(), playerWager);
                    EXPECT_EQ(testPlayer->GetCurrentHands()->RetrieveNode(0)->data->GetInsuranceWager(), 0);
                    EXPECT_EQ(testPlayer->GetCurrentHands()->RetrieveNode(0)->data->GetNet(), 1.5 * testPlayer->GetCurrentHands()->RetrieveNode(0)->data->GetWager());
                    EXPECT_FALSE(result);
                    testPlayer->SetBankTotal(priorBank);
                    testPlayer->GetCurrentHands()->ClearList();
                    testPlayer->GetTotalHandBankTotals()->ClearList();
                    testPlayer->GetTotalHandCardTotals()->ClearList();
                    testPlayer->GetTotalHandNets()->ClearList();
                    testPlayer->GetTotalHandsPlayed()->ClearList();
                    testPlayer->GetTotalHandWagers()->ClearList();
                    testDealer->GetCurrentHands()->ClearList();
                    playerWager++;
                    testShoe->GetCardsInShoe()->ClearList();
                }
            }
            // Testing with false
            {
                playerWager = 10;
                while (playerWager <= priorBank) {
                    testShoe->CopyShoe(copyShoe);
                    auto result = blackjack_check_sim(testPlayer, testDealer, testShoe, playerWager, false);
                    EXPECT_EQ(testPlayer->GetCurrentHands()->RetrieveNode(0)->data->GetWager(), playerWager);
                    EXPECT_EQ(testPlayer->GetCurrentHands()->RetrieveNode(0)->data->GetInsuranceWager(), 0);
                    EXPECT_EQ(testPlayer->GetCurrentHands()->RetrieveNode(0)->data->GetNet(), 1.5 * testPlayer->GetCurrentHands()->RetrieveNode(0)->data->GetWager());
                    EXPECT_FALSE(result);
                    testPlayer->SetBankTotal(priorBank);
                    testPlayer->GetCurrentHands()->ClearList();
                    testPlayer->GetTotalHandBankTotals()->ClearList();
                    testPlayer->GetTotalHandCardTotals()->ClearList();
                    testPlayer->GetTotalHandNets()->ClearList();
                    testPlayer->GetTotalHandsPlayed()->ClearList();
                    testPlayer->GetTotalHandWagers()->ClearList();
                    testDealer->GetCurrentHands()->ClearList();
                    playerWager++;
                    testShoe->GetCardsInShoe()->ClearList();
                }
            }
        }
        playerWager = 10;
    }
    testShoe->GetCardsInShoe()->ClearList();
    // Neither player has blackjack
    for (int i = 9; i <= 12; i++) {
        testCard = std::make_shared<Card>(Ranks[1], Suits[3]);
        testNode = testShoe->GetCardsInShoe()->InitNode(testCard);
        testShoe->GetCardsInShoe()->AppendNode(testNode);
        testCard = std::make_shared<Card>(Ranks[1], Suits[2]);
        testNode = testShoe->GetCardsInShoe()->InitNode(testCard);
        testShoe->GetCardsInShoe()->AppendNode(testNode);
        testCard = std::make_shared<Card>(Ranks[i], Suits[1]);
        testNode = testShoe->GetCardsInShoe()->InitNode(testCard);
        testShoe->GetCardsInShoe()->AppendNode(testNode);
        testCard = std::make_shared<Card>(Ranks[i], Suits[0]);
        testNode = testShoe->GetCardsInShoe()->InitNode(testCard);
        testShoe->GetCardsInShoe()->AppendNode(testNode);
        EXPECT_EQ(testPlayer->GetBankTotal(), priorBank);
        copyShoe->CopyShoe(testShoe);
        // Player cannot buy insurance
        {
            // Testing with true
            {
                playerWager = 10;
                while (playerWager <= priorBank) {
                    testShoe->CopyShoe(copyShoe);
                    auto result = blackjack_check_sim(testPlayer, testDealer, testShoe, playerWager, true);
                    EXPECT_EQ(testPlayer->GetCurrentHands()->RetrieveNode(0)->data->GetWager(), playerWager);
                    EXPECT_EQ(testPlayer->GetCurrentHands()->RetrieveNode(0)->data->GetInsuranceWager(), 0);
                    EXPECT_EQ(testPlayer->GetCurrentHands()->RetrieveNode(0)->data->GetNet(), 0);
                    EXPECT_TRUE(result);
                    testPlayer->SetBankTotal(priorBank);
                    testPlayer->GetCurrentHands()->ClearList();
                    testPlayer->GetTotalHandBankTotals()->ClearList();
                    testPlayer->GetTotalHandCardTotals()->ClearList();
                    testPlayer->GetTotalHandNets()->ClearList();
                    testPlayer->GetTotalHandsPlayed()->ClearList();
                    testPlayer->GetTotalHandWagers()->ClearList();
                    testDealer->GetCurrentHands()->ClearList();
                    playerWager++;
                    testShoe->GetCardsInShoe()->ClearList();
                }
            }
            // Testing with false
            {
                playerWager = 10;
                while (playerWager <= priorBank) {
                    testShoe->CopyShoe(copyShoe);
                    auto result = blackjack_check_sim(testPlayer, testDealer, testShoe, playerWager, false);
                    EXPECT_EQ(testPlayer->GetCurrentHands()->RetrieveNode(0)->data->GetWager(), playerWager);
                    EXPECT_EQ(testPlayer->GetCurrentHands()->RetrieveNode(0)->data->GetInsuranceWager(), 0);
                    EXPECT_EQ(testPlayer->GetCurrentHands()->RetrieveNode(0)->data->GetNet(), 0);
                    EXPECT_TRUE(result);
                    testPlayer->SetBankTotal(priorBank);
                    testPlayer->GetCurrentHands()->ClearList();
                    testPlayer->GetTotalHandBankTotals()->ClearList();
                    testPlayer->GetTotalHandCardTotals()->ClearList();
                    testPlayer->GetTotalHandNets()->ClearList();
                    testPlayer->GetTotalHandsPlayed()->ClearList();
                    testPlayer->GetTotalHandWagers()->ClearList();
                    testDealer->GetCurrentHands()->ClearList();
                    playerWager++;
                    testShoe->GetCardsInShoe()->ClearList();
                }
            }
        }
        playerWager = 10;
    }
    testShoe->GetCardsInShoe()->ClearList();
}

// Blackjack strategy test, no duplicate ranks, no ace in hand off deal
TEST_F(test_x, BlackjackStrat){
    // Create hands, players, and cards
    std::shared_ptr<Player> testUser(new Player());
    std::shared_ptr<Hand> userHand(new Hand());
    std::shared_ptr<Player> testDealer(new Player());
    std::shared_ptr<Hand> dealerHand(new Hand());
    std::shared_ptr<Card> testCard(new Card);
    std::shared_ptr<node<Card>> testNode;
    testUser->SetBankTotal(100);
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
        testUser->SetCurrentHands(userHand);
        testUser->GetCurrentHands()->RetrieveNode(0)->data->SetWager(10);
        for (int j = 0; j < 13; j++) {
            // Add card to dealer hand
            testCard = std::make_shared<Card>(Ranks[j], Suits[0]);
            testNode = dealerHand->GetPlayerCards()->InitNode(testCard);
            dealerHand->SetPlayerCards(testNode);
            testDealer->SetCurrentHands(dealerHand);
            blackjack_strategy(testUser, testUser->GetCurrentHands()->RetrieveNode(0)->data, testDealer, false, false);
            EXPECT_FALSE(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][0]));
            EXPECT_TRUE(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][1]));
            EXPECT_FALSE(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][2]));
            EXPECT_FALSE(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][3]));
            testDealer->GetCurrentHands()->RetrieveNode(0)->data->GetPlayerCards()->RemoveNode(-1);
            testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->ClearHashTable();
        }
        testUser->GetCurrentHands()->RemoveNode(0);
    }
    // Player has a card total of 9
    userHand->SetCardsTotal(9);
    testUser->SetCurrentHands(userHand);
    for (int i = 0; i < 13; i++) {
        // Add card to dealer hand
        testCard = std::make_shared<Card>(Ranks[i], Suits[0]);
        testNode = dealerHand->GetPlayerCards()->InitNode(testCard);
        dealerHand->SetPlayerCards(testNode);
        testDealer->SetCurrentHands(dealerHand);
        // Dealer has a 2 - 6
        if (i != 0 && i < 6) {
            // Test strategy for if a player can double down
            {   
                // Set wager
                testUser->GetCurrentHands()->RetrieveNode(0)->data->SetWager(10);
                // Test strategy
                blackjack_strategy(testUser, testUser->GetCurrentHands()->RetrieveNode(0)->data, testDealer, false, false);
                EXPECT_TRUE(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][0]));
                EXPECT_TRUE(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][1]));
                EXPECT_FALSE(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][2]));
                EXPECT_FALSE(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][3]));
                testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->ClearHashTable();
            }
            // Test strategy for if a player cannot double down
            {
                // Set wager
                testUser->GetCurrentHands()->RetrieveNode(0)->data->SetWager(200);
                // Test strategy
                blackjack_strategy(testUser, testUser->GetCurrentHands()->RetrieveNode(0)->data, testDealer, false, false);
                EXPECT_FALSE(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][0]));
                EXPECT_TRUE(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][1]));
                EXPECT_FALSE(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][2]));
                EXPECT_FALSE(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][3]));
                testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->ClearHashTable();
            }
        }
        // Otherwise
        else {
            // Set wager
            testUser->GetCurrentHands()->RetrieveNode(0)->data->SetWager(10);
            // Test strategy
            blackjack_strategy(testUser, testUser->GetCurrentHands()->RetrieveNode(0)->data, testDealer, false, false);
            EXPECT_FALSE(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][0]));
            EXPECT_TRUE(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][1]));
            EXPECT_FALSE(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][2]));
            EXPECT_FALSE(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][3]));
            testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->ClearHashTable();
        }    
        testDealer->GetCurrentHands()->RetrieveNode(0)->data->GetPlayerCards()->RemoveNode(-1);
    }
    // Player has a card total of 10
    userHand->SetCardsTotal(10);
    testUser->SetCurrentHands(userHand);
    for (int i = 0; i < 13; i++) {
        // Add card to dealer hand
        testCard = std::make_shared<Card>(Ranks[i], Suits[0]);
        testNode = dealerHand->GetPlayerCards()->InitNode(testCard);
        dealerHand->SetPlayerCards(testNode);
        testDealer->SetCurrentHands(dealerHand);
        // Dealer has a 2 - 9
        if (i != 0 && i < 9) {
            // Test strategy for if a player can double down
            {
                // Set wager
                testUser->GetCurrentHands()->RetrieveNode(0)->data->SetWager(10);
                // Test strategy
                blackjack_strategy(testUser, testUser->GetCurrentHands()->RetrieveNode(0)->data, testDealer, false, false);
                EXPECT_TRUE(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][0]));
                EXPECT_TRUE(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][1]));
                EXPECT_FALSE(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][2]));
                EXPECT_FALSE(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][3]));
                testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->ClearHashTable();
            }
            // Test strategy for if a player cannot double down
            {
                // Set wager
                testUser->GetCurrentHands()->RetrieveNode(0)->data->SetWager(200);
                // Test strategy
                blackjack_strategy(testUser, testUser->GetCurrentHands()->RetrieveNode(0)->data, testDealer, false, false);
                EXPECT_FALSE(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][0]));
                EXPECT_TRUE(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][1]));
                EXPECT_FALSE(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][2]));
                EXPECT_FALSE(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][3]));
                testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->ClearHashTable();
            }
        }
        // Otherwise
        else {
            // Set wager
            testUser->GetCurrentHands()->RetrieveNode(0)->data->SetWager(10);
            // Test strategy
            blackjack_strategy(testUser, testUser->GetCurrentHands()->RetrieveNode(0)->data, testDealer, false, false);
            EXPECT_FALSE(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][0]));
            EXPECT_TRUE(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][1]));
            EXPECT_FALSE(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][2]));
            EXPECT_FALSE(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][3]));
            testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->ClearHashTable();
        }
        testDealer->GetCurrentHands()->RetrieveNode(0)->data->GetPlayerCards()->RemoveNode(-1);
    }
    // Player has a hand card value of 11
    userHand->SetCardsTotal(11);
    testUser->SetCurrentHands(userHand);
    for (int i = 0; i < 13; i++) {
        // Player can double down
        {
            testUser->GetCurrentHands()->RetrieveNode(0)->data->SetWager(10);
            // Add card to dealer hand
            testCard = std::make_shared<Card>(Ranks[i], Suits[0]);
            testNode = dealerHand->GetPlayerCards()->InitNode(testCard);
            dealerHand->SetPlayerCards(testNode);
            testDealer->SetCurrentHands(dealerHand);
            // Test strategy - Can double down
            blackjack_strategy(testUser, testUser->GetCurrentHands()->RetrieveNode(0)->data, testDealer, false, false);
            EXPECT_TRUE(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][0]));
            EXPECT_TRUE(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][1]));
            EXPECT_FALSE(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][2]));
            EXPECT_FALSE(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][3]));
            testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->ClearHashTable();
            // Remove last card from dealer hand
            testDealer->GetCurrentHands()->RetrieveNode(0)->data->GetPlayerCards()->RemoveNode(-1);           
        }
        // Player cannot double down
        {
            testUser->GetCurrentHands()->RetrieveNode(0)->data->SetWager(200);
            // Add card to dealer hand
            testCard = std::make_shared<Card>(Ranks[i], Suits[0]);
            testNode = dealerHand->GetPlayerCards()->InitNode(testCard);
            dealerHand->SetPlayerCards(testNode);
            // Test strategy - Can double down
            blackjack_strategy(testUser, testUser->GetCurrentHands()->RetrieveNode(0)->data, testDealer, false, false);
            EXPECT_FALSE(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][0]));
            EXPECT_TRUE(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][1]));
            EXPECT_FALSE(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][2]));
            EXPECT_FALSE(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][3]));
            testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->ClearHashTable();
            // Remove last card from dealer hand
            testDealer->GetCurrentHands()->RetrieveNode(0)->data->GetPlayerCards()->RemoveNode(-1);     
        }
    }
    // Player has a hand card value of 12
    userHand->SetCardsTotal(12);
    testUser->SetCurrentHands(userHand);
    for (int i = 0; i < 13; i++) {
        testUser->GetCurrentHands()->RetrieveNode(0)->data->SetWager(10);
        // Add card to dealer hand
        testCard = std::make_shared<Card>(Ranks[i], Suits[0]);
        testNode = dealerHand->GetPlayerCards()->InitNode(testCard);
        dealerHand->SetPlayerCards(testNode);
        testDealer->SetCurrentHands(dealerHand);
        blackjack_strategy(testUser, testUser->GetCurrentHands()->RetrieveNode(0)->data, testDealer, false, false);
        // Test strategy for 4, 5, and 6 cards
        if (i == 3 || i == 4 || i == 5) {
            EXPECT_FALSE(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][0]));
            EXPECT_FALSE(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][1]));
            EXPECT_FALSE(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][2]));
            EXPECT_TRUE(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][3]));
        }
        // Test strategy for other cards
        else {
            EXPECT_FALSE(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][0]));
            EXPECT_TRUE(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][1]));
            EXPECT_FALSE(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][2]));
            EXPECT_FALSE(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][3]));
        }
        testDealer->GetCurrentHands()->RetrieveNode(0)->data->GetPlayerCards()->RemoveNode(-1);  
        testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->ClearHashTable();
    }
    // Player has a hand card value of 13 through 16
    for (int i = 13; i <= 16; i++) {
        userHand->SetCardsTotal(i);
        testUser->GetCurrentHands()->RetrieveNode(0)->data->SetWager(10);
        testUser->SetCurrentHands(userHand);
        for (int j = 0; j < 13; j++) {
            // Add card to dealer hand
            testCard = std::make_shared<Card>(Ranks[j], Suits[0]);
            testNode = dealerHand->GetPlayerCards()->InitNode(testCard);
            dealerHand->SetPlayerCards(testNode);
            testDealer->SetCurrentHands(dealerHand);
            blackjack_strategy(testUser, testUser->GetCurrentHands()->RetrieveNode(0)->data, testDealer, false, false);
            // Test strategy for 2 through 6
            if (j != 0 && j < 6) {
                EXPECT_FALSE(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][0]));
                EXPECT_FALSE(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][1]));
                EXPECT_FALSE(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][2]));
                EXPECT_TRUE(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][3]));
            }
            // Test strategy otherwise
            else {
                EXPECT_FALSE(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][0]));
                EXPECT_TRUE(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][1]));
                EXPECT_FALSE(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][2]));
                EXPECT_FALSE(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][3]));
            }
            testDealer->GetCurrentHands()->RetrieveNode(0)->data->GetPlayerCards()->RemoveNode(-1);
            testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->ClearHashTable();
        }
        testUser->GetCurrentHands()->RemoveNode(0);
    }
    // Player has a hand card value of 17 through 21
    for (int i = 17; i <= 21; i++) {
        userHand->SetCardsTotal(i);
        testUser->GetCurrentHands()->RetrieveNode(0)->data->SetWager(10);
        testUser->SetCurrentHands(userHand);
        for (int j = 0; j < 13; j++) {
            // Add card to dealer hand
            testCard = std::make_shared<Card>(Ranks[j], Suits[0]);
            testNode = dealerHand->GetPlayerCards()->InitNode(testCard);
            dealerHand->SetPlayerCards(testNode);
            testDealer->SetCurrentHands(dealerHand);
            blackjack_strategy(testUser, testUser->GetCurrentHands()->RetrieveNode(0)->data, testDealer, false, false);
            EXPECT_FALSE(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][0]));
            EXPECT_FALSE(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][1]));
            EXPECT_FALSE(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][2]));
            EXPECT_TRUE(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][3]));
            testDealer->GetCurrentHands()->RetrieveNode(0)->data->GetPlayerCards()->RemoveNode(-1);
            testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->ClearHashTable();
        }
        testUser->GetCurrentHands()->RemoveNode(0);
    }
}

// Blackjack strategy test, no duplicate ranks, Ace in hand off deal
TEST_F(test_x, BlackjackStratAces) {
    // Create hands, players, and cards
    std::shared_ptr<Player> testUser(new Player());
    std::shared_ptr<Hand> userHand(new Hand());
    std::shared_ptr<Player> testDealer(new Player());
    std::shared_ptr<Hand> dealerHand(new Hand());
    std::shared_ptr<Card> testCard(new Card);
    std::shared_ptr<node<Card>> testNode;
    testUser->SetBankTotal(100);
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
        testUser->GetCurrentHands()->ClearList();
        testCard = std::make_shared<Card>(Ranks[i], Suits[0]);
        testNode = dealerHand->GetPlayerCards()->InitNode(testCard);
        userHand->SetPlayerCards(testNode);
        userHand->AddHandTotal();
        testUser->SetCurrentHands(userHand);
        for (int j = 0; j < 13; j++) {
            // Add card to dealer hand
            testDealer->GetCurrentHands()->ClearList();
            testCard = std::make_shared<Card>(Ranks[j], Suits[0]);
            testNode = dealerHand->GetPlayerCards()->InitNode(testCard);
            dealerHand->SetPlayerCards(testNode);
            testDealer->SetCurrentHands(dealerHand);
            // Card being added is a 5 or 6
            if (j == 4 || j == 5) {
                // Player can double down
                {
                    // Set wager
                    testUser->GetCurrentHands()->RetrieveNode(0)->data->SetWager(10);
                    // Test strategy - Can double down
                    blackjack_strategy(testUser, testUser->GetCurrentHands()->RetrieveNode(0)->data, testDealer, false, false);
                    EXPECT_TRUE(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][0]));
                    EXPECT_TRUE(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][1]));
                    EXPECT_FALSE(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][2]));
                    EXPECT_FALSE(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][3]));
                    testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->ClearHashTable();
                }
                // Player can't double down
                {
                    // Set wager
                    testUser->GetCurrentHands()->RetrieveNode(0)->data->SetWager(200);
                    // Test strategy - Can't double down
                    blackjack_strategy(testUser, testUser->GetCurrentHands()->RetrieveNode(0)->data, testDealer, false, false);
                    EXPECT_FALSE(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][0]));
                    EXPECT_TRUE(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][1]));
                    EXPECT_FALSE(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][2]));
                    EXPECT_FALSE(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][3]));
                    testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->ClearHashTable();
                }
            }
            // Otherwise
            else {
                // Set wager
                testUser->GetCurrentHands()->RetrieveNode(0)->data->SetWager(10);
                // Test strategy - Can't double down
                blackjack_strategy(testUser, testUser->GetCurrentHands()->RetrieveNode(0)->data, testDealer, false, false);
                EXPECT_FALSE(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][0]));
                EXPECT_TRUE(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][1]));
                EXPECT_FALSE(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][2]));
                EXPECT_FALSE(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][3]));
                testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->ClearHashTable();
            }
            testDealer->GetCurrentHands()->RetrieveNode(0)->data->GetPlayerCards()->RemoveNode(-1);
        }
        testUser->GetCurrentHands()->RetrieveNode(0)->data->GetPlayerCards()->RemoveNode(-1);
        testUser->GetCurrentHands()->RetrieveNode(0)->data->AddHandTotal();
    }
    // Player has a card total of 15 or 16 (Ace, 4 || Ace, 5)
    for (int i = 3; i <= 4; i++) {
        testUser->GetCurrentHands()->ClearList();
        testCard = std::make_shared<Card>(Ranks[i], Suits[0]);
        testNode = dealerHand->GetPlayerCards()->InitNode(testCard);
        userHand->SetPlayerCards(testNode);
        userHand->AddHandTotal();
        testUser->SetCurrentHands(userHand);
        for (int j = 0; j < 13; j++) {
            // Add card to dealer hand
            testDealer->GetCurrentHands()->ClearList();
            testCard = std::make_shared<Card>(Ranks[j], Suits[0]);
            testNode = dealerHand->GetPlayerCards()->InitNode(testCard);
            dealerHand->SetPlayerCards(testNode);
            testDealer->SetCurrentHands(dealerHand);
            // Card being added is a 4, 5, or 6
            if (j == 3 || j == 4 || j == 5) {
                // Player can double down
                {
                    // Set wager
                    testUser->GetCurrentHands()->RetrieveNode(0)->data->SetWager(10);
                    // Test strategy - Can double down
                    blackjack_strategy(testUser, testUser->GetCurrentHands()->RetrieveNode(0)->data, testDealer, false, false);
                    EXPECT_TRUE(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][0]));
                    EXPECT_TRUE(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][1]));
                    EXPECT_FALSE(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][2]));
                    EXPECT_FALSE(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][3]));
                    testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->ClearHashTable();
                }
                // Player can't double down
                {
                    // Set wager
                    testUser->GetCurrentHands()->RetrieveNode(0)->data->SetWager(200);
                    // Test strategy - Can't double down
                    blackjack_strategy(testUser, testUser->GetCurrentHands()->RetrieveNode(0)->data, testDealer, false, false);
                    EXPECT_FALSE(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][0]));
                    EXPECT_TRUE(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][1]));
                    EXPECT_FALSE(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][2]));
                    EXPECT_FALSE(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][3]));
                    testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->ClearHashTable();
                }
            }
            // Otherwise
            else {
                // Set wager
                testUser->GetCurrentHands()->RetrieveNode(0)->data->SetWager(10);
                // Test strategy
                blackjack_strategy(testUser, testUser->GetCurrentHands()->RetrieveNode(0)->data, testDealer, false, false);
                EXPECT_FALSE(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][0]));
                EXPECT_TRUE(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][1]));
                EXPECT_FALSE(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][2]));
                EXPECT_FALSE(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][3]));
                testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->ClearHashTable();
            }
            testDealer->GetCurrentHands()->RetrieveNode(0)->data->GetPlayerCards()->RemoveNode(-1);
        }
        testUser->GetCurrentHands()->RetrieveNode(0)->data->GetPlayerCards()->RemoveNode(-1);
        testUser->GetCurrentHands()->RetrieveNode(0)->data->AddHandTotal();
    }
    // Player has a card total of 17 (Ace, 6)
    {
        testUser->GetCurrentHands()->ClearList();
        testCard = std::make_shared<Card>(Ranks[5], Suits[0]);
        testNode = dealerHand->GetPlayerCards()->InitNode(testCard);
        userHand->SetPlayerCards(testNode);
        userHand->AddHandTotal();
        testUser->SetCurrentHands(userHand);
        for (int i = 0; i < 13; i++) {
            // Add card to dealer hand
            testDealer->GetCurrentHands()->ClearList();
            testCard = std::make_shared<Card>(Ranks[i], Suits[0]);
            testNode = dealerHand->GetPlayerCards()->InitNode(testCard);
            dealerHand->SetPlayerCards(testNode);
            testDealer->SetCurrentHands(dealerHand);
            if (i >= 2 && i <= 5) {
                // Player can double down
                {
                    // Set wager
                    testUser->GetCurrentHands()->RetrieveNode(0)->data->SetWager(10);
                    // Test strategy - Can double down
                    blackjack_strategy(testUser, testUser->GetCurrentHands()->RetrieveNode(0)->data, testDealer, false, false);
                    EXPECT_TRUE(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][0]));
                    EXPECT_TRUE(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][1]));
                    EXPECT_FALSE(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][2]));
                    EXPECT_FALSE(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][3]));
                    testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->ClearHashTable();
                }
                // Player can't double down
                {
                    // Set wager
                    testUser->GetCurrentHands()->RetrieveNode(0)->data->SetWager(200);
                    // Test strategy - Can't double down
                    blackjack_strategy(testUser, testUser->GetCurrentHands()->RetrieveNode(0)->data, testDealer, false, false);
                    EXPECT_FALSE(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][0]));
                    EXPECT_TRUE(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][1]));
                    EXPECT_FALSE(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][2]));
                    EXPECT_FALSE(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][3]));
                    testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->ClearHashTable();
                }
            }
            // Otherwise
            else {
                // Set wager
                testUser->GetCurrentHands()->RetrieveNode(0)->data->SetWager(10);
                // Test strategy
                blackjack_strategy(testUser, testUser->GetCurrentHands()->RetrieveNode(0)->data, testDealer, false, false);
                EXPECT_FALSE(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][0]));
                EXPECT_TRUE(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][1]));
                EXPECT_FALSE(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][2]));
                EXPECT_FALSE(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][3]));
                testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->ClearHashTable();
            }
            testDealer->GetCurrentHands()->RetrieveNode(0)->data->GetPlayerCards()->RemoveNode(-1);
        }
        testUser->GetCurrentHands()->RetrieveNode(0)->data->GetPlayerCards()->RemoveNode(-1);
        testUser->GetCurrentHands()->RetrieveNode(0)->data->AddHandTotal();
    }
    // Player card total is 18 (Ace, 7)
    {
        testDealer->GetCurrentHands()->ClearList();
        testCard = std::make_shared<Card>(Ranks[6], Suits[0]);
        testNode = dealerHand->GetPlayerCards()->InitNode(testCard);
        userHand->SetPlayerCards(testNode);
        userHand->AddHandTotal();
        testUser->SetCurrentHands(userHand);
        for (int i = 0; i < 13; i++) {
            // Add card to dealer hand
            testDealer->GetCurrentHands()->ClearList();
            testCard = std::make_shared<Card>(Ranks[i], Suits[0]);
            testNode = dealerHand->GetPlayerCards()->InitNode(testCard);
            dealerHand->SetPlayerCards(testNode);
            testDealer->SetCurrentHands(dealerHand);
            if (i == 1 || i == 6 || i == 7) {
                // Set wager
                testUser->GetCurrentHands()->RetrieveNode(0)->data->SetWager(10);
                // Test strategy
                blackjack_strategy(testUser, testUser->GetCurrentHands()->RetrieveNode(0)->data, testDealer, false, false);
                EXPECT_FALSE(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][0]));
                EXPECT_FALSE(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][1]));
                EXPECT_FALSE(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][2]));
                EXPECT_TRUE(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][3]));
                testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->ClearHashTable();
            }
            else if (i >= 2 && i <= 5) {
                // Player can double down
                {
                    // Set wager
                    testUser->GetCurrentHands()->RetrieveNode(0)->data->SetWager(10);
                    // Test strategy - Can double down
                    blackjack_strategy(testUser, testUser->GetCurrentHands()->RetrieveNode(0)->data, testDealer, false, false);
                    EXPECT_TRUE(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][0]));
                    EXPECT_FALSE(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][1]));
                    EXPECT_FALSE(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][2]));
                    EXPECT_TRUE(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][3]));
                    testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->ClearHashTable();
                }
                // Player can't double down
                {
                    // Set wager
                    testUser->GetCurrentHands()->RetrieveNode(0)->data->SetWager(200);
                    // Test strategy - Can't double down
                    blackjack_strategy(testUser, testUser->GetCurrentHands()->RetrieveNode(0)->data, testDealer, false, false);
                    EXPECT_FALSE(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][0]));
                    EXPECT_FALSE(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][1]));
                    EXPECT_FALSE(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][2]));
                    EXPECT_TRUE(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][3]));
                    testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->ClearHashTable();
                }
            }
            else {
                // Set wager
                testUser->GetCurrentHands()->RetrieveNode(0)->data->SetWager(10);
                // Test strategy
                blackjack_strategy(testUser, testUser->GetCurrentHands()->RetrieveNode(0)->data, testDealer, false, false);
                EXPECT_FALSE(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][0]));
                EXPECT_TRUE(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][1]));
                EXPECT_FALSE(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][2]));
                EXPECT_FALSE(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][3]));
                testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->ClearHashTable();
            }
            testDealer->GetCurrentHands()->RetrieveNode(0)->data->GetPlayerCards()->RemoveNode(-1);
        }
        testUser->GetCurrentHands()->RetrieveNode(0)->data->GetPlayerCards()->RemoveNode(-1);
        testUser->GetCurrentHands()->RetrieveNode(0)->data->AddHandTotal();
    }
    // Player card total is 19, 20, or 21 (Ace, 8 || Ace, 9 || Ace, Ten)
    for (int i = 8; i <= 12; i++) {
        testDealer->GetCurrentHands()->ClearList();
        testCard = std::make_shared<Card>(Ranks[i], Suits[0]);
        testNode = dealerHand->GetPlayerCards()->InitNode(testCard);
        userHand->SetPlayerCards(testNode);
        userHand->AddHandTotal();
        testUser->SetCurrentHands(userHand);
        for (int j = 0; j < 13; j++) {
            // Add card to dealer hand
            testDealer->GetCurrentHands()->ClearList();
            testCard = std::make_shared<Card>(Ranks[j], Suits[0]);
            testNode = dealerHand->GetPlayerCards()->InitNode(testCard);
            dealerHand->SetPlayerCards(testNode);
            testDealer->SetCurrentHands(dealerHand);
            // Set wager
            testUser->GetCurrentHands()->RetrieveNode(0)->data->SetWager(200);
            // Test strategy
            blackjack_strategy(testUser, testUser->GetCurrentHands()->RetrieveNode(0)->data, testDealer, false, false);
            EXPECT_FALSE(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][0]));
            EXPECT_FALSE(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][1]));
            EXPECT_FALSE(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][2]));
            EXPECT_TRUE(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][3]));
            testDealer->GetCurrentHands()->RetrieveNode(0)->data->GetPlayerCards()->RemoveNode(-1);
            testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->ClearHashTable();
        }
        testUser->GetCurrentHands()->RetrieveNode(0)->data->GetPlayerCards()->RemoveNode(-1);
        testUser->GetCurrentHands()->RetrieveNode(0)->data->AddHandTotal();
    }
}

// Blackjack strategy test, duplicate ranks
TEST_F(test_x, BlackjackStratDuplicates) {
    // Create hands, players, and cards
    std::shared_ptr<Player> testUser(new Player());
    std::shared_ptr<Hand> userHand(new Hand());
    std::shared_ptr<Player> testDealer(new Player());
    std::shared_ptr<Hand> dealerHand(new Hand());
    std::shared_ptr<Card> testCard(new Card);
    std::shared_ptr<node<Card>> testNode;
    testUser->SetBankTotal(100);
    // Add first card to dealer
    testCard = std::make_shared<Card>(Ranks[0], Suits[0]);
    testNode = dealerHand->GetPlayerCards()->InitNode(testCard);
    dealerHand->SetPlayerCards(testNode);
    // Player card total is 4 (two, two) or 6 (three, three)
    for (int i = 1; i <= 2; i++) {
        // Add cards to player hand
        testUser->GetCurrentHands()->ClearList();
        testCard = std::make_shared<Card>(Ranks[i], Suits[0]);
        testNode = dealerHand->GetPlayerCards()->InitNode(testCard);
        userHand->AddCardToHand(testNode);
        testCard = std::make_shared<Card>(Ranks[i], Suits[0]);
        testNode = dealerHand->GetPlayerCards()->InitNode(testCard);
        userHand->AddCardToHand(testNode);
        testUser->SetCurrentHands(userHand);
        for (int j = 0; j < 13; j++) {
            // Add card to dealer hand
            testDealer->GetCurrentHands()->ClearList();
            testCard = std::make_shared<Card>(Ranks[j], Suits[0]);
            testNode = dealerHand->GetPlayerCards()->InitNode(testCard);
            dealerHand->SetPlayerCards(testNode);
            testDealer->SetCurrentHands(dealerHand);
            testUser->GetCurrentHands()->RetrieveNode(0)->data->SetWager(10);
            // Can split hand
            {
                // Test strategy
                blackjack_strategy(testUser, testUser->GetCurrentHands()->RetrieveNode(0)->data, testDealer, false, false);
                if (j == 1 || j == 2) {
                    EXPECT_FALSE(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][0]));
                    EXPECT_TRUE(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][1]));
                    EXPECT_TRUE(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][2]));
                    EXPECT_FALSE(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][3]));
                }
                else if (j >= 3 && j <= 6) {
                    EXPECT_FALSE(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][0]));
                    EXPECT_FALSE(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][1]));
                    EXPECT_TRUE(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][2]));
                    EXPECT_FALSE(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][3]));      
                }
                else {
                    EXPECT_FALSE(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][0]));
                    EXPECT_TRUE(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][1]));
                    EXPECT_FALSE(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][2]));
                    EXPECT_FALSE(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][3]));
                }
                testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->ClearHashTable();      
            }
            // Can't split hand
            {
                // Can't split
                testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->AddToTable(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[4][1]);
                // Test strategy
                blackjack_strategy(testUser, testUser->GetCurrentHands()->RetrieveNode(0)->data, testDealer, false, false);
                EXPECT_FALSE(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][0]));
                EXPECT_TRUE(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][1]));
                EXPECT_FALSE(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][2]));
                EXPECT_FALSE(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][3]));
                // Can split
                testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->RemoveElement(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[4][1]);
                testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->ClearHashTable();
            }
            testDealer->GetCurrentHands()->RetrieveNode(0)->data->GetPlayerCards()->RemoveNode(-1);
        }
        testUser->GetCurrentHands()->RetrieveNode(0)->data->GetPlayerCards()->RemoveNode(-1);
        testUser->GetCurrentHands()->RetrieveNode(0)->data->GetPlayerCards()->RemoveNode(-1);
        testUser->GetCurrentHands()->RetrieveNode(0)->data->AddHandTotal();
    }
    // Player card total is 8 (four, four)
    {
        // Add cards to player hand, set wager
        testUser->GetCurrentHands()->ClearList();
        testCard = std::make_shared<Card>(Ranks[3], Suits[0]);
        testNode = dealerHand->GetPlayerCards()->InitNode(testCard);
        userHand->AddCardToHand(testNode);
        testCard = std::make_shared<Card>(Ranks[3], Suits[0]);
        testNode = dealerHand->GetPlayerCards()->InitNode(testCard);
        userHand->AddCardToHand(testNode);
        testUser->SetCurrentHands(userHand);
        testUser->GetCurrentHands()->RetrieveNode(0)->data->SetWager(10);
        for (int i = 0; i < 13; i++) {
            // Add card to dealer hand
            testDealer->GetCurrentHands()->ClearList();
            testCard = std::make_shared<Card>(Ranks[i], Suits[0]);
            testNode = dealerHand->GetPlayerCards()->InitNode(testCard);
            dealerHand->SetPlayerCards(testNode);
            testDealer->SetCurrentHands(dealerHand);
            // Can split hand
            {
                // Test strategy
                blackjack_strategy(testUser, testUser->GetCurrentHands()->RetrieveNode(0)->data, testDealer, false, false);
                if (i == 4 || i == 5) {
                    EXPECT_FALSE(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][0]));
                    EXPECT_TRUE(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][1]));
                    EXPECT_TRUE(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][2]));
                    EXPECT_FALSE(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][3]));
                }
                else {
                    EXPECT_FALSE(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][0]));
                    EXPECT_TRUE(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][1]));
                    EXPECT_FALSE(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][2]));
                    EXPECT_FALSE(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][3]));
                }
                testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->ClearHashTable();
            }
            // Can't split hand
            {
                // Can't split
                testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->AddToTable(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[4][1]);
                // Test strategy
                blackjack_strategy(testUser, testUser->GetCurrentHands()->RetrieveNode(0)->data, testDealer, false, false);
                EXPECT_FALSE(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][0]));
                EXPECT_TRUE(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][1]));
                EXPECT_FALSE(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][2]));
                EXPECT_FALSE(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][3]));
                // Can split
                testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->RemoveElement(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[4][1]);
                testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->ClearHashTable();
            }
            testDealer->GetCurrentHands()->RetrieveNode(0)->data->GetPlayerCards()->RemoveNode(-1);
        }
        testUser->GetCurrentHands()->RetrieveNode(0)->data->GetPlayerCards()->RemoveNode(-1);
        testUser->GetCurrentHands()->RetrieveNode(0)->data->GetPlayerCards()->RemoveNode(-1);
        testUser->GetCurrentHands()->RetrieveNode(0)->data->AddHandTotal();     
    }
    // Player card total is 10 (five, five)
    {
        // Add cards to player hand, set wager
        testUser->GetCurrentHands()->ClearList();
        testCard = std::make_shared<Card>(Ranks[4], Suits[0]);
        testNode = dealerHand->GetPlayerCards()->InitNode(testCard);
        userHand->AddCardToHand(testNode);
        testCard = std::make_shared<Card>(Ranks[4], Suits[0]);
        testNode = dealerHand->GetPlayerCards()->InitNode(testCard);
        userHand->AddCardToHand(testNode);
        testUser->SetCurrentHands(userHand);
        for (int i = 0; i < 13; i++) {
            // Add card to dealer hand
            testDealer->GetCurrentHands()->ClearList();
            testCard = std::make_shared<Card>(Ranks[i], Suits[0]);
            testNode = dealerHand->GetPlayerCards()->InitNode(testCard);
            dealerHand->SetPlayerCards(testNode);
            testDealer->SetCurrentHands(dealerHand);
            if (i == 0 || i >= 9) {
                // Set wager
                testUser->GetCurrentHands()->RetrieveNode(0)->data->SetWager(10);
                // Test strategy
                blackjack_strategy(testUser, testUser->GetCurrentHands()->RetrieveNode(0)->data, testDealer, false, false);
                EXPECT_FALSE(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][0]));
                EXPECT_TRUE(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][1]));
                EXPECT_FALSE(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][2]));
                EXPECT_FALSE(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][3]));
                testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->ClearHashTable();
            }
            else {
                // Can double down
                {
                    // Set wager
                    testUser->GetCurrentHands()->RetrieveNode(0)->data->SetWager(10);
                    // Test strategy
                    blackjack_strategy(testUser, testUser->GetCurrentHands()->RetrieveNode(0)->data, testDealer, false, false);
                    EXPECT_TRUE(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][0]));
                    EXPECT_TRUE(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][1]));
                    EXPECT_FALSE(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][2]));
                    EXPECT_FALSE(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][3]));
                    testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->ClearHashTable();
                }
                // Cannot double down
                {
                    // Set wager
                    testUser->GetCurrentHands()->RetrieveNode(0)->data->SetWager(101);
                    // Test strategy
                    blackjack_strategy(testUser, testUser->GetCurrentHands()->RetrieveNode(0)->data, testDealer, false, false);
                    EXPECT_FALSE(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][0]));
                    EXPECT_TRUE(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][1]));
                    EXPECT_FALSE(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][2]));
                    EXPECT_FALSE(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][3]));
                    testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->ClearHashTable();
                }
            }
            testDealer->GetCurrentHands()->RetrieveNode(0)->data->GetPlayerCards()->RemoveNode(-1);
        }
        testUser->GetCurrentHands()->RetrieveNode(0)->data->GetPlayerCards()->RemoveNode(-1);
        testUser->GetCurrentHands()->RetrieveNode(0)->data->GetPlayerCards()->RemoveNode(-1);
        testUser->GetCurrentHands()->RetrieveNode(0)->data->AddHandTotal();   
    }
    // Player card total is 12 (six, six || Ace, Ace) 
    {
        // Player has two sixes
        {
            // Add cards to player hand, set wager
            testUser->GetCurrentHands()->ClearList();
            testCard = std::make_shared<Card>(Ranks[5], Suits[0]);
            testNode = dealerHand->GetPlayerCards()->InitNode(testCard);
            userHand->AddCardToHand(testNode);
            testCard = std::make_shared<Card>(Ranks[5], Suits[0]);
            testNode = dealerHand->GetPlayerCards()->InitNode(testCard);
            userHand->AddCardToHand(testNode);
            testUser->SetCurrentHands(userHand);
            testUser->GetCurrentHands()->RetrieveNode(0)->data->SetWager(10);
            for (int i = 0; i < 13; i++) {
                // Add card to dealer hand
                testDealer->GetCurrentHands()->ClearList();
                testCard = std::make_shared<Card>(Ranks[i], Suits[0]);
                testNode = dealerHand->GetPlayerCards()->InitNode(testCard);
                dealerHand->SetPlayerCards(testNode);
                testDealer->SetCurrentHands(dealerHand);
                // Can split
                {
                    // Test strategy
                    blackjack_strategy(testUser, testUser->GetCurrentHands()->RetrieveNode(0)->data, testDealer, false, false);
                    if (i >= 1 && i <= 5) {
                        EXPECT_FALSE(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][0]));
                        EXPECT_FALSE(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][1]));
                        EXPECT_TRUE(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][2]));
                        EXPECT_FALSE(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][3]));
                    }
                    else if (i == 6) {
                        EXPECT_FALSE(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][0]));
                        EXPECT_TRUE(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][1]));
                        EXPECT_TRUE(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][2]));
                        EXPECT_FALSE(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][3]));
                    }
                    else {
                        EXPECT_FALSE(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][0]));
                        EXPECT_TRUE(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][1]));
                        EXPECT_FALSE(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][2]));
                        EXPECT_FALSE(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][3]));
                    }
                    testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->ClearHashTable();
                }
                // Can't split
                {
                    testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->AddToTable(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[4][1]);
                    // Test strategy
                    blackjack_strategy(testUser, testUser->GetCurrentHands()->RetrieveNode(0)->data, testDealer, false, false);
                    if ((i >= 1 && i <= 2) || (i == 0 || i >= 6)) {
                        EXPECT_FALSE(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][0]));
                        EXPECT_TRUE(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][1]));
                        EXPECT_FALSE(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][2]));
                        EXPECT_FALSE(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][3]));
                    }
                    else {
                        EXPECT_FALSE(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][0]));
                        EXPECT_FALSE(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][1]));
                        EXPECT_FALSE(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][2]));
                        EXPECT_TRUE(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][3]));
                    }
                    testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->RemoveElement(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[4][1]);
                    testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->ClearHashTable();
                }
                testDealer->GetCurrentHands()->RetrieveNode(0)->data->GetPlayerCards()->RemoveNode(-1);
            }
            testUser->GetCurrentHands()->RetrieveNode(0)->data->GetPlayerCards()->RemoveNode(-1);
            testUser->GetCurrentHands()->RetrieveNode(0)->data->GetPlayerCards()->RemoveNode(-1);
            testUser->GetCurrentHands()->RetrieveNode(0)->data->AddHandTotal();
        }
        // Player has two aces
        {
            // Add cards to player hand, set wager
            testUser->GetCurrentHands()->ClearList();
            testCard = std::make_shared<Card>(Ranks[0], Suits[0]);
            testNode = dealerHand->GetPlayerCards()->InitNode(testCard);
            userHand->AddCardToHand(testNode);
            testCard = std::make_shared<Card>(Ranks[0], Suits[0]);
            testNode = dealerHand->GetPlayerCards()->InitNode(testCard);
            userHand->AddCardToHand(testNode);
            testUser->SetCurrentHands(userHand);
            testUser->GetCurrentHands()->RetrieveNode(0)->data->SetWager(10);
            for (int i = 0; i < 13; i++) {
                // Add card to dealer hand
                testDealer->GetCurrentHands()->ClearList();
                testCard = std::make_shared<Card>(Ranks[i], Suits[0]);
                testNode = dealerHand->GetPlayerCards()->InitNode(testCard);
                dealerHand->SetPlayerCards(testNode);
                testDealer->SetCurrentHands(dealerHand);
                // Can split
                {
                    // Test strategy
                    blackjack_strategy(testUser, testUser->GetCurrentHands()->RetrieveNode(0)->data, testDealer, false, false);
                    EXPECT_FALSE(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][0]));
                    EXPECT_FALSE(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][1]));
                    EXPECT_TRUE(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][2]));
                    EXPECT_FALSE(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][3]));
                    testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->ClearHashTable();
                }
                // Can't split
                {
                    testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->AddToTable(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[4][0]);
                    // Test strategy
                    blackjack_strategy(testUser, testUser->GetCurrentHands()->RetrieveNode(0)->data, testDealer, false, false);
                    if ((i >= 1 && i <= 2) || (i == 0 || i >= 6)) {
                        EXPECT_FALSE(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][0]));
                        EXPECT_TRUE(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][1]));
                        EXPECT_FALSE(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][2]));
                        EXPECT_FALSE(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][3]));
                    }
                    else {
                        EXPECT_FALSE(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][0]));
                        EXPECT_FALSE(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][1]));
                        EXPECT_FALSE(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][2]));
                        EXPECT_TRUE(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][3]));
                    }
                    testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->RemoveElement(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[4][0]);
                    testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->ClearHashTable();
                }
                testDealer->GetCurrentHands()->RetrieveNode(0)->data->GetPlayerCards()->RemoveNode(-1);
            }
            testUser->GetCurrentHands()->RetrieveNode(0)->data->GetPlayerCards()->RemoveNode(-1);
            testUser->GetCurrentHands()->RetrieveNode(0)->data->GetPlayerCards()->RemoveNode(-1);
            testUser->GetCurrentHands()->RetrieveNode(0)->data->AddHandTotal();
        }
    }
    // Player card total is 14 (seven, seven) 
    {
        // Add cards to player hand, set wager
            testUser->GetCurrentHands()->ClearList();
            testCard = std::make_shared<Card>(Ranks[6], Suits[0]);
            testNode = dealerHand->GetPlayerCards()->InitNode(testCard);
            userHand->AddCardToHand(testNode);
            testCard = std::make_shared<Card>(Ranks[6], Suits[0]);
            testNode = dealerHand->GetPlayerCards()->InitNode(testCard);
            userHand->AddCardToHand(testNode);
            testUser->SetCurrentHands(userHand);
            testUser->GetCurrentHands()->RetrieveNode(0)->data->SetWager(10);
        for (int i = 0; i < 13; i++) {
            // Add card to dealer hand
            testDealer->GetCurrentHands()->ClearList();
            testCard = std::make_shared<Card>(Ranks[i], Suits[0]);
            testNode = dealerHand->GetPlayerCards()->InitNode(testCard);
            dealerHand->SetPlayerCards(testNode);
            testDealer->SetCurrentHands(dealerHand);
            // Can split
            {
                // Test strategy
                blackjack_strategy(testUser, testUser->GetCurrentHands()->RetrieveNode(0)->data, testDealer, false, false);
                if (i >= 1 && i <= 6) {
                    EXPECT_FALSE(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][0]));
                    EXPECT_FALSE(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][1]));
                    EXPECT_TRUE(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][2]));
                    EXPECT_FALSE(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][3]));
                }
                else if (i == 7) {
                    EXPECT_FALSE(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][0]));
                    EXPECT_TRUE(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][1]));
                    EXPECT_TRUE(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][2]));
                    EXPECT_FALSE(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][3]));
                }
                else {
                    EXPECT_FALSE(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][0]));
                    EXPECT_TRUE(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][1]));
                    EXPECT_FALSE(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][2]));
                    EXPECT_FALSE(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][3]));
                }
                testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->ClearHashTable();
            }
            // Can't split
            {
                testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->AddToTable(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[4][1]);
                // Test strategy
                blackjack_strategy(testUser, testUser->GetCurrentHands()->RetrieveNode(0)->data, testDealer, false, false);
                if (i >= 1 && i <= 5) {
                    EXPECT_FALSE(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][0]));
                    EXPECT_FALSE(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][1]));
                    EXPECT_FALSE(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][2]));
                    EXPECT_TRUE(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][3]));
                }
                else {
                    EXPECT_FALSE(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][0]));
                    EXPECT_TRUE(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][1]));
                    EXPECT_FALSE(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][2]));
                    EXPECT_FALSE(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][3]));
                }
                testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->RemoveElement(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[4][1]);
                testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->ClearHashTable();
            }
            testDealer->GetCurrentHands()->RetrieveNode(0)->data->GetPlayerCards()->RemoveNode(-1);
        }
        testUser->GetCurrentHands()->RetrieveNode(0)->data->GetPlayerCards()->RemoveNode(-1);
        testUser->GetCurrentHands()->RetrieveNode(0)->data->GetPlayerCards()->RemoveNode(-1);
        testUser->GetCurrentHands()->RetrieveNode(0)->data->AddHandTotal();
    }
    // Player card total is 16 (eight, eight)
    {
        // Add cards to player hand, set wager
        testUser->GetCurrentHands()->ClearList();
        testCard = std::make_shared<Card>(Ranks[7], Suits[0]);
        testNode = dealerHand->GetPlayerCards()->InitNode(testCard);
        userHand->AddCardToHand(testNode);
        testCard = std::make_shared<Card>(Ranks[7], Suits[0]);
        testNode = dealerHand->GetPlayerCards()->InitNode(testCard);
        userHand->AddCardToHand(testNode);
        testUser->SetCurrentHands(userHand);
        testUser->GetCurrentHands()->RetrieveNode(0)->data->SetWager(10);
        for (int i = 0; i < 13; i++) {
            // Add card to dealer hand
            testDealer->GetCurrentHands()->ClearList();
            testCard = std::make_shared<Card>(Ranks[i], Suits[0]);
            testNode = dealerHand->GetPlayerCards()->InitNode(testCard);
            dealerHand->SetPlayerCards(testNode);
            testDealer->SetCurrentHands(dealerHand);
            // Can split
            {
                // Test strategy
                blackjack_strategy(testUser, testUser->GetCurrentHands()->RetrieveNode(0)->data, testDealer, false, false);
                EXPECT_FALSE(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][0]));
                EXPECT_FALSE(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][1]));
                EXPECT_TRUE(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][2]));
                EXPECT_FALSE(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][3]));       
                testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->ClearHashTable();         
            }
            // Can't split
            {
                testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->AddToTable(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[4][1]);
                // Test strategy
                blackjack_strategy(testUser, testUser->GetCurrentHands()->RetrieveNode(0)->data, testDealer, false, false);
                if (i >= 1 && i <= 5) {
                    EXPECT_FALSE(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][0]));
                    EXPECT_FALSE(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][1]));
                    EXPECT_FALSE(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][2]));
                    EXPECT_TRUE(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][3]));
                }
                else {
                    EXPECT_FALSE(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][0]));
                    EXPECT_TRUE(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][1]));
                    EXPECT_FALSE(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][2]));
                    EXPECT_FALSE(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][3]));
                }
                testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->RemoveElement(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[4][1]);
                testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->ClearHashTable();
            }
            testDealer->GetCurrentHands()->RetrieveNode(0)->data->GetPlayerCards()->RemoveNode(-1);
        }
        testUser->GetCurrentHands()->RetrieveNode(0)->data->GetPlayerCards()->RemoveNode(-1);
        testUser->GetCurrentHands()->RetrieveNode(0)->data->GetPlayerCards()->RemoveNode(-1);
        testUser->GetCurrentHands()->RetrieveNode(0)->data->AddHandTotal();
    }
    // Player card total is 18 (nine, nine)
    {
        // Add cards to player hand, set wager
        testUser->GetCurrentHands()->ClearList();
        testCard = std::make_shared<Card>(Ranks[8], Suits[0]);
        testNode = dealerHand->GetPlayerCards()->InitNode(testCard);
        userHand->AddCardToHand(testNode);
        testCard = std::make_shared<Card>(Ranks[8], Suits[0]);
        testNode = dealerHand->GetPlayerCards()->InitNode(testCard);
        userHand->AddCardToHand(testNode);
        testUser->SetCurrentHands(userHand);
        testUser->GetCurrentHands()->RetrieveNode(0)->data->SetWager(10);
        for (int i = 0; i < 13; i++) {
            // Add card to dealer hand
            testDealer->GetCurrentHands()->ClearList();
            testCard = std::make_shared<Card>(Ranks[i], Suits[0]);
            testNode = dealerHand->GetPlayerCards()->InitNode(testCard);
            dealerHand->SetPlayerCards(testNode);
            testDealer->SetCurrentHands(dealerHand);
            // Can split
            {
                // Test strategy
                blackjack_strategy(testUser, testUser->GetCurrentHands()->RetrieveNode(0)->data, testDealer, false, false); 
                if (i == 0 || i == 6 || i >= 9) {
                    EXPECT_FALSE(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][0]));
                    EXPECT_FALSE(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][1]));
                    EXPECT_FALSE(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][2]));
                    EXPECT_TRUE(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][3]));
                }
                else {
                    EXPECT_FALSE(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][0]));
                    EXPECT_FALSE(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][1]));
                    EXPECT_TRUE(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][2]));
                    EXPECT_FALSE(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][3]));
                }
                testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->ClearHashTable();
            }
            // Can't split
            {
                testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->AddToTable(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[4][1]);
                // Test strategy
                blackjack_strategy(testUser, testUser->GetCurrentHands()->RetrieveNode(0)->data, testDealer, false, false);
                EXPECT_FALSE(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][0]));
                EXPECT_FALSE(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][1]));
                EXPECT_FALSE(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][2]));
                EXPECT_TRUE(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][3]));                
                testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->RemoveElement(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[4][1]);
                testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->ClearHashTable();
            }
            testDealer->GetCurrentHands()->RetrieveNode(0)->data->GetPlayerCards()->RemoveNode(-1);
        }
        testUser->GetCurrentHands()->RetrieveNode(0)->data->GetPlayerCards()->RemoveNode(-1);
        testUser->GetCurrentHands()->RetrieveNode(0)->data->GetPlayerCards()->RemoveNode(-1);
        testUser->GetCurrentHands()->RetrieveNode(0)->data->AddHandTotal();
    }
    // Player card total is 20 (face, face)
    {
        // Add cards to player hand, set wager
        for (int i = 9; i <= 12; i++) {
            testUser->GetCurrentHands()->ClearList();
            testCard = std::make_shared<Card>(Ranks[i], Suits[0]);
            testNode = dealerHand->GetPlayerCards()->InitNode(testCard);
            userHand->AddCardToHand(testNode);
            testCard = std::make_shared<Card>(Ranks[i], Suits[0]);
            testNode = dealerHand->GetPlayerCards()->InitNode(testCard);
            userHand->AddCardToHand(testNode);
            testUser->SetCurrentHands(userHand);
            testUser->GetCurrentHands()->RetrieveNode(0)->data->SetWager(10);
            for (int j = 0; j < 13; j++) {
                // Add card to dealer hand
                testDealer->GetCurrentHands()->ClearList();
                testCard = std::make_shared<Card>(Ranks[i], Suits[0]);
                testNode = dealerHand->GetPlayerCards()->InitNode(testCard);
                dealerHand->SetPlayerCards(testNode);
                testDealer->SetCurrentHands(dealerHand);
                // Can split
                {
                    // Test strategy
                    blackjack_strategy(testUser, testUser->GetCurrentHands()->RetrieveNode(0)->data, testDealer, false, false);
                    EXPECT_FALSE(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][0]));
                    EXPECT_FALSE(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][1]));
                    EXPECT_FALSE(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][2]));
                    EXPECT_TRUE(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][3]));
                    testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->ClearHashTable();
                }
                // Can't split
                {
                    testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->AddToTable(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[4][1]);
                    // Test strategy
                    blackjack_strategy(testUser, testUser->GetCurrentHands()->RetrieveNode(0)->data, testDealer, false, false);
                    EXPECT_FALSE(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][0]));
                    EXPECT_FALSE(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][1]));
                    EXPECT_FALSE(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][2]));
                    EXPECT_TRUE(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[3][3])); 
                    testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->RemoveElement(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[4][1]);    
                    testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->ClearHashTable();               
                }
                testDealer->GetCurrentHands()->RetrieveNode(0)->data->GetPlayerCards()->RemoveNode(-1);
            }
            testUser->GetCurrentHands()->RetrieveNode(0)->data->GetPlayerCards()->RemoveNode(-1);
            testUser->GetCurrentHands()->RetrieveNode(0)->data->GetPlayerCards()->RemoveNode(-1);
            testUser->GetCurrentHands()->RetrieveNode(0)->data->AddHandTotal();
        }
    }
}

// Split hand linked list check
TEST_F(test_x, SplitHandLinkedListCheck) {
    std::shared_ptr<Player> testPlayer(new Player());
    std::shared_ptr<Hand> testHand(new Hand);
    std::shared_ptr<Card> testCard(new Card);
    std::shared_ptr<node<Card>> testNode;
    testPlayer->SetBankTotal(100);
    testHand->SetWager(10);
    testCard = std::make_shared<Card>(Ranks[0], Suits[0]);
    testNode = testHand->GetPlayerCards()->InitNode(testCard);
    testHand->SetPlayerCards(testNode);
    testCard = std::make_shared<Card>(Ranks[12], Suits[1]);
    testNode = testHand->GetPlayerCards()->InitNode(testCard);
    testHand->SetPlayerCards(testNode);
    EXPECT_EQ(testHand->GetPlayerCards()->GetSize(), 2);
    testPlayer->SetCurrentHands(testHand);
    testPlayer->GetCurrentHands()->RetrieveNode(0)->data->PlaceWagerSim(testPlayer->GetBankTotal(), 10);
    EXPECT_EQ(testPlayer->GetBankTotal(), 90);
    split_hand(testPlayer);
    EXPECT_EQ(testPlayer->GetBankTotal(), 80);
    EXPECT_EQ(testPlayer->GetCurrentHands()->GetSize(), 2);
    EXPECT_EQ(testPlayer->GetCurrentHandsPossessed(), testPlayer->GetCurrentHands()->GetSize());
    EXPECT_EQ(testPlayer->GetCurrentHands()->RetrieveNode(0)->data->GetPlayerCards()->GetSize(), 1);
    EXPECT_EQ(testPlayer->GetCurrentHands()->RetrieveNode(0)->data->GetPlayerCards()->RetrieveNode(0)->data.GetRank(), Ranks[0]);
    EXPECT_EQ(testPlayer->GetCurrentHands()->RetrieveNode(0)->data->GetPlayerCards()->RetrieveNode(0)->data.GetSuit(), Suits[0]);
    EXPECT_EQ(testPlayer->GetCurrentHands()->RetrieveNode(0)->data->GetPlayerCards()->RetrieveNode(0)->data.GetCardValue(), 11);
    EXPECT_EQ(testPlayer->GetCurrentHands()->RetrieveNode(0)->data->GetWager(), 10);
    EXPECT_EQ(testPlayer->GetCurrentHands()->RetrieveNode(-1)->data->GetPlayerCards()->GetSize(), 1);
    EXPECT_EQ(testPlayer->GetCurrentHands()->RetrieveNode(-1)->data->GetPlayerCards()->RetrieveNode(0)->data.GetRank(), Ranks[12]);
    EXPECT_EQ(testPlayer->GetCurrentHands()->RetrieveNode(-1)->data->GetPlayerCards()->RetrieveNode(0)->data.GetSuit(), Suits[1]);
    EXPECT_EQ(testPlayer->GetCurrentHands()->RetrieveNode(-1)->data->GetPlayerCards()->RetrieveNode(0)->data.GetCardValue(), 10);
    EXPECT_EQ(testPlayer->GetCurrentHands()->RetrieveNode(-1)->data->GetWager(), 10);
}

// Same rank check test
TEST_F(test_x, SameRankCheck) {
    for (int i = 0; i < 10; i++) {
        std::shared_ptr<Player> testUser(new Player());
        std::shared_ptr<Player> testDealer(new Player());
        std::shared_ptr<Shoe> testShoe(new Shoe);
        std::shared_ptr<Shoe> copyShoe(new Shoe);
        std::shared_ptr<Card> testCard(new Card);
        std::shared_ptr<node<Card>> testNode;
        float priorBank = 100;
        float handWager = 10;
        testUser->SetName("Borby");
        testDealer->SetName("Dealer");
        testUser->SetBankTotal(priorBank);
        // Check for splitting Aces
        testCard = std::make_shared<Card>(Ranks[12], Suits[3]);
        testNode = testShoe->GetCardsInShoe()->InitNode(testCard);
        testShoe->GetCardsInShoe()->AppendNode(testNode);
        testCard = std::make_shared<Card>(Ranks[12], Suits[1]);
        testNode = testShoe->GetCardsInShoe()->InitNode(testCard);
        testShoe->GetCardsInShoe()->AppendNode(testNode);
        testCard = std::make_shared<Card>(Ranks[7], Suits[3]);
        testNode = testShoe->GetCardsInShoe()->InitNode(testCard);
        testShoe->GetCardsInShoe()->AppendNode(testNode);
        testCard = std::make_shared<Card>(Ranks[0], Suits[2]);
        testNode = testShoe->GetCardsInShoe()->InitNode(testCard);
        testShoe->GetCardsInShoe()->AppendNode(testNode);
        testCard = std::make_shared<Card>(Ranks[7], Suits[1]);
        testNode = testShoe->GetCardsInShoe()->InitNode(testCard);
        testShoe->GetCardsInShoe()->AppendNode(testNode);
        testCard = std::make_shared<Card>(Ranks[0], Suits[0]);
        testNode = testShoe->GetCardsInShoe()->InitNode(testCard);
        testShoe->GetCardsInShoe()->AppendNode(testNode);
        copyShoe->CopyShoe(testShoe);
        // Player chooses to split
        while (handWager <= priorBank) {
            deal_hand_sim(testUser, testDealer, testShoe, handWager);
            same_rank_check_sim(testUser, testDealer, testShoe, true);
            // Player is eligible to split
            if (testUser->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[1][3])) {
                EXPECT_EQ(testUser->GetCurrentHands()->GetSize(), 2);
                EXPECT_EQ(testUser->GetCurrentHandsPossessed(), testUser->GetCurrentHands()->GetSize());
                for (int i = 0; i < testUser->GetCurrentHands()->GetSize(); i++) {
                    EXPECT_EQ(testUser->GetCurrentHands()->RetrieveNode(i)->data->GetPlayerCards()->GetSize(), 2);
                    EXPECT_EQ(testUser->GetCurrentHands()->RetrieveNode(i)->data->GetWager(), handWager);
                    EXPECT_EQ(testUser->GetBankTotal(), priorBank - 2 * testUser->GetCurrentHands()->RetrieveNode(i)->data->GetWager());
                    EXPECT_EQ(testUser->GetCurrentHands()->RetrieveNode(i)->data->GetCardsTotal(), 21);
                    EXPECT_EQ(testDealer->GetCurrentHands()->GetSize(), 1);
                    EXPECT_EQ(testDealer->GetCurrentHands()->RetrieveNode(0)->data->GetPlayerCards()->GetSize(), 2);
                    EXPECT_EQ(testShoe->GetCardsInShoe()->GetSize(), 0);
                }
            }
            // Player cannot split
            else {
                EXPECT_EQ(testUser->GetCurrentHands()->GetSize(), 1);
                EXPECT_EQ(testUser->GetCurrentHandsPossessed(), testUser->GetCurrentHands()->GetSize());
                for (int i = 0; i < testUser->GetCurrentHands()->GetSize(); i++) {
                    EXPECT_EQ(testUser->GetCurrentHands()->RetrieveNode(i)->data->GetPlayerCards()->GetSize(), 2);
                    EXPECT_EQ(testUser->GetCurrentHands()->RetrieveNode(i)->data->GetWager(), handWager);
                    EXPECT_EQ(testUser->GetBankTotal(), priorBank - testUser->GetCurrentHands()->RetrieveNode(i)->data->GetWager());
                    EXPECT_EQ(testUser->GetCurrentHands()->RetrieveNode(i)->data->GetCardsTotal(), 12);
                    EXPECT_EQ(testDealer->GetCurrentHands()->GetSize(), 1);
                    EXPECT_EQ(testDealer->GetCurrentHands()->RetrieveNode(0)->data->GetPlayerCards()->GetSize(), 2);
                    EXPECT_EQ(testShoe->GetCardsInShoe()->GetSize(), 2);
                }
            }
            testUser->SetBankTotal(priorBank);
            testUser->ResetPlayer();
            testDealer->ResetPlayer();
            testShoe->EmptyShoe();
            testShoe->CopyShoe(copyShoe);
            handWager++;
        }
        // Player chooses not to split
        {
            deal_hand_sim(testUser, testDealer, testShoe, handWager);
            same_rank_check_sim(testUser, testDealer, testShoe, false);
            EXPECT_EQ(testUser->GetCurrentHands()->GetSize(), 1);
            EXPECT_EQ(testUser->GetCurrentHandsPossessed(), testUser->GetCurrentHands()->GetSize());
            for (int i = 0; i < testUser->GetCurrentHands()->GetSize(); i++) {
                EXPECT_EQ(testUser->GetCurrentHands()->RetrieveNode(i)->data->GetPlayerCards()->GetSize(), 2);
                EXPECT_EQ(testUser->GetCurrentHands()->RetrieveNode(i)->data->GetWager(), handWager);
                EXPECT_EQ(testUser->GetBankTotal(), priorBank - testUser->GetCurrentHands()->RetrieveNode(i)->data->GetWager());
                EXPECT_EQ(testUser->GetCurrentHands()->RetrieveNode(i)->data->GetCardsTotal(), 12);
                EXPECT_EQ(testDealer->GetCurrentHands()->GetSize(), 1);
                EXPECT_EQ(testDealer->GetCurrentHands()->RetrieveNode(0)->data->GetPlayerCards()->GetSize(), 2);
            }
            EXPECT_EQ(testShoe->GetCardsInShoe()->GetSize(), 2);
        }
        testUser->ResetPlayer();
        testDealer->ResetPlayer();
        testShoe->EmptyShoe();
        testUser->SetBankTotal(priorBank);
        handWager = 10;
        // Random Number Generator
        int rankVal = random_int(1, 12);
        int dealerFirst = random_int(1, 12);
        int dealerSecond = random_int(1, 12);
        // Check for splitting hand
        testCard = std::make_shared<Card>(Ranks[rankVal], Suits[0]);
        testNode = testShoe->GetCardsInShoe()->InitNode(testCard);
        testShoe->GetCardsInShoe()->AppendNode(testNode);
        testCard = std::make_shared<Card>(Ranks[rankVal], Suits[1]);
        testNode = testShoe->GetCardsInShoe()->InitNode(testCard);
        testShoe->GetCardsInShoe()->AppendNode(testNode);
        testCard = std::make_shared<Card>(Ranks[rankVal], Suits[2]);
        testNode = testShoe->GetCardsInShoe()->InitNode(testCard);
        testShoe->GetCardsInShoe()->AppendNode(testNode);
        testCard = std::make_shared<Card>(Ranks[rankVal], Suits[3]);
        testNode = testShoe->GetCardsInShoe()->InitNode(testCard);
        testShoe->GetCardsInShoe()->AppendNode(testNode);
        testCard = std::make_shared<Card>(Ranks[dealerSecond], Suits[3]);
        testNode = testShoe->GetCardsInShoe()->InitNode(testCard);
        testShoe->GetCardsInShoe()->AppendNode(testNode);
        testCard = std::make_shared<Card>(Ranks[rankVal], Suits[2]);
        testNode = testShoe->GetCardsInShoe()->InitNode(testCard);
        testShoe->GetCardsInShoe()->AppendNode(testNode);
        testCard = std::make_shared<Card>(Ranks[dealerFirst], Suits[1]);
        testNode = testShoe->GetCardsInShoe()->InitNode(testCard);
        testShoe->GetCardsInShoe()->AppendNode(testNode);
        testCard = std::make_shared<Card>(Ranks[rankVal], Suits[0]);
        testNode = testShoe->GetCardsInShoe()->InitNode(testCard);
        testShoe->GetCardsInShoe()->AppendNode(testNode);
        copyShoe->CopyShoe(testShoe);
        // Max hands split check
        while (handWager <= priorBank) {
            // Player has chosen to split their hand
            {
                deal_hand_sim(testUser, testDealer, testShoe, handWager);
                EXPECT_EQ(testUser->GetCurrentHands()->GetSize(), 1);
                EXPECT_EQ(testUser->GetCurrentHands()->GetSize(), testUser->GetCurrentHandsPossessed());
                EXPECT_EQ(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetPlayerCards()->GetSize(), 2);
                EXPECT_EQ(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetWager(), handWager);
                EXPECT_EQ(testUser->GetBankTotal(), priorBank - testUser->GetCurrentHands()->RetrieveNode(0)->data->GetWager());
                same_rank_check_sim(testUser, testDealer, testShoe, true);
                EXPECT_EQ(testUser->GetCurrentHands()->GetSize(), testUser->GetCurrentHandsPossessed());
                // Player has split hands
                if (testUser->GetCurrentHandsPossessed() > 1) {
                    if (handWager <= 0.2 * priorBank) {
                        EXPECT_EQ(testUser->GetCurrentHands()->GetSize(), 5);
                        EXPECT_EQ(testUser->GetCurrentHandsPossessed(), testUser->GetCurrentHands()->GetSize());
                    }
                    else if (handWager > 0.2 * priorBank && handWager <= 0.25 * priorBank) {
                        EXPECT_EQ(testUser->GetCurrentHands()->GetSize(), 4);
                        EXPECT_EQ(testUser->GetCurrentHandsPossessed(), testUser->GetCurrentHands()->GetSize());
                    }
                    else if (handWager > 0.25 * priorBank && handWager <= 0.33 * priorBank) {
                        EXPECT_EQ(testUser->GetCurrentHands()->GetSize(), 3);
                        EXPECT_EQ(testUser->GetCurrentHandsPossessed(), testUser->GetCurrentHands()->GetSize());
                    }
                    else if (handWager > 0.33 * priorBank && handWager <= 0.5 * priorBank) {
                        EXPECT_EQ(testUser->GetCurrentHands()->GetSize(), 2);
                        EXPECT_EQ(testUser->GetCurrentHandsPossessed(), testUser->GetCurrentHands()->GetSize());
                    }
                }
                // Player does not have split hands
                else {
                    EXPECT_EQ(testUser->GetCurrentHands()->GetSize(), 1);
                    EXPECT_EQ(testUser->GetCurrentHandsPossessed(), testUser->GetCurrentHands()->GetSize());
                }
            for (int i = 0; i < testUser->GetCurrentHands()->GetSize(); i++) {
                if (i == 0) {
                    EXPECT_EQ(testUser->GetCurrentHands()->RetrieveNode(i)->data->GetPlayerCards()->GetSize(), 2);
                }
                else {
                    EXPECT_EQ(testUser->GetCurrentHands()->RetrieveNode(i)->data->GetPlayerCards()->GetSize(), 1);
                }
                EXPECT_EQ(testUser->GetCurrentHands()->RetrieveNode(i)->data->GetWager(), handWager);
            }
            EXPECT_EQ(testUser->GetBankTotal(), priorBank - testUser->GetCurrentHandsPossessed() * handWager);
            testUser->SetBankTotal(priorBank);
            testUser->ResetPlayer();
            testDealer->ResetPlayer();
            testShoe->EmptyShoe();
            testShoe->CopyShoe(copyShoe);
            }
            // Player has chosen to not split their hand
            {
                deal_hand_sim(testUser, testDealer, testShoe, handWager);
                EXPECT_EQ(testUser->GetCurrentHands()->GetSize(), 1);
                EXPECT_EQ(testUser->GetCurrentHands()->GetSize(), testUser->GetCurrentHandsPossessed());
                EXPECT_EQ(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetPlayerCards()->GetSize(), 2);
                EXPECT_EQ(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetWager(), handWager);
                EXPECT_EQ(testUser->GetBankTotal(), priorBank - testUser->GetCurrentHands()->RetrieveNode(0)->data->GetWager());
                same_rank_check_sim(testUser, testDealer, testShoe, true);
                EXPECT_EQ(testUser->GetCurrentHands()->GetSize(), testUser->GetCurrentHandsPossessed());
                for (int i = 0; i < testUser->GetCurrentHands()->GetSize(); i++) {
                    if (i == 0) {
                        EXPECT_EQ(testUser->GetCurrentHands()->RetrieveNode(i)->data->GetPlayerCards()->GetSize(), 2);
                    }
                    else {
                        EXPECT_EQ(testUser->GetCurrentHands()->RetrieveNode(i)->data->GetPlayerCards()->GetSize(), 1);
                    }
                    EXPECT_EQ(testUser->GetCurrentHands()->RetrieveNode(i)->data->GetWager(), handWager);
                }
                EXPECT_EQ(testUser->GetBankTotal(), priorBank - testUser->GetCurrentHandsPossessed() * handWager);
                testUser->SetBankTotal(priorBank);
                testUser->ResetPlayer();
                testDealer->ResetPlayer();
                testShoe->EmptyShoe();
                testShoe->CopyShoe(copyShoe);
            }
            handWager++;
        }
        testShoe->EmptyShoe();
        handWager = 10;
        // Random Number Generator
        rankVal = random_int(1, 12);
        dealerFirst = random_int(1, 12);
        dealerSecond = random_int(1, 12);
        // Check for splitting hand
        testCard = std::make_shared<Card>(Ranks[rankVal - 1], Suits[1]);
        testNode = testShoe->GetCardsInShoe()->InitNode(testCard);
        testShoe->GetCardsInShoe()->AppendNode(testNode);
        testCard = std::make_shared<Card>(Ranks[rankVal], Suits[2]);
        testNode = testShoe->GetCardsInShoe()->InitNode(testCard);
        testShoe->GetCardsInShoe()->AppendNode(testNode);
        testCard = std::make_shared<Card>(Ranks[rankVal], Suits[3]);
        testNode = testShoe->GetCardsInShoe()->InitNode(testCard);
        testShoe->GetCardsInShoe()->AppendNode(testNode);
        testCard = std::make_shared<Card>(Ranks[dealerSecond], Suits[3]);
        testNode = testShoe->GetCardsInShoe()->InitNode(testCard);
        testShoe->GetCardsInShoe()->AppendNode(testNode);
        testCard = std::make_shared<Card>(Ranks[rankVal], Suits[2]);
        testNode = testShoe->GetCardsInShoe()->InitNode(testCard);
        testShoe->GetCardsInShoe()->AppendNode(testNode);
        testCard = std::make_shared<Card>(Ranks[dealerFirst], Suits[1]);
        testNode = testShoe->GetCardsInShoe()->InitNode(testCard);
        testShoe->GetCardsInShoe()->AppendNode(testNode);
        testCard = std::make_shared<Card>(Ranks[rankVal], Suits[0]);
        testNode = testShoe->GetCardsInShoe()->InitNode(testCard);
        testShoe->GetCardsInShoe()->AppendNode(testNode);
        copyShoe->CopyShoe(testShoe);
        // Max hands split check
        while (handWager <= priorBank) {
            // Player has chosen to split their hand
            {
                deal_hand_sim(testUser, testDealer, testShoe, handWager);
                EXPECT_EQ(testUser->GetCurrentHands()->GetSize(), 1);
                EXPECT_EQ(testUser->GetCurrentHands()->GetSize(), testUser->GetCurrentHandsPossessed());
                EXPECT_EQ(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetPlayerCards()->GetSize(), 2);
                EXPECT_EQ(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetWager(), handWager);
                EXPECT_EQ(testUser->GetBankTotal(), priorBank - testUser->GetCurrentHands()->RetrieveNode(0)->data->GetWager());
                same_rank_check_sim(testUser, testDealer, testShoe, true);
                EXPECT_EQ(testUser->GetCurrentHands()->GetSize(), testUser->GetCurrentHandsPossessed());
                // Player has split hands
                if (testUser->GetCurrentHandsPossessed() > 1) {
                    if (handWager <= 0.2 * priorBank) {
                        EXPECT_EQ(testUser->GetCurrentHands()->GetSize(), 4);
                        EXPECT_EQ(testUser->GetCurrentHandsPossessed(), testUser->GetCurrentHands()->GetSize());
                    }
                    else if (handWager > 0.2 * priorBank && handWager <= 0.25 * priorBank) {
                        EXPECT_EQ(testUser->GetCurrentHands()->GetSize(), 4);
                        EXPECT_EQ(testUser->GetCurrentHandsPossessed(), testUser->GetCurrentHands()->GetSize());
                    }
                    else if (handWager > 0.25 * priorBank && handWager <= 0.33 * priorBank) {
                        EXPECT_EQ(testUser->GetCurrentHands()->GetSize(), 3);
                        EXPECT_EQ(testUser->GetCurrentHandsPossessed(), testUser->GetCurrentHands()->GetSize());
                    }
                    else if (handWager > 0.33 * priorBank && handWager <= 0.5 * priorBank) {
                        EXPECT_EQ(testUser->GetCurrentHands()->GetSize(), 2);
                        EXPECT_EQ(testUser->GetCurrentHandsPossessed(), testUser->GetCurrentHands()->GetSize());
                    }
                }
                // Player does not have split hands
                else {
                    EXPECT_EQ(testUser->GetCurrentHands()->GetSize(), 1);
                    EXPECT_EQ(testUser->GetCurrentHandsPossessed(), testUser->GetCurrentHands()->GetSize());
                }
            for (int i = 0; i < testUser->GetCurrentHands()->GetSize(); i++) {
                if (i == 0) {
                    EXPECT_EQ(testUser->GetCurrentHands()->RetrieveNode(i)->data->GetPlayerCards()->GetSize(), 2);
                }
                else {
                    EXPECT_EQ(testUser->GetCurrentHands()->RetrieveNode(i)->data->GetPlayerCards()->GetSize(), 1);
                }
                EXPECT_EQ(testUser->GetCurrentHands()->RetrieveNode(i)->data->GetWager(), handWager);
            }
            EXPECT_EQ(testUser->GetBankTotal(), priorBank - testUser->GetCurrentHandsPossessed() * handWager);
            testUser->SetBankTotal(priorBank);
            testUser->ResetPlayer();
            testDealer->ResetPlayer();
            testShoe->EmptyShoe();
            testShoe->CopyShoe(copyShoe);
            }
            // Player has chosen to not split their hand
            {
                deal_hand_sim(testUser, testDealer, testShoe, handWager);
                EXPECT_EQ(testUser->GetCurrentHands()->GetSize(), 1);
                EXPECT_EQ(testUser->GetCurrentHands()->GetSize(), testUser->GetCurrentHandsPossessed());
                EXPECT_EQ(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetPlayerCards()->GetSize(), 2);
                EXPECT_EQ(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetWager(), handWager);
                EXPECT_EQ(testUser->GetBankTotal(), priorBank - testUser->GetCurrentHands()->RetrieveNode(0)->data->GetWager());
                same_rank_check_sim(testUser, testDealer, testShoe, true);
                EXPECT_EQ(testUser->GetCurrentHands()->GetSize(), testUser->GetCurrentHandsPossessed());
                for (int i = 0; i < testUser->GetCurrentHands()->GetSize(); i++) {
                    if (i == 0) {
                        EXPECT_EQ(testUser->GetCurrentHands()->RetrieveNode(i)->data->GetPlayerCards()->GetSize(), 2);
                    }
                    else {
                        EXPECT_EQ(testUser->GetCurrentHands()->RetrieveNode(i)->data->GetPlayerCards()->GetSize(), 1);
                    }
                    EXPECT_EQ(testUser->GetCurrentHands()->RetrieveNode(i)->data->GetWager(), handWager);
                }
                EXPECT_EQ(testUser->GetBankTotal(), priorBank - testUser->GetCurrentHandsPossessed() * handWager);
                testUser->SetBankTotal(priorBank);
                testUser->ResetPlayer();
                testDealer->ResetPlayer();
                testShoe->EmptyShoe();
                testShoe->CopyShoe(copyShoe);
            }
            handWager++;
        }
        testShoe->EmptyShoe();
        handWager = 10;
        // Random Number Generator
        rankVal = random_int(1, 12);
        dealerFirst = random_int(1, 12);
        dealerSecond = random_int(1, 12);
        // Check for splitting hand
        testCard = std::make_shared<Card>(Ranks[rankVal - 1], Suits[2]);
        testNode = testShoe->GetCardsInShoe()->InitNode(testCard);
        testShoe->GetCardsInShoe()->AppendNode(testNode);
        testCard = std::make_shared<Card>(Ranks[rankVal], Suits[3]);
        testNode = testShoe->GetCardsInShoe()->InitNode(testCard);
        testShoe->GetCardsInShoe()->AppendNode(testNode);
        testCard = std::make_shared<Card>(Ranks[dealerSecond], Suits[3]);
        testNode = testShoe->GetCardsInShoe()->InitNode(testCard);
        testShoe->GetCardsInShoe()->AppendNode(testNode);
        testCard = std::make_shared<Card>(Ranks[rankVal], Suits[2]);
        testNode = testShoe->GetCardsInShoe()->InitNode(testCard);
        testShoe->GetCardsInShoe()->AppendNode(testNode);
        testCard = std::make_shared<Card>(Ranks[dealerFirst], Suits[1]);
        testNode = testShoe->GetCardsInShoe()->InitNode(testCard);
        testShoe->GetCardsInShoe()->AppendNode(testNode);
        testCard = std::make_shared<Card>(Ranks[rankVal], Suits[0]);
        testNode = testShoe->GetCardsInShoe()->InitNode(testCard);
        testShoe->GetCardsInShoe()->AppendNode(testNode);
        copyShoe->CopyShoe(testShoe);
        // Max hands split check
        while (handWager <= priorBank) {
            // Player has chosen to split their hand
            {
                deal_hand_sim(testUser, testDealer, testShoe, handWager);
                EXPECT_EQ(testUser->GetCurrentHands()->GetSize(), 1);
                EXPECT_EQ(testUser->GetCurrentHands()->GetSize(), testUser->GetCurrentHandsPossessed());
                EXPECT_EQ(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetPlayerCards()->GetSize(), 2);
                EXPECT_EQ(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetWager(), handWager);
                EXPECT_EQ(testUser->GetBankTotal(), priorBank - testUser->GetCurrentHands()->RetrieveNode(0)->data->GetWager());
                same_rank_check_sim(testUser, testDealer, testShoe, true);
                EXPECT_EQ(testUser->GetCurrentHands()->GetSize(), testUser->GetCurrentHandsPossessed());
                // Player has split hands
                if (testUser->GetCurrentHandsPossessed() > 1) {
                    if (handWager <= 0.2 * priorBank) {
                        EXPECT_EQ(testUser->GetCurrentHands()->GetSize(), 3);
                        EXPECT_EQ(testUser->GetCurrentHandsPossessed(), testUser->GetCurrentHands()->GetSize());
                    }
                    else if (handWager > 0.2 * priorBank && handWager <= 0.25 * priorBank) {
                        EXPECT_EQ(testUser->GetCurrentHands()->GetSize(), 3);
                        EXPECT_EQ(testUser->GetCurrentHandsPossessed(), testUser->GetCurrentHands()->GetSize());
                    }
                    else if (handWager > 0.25 * priorBank && handWager <= 0.33 * priorBank) {
                        EXPECT_EQ(testUser->GetCurrentHands()->GetSize(), 3);
                        EXPECT_EQ(testUser->GetCurrentHandsPossessed(), testUser->GetCurrentHands()->GetSize());
                    }
                    else if (handWager > 0.33 * priorBank && handWager <= 0.5 * priorBank) {
                        EXPECT_EQ(testUser->GetCurrentHands()->GetSize(), 2);
                        EXPECT_EQ(testUser->GetCurrentHandsPossessed(), testUser->GetCurrentHands()->GetSize());
                    }
                }
                // Player does not have split hands
                else {
                    EXPECT_EQ(testUser->GetCurrentHands()->GetSize(), 1);
                    EXPECT_EQ(testUser->GetCurrentHandsPossessed(), testUser->GetCurrentHands()->GetSize());
                }
            for (int i = 0; i < testUser->GetCurrentHands()->GetSize(); i++) {
                if (i == 0) {
                    EXPECT_EQ(testUser->GetCurrentHands()->RetrieveNode(i)->data->GetPlayerCards()->GetSize(), 2);
                }
                else {
                    EXPECT_EQ(testUser->GetCurrentHands()->RetrieveNode(i)->data->GetPlayerCards()->GetSize(), 1);
                }
                EXPECT_EQ(testUser->GetCurrentHands()->RetrieveNode(i)->data->GetWager(), handWager);
            }
            EXPECT_EQ(testUser->GetBankTotal(), priorBank - testUser->GetCurrentHandsPossessed() * handWager);
            testUser->SetBankTotal(priorBank);
            testUser->ResetPlayer();
            testDealer->ResetPlayer();
            testShoe->EmptyShoe();
            testShoe->CopyShoe(copyShoe);
            }
            // Player has chosen to not split their hand
            {
                deal_hand_sim(testUser, testDealer, testShoe, handWager);
                EXPECT_EQ(testUser->GetCurrentHands()->GetSize(), 1);
                EXPECT_EQ(testUser->GetCurrentHands()->GetSize(), testUser->GetCurrentHandsPossessed());
                EXPECT_EQ(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetPlayerCards()->GetSize(), 2);
                EXPECT_EQ(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetWager(), handWager);
                EXPECT_EQ(testUser->GetBankTotal(), priorBank - testUser->GetCurrentHands()->RetrieveNode(0)->data->GetWager());
                same_rank_check_sim(testUser, testDealer, testShoe, true);
                EXPECT_EQ(testUser->GetCurrentHands()->GetSize(), testUser->GetCurrentHandsPossessed());
                for (int i = 0; i < testUser->GetCurrentHands()->GetSize(); i++) {
                    if (i == 0) {
                        EXPECT_EQ(testUser->GetCurrentHands()->RetrieveNode(i)->data->GetPlayerCards()->GetSize(), 2);
                    }
                    else {
                        EXPECT_EQ(testUser->GetCurrentHands()->RetrieveNode(i)->data->GetPlayerCards()->GetSize(), 1);
                    }
                    EXPECT_EQ(testUser->GetCurrentHands()->RetrieveNode(i)->data->GetWager(), handWager);
                }
                EXPECT_EQ(testUser->GetBankTotal(), priorBank - testUser->GetCurrentHandsPossessed() * handWager);
                testUser->SetBankTotal(priorBank);
                testUser->ResetPlayer();
                testDealer->ResetPlayer();
                testShoe->EmptyShoe();
                testShoe->CopyShoe(copyShoe);
            }
            handWager++;
        }
        testShoe->EmptyShoe();
        handWager = 10;
        // Random Number Generator
        rankVal = random_int(1, 12);
        dealerFirst = random_int(1, 12);
        dealerSecond = random_int(1, 12);
        // Check for splitting hand
        testCard = std::make_shared<Card>(Ranks[rankVal - 1], Suits[2]);
        testNode = testShoe->GetCardsInShoe()->InitNode(testCard);
        testShoe->GetCardsInShoe()->AppendNode(testNode);
        testCard = std::make_shared<Card>(Ranks[dealerSecond], Suits[3]);
        testNode = testShoe->GetCardsInShoe()->InitNode(testCard);
        testShoe->GetCardsInShoe()->AppendNode(testNode);
        testCard = std::make_shared<Card>(Ranks[rankVal], Suits[2]);
        testNode = testShoe->GetCardsInShoe()->InitNode(testCard);
        testShoe->GetCardsInShoe()->AppendNode(testNode);
        testCard = std::make_shared<Card>(Ranks[dealerFirst], Suits[1]);
        testNode = testShoe->GetCardsInShoe()->InitNode(testCard);
        testShoe->GetCardsInShoe()->AppendNode(testNode);
        testCard = std::make_shared<Card>(Ranks[rankVal], Suits[0]);
        testNode = testShoe->GetCardsInShoe()->InitNode(testCard);
        testShoe->GetCardsInShoe()->AppendNode(testNode);
        copyShoe->CopyShoe(testShoe);
        // Max hands split check
        while (handWager <= priorBank) {
            // Player has chosen to split their hand
            {
                deal_hand_sim(testUser, testDealer, testShoe, handWager);
                EXPECT_EQ(testUser->GetCurrentHands()->GetSize(), 1);
                EXPECT_EQ(testUser->GetCurrentHands()->GetSize(), testUser->GetCurrentHandsPossessed());
                EXPECT_EQ(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetPlayerCards()->GetSize(), 2);
                EXPECT_EQ(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetWager(), handWager);
                EXPECT_EQ(testUser->GetBankTotal(), priorBank - testUser->GetCurrentHands()->RetrieveNode(0)->data->GetWager());
                same_rank_check_sim(testUser, testDealer, testShoe, true);
                EXPECT_EQ(testUser->GetCurrentHands()->GetSize(), testUser->GetCurrentHandsPossessed());
                // Player has split hands
                if (testUser->GetCurrentHandsPossessed() > 1) {
                    if (handWager <= 0.2 * priorBank) {
                        EXPECT_EQ(testUser->GetCurrentHands()->GetSize(), 2);
                        EXPECT_EQ(testUser->GetCurrentHandsPossessed(), testUser->GetCurrentHands()->GetSize());
                    }
                    else if (handWager > 0.2 * priorBank && handWager <= 0.25 * priorBank) {
                        EXPECT_EQ(testUser->GetCurrentHands()->GetSize(), 2);
                        EXPECT_EQ(testUser->GetCurrentHandsPossessed(), testUser->GetCurrentHands()->GetSize());
                    }
                    else if (handWager > 0.25 * priorBank && handWager <= 0.33 * priorBank) {
                        EXPECT_EQ(testUser->GetCurrentHands()->GetSize(), 2);
                        EXPECT_EQ(testUser->GetCurrentHandsPossessed(), testUser->GetCurrentHands()->GetSize());
                    }
                    else if (handWager > 0.33 * priorBank && handWager <= 0.5 * priorBank) {
                        EXPECT_EQ(testUser->GetCurrentHands()->GetSize(), 2);
                        EXPECT_EQ(testUser->GetCurrentHandsPossessed(), testUser->GetCurrentHands()->GetSize());
                    }
                }
                // Player does not have split hands
                else {
                    EXPECT_EQ(testUser->GetCurrentHands()->GetSize(), 1);
                    EXPECT_EQ(testUser->GetCurrentHandsPossessed(), testUser->GetCurrentHands()->GetSize());
                }
            for (int i = 0; i < testUser->GetCurrentHands()->GetSize(); i++) {
                if (i == 0) {
                    EXPECT_EQ(testUser->GetCurrentHands()->RetrieveNode(i)->data->GetPlayerCards()->GetSize(), 2);
                }
                else {
                    EXPECT_EQ(testUser->GetCurrentHands()->RetrieveNode(i)->data->GetPlayerCards()->GetSize(), 1);
                }
                EXPECT_EQ(testUser->GetCurrentHands()->RetrieveNode(i)->data->GetWager(), handWager);
            }
            EXPECT_EQ(testUser->GetBankTotal(), priorBank - testUser->GetCurrentHandsPossessed() * handWager);
            testUser->SetBankTotal(priorBank);
            testUser->ResetPlayer();
            testDealer->ResetPlayer();
            testShoe->EmptyShoe();
            testShoe->CopyShoe(copyShoe);
            }
            // Player has chosen to not split their hand
            {
                deal_hand_sim(testUser, testDealer, testShoe, handWager);
                EXPECT_EQ(testUser->GetCurrentHands()->GetSize(), 1);
                EXPECT_EQ(testUser->GetCurrentHands()->GetSize(), testUser->GetCurrentHandsPossessed());
                EXPECT_EQ(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetPlayerCards()->GetSize(), 2);
                EXPECT_EQ(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetWager(), handWager);
                EXPECT_EQ(testUser->GetBankTotal(), priorBank - testUser->GetCurrentHands()->RetrieveNode(0)->data->GetWager());
                same_rank_check_sim(testUser, testDealer, testShoe, true);
                EXPECT_EQ(testUser->GetCurrentHands()->GetSize(), testUser->GetCurrentHandsPossessed());
                for (int i = 0; i < testUser->GetCurrentHands()->GetSize(); i++) {
                    if (i == 0) {
                        EXPECT_EQ(testUser->GetCurrentHands()->RetrieveNode(i)->data->GetPlayerCards()->GetSize(), 2);
                    }
                    else {
                        EXPECT_EQ(testUser->GetCurrentHands()->RetrieveNode(i)->data->GetPlayerCards()->GetSize(), 1);
                    }
                    EXPECT_EQ(testUser->GetCurrentHands()->RetrieveNode(i)->data->GetWager(), handWager);
                }
                EXPECT_EQ(testUser->GetBankTotal(), priorBank - testUser->GetCurrentHandsPossessed() * handWager);
                testUser->SetBankTotal(priorBank);
                testUser->ResetPlayer();
                testDealer->ResetPlayer();
                testShoe->EmptyShoe();
                testShoe->CopyShoe(copyShoe);
            }
            handWager++;
        }
        testShoe->EmptyShoe();
        handWager = 10;
        // Random Number Generator
        rankVal = random_int(1, 12);
        dealerFirst = random_int(1, 12);
        dealerSecond = random_int(1, 12);
        // Check for splitting hand
        testCard = std::make_shared<Card>(Ranks[dealerSecond], Suits[3]);
        testNode = testShoe->GetCardsInShoe()->InitNode(testCard);
        testShoe->GetCardsInShoe()->AppendNode(testNode);
        testCard = std::make_shared<Card>(Ranks[rankVal - 1], Suits[2]);
        testNode = testShoe->GetCardsInShoe()->InitNode(testCard);
        testShoe->GetCardsInShoe()->AppendNode(testNode);
        testCard = std::make_shared<Card>(Ranks[dealerFirst], Suits[1]);
        testNode = testShoe->GetCardsInShoe()->InitNode(testCard);
        testShoe->GetCardsInShoe()->AppendNode(testNode);
        testCard = std::make_shared<Card>(Ranks[rankVal], Suits[0]);
        testNode = testShoe->GetCardsInShoe()->InitNode(testCard);
        testShoe->GetCardsInShoe()->AppendNode(testNode);
        copyShoe->CopyShoe(testShoe);
        // Max hands split check
        while (handWager <= priorBank) {
            // Player has chosen to split their hand
            {
                deal_hand_sim(testUser, testDealer, testShoe, handWager);
                EXPECT_EQ(testUser->GetCurrentHands()->GetSize(), 1);
                EXPECT_EQ(testUser->GetCurrentHands()->GetSize(), testUser->GetCurrentHandsPossessed());
                EXPECT_EQ(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetPlayerCards()->GetSize(), 2);
                EXPECT_EQ(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetWager(), handWager);
                EXPECT_EQ(testUser->GetBankTotal(), priorBank - testUser->GetCurrentHands()->RetrieveNode(0)->data->GetWager());
                same_rank_check_sim(testUser, testDealer, testShoe, true);
                EXPECT_EQ(testUser->GetCurrentHands()->GetSize(), testUser->GetCurrentHandsPossessed());
                // Player does not have split hands
                EXPECT_EQ(testUser->GetCurrentHands()->GetSize(), 1);
                EXPECT_EQ(testUser->GetCurrentHandsPossessed(), testUser->GetCurrentHands()->GetSize());
            for (int i = 0; i < testUser->GetCurrentHands()->GetSize(); i++) {
                if (i == 0) {
                    EXPECT_EQ(testUser->GetCurrentHands()->RetrieveNode(i)->data->GetPlayerCards()->GetSize(), 2);
                }
                else {
                    EXPECT_EQ(testUser->GetCurrentHands()->RetrieveNode(i)->data->GetPlayerCards()->GetSize(), 1);
                }
                EXPECT_EQ(testUser->GetCurrentHands()->RetrieveNode(i)->data->GetWager(), handWager);
            }
            EXPECT_EQ(testUser->GetBankTotal(), priorBank - testUser->GetCurrentHandsPossessed() * handWager);
            testUser->SetBankTotal(priorBank);
            testUser->ResetPlayer();
            testDealer->ResetPlayer();
            testShoe->EmptyShoe();
            testShoe->CopyShoe(copyShoe);
            }
            // Player has chosen to not split their hand
            {
                deal_hand_sim(testUser, testDealer, testShoe, handWager);
                EXPECT_EQ(testUser->GetCurrentHands()->GetSize(), 1);
                EXPECT_EQ(testUser->GetCurrentHands()->GetSize(), testUser->GetCurrentHandsPossessed());
                EXPECT_EQ(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetPlayerCards()->GetSize(), 2);
                EXPECT_EQ(testUser->GetCurrentHands()->RetrieveNode(0)->data->GetWager(), handWager);
                EXPECT_EQ(testUser->GetBankTotal(), priorBank - testUser->GetCurrentHands()->RetrieveNode(0)->data->GetWager());
                same_rank_check_sim(testUser, testDealer, testShoe, true);
                EXPECT_EQ(testUser->GetCurrentHands()->GetSize(), testUser->GetCurrentHandsPossessed());
                for (int i = 0; i < testUser->GetCurrentHands()->GetSize(); i++) {
                    if (i == 0) {
                        EXPECT_EQ(testUser->GetCurrentHands()->RetrieveNode(i)->data->GetPlayerCards()->GetSize(), 2);
                    }
                    else {
                        EXPECT_EQ(testUser->GetCurrentHands()->RetrieveNode(i)->data->GetPlayerCards()->GetSize(), 1);
                    }
                    EXPECT_EQ(testUser->GetCurrentHands()->RetrieveNode(i)->data->GetWager(), handWager);
                }
                EXPECT_EQ(testUser->GetBankTotal(), priorBank - testUser->GetCurrentHandsPossessed() * handWager);
                testUser->SetBankTotal(priorBank);
                testUser->ResetPlayer();
                testDealer->ResetPlayer();
                testShoe->EmptyShoe();
                testShoe->CopyShoe(copyShoe);
            }
            handWager++;
        }
    }
}

// Player Logic check test
TEST_F(test_x, PlayerLogic) {
    for (int i = 0; i < random_int(100, 1000); i++) {
        std::shared_ptr<Player> testPlayer(new Player());
        std::shared_ptr<Player> testDealer(new Player());
        std::shared_ptr<Shoe> testShoe(new Shoe);
        float priorBank = 100;
        float handWager = 10;
        testPlayer->SetName("Borby");
        testDealer->SetName("Dealer");
        testPlayer->SetBankTotal(priorBank);
        testShoe->SetNumOfDecks(1);
        testShoe->CreateShoeSim();
        while (testShoe->GetCardsInShoe()->GetSize() >= 13) {
            auto bjc_result = blackjack_check_sim(testPlayer, testDealer, testShoe, handWager, false);
            // Neither player has blackjack
            if (bjc_result) {
                player_logic_sim(testPlayer, testDealer, testShoe, true);
                for (int i = 0; i < testPlayer->GetCurrentHands()->GetSize(); i++) {
                    // Player doubled down
                    if (testPlayer->GetCurrentHands()->RetrieveNode(i)->data->GetHashTable()->Contains(testPlayer->GetCurrentHands()->RetrieveNode(i)->data->GetValuesMatrix()[3][0])) {
                        EXPECT_TRUE(testPlayer->GetCurrentHands()->RetrieveNode(i)->data->GetHashTable()->Contains(testPlayer->GetCurrentHands()->RetrieveNode(i)->data->GetValuesMatrix()[1][0]));
                        EXPECT_FALSE(testPlayer->GetCurrentHands()->RetrieveNode(i)->data->GetHashTable()->Contains(testPlayer->GetCurrentHands()->RetrieveNode(i)->data->GetValuesMatrix()[1][1]));
                        EXPECT_FALSE(testPlayer->GetCurrentHands()->RetrieveNode(i)->data->GetHashTable()->Contains(testPlayer->GetCurrentHands()->RetrieveNode(i)->data->GetValuesMatrix()[1][2]));
                        EXPECT_TRUE(testPlayer->GetCurrentHands()->RetrieveNode(i)->data->GetHashTable()->Contains(testPlayer->GetCurrentHands()->RetrieveNode(i)->data->GetValuesMatrix()[2][0]));
                        EXPECT_EQ(testPlayer->GetCurrentHands()->RetrieveNode(i)->data->GetWager(), 2 * handWager);
                        EXPECT_EQ(testPlayer->GetCurrentHands()->RetrieveNode(i)->data->GetPlayerCards()->GetSize(), 3);
                        EXPECT_EQ(testDealer->GetCurrentHands()->RetrieveNode(i)->data->GetPlayerCards()->GetSize(), 2);
                    }
                    // Player hit their hand
                    else if (testPlayer->GetCurrentHands()->RetrieveNode(i)->data->GetHashTable()->Contains(testPlayer->GetCurrentHands()->RetrieveNode(i)->data->GetValuesMatrix()[3][1])) {
                        EXPECT_FALSE(testPlayer->GetCurrentHands()->RetrieveNode(i)->data->GetHashTable()->Contains(testPlayer->GetCurrentHands()->RetrieveNode(i)->data->GetValuesMatrix()[1][0]));
                        EXPECT_TRUE(testPlayer->GetCurrentHands()->RetrieveNode(i)->data->GetHashTable()->Contains(testPlayer->GetCurrentHands()->RetrieveNode(i)->data->GetValuesMatrix()[1][1]));
                        EXPECT_FALSE(testPlayer->GetCurrentHands()->RetrieveNode(i)->data->GetHashTable()->Contains(testPlayer->GetCurrentHands()->RetrieveNode(i)->data->GetValuesMatrix()[1][2]));
                        EXPECT_EQ(testPlayer->GetCurrentHands()->RetrieveNode(i)->data->GetWager(), handWager);
                        EXPECT_NE(testPlayer->GetCurrentHands()->RetrieveNode(i)->data->GetPlayerCards()->GetSize(), 2);
                        EXPECT_EQ(testDealer->GetCurrentHands()->RetrieveNode(i)->data->GetPlayerCards()->GetSize(), 2);
                    }
                    else if (testPlayer->GetCurrentHands()->RetrieveNode(i)->data->GetHashTable()->Contains(testPlayer->GetCurrentHands()->RetrieveNode(i)->data->GetValuesMatrix()[3][3])) {
                        EXPECT_FALSE(testPlayer->GetCurrentHands()->RetrieveNode(i)->data->GetHashTable()->Contains(testPlayer->GetCurrentHands()->RetrieveNode(i)->data->GetValuesMatrix()[1][0]));
                        EXPECT_FALSE(testPlayer->GetCurrentHands()->RetrieveNode(i)->data->GetHashTable()->Contains(testPlayer->GetCurrentHands()->RetrieveNode(i)->data->GetValuesMatrix()[1][1]));
                        EXPECT_TRUE(testPlayer->GetCurrentHands()->RetrieveNode(i)->data->GetHashTable()->Contains(testPlayer->GetCurrentHands()->RetrieveNode(i)->data->GetValuesMatrix()[1][2]));
                        EXPECT_EQ(testPlayer->GetCurrentHands()->RetrieveNode(i)->data->GetWager(), handWager);
                        EXPECT_TRUE(testPlayer->GetCurrentHands()->RetrieveNode(i)->data->GetPlayerCards()->GetSize() >= 2);
                        EXPECT_EQ(testDealer->GetCurrentHands()->RetrieveNode(i)->data->GetPlayerCards()->GetSize(), 2);
                    }
                }
            }
            // Someone has blackjack
            else {
                EXPECT_FALSE(testPlayer->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testPlayer->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[1][0]));
                EXPECT_FALSE(testPlayer->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testPlayer->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[1][1]));
                EXPECT_FALSE(testPlayer->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testPlayer->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[1][2]));
                EXPECT_FALSE(testPlayer->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testPlayer->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[1][3]));
                EXPECT_FALSE(testPlayer->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testPlayer->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[1][4]));
                if (testPlayer->GetCurrentHands()->RetrieveNode(0)->data->GetCardsTotal() == 21) {
                    EXPECT_TRUE(testPlayer->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testPlayer->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[2][1]));
                }
                else {
                    EXPECT_FALSE(testPlayer->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testPlayer->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[2][1]));
                }
                if (testDealer->GetCurrentHands()->RetrieveNode(0)->data->GetCardsTotal() == 21) {
                    EXPECT_TRUE(testDealer->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testDealer->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[2][1]));
                }
                else {
                    EXPECT_FALSE(testDealer->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testDealer->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[2][1]));
                }
                EXPECT_EQ(testPlayer->GetCurrentHands()->GetSize(), 1);
                EXPECT_EQ(testPlayer->GetCurrentHands()->RetrieveNode(0)->data->GetPlayerCards()->GetSize(), 2);
                EXPECT_EQ(testDealer->GetCurrentHands()->GetSize(), 1);
                EXPECT_EQ(testDealer->GetCurrentHands()->RetrieveNode(0)->data->GetPlayerCards()->GetSize(), 2);
            }
            testPlayer->ResetPlayer();
            testDealer->ResetPlayer();
            testPlayer->SetBankTotal(priorBank);
        }
    }
}

// Dealer logic test check
TEST_F(test_x, DealerLogicTest) {
    for (int i = 0; i < random_int(100, 1000); i++) {
        std::shared_ptr<Player> testPlayer(new Player());
        std::shared_ptr<Player> testDealer(new Player());
        std::shared_ptr<Shoe> testShoe(new Shoe);
        std::shared_ptr<Card> testCard(new Card);
        std::shared_ptr<node<Card>> testNode;
        float priorBank = 100;
        float handWager = 10;
        testPlayer->SetName("Borby");
        testDealer->SetName("Dealer");
        testPlayer->SetBankTotal(priorBank);
        testShoe->SetNumOfDecks(1);
        testShoe->CreateShoeSim();
        while (testShoe->GetCardsInShoe()->GetSize() >= 13) {
            auto bjc_result = blackjack_check_sim(testPlayer, testDealer, testShoe, handWager, false);
            // Neither player has blackjack
            if (bjc_result) {
                EXPECT_EQ(testPlayer->GetCurrentHands()->GetSize(), 1);
                EXPECT_EQ(testPlayer->GetCurrentHands()->RetrieveNode(0)->data->GetPlayerCards()->GetSize(), 2);
                EXPECT_EQ(testDealer->GetCurrentHands()->GetSize(), 1);
                EXPECT_EQ(testDealer->GetCurrentHands()->RetrieveNode(0)->data->GetPlayerCards()->GetSize(), 2);
                EXPECT_TRUE(testPlayer->GetCurrentHands()->RetrieveNode(0)->data->GetCardsTotal() < 21);
                EXPECT_TRUE(testDealer->GetCurrentHands()->RetrieveNode(0)->data->GetCardsTotal() < 21);
                player_logic_sim(testPlayer, testDealer, testShoe, true);
                for (int i = 0; i < testPlayer->GetCurrentHands()->GetSize(); i++) {
                    EXPECT_TRUE(testPlayer->GetCurrentHands()->RetrieveNode(i)->data->GetPlayerCards()->GetSize() >= 2);
                }
                dealer_logic_sim(testPlayer, testDealer, testShoe);
                EXPECT_TRUE(testDealer->GetCurrentHands()->RetrieveNode(0)->data->GetPlayerCards()->GetSize() >= 2);
            }
            // Someone has blackjack
            else {
                EXPECT_FALSE(testPlayer->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testPlayer->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[1][0]));
                EXPECT_FALSE(testPlayer->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testPlayer->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[1][1]));
                EXPECT_FALSE(testPlayer->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testPlayer->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[1][2]));
                EXPECT_FALSE(testPlayer->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testPlayer->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[1][3]));
                EXPECT_FALSE(testPlayer->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testPlayer->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[1][4]));
                if (testPlayer->GetCurrentHands()->RetrieveNode(0)->data->GetCardsTotal() == 21) {
                    EXPECT_TRUE(testPlayer->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testPlayer->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[2][1]));
                }
                else {
                    EXPECT_FALSE(testPlayer->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testPlayer->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[2][1]));
                }
                if (testDealer->GetCurrentHands()->RetrieveNode(0)->data->GetCardsTotal() == 21) {
                    EXPECT_TRUE(testDealer->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testDealer->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[2][1]));
                }
                else {
                    EXPECT_FALSE(testDealer->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testDealer->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[2][1]));
                }
                EXPECT_EQ(testPlayer->GetCurrentHands()->GetSize(), 1);
                EXPECT_EQ(testPlayer->GetCurrentHands()->RetrieveNode(0)->data->GetPlayerCards()->GetSize(), 2);
                EXPECT_EQ(testDealer->GetCurrentHands()->GetSize(), 1);
                EXPECT_EQ(testDealer->GetCurrentHands()->RetrieveNode(0)->data->GetPlayerCards()->GetSize(), 2);
            }
            testPlayer->ResetPlayer();
            testDealer->ResetPlayer();
            testPlayer->SetBankTotal(priorBank);
        }
    }
}

// Hand comparison logic test
TEST_F(test_x, HandComparisonLogic) {
    for (int i = 0; i < random_int(100, 1000); i++) {
        std::shared_ptr<Player> testPlayer(new Player());
        std::shared_ptr<Player> testDealer(new Player());
        std::shared_ptr<Shoe> testShoe(new Shoe);
        float priorBank = 100;
        float handWager = 10;
        testPlayer->SetName("Borby");
        testDealer->SetName("Dealer");
        testPlayer->SetBankTotal(priorBank);
        testShoe->SetNumOfDecks(1);
        testShoe->CreateShoeSim();
        while (testShoe->GetCardsInShoe()->GetSize() >= 13) {
            auto bjc_result = blackjack_check_sim(testPlayer, testDealer, testShoe, handWager, false);
            // Neither player has blackjack
            if (bjc_result) {
                EXPECT_EQ(testPlayer->GetCurrentHands()->GetSize(), 1);
                EXPECT_EQ(testPlayer->GetCurrentHands()->RetrieveNode(0)->data->GetPlayerCards()->GetSize(), 2);
                EXPECT_EQ(testDealer->GetCurrentHands()->GetSize(), 1);
                EXPECT_EQ(testDealer->GetCurrentHands()->RetrieveNode(0)->data->GetPlayerCards()->GetSize(), 2);
                EXPECT_TRUE(testPlayer->GetCurrentHands()->RetrieveNode(0)->data->GetCardsTotal() < 21);
                EXPECT_TRUE(testDealer->GetCurrentHands()->RetrieveNode(0)->data->GetCardsTotal() < 21);
                player_logic_sim(testPlayer, testDealer, testShoe, true);
                dealer_logic_sim(testPlayer, testDealer, testShoe);
                hand_comparison_logic_sim(testPlayer, testDealer);
            }
            // Someone has blackjack
            else {
                EXPECT_FALSE(testPlayer->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testPlayer->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[1][0]));
                EXPECT_FALSE(testPlayer->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testPlayer->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[1][1]));
                EXPECT_FALSE(testPlayer->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testPlayer->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[1][2]));
                EXPECT_FALSE(testPlayer->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testPlayer->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[1][3]));
                EXPECT_FALSE(testPlayer->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testPlayer->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[1][4]));
                if (testPlayer->GetCurrentHands()->RetrieveNode(0)->data->GetCardsTotal() == 21) {
                    EXPECT_TRUE(testPlayer->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testPlayer->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[2][1]));
                }
                else {
                    EXPECT_FALSE(testPlayer->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testPlayer->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[2][1]));
                }
                if (testDealer->GetCurrentHands()->RetrieveNode(0)->data->GetCardsTotal() == 21) {
                    EXPECT_TRUE(testDealer->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testDealer->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[2][1]));
                }
                else {
                    EXPECT_FALSE(testDealer->GetCurrentHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testDealer->GetCurrentHands()->RetrieveNode(0)->data->GetValuesMatrix()[2][1]));
                }
                EXPECT_EQ(testPlayer->GetCurrentHands()->GetSize(), 1);
                EXPECT_EQ(testPlayer->GetCurrentHands()->RetrieveNode(0)->data->GetPlayerCards()->GetSize(), 2);
                EXPECT_EQ(testDealer->GetCurrentHands()->GetSize(), 1);
                EXPECT_EQ(testDealer->GetCurrentHands()->RetrieveNode(0)->data->GetPlayerCards()->GetSize(), 2);
            }
            testPlayer->SetBankTotal(priorBank);
            testPlayer->ResetPlayer();
            testDealer->ResetPlayer();
        }
        break;
    }
}