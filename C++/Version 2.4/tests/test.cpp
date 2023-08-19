#include <gtest/gtest.h>
#include "../app/Assets/HPP/Core.hpp"

class test_x : public ::testing::Test {};

/////////////////////////////////////////
// Test Helper Functions
/////////////////////////////////////////

// /////////////////////////////////////////
// // HashTable Table Tests
// /////////////////////////////////////////

// // HashTable table initialize test
// TEST_F(test_x, HashTableInitTest) {
//     // Create table
//     std::shared_ptr<HashTable> testFilter;
//     // Change bit size
//     for (int i = 1; i < random_int(900, 1000); i++) {
//         // Change hash function iterations
//         for (int j = 1; j < random_int(20, 40); j++) {
//             testFilter = std::make_shared<HashTable>(i, j);
//             EXPECT_EQ(testFilter->GetTable().size(), i);
//             EXPECT_EQ(testFilter->GetHashFuncIterations(), j);
//         }
//     }
// }

// // HashTable table hash calc test
// TEST_F(test_x, HashTableHashCalc) {
//     // Create test variables
//     std::string testString = "Hello World!";
//     // Create table
//     std::shared_ptr<HashTable> testFilter(new HashTable(1000, 12));
//     unsigned int tempHash = testFilter->CalculateHashCode(testString); 
//     EXPECT_TRUE(tempHash > 0);
// }

// // HashTable table bucket calc test
// TEST_F(test_x, HashTableBucketCalc) {
//     // Create test variables
//     std::string testString = "Goodbye World!";
//     // Create table
//     std::shared_ptr<HashTable> testFilter(new HashTable(1000, 12));
//     testFilter->SetHashCode(testString);
//     testFilter->SetBucket(testFilter->GetHashCode());
//     EXPECT_TRUE(testFilter->GetBucket() >= 0 && testFilter->GetBucket() < 1000);
// }

// // HashTable table add element test
// TEST_F(test_x, HashTableAdd) {
//     // Create test variables
//     std::string testString = "What world?";
//     // Create table
//     std::shared_ptr<HashTable> testFilter;
//     for (int i = 1; i < random_int(80, 100); i++) {
//         testFilter = std::make_shared<HashTable>(random_int(1000, 2000), i);
//         testFilter->AddToTable(testString);
//         EXPECT_TRUE(testFilter->GetBucket() >= 0);
//         EXPECT_TRUE(testFilter->GetBucket() < testFilter->GetTable().size());
//     }
// }

// // HashTable table clear test
// TEST_F(test_x, HashTableClear) {
//     // Create test variables
//     std::string testString = "What is this world?";
//     // Create table
//     std::shared_ptr<HashTable> testFilter;
//     for (int i = 1; i < random_int(80, 100); i++) {
//         testFilter = std::make_shared<HashTable>(random_int(1000, 2000), i);
//         testFilter->AddToTable(testString);
//         testFilter->ClearHashTable();
//         for (int i = 0; i < testFilter->GetTable().size(); i++) {
//             EXPECT_FALSE(testFilter->GetTable().at(i));
//         }
//     }
// }

// // HashTable table contains test
// TEST_F(test_x, HashTableContains) {
//     // Create table
//     std::shared_ptr<HashTable> testFilter(new HashTable(1000, 12));
//     std::vector<std::string> testTrueVector = {"This", "is", "a", "test", "of", "bloom", "filters", "efficiency"};
//     std::vector<std::string> testFalseVector = {"On", "the", "other", "hand", "I'm", "mister", "negative", "examination"};
//     for (int i = 0; i < testTrueVector.size(); i++) {
//         testFilter->AddToTable(testTrueVector.at(i));
//         EXPECT_TRUE(testFilter->Contains(testTrueVector.at(i)));
//         EXPECT_FALSE(testFilter->Contains(testFalseVector.at(i)));
//     }
// }

// // HashTable table remove test
// TEST_F(test_x, HashTableRemove) {
//     // Create table
//     std::shared_ptr<HashTable> testFilter(new HashTable(1000, 12));
//     std::vector<std::string> testTrueVector = {"This", "is", "a", "test", "of", "bloom", "filters", "efficiency"};
//     for (int i = 0; i < testTrueVector.size(); i++) {
//         testFilter->AddToTable(testTrueVector.at(i));
//     }
//     while (!testTrueVector.empty()) {
//         testFilter->RemoveElement(testTrueVector.at(testTrueVector.size() - 1));
//         EXPECT_FALSE(testFilter->Contains(testTrueVector.at(testTrueVector.size() - 1)));
//         testTrueVector.pop_back();
//     }
// }

// /////////////////////////////////////////
// // Linked List Tests
// /////////////////////////////////////////

// // Linked list test, init node
// TEST_F(test_x, LinkedListInitNode) {
//     // Integer list
//     std::shared_ptr<LinkedList<int>> intList(new LinkedList<int>);
//     int intVal = 13;
//     std::shared_ptr<node<int>> intNode = intList->InitNode(intVal);
//     ASSERT_TRUE(typeid(intNode->data) == typeid(int));
//     ASSERT_EQ(intNode->nextNode, nullptr);
//     ASSERT_EQ(intNode->previousNode, nullptr);
//     ASSERT_EQ(intNode->data, intVal);
//     // Float list
//     std::shared_ptr<LinkedList<float>> floatList(new LinkedList<float>);
//     float floatVal = 3.14;
//     std::shared_ptr<node<float>> floatNode = floatList->InitNode(floatVal);
//     ASSERT_TRUE(typeid(floatNode->data) == typeid(float));
//     ASSERT_EQ(floatNode->nextNode, nullptr);
//     ASSERT_EQ(floatNode->previousNode, nullptr);
//     ASSERT_EQ(floatNode->data, floatVal);
//     // Double list
//     std::shared_ptr<LinkedList<double>> doubleList(new LinkedList<double>);
//     double doubleVal = 3.141592654;
//     std::shared_ptr<node<double>> doubleNode = doubleList->InitNode(doubleVal);
//     ASSERT_TRUE(typeid(doubleNode->data) == typeid(double));
//     ASSERT_EQ(doubleNode->nextNode, nullptr);
//     ASSERT_EQ(doubleNode->previousNode, nullptr);
//     ASSERT_EQ(doubleNode->data, doubleVal);
//     // Long list
//     std::shared_ptr<LinkedList<long>> longList(new LinkedList<long>);
//     long longVal = 2147483647;
//     std::shared_ptr<node<long>> longNode = longList->InitNode(longVal);
//     ASSERT_TRUE(typeid(longNode->data) == typeid(long));
//     ASSERT_EQ(longNode->nextNode, nullptr);
//     ASSERT_EQ(longNode->previousNode, nullptr);
//     ASSERT_EQ(longNode->data, longVal);
//     // String list
//     std::shared_ptr<LinkedList<std::string>> stringList(new LinkedList<std::string>);
//     std::string stringVal = "Hello World!";
//     std::shared_ptr<node<std::string>> stringNode = stringList->InitNode(stringVal);
//     ASSERT_TRUE(typeid(stringNode->data) == typeid(std::string));
//     ASSERT_EQ(stringNode->nextNode, nullptr);
//     ASSERT_EQ(stringNode->previousNode, nullptr);
//     ASSERT_EQ(stringNode->data, stringVal);
//     // Card list
//     std::shared_ptr<LinkedList<Card>> cardList(new LinkedList<Card>);
//     std::shared_ptr<Card> testCard(new Card(Ranks[0], Suits[0]));
//     std::shared_ptr<node<Card>> cardNode = cardList->InitNode(testCard);
//     ASSERT_TRUE(typeid(cardNode->data) == typeid(Card));
//     ASSERT_EQ(cardNode->nextNode, nullptr);
//     ASSERT_EQ(cardNode->previousNode, nullptr);
//     ASSERT_EQ(cardNode->data.GetCardValue(), 11);
//     ASSERT_EQ(cardNode->data.GetRank(), Ranks[0]);
//     ASSERT_EQ(cardNode->data.GetSuit(), Suits[0]);
// }

// // Linked list test, set root
// TEST_F(test_x, LinkedListRoot) {
//     std::shared_ptr<LinkedList<float>> testList(new LinkedList<float>);
//     float floatVal = 4.15;
//     std::shared_ptr<node<float>> testRoot = testList->InitNode(floatVal);
//     testList->SetRoot(testRoot);
//     ASSERT_EQ(testList->GetRoot()->data, floatVal);
//     ASSERT_EQ(testList->GetRoot()->previousNode, nullptr);
//     ASSERT_EQ(testList->GetRoot()->nextNode, nullptr);
// }

// // Linked list test, set tail
// TEST_F(test_x, LinkedListTail) {
//     std::shared_ptr<LinkedList<float>> testList(new LinkedList<float>);
//     float floatVal = 6.15;
//     std::shared_ptr<node<float>> testTail = testList->InitNode(floatVal);
//     testList->SetTail(testTail);
//     ASSERT_EQ(testList->GetTail()->data, floatVal);
//     ASSERT_EQ(testList->GetTail()->previousNode, nullptr);
//     ASSERT_EQ(testList->GetTail()->nextNode, nullptr);
// }

// // Linked list test, size
// TEST_F(test_x, LinkedListSize) {
//     std::shared_ptr<LinkedList<int>> testList(new LinkedList<int>);
//     ASSERT_EQ(testList->GetSize(), 0);
//     int intVal = 123;
//     std::shared_ptr<node<int>> testNode = testList->InitNode(intVal);
//     ASSERT_EQ(testList->GetSize(), 0);
//     testList->SetRoot(testNode);
//     ASSERT_EQ(testList->GetSize(), 1);
// }

// // Linked list, append node
// TEST_F(test_x, LinkedListAppend) {
//     std::shared_ptr<LinkedList<float>> testList(new LinkedList<float>);
//     float floatVal = 4.23;
//     // Insert into empty list
//     std::shared_ptr<node<float>> testNode1 = testList->InitNode(floatVal);
//     testList->AppendNode(testNode1);
//     EXPECT_EQ(testList->GetSize(), 1);
//     EXPECT_EQ(testList->GetRoot(), testNode1);
//     EXPECT_EQ(testList->GetRoot()->previousNode, nullptr);
//     EXPECT_EQ(testList->GetRoot()->nextNode, nullptr);
//     EXPECT_EQ(testList->GetTail(), testNode1);
//     EXPECT_EQ(testList->GetTail()->previousNode, nullptr);
//     EXPECT_EQ(testList->GetTail()->nextNode, nullptr);
//     floatVal = 5.32;
//     // Insert into list with one element
//     std::shared_ptr<node<float>> testNode2 = testList->InitNode(floatVal);
//     testList->AppendNode(testNode2);
//     EXPECT_EQ(testList->GetSize(), 2);
//     EXPECT_EQ(testList->GetRoot(), testNode1);
//     EXPECT_EQ(testList->GetTail(), testNode2);
//     EXPECT_EQ(testList->GetRoot()->previousNode, nullptr);
//     EXPECT_EQ(testList->GetTail(), testList->GetRoot()->nextNode);
//     EXPECT_EQ(testList->GetRoot(), testList->GetTail()->previousNode);
//     EXPECT_EQ(testList->GetTail()->nextNode, nullptr);
//     floatVal = 6.72;
//     // Insert into list with two elements
//     std::shared_ptr<node<float>> testNode3 = testList->InitNode(floatVal);
//     testList->AppendNode(testNode3);
//     EXPECT_EQ(testList->GetSize(), 3);
//     EXPECT_EQ(testList->GetRoot(), testNode1);
//     EXPECT_EQ(testList->GetTail(), testNode3);
//     EXPECT_EQ(testList->GetRoot()->previousNode, nullptr);
//     EXPECT_EQ(testList->GetRoot()->nextNode, testNode2);
//     EXPECT_EQ(testList->GetRoot(), testNode2->previousNode);
//     EXPECT_EQ(testList->GetTail(), testNode2->nextNode);
//     EXPECT_EQ(testList->GetTail()->previousNode, testNode2);
//     EXPECT_EQ(testList->GetTail()->nextNode, nullptr);
// }

// // Linked list, pop node
// TEST_F(test_x, LinkedListPop) {
//     std::shared_ptr<LinkedList<int>> testList(new LinkedList<int>);
//     int intVal = 3;
//     // Check on empty list
//     std::shared_ptr<node<int>> emptyNode = testList->PopNode();
//     EXPECT_EQ(testList->GetSize(), 0);
//     EXPECT_EQ(emptyNode, nullptr);
//     EXPECT_EQ(testList->GetRoot(), emptyNode);
//     // Test on list with one element
//     std::shared_ptr<node<int>> testNode1 = testList->InitNode(intVal);
//     testList->AppendNode(testNode1);
//     std::shared_ptr<node<int>> poppedNode = testList->PopNode();
//     EXPECT_EQ(testList->GetSize(), 0);
//     EXPECT_EQ(testList->GetRoot(), nullptr);
//     EXPECT_EQ(testList->GetTail(), nullptr);
//     EXPECT_EQ(poppedNode, testNode1);
//     EXPECT_EQ(poppedNode->previousNode, nullptr);
//     EXPECT_EQ(poppedNode->nextNode, nullptr);
//     // Test on list with two elements
//     intVal = 4;
//     std::shared_ptr<node<int>> testNode2 = testList->InitNode(intVal);
//     intVal = 5;
//     std::shared_ptr<node<int>> testNode3 = testList->InitNode(intVal);
//     // Add test nodes
//     testList->AppendNode(testNode2);
//     testList->AppendNode(testNode3);
//     // Pop node
//     poppedNode = testList->PopNode();
//     EXPECT_EQ(testList->GetSize(), 1);
//     EXPECT_EQ(testList->GetRoot(), testNode2);
//     EXPECT_EQ(testList->GetTail(), testNode2);
//     EXPECT_EQ(poppedNode, testNode3);
//     // Pop node again
//     poppedNode = testList->PopNode();
//     EXPECT_EQ(testList->GetSize(), 0);
//     EXPECT_EQ(testList->GetRoot(), nullptr);
//     EXPECT_EQ(testList->GetTail(), nullptr);
//     EXPECT_EQ(poppedNode, testNode2);
//     // Attempt to pop node again (empty list now)
//     poppedNode = testList->PopNode();
//     EXPECT_EQ(testList->GetRoot(), nullptr);
//     EXPECT_EQ(testList->GetTail(), nullptr);
//     EXPECT_EQ(poppedNode, nullptr);
// }

// // Linked list, clear list
// TEST_F(test_x, LinkedListClear) {
//     std::shared_ptr<LinkedList<double>> testList(new LinkedList<double>);
//     double doubleVal = 3.141592654;
//     // Insert into empty list
//     std::shared_ptr<node<double>> testNode1 = testList->InitNode(doubleVal);
//     testList->AppendNode(testNode1);
//     EXPECT_EQ(testList->GetSize(), 1);
//     EXPECT_EQ(testList->GetRoot(), testNode1);
//     EXPECT_EQ(testList->GetRoot()->previousNode, nullptr);
//     EXPECT_EQ(testList->GetRoot()->nextNode, nullptr);
//     EXPECT_EQ(testList->GetTail(), testNode1);
//     EXPECT_EQ(testList->GetTail()->previousNode, nullptr);
//     EXPECT_EQ(testList->GetTail()->nextNode, nullptr);
//     testList->ClearList();
//     EXPECT_EQ(testList->GetSize(), 0);
//     EXPECT_EQ(testList->GetRoot(), nullptr);
//     EXPECT_EQ(testList->GetTail(), nullptr);
// }

// // Linked list, insert into list
// TEST_F(test_x, LinkedListInsert) {
//     std::shared_ptr<LinkedList<int>> testList(new LinkedList<int>);
//     int intVal = 8;
//     // Insert into empty list (testNode1)
//     std::shared_ptr<node<int>> testNode1 = testList->InitNode(intVal);
//     testList->InsertNode(testNode1, 0);
//     EXPECT_EQ(testList->GetRoot(), testNode1);
//     EXPECT_EQ(testList->GetTail(), testNode1);
//     EXPECT_EQ(testNode1->nextNode, nullptr);
//     EXPECT_EQ(testNode1->previousNode, nullptr);
//     EXPECT_EQ(testList->GetSize(), 1);
//     intVal = 10;
//     // Insert at tail (testNode1, testNode2)
//     std::shared_ptr<node<int>> testNode2 = testList->InitNode(intVal);
//     testList->InsertNode(testNode2, 1);
//     EXPECT_EQ(testList->GetRoot(), testNode1);
//     EXPECT_EQ(testList->GetTail(), testNode2);
//     EXPECT_EQ(testNode1->nextNode, testNode2);
//     EXPECT_EQ(testNode2->previousNode, testNode1);
//     EXPECT_EQ(testList->GetSize(), 2);
//     intVal = 20;
//     // Insert at root (testNode3, testNode1, testNode2)
//     std::shared_ptr<node<int>> testNode3 = testList->InitNode(intVal);
//     testList->InsertNode(testNode3, 0);
//     EXPECT_EQ(testList->GetRoot()->nextNode, testNode1);
//     EXPECT_EQ(testList->GetRoot()->nextNode->nextNode, testNode2);
//     EXPECT_EQ(testNode1->previousNode, testNode3);
//     EXPECT_EQ(testNode1->nextNode, testNode2);
//     EXPECT_EQ(testList->GetSize(), 3);
//     intVal = 30;
//     // Insert in between (testNode3, testNode1, testNode4, testNode2)
//     std::shared_ptr<node<int>> testNode4 = testList->InitNode(intVal);
//     testList->InsertNode(testNode4, 2);
//     EXPECT_EQ(testList->GetRoot()->nextNode->nextNode, testNode4);
//     EXPECT_EQ(testList->GetTail()->previousNode, testNode4);
//     EXPECT_EQ(testNode4->previousNode, testNode1);
//     EXPECT_EQ(testNode4->nextNode, testNode2);
//     EXPECT_EQ(testList->GetSize(), 4);
//     intVal = 40;
//     // Insert immediately after root (testNode3, testNode5, testNode1, testNode4, testNode2)
//     std::shared_ptr<node<int>> testNode5 = testList->InitNode(intVal);
//     testList->InsertNode(testNode5, 1);
//     EXPECT_EQ(testList->GetRoot()->nextNode, testNode5);
//     EXPECT_EQ(testList->GetTail()->previousNode->previousNode->previousNode, testNode5);
//     EXPECT_EQ(testNode5->nextNode, testNode1);
//     EXPECT_EQ(testNode5->previousNode, testNode3);
//     EXPECT_EQ(testList->GetSize(), 5);
// }

// // Linked list, retrieve test
// TEST_F(test_x, LinkedListRetrieve) {
//     std::shared_ptr<LinkedList<int>> testList(new LinkedList<int>);
//     int intVal = 12;
//     // Create nodes
//     std::shared_ptr<node<int>> testNode1 = testList->InitNode(intVal);
//     intVal = 13;
//     std::shared_ptr<node<int>> testNode2 = testList->InitNode(intVal);
//     intVal = 14;
//     std::shared_ptr<node<int>> testNode3 = testList->InitNode(intVal);
//     intVal = 15;
//     std::shared_ptr<node<int>> testNode4 = testList->InitNode(intVal);
//     // Insert nodes (testNode1, testNode2, testNode3, testNode4)
//     testList->AppendNode(testNode1);
//     testList->AppendNode(testNode2);
//     testList->AppendNode(testNode3);
//     testList->AppendNode(testNode4);
//     // Test retrieving nodes
//     EXPECT_EQ(testList->GetRoot(), testNode1);
//     EXPECT_EQ(testList->GetTail(), testNode4);
//     EXPECT_EQ(testList->RetrieveNode(0), testNode1);
//     EXPECT_EQ(testList->RetrieveNode(1), testNode2);
//     EXPECT_EQ(testList->RetrieveNode(2), testNode3);
//     EXPECT_EQ(testList->RetrieveNode(3), testNode4);
//     EXPECT_EQ(testList->RetrieveNode(-1), testNode4);
//     EXPECT_EQ(testList->RetrieveNode(4), testNode4);
//     EXPECT_EQ(testList->GetSize(), 4);
// }

// // Linked list, remove list
// TEST_F(test_x, LinkedListRemove) {
//     std::shared_ptr<LinkedList<int>> testList(new LinkedList<int>);
//     int intVal = 12;
//     // Create nodes
//     std::shared_ptr<node<int>> testNode1 = testList->InitNode(intVal);
//     intVal = 13;
//     std::shared_ptr<node<int>> testNode2 = testList->InitNode(intVal);
//     intVal = 14;
//     std::shared_ptr<node<int>> testNode3 = testList->InitNode(intVal);
//     intVal = 15;
//     std::shared_ptr<node<int>> testNode4 = testList->InitNode(intVal);
//     // Insert nodes (testNode1, testNode2, testNode3, testNode4)
//     testList->AppendNode(testNode1);
//     testList->AppendNode(testNode2);
//     testList->AppendNode(testNode3);
//     testList->AppendNode(testNode4);
//     // Remove root (testNode2, testNode3, testNode4)
//     testList->RemoveNode(0);
//     EXPECT_EQ(testList->GetSize(), 3);
//     EXPECT_EQ(testList->GetRoot(), testNode2);
//     EXPECT_EQ(testList->GetTail(), testNode4);
//     EXPECT_EQ(testNode2->nextNode, testNode3);;
//     EXPECT_EQ(testNode3->previousNode, testNode2);
//     EXPECT_EQ(testNode3->nextNode, testNode4);
//     EXPECT_EQ(testNode4->previousNode, testNode3);
//     // Remove tail (testNode2, testNode3)
//     testList->RemoveNode(-1);
//     EXPECT_EQ(testList->GetSize(), 2);
//     EXPECT_EQ(testList->GetRoot(), testNode2);
//     EXPECT_EQ(testList->GetTail(), testNode3);
//     EXPECT_EQ(testNode2->nextNode, testNode3);
//     EXPECT_EQ(testNode3->previousNode, testNode2);
//     // Clear list and repopulate (testNode1, testNode2, testNode3, testNode4)
//     testList->ClearList();
//     testList->AppendNode(testNode1);
//     testList->AppendNode(testNode2);
//     testList->AppendNode(testNode3);
//     testList->AppendNode(testNode4);
//     // Remove element 1 (testNode1, testNode3, testNode4)
//     testList->RemoveNode(1);
//     EXPECT_EQ(testList->GetSize(), 3);
//     EXPECT_EQ(testList->GetRoot(), testNode1);
//     EXPECT_EQ(testList->GetTail(), testNode4);
//     EXPECT_EQ(testNode1->nextNode, testNode3);
//     EXPECT_EQ(testNode3->previousNode, testNode1);
//     EXPECT_EQ(testNode3->nextNode, testNode4);
//     EXPECT_EQ(testNode4->previousNode, testNode3);
//     // Remove element 1 again (testNode1, testNode4)
//     testList->RemoveNode(1);
//     EXPECT_EQ(testList->GetSize(), 2);
//     EXPECT_EQ(testList->GetRoot(), testNode1);
//     EXPECT_EQ(testList->GetTail(), testNode4);
//     EXPECT_EQ(testNode1->nextNode, testNode4);
//     EXPECT_EQ(testNode4->previousNode, testNode1);
//     // Remove tail with out of bounds iterator (testNode1)
//     testList->RemoveNode(123);
//     EXPECT_EQ(testList->GetSize(), 1);
//     EXPECT_EQ(testList->GetRoot(), testNode1);
//     EXPECT_EQ(testList->GetTail(), testNode1);
//     // Empty list, remove tail
//     testList->RemoveNode(-1);
//     EXPECT_EQ(testList->GetSize(), 0);
//     EXPECT_EQ(testList->GetRoot(), nullptr);
//     EXPECT_EQ(testList->GetTail(), nullptr);
//     // Repopulate with just two elements, remove root (testNode1, testNode2)
//     testList->AppendNode(testNode1);
//     testList->AppendNode(testNode2);
//     testList->RemoveNode(0);
//     EXPECT_EQ(testList->GetSize(), 1);
//     EXPECT_EQ(testList->GetRoot(), testNode2);
//     EXPECT_EQ(testList->GetTail(), testNode2);
//     // Empty list, remove root
//     testList->RemoveNode(0);
//     EXPECT_EQ(testList->GetSize(), 0);
//     EXPECT_EQ(testList->GetRoot(), nullptr);
//     EXPECT_EQ(testList->GetTail(), nullptr);
// }

// /////////////////////////////////////////
// // Card Class Tests
// /////////////////////////////////////////

// // Card class test
// TEST_F(test_x, CardClassConst) {
//     for (int i = 0; i < 4; i++) {
//         for (int j = 0; j < 13; j++) {
//             std::shared_ptr<Card> testCard(new Card(Ranks[j], Suits[i]));
//             ASSERT_EQ(testCard->GetRank(), Ranks[j]);
//             ASSERT_EQ(testCard->GetSuit(), Suits[i]);
//             if (j == 0) {
//                 ASSERT_EQ(testCard->GetCardValue(), 11);
//             }
//             else if (j >= 1 && j <= 8) {
//                 ASSERT_EQ(testCard->GetCardValue(), j+1);
//             }
//             else {
//                 ASSERT_EQ(testCard->GetCardValue(), 10);
//             }
//         }
//     }
//     std::shared_ptr<Card> testCard(new Card(Ranks[0], Suits[0]));
//     ASSERT_EQ(testCard->GetCardValue(), 11);
//     testCard->SetNewCardValue(123);
//     ASSERT_EQ(testCard->GetCardValue(), 123);
// }

// /////////////////////////////////////////
// // Shoe Class Tests
// /////////////////////////////////////////
// // Shoe class constructor test
// TEST_F(test_x, ShoeClassConst) {
//     std::shared_ptr<Shoe> testShoe(new Shoe());
//     EXPECT_EQ(testShoe->GetNumOfDecks(), 0);
//     EXPECT_EQ(testShoe->GetCardsInShoe()->GetSize(), 0);
// }

// // Shoe class setter test
// TEST_F(test_x, ShoeClassSet) {
//     std::shared_ptr<Shoe> testShoe(new Shoe());
//     // Set deck count
//     int deckCount = 13;
//     testShoe->SetNumOfDecks(deckCount);
//     EXPECT_EQ(testShoe->GetNumOfDecks(), deckCount);
//     // Append a card to the shoe of cards
//     std::shared_ptr<Card> testCard1(new Card(Ranks[0], Suits[0]));
//     std::shared_ptr<node<Card>> testNode1 = testShoe->GetCardsInShoe()->InitNode(testCard1);
//     testShoe->SetCardsInShoe(testNode1);
//     EXPECT_EQ(testShoe->GetCardsInShoe()->GetSize(), 1);
// }

// // Shoe class create shoe test
// TEST_F(test_x, ShoeClassCreate) {
//     std::shared_ptr<Shoe> testShoe(new Shoe());
//     // Set deck count
//     for (int i = 1; i <= 10; i++) {
//         testShoe->SetNumOfDecks(i);
//         testShoe->CreateShoeSim();
//         EXPECT_EQ(testShoe->GetCardsInShoe()->GetSize(), testShoe->GetNumOfDecks()*52);
//         testShoe->EmptyShoe();
//         EXPECT_EQ(testShoe->GetCardsInShoe()->GetSize(), 0);
//     }
// }

// // Shoe class, draw test
// TEST_F(test_x, ShoeClassDraw) {
//     std::shared_ptr<Shoe> testShoe(new Shoe());
//     testShoe->SetNumOfDecks(1);
//     testShoe->CreateShoeSim();
//     EXPECT_EQ(testShoe->GetCardsInShoe()->GetSize(), testShoe->GetNumOfDecks()*52);
//     for (int i = testShoe->GetNumOfDecks()*52; i > 0; i--) {
//         std::shared_ptr<Card> poppedCard = testShoe->Draw();
//         EXPECT_EQ(testShoe->GetCardsInShoe()->GetSize(), i - 1);
//     }
// }

// /////////////////////////////////////////
// // Hand Class Test
// /////////////////////////////////////////

// // Hand class, constructor test
// TEST_F(test_x, HandClassConst) {
//     std::shared_ptr<Hand> testHand(new Hand);
//     // Test initial table values
//     EXPECT_EQ(testHand->GetHashTable()->GetTable().size(), HASTABLESIZE);
//     EXPECT_EQ(testHand->GetHashTable()->GetHashFuncIterations(), HASHTABLEITERATIONS);
//     for (int i = 0; i < testHand->GetHashTable()->GetTable().size(); i++) {
//         EXPECT_FALSE(testHand->GetHashTable()->GetTable().at(i));
//     }
//     // Test initial float values
//     EXPECT_EQ(testHand->GetBankTotal(), 0);
//     EXPECT_EQ(testHand->GetInsuranceWager(), 0);
//     EXPECT_EQ(testHand->GetNet(), 0);
//     EXPECT_EQ(testHand->GetWager(), 0);
//     // Test initial integer values
//     EXPECT_EQ(testHand->GetCardsTotal(), 0);
//     EXPECT_EQ(testHand->GetHandsBlackjack(), 0);
//     EXPECT_EQ(testHand->GetHandsLost(), 0);
//     EXPECT_EQ(testHand->GetHandsPlayed(), 0);
//     EXPECT_EQ(testHand->GetHandsPushed(), 0);
//     EXPECT_EQ(testHand->GetHandsWon(), 0);
//     // Test initial string values
//     EXPECT_EQ(testHand->GetDisplayBankTotal(), "");
//     EXPECT_EQ(testHand->GetDisplayCardsTotal(), "");
//     EXPECT_EQ(testHand->GetDisplayInsuranceWager(), "");
//     EXPECT_EQ(testHand->GetDisplayName(), "");
//     EXPECT_EQ(testHand->GetDisplayNet(), "");
//     EXPECT_EQ(testHand->GetDisplayWager(), "");
//     EXPECT_EQ(testHand->GetName(), "");
//     // Test linked list sizes
//     EXPECT_EQ(testHand->GetHandBankTotals()->GetSize(), 0);
//     EXPECT_EQ(testHand->GetHandCardTotals()->GetSize(), 0);
//     EXPECT_EQ(testHand->GetHandNets()->GetSize(), 0);
//     EXPECT_EQ(testHand->GetHandPlayed()->GetSize(), 0);
//     EXPECT_EQ(testHand->GetHandWagers()->GetSize(), 0);
//     EXPECT_EQ(testHand->GetPlayerCards()->GetSize(), 0);
// }

// // Hand class, set name test
// TEST_F(test_x, HandClassName) {
//     // Create object
//     std::shared_ptr<Hand> testHand(new Hand);
//     EXPECT_TRUE(testHand->GetName() == "");
//     testHand->NameSim("Borby");
//     EXPECT_TRUE(testHand->GetName() == "Borby");
//     testHand->NameSim("Borby Johnson");
//     EXPECT_TRUE(testHand->GetName() == "Borby Johnson");
//     testHand->NameSim("Dealer");
//     EXPECT_TRUE(testHand->GetName() == "Dealer");
//     testHand->GetName().clear();
//     EXPECT_TRUE(testHand->GetName() == "");
// }

// // Hand class, add card to hand test
// TEST_F(test_x, HandClassAdd) {
//     // Create test hand, shoe, and card
//     std::shared_ptr<Hand> testHand(new Hand);
//     std::shared_ptr<Shoe> testShoe(new Shoe);
//     std::shared_ptr<Card> testCard(new Card);
//     std::shared_ptr<node<Card>> testNode;
//     // Add Ace to hand
//     testCard = std::make_shared<Card>(Ranks[0], Suits[0]);
//     testNode = testShoe->GetCardsInShoe()->InitNode(testCard);
//     testHand->AddCardToHand(testNode);
//     EXPECT_EQ(testHand->GetPlayerCards()->GetSize(), 1);
//     EXPECT_EQ(testHand->GetCardsTotal(), 11);
//     // Add King to hand
//     testCard = std::make_shared<Card>(Ranks[12], Suits[0]);
//     testNode = testShoe->GetCardsInShoe()->InitNode(testCard);
//     testHand->AddCardToHand(testNode);
//     EXPECT_EQ(testHand->GetPlayerCards()->GetSize(), 2);
//     EXPECT_EQ(testHand->GetCardsTotal(), 21);
//     // Add another Ace to hand
//     testCard = std::make_shared<Card>(Ranks[0], Suits[0]);
//     testNode = testShoe->GetCardsInShoe()->InitNode(testCard);
//     testHand->AddCardToHand(testNode);
//     EXPECT_EQ(testHand->GetPlayerCards()->GetSize(), 3);
//     EXPECT_EQ(testHand->GetCardsTotal(), 12);
//     // Add a Nine to hand
//     testCard = std::make_shared<Card>(Ranks[8], Suits[0]);
//     testNode = testShoe->GetCardsInShoe()->InitNode(testCard);
//     testHand->AddCardToHand(testNode);
//     EXPECT_EQ(testHand->GetPlayerCards()->GetSize(), 4);
//     EXPECT_EQ(testHand->GetCardsTotal(), 21);
//     // Add a Nine to hand
//     testCard = std::make_shared<Card>(Ranks[8], Suits[0]);
//     testNode = testShoe->GetCardsInShoe()->InitNode(testCard);
//     testHand->AddCardToHand(testNode);
//     EXPECT_EQ(testHand->GetPlayerCards()->GetSize(), 5);
//     EXPECT_EQ(testHand->GetCardsTotal(), 30);
// }

// // Hand class, bank deposit test
// TEST_F(test_x, HandClassDeposit) {
//     // Create test hand
//     std::shared_ptr<Hand> testHand(new Hand);
//     float value;
//     for (int i = 0; i < 200; i++) {
//         value = static_cast<int>(i);
//         testHand->BankDepositSim(value);
//         EXPECT_EQ(testHand->GetBankTotal(), value);
//     }
// }

// // Hand class, check parameter test
// TEST_F(test_x, HandClassCheckParam) {
//     // Create test hand, shoe, and card
//     std::shared_ptr<Hand> testHand(new Hand);
//     std::shared_ptr<Shoe> testShoe(new Shoe);
//     std::shared_ptr<Card> testCard(new Card);
//     std::shared_ptr<node<Card>> testNode;
//     // Iterate over all possibilities
//     for (int i = 0; i < 13; i++) {
//         for (int j = 0; j < 4; j++) {
//             testCard = std::make_shared<Card>(Ranks[i], Suits[j]);
//             testNode = testShoe->GetCardsInShoe()->InitNode(testCard);
//             testHand->AddCardToHand(testNode);
//             testHand->CheckParamInHand("R", Ranks[i]);
//             EXPECT_TRUE(testHand->GetHashTable()->Contains("ParamInHand"));
//             testHand->GetHashTable()->ClearHashTable();
//             testHand->CheckParamInHand("S", Suits[j]);
//             EXPECT_TRUE(testHand->GetHashTable()->Contains("ParamInHand"));
//             testHand->GetHashTable()->ClearHashTable();
//             testHand->GetPlayerCards()->RemoveNode(-1);
//         }
//     }
// }

// // Hand class, check same parameter test
// TEST_F(test_x, HandClassCheckSameParam) {
//     // Create test hand, shoe, and card
//     std::shared_ptr<Hand> testHand(new Hand);
//     std::shared_ptr<Shoe> testShoe(new Shoe);
//     std::shared_ptr<Card> testCard1(new Card);
//     std::shared_ptr<Card> testCard2(new Card);
//     std::shared_ptr<node<Card>> testNode1;
//     std::shared_ptr<node<Card>> testNode2;
//     // Iterate over all possibilities, checking random ranks
//     for (int i = 0; i < 13; i++) {
//         testCard1 = std::make_shared<Card>(Ranks[i], Suits[0]);
//         testNode1 = testShoe->GetCardsInShoe()->InitNode(testCard1);
//         testHand->AddCardToHand(testNode1);
//         for (int j = 0; j < 13; j++) {
//             testCard2 = std::make_shared<Card>(Ranks[j], Suits[3]);
//             testNode2 = testShoe->GetCardsInShoe()->InitNode(testCard2);
//             testHand->AddCardToHand(testNode2);
//             testHand->CheckSameParamInHand("R");
//             if (i == j) {
//                 ASSERT_TRUE(testHand->GetHashTable()->Contains("SameParamInHand"));
//             }
//             else {
//                 ASSERT_FALSE(testHand->GetHashTable()->Contains("SameParamInHand"));
//             }
//             testHand->GetHashTable()->ClearHashTable();
//             testHand->CheckSameParamInHand("S");
//             ASSERT_FALSE(testHand->GetHashTable()->Contains("SameParamInHand"));
//             testHand->GetHashTable()->ClearHashTable();
//             testHand->GetPlayerCards()->RemoveNode(-1);
//         }
//         testHand->GetPlayerCards()->RemoveNode(0);
//     }
//     // Iterate over all possibilities, checking random suits
//     for (int i = 0; i < 4; i++) {
//         testCard1 = std::make_shared<Card>(Ranks[0], Suits[i]);
//         testNode1 = testShoe->GetCardsInShoe()->InitNode(testCard1);
//         testHand->AddCardToHand(testNode1);
//         for (int j = 0; j < 4; j++) {
//             testCard2 = std::make_shared<Card>(Ranks[12], Suits[j]);
//             testNode2 = testShoe->GetCardsInShoe()->InitNode(testCard2);
//             testHand->AddCardToHand(testNode2);
//             testHand->CheckSameParamInHand("S");
//             if (i == j) {
//                 ASSERT_TRUE(testHand->GetHashTable()->Contains("SameParamInHand"));
//             }
//             else {
//                 ASSERT_FALSE(testHand->GetHashTable()->Contains("SameParamInHand"));
//             }
//             testHand->GetHashTable()->ClearHashTable();
//             testHand->CheckSameParamInHand("R");
//             ASSERT_FALSE(testHand->GetHashTable()->Contains("SameParamInHand"));
//             testHand->GetHashTable()->ClearHashTable();
//             testHand->GetPlayerCards()->RemoveNode(-1);
//         }
//         testHand->GetPlayerCards()->RemoveNode(0);
//     }
// }

// // Hand class, check for blackjack
// TEST_F(test_x, HandClassCheckBlackjack) {
//     // Create test hand, shoe, and card
//     std::shared_ptr<Hand> testHand(new Hand);
//     std::shared_ptr<Shoe> testShoe(new Shoe);
//     std::shared_ptr<Card> testCard1(new Card);
//     std::shared_ptr<Card> testCard2(new Card);
//     std::shared_ptr<Card> testCard3(new Card);
//     std::shared_ptr<node<Card>> testNode1;
//     std::shared_ptr<node<Card>> testNode2;
//     std::shared_ptr<node<Card>> testNode3;
//     // First card is an Ace
//     testCard1 = std::make_shared<Card>(Card(Ranks[0], Suits[0]));
//     testNode1 = testShoe->GetCardsInShoe()->InitNode(testCard1);
//     testHand->AddCardToHand(testNode1);
//     // Test for false cases
//     for (int i = 0; i < 9; i++) {
//         testCard2 = std::make_shared<Card>(Card(Ranks[i], Suits[0]));
//         testNode2 = testShoe->GetCardsInShoe()->InitNode(testCard2);
//         testHand->AddCardToHand(testNode2);
//         testHand->CheckBlackJack();
//         ASSERT_FALSE(testHand->GetHashTable()->Contains("HasBlackjack"));
//         ASSERT_EQ(testHand->GetPlayerCards()->GetSize(), 2);
//         testHand->GetPlayerCards()->RemoveNode(-1);
//         testHand->GetHashTable()->ClearHashTable();
//     }
//     // Test for true cases
//     for (int i = 9; i < 13; i++) {
//         testCard2 = std::make_shared<Card>(Card(Ranks[i], Suits[0]));
//         testNode2 = testShoe->GetCardsInShoe()->InitNode(testCard2);
//         testHand->AddCardToHand(testNode2);
//         testHand->CheckBlackJack();
//         ASSERT_TRUE(testHand->GetHashTable()->Contains("HasBlackjack"));
//         ASSERT_EQ(testHand->GetPlayerCards()->GetSize(), 2);
//         testHand->GetPlayerCards()->RemoveNode(-1);
//         testHand->GetHashTable()->ClearHashTable();
//     }
//     // Add second card to player hand
//     testCard3 = std::make_shared<Card>(Card(Ranks[1], Suits[0]));
//     testNode3 = testShoe->GetCardsInShoe()->InitNode(testCard3);
//     testHand->AddCardToHand(testNode3);
//     // Test for false case
//     for (int i = 0; i < 13; i++) {
//         testCard2 = std::make_shared<Card>(Card(Ranks[i], Suits[0]));
//         testNode2 = testShoe->GetCardsInShoe()->InitNode(testCard2);
//         testHand->AddCardToHand(testNode2);
//         testHand->CheckBlackJack();
//         ASSERT_FALSE(testHand->GetHashTable()->Contains("HasBlackjack"));
//         ASSERT_EQ(testHand->GetPlayerCards()->GetSize(), 3);
//         testHand->GetPlayerCards()->RemoveNode(-1);
//         testHand->GetHashTable()->ClearHashTable();
//     }
// }

// // Hand class, hit hand test
// TEST_F(test_x, HandClassHitHand) {
//     // Create test hand, shoe, and card
//     std::shared_ptr<Hand> testHand(new Hand);
//     std::shared_ptr<Shoe> testShoe(new Shoe);
//     testShoe->SetNumOfDecks(1);
//     testShoe->CreateShoeSim();
//     int handCardCounter = 0;
//     for (int i = 52; i > 0; i--) {
//         handCardCounter++;
//         EXPECT_EQ(testShoe->GetCardsInShoe()->GetSize(), i);
//         testHand->HitHand(testShoe);
//         EXPECT_EQ(testHand->GetPlayerCards()->GetSize(), handCardCounter);
//     }
// }

// // Hand class, update hand test
// TEST_F(test_x, HandClassUpdate) {
//     std::shared_ptr<Hand> testHand(new Hand);
//     int bankValue = 100;
//     int loopValue = 1;
//     int wagerValue = loopValue;
//     testHand->SetBankTotal(bankValue);
//     // Test deposit
//     while (testHand->GetBankTotal() > 0) {
//         testHand->SetWager(wagerValue);
//         testHand->UpdateBank(0, testHand->GetWager());
//         EXPECT_EQ(testHand->GetBankTotal(), bankValue - loopValue);
//         loopValue++;
//     }
//     testHand->SetBankTotal(bankValue);
//     loopValue = 1;
//     wagerValue = loopValue;
//     // Test win
//     while (testHand->GetBankTotal() < 200) {
//         testHand->SetWager(wagerValue);
//         testHand->UpdateBank(0, testHand->GetWager());
//         testHand->UpdateBank(1, testHand->GetWager());
//         EXPECT_EQ(testHand->GetBankTotal(), bankValue + loopValue);
//         loopValue++;
//     }
//     testHand->SetBankTotal(bankValue);
//     loopValue = 1;
//     wagerValue = loopValue;
//     // Test loss
//     while(testHand->GetBankTotal() > 0) {
//         testHand->SetWager(wagerValue);
//         testHand->UpdateBank(0, testHand->GetWager());
//         testHand->UpdateBank(2, testHand->GetWager());
//         EXPECT_EQ(testHand->GetBankTotal(), bankValue - loopValue);
//         loopValue++;
//     }
//     testHand->SetBankTotal(bankValue);
//     loopValue = 1;
//     wagerValue = loopValue;
//     // Test push
//     while (loopValue < 100) {
//         testHand->SetWager(wagerValue);
//         testHand->UpdateBank(0, testHand->GetWager());
//         testHand->UpdateBank(3, testHand->GetWager());
//         EXPECT_EQ(testHand->GetBankTotal(), bankValue);
//         loopValue++;
//     }
//     testHand->SetBankTotal(bankValue);
//     loopValue = 1;
//     wagerValue = loopValue;
//     // Test blackjack
//     while (testHand->GetBankTotal() < 250) {
//         testHand->SetWager(wagerValue);
//         testHand->UpdateBank(0, testHand->GetWager());
//         testHand->UpdateBank(4, testHand->GetWager());
//         EXPECT_EQ(testHand->GetBankTotal(), bankValue + 1.5*loopValue);
//         loopValue++;
//     }
//     testHand->SetBankTotal(bankValue);
//     loopValue = 1;
//     wagerValue = loopValue;
//     // Test insurance
//     while (testHand->GetBankTotal() < 200) {
//         testHand->SetWager(wagerValue);
//         testHand->SetInsuranceWager(testHand->GetWager());
//         testHand->UpdateBank(0, testHand->GetWager());
//         testHand->UpdateBank(5, testHand->GetInsuranceWager());
//         EXPECT_EQ(testHand->GetBankTotal(), bankValue + 2.0*loopValue);
//         loopValue++;
//     }  
// }

// // Hand class, place wager
// TEST_F(test_x, HandClassPlaceWager) {
//     // Create objects
//     std::shared_ptr<Hand> testHand(new Hand);
//     testHand->BankDepositSim(100);
//     float wager = 5;
//     float priorBank = 0;
//     while (testHand->GetBankTotal() >= 0) {
//         priorBank = testHand->GetBankTotal();
//         EXPECT_EQ(testHand->GetBankTotal(), priorBank);
//         testHand->PlaceWagerSim(wager);
//         EXPECT_EQ(testHand->GetBankTotal(), priorBank - testHand->GetWager());
//     }
// }

// // Hand class, create an insurance wager for a player
// TEST_F(test_x, HandClassInsuranceDeposit) {
//     // Create objects
//     std::shared_ptr<Hand> testHand(new Hand);
//     testHand->BankDepositSim(100);
//     float wager = 5;
//     float priorBank = 0;
//     while (testHand->GetBankTotal() >= 0) {
//         priorBank = testHand->GetBankTotal();
//         // No insurance check
//         {
//             testHand->SetBankTotal(priorBank);
//             testHand->PlaceWagerSim(wager);
//             testHand->InsuranceSim(false);
//             EXPECT_EQ(testHand->GetBankTotal(), priorBank - testHand->GetWager());
//         }
//         // Insurance check
//         {
//             testHand->SetBankTotal(priorBank);
//             testHand->PlaceWagerSim(wager);
//             testHand->InsuranceSim(true);
//             EXPECT_EQ(testHand->GetBankTotal(), priorBank - wager - testHand->GetInsuranceWager());
//         }
//     }
// }

// // Hand class, parameters check test
// TEST_F(test_x, HandClassParameterCheck) {
//     // Create objects
//     std::shared_ptr<Hand> testHand(new Hand);
//     std::shared_ptr<Hand> dealerHand(new Hand);
//     std::shared_ptr<Shoe> testShoe(new Shoe);
//     std::shared_ptr<Card> testCard(new Card);
//     std::shared_ptr<node<Card>> testNode;
//     testCard = std::make_shared<Card>(Ranks[0], Suits[0]);
//     testNode = testShoe->GetCardsInShoe()->InitNode(testCard);
//     dealerHand->AddCardToHand(testNode);
//     dealerHand->AddCardToHand(testNode);
//     testHand->AddCardToHand(testNode);
//     testHand->AddCardToHand(testNode);
//     testHand->SetBankTotal(100);
//     testHand->SetName("Borby");
//     // Test can double down
//     for (int i = 1; i <= 200; i++) {
//         testHand->SetWager(i);
//         {
//             {
//                 testHand->ParametersCheck(dealerHand);
//                 if (testHand->GetBankTotal() >= testHand->GetWager()) {
//                     EXPECT_TRUE(testHand->GetHashTable()->Contains("CanDoubleDown"));
//                 }
//                 else {
//                     EXPECT_FALSE(testHand->GetHashTable()->Contains("CanDoubleDown"));
//                 }
//             }
//             testHand->GetHashTable()->ClearHashTable();
//             testHand->GetHashTable()->AddToTable("DoubleDownResponse");
//             {
//                 testHand->GetHashTable()->AddToTable("CanDoubleDown");
//                 testHand->ParametersCheck(dealerHand);
//                 EXPECT_FALSE(testHand->GetHashTable()->Contains("CanDoubleDown"));
//             }
//             testHand->GetHashTable()->ClearHashTable();
//         }
//         testHand->GetHashTable()->AddToTable("HasHit");
//         testHand->ParametersCheck(dealerHand);
//         EXPECT_FALSE(testHand->GetHashTable()->Contains("CanDoubleDown"));
//         testHand->GetHashTable()->ClearHashTable();
//     }
//     testHand->GetPlayerCards()->ClearList();
//     // Soft seventeen check
//     // (Ace, Ace, Ace, Ace, Ace, Ace, Ace)
//     for (int i = 1; i <= 7; i++) {
//         testCard = std::make_shared<Card>(Ranks[0], Suits[0]);
//         testNode = testShoe->GetCardsInShoe()->InitNode(testCard);
//         testHand->AddCardToHand(testNode);  
//     }
//     testHand->GetHashTable()->AddToTable("SoftSevenTeen");
//     testHand->ParametersCheck(dealerHand);
//     EXPECT_TRUE(testHand->GetHashTable()->Contains("SoftSevenTeen"));
//     testHand->GetPlayerCards()->ClearList();
//     testHand->GetHashTable()->ClearHashTable();
//     // (King, 7)
//     testCard = std::make_shared<Card>(Ranks[12], Suits[0]);
//     testNode = testShoe->GetCardsInShoe()->InitNode(testCard);
//     testHand->AddCardToHand(testNode);
//     testCard = std::make_shared<Card>(Ranks[6], Suits[0]);
//     testNode = testShoe->GetCardsInShoe()->InitNode(testCard);
//     testHand->AddCardToHand(testNode);
//     testHand->GetHashTable()->AddToTable("SoftSevenTeen");
//     testHand->ParametersCheck(dealerHand);
//     EXPECT_FALSE(testHand->GetHashTable()->Contains("SoftSevenTeen"));
//     testHand->GetPlayerCards()->ClearList();
//     testHand->GetHashTable()->ClearHashTable();
//     // (Queen, Ace, Ace, Ace, Ace, Ace, Ace, Ace, Ace)
//     testCard = std::make_shared<Card>(Ranks[11], Suits[0]);
//     testNode = testShoe->GetCardsInShoe()->InitNode(testCard);
//     testHand->AddCardToHand(testNode);
//     for (int i = 1; i <= 7; i++) {
//         testCard = std::make_shared<Card>(Ranks[0], Suits[0]);
//         testNode = testShoe->GetCardsInShoe()->InitNode(testCard);
//         testHand->AddCardToHand(testNode);  
//     }
//     testHand->GetHashTable()->AddToTable("SoftSevenTeen");
//     testHand->ParametersCheck(dealerHand);
//     EXPECT_FALSE(testHand->GetHashTable()->Contains("SoftSevenTeen"));
//     testHand->GetPlayerCards()->ClearList();
//     testHand->AddCardToHand(testNode);
//     testHand->AddCardToHand(testNode);
//     dealerHand->GetPlayerCards()->ClearList();
//     testHand->GetHashTable()->ClearHashTable();
//     // Insurance check
//     for (int i = 0; i < 13; i++) {
//         testCard = std::make_shared<Card>(Ranks[i], Suits[0]);
//         testNode = testShoe->GetCardsInShoe()->InitNode(testCard);
//         dealerHand->AddCardToHand(testNode);
//         for (int j = 0; j < 13; j++) {
//             testCard = std::make_shared<Card>(Ranks[j], Suits[0]);
//             testNode = testShoe->GetCardsInShoe()->InitNode(testCard);
//             dealerHand->AddCardToHand(testNode);
//             dealerHand->CheckBlackJack();
//             if (dealerHand->GetPlayerCards()->RetrieveNode(-1)->data.GetRank() == Ranks[0] && !dealerHand->GetHashTable()->Contains("HasBlackjack")) {
//                 for (int k = 1; k <= 400; k++) {
//                     testHand->SetWager(k);
//                     testHand->GetHashTable()->AddToTable("CanBuyInsurance");
//                     testHand->ParametersCheck(dealerHand);
//                     if (k <= 200) {
//                         EXPECT_TRUE(testHand->GetHashTable()->Contains("CanBuyInsurance"));
//                     }
//                     else {
//                         EXPECT_FALSE(testHand->GetHashTable()->Contains("CanBuyInsurance"));
//                     }
//                     testHand->GetHashTable()->ClearHashTable();
//                 }
//             }
//             else {
//                 testHand->GetHashTable()->AddToTable("CanBuyInsurance");
//                 testHand->ParametersCheck(dealerHand);
//                 EXPECT_FALSE(testHand->GetHashTable()->Contains("CanBuyInsurance"));
//             }
//             dealerHand->GetPlayerCards()->RemoveNode(-1);
//             testHand->GetHashTable()->ClearHashTable();
//             dealerHand->GetHashTable()->ClearHashTable();
//         }
//         dealerHand->GetPlayerCards()->RemoveNode(0);
//         dealerHand->GetHashTable()->ClearHashTable();
//     }
//     testHand->GetPlayerCards()->ClearList();
//     testHand->GetHashTable()->ClearHashTable();
//     dealerHand->AddCardToHand(testNode);
//     dealerHand->AddCardToHand(testNode);
//     // Can split hand check
//     for (int i = 0; i < 13; i++) {
//         testCard = std::make_shared<Card>(Ranks[i], Suits[0]);
//         testNode = testShoe->GetCardsInShoe()->InitNode(testCard);
//         testHand->AddCardToHand(testNode);
//         for (int j = 0; j < 13; j++) {
//             testCard = std::make_shared<Card>(Ranks[j], Suits[0]);
//             testNode = testShoe->GetCardsInShoe()->InitNode(testCard);
//             testHand->AddCardToHand(testNode);
//             testHand->CheckSameParamInHand("R");
//             if (testHand->GetHashTable()->Contains("SameParamInHand")) {
//                 for (int k = 1; k <= 200; k++) {
//                     testHand->SetWager(k);
//                     testHand->GetHashTable()->AddToTable("CanSplitAces");
//                     testHand->GetHashTable()->AddToTable("CanSplitHand");
//                     testHand->ParametersCheck(dealerHand);
//                     testHand->CheckParamInHand("R", Ranks[0]);
//                     if (k <= 100) {
//                         if (testHand->GetHashTable()->Contains("ParamInHand")) {
//                             EXPECT_TRUE(testHand->GetHashTable()->Contains("CanSplitAces"));
//                             EXPECT_FALSE(testHand->GetHashTable()->Contains("CanSplitHand"));
//                         }
//                         else {
//                             EXPECT_FALSE(testHand->GetHashTable()->Contains("CanSplitAces"));
//                             EXPECT_TRUE(testHand->GetHashTable()->Contains("CanSplitHand"));
//                         }
//                     }
//                     else {
//                         EXPECT_FALSE(testHand->GetHashTable()->Contains("CanSplitAces"));
//                         EXPECT_FALSE(testHand->GetHashTable()->Contains("CanSplitHand"));
//                     }
//                     testHand->GetHashTable()->ClearHashTable();
//                 }
//             }
//             else {
//                 testHand->GetHashTable()->AddToTable("CanSplitAces");
//                 testHand->GetHashTable()->AddToTable("CanSplitHand");
//                 testHand->ParametersCheck(dealerHand);
//                 EXPECT_FALSE(testHand->GetHashTable()->Contains("CanSplitAces"));
//                 EXPECT_FALSE(testHand->GetHashTable()->Contains("CanSplitHand"));
//             }
//             testHand->GetPlayerCards()->RemoveNode(-1);
//             testHand->GetHashTable()->ClearHashTable();
//         }
//         testHand->GetPlayerCards()->RemoveNode(0);
//         testHand->GetHashTable()->ClearHashTable();
//     }
// }

// // Hand class, reset test
// TEST_F(test_x, HandClassReset) {
//     std::shared_ptr<Hand> testHand(new Hand);
//     std::shared_ptr<Shoe> testShoe(new Shoe);
//     testShoe->SetNumOfDecks(1);
//     testShoe->CreateShoeSim();
//     // Set dummy values
//     testHand->SetName("Borby");
//     testHand->SetBankTotal(100);
//     testHand->SetWager(10);
//     testHand->SetInsuranceWager(5);
//     testHand->SetNet(5);
//     testHand->HitHand(testShoe);
//     testHand->HitHand(testShoe);
//     EXPECT_EQ(testHand->GetName(), "Borby");
//     EXPECT_EQ(testHand->GetPlayerCards()->GetSize(), 2);
//     EXPECT_EQ(testHand->GetBankTotal(), 100);
//     EXPECT_EQ(testHand->GetInsuranceWager(), 5);
//     EXPECT_EQ(testHand->GetNet(), 5);
//     EXPECT_EQ(testHand->GetWager(), 10);
//     for (int i = 0; i < 4; i++) {
//         for (int j = 0; j < 5; j++) {
//             testHand->GetHashTable()->AddToTable(testHand->GetTableMatrix()[i][j]);
//             EXPECT_TRUE(testHand->GetHashTable()->Contains(testHand->GetTableMatrix()[i][j]));
//             // unsigned int testHash = testHand->GetHashTable()->CalculateHashCode(testHand->GetTableMatrix()[i][j]);
//             // unsigned int testBucket = testHash % testHand->GetHashTable()->GetTable().size();
//             // std::cout << color_text(31, testHand->GetTableMatrix()[i][j]) << " " << color_text(32, std::to_string(testHash)) << " " << color_text(34, std::to_string(testBucket)) << std::endl;
//         }
//     }
//     // Reset Hand
//     testHand->ResetHand();
//     EXPECT_EQ(testHand->GetPlayerCards()->GetSize(), 0);
//     EXPECT_EQ(testHand->GetBankTotal(), 100);
//     EXPECT_EQ(testHand->GetInsuranceWager(), 0);
//     EXPECT_EQ(testHand->GetNet(), 0);
//     EXPECT_EQ(testHand->GetWager(), 0);
//     for (int i = 0; i < 4; i++) {
//         for (int j = 0; j < 5; j++) {
//             EXPECT_FALSE(testHand->GetHashTable()->Contains(testHand->GetTableMatrix()[i][j]));
//         }
//     }
// }

// // Hand class, copy variables test
// TEST_F(test_x, HandClassCopy) {
//     std::shared_ptr<Hand> hand1(new Hand);
//     std::shared_ptr<Hand> hand1Copy(new Hand);
//     hand1->SetName("Borby");
//     hand1->SetBankTotal(100);
//     hand1->SetWager(10);
//     hand1Copy->CopyVariables(hand1);
//     ASSERT_EQ(hand1->GetName(), "Borby");
//     ASSERT_EQ(hand1->GetBankTotal(), 100);
//     ASSERT_EQ(hand1->GetWager(), 10);
//     ASSERT_EQ(hand1Copy->GetName(), "Borby");
//     ASSERT_EQ(hand1Copy->GetBankTotal(), 100);
//     ASSERT_EQ(hand1Copy->GetWager(), 10);
// }

// /////////////////////////////////////////
// // Core Functions Tests
// /////////////////////////////////////////

// // Blackjack strategy test, no duplicate ranks, no ace in hand off deal
// TEST_F(test_x, BlackjackStrat){
//     // Create hands and card objects
//     std::shared_ptr<Hand> userHand(new Hand);
//     std::shared_ptr<Hand> dealerHand(new Hand);
//     std::shared_ptr<Card> testCard(new Card);
//     std::shared_ptr<node<Card>> testNode;
//     userHand->SetBankTotal(100);
//     // Add first card to dealer
//     testCard = std::make_shared<Card>(Ranks[0], Suits[0]);
//     testNode = dealerHand->GetPlayerCards()->InitNode(testCard);
//     dealerHand->SetPlayerCards(testNode);
//     // Add dummy cards to user hand
//     testCard = std::make_shared<Card>(Ranks[1], Suits[0]);
//     testNode = userHand->GetPlayerCards()->InitNode(testCard);
//     userHand->SetPlayerCards(testNode);
//     testCard = std::make_shared<Card>(Ranks[12], Suits[0]);
//     testNode = userHand->GetPlayerCards()->InitNode(testCard);
//     userHand->SetPlayerCards(testNode);
//     // Player has a card total of 4 through 8
//     for (int i = 4; i <= 8; i++) {
//         userHand->SetCardsTotal(i);
//         userHand->SetWager(10);
//         for (int j = 0; j < 13; j++) {
//             // Add card to dealer hand
//             testCard = std::make_shared<Card>(Ranks[j], Suits[0]);
//             testNode = dealerHand->GetPlayerCards()->InitNode(testCard);
//             dealerHand->SetPlayerCards(testNode);
//             blackjack_strategy(userHand, dealerHand, false, false);
//             EXPECT_FALSE(userHand->GetHashTable()->Contains(userHand->GetTableMatrix()[2][3]));
//             EXPECT_TRUE(userHand->GetHashTable()->Contains(userHand->GetTableMatrix()[2][4]));
//             EXPECT_FALSE(userHand->GetHashTable()->Contains(userHand->GetTableMatrix()[3][0]));
//             EXPECT_FALSE(userHand->GetHashTable()->Contains(userHand->GetTableMatrix()[3][1]));
//             dealerHand->GetPlayerCards()->RemoveNode(-1);
//             userHand->GetHashTable()->ClearHashTable();
//         }
//     }
//     // Player has a card total of 9
//     userHand->SetCardsTotal(9);
//     for (int i = 0; i < 13; i++) {
//         // Add card to dealer hand
//         testCard = std::make_shared<Card>(Ranks[i], Suits[0]);
//         testNode = dealerHand->GetPlayerCards()->InitNode(testCard);
//         dealerHand->SetPlayerCards(testNode);
//         // Dealer has a 2 - 6
//         if (i != 0 && i < 6) {
//             // Test strategy for if a player can double down
//             {   
//                 // Set wager
//                 userHand->SetWager(10);
//                 // Test strategy
//                 blackjack_strategy(userHand, dealerHand, false, false);
//                 EXPECT_TRUE(userHand->GetHashTable()->Contains(userHand->GetTableMatrix()[2][3]));
//                 EXPECT_TRUE(userHand->GetHashTable()->Contains(userHand->GetTableMatrix()[2][4]));
//                 EXPECT_FALSE(userHand->GetHashTable()->Contains(userHand->GetTableMatrix()[3][0]));
//                 EXPECT_FALSE(userHand->GetHashTable()->Contains(userHand->GetTableMatrix()[3][1]));
//                 userHand->GetHashTable()->ClearHashTable();
//             }
//             // Test strategy for if a player cannot double down
//             {
//                 // Set wager
//                 userHand->SetWager(200);
//                 // Test strategy
//                 blackjack_strategy(userHand, dealerHand, false, false);
//                 EXPECT_FALSE(userHand->GetHashTable()->Contains(userHand->GetTableMatrix()[2][3]));
//                 EXPECT_TRUE(userHand->GetHashTable()->Contains(userHand->GetTableMatrix()[2][4]));
//                 EXPECT_FALSE(userHand->GetHashTable()->Contains(userHand->GetTableMatrix()[3][0]));
//                 EXPECT_FALSE(userHand->GetHashTable()->Contains(userHand->GetTableMatrix()[3][1]));
//                 userHand->GetHashTable()->ClearHashTable();
//             }
//         }
//         // Otherwise
//         else {
//             // Set wager
//             userHand->SetWager(10);
//             // Test strategy
//             blackjack_strategy(userHand, dealerHand, false, false);
//             EXPECT_FALSE(userHand->GetHashTable()->Contains(userHand->GetTableMatrix()[2][3]));
//             EXPECT_TRUE(userHand->GetHashTable()->Contains(userHand->GetTableMatrix()[2][4]));
//             EXPECT_FALSE(userHand->GetHashTable()->Contains(userHand->GetTableMatrix()[3][0]));
//             EXPECT_FALSE(userHand->GetHashTable()->Contains(userHand->GetTableMatrix()[3][1]));
//             userHand->GetHashTable()->ClearHashTable();
//         }    
//         dealerHand->GetPlayerCards()->RemoveNode(-1);
//     }
//     // Player has a card total of 10
//     userHand->SetCardsTotal(10);
//     for (int i = 0; i < 13; i++) {
//         // Add card to dealer hand
//         testCard = std::make_shared<Card>(Ranks[i], Suits[0]);
//         testNode = dealerHand->GetPlayerCards()->InitNode(testCard);
//         dealerHand->SetPlayerCards(testNode);
//         // Dealer has a 2 - 9
//         if (i != 0 && i < 9) {
//             // Test strategy for if a player can double down
//             {
//                 // Set wager
//                 userHand->SetWager(10);
//                 // Test strategy
//                 blackjack_strategy(userHand, dealerHand, false, false);
//                 EXPECT_TRUE(userHand->GetHashTable()->Contains(userHand->GetTableMatrix()[2][3]));
//                 EXPECT_TRUE(userHand->GetHashTable()->Contains(userHand->GetTableMatrix()[2][4]));
//                 EXPECT_FALSE(userHand->GetHashTable()->Contains(userHand->GetTableMatrix()[3][0]));
//                 EXPECT_FALSE(userHand->GetHashTable()->Contains(userHand->GetTableMatrix()[3][1]));
//                 userHand->GetHashTable()->ClearHashTable();
//             }
//             // Test strategy for if a player cannot double down
//             {
//                 // Set wager
//                 userHand->SetWager(200);
//                 // Test strategy
//                 blackjack_strategy(userHand, dealerHand, false, false);
//                 EXPECT_FALSE(userHand->GetHashTable()->Contains(userHand->GetTableMatrix()[2][3]));
//                 EXPECT_TRUE(userHand->GetHashTable()->Contains(userHand->GetTableMatrix()[2][4]));
//                 EXPECT_FALSE(userHand->GetHashTable()->Contains(userHand->GetTableMatrix()[3][0]));
//                 EXPECT_FALSE(userHand->GetHashTable()->Contains(userHand->GetTableMatrix()[3][1]));
//                 userHand->GetHashTable()->ClearHashTable();
//             }
//         }
//         // Otherwise
//         else {
//             // Set wager
//             userHand->SetWager(10);
//             // Test strategy
//             blackjack_strategy(userHand, dealerHand, false, false);
//             EXPECT_FALSE(userHand->GetHashTable()->Contains(userHand->GetTableMatrix()[2][3]));
//             EXPECT_TRUE(userHand->GetHashTable()->Contains(userHand->GetTableMatrix()[2][4]));
//             EXPECT_FALSE(userHand->GetHashTable()->Contains(userHand->GetTableMatrix()[3][0]));
//             EXPECT_FALSE(userHand->GetHashTable()->Contains(userHand->GetTableMatrix()[3][1]));
//             userHand->GetHashTable()->ClearHashTable();
//         }
//         dealerHand->GetPlayerCards()->RemoveNode(-1);
//     }
//     // Player has a hand card value of 11
//     userHand->SetCardsTotal(11);
//     for (int i = 0; i < 13; i++) {
//         // Player can double down
//         {
//             userHand->SetWager(10);
//             // Add card to dealer hand
//             testCard = std::make_shared<Card>(Ranks[i], Suits[0]);
//             testNode = dealerHand->GetPlayerCards()->InitNode(testCard);
//             dealerHand->SetPlayerCards(testNode);
//             // Test strategy - Can double down
//             blackjack_strategy(userHand, dealerHand, false, false);
//             EXPECT_TRUE(userHand->GetHashTable()->Contains(userHand->GetTableMatrix()[2][3]));
//             EXPECT_TRUE(userHand->GetHashTable()->Contains(userHand->GetTableMatrix()[2][4]));
//             EXPECT_FALSE(userHand->GetHashTable()->Contains(userHand->GetTableMatrix()[3][0]));
//             EXPECT_FALSE(userHand->GetHashTable()->Contains(userHand->GetTableMatrix()[3][1]));
//             userHand->GetHashTable()->ClearHashTable();
//             // Remove last card from dealer hand
//             dealerHand->GetPlayerCards()->RemoveNode(-1);           
//         }
//         // Player cannot double down
//         {
//             userHand->SetWager(200);
//             // Add card to dealer hand
//             testCard = std::make_shared<Card>(Ranks[i], Suits[0]);
//             testNode = dealerHand->GetPlayerCards()->InitNode(testCard);
//             dealerHand->SetPlayerCards(testNode);
//             // Test strategy - Can double down
//             blackjack_strategy(userHand, dealerHand, false, false);
//             EXPECT_FALSE(userHand->GetHashTable()->Contains(userHand->GetTableMatrix()[2][3]));
//             EXPECT_TRUE(userHand->GetHashTable()->Contains(userHand->GetTableMatrix()[2][4]));
//             EXPECT_FALSE(userHand->GetHashTable()->Contains(userHand->GetTableMatrix()[3][0]));
//             EXPECT_FALSE(userHand->GetHashTable()->Contains(userHand->GetTableMatrix()[3][1]));
//             userHand->GetHashTable()->ClearHashTable();
//             // Remove last card from dealer hand
//             dealerHand->GetPlayerCards()->RemoveNode(-1);     
//         }
//     }
//     // Player has a hand card value of 12
//     userHand->SetCardsTotal(12);
//     for (int i = 0; i < 13; i++) {
//         userHand->SetWager(10);
//         // Add card to dealer hand
//         testCard = std::make_shared<Card>(Ranks[i], Suits[0]);
//         testNode = dealerHand->GetPlayerCards()->InitNode(testCard);
//         dealerHand->SetPlayerCards(testNode);
//         blackjack_strategy(userHand, dealerHand, false, false);
//         // Test strategy for 4, 5, and 6 cards
//         if (i == 3 || i == 4 || i == 5) {
//             EXPECT_FALSE(userHand->GetHashTable()->Contains(userHand->GetTableMatrix()[2][3]));
//             EXPECT_FALSE(userHand->GetHashTable()->Contains(userHand->GetTableMatrix()[2][4]));
//             EXPECT_FALSE(userHand->GetHashTable()->Contains(userHand->GetTableMatrix()[3][0]));
//             EXPECT_TRUE(userHand->GetHashTable()->Contains(userHand->GetTableMatrix()[3][1]));
//         }
//         // Test strategy for other cards
//         else {
//             EXPECT_FALSE(userHand->GetHashTable()->Contains(userHand->GetTableMatrix()[2][3]));
//             EXPECT_TRUE(userHand->GetHashTable()->Contains(userHand->GetTableMatrix()[2][4]));
//             EXPECT_FALSE(userHand->GetHashTable()->Contains(userHand->GetTableMatrix()[3][0]));
//             EXPECT_FALSE(userHand->GetHashTable()->Contains(userHand->GetTableMatrix()[3][1]));
//         }
//         dealerHand->GetPlayerCards()->RemoveNode(-1);  
//         userHand->GetHashTable()->ClearHashTable();
//     }
//     // Player has a hand card value of 13 through 16
//     for (int i = 13; i <= 16; i++) {
//         userHand->SetCardsTotal(i);
//         userHand->SetWager(10);
//         for (int j = 0; j < 13; j++) {
//             // Add card to dealer hand
//             testCard = std::make_shared<Card>(Ranks[j], Suits[0]);
//             testNode = dealerHand->GetPlayerCards()->InitNode(testCard);
//             dealerHand->SetPlayerCards(testNode);
//             blackjack_strategy(userHand, dealerHand, false, false);
//             // Test strategy for 2 through 6
//             if (j != 0 && j < 6) {
//                 EXPECT_FALSE(userHand->GetHashTable()->Contains(userHand->GetTableMatrix()[2][3]));
//                 EXPECT_FALSE(userHand->GetHashTable()->Contains(userHand->GetTableMatrix()[2][4]));
//                 EXPECT_FALSE(userHand->GetHashTable()->Contains(userHand->GetTableMatrix()[3][0]));
//                 EXPECT_TRUE(userHand->GetHashTable()->Contains(userHand->GetTableMatrix()[3][1]));
//             }
//             // Test strategy otherwise
//             else {
//                 EXPECT_FALSE(userHand->GetHashTable()->Contains(userHand->GetTableMatrix()[2][3]));
//                 EXPECT_TRUE(userHand->GetHashTable()->Contains(userHand->GetTableMatrix()[2][4]));
//                 EXPECT_FALSE(userHand->GetHashTable()->Contains(userHand->GetTableMatrix()[3][0]));
//                 EXPECT_FALSE(userHand->GetHashTable()->Contains(userHand->GetTableMatrix()[3][1]));
//             }
//             dealerHand->GetPlayerCards()->RemoveNode(-1);
//             userHand->GetHashTable()->ClearHashTable();
//         }
//     }
//     // Player has a hand card value of 17 through 21
//     for (int i = 17; i <= 21; i++) {
//         userHand->SetCardsTotal(i);
//         userHand->SetWager(10);
//         for (int j = 0; j < 13; j++) {
//             // Add card to dealer hand
//             testCard = std::make_shared<Card>(Ranks[j], Suits[0]);
//             testNode = dealerHand->GetPlayerCards()->InitNode(testCard);
//             dealerHand->SetPlayerCards(testNode);
//             blackjack_strategy(userHand, dealerHand, false, false);
//             EXPECT_FALSE(userHand->GetHashTable()->Contains(userHand->GetTableMatrix()[2][3]));
//             EXPECT_FALSE(userHand->GetHashTable()->Contains(userHand->GetTableMatrix()[2][4]));
//             EXPECT_FALSE(userHand->GetHashTable()->Contains(userHand->GetTableMatrix()[3][0]));
//             EXPECT_TRUE(userHand->GetHashTable()->Contains(userHand->GetTableMatrix()[3][1]));
//             dealerHand->GetPlayerCards()->RemoveNode(-1);
//             userHand->GetHashTable()->ClearHashTable();
//         }
//     }
// }

// // Blackjack strategy test, no duplicate ranks, Ace in hand off deal
// TEST_F(test_x, BlackjackStratAces) {
//     // Create hands
//     std::shared_ptr<Hand> userHand(new Hand);
//     std::shared_ptr<Hand> dealerHand(new Hand);
//     std::shared_ptr<Card> testCard(new Card);
//     std::shared_ptr<node<Card>> testNode;
//     userHand->SetBankTotal(100);
//     // Add first card to dealer
//     testCard = std::make_shared<Card>(Ranks[0], Suits[0]);
//     testNode = dealerHand->GetPlayerCards()->InitNode(testCard);
//     dealerHand->SetPlayerCards(testNode);
//     dealerHand->AddHandTotal();
//     // Add first card to player - Ace
//     testCard = std::make_shared<Card>(Ranks[0], Suits[0]);
//     testNode = dealerHand->GetPlayerCards()->InitNode(testCard);
//     userHand->SetPlayerCards(testNode);
//     userHand->AddHandTotal();
//     // Player has a card total of 13 or 14 (Ace, 2 || Ace, 3)
//     for (int i = 1; i <= 2; i++) {
//         testCard = std::make_shared<Card>(Ranks[i], Suits[0]);
//         testNode = dealerHand->GetPlayerCards()->InitNode(testCard);
//         userHand->SetPlayerCards(testNode);
//         userHand->AddHandTotal();
//         for (int j = 0; j < 13; j++) {
//             // Add card to dealer hand
//             testCard = std::make_shared<Card>(Ranks[j], Suits[0]);
//             testNode = dealerHand->GetPlayerCards()->InitNode(testCard);
//             dealerHand->SetPlayerCards(testNode);
//             // Card being added is a 5 or 6
//             if (j == 4 || j == 5) {
//                 // Player can double down
//                 {
//                     // Set wager
//                     userHand->SetWager(10);
//                     // Test strategy - Can double down
//                     blackjack_strategy(userHand, dealerHand, false, false);
//                     EXPECT_TRUE(userHand->GetHashTable()->Contains(userHand->GetTableMatrix()[2][3]));
//                     EXPECT_TRUE(userHand->GetHashTable()->Contains(userHand->GetTableMatrix()[2][4]));
//                     EXPECT_FALSE(userHand->GetHashTable()->Contains(userHand->GetTableMatrix()[3][0]));
//                     EXPECT_FALSE(userHand->GetHashTable()->Contains(userHand->GetTableMatrix()[3][1]));
//                     userHand->GetHashTable()->ClearHashTable();
//                 }
//                 // Player can't double down
//                 {
//                     // Set wager
//                     userHand->SetWager(200);
//                     // Test strategy - Can't double down
//                     blackjack_strategy(userHand, dealerHand, false, false);
//                     EXPECT_FALSE(userHand->GetHashTable()->Contains(userHand->GetTableMatrix()[2][3]));
//                     EXPECT_TRUE(userHand->GetHashTable()->Contains(userHand->GetTableMatrix()[2][4]));
//                     EXPECT_FALSE(userHand->GetHashTable()->Contains(userHand->GetTableMatrix()[3][0]));
//                     EXPECT_FALSE(userHand->GetHashTable()->Contains(userHand->GetTableMatrix()[3][1]));
//                     userHand->GetHashTable()->ClearHashTable();
//                 }
//             }
//             // Otherwise
//             else {
//                 // Set wager
//                 userHand->SetWager(10);
//                 // Test strategy - Can't double down
//                 blackjack_strategy(userHand, dealerHand, false, false);
//                 EXPECT_FALSE(userHand->GetHashTable()->Contains(userHand->GetTableMatrix()[2][3]));
//                 EXPECT_TRUE(userHand->GetHashTable()->Contains(userHand->GetTableMatrix()[2][4]));
//                 EXPECT_FALSE(userHand->GetHashTable()->Contains(userHand->GetTableMatrix()[3][0]));
//                 EXPECT_FALSE(userHand->GetHashTable()->Contains(userHand->GetTableMatrix()[3][1]));
//                 userHand->GetHashTable()->ClearHashTable();
//             }
//             dealerHand->GetPlayerCards()->RemoveNode(-1);
//         }
//         userHand->GetPlayerCards()->RemoveNode(-1);
//         userHand->AddHandTotal();
//     }
//     // Player has a card total of 15 or 16 (Ace, 4 || Ace, 5)
//     for (int i = 3; i <= 4; i++) {
//         testCard = std::make_shared<Card>(Ranks[i], Suits[0]);
//         testNode = dealerHand->GetPlayerCards()->InitNode(testCard);
//         userHand->SetPlayerCards(testNode);
//         userHand->AddHandTotal();
//         for (int j = 0; j < 13; j++) {
//             // Add card to dealer hand
//             testCard = std::make_shared<Card>(Ranks[j], Suits[0]);
//             testNode = dealerHand->GetPlayerCards()->InitNode(testCard);
//             dealerHand->SetPlayerCards(testNode);
//             // Card being added is a 4, 5, or 6
//             if (j == 3 || j == 4 || j == 5) {
//                 // Player can double down
//                 {
//                     // Set wager
//                     userHand->SetWager(10);
//                     // Test strategy - Can double down
//                     blackjack_strategy(userHand, dealerHand, false, false);
//                     EXPECT_TRUE(userHand->GetHashTable()->Contains(userHand->GetTableMatrix()[2][3]));
//                     EXPECT_TRUE(userHand->GetHashTable()->Contains(userHand->GetTableMatrix()[2][4]));
//                     EXPECT_FALSE(userHand->GetHashTable()->Contains(userHand->GetTableMatrix()[3][0]));
//                     EXPECT_FALSE(userHand->GetHashTable()->Contains(userHand->GetTableMatrix()[3][1]));
//                     userHand->GetHashTable()->ClearHashTable();
//                 }
//                 // Player can't double down
//                 {
//                     // Set wager
//                     userHand->SetWager(200);
//                     // Test strategy - Can't double down
//                     blackjack_strategy(userHand, dealerHand, false, false);
//                     EXPECT_FALSE(userHand->GetHashTable()->Contains(userHand->GetTableMatrix()[2][3]));
//                     EXPECT_TRUE(userHand->GetHashTable()->Contains(userHand->GetTableMatrix()[2][4]));
//                     EXPECT_FALSE(userHand->GetHashTable()->Contains(userHand->GetTableMatrix()[3][0]));
//                     EXPECT_FALSE(userHand->GetHashTable()->Contains(userHand->GetTableMatrix()[3][1]));
//                     userHand->GetHashTable()->ClearHashTable();
//                 }
//             }
//             // Otherwise
//             else {
//                 // Set wager
//                 userHand->SetWager(10);
//                 // Test strategy
//                 blackjack_strategy(userHand, dealerHand, false, false);
//                 EXPECT_FALSE(userHand->GetHashTable()->Contains(userHand->GetTableMatrix()[2][3]));
//                 EXPECT_TRUE(userHand->GetHashTable()->Contains(userHand->GetTableMatrix()[2][4]));
//                 EXPECT_FALSE(userHand->GetHashTable()->Contains(userHand->GetTableMatrix()[3][0]));
//                 EXPECT_FALSE(userHand->GetHashTable()->Contains(userHand->GetTableMatrix()[3][1]));
//                 userHand->GetHashTable()->ClearHashTable();
//             }
//             dealerHand->GetPlayerCards()->RemoveNode(-1);
//         }
//         userHand->GetPlayerCards()->RemoveNode(-1);
//         userHand->AddHandTotal();
//     }
//     // Player has a card total of 17 (Ace, 6)
//     {
//         testCard = std::make_shared<Card>(Ranks[5], Suits[0]);
//         testNode = dealerHand->GetPlayerCards()->InitNode(testCard);
//         userHand->SetPlayerCards(testNode);
//         userHand->AddHandTotal();
//         for (int i = 0; i < 13; i++) {
//             // Add card to dealer hand
//             testCard = std::make_shared<Card>(Ranks[i], Suits[0]);
//             testNode = dealerHand->GetPlayerCards()->InitNode(testCard);
//             dealerHand->SetPlayerCards(testNode);
//             if (i >= 2 && i <= 5) {
//                 // Player can double down
//                 {
//                     // Set wager
//                     userHand->SetWager(10);
//                     // Test strategy - Can double down
//                     blackjack_strategy(userHand, dealerHand, false, false);
//                     EXPECT_TRUE(userHand->GetHashTable()->Contains(userHand->GetTableMatrix()[2][3]));
//                     EXPECT_TRUE(userHand->GetHashTable()->Contains(userHand->GetTableMatrix()[2][4]));
//                     EXPECT_FALSE(userHand->GetHashTable()->Contains(userHand->GetTableMatrix()[3][0]));
//                     EXPECT_FALSE(userHand->GetHashTable()->Contains(userHand->GetTableMatrix()[3][1]));
//                     userHand->GetHashTable()->ClearHashTable();
//                 }
//                 // Player can't double down
//                 {
//                     // Set wager
//                     userHand->SetWager(200);
//                     // Test strategy - Can't double down
//                     blackjack_strategy(userHand, dealerHand, false, false);
//                     EXPECT_FALSE(userHand->GetHashTable()->Contains(userHand->GetTableMatrix()[2][3]));
//                     EXPECT_TRUE(userHand->GetHashTable()->Contains(userHand->GetTableMatrix()[2][4]));
//                     EXPECT_FALSE(userHand->GetHashTable()->Contains(userHand->GetTableMatrix()[3][0]));
//                     EXPECT_FALSE(userHand->GetHashTable()->Contains(userHand->GetTableMatrix()[3][1]));
//                     userHand->GetHashTable()->ClearHashTable();
//                 }
//             }
//             // Otherwise
//             else {
//                 // Set wager
//                 userHand->SetWager(10);
//                 // Test strategy
//                 blackjack_strategy(userHand, dealerHand, false, false);
//                 EXPECT_FALSE(userHand->GetHashTable()->Contains(userHand->GetTableMatrix()[2][3]));
//                 EXPECT_TRUE(userHand->GetHashTable()->Contains(userHand->GetTableMatrix()[2][4]));
//                 EXPECT_FALSE(userHand->GetHashTable()->Contains(userHand->GetTableMatrix()[3][0]));
//                 EXPECT_FALSE(userHand->GetHashTable()->Contains(userHand->GetTableMatrix()[3][1]));
//                 userHand->GetHashTable()->ClearHashTable();
//             }
//             dealerHand->GetPlayerCards()->RemoveNode(-1);
//         }
//         userHand->GetPlayerCards()->RemoveNode(-1);
//         userHand->AddHandTotal();
//     }
//     // Player card total is 18 (Ace, 7)
//     {
//         testCard = std::make_shared<Card>(Ranks[6], Suits[0]);
//         testNode = dealerHand->GetPlayerCards()->InitNode(testCard);
//         userHand->SetPlayerCards(testNode);
//         userHand->AddHandTotal();
//         for (int i = 0; i < 13; i++) {
//             // Add card to dealer hand
//             testCard = std::make_shared<Card>(Ranks[i], Suits[0]);
//             testNode = dealerHand->GetPlayerCards()->InitNode(testCard);
//             dealerHand->SetPlayerCards(testNode);
//             if (i == 1 || i == 6 || i == 7) {
//                 // Set wager
//                 userHand->SetWager(10);
//                 // Test strategy
//                 blackjack_strategy(userHand, dealerHand, false, false);
//                 EXPECT_FALSE(userHand->GetHashTable()->Contains(userHand->GetTableMatrix()[2][3]));
//                 EXPECT_FALSE(userHand->GetHashTable()->Contains(userHand->GetTableMatrix()[2][4]));
//                 EXPECT_FALSE(userHand->GetHashTable()->Contains(userHand->GetTableMatrix()[3][0]));
//                 EXPECT_TRUE(userHand->GetHashTable()->Contains(userHand->GetTableMatrix()[3][1]));
//                 userHand->GetHashTable()->ClearHashTable();
//             }
//             else if (i >= 2 && i <= 5) {
//                 // Player can double down
//                 {
//                     // Set wager
//                     userHand->SetWager(10);
//                     // Test strategy - Can double down
//                     blackjack_strategy(userHand, dealerHand, false, false);
//                     EXPECT_TRUE(userHand->GetHashTable()->Contains(userHand->GetTableMatrix()[2][3]));
//                     EXPECT_FALSE(userHand->GetHashTable()->Contains(userHand->GetTableMatrix()[2][4]));
//                     EXPECT_FALSE(userHand->GetHashTable()->Contains(userHand->GetTableMatrix()[3][0]));
//                     EXPECT_TRUE(userHand->GetHashTable()->Contains(userHand->GetTableMatrix()[3][1]));
//                     userHand->GetHashTable()->ClearHashTable();
//                 }
//                 // Player can't double down
//                 {
//                     // Set wager
//                     userHand->SetWager(200);
//                     // Test strategy - Can't double down
//                     blackjack_strategy(userHand, dealerHand, false, false);
//                     EXPECT_FALSE(userHand->GetHashTable()->Contains(userHand->GetTableMatrix()[2][3]));
//                     EXPECT_FALSE(userHand->GetHashTable()->Contains(userHand->GetTableMatrix()[2][4]));
//                     EXPECT_FALSE(userHand->GetHashTable()->Contains(userHand->GetTableMatrix()[3][0]));
//                     EXPECT_TRUE(userHand->GetHashTable()->Contains(userHand->GetTableMatrix()[3][1]));
//                     userHand->GetHashTable()->ClearHashTable();
//                 }
//             }
//             else {
//                 // Set wager
//                 userHand->SetWager(10);
//                 // Test strategy
//                 blackjack_strategy(userHand, dealerHand, false, false);
//                 EXPECT_FALSE(userHand->GetHashTable()->Contains(userHand->GetTableMatrix()[2][3]));
//                 EXPECT_TRUE(userHand->GetHashTable()->Contains(userHand->GetTableMatrix()[2][4]));
//                 EXPECT_FALSE(userHand->GetHashTable()->Contains(userHand->GetTableMatrix()[3][0]));
//                 EXPECT_FALSE(userHand->GetHashTable()->Contains(userHand->GetTableMatrix()[3][1]));
//                 userHand->GetHashTable()->ClearHashTable();
//             }
//             dealerHand->GetPlayerCards()->RemoveNode(-1);
//         }
//         userHand->GetPlayerCards()->RemoveNode(-1);
//         userHand->AddHandTotal();
//     }
//     // Player card total is 19, 20, or 21 (Ace, 8 || Ace, 9 || Ace, Ten)
//     for (int i = 8; i <= 12; i++) {
//         testCard = std::make_shared<Card>(Ranks[i], Suits[0]);
//         testNode = dealerHand->GetPlayerCards()->InitNode(testCard);
//         userHand->SetPlayerCards(testNode);
//         userHand->AddHandTotal();
//         for (int j = 0; j < 13; j++) {
//             // Add card to dealer hand
//             testCard = std::make_shared<Card>(Ranks[j], Suits[0]);
//             testNode = dealerHand->GetPlayerCards()->InitNode(testCard);
//             dealerHand->SetPlayerCards(testNode);
//             // Set wager
//             userHand->SetWager(200);
//             // Test strategy
//             blackjack_strategy(userHand, dealerHand, false, false);
//             EXPECT_FALSE(userHand->GetHashTable()->Contains(userHand->GetTableMatrix()[2][3]));
//             EXPECT_FALSE(userHand->GetHashTable()->Contains(userHand->GetTableMatrix()[2][4]));
//             EXPECT_FALSE(userHand->GetHashTable()->Contains(userHand->GetTableMatrix()[3][0]));
//             EXPECT_TRUE(userHand->GetHashTable()->Contains(userHand->GetTableMatrix()[3][1]));
//             dealerHand->GetPlayerCards()->RemoveNode(-1);
//             userHand->GetHashTable()->ClearHashTable();
//         }
//         userHand->GetPlayerCards()->RemoveNode(-1);
//         userHand->AddHandTotal();
//     }
// }

// // Blackjack strategy test, duplicate ranks
// TEST_F(test_x, BlackjackStratDuplicates) {
//     // Create hands
//     std::shared_ptr<Hand> userHand(new Hand);
//     std::shared_ptr<Hand> dealerHand(new Hand);
//     std::shared_ptr<Card> testCard(new Card);
//     std::shared_ptr<node<Card>> testNode;
//     userHand->SetBankTotal(100);
//     // Add first card to dealer
//     testCard = std::make_shared<Card>(Ranks[0], Suits[0]);
//     testNode = dealerHand->GetPlayerCards()->InitNode(testCard);
//     dealerHand->SetPlayerCards(testNode);
//     // Player card total is 4 (two, two) or 6 (three, three)
//     for (int i = 1; i <= 2; i++) {
//         // Add cards to player hand
//         testCard = std::make_shared<Card>(Ranks[i], Suits[0]);
//         testNode = dealerHand->GetPlayerCards()->InitNode(testCard);
//         userHand->AddCardToHand(testNode);
//         testCard = std::make_shared<Card>(Ranks[i], Suits[0]);
//         testNode = dealerHand->GetPlayerCards()->InitNode(testCard);
//         userHand->AddCardToHand(testNode);
//         for (int j = 0; j < 13; j++) {
//             // Add card to dealer hand
//             testCard = std::make_shared<Card>(Ranks[j], Suits[0]);
//             testNode = dealerHand->GetPlayerCards()->InitNode(testCard);
//             dealerHand->SetPlayerCards(testNode);
//             userHand->SetWager(10);
//             // Can split hand
//             {
//                 // Test strategy
//                 blackjack_strategy(userHand, dealerHand, false, false);
//                 if (j == 1 || j == 2) {
//                     EXPECT_FALSE(userHand->GetHashTable()->Contains(userHand->GetTableMatrix()[2][3]));
//                     EXPECT_TRUE(userHand->GetHashTable()->Contains(userHand->GetTableMatrix()[2][4]));
//                     EXPECT_TRUE(userHand->GetHashTable()->Contains(userHand->GetTableMatrix()[3][0]));
//                     EXPECT_FALSE(userHand->GetHashTable()->Contains(userHand->GetTableMatrix()[3][1]));
//                 }
//                 else if (j >= 3 && j <= 6) {
//                     EXPECT_FALSE(userHand->GetHashTable()->Contains(userHand->GetTableMatrix()[2][3]));
//                     EXPECT_FALSE(userHand->GetHashTable()->Contains(userHand->GetTableMatrix()[2][4]));
//                     EXPECT_TRUE(userHand->GetHashTable()->Contains(userHand->GetTableMatrix()[3][0]));
//                     EXPECT_FALSE(userHand->GetHashTable()->Contains(userHand->GetTableMatrix()[3][1]));      
//                 }
//                 else {
//                     EXPECT_FALSE(userHand->GetHashTable()->Contains(userHand->GetTableMatrix()[2][3]));
//                     EXPECT_TRUE(userHand->GetHashTable()->Contains(userHand->GetTableMatrix()[2][4]));
//                     EXPECT_FALSE(userHand->GetHashTable()->Contains(userHand->GetTableMatrix()[3][0]));
//                     EXPECT_FALSE(userHand->GetHashTable()->Contains(userHand->GetTableMatrix()[3][1]));
//                 }
//                 userHand->GetHashTable()->ClearHashTable();      
//             }
//             // Can't split hand
//             {
//                 // Can't split
//                 userHand->GetHashTable()->AddToTable(userHand->GetTableMatrix()[3][4]);
//                 // Test strategy
//                 blackjack_strategy(userHand, dealerHand, false, false);
//                 EXPECT_FALSE(userHand->GetHashTable()->Contains(userHand->GetTableMatrix()[2][3]));
//                 EXPECT_TRUE(userHand->GetHashTable()->Contains(userHand->GetTableMatrix()[2][4]));
//                 EXPECT_FALSE(userHand->GetHashTable()->Contains(userHand->GetTableMatrix()[3][0]));
//                 EXPECT_FALSE(userHand->GetHashTable()->Contains(userHand->GetTableMatrix()[3][1]));
//                 // Can split
//                 userHand->GetHashTable()->RemoveElement(userHand->GetTableMatrix()[3][4]);
//                 userHand->GetHashTable()->ClearHashTable();
//             }
//             dealerHand->GetPlayerCards()->RemoveNode(-1);
//         }
//         userHand->GetPlayerCards()->RemoveNode(-1);
//         userHand->GetPlayerCards()->RemoveNode(-1);
//         userHand->AddHandTotal();
//     }
//     // Player card total is 8 (four, four)
//     {
//         // Add cards to player hand, set wager
//         testCard = std::make_shared<Card>(Ranks[3], Suits[0]);
//         testNode = dealerHand->GetPlayerCards()->InitNode(testCard);
//         userHand->AddCardToHand(testNode);
//         testCard = std::make_shared<Card>(Ranks[3], Suits[0]);
//         testNode = dealerHand->GetPlayerCards()->InitNode(testCard);
//         userHand->AddCardToHand(testNode);
//         userHand->SetWager(10);
//         for (int i = 0; i < 13; i++) {
//             // Add card to dealer hand
//             testCard = std::make_shared<Card>(Ranks[i], Suits[0]);
//             testNode = dealerHand->GetPlayerCards()->InitNode(testCard);
//             dealerHand->SetPlayerCards(testNode);
//             // Can split hand
//             {
//                 // Test strategy
//                 blackjack_strategy(userHand, dealerHand, false, false);
//                 if (i == 4 || i == 5) {
//                     EXPECT_FALSE(userHand->GetHashTable()->Contains(userHand->GetTableMatrix()[2][3]));
//                     EXPECT_TRUE(userHand->GetHashTable()->Contains(userHand->GetTableMatrix()[2][4]));
//                     EXPECT_TRUE(userHand->GetHashTable()->Contains(userHand->GetTableMatrix()[3][0]));
//                     EXPECT_FALSE(userHand->GetHashTable()->Contains(userHand->GetTableMatrix()[3][1]));
//                 }
//                 else {
//                     EXPECT_FALSE(userHand->GetHashTable()->Contains(userHand->GetTableMatrix()[2][3]));
//                     EXPECT_TRUE(userHand->GetHashTable()->Contains(userHand->GetTableMatrix()[2][4]));
//                     EXPECT_FALSE(userHand->GetHashTable()->Contains(userHand->GetTableMatrix()[3][0]));
//                     EXPECT_FALSE(userHand->GetHashTable()->Contains(userHand->GetTableMatrix()[3][1]));
//                 }
//                 userHand->GetHashTable()->ClearHashTable();
//             }
//             // Can't split hand
//             {
//                 // Can't split
//                 userHand->GetHashTable()->AddToTable(userHand->GetTableMatrix()[3][4]);
//                 // Test strategy
//                 blackjack_strategy(userHand, dealerHand, false, false);
//                 EXPECT_FALSE(userHand->GetHashTable()->Contains(userHand->GetTableMatrix()[2][3]));
//                 EXPECT_TRUE(userHand->GetHashTable()->Contains(userHand->GetTableMatrix()[2][4]));
//                 EXPECT_FALSE(userHand->GetHashTable()->Contains(userHand->GetTableMatrix()[3][0]));
//                 EXPECT_FALSE(userHand->GetHashTable()->Contains(userHand->GetTableMatrix()[3][1]));
//                 // Can split
//                 userHand->GetHashTable()->RemoveElement(userHand->GetTableMatrix()[3][4]);
//                 userHand->GetHashTable()->ClearHashTable();
//             }
//             dealerHand->GetPlayerCards()->RemoveNode(-1);
//         }
//         userHand->GetPlayerCards()->RemoveNode(-1);
//         userHand->GetPlayerCards()->RemoveNode(-1);
//         userHand->AddHandTotal();        
//     }
//     // Player card total is 10 (five, five)
//     {
//         // Add cards to player hand, set wager
//         testCard = std::make_shared<Card>(Ranks[4], Suits[0]);
//         testNode = dealerHand->GetPlayerCards()->InitNode(testCard);
//         userHand->AddCardToHand(testNode);
//         testCard = std::make_shared<Card>(Ranks[4], Suits[0]);
//         testNode = dealerHand->GetPlayerCards()->InitNode(testCard);
//         userHand->AddCardToHand(testNode);
//         for (int i = 0; i < 13; i++) {
//             // Add card to dealer hand
//             testCard = std::make_shared<Card>(Ranks[i], Suits[0]);
//             testNode = dealerHand->GetPlayerCards()->InitNode(testCard);
//             dealerHand->SetPlayerCards(testNode);
//             if (i == 0 || i >= 9) {
//                 // Set wager
//                 userHand->SetWager(10);
//                 // Test strategy
//                 blackjack_strategy(userHand, dealerHand, false, false);
//                 EXPECT_FALSE(userHand->GetHashTable()->Contains(userHand->GetTableMatrix()[2][3]));
//                 EXPECT_TRUE(userHand->GetHashTable()->Contains(userHand->GetTableMatrix()[2][4]));
//                 EXPECT_FALSE(userHand->GetHashTable()->Contains(userHand->GetTableMatrix()[3][0]));
//                 EXPECT_FALSE(userHand->GetHashTable()->Contains(userHand->GetTableMatrix()[3][1]));
//                 userHand->GetHashTable()->ClearHashTable();
//             }
//             else {
//                 // Can double down
//                 {
//                     // Set wager
//                     userHand->SetWager(10);
//                     // Test strategy
//                     blackjack_strategy(userHand, dealerHand, false, false);
//                     EXPECT_TRUE(userHand->GetHashTable()->Contains(userHand->GetTableMatrix()[2][3]));
//                     EXPECT_TRUE(userHand->GetHashTable()->Contains(userHand->GetTableMatrix()[2][4]));
//                     EXPECT_FALSE(userHand->GetHashTable()->Contains(userHand->GetTableMatrix()[3][0]));
//                     EXPECT_FALSE(userHand->GetHashTable()->Contains(userHand->GetTableMatrix()[3][1]));
//                     userHand->GetHashTable()->ClearHashTable();
//                 }
//                 // Cannot double down
//                 {
//                     // Set wager
//                     userHand->SetWager(101);
//                     // Test strategy
//                     blackjack_strategy(userHand, dealerHand, false, false);
//                     EXPECT_FALSE(userHand->GetHashTable()->Contains(userHand->GetTableMatrix()[2][3]));
//                     EXPECT_TRUE(userHand->GetHashTable()->Contains(userHand->GetTableMatrix()[2][4]));
//                     EXPECT_FALSE(userHand->GetHashTable()->Contains(userHand->GetTableMatrix()[3][0]));
//                     EXPECT_FALSE(userHand->GetHashTable()->Contains(userHand->GetTableMatrix()[3][1]));
//                     userHand->GetHashTable()->ClearHashTable();
//                 }
//             }
//             dealerHand->GetPlayerCards()->RemoveNode(-1);
//         }
//         userHand->GetPlayerCards()->RemoveNode(-1);
//         userHand->GetPlayerCards()->RemoveNode(-1);
//         userHand->AddHandTotal();
//     }
//     // Player card total is 12 (six, six || Ace, Ace) 
//     {
//         // Player has two sixes
//         {
//             // Add cards to player hand, set wager
//             testCard = std::make_shared<Card>(Ranks[5], Suits[0]);
//             testNode = dealerHand->GetPlayerCards()->InitNode(testCard);
//             userHand->AddCardToHand(testNode);
//             testCard = std::make_shared<Card>(Ranks[5], Suits[0]);
//             testNode = dealerHand->GetPlayerCards()->InitNode(testCard);
//             userHand->AddCardToHand(testNode);
//             userHand->SetWager(10);
//             for (int i = 0; i < 13; i++) {
//                 // Add card to dealer hand
//                 testCard = std::make_shared<Card>(Ranks[i], Suits[0]);
//                 testNode = dealerHand->GetPlayerCards()->InitNode(testCard);
//                 dealerHand->SetPlayerCards(testNode);
//                 // Can split
//                 {
//                     // Test strategy
//                     blackjack_strategy(userHand, dealerHand, false, false);
//                     if (i >= 1 && i <= 5) {
//                         EXPECT_FALSE(userHand->GetHashTable()->Contains(userHand->GetTableMatrix()[2][3]));
//                         EXPECT_FALSE(userHand->GetHashTable()->Contains(userHand->GetTableMatrix()[2][4]));
//                         EXPECT_TRUE(userHand->GetHashTable()->Contains(userHand->GetTableMatrix()[3][0]));
//                         EXPECT_FALSE(userHand->GetHashTable()->Contains(userHand->GetTableMatrix()[3][1]));
//                     }
//                     else if (i == 6) {
//                         EXPECT_FALSE(userHand->GetHashTable()->Contains(userHand->GetTableMatrix()[2][3]));
//                         EXPECT_TRUE(userHand->GetHashTable()->Contains(userHand->GetTableMatrix()[2][4]));
//                         EXPECT_TRUE(userHand->GetHashTable()->Contains(userHand->GetTableMatrix()[3][0]));
//                         EXPECT_FALSE(userHand->GetHashTable()->Contains(userHand->GetTableMatrix()[3][1]));
//                     }
//                     else {
//                         EXPECT_FALSE(userHand->GetHashTable()->Contains(userHand->GetTableMatrix()[2][3]));
//                         EXPECT_TRUE(userHand->GetHashTable()->Contains(userHand->GetTableMatrix()[2][4]));
//                         EXPECT_FALSE(userHand->GetHashTable()->Contains(userHand->GetTableMatrix()[3][0]));
//                         EXPECT_FALSE(userHand->GetHashTable()->Contains(userHand->GetTableMatrix()[3][1]));
//                     }
//                     userHand->GetHashTable()->ClearHashTable();
//                 }
//                 // Can't split
//                 {
//                     userHand->GetHashTable()->AddToTable(userHand->GetTableMatrix()[3][4]);
//                     // Test strategy
//                     blackjack_strategy(userHand, dealerHand, false, false);
//                     if ((i >= 1 && i <= 2) || (i == 0 || i >= 6)) {
//                         EXPECT_FALSE(userHand->GetHashTable()->Contains(userHand->GetTableMatrix()[2][3]));
//                         EXPECT_TRUE(userHand->GetHashTable()->Contains(userHand->GetTableMatrix()[2][4]));
//                         EXPECT_FALSE(userHand->GetHashTable()->Contains(userHand->GetTableMatrix()[3][0]));
//                         EXPECT_FALSE(userHand->GetHashTable()->Contains(userHand->GetTableMatrix()[3][1]));
//                     }
//                     else {
//                         EXPECT_FALSE(userHand->GetHashTable()->Contains(userHand->GetTableMatrix()[2][3]));
//                         EXPECT_FALSE(userHand->GetHashTable()->Contains(userHand->GetTableMatrix()[2][4]));
//                         EXPECT_FALSE(userHand->GetHashTable()->Contains(userHand->GetTableMatrix()[3][0]));
//                         EXPECT_TRUE(userHand->GetHashTable()->Contains(userHand->GetTableMatrix()[3][1]));
//                     }
//                     userHand->GetHashTable()->RemoveElement(userHand->GetTableMatrix()[3][4]);
//                     userHand->GetHashTable()->ClearHashTable();
//                 }
//                 dealerHand->GetPlayerCards()->RemoveNode(-1);
//             }
//             userHand->GetPlayerCards()->RemoveNode(-1);
//             userHand->GetPlayerCards()->RemoveNode(-1);
//             userHand->AddHandTotal();
//         }
//         // Player has two aces
//         {
//             // Add cards to player hand, set wager
//             testCard = std::make_shared<Card>(Ranks[0], Suits[0]);
//             testNode = dealerHand->GetPlayerCards()->InitNode(testCard);
//             userHand->AddCardToHand(testNode);
//             testCard = std::make_shared<Card>(Ranks[0], Suits[0]);
//             testNode = dealerHand->GetPlayerCards()->InitNode(testCard);
//             userHand->AddCardToHand(testNode);
//             userHand->SetWager(10);
//             for (int i = 0; i < 13; i++) {
//                 // Add card to dealer hand
//                 testCard = std::make_shared<Card>(Ranks[i], Suits[0]);
//                 testNode = dealerHand->GetPlayerCards()->InitNode(testCard);
//                 dealerHand->SetPlayerCards(testNode);
//                 // Can split
//                 {
//                     // Test strategy
//                     blackjack_strategy(userHand, dealerHand, false, false);
//                     EXPECT_FALSE(userHand->GetHashTable()->Contains(userHand->GetTableMatrix()[2][3]));
//                     EXPECT_FALSE(userHand->GetHashTable()->Contains(userHand->GetTableMatrix()[2][4]));
//                     EXPECT_TRUE(userHand->GetHashTable()->Contains(userHand->GetTableMatrix()[3][0]));
//                     EXPECT_FALSE(userHand->GetHashTable()->Contains(userHand->GetTableMatrix()[3][1]));
//                     userHand->GetHashTable()->ClearHashTable();
//                 }
//                 // Can't split
//                 {
//                     userHand->GetHashTable()->AddToTable(userHand->GetTableMatrix()[3][3]);
//                     // Test strategy
//                     blackjack_strategy(userHand, dealerHand, false, false);
//                     if ((i >= 1 && i <= 2) || (i == 0 || i >= 6)) {
//                         EXPECT_FALSE(userHand->GetHashTable()->Contains(userHand->GetTableMatrix()[2][3]));
//                         EXPECT_TRUE(userHand->GetHashTable()->Contains(userHand->GetTableMatrix()[2][4]));
//                         EXPECT_FALSE(userHand->GetHashTable()->Contains(userHand->GetTableMatrix()[3][0]));
//                         EXPECT_FALSE(userHand->GetHashTable()->Contains(userHand->GetTableMatrix()[3][1]));
//                     }
//                     else {
//                         EXPECT_FALSE(userHand->GetHashTable()->Contains(userHand->GetTableMatrix()[2][3]));
//                         EXPECT_FALSE(userHand->GetHashTable()->Contains(userHand->GetTableMatrix()[2][4]));
//                         EXPECT_FALSE(userHand->GetHashTable()->Contains(userHand->GetTableMatrix()[3][0]));
//                         EXPECT_TRUE(userHand->GetHashTable()->Contains(userHand->GetTableMatrix()[3][1]));
//                     }
//                     userHand->GetHashTable()->RemoveElement(userHand->GetTableMatrix()[3][3]);
//                     userHand->GetHashTable()->ClearHashTable();
//                 }
//                 dealerHand->GetPlayerCards()->RemoveNode(-1);
//             }
//             userHand->GetPlayerCards()->RemoveNode(-1);
//             userHand->GetPlayerCards()->RemoveNode(-1);
//             userHand->AddHandTotal();
//         }
//     }
//     // Player card total is 14 (seven, seven) 
//     {
//         // Add cards to player hand, set wager
//             testCard = std::make_shared<Card>(Ranks[6], Suits[0]);
//             testNode = dealerHand->GetPlayerCards()->InitNode(testCard);
//             userHand->AddCardToHand(testNode);
//             testCard = std::make_shared<Card>(Ranks[6], Suits[0]);
//             testNode = dealerHand->GetPlayerCards()->InitNode(testCard);
//             userHand->AddCardToHand(testNode);
//             userHand->SetWager(10);
//         for (int i = 0; i < 13; i++) {
//             // Add card to dealer hand
//             testCard = std::make_shared<Card>(Ranks[i], Suits[0]);
//             testNode = dealerHand->GetPlayerCards()->InitNode(testCard);
//             dealerHand->SetPlayerCards(testNode);
//             // Can split
//             {
//                 // Test strategy
//                 blackjack_strategy(userHand, dealerHand, false, false);
//                 if (i >= 1 && i <= 6) {
//                     EXPECT_FALSE(userHand->GetHashTable()->Contains(userHand->GetTableMatrix()[2][3]));
//                     EXPECT_FALSE(userHand->GetHashTable()->Contains(userHand->GetTableMatrix()[2][4]));
//                     EXPECT_TRUE(userHand->GetHashTable()->Contains(userHand->GetTableMatrix()[3][0]));
//                     EXPECT_FALSE(userHand->GetHashTable()->Contains(userHand->GetTableMatrix()[3][1]));
//                 }
//                 else if (i == 7) {
//                     EXPECT_FALSE(userHand->GetHashTable()->Contains(userHand->GetTableMatrix()[2][3]));
//                     EXPECT_TRUE(userHand->GetHashTable()->Contains(userHand->GetTableMatrix()[2][4]));
//                     EXPECT_TRUE(userHand->GetHashTable()->Contains(userHand->GetTableMatrix()[3][0]));
//                     EXPECT_FALSE(userHand->GetHashTable()->Contains(userHand->GetTableMatrix()[3][1]));
//                 }
//                 else {
//                     EXPECT_FALSE(userHand->GetHashTable()->Contains(userHand->GetTableMatrix()[2][3]));
//                     EXPECT_TRUE(userHand->GetHashTable()->Contains(userHand->GetTableMatrix()[2][4]));
//                     EXPECT_FALSE(userHand->GetHashTable()->Contains(userHand->GetTableMatrix()[3][0]));
//                     EXPECT_FALSE(userHand->GetHashTable()->Contains(userHand->GetTableMatrix()[3][1]));
//                 }
//                 userHand->GetHashTable()->ClearHashTable();
//             }
//             // Can't split
//             {
//                 userHand->GetHashTable()->AddToTable(userHand->GetTableMatrix()[3][4]);
//                 // Test strategy
//                 blackjack_strategy(userHand, dealerHand, false, false);
//                 if (i >= 1 && i <= 5) {
//                     EXPECT_FALSE(userHand->GetHashTable()->Contains(userHand->GetTableMatrix()[2][3]));
//                     EXPECT_FALSE(userHand->GetHashTable()->Contains(userHand->GetTableMatrix()[2][4]));
//                     EXPECT_FALSE(userHand->GetHashTable()->Contains(userHand->GetTableMatrix()[3][0]));
//                     EXPECT_TRUE(userHand->GetHashTable()->Contains(userHand->GetTableMatrix()[3][1]));
//                 }
//                 else {
//                     EXPECT_FALSE(userHand->GetHashTable()->Contains(userHand->GetTableMatrix()[2][3]));
//                     EXPECT_TRUE(userHand->GetHashTable()->Contains(userHand->GetTableMatrix()[2][4]));
//                     EXPECT_FALSE(userHand->GetHashTable()->Contains(userHand->GetTableMatrix()[3][0]));
//                     EXPECT_FALSE(userHand->GetHashTable()->Contains(userHand->GetTableMatrix()[3][1]));
//                 }
//                 userHand->GetHashTable()->RemoveElement(userHand->GetTableMatrix()[3][4]);
//                 userHand->GetHashTable()->ClearHashTable();
//             }
//             dealerHand->GetPlayerCards()->RemoveNode(-1);
//         }
//         userHand->GetPlayerCards()->RemoveNode(-1);
//         userHand->GetPlayerCards()->RemoveNode(-1);
//         userHand->AddHandTotal();
//     }
//     // Player card total is 16 (eight, eight)
//     {
//         // Add cards to player hand, set wager
//         testCard = std::make_shared<Card>(Ranks[7], Suits[0]);
//         testNode = dealerHand->GetPlayerCards()->InitNode(testCard);
//         userHand->AddCardToHand(testNode);
//         testCard = std::make_shared<Card>(Ranks[7], Suits[0]);
//         testNode = dealerHand->GetPlayerCards()->InitNode(testCard);
//         userHand->AddCardToHand(testNode);
//         userHand->SetWager(10);
//         for (int i = 0; i < 13; i++) {
//             // Add card to dealer hand
//             testCard = std::make_shared<Card>(Ranks[i], Suits[0]);
//             testNode = dealerHand->GetPlayerCards()->InitNode(testCard);
//             dealerHand->SetPlayerCards(testNode);
//             // Can split
//             {
//                 // Test strategy
//                 blackjack_strategy(userHand, dealerHand, false, false);
//                 EXPECT_FALSE(userHand->GetHashTable()->Contains(userHand->GetTableMatrix()[2][3]));
//                 EXPECT_FALSE(userHand->GetHashTable()->Contains(userHand->GetTableMatrix()[2][4]));
//                 EXPECT_TRUE(userHand->GetHashTable()->Contains(userHand->GetTableMatrix()[3][0]));
//                 EXPECT_FALSE(userHand->GetHashTable()->Contains(userHand->GetTableMatrix()[3][1]));       
//                 userHand->GetHashTable()->ClearHashTable();         
//             }
//             // Can't split
//             {
//                 userHand->GetHashTable()->AddToTable(userHand->GetTableMatrix()[3][4]);
//                 // Test strategy
//                 blackjack_strategy(userHand, dealerHand, false, false);
//                 if (i >= 1 && i <= 5) {
//                     EXPECT_FALSE(userHand->GetHashTable()->Contains(userHand->GetTableMatrix()[2][3]));
//                     EXPECT_FALSE(userHand->GetHashTable()->Contains(userHand->GetTableMatrix()[2][4]));
//                     EXPECT_FALSE(userHand->GetHashTable()->Contains(userHand->GetTableMatrix()[3][0]));
//                     EXPECT_TRUE(userHand->GetHashTable()->Contains(userHand->GetTableMatrix()[3][1]));
//                 }
//                 else {
//                     EXPECT_FALSE(userHand->GetHashTable()->Contains(userHand->GetTableMatrix()[2][3]));
//                     EXPECT_TRUE(userHand->GetHashTable()->Contains(userHand->GetTableMatrix()[2][4]));
//                     EXPECT_FALSE(userHand->GetHashTable()->Contains(userHand->GetTableMatrix()[3][0]));
//                     EXPECT_FALSE(userHand->GetHashTable()->Contains(userHand->GetTableMatrix()[3][1]));
//                 }
//                 userHand->GetHashTable()->RemoveElement(userHand->GetTableMatrix()[3][4]);
//                 userHand->GetHashTable()->ClearHashTable();
//             }
//             dealerHand->GetPlayerCards()->RemoveNode(-1);
//         }
//         userHand->GetPlayerCards()->RemoveNode(-1);
//         userHand->GetPlayerCards()->RemoveNode(-1);
//         userHand->AddHandTotal();
//     }
//     // Player card total is 18 (nine, nine)
//     {
//         // Add cards to player hand, set wager
//         testCard = std::make_shared<Card>(Ranks[8], Suits[0]);
//         testNode = dealerHand->GetPlayerCards()->InitNode(testCard);
//         userHand->AddCardToHand(testNode);
//         testCard = std::make_shared<Card>(Ranks[8], Suits[0]);
//         testNode = dealerHand->GetPlayerCards()->InitNode(testCard);
//         userHand->AddCardToHand(testNode);
//         userHand->SetWager(10);
//         for (int i = 0; i < 13; i++) {
//             // Add card to dealer hand
//             testCard = std::make_shared<Card>(Ranks[i], Suits[0]);
//             testNode = dealerHand->GetPlayerCards()->InitNode(testCard);
//             dealerHand->SetPlayerCards(testNode);
//             // Can split
//             {
//                 // Test strategy
//                 blackjack_strategy(userHand, dealerHand, false, false); 
//                 if (i == 0 || i == 6 || i >= 9) {
//                     EXPECT_FALSE(userHand->GetHashTable()->Contains(userHand->GetTableMatrix()[2][3]));
//                     EXPECT_FALSE(userHand->GetHashTable()->Contains(userHand->GetTableMatrix()[2][4]));
//                     EXPECT_FALSE(userHand->GetHashTable()->Contains(userHand->GetTableMatrix()[3][0]));
//                     EXPECT_TRUE(userHand->GetHashTable()->Contains(userHand->GetTableMatrix()[3][1]));
//                 }
//                 else {
//                     EXPECT_FALSE(userHand->GetHashTable()->Contains(userHand->GetTableMatrix()[2][3]));
//                     EXPECT_FALSE(userHand->GetHashTable()->Contains(userHand->GetTableMatrix()[2][4]));
//                     EXPECT_TRUE(userHand->GetHashTable()->Contains(userHand->GetTableMatrix()[3][0]));
//                     EXPECT_FALSE(userHand->GetHashTable()->Contains(userHand->GetTableMatrix()[3][1]));
//                 }
//                 userHand->GetHashTable()->ClearHashTable();
//             }
//             // Can't split
//             {
//                 userHand->GetHashTable()->AddToTable(userHand->GetTableMatrix()[3][4]);
//                 // Test strategy
//                 blackjack_strategy(userHand, dealerHand, false, false);
//                 EXPECT_FALSE(userHand->GetHashTable()->Contains(userHand->GetTableMatrix()[2][3]));
//                 EXPECT_FALSE(userHand->GetHashTable()->Contains(userHand->GetTableMatrix()[2][4]));
//                 EXPECT_FALSE(userHand->GetHashTable()->Contains(userHand->GetTableMatrix()[3][0]));
//                 EXPECT_TRUE(userHand->GetHashTable()->Contains(userHand->GetTableMatrix()[3][1]));                
//                 userHand->GetHashTable()->RemoveElement(userHand->GetTableMatrix()[3][4]);
//                 userHand->GetHashTable()->ClearHashTable();
//             }
//             dealerHand->GetPlayerCards()->RemoveNode(-1);
//         }
//         userHand->GetPlayerCards()->RemoveNode(-1);
//         userHand->GetPlayerCards()->RemoveNode(-1);
//         userHand->AddHandTotal();
//     }
//     // Player card total is 20 (face, face)
//     {
//         // Add cards to player hand, set wager
//         for (int i = 9; i <= 12; i++) {
//             testCard = std::make_shared<Card>(Ranks[i], Suits[0]);
//             testNode = dealerHand->GetPlayerCards()->InitNode(testCard);
//             userHand->AddCardToHand(testNode);
//             testCard = std::make_shared<Card>(Ranks[i], Suits[0]);
//             testNode = dealerHand->GetPlayerCards()->InitNode(testCard);
//             userHand->AddCardToHand(testNode);
//             userHand->SetWager(10);
//             for (int j = 0; j < 13; j++) {
//                 // Add card to dealer hand
//                 testCard = std::make_shared<Card>(Ranks[j], Suits[0]);
//                 testNode = dealerHand->GetPlayerCards()->InitNode(testCard);
//                 dealerHand->SetPlayerCards(testNode);
//                 // Can split
//                 {
//                     // Test strategy
//                     blackjack_strategy(userHand, dealerHand, false, false);
//                     EXPECT_FALSE(userHand->GetHashTable()->Contains(userHand->GetTableMatrix()[2][3]));
//                     EXPECT_FALSE(userHand->GetHashTable()->Contains(userHand->GetTableMatrix()[2][4]));
//                     EXPECT_FALSE(userHand->GetHashTable()->Contains(userHand->GetTableMatrix()[3][0]));
//                     EXPECT_TRUE(userHand->GetHashTable()->Contains(userHand->GetTableMatrix()[3][1]));
//                     userHand->GetHashTable()->ClearHashTable();
//                 }
//                 // Can't split
//                 {
//                     userHand->GetHashTable()->AddToTable(userHand->GetTableMatrix()[3][4]);
//                     // Test strategy
//                     blackjack_strategy(userHand, dealerHand, false, false);
//                     EXPECT_FALSE(userHand->GetHashTable()->Contains(userHand->GetTableMatrix()[2][3]));
//                     EXPECT_FALSE(userHand->GetHashTable()->Contains(userHand->GetTableMatrix()[2][4]));
//                     EXPECT_FALSE(userHand->GetHashTable()->Contains(userHand->GetTableMatrix()[3][0]));
//                     EXPECT_TRUE(userHand->GetHashTable()->Contains(userHand->GetTableMatrix()[3][1])); 
//                     userHand->GetHashTable()->RemoveElement(userHand->GetTableMatrix()[3][4]);    
//                     userHand->GetHashTable()->ClearHashTable();               
//                 }
//                 dealerHand->GetPlayerCards()->RemoveNode(-1);
//             }
//             userHand->GetPlayerCards()->RemoveNode(-1);
//             userHand->GetPlayerCards()->RemoveNode(-1);
//             userHand->AddHandTotal();
//         }
//     }
// }

// // Deal hand test
// TEST_F(test_x, DealHand) {
//     // Create hands and shoe
//     std::shared_ptr<Hand> testHand(new Hand);
//     std::shared_ptr<Hand> dealerHand(new Hand);
//     std::shared_ptr<Shoe> testShoe(new Shoe);
//     testHand->SetName("Borby");
//     dealerHand->SetName("Dealer");
//     testHand->SetBankTotal(100);
//     testHand->SetWager(10);
//     testShoe->SetNumOfDecks(1);
//     testShoe->CreateShoeSim();
//     // Test function
//     deal_hand_sim(testHand, dealerHand, testShoe, testHand->GetWager());
//     EXPECT_EQ(testShoe->GetCardsInShoe()->GetSize(), 48);
//     EXPECT_EQ(testHand->GetPlayerCards()->GetSize(), 2);
//     EXPECT_EQ(dealerHand->GetPlayerCards()->GetSize(), 2);
//     EXPECT_EQ(testHand->GetBankTotal(), 90);
//     EXPECT_EQ(testHand->GetWager(), 10);
// }

// // Dealer showing Ace check
// TEST_F(test_x, DealerShowingAce) {
//     std::shared_ptr<Hand> testHand(new Hand);
//     std::shared_ptr<Hand> dealerHand(new Hand);
//     std::shared_ptr<Shoe> testShoe(new Shoe);
//     std::shared_ptr<Shoe> copyShoe(new Shoe);
//     std::shared_ptr<Card> testCard(new Card);
//     std::shared_ptr<node<Card>> testNode;
//     float priorBank = 0;
//     float playerWager = 10;
//     testHand->BankDepositSim(100);
//     testHand->NameSim("Borby");
//     dealerHand->NameSim("Dealer");
//     priorBank = testHand->GetBankTotal();
//     // Both players have blackjack
//     for (int i = 9; i <= 12; i++) {
//         testCard = std::make_shared<Card>(Ranks[0], Suits[3]);
//         testNode = testShoe->GetCardsInShoe()->InitNode(testCard);
//         testShoe->GetCardsInShoe()->AppendNode(testNode);
//         testCard = std::make_shared<Card>(Ranks[0], Suits[2]);
//         testNode = testShoe->GetCardsInShoe()->InitNode(testCard);
//         testShoe->GetCardsInShoe()->AppendNode(testNode);
//         testCard = std::make_shared<Card>(Ranks[i], Suits[1]);
//         testNode = testShoe->GetCardsInShoe()->InitNode(testCard);
//         testShoe->GetCardsInShoe()->AppendNode(testNode);
//         testCard = std::make_shared<Card>(Ranks[i], Suits[0]);
//         testNode = testShoe->GetCardsInShoe()->InitNode(testCard);
//         testShoe->GetCardsInShoe()->AppendNode(testNode);
//         EXPECT_EQ(testHand->GetBankTotal(), priorBank);
//         copyShoe->CopyShoe(testShoe);
//         // Player can buy insurance
//         {
//             // Player chose to buy insurance
//             {
//                 auto result = dealer_showing_ace_sim(testHand, dealerHand, testShoe, playerWager, true);
//                 EXPECT_EQ(testHand->GetWager(), playerWager);
//                 EXPECT_EQ(testHand->GetInsuranceWager(), 0.5 * testHand->GetWager());
//                 EXPECT_EQ(testHand->GetNet(), 2 * testHand->GetInsuranceWager());
//                 EXPECT_EQ(testHand->GetBankTotal(), priorBank + testHand->GetNet());
//                 EXPECT_FALSE(std::get<3>(result));
//                 testHand->SetBankTotal(priorBank);
//                 testHand->ResetHand();
//                 dealerHand->ResetHand();
//             }
//             // Player chose to not buy insurance
//             testShoe->CopyShoe(copyShoe);
//             {
//                 auto result = dealer_showing_ace_sim(testHand, dealerHand, testShoe, playerWager, false);
//                 EXPECT_EQ(testHand->GetWager(), playerWager);
//                 EXPECT_EQ(testHand->GetInsuranceWager(), 0);
//                 EXPECT_EQ(testHand->GetNet(), 0);
//                 EXPECT_EQ(testHand->GetBankTotal(), priorBank + testHand->GetNet());
//                 EXPECT_FALSE(std::get<3>(result));
//                 testHand->SetBankTotal(priorBank);
//                 testHand->ResetHand();
//                 dealerHand->ResetHand();
//             }
//             testShoe->GetCardsInShoe()->ClearList();
//         }
//         // Player cannot buy insurance
//         {
//             // Testing with true
//             {
//                 playerWager = 70;
//                 while (playerWager <= priorBank) {
//                     testShoe->CopyShoe(copyShoe);
//                     auto result = dealer_showing_ace_sim(testHand, dealerHand, testShoe, playerWager, true);
//                     EXPECT_EQ(testHand->GetWager(), playerWager);
//                     EXPECT_EQ(testHand->GetInsuranceWager(), 0);
//                     EXPECT_EQ(testHand->GetNet(), 0);
//                     EXPECT_EQ(testHand->GetBankTotal(), priorBank + testHand->GetNet());
//                     EXPECT_FALSE(std::get<3>(result));
//                     testHand->SetBankTotal(priorBank);
//                     testHand->ResetHand();
//                     dealerHand->ResetHand();
//                     playerWager++;
//                     testShoe->GetCardsInShoe()->ClearList();
//                 }
//             }
//             // Testing with false
//             {
//                 playerWager = 70;
//                 while (playerWager <= priorBank) {
//                     testShoe->CopyShoe(copyShoe);
//                     auto result = dealer_showing_ace_sim(testHand, dealerHand, testShoe, playerWager, false);
//                     EXPECT_EQ(testHand->GetWager(), playerWager);
//                     EXPECT_EQ(testHand->GetInsuranceWager(), 0);
//                     EXPECT_EQ(testHand->GetNet(), 0);
//                     EXPECT_EQ(testHand->GetBankTotal(), priorBank + testHand->GetNet());
//                     EXPECT_FALSE(std::get<3>(result));
//                     testHand->SetBankTotal(priorBank);
//                     testHand->ResetHand();
//                     dealerHand->ResetHand();
//                     playerWager++;
//                     testShoe->GetCardsInShoe()->ClearList();
//                 }
//             }
//         }
//         playerWager = 10;
//     }
//     testShoe->GetCardsInShoe()->ClearList();
//     // Dealer has blackjack, player does not
//     for (int i = 9; i <= 12; i++) {
//         testCard = std::make_shared<Card>(Ranks[0], Suits[3]);
//         testNode = testShoe->GetCardsInShoe()->InitNode(testCard);
//         testShoe->GetCardsInShoe()->AppendNode(testNode);
//         testCard = std::make_shared<Card>(Ranks[0], Suits[2]);
//         testNode = testShoe->GetCardsInShoe()->InitNode(testCard);
//         testShoe->GetCardsInShoe()->AppendNode(testNode);
//         testCard = std::make_shared<Card>(Ranks[i], Suits[1]);
//         testNode = testShoe->GetCardsInShoe()->InitNode(testCard);
//         testShoe->GetCardsInShoe()->AppendNode(testNode);
//         testCard = std::make_shared<Card>(Ranks[8], Suits[0]);
//         testNode = testShoe->GetCardsInShoe()->InitNode(testCard);
//         testShoe->GetCardsInShoe()->AppendNode(testNode);
//         EXPECT_EQ(testHand->GetBankTotal(), priorBank);
//         copyShoe->CopyShoe(testShoe);
//         // Player can buy insurance
//         {
//             // Player chose to buy insurance
//             {
//                 auto result = dealer_showing_ace_sim(testHand, dealerHand, testShoe, playerWager, true);
//                 EXPECT_EQ(testHand->GetWager(), playerWager);
//                 EXPECT_EQ(testHand->GetInsuranceWager(), 0.5 * testHand->GetWager());
//                 EXPECT_EQ(testHand->GetNet(), 0);
//                 EXPECT_EQ(testHand->GetBankTotal(), priorBank + testHand->GetNet());
//                 EXPECT_FALSE(std::get<3>(result));
//                 testHand->SetBankTotal(priorBank);
//                 testHand->ResetHand();
//                 dealerHand->ResetHand();
//             }
//             // Player chose to not buy insurance
//             testShoe->CopyShoe(copyShoe);
//             {
//                 auto result = dealer_showing_ace_sim(testHand, dealerHand, testShoe, playerWager, false);
//                 EXPECT_EQ(testHand->GetWager(), playerWager);
//                 EXPECT_EQ(testHand->GetInsuranceWager(), 0);
//                 EXPECT_EQ(testHand->GetNet(), -testHand->GetWager());
//                 EXPECT_EQ(testHand->GetBankTotal(), priorBank + testHand->GetNet());
//                 EXPECT_FALSE(std::get<3>(result));
//                 testHand->SetBankTotal(priorBank);
//                 testHand->ResetHand();
//                 dealerHand->ResetHand();
//             }
//             testShoe->GetCardsInShoe()->ClearList();
//         }
//         // Player cannot buy insurance
//         {
//             // Testing with true
//             {
//                 playerWager = 70;
//                 while (playerWager <= priorBank) {
//                     testShoe->CopyShoe(copyShoe);
//                     auto result = dealer_showing_ace_sim(testHand, dealerHand, testShoe, playerWager, true);
//                     EXPECT_EQ(testHand->GetWager(), playerWager);
//                     EXPECT_EQ(testHand->GetInsuranceWager(), 0);
//                     EXPECT_EQ(testHand->GetNet(), -testHand->GetWager());
//                     EXPECT_EQ(testHand->GetBankTotal(), priorBank + testHand->GetNet());
//                     EXPECT_FALSE(std::get<3>(result));
//                     testHand->SetBankTotal(priorBank);
//                     testHand->ResetHand();
//                     dealerHand->ResetHand();
//                     playerWager++;
//                     testShoe->GetCardsInShoe()->ClearList();
//                 }
//             }
//             // Testing with false
//             {
//                 playerWager = 70;
//                 while (playerWager <= priorBank) {
//                     testShoe->CopyShoe(copyShoe);
//                     auto result = dealer_showing_ace_sim(testHand, dealerHand, testShoe, playerWager, false);
//                     EXPECT_EQ(testHand->GetWager(), playerWager);
//                     EXPECT_EQ(testHand->GetInsuranceWager(), 0);
//                     EXPECT_EQ(testHand->GetNet(), -testHand->GetWager());
//                     EXPECT_EQ(testHand->GetBankTotal(), priorBank + testHand->GetNet());
//                     EXPECT_FALSE(std::get<3>(result));
//                     testHand->SetBankTotal(priorBank);
//                     testHand->ResetHand();
//                     dealerHand->ResetHand();
//                     playerWager++;
//                     testShoe->GetCardsInShoe()->ClearList();
//                 }
//             }
//         }
//         playerWager = 10;
//     }
//     testShoe->GetCardsInShoe()->ClearList();
//     // Player has blackjack, dealer does not
//     for (int i = 9; i <= 12; i++) {
//         testCard = std::make_shared<Card>(Ranks[0], Suits[3]);
//         testNode = testShoe->GetCardsInShoe()->InitNode(testCard);
//         testShoe->GetCardsInShoe()->AppendNode(testNode);
//         testCard = std::make_shared<Card>(Ranks[0], Suits[2]);
//         testNode = testShoe->GetCardsInShoe()->InitNode(testCard);
//         testShoe->GetCardsInShoe()->AppendNode(testNode);
//         testCard = std::make_shared<Card>(Ranks[8], Suits[1]);
//         testNode = testShoe->GetCardsInShoe()->InitNode(testCard);
//         testShoe->GetCardsInShoe()->AppendNode(testNode);
//         testCard = std::make_shared<Card>(Ranks[i], Suits[0]);
//         testNode = testShoe->GetCardsInShoe()->InitNode(testCard);
//         testShoe->GetCardsInShoe()->AppendNode(testNode);
//         EXPECT_EQ(testHand->GetBankTotal(), priorBank);
//         copyShoe->CopyShoe(testShoe);
//         // Player can buy insurance
//         {
//             // Player chose to buy insurance
//             {
//                 auto result = dealer_showing_ace_sim(testHand, dealerHand, testShoe, playerWager, true);
//                 EXPECT_EQ(testHand->GetWager(), playerWager);
//                 EXPECT_EQ(testHand->GetInsuranceWager(), 0.5 * testHand->GetWager());
//                 EXPECT_EQ(testHand->GetNet(), testHand->GetWager());
//                 EXPECT_EQ(testHand->GetBankTotal(), priorBank + testHand->GetNet());
//                 EXPECT_FALSE(std::get<3>(result));
//                 testHand->SetBankTotal(priorBank);
//                 testHand->ResetHand();
//                 dealerHand->ResetHand();
//             }
//             // Player chose to not buy insurance
//             testShoe->CopyShoe(copyShoe);
//             {
//                 auto result = dealer_showing_ace_sim(testHand, dealerHand, testShoe, playerWager, false);
//                 EXPECT_EQ(testHand->GetWager(), playerWager);
//                 EXPECT_EQ(testHand->GetInsuranceWager(), 0);
//                 EXPECT_EQ(testHand->GetNet(), 1.5 * testHand->GetWager());
//                 EXPECT_EQ(testHand->GetBankTotal(), priorBank + testHand->GetNet());
//                 EXPECT_FALSE(std::get<3>(result));
//                 testHand->SetBankTotal(priorBank);
//                 testHand->ResetHand();
//                 dealerHand->ResetHand();
//             }
//             testShoe->GetCardsInShoe()->ClearList();
//         }
//         // Player cannot buy insurance
//         {
//             // Testing with true
//             {
//                 playerWager = 70;
//                 while (playerWager <= priorBank) {
//                     testShoe->CopyShoe(copyShoe);
//                     auto result = dealer_showing_ace_sim(testHand, dealerHand, testShoe, playerWager, true);
//                     EXPECT_EQ(testHand->GetWager(), playerWager);
//                     EXPECT_EQ(testHand->GetInsuranceWager(), 0);
//                     EXPECT_EQ(testHand->GetNet(), 1.5 * testHand->GetWager());
//                     EXPECT_EQ(testHand->GetBankTotal(), priorBank + testHand->GetNet());
//                     EXPECT_FALSE(std::get<3>(result));
//                     testHand->SetBankTotal(priorBank);
//                     testHand->ResetHand();
//                     dealerHand->ResetHand();
//                     playerWager++;
//                     testShoe->GetCardsInShoe()->ClearList();
//                 }
//             }
//             // Testing with false
//             {
//                 playerWager = 70;
//                 while (playerWager <= priorBank) {
//                     testShoe->CopyShoe(copyShoe);
//                     auto result = dealer_showing_ace_sim(testHand, dealerHand, testShoe, playerWager, false);
//                     EXPECT_EQ(testHand->GetWager(), playerWager);
//                     EXPECT_EQ(testHand->GetInsuranceWager(), 0);
//                     EXPECT_EQ(testHand->GetNet(), 1.5 * testHand->GetWager());
//                     EXPECT_EQ(testHand->GetBankTotal(), priorBank + testHand->GetNet());
//                     EXPECT_FALSE(std::get<3>(result));
//                     testHand->SetBankTotal(priorBank);
//                     testHand->ResetHand();
//                     dealerHand->ResetHand();
//                     playerWager++;
//                     testShoe->GetCardsInShoe()->ClearList();
//                 }
//             }
//         }
//         playerWager = 10;
//     }
//     testShoe->GetCardsInShoe()->ClearList();
//     // Neither player has blackjack
//     for (int i = 0; i <= 8; i++) {
//         testCard = std::make_shared<Card>(Ranks[0], Suits[3]);
//         testNode = testShoe->GetCardsInShoe()->InitNode(testCard);
//         testShoe->GetCardsInShoe()->AppendNode(testNode);
//         testCard = std::make_shared<Card>(Ranks[0], Suits[2]);
//         testNode = testShoe->GetCardsInShoe()->InitNode(testCard);
//         testShoe->GetCardsInShoe()->AppendNode(testNode);
//         testCard = std::make_shared<Card>(Ranks[i], Suits[1]);
//         testNode = testShoe->GetCardsInShoe()->InitNode(testCard);
//         testShoe->GetCardsInShoe()->AppendNode(testNode);
//         testCard = std::make_shared<Card>(Ranks[i], Suits[0]);
//         testNode = testShoe->GetCardsInShoe()->InitNode(testCard);
//         testShoe->GetCardsInShoe()->AppendNode(testNode);
//         EXPECT_EQ(testHand->GetBankTotal(), priorBank);
//         copyShoe->CopyShoe(testShoe);
//         // Player can buy insurance
//         {
//             // Player chose to buy insurance
//             {
//                 auto result = dealer_showing_ace_sim(testHand, dealerHand, testShoe, playerWager, true);
//                 EXPECT_EQ(testHand->GetWager(), playerWager);
//                 EXPECT_EQ(testHand->GetInsuranceWager(), 0.5 * testHand->GetWager());
//                 EXPECT_EQ(testHand->GetNet(), -testHand->GetInsuranceWager());
//                 EXPECT_EQ(testHand->GetBankTotal(), priorBank - testHand->GetInsuranceWager() - testHand->GetWager());
//                 EXPECT_TRUE(std::get<3>(result));
//                 testHand->SetBankTotal(priorBank);
//                 testHand->ResetHand();
//                 dealerHand->ResetHand();
//             }
//             // Player chose to not buy insurance
//             testShoe->CopyShoe(copyShoe);
//             {
//                 auto result = dealer_showing_ace_sim(testHand, dealerHand, testShoe, playerWager, false);
//                 EXPECT_EQ(testHand->GetWager(), playerWager);
//                 EXPECT_EQ(testHand->GetInsuranceWager(), 0);
//                 EXPECT_EQ(testHand->GetNet(), 0);
//                 EXPECT_EQ(testHand->GetBankTotal(), priorBank - testHand->GetInsuranceWager() - testHand->GetWager());
//                 EXPECT_TRUE(std::get<3>(result));
//                 testHand->SetBankTotal(priorBank);
//                 testHand->ResetHand();
//                 dealerHand->ResetHand();
//             }
//             testShoe->GetCardsInShoe()->ClearList();
//         }
//         // Player cannot buy insurance
//         {
//             // Testing with true
//             {
//                 playerWager = 70;
//                 while (playerWager <= priorBank) {
//                     testShoe->CopyShoe(copyShoe);
//                     auto result = dealer_showing_ace_sim(testHand, dealerHand, testShoe, playerWager, true);
//                     EXPECT_EQ(testHand->GetWager(), playerWager);
//                     EXPECT_EQ(testHand->GetInsuranceWager(), 0);
//                     EXPECT_EQ(testHand->GetNet(), 0);
//                     EXPECT_EQ(testHand->GetBankTotal(), priorBank - testHand->GetInsuranceWager() - testHand->GetWager());
//                     EXPECT_TRUE(std::get<3>(result));
//                     testHand->SetBankTotal(priorBank);
//                     testHand->ResetHand();
//                     dealerHand->ResetHand();
//                     playerWager++;
//                     testShoe->GetCardsInShoe()->ClearList();
//                 }
//             }
//             // Testing with false
//             {
//                 playerWager = 70;
//                 while (playerWager <= priorBank) {
//                     testShoe->CopyShoe(copyShoe);
//                     auto result = dealer_showing_ace_sim(testHand, dealerHand, testShoe, playerWager, false);
//                     EXPECT_EQ(testHand->GetWager(), playerWager);
//                     EXPECT_EQ(testHand->GetInsuranceWager(), 0);
//                     EXPECT_EQ(testHand->GetNet(), 0);
//                     EXPECT_EQ(testHand->GetBankTotal(), priorBank - testHand->GetInsuranceWager() - testHand->GetWager());
//                     EXPECT_TRUE(std::get<3>(result));
//                     testHand->SetBankTotal(priorBank);
//                     testHand->ResetHand();
//                     dealerHand->ResetHand();
//                     playerWager++;
//                     testShoe->GetCardsInShoe()->ClearList();
//                 }
//             }
//         }
//         playerWager = 10;
//     }
//     testShoe->GetCardsInShoe()->ClearList();
//     // Dealer is not showing an Ace, player cannot buy insurance no matter what
//     // Both players have blackjack
//     for (int i = 9; i <= 12; i++) {
//         testCard = std::make_shared<Card>(Ranks[i], Suits[3]);
//         testNode = testShoe->GetCardsInShoe()->InitNode(testCard);
//         testShoe->GetCardsInShoe()->AppendNode(testNode);
//         testCard = std::make_shared<Card>(Ranks[0], Suits[2]);
//         testNode = testShoe->GetCardsInShoe()->InitNode(testCard);
//         testShoe->GetCardsInShoe()->AppendNode(testNode);
//         testCard = std::make_shared<Card>(Ranks[0], Suits[1]);
//         testNode = testShoe->GetCardsInShoe()->InitNode(testCard);
//         testShoe->GetCardsInShoe()->AppendNode(testNode);
//         testCard = std::make_shared<Card>(Ranks[i], Suits[0]);
//         testNode = testShoe->GetCardsInShoe()->InitNode(testCard);
//         testShoe->GetCardsInShoe()->AppendNode(testNode);
//         EXPECT_EQ(testHand->GetBankTotal(), priorBank);
//         copyShoe->CopyShoe(testShoe);
//         // Player cannot buy insurance
//         {
//             // Testing with true
//             {
//                 playerWager = 10;
//                 while (playerWager <= priorBank) {
//                     testShoe->CopyShoe(copyShoe);
//                     auto result = dealer_showing_ace_sim(testHand, dealerHand, testShoe, playerWager, true);
//                     EXPECT_EQ(testHand->GetWager(), playerWager);
//                     EXPECT_EQ(testHand->GetInsuranceWager(), 0);
//                     EXPECT_EQ(testHand->GetNet(), 0);
//                     EXPECT_EQ(testHand->GetBankTotal(), priorBank + testHand->GetNet());
//                     EXPECT_FALSE(std::get<3>(result));
//                     testHand->SetBankTotal(priorBank);
//                     testHand->ResetHand();
//                     dealerHand->ResetHand();
//                     playerWager++;
//                     testShoe->GetCardsInShoe()->ClearList();
//                 }
//             }
//             // Testing with false
//             {
//                 playerWager = 10;
//                 while (playerWager <= priorBank) {
//                     testShoe->CopyShoe(copyShoe);
//                     auto result = dealer_showing_ace_sim(testHand, dealerHand, testShoe, playerWager, false);
//                     EXPECT_EQ(testHand->GetWager(), playerWager);
//                     EXPECT_EQ(testHand->GetInsuranceWager(), 0);
//                     EXPECT_EQ(testHand->GetNet(), 0);
//                     EXPECT_EQ(testHand->GetBankTotal(), priorBank + testHand->GetNet());
//                     EXPECT_FALSE(std::get<3>(result));
//                     testHand->SetBankTotal(priorBank);
//                     testHand->ResetHand();
//                     dealerHand->ResetHand();
//                     playerWager++;
//                     testShoe->GetCardsInShoe()->ClearList();
//                 }
//             }
//         }
//         playerWager = 10;
//     }
//     testShoe->GetCardsInShoe()->ClearList();
//     // Dealer has blackjack, player does not
//     for (int i = 9; i <= 12; i++) {
//         testCard = std::make_shared<Card>(Ranks[i], Suits[3]);
//         testNode = testShoe->GetCardsInShoe()->InitNode(testCard);
//         testShoe->GetCardsInShoe()->AppendNode(testNode);
//         testCard = std::make_shared<Card>(Ranks[1], Suits[2]);
//         testNode = testShoe->GetCardsInShoe()->InitNode(testCard);
//         testShoe->GetCardsInShoe()->AppendNode(testNode);
//         testCard = std::make_shared<Card>(Ranks[0], Suits[1]);
//         testNode = testShoe->GetCardsInShoe()->InitNode(testCard);
//         testShoe->GetCardsInShoe()->AppendNode(testNode);
//         testCard = std::make_shared<Card>(Ranks[i], Suits[0]);
//         testNode = testShoe->GetCardsInShoe()->InitNode(testCard);
//         testShoe->GetCardsInShoe()->AppendNode(testNode);
//         EXPECT_EQ(testHand->GetBankTotal(), priorBank);
//         copyShoe->CopyShoe(testShoe);
//         // Player cannot buy insurance
//         {
//             // Testing with true
//             {
//                 playerWager = 10;
//                 while (playerWager <= priorBank) {
//                     testShoe->CopyShoe(copyShoe);
//                     auto result = dealer_showing_ace_sim(testHand, dealerHand, testShoe, playerWager, true);
//                     EXPECT_EQ(testHand->GetWager(), playerWager);
//                     EXPECT_EQ(testHand->GetInsuranceWager(), 0);
//                     EXPECT_EQ(testHand->GetNet(), -testHand->GetWager());
//                     EXPECT_EQ(testHand->GetBankTotal(), priorBank + testHand->GetNet());
//                     EXPECT_FALSE(std::get<3>(result));
//                     testHand->SetBankTotal(priorBank);
//                     testHand->ResetHand();
//                     dealerHand->ResetHand();
//                     playerWager++;
//                     testShoe->GetCardsInShoe()->ClearList();
//                 }
//             }
//             // Testing with false
//             {
//                 playerWager = 10;
//                 while (playerWager <= priorBank) {
//                     testShoe->CopyShoe(copyShoe);
//                     auto result = dealer_showing_ace_sim(testHand, dealerHand, testShoe, playerWager, false);
//                     EXPECT_EQ(testHand->GetWager(), playerWager);
//                     EXPECT_EQ(testHand->GetInsuranceWager(), 0);
//                     EXPECT_EQ(testHand->GetNet(), -testHand->GetWager());
//                     EXPECT_EQ(testHand->GetBankTotal(), priorBank + testHand->GetNet());
//                     EXPECT_FALSE(std::get<3>(result));
//                     testHand->SetBankTotal(priorBank);
//                     testHand->ResetHand();
//                     dealerHand->ResetHand();
//                     playerWager++;
//                     testShoe->GetCardsInShoe()->ClearList();
//                 }
//             }
//         }
//         playerWager = 10;
//     }
//     testShoe->GetCardsInShoe()->ClearList();
//     // Player has blackjack, dealer does not
//     for (int i = 9; i <= 12; i++) {
//         testCard = std::make_shared<Card>(Ranks[8], Suits[3]);
//         testNode = testShoe->GetCardsInShoe()->InitNode(testCard);
//         testShoe->GetCardsInShoe()->AppendNode(testNode);
//         testCard = std::make_shared<Card>(Ranks[i], Suits[2]);
//         testNode = testShoe->GetCardsInShoe()->InitNode(testCard);
//         testShoe->GetCardsInShoe()->AppendNode(testNode);
//         testCard = std::make_shared<Card>(Ranks[0], Suits[1]);
//         testNode = testShoe->GetCardsInShoe()->InitNode(testCard);
//         testShoe->GetCardsInShoe()->AppendNode(testNode);
//         testCard = std::make_shared<Card>(Ranks[0], Suits[0]);
//         testNode = testShoe->GetCardsInShoe()->InitNode(testCard);
//         testShoe->GetCardsInShoe()->AppendNode(testNode);
//         EXPECT_EQ(testHand->GetBankTotal(), priorBank);
//         copyShoe->CopyShoe(testShoe);
//         // Player cannot buy insurance
//         {
//             // Testing with true
//             {
//                 playerWager = 10;
//                 while (playerWager <= priorBank) {
//                     testShoe->CopyShoe(copyShoe);
//                     auto result = dealer_showing_ace_sim(testHand, dealerHand, testShoe, playerWager, true);
//                     EXPECT_EQ(testHand->GetWager(), playerWager);
//                     EXPECT_EQ(testHand->GetInsuranceWager(), 0);
//                     EXPECT_EQ(testHand->GetNet(), 1.5 * testHand->GetWager());
//                     EXPECT_EQ(testHand->GetBankTotal(), priorBank + testHand->GetNet());
//                     EXPECT_FALSE(std::get<3>(result));
//                     testHand->SetBankTotal(priorBank);
//                     testHand->ResetHand();
//                     dealerHand->ResetHand();
//                     playerWager++;
//                     testShoe->GetCardsInShoe()->ClearList();
//                 }
//             }
//             // Testing with false
//             {
//                 playerWager = 10;
//                 while (playerWager <= priorBank) {
//                     testShoe->CopyShoe(copyShoe);
//                     auto result = dealer_showing_ace_sim(testHand, dealerHand, testShoe, playerWager, false);
//                     EXPECT_EQ(testHand->GetWager(), playerWager);
//                     EXPECT_EQ(testHand->GetInsuranceWager(), 0);
//                     EXPECT_EQ(testHand->GetNet(), 1.5 * testHand->GetWager());
//                     EXPECT_EQ(testHand->GetBankTotal(), priorBank + testHand->GetNet());
//                     EXPECT_FALSE(std::get<3>(result));
//                     testHand->SetBankTotal(priorBank);
//                     testHand->ResetHand();
//                     dealerHand->ResetHand();
//                     playerWager++;
//                     testShoe->GetCardsInShoe()->ClearList();
//                 }
//             }
//         }
//         playerWager = 10;
//     }
//     testShoe->GetCardsInShoe()->ClearList();
//     // Neither player has blackjack
//     for (int i = 9; i <= 12; i++) {
//         testCard = std::make_shared<Card>(Ranks[1], Suits[3]);
//         testNode = testShoe->GetCardsInShoe()->InitNode(testCard);
//         testShoe->GetCardsInShoe()->AppendNode(testNode);
//         testCard = std::make_shared<Card>(Ranks[1], Suits[2]);
//         testNode = testShoe->GetCardsInShoe()->InitNode(testCard);
//         testShoe->GetCardsInShoe()->AppendNode(testNode);
//         testCard = std::make_shared<Card>(Ranks[i], Suits[1]);
//         testNode = testShoe->GetCardsInShoe()->InitNode(testCard);
//         testShoe->GetCardsInShoe()->AppendNode(testNode);
//         testCard = std::make_shared<Card>(Ranks[i], Suits[0]);
//         testNode = testShoe->GetCardsInShoe()->InitNode(testCard);
//         testShoe->GetCardsInShoe()->AppendNode(testNode);
//         EXPECT_EQ(testHand->GetBankTotal(), priorBank);
//         copyShoe->CopyShoe(testShoe);
//         // Player cannot buy insurance
//         {
//             // Testing with true
//             {
//                 playerWager = 10;
//                 while (playerWager <= priorBank) {
//                     testShoe->CopyShoe(copyShoe);
//                     auto result = dealer_showing_ace_sim(testHand, dealerHand, testShoe, playerWager, true);
//                     EXPECT_EQ(testHand->GetWager(), playerWager);
//                     EXPECT_EQ(testHand->GetInsuranceWager(), 0);
//                     EXPECT_EQ(testHand->GetNet(), 0);
//                     EXPECT_EQ(testHand->GetBankTotal(), priorBank - testHand->GetWager());
//                     EXPECT_TRUE(std::get<3>(result));
//                     testHand->SetBankTotal(priorBank);
//                     testHand->ResetHand();
//                     dealerHand->ResetHand();
//                     playerWager++;
//                     testShoe->GetCardsInShoe()->ClearList();
//                 }
//             }
//             // Testing with false
//             {
//                 playerWager = 10;
//                 while (playerWager <= priorBank) {
//                     testShoe->CopyShoe(copyShoe);
//                     auto result = dealer_showing_ace_sim(testHand, dealerHand, testShoe, playerWager, true);
//                     EXPECT_EQ(testHand->GetWager(), playerWager);
//                     EXPECT_EQ(testHand->GetInsuranceWager(), 0);
//                     EXPECT_EQ(testHand->GetNet(), 0);
//                     EXPECT_EQ(testHand->GetBankTotal(), priorBank - testHand->GetWager());
//                     EXPECT_TRUE(std::get<3>(result));
//                     testHand->SetBankTotal(priorBank);
//                     testHand->ResetHand();
//                     dealerHand->ResetHand();
//                     playerWager++;
//                     testShoe->GetCardsInShoe()->ClearList();
//                 }
//             }
//         }
//         playerWager = 10;
//     }
//     testShoe->GetCardsInShoe()->ClearList();
// }

// // Split hand vector check
// TEST_F(test_x, SplitHandVectorCheck) {
//     std::shared_ptr<Hand> testHand1(new Hand);
//     std::shared_ptr<Hand> testHand2(new Hand);
//     std::shared_ptr<Card> testCard(new Card);
//     std::shared_ptr<node<Card>> testNode;
//     testHand1->SetName("Borby");
//     testHand1->SetBankTotal(100);
//     testHand1->SetWager(10);
//     testCard = std::make_shared<Card>(Ranks[0], Suits[0]);
//     testNode = testHand1->GetPlayerCards()->InitNode(testCard);
//     testHand1->SetPlayerCards(testNode);
//     testCard = std::make_shared<Card>(Ranks[12], Suits[1]);
//     testNode = testHand1->GetPlayerCards()->InitNode(testCard);
//     testHand1->SetPlayerCards(testNode);
//     EXPECT_EQ(testHand1->GetPlayerCards()->GetSize(), 2);
//     std::vector<std::shared_ptr<Hand>> newHands = split_hand(testHand1);
//     testHand1 = newHands.at(0);
//     testHand2 = newHands.at(1);
//     EXPECT_EQ(newHands.size(), 2);
//     EXPECT_EQ(testHand1->GetPlayerCards()->GetSize(), 1);
//     EXPECT_EQ(testHand1->GetPlayerCards()->RetrieveNode(0)->data.GetRank(), Ranks[0]);
//     EXPECT_EQ(testHand1->GetPlayerCards()->RetrieveNode(0)->data.GetSuit(), Suits[0]);
//     EXPECT_EQ(testHand2->GetPlayerCards()->GetSize(), 1);
//     EXPECT_EQ(testHand2->GetPlayerCards()->RetrieveNode(0)->data.GetRank(), Ranks[12]);
//     EXPECT_EQ(testHand2->GetPlayerCards()->RetrieveNode(0)->data.GetSuit(), Suits[1]);
// }

// // Split hand linked list check
// TEST_F(test_x, SplitHandLinkedListCheck) {
//     std::shared_ptr<Hand> testHand(new Hand);
//     std::shared_ptr<Card> testCard(new Card);
//     std::shared_ptr<node<Card>> testNode;
//     testHand->SetName("Borby");
//     testHand->SetBankTotal(100);
//     testHand->SetWager(10);
//     testCard = std::make_shared<Card>(Ranks[0], Suits[0]);
//     testNode = testHand->GetPlayerCards()->InitNode(testCard);
//     testHand->SetPlayerCards(testNode);
//     testCard = std::make_shared<Card>(Ranks[12], Suits[1]);
//     testNode = testHand->GetPlayerCards()->InitNode(testCard);
//     testHand->SetPlayerCards(testNode);
//     EXPECT_EQ(testHand->GetPlayerCards()->GetSize(), 2);
//     testHand->PlaceWagerSim(testHand->GetWager());
//     split_hand_sim(testHand);
//     EXPECT_EQ(testHand->GetPlayerHands()->GetSize(), 2);
//     EXPECT_EQ(testHand->GetHandsCurrentlyHeld(), 2);
//     EXPECT_EQ(testHand->GetPlayerHands()->RetrieveNode(0)->data->GetPlayerCards()->GetSize(), 1);
//     EXPECT_EQ(testHand->GetPlayerHands()->RetrieveNode(0)->data->GetPlayerCards()->RetrieveNode(0)->data.GetRank(), Ranks[0]);
//     EXPECT_EQ(testHand->GetPlayerHands()->RetrieveNode(0)->data->GetPlayerCards()->RetrieveNode(0)->data.GetSuit(), Suits[0]);
//     EXPECT_EQ(testHand->GetPlayerHands()->RetrieveNode(0)->data->GetPlayerCards()->RetrieveNode(0)->data.GetCardValue(), 11);
//     EXPECT_EQ(testHand->GetPlayerHands()->RetrieveNode(0)->data->GetWager(), 10);
//     EXPECT_EQ(testHand->GetPlayerHands()->RetrieveNode(0)->data->GetBankTotal(), 80);
//     EXPECT_EQ(testHand->GetPlayerHands()->RetrieveNode(-1)->data->GetPlayerCards()->GetSize(), 1);
//     EXPECT_EQ(testHand->GetPlayerHands()->RetrieveNode(-1)->data->GetPlayerCards()->RetrieveNode(0)->data.GetRank(), Ranks[12]);
//     EXPECT_EQ(testHand->GetPlayerHands()->RetrieveNode(-1)->data->GetPlayerCards()->RetrieveNode(0)->data.GetSuit(), Suits[1]);
//     EXPECT_EQ(testHand->GetPlayerHands()->RetrieveNode(-1)->data->GetPlayerCards()->RetrieveNode(0)->data.GetCardValue(), 10);
//     EXPECT_EQ(testHand->GetPlayerHands()->RetrieveNode(-1)->data->GetWager(), 10);
//     EXPECT_EQ(testHand->GetPlayerHands()->RetrieveNode(-1)->data->GetBankTotal(), 80);
//     EXPECT_EQ(testHand->GetWager(), 10);
//     EXPECT_EQ(testHand->GetBankTotal(), 80);
// }

// // Same rank check test
// TEST_F(test_x, SameRankCheck) {
//     std::shared_ptr<Hand> testHand(new Hand);
//     std::shared_ptr<Hand> dealerHand(new Hand);
//     std::shared_ptr<Shoe> testShoe(new Shoe);
//     std::shared_ptr<Shoe> copyShoe(new Shoe);
//     std::shared_ptr<Card> testCard(new Card);
//     std::shared_ptr<node<Card>> testNode;
//     float priorBank = 100;
//     float handWager = 10;
//     testHand->NameSim("Borby");
//     dealerHand->NameSim("Dealer");
//     testHand->BankDepositSim(priorBank);
//     priorBank = testHand->GetBankTotal();
//     // Check for splitting Aces
//     testCard = std::make_shared<Card>(Ranks[12], Suits[3]);
//     testNode = testShoe->GetCardsInShoe()->InitNode(testCard);
//     testShoe->GetCardsInShoe()->AppendNode(testNode);
//     testCard = std::make_shared<Card>(Ranks[12], Suits[1]);
//     testNode = testShoe->GetCardsInShoe()->InitNode(testCard);
//     testShoe->GetCardsInShoe()->AppendNode(testNode);
//     testCard = std::make_shared<Card>(Ranks[7], Suits[3]);
//     testNode = testShoe->GetCardsInShoe()->InitNode(testCard);
//     testShoe->GetCardsInShoe()->AppendNode(testNode);
//     testCard = std::make_shared<Card>(Ranks[0], Suits[2]);
//     testNode = testShoe->GetCardsInShoe()->InitNode(testCard);
//     testShoe->GetCardsInShoe()->AppendNode(testNode);
//     testCard = std::make_shared<Card>(Ranks[7], Suits[1]);
//     testNode = testShoe->GetCardsInShoe()->InitNode(testCard);
//     testShoe->GetCardsInShoe()->AppendNode(testNode);
//     testCard = std::make_shared<Card>(Ranks[0], Suits[0]);
//     testNode = testShoe->GetCardsInShoe()->InitNode(testCard);
//     testShoe->GetCardsInShoe()->AppendNode(testNode);
//     copyShoe->CopyShoe(testShoe);
//     // Player chooses to split
//     while (handWager < priorBank) {
//         deal_hand_sim(testHand, dealerHand, testShoe, handWager);
//         auto result = same_rank_check_sim(testHand, dealerHand, testShoe, true);
//         // Player is eligible to split
//         if (testHand->GetHashTable()->Contains(testHand->GetTableMatrix()[0][2])) {
//             for (int i = 0; i < std::get<0>(result)->GetPlayerHands()->GetSize(); i++) {
//                 EXPECT_EQ(std::get<0>(result)->GetPlayerHands()->GetSize(), 2);
//                 EXPECT_EQ(std::get<0>(result)->GetPlayerHands()->RetrieveNode(i)->data->GetPlayerCards()->GetSize(), 2);
//                 EXPECT_EQ(std::get<0>(result)->GetPlayerHands()->RetrieveNode(i)->data->GetWager(), testHand->GetWager());
//                 EXPECT_EQ(std::get<0>(result)->GetPlayerHands()->RetrieveNode(i)->data->GetBankTotal(), priorBank - 2 * testHand->GetWager());
//                 EXPECT_EQ(std::get<0>(result)->GetPlayerHands()->RetrieveNode(i)->data->GetCardsTotal(), 21);
//                 EXPECT_EQ(testHand->GetPlayerCards()->GetSize(), 2);
//                 EXPECT_EQ(testHand->GetCardsTotal(), 12);
//                 EXPECT_EQ(testHand->GetWager(), handWager);
//                 EXPECT_EQ(testHand->GetBankTotal(), priorBank - 2 * testHand->GetWager());
//                 EXPECT_EQ(testShoe->GetCardsInShoe()->GetSize(), 0);
//             }
//         }
//         // Player cannot split
//         else {
//             EXPECT_EQ(std::get<0>(result)->GetPlayerHands()->GetSize(), 1);
//             EXPECT_EQ(std::get<0>(result)->GetPlayerHands()->RetrieveNode(0)->data->GetPlayerCards()->GetSize(), 2);
//             EXPECT_EQ(std::get<0>(result)->GetPlayerHands()->RetrieveNode(0)->data->GetWager(), testHand->GetWager());
//             EXPECT_EQ(std::get<0>(result)->GetPlayerHands()->RetrieveNode(0)->data->GetBankTotal(), priorBank - testHand->GetWager());
//             EXPECT_EQ(std::get<0>(result)->GetPlayerHands()->RetrieveNode(0)->data->GetCardsTotal(), 12);
//             EXPECT_EQ(testHand->GetPlayerCards()->GetSize(), 2);
//             EXPECT_EQ(testHand->GetCardsTotal(), 12);
//             EXPECT_EQ(testHand->GetWager(), handWager);
//             EXPECT_EQ(testHand->GetBankTotal(), priorBank - testHand->GetWager());
//             EXPECT_EQ(testShoe->GetCardsInShoe()->GetSize(), 2);
//         }
//         testHand->SetBankTotal(priorBank);
//         testHand->ResetHand();
//         dealerHand->ResetHand();
//         testShoe->EmptyShoe();
//         testShoe->CopyShoe(copyShoe);
//         handWager++;
//     }
//     // Player chooses not to split
//     {
//         deal_hand_sim(testHand, dealerHand, testShoe, handWager);
//         auto result = same_rank_check_sim(testHand, dealerHand, testShoe, false);
//         EXPECT_EQ(std::get<0>(result)->GetPlayerHands()->GetSize(), 1);
//         EXPECT_EQ(std::get<0>(result)->GetPlayerHands()->RetrieveNode(0)->data->GetPlayerCards()->GetSize(), 2);
//         EXPECT_EQ(std::get<0>(result)->GetPlayerHands()->RetrieveNode(0)->data->GetWager(), testHand->GetWager());
//         EXPECT_EQ(std::get<0>(result)->GetPlayerHands()->RetrieveNode(0)->data->GetBankTotal(), priorBank - testHand->GetWager());
//         EXPECT_EQ(std::get<0>(result)->GetPlayerHands()->RetrieveNode(0)->data->GetCardsTotal(), 12);
//         EXPECT_EQ(testHand->GetPlayerCards()->GetSize(), 2);
//         EXPECT_EQ(testHand->GetCardsTotal(), 12);
//         EXPECT_EQ(testHand->GetWager(), handWager);
//         EXPECT_EQ(testHand->GetBankTotal(), priorBank - testHand->GetWager());
//         EXPECT_EQ(testShoe->GetCardsInShoe()->GetSize(), 2);
//     }
//     testShoe->EmptyShoe();
//     testHand->ResetHand();
//     dealerHand->ResetHand();
//     testHand->SetBankTotal(priorBank);
//     handWager = 10;
//     // Random Number Generator
//     int rankVal = random_int(1, 12);
//     int dealerFirst = random_int(1, 12);
//     int dealerSecond = random_int(1, 12);
//     // Check for splitting hand
//     testCard = std::make_shared<Card>(Ranks[rankVal], Suits[0]);
//     testNode = testShoe->GetCardsInShoe()->InitNode(testCard);
//     testShoe->GetCardsInShoe()->AppendNode(testNode);
//     testCard = std::make_shared<Card>(Ranks[rankVal], Suits[1]);
//     testNode = testShoe->GetCardsInShoe()->InitNode(testCard);
//     testShoe->GetCardsInShoe()->AppendNode(testNode);
//     testCard = std::make_shared<Card>(Ranks[rankVal], Suits[2]);
//     testNode = testShoe->GetCardsInShoe()->InitNode(testCard);
//     testShoe->GetCardsInShoe()->AppendNode(testNode);
//     testCard = std::make_shared<Card>(Ranks[rankVal], Suits[3]);
//     testNode = testShoe->GetCardsInShoe()->InitNode(testCard);
//     testShoe->GetCardsInShoe()->AppendNode(testNode);
//     testCard = std::make_shared<Card>(Ranks[dealerSecond], Suits[3]);
//     testNode = testShoe->GetCardsInShoe()->InitNode(testCard);
//     testShoe->GetCardsInShoe()->AppendNode(testNode);
//     testCard = std::make_shared<Card>(Ranks[rankVal], Suits[2]);
//     testNode = testShoe->GetCardsInShoe()->InitNode(testCard);
//     testShoe->GetCardsInShoe()->AppendNode(testNode);
//     testCard = std::make_shared<Card>(Ranks[dealerFirst], Suits[1]);
//     testNode = testShoe->GetCardsInShoe()->InitNode(testCard);
//     testShoe->GetCardsInShoe()->AppendNode(testNode);
//     testCard = std::make_shared<Card>(Ranks[rankVal], Suits[0]);
//     testNode = testShoe->GetCardsInShoe()->InitNode(testCard);
//     testShoe->GetCardsInShoe()->AppendNode(testNode);
//     copyShoe->CopyShoe(testShoe);
//     // Max hands split check
//     while (handWager < priorBank) {
//         // Player has chosen to split their hand
//         {
//             deal_hand_sim(testHand, dealerHand, testShoe, handWager);
//             EXPECT_EQ(testHand->GetPlayerHands()->GetSize(), 0);
//             EXPECT_EQ(testHand->GetHandsCurrentlyHeld(), 1);
//             EXPECT_EQ(testHand->GetPlayerCards()->GetSize(), 2);
//             EXPECT_EQ(testHand->GetWager(), handWager);
//             EXPECT_EQ(testHand->GetBankTotal(), priorBank - testHand->GetHandsCurrentlyHeld() * handWager);
//             auto result = same_rank_check_sim(testHand, dealerHand, testShoe, true);
//             EXPECT_EQ(testHand->GetHandsCurrentlyHeld(), testHand->GetPlayerHands()->GetSize());
//             // Player has split hands
//             if (testHand->GetHandsCurrentlyHeld() > 1) {
//                 if (handWager <= 0.2 * priorBank) {
//                     EXPECT_EQ(testHand->GetPlayerHands()->GetSize(), 5);
//                     EXPECT_EQ(testHand->GetHandsCurrentlyHeld(), 5);
//                     for (int i = 0; i < testHand->GetPlayerHands()->GetSize(); i++) {
//                         if (i == 0) {
//                             EXPECT_EQ(testHand->GetPlayerHands()->RetrieveNode(i)->data->GetPlayerCards()->GetSize(), 2);
//                         }
//                         else {
//                             EXPECT_EQ(testHand->GetPlayerHands()->RetrieveNode(i)->data->GetPlayerCards()->GetSize(), 1);
//                         }
//                         EXPECT_EQ(testHand->GetPlayerHands()->RetrieveNode(i)->data->GetHandsCurrentlyHeld(), 5);
//                         EXPECT_EQ(testHand->GetPlayerHands()->RetrieveNode(i)->data->GetWager(), handWager);
//                         EXPECT_EQ(testHand->GetPlayerHands()->RetrieveNode(i)->data->GetBankTotal(), priorBank - testHand->GetPlayerHands()->RetrieveNode(0)->data->GetHandsCurrentlyHeld() * handWager);
//                     }
//                     EXPECT_EQ(testHand->GetPlayerCards()->GetSize(), 2);
//                     EXPECT_EQ(testHand->GetWager(), handWager);
//                     EXPECT_EQ(testHand->GetBankTotal(), priorBank - testHand->GetHandsCurrentlyHeld() * handWager);
//                 }
//                 else if (handWager > 0.2 * priorBank && handWager <= 0.25 * priorBank) {
//                     EXPECT_EQ(testHand->GetPlayerHands()->GetSize(), 4);
//                     EXPECT_EQ(testHand->GetHandsCurrentlyHeld(), 4);
//                     for (int i = 0; i < testHand->GetPlayerHands()->GetSize(); i++) {
//                         if (i == 0) {
//                             EXPECT_EQ(testHand->GetPlayerHands()->RetrieveNode(i)->data->GetPlayerCards()->GetSize(), 2);
//                         }
//                         else {
//                             EXPECT_EQ(testHand->GetPlayerHands()->RetrieveNode(i)->data->GetPlayerCards()->GetSize(), 1);
//                         }
//                         EXPECT_EQ(testHand->GetPlayerHands()->RetrieveNode(i)->data->GetHandsCurrentlyHeld(), 4);
//                         EXPECT_EQ(testHand->GetPlayerHands()->RetrieveNode(i)->data->GetWager(), handWager);
//                         EXPECT_EQ(testHand->GetPlayerHands()->RetrieveNode(i)->data->GetBankTotal(), priorBank - testHand->GetPlayerHands()->RetrieveNode(0)->data->GetHandsCurrentlyHeld() * handWager);
//                     }
//                     EXPECT_EQ(testHand->GetPlayerCards()->GetSize(), 2);
//                     EXPECT_EQ(testHand->GetWager(), handWager);
//                     EXPECT_EQ(testHand->GetBankTotal(), priorBank - testHand->GetHandsCurrentlyHeld() * handWager);
//                 }
//                 else if (handWager > 0.25 * priorBank && handWager <= 0.33 * priorBank) {
//                     EXPECT_EQ(testHand->GetPlayerHands()->GetSize(), 3);
//                     EXPECT_EQ(testHand->GetHandsCurrentlyHeld(), 3);
//                     for (int i = 0; i < testHand->GetPlayerHands()->GetSize(); i++) {
//                         if (i == 0) {
//                             EXPECT_EQ(testHand->GetPlayerHands()->RetrieveNode(i)->data->GetPlayerCards()->GetSize(), 2);
//                         }
//                         else {
//                             EXPECT_EQ(testHand->GetPlayerHands()->RetrieveNode(i)->data->GetPlayerCards()->GetSize(), 1);
//                         }
//                         EXPECT_EQ(testHand->GetPlayerHands()->RetrieveNode(i)->data->GetHandsCurrentlyHeld(), 3);
//                         EXPECT_EQ(testHand->GetPlayerHands()->RetrieveNode(i)->data->GetWager(), handWager);
//                         EXPECT_EQ(testHand->GetPlayerHands()->RetrieveNode(i)->data->GetBankTotal(), priorBank - testHand->GetPlayerHands()->RetrieveNode(0)->data->GetHandsCurrentlyHeld() * handWager);
//                     }
//                     EXPECT_EQ(testHand->GetPlayerCards()->GetSize(), 2);
//                     EXPECT_EQ(testHand->GetWager(), handWager);
//                     EXPECT_EQ(testHand->GetBankTotal(), priorBank - testHand->GetHandsCurrentlyHeld() * handWager);
//                 }
//                 else if (handWager > 0.33 * priorBank && handWager <= 0.5 * priorBank) {
//                     EXPECT_EQ(testHand->GetPlayerHands()->GetSize(), 2);
//                     EXPECT_EQ(testHand->GetHandsCurrentlyHeld(), 2);
//                     for (int i = 0; i < testHand->GetPlayerHands()->GetSize(); i++) {
//                         if (i == 0) {
//                             EXPECT_EQ(testHand->GetPlayerHands()->RetrieveNode(i)->data->GetPlayerCards()->GetSize(), 2);
//                         }
//                         else {
//                             EXPECT_EQ(testHand->GetPlayerHands()->RetrieveNode(i)->data->GetPlayerCards()->GetSize(), 1);
//                         }
//                         EXPECT_EQ(testHand->GetPlayerHands()->RetrieveNode(i)->data->GetHandsCurrentlyHeld(), 2);
//                         EXPECT_EQ(testHand->GetPlayerHands()->RetrieveNode(i)->data->GetWager(), handWager);
//                         EXPECT_EQ(testHand->GetPlayerHands()->RetrieveNode(i)->data->GetBankTotal(), priorBank - testHand->GetPlayerHands()->RetrieveNode(0)->data->GetHandsCurrentlyHeld() * handWager);
//                     }
//                     EXPECT_EQ(testHand->GetPlayerCards()->GetSize(), 2);
//                     EXPECT_EQ(testHand->GetWager(), handWager);
//                     EXPECT_EQ(testHand->GetBankTotal(), priorBank - testHand->GetHandsCurrentlyHeld() * handWager);
//                 }
//             }
//             // Player does not have split hands
//             else {
//                 EXPECT_EQ(testHand->GetPlayerHands()->GetSize(), 1);
//                 EXPECT_EQ(testHand->GetPlayerHands()->RetrieveNode(0)->data->GetHandsCurrentlyHeld(), 1);
//                 EXPECT_EQ(testHand->GetPlayerHands()->RetrieveNode(0)->data->GetPlayerCards()->GetSize(), 2);
//                 EXPECT_EQ(testHand->GetPlayerHands()->RetrieveNode(0)->data->GetWager(), handWager);
//                 EXPECT_EQ(testHand->GetPlayerHands()->RetrieveNode(0)->data->GetBankTotal(), priorBank - testHand->GetPlayerHands()->RetrieveNode(0)->data->GetHandsCurrentlyHeld() * handWager);
//                 EXPECT_EQ(testHand->GetHandsCurrentlyHeld(), 1);
//                 EXPECT_EQ(testHand->GetPlayerCards()->GetSize(), 2);
//                 EXPECT_EQ(testHand->GetWager(), handWager);
//                 EXPECT_EQ(testHand->GetBankTotal(), priorBank - testHand->GetHandsCurrentlyHeld() * handWager);
//             }
//             testHand->SetBankTotal(priorBank);
//             testHand->ResetHand();
//             dealerHand->ResetHand();
//             testShoe->EmptyShoe();
//             testShoe->CopyShoe(copyShoe);
//         }
//         // Player has chosen to not split their hand
//         {
//             deal_hand_sim(testHand, dealerHand, testShoe, handWager);
//             EXPECT_EQ(testHand->GetPlayerHands()->GetSize(), 0);
//             EXPECT_EQ(testHand->GetHandsCurrentlyHeld(), 1);
//             EXPECT_EQ(testHand->GetPlayerCards()->GetSize(), 2);
//             EXPECT_EQ(testHand->GetWager(), handWager);
//             EXPECT_EQ(testHand->GetBankTotal(), priorBank - testHand->GetHandsCurrentlyHeld() * handWager);
//             auto result = same_rank_check_sim(testHand, dealerHand, testShoe, false);
//             for (int i = 0; i < testHand->GetPlayerHands()->GetSize(); i++) {
//                 if (i == 0) {
//                     EXPECT_EQ(testHand->GetPlayerHands()->RetrieveNode(i)->data->GetPlayerCards()->GetSize(), 2);
//                 }
//                 else {
//                     EXPECT_EQ(testHand->GetPlayerHands()->RetrieveNode(i)->data->GetPlayerCards()->GetSize(), 1);
//                 }
//                 EXPECT_EQ(testHand->GetPlayerHands()->RetrieveNode(i)->data->GetPlayerHands()->GetSize(), 1);
//                 EXPECT_EQ(testHand->GetPlayerHands()->RetrieveNode(i)->data->GetHandsCurrentlyHeld(), 1);
//                 EXPECT_EQ(testHand->GetPlayerHands()->RetrieveNode(i)->data->GetWager(), handWager);
//                 EXPECT_EQ(testHand->GetPlayerHands()->RetrieveNode(i)->data->GetBankTotal(), priorBank - testHand->GetPlayerHands()->RetrieveNode(i)->data->GetHandsCurrentlyHeld() * handWager);
//             }
//             testHand->SetBankTotal(priorBank);
//             testHand->ResetHand();
//             dealerHand->ResetHand();
//             testShoe->EmptyShoe();
//             testShoe->CopyShoe(copyShoe);
//         }
//         handWager++;
//     }
//     handWager = 10;
//     // Random Number Generator
//     rankVal = random_int(1, 12);
//     dealerFirst = random_int(1, 12);
//     dealerSecond = random_int(1, 12);
//     // Check for splitting hand
//     testCard = std::make_shared<Card>(Ranks[rankVal - 1], Suits[1]);
//     testNode = testShoe->GetCardsInShoe()->InitNode(testCard);
//     testShoe->GetCardsInShoe()->AppendNode(testNode);
//     testCard = std::make_shared<Card>(Ranks[rankVal], Suits[2]);
//     testNode = testShoe->GetCardsInShoe()->InitNode(testCard);
//     testShoe->GetCardsInShoe()->AppendNode(testNode);
//     testCard = std::make_shared<Card>(Ranks[rankVal], Suits[3]);
//     testNode = testShoe->GetCardsInShoe()->InitNode(testCard);
//     testShoe->GetCardsInShoe()->AppendNode(testNode);
//     testCard = std::make_shared<Card>(Ranks[dealerSecond], Suits[3]);
//     testNode = testShoe->GetCardsInShoe()->InitNode(testCard);
//     testShoe->GetCardsInShoe()->AppendNode(testNode);
//     testCard = std::make_shared<Card>(Ranks[rankVal], Suits[2]);
//     testNode = testShoe->GetCardsInShoe()->InitNode(testCard);
//     testShoe->GetCardsInShoe()->AppendNode(testNode);
//     testCard = std::make_shared<Card>(Ranks[dealerFirst], Suits[1]);
//     testNode = testShoe->GetCardsInShoe()->InitNode(testCard);
//     testShoe->GetCardsInShoe()->AppendNode(testNode);
//     testCard = std::make_shared<Card>(Ranks[rankVal], Suits[0]);
//     testNode = testShoe->GetCardsInShoe()->InitNode(testCard);
//     testShoe->GetCardsInShoe()->AppendNode(testNode);
//     copyShoe->CopyShoe(testShoe);
//     // Max hands split check
//     while (handWager < priorBank) {
//         // Player has chosen to split their hand
//         {
//             deal_hand_sim(testHand, dealerHand, testShoe, handWager);
//             EXPECT_EQ(testHand->GetPlayerHands()->GetSize(), 0);
//             EXPECT_EQ(testHand->GetHandsCurrentlyHeld(), 1);
//             EXPECT_EQ(testHand->GetPlayerCards()->GetSize(), 2);
//             EXPECT_EQ(testHand->GetWager(), handWager);
//             EXPECT_EQ(testHand->GetBankTotal(), priorBank - testHand->GetHandsCurrentlyHeld() * handWager);
//             auto result = same_rank_check_sim(testHand, dealerHand, testShoe, true);
//             EXPECT_EQ(testHand->GetHandsCurrentlyHeld(), testHand->GetPlayerHands()->GetSize());
//             // Player has split hands
//             if (testHand->GetHandsCurrentlyHeld() > 1) {
//                 if (handWager <= 0.25 * priorBank) {
//                     EXPECT_EQ(testHand->GetPlayerHands()->GetSize(), 4);
//                     EXPECT_EQ(testHand->GetHandsCurrentlyHeld(), 4);
//                     for (int i = 0; i < testHand->GetPlayerHands()->GetSize(); i++) {
//                         if (i == 0) {
//                             EXPECT_EQ(testHand->GetPlayerHands()->RetrieveNode(i)->data->GetPlayerCards()->GetSize(), 2);
//                         }
//                         else {
//                             EXPECT_EQ(testHand->GetPlayerHands()->RetrieveNode(i)->data->GetPlayerCards()->GetSize(), 1);
//                         }
//                         EXPECT_EQ(testHand->GetPlayerHands()->RetrieveNode(i)->data->GetHandsCurrentlyHeld(), 4);
//                         EXPECT_EQ(testHand->GetPlayerHands()->RetrieveNode(i)->data->GetWager(), handWager);
//                         EXPECT_EQ(testHand->GetPlayerHands()->RetrieveNode(i)->data->GetBankTotal(), priorBank - testHand->GetPlayerHands()->RetrieveNode(0)->data->GetHandsCurrentlyHeld() * handWager);
//                     }
//                     EXPECT_EQ(testHand->GetPlayerCards()->GetSize(), 2);
//                     EXPECT_EQ(testHand->GetWager(), handWager);
//                     EXPECT_EQ(testHand->GetBankTotal(), priorBank - testHand->GetHandsCurrentlyHeld() * handWager);
//                 }
//                 else if (handWager > 0.25 * priorBank && handWager <= 0.33 * priorBank) {
//                     EXPECT_EQ(testHand->GetPlayerHands()->GetSize(), 3);
//                     EXPECT_EQ(testHand->GetHandsCurrentlyHeld(), 3);
//                     for (int i = 0; i < testHand->GetPlayerHands()->GetSize(); i++) {
//                         if (i == 0) {
//                             EXPECT_EQ(testHand->GetPlayerHands()->RetrieveNode(i)->data->GetPlayerCards()->GetSize(), 2);
//                         }
//                         else {
//                             EXPECT_EQ(testHand->GetPlayerHands()->RetrieveNode(i)->data->GetPlayerCards()->GetSize(), 1);
//                         }
//                         EXPECT_EQ(testHand->GetPlayerHands()->RetrieveNode(i)->data->GetHandsCurrentlyHeld(), 3);
//                         EXPECT_EQ(testHand->GetPlayerHands()->RetrieveNode(i)->data->GetWager(), handWager);
//                         EXPECT_EQ(testHand->GetPlayerHands()->RetrieveNode(i)->data->GetBankTotal(), priorBank - testHand->GetPlayerHands()->RetrieveNode(0)->data->GetHandsCurrentlyHeld() * handWager);
//                     }
//                     EXPECT_EQ(testHand->GetPlayerCards()->GetSize(), 2);
//                     EXPECT_EQ(testHand->GetWager(), handWager);
//                     EXPECT_EQ(testHand->GetBankTotal(), priorBank - testHand->GetHandsCurrentlyHeld() * handWager);
//                 }
//                 else if (handWager > 0.33 * priorBank && handWager <= 0.5 * priorBank) {
//                     EXPECT_EQ(testHand->GetPlayerHands()->GetSize(), 2);
//                     EXPECT_EQ(testHand->GetHandsCurrentlyHeld(), 2);
//                     for (int i = 0; i < testHand->GetPlayerHands()->GetSize(); i++) {
//                         if (i == 0) {
//                             EXPECT_EQ(testHand->GetPlayerHands()->RetrieveNode(i)->data->GetPlayerCards()->GetSize(), 2);
//                         }
//                         else {
//                             EXPECT_EQ(testHand->GetPlayerHands()->RetrieveNode(i)->data->GetPlayerCards()->GetSize(), 1);
//                         }
//                         EXPECT_EQ(testHand->GetPlayerHands()->RetrieveNode(i)->data->GetHandsCurrentlyHeld(), 2);
//                         EXPECT_EQ(testHand->GetPlayerHands()->RetrieveNode(i)->data->GetWager(), handWager);
//                         EXPECT_EQ(testHand->GetPlayerHands()->RetrieveNode(i)->data->GetBankTotal(), priorBank - testHand->GetPlayerHands()->RetrieveNode(0)->data->GetHandsCurrentlyHeld() * handWager);
//                     }
//                     EXPECT_EQ(testHand->GetPlayerCards()->GetSize(), 2);
//                     EXPECT_EQ(testHand->GetWager(), handWager);
//                     EXPECT_EQ(testHand->GetBankTotal(), priorBank - testHand->GetHandsCurrentlyHeld() * handWager);
//                 }
//             }
//             // Player does not have split hands
//             else {
//                 EXPECT_EQ(testHand->GetPlayerHands()->GetSize(), 1);
//                 EXPECT_EQ(testHand->GetPlayerHands()->RetrieveNode(0)->data->GetHandsCurrentlyHeld(), 1);
//                 EXPECT_EQ(testHand->GetPlayerHands()->RetrieveNode(0)->data->GetPlayerCards()->GetSize(), 2);
//                 EXPECT_EQ(testHand->GetPlayerHands()->RetrieveNode(0)->data->GetWager(), handWager);
//                 EXPECT_EQ(testHand->GetPlayerHands()->RetrieveNode(0)->data->GetBankTotal(), priorBank - testHand->GetPlayerHands()->RetrieveNode(0)->data->GetHandsCurrentlyHeld() * handWager);
//                 EXPECT_EQ(testHand->GetHandsCurrentlyHeld(), 1);
//                 EXPECT_EQ(testHand->GetPlayerCards()->GetSize(), 2);
//                 EXPECT_EQ(testHand->GetWager(), handWager);
//                 EXPECT_EQ(testHand->GetBankTotal(), priorBank - testHand->GetHandsCurrentlyHeld() * handWager);
//             }
//             testHand->SetBankTotal(priorBank);
//             testHand->ResetHand();
//             dealerHand->ResetHand();
//             testShoe->EmptyShoe();
//             testShoe->CopyShoe(copyShoe);
//         }
//         // Player has chosen to not split their hand
//         {
//             deal_hand_sim(testHand, dealerHand, testShoe, handWager);
//             EXPECT_EQ(testHand->GetPlayerHands()->GetSize(), 0);
//             EXPECT_EQ(testHand->GetHandsCurrentlyHeld(), 1);
//             EXPECT_EQ(testHand->GetPlayerCards()->GetSize(), 2);
//             EXPECT_EQ(testHand->GetWager(), handWager);
//             EXPECT_EQ(testHand->GetBankTotal(), priorBank - testHand->GetHandsCurrentlyHeld() * handWager);
//             auto result = same_rank_check_sim(testHand, dealerHand, testShoe, false);
//             for (int i = 0; i < testHand->GetPlayerHands()->GetSize(); i++) {
//                 if (i == 0) {
//                     EXPECT_EQ(testHand->GetPlayerHands()->RetrieveNode(i)->data->GetPlayerCards()->GetSize(), 2);
//                 }
//                 else {
//                     EXPECT_EQ(testHand->GetPlayerHands()->RetrieveNode(i)->data->GetPlayerCards()->GetSize(), 1);
//                 }
//                 EXPECT_EQ(testHand->GetPlayerHands()->RetrieveNode(i)->data->GetPlayerHands()->GetSize(), 1);
//                 EXPECT_EQ(testHand->GetPlayerHands()->RetrieveNode(i)->data->GetHandsCurrentlyHeld(), 1);
//                 EXPECT_EQ(testHand->GetPlayerHands()->RetrieveNode(i)->data->GetWager(), handWager);
//                 EXPECT_EQ(testHand->GetPlayerHands()->RetrieveNode(i)->data->GetBankTotal(), priorBank - testHand->GetPlayerHands()->RetrieveNode(i)->data->GetHandsCurrentlyHeld() * handWager);
//             }
//             testHand->SetBankTotal(priorBank);
//             testHand->ResetHand();
//             dealerHand->ResetHand();
//             testShoe->EmptyShoe();
//             testShoe->CopyShoe(copyShoe);
//         }
//         handWager++;
//     }
//     handWager = 10;
//     // Random Number Generator
//     rankVal = random_int(1, 12);
//     dealerFirst = random_int(1, 12);
//     dealerSecond = random_int(1, 12);
//     // Check for splitting hand
//     testCard = std::make_shared<Card>(Ranks[rankVal - 1], Suits[2]);
//     testNode = testShoe->GetCardsInShoe()->InitNode(testCard);
//     testShoe->GetCardsInShoe()->AppendNode(testNode);
//     testCard = std::make_shared<Card>(Ranks[rankVal], Suits[3]);
//     testNode = testShoe->GetCardsInShoe()->InitNode(testCard);
//     testShoe->GetCardsInShoe()->AppendNode(testNode);
//     testCard = std::make_shared<Card>(Ranks[dealerSecond], Suits[3]);
//     testNode = testShoe->GetCardsInShoe()->InitNode(testCard);
//     testShoe->GetCardsInShoe()->AppendNode(testNode);
//     testCard = std::make_shared<Card>(Ranks[rankVal], Suits[2]);
//     testNode = testShoe->GetCardsInShoe()->InitNode(testCard);
//     testShoe->GetCardsInShoe()->AppendNode(testNode);
//     testCard = std::make_shared<Card>(Ranks[dealerFirst], Suits[1]);
//     testNode = testShoe->GetCardsInShoe()->InitNode(testCard);
//     testShoe->GetCardsInShoe()->AppendNode(testNode);
//     testCard = std::make_shared<Card>(Ranks[rankVal], Suits[0]);
//     testNode = testShoe->GetCardsInShoe()->InitNode(testCard);
//     testShoe->GetCardsInShoe()->AppendNode(testNode);
//     copyShoe->CopyShoe(testShoe);
//     // Max hands split check
//     while (handWager < priorBank) {
//         // Player has chosen to split their hand
//         {
//             deal_hand_sim(testHand, dealerHand, testShoe, handWager);
//             EXPECT_EQ(testHand->GetPlayerHands()->GetSize(), 0);
//             EXPECT_EQ(testHand->GetHandsCurrentlyHeld(), 1);
//             EXPECT_EQ(testHand->GetPlayerCards()->GetSize(), 2);
//             EXPECT_EQ(testHand->GetWager(), handWager);
//             EXPECT_EQ(testHand->GetBankTotal(), priorBank - testHand->GetHandsCurrentlyHeld() * handWager);
//             auto result = same_rank_check_sim(testHand, dealerHand, testShoe, true);
//             EXPECT_EQ(testHand->GetHandsCurrentlyHeld(), testHand->GetPlayerHands()->GetSize());
//             // Player has split hands
//             if (testHand->GetHandsCurrentlyHeld() > 1) {
//                 if (handWager <= 0.33 * priorBank) {
//                     EXPECT_EQ(testHand->GetPlayerHands()->GetSize(), 3);
//                     EXPECT_EQ(testHand->GetHandsCurrentlyHeld(), 3);
//                     for (int i = 0; i < testHand->GetPlayerHands()->GetSize(); i++) {
//                         if (i == 0) {
//                             EXPECT_EQ(testHand->GetPlayerHands()->RetrieveNode(i)->data->GetPlayerCards()->GetSize(), 2);
//                         }
//                         else {
//                             EXPECT_EQ(testHand->GetPlayerHands()->RetrieveNode(i)->data->GetPlayerCards()->GetSize(), 1);
//                         }
//                         EXPECT_EQ(testHand->GetPlayerHands()->RetrieveNode(i)->data->GetHandsCurrentlyHeld(), 3);
//                         EXPECT_EQ(testHand->GetPlayerHands()->RetrieveNode(i)->data->GetWager(), handWager);
//                         EXPECT_EQ(testHand->GetPlayerHands()->RetrieveNode(i)->data->GetBankTotal(), priorBank - testHand->GetPlayerHands()->RetrieveNode(0)->data->GetHandsCurrentlyHeld() * handWager);
//                     }
//                     EXPECT_EQ(testHand->GetPlayerCards()->GetSize(), 2);
//                     EXPECT_EQ(testHand->GetWager(), handWager);
//                     EXPECT_EQ(testHand->GetBankTotal(), priorBank - testHand->GetHandsCurrentlyHeld() * handWager);
//                 }
//                 else if (handWager > 0.33 * priorBank && handWager <= 0.5 * priorBank) {
//                     EXPECT_EQ(testHand->GetPlayerHands()->GetSize(), 2);
//                     EXPECT_EQ(testHand->GetHandsCurrentlyHeld(), 2);
//                     for (int i = 0; i < testHand->GetPlayerHands()->GetSize(); i++) {
//                         if (i == 0) {
//                             EXPECT_EQ(testHand->GetPlayerHands()->RetrieveNode(i)->data->GetPlayerCards()->GetSize(), 2);
//                         }
//                         else {
//                             EXPECT_EQ(testHand->GetPlayerHands()->RetrieveNode(i)->data->GetPlayerCards()->GetSize(), 1);
//                         }
//                         EXPECT_EQ(testHand->GetPlayerHands()->RetrieveNode(i)->data->GetHandsCurrentlyHeld(), 2);
//                         EXPECT_EQ(testHand->GetPlayerHands()->RetrieveNode(i)->data->GetWager(), handWager);
//                         EXPECT_EQ(testHand->GetPlayerHands()->RetrieveNode(i)->data->GetBankTotal(), priorBank - testHand->GetPlayerHands()->RetrieveNode(0)->data->GetHandsCurrentlyHeld() * handWager);
//                     }
//                     EXPECT_EQ(testHand->GetPlayerCards()->GetSize(), 2);
//                     EXPECT_EQ(testHand->GetWager(), handWager);
//                     EXPECT_EQ(testHand->GetBankTotal(), priorBank - testHand->GetHandsCurrentlyHeld() * handWager);
//                 }
//             }
//             // Player does not have split hands
//             else {
//                 EXPECT_EQ(testHand->GetPlayerHands()->GetSize(), 1);
//                 EXPECT_EQ(testHand->GetPlayerHands()->RetrieveNode(0)->data->GetHandsCurrentlyHeld(), 1);
//                 EXPECT_EQ(testHand->GetPlayerHands()->RetrieveNode(0)->data->GetPlayerCards()->GetSize(), 2);
//                 EXPECT_EQ(testHand->GetPlayerHands()->RetrieveNode(0)->data->GetWager(), handWager);
//                 EXPECT_EQ(testHand->GetPlayerHands()->RetrieveNode(0)->data->GetBankTotal(), priorBank - testHand->GetPlayerHands()->RetrieveNode(0)->data->GetHandsCurrentlyHeld() * handWager);
//                 EXPECT_EQ(testHand->GetHandsCurrentlyHeld(), 1);
//                 EXPECT_EQ(testHand->GetPlayerCards()->GetSize(), 2);
//                 EXPECT_EQ(testHand->GetWager(), handWager);
//                 EXPECT_EQ(testHand->GetBankTotal(), priorBank - testHand->GetHandsCurrentlyHeld() * handWager);
//             }
//             testHand->SetBankTotal(priorBank);
//             testHand->ResetHand();
//             dealerHand->ResetHand();
//             testShoe->EmptyShoe();
//             testShoe->CopyShoe(copyShoe);
//         }
//         // Player has chosen to not split their hand
//         {
//             deal_hand_sim(testHand, dealerHand, testShoe, handWager);
//             EXPECT_EQ(testHand->GetPlayerHands()->GetSize(), 0);
//             EXPECT_EQ(testHand->GetHandsCurrentlyHeld(), 1);
//             EXPECT_EQ(testHand->GetPlayerCards()->GetSize(), 2);
//             EXPECT_EQ(testHand->GetWager(), handWager);
//             EXPECT_EQ(testHand->GetBankTotal(), priorBank - testHand->GetHandsCurrentlyHeld() * handWager);
//             auto result = same_rank_check_sim(testHand, dealerHand, testShoe, false);
//             for (int i = 0; i < testHand->GetPlayerHands()->GetSize(); i++) {
//                 if (i == 0) {
//                     EXPECT_EQ(testHand->GetPlayerHands()->RetrieveNode(i)->data->GetPlayerCards()->GetSize(), 2);
//                 }
//                 else {
//                     EXPECT_EQ(testHand->GetPlayerHands()->RetrieveNode(i)->data->GetPlayerCards()->GetSize(), 1);
//                 }
//                 EXPECT_EQ(testHand->GetPlayerHands()->RetrieveNode(i)->data->GetPlayerHands()->GetSize(), 1);
//                 EXPECT_EQ(testHand->GetPlayerHands()->RetrieveNode(i)->data->GetHandsCurrentlyHeld(), 1);
//                 EXPECT_EQ(testHand->GetPlayerHands()->RetrieveNode(i)->data->GetWager(), handWager);
//                 EXPECT_EQ(testHand->GetPlayerHands()->RetrieveNode(i)->data->GetBankTotal(), priorBank - testHand->GetPlayerHands()->RetrieveNode(i)->data->GetHandsCurrentlyHeld() * handWager);
//             }
//             testHand->SetBankTotal(priorBank);
//             testHand->ResetHand();
//             dealerHand->ResetHand();
//             testShoe->EmptyShoe();
//             testShoe->CopyShoe(copyShoe);
//         }
//         handWager++;
//     }
//     handWager = 10;
//     // Random Number Generator
//     rankVal = random_int(1, 12);
//     dealerFirst = random_int(1, 12);
//     dealerSecond = random_int(1, 12);
//     // Check for splitting hand
//     testCard = std::make_shared<Card>(Ranks[rankVal - 1], Suits[2]);
//     testNode = testShoe->GetCardsInShoe()->InitNode(testCard);
//     testShoe->GetCardsInShoe()->AppendNode(testNode);
//     testCard = std::make_shared<Card>(Ranks[dealerSecond], Suits[3]);
//     testNode = testShoe->GetCardsInShoe()->InitNode(testCard);
//     testShoe->GetCardsInShoe()->AppendNode(testNode);
//     testCard = std::make_shared<Card>(Ranks[rankVal], Suits[2]);
//     testNode = testShoe->GetCardsInShoe()->InitNode(testCard);
//     testShoe->GetCardsInShoe()->AppendNode(testNode);
//     testCard = std::make_shared<Card>(Ranks[dealerFirst], Suits[1]);
//     testNode = testShoe->GetCardsInShoe()->InitNode(testCard);
//     testShoe->GetCardsInShoe()->AppendNode(testNode);
//     testCard = std::make_shared<Card>(Ranks[rankVal], Suits[0]);
//     testNode = testShoe->GetCardsInShoe()->InitNode(testCard);
//     testShoe->GetCardsInShoe()->AppendNode(testNode);
//     copyShoe->CopyShoe(testShoe);
//     // Max hands split check
//     while (handWager < priorBank) {
//         // Player has chosen to split their hand
//         {
//             deal_hand_sim(testHand, dealerHand, testShoe, handWager);
//             EXPECT_EQ(testHand->GetPlayerHands()->GetSize(), 0);
//             EXPECT_EQ(testHand->GetHandsCurrentlyHeld(), 1);
//             EXPECT_EQ(testHand->GetPlayerCards()->GetSize(), 2);
//             EXPECT_EQ(testHand->GetWager(), handWager);
//             EXPECT_EQ(testHand->GetBankTotal(), priorBank - testHand->GetHandsCurrentlyHeld() * handWager);
//             auto result = same_rank_check_sim(testHand, dealerHand, testShoe, true);
//             EXPECT_EQ(testHand->GetHandsCurrentlyHeld(), testHand->GetPlayerHands()->GetSize());
//             // Player has split hands
//             if (testHand->GetHandsCurrentlyHeld() > 1) {
//                 if (handWager <= 0.5 * priorBank) {
//                     EXPECT_EQ(testHand->GetPlayerHands()->GetSize(), 2);
//                     EXPECT_EQ(testHand->GetHandsCurrentlyHeld(), 2);
//                     for (int i = 0; i < testHand->GetPlayerHands()->GetSize(); i++) {
//                         if (i == 0) {
//                             EXPECT_EQ(testHand->GetPlayerHands()->RetrieveNode(i)->data->GetPlayerCards()->GetSize(), 2);
//                         }
//                         else {
//                             EXPECT_EQ(testHand->GetPlayerHands()->RetrieveNode(i)->data->GetPlayerCards()->GetSize(), 1);
//                         }
//                         EXPECT_EQ(testHand->GetPlayerHands()->RetrieveNode(i)->data->GetHandsCurrentlyHeld(), 2);
//                         EXPECT_EQ(testHand->GetPlayerHands()->RetrieveNode(i)->data->GetWager(), handWager);
//                         EXPECT_EQ(testHand->GetPlayerHands()->RetrieveNode(i)->data->GetBankTotal(), priorBank - testHand->GetPlayerHands()->RetrieveNode(0)->data->GetHandsCurrentlyHeld() * handWager);
//                     }
//                     EXPECT_EQ(testHand->GetPlayerCards()->GetSize(), 2);
//                     EXPECT_EQ(testHand->GetWager(), handWager);
//                     EXPECT_EQ(testHand->GetBankTotal(), priorBank - testHand->GetHandsCurrentlyHeld() * handWager);
//                 }
//             }
//             // Player does not have split hands
//             else {
//                 EXPECT_EQ(testHand->GetPlayerHands()->GetSize(), 1);
//                 EXPECT_EQ(testHand->GetPlayerHands()->RetrieveNode(0)->data->GetHandsCurrentlyHeld(), 1);
//                 EXPECT_EQ(testHand->GetPlayerHands()->RetrieveNode(0)->data->GetPlayerCards()->GetSize(), 2);
//                 EXPECT_EQ(testHand->GetPlayerHands()->RetrieveNode(0)->data->GetWager(), handWager);
//                 EXPECT_EQ(testHand->GetPlayerHands()->RetrieveNode(0)->data->GetBankTotal(), priorBank - testHand->GetPlayerHands()->RetrieveNode(0)->data->GetHandsCurrentlyHeld() * handWager);
//                 EXPECT_EQ(testHand->GetHandsCurrentlyHeld(), 1);
//                 EXPECT_EQ(testHand->GetPlayerCards()->GetSize(), 2);
//                 EXPECT_EQ(testHand->GetWager(), handWager);
//                 EXPECT_EQ(testHand->GetBankTotal(), priorBank - testHand->GetHandsCurrentlyHeld() * handWager);
//             }
//             testHand->SetBankTotal(priorBank);
//             testHand->ResetHand();
//             dealerHand->ResetHand();
//             testShoe->EmptyShoe();
//             testShoe->CopyShoe(copyShoe);
//         }
//         // Player has chosen to not split their hand
//         {
//             deal_hand_sim(testHand, dealerHand, testShoe, handWager);
//             EXPECT_EQ(testHand->GetPlayerHands()->GetSize(), 0);
//             EXPECT_EQ(testHand->GetHandsCurrentlyHeld(), 1);
//             EXPECT_EQ(testHand->GetPlayerCards()->GetSize(), 2);
//             EXPECT_EQ(testHand->GetWager(), handWager);
//             EXPECT_EQ(testHand->GetBankTotal(), priorBank - testHand->GetHandsCurrentlyHeld() * handWager);
//             auto result = same_rank_check_sim(testHand, dealerHand, testShoe, false);
//             for (int i = 0; i < testHand->GetPlayerHands()->GetSize(); i++) {
//                 if (i == 0) {
//                     EXPECT_EQ(testHand->GetPlayerHands()->RetrieveNode(i)->data->GetPlayerCards()->GetSize(), 2);
//                 }
//                 else {
//                     EXPECT_EQ(testHand->GetPlayerHands()->RetrieveNode(i)->data->GetPlayerCards()->GetSize(), 1);
//                 }
//                 EXPECT_EQ(testHand->GetPlayerHands()->RetrieveNode(i)->data->GetPlayerHands()->GetSize(), 1);
//                 EXPECT_EQ(testHand->GetPlayerHands()->RetrieveNode(i)->data->GetHandsCurrentlyHeld(), 1);
//                 EXPECT_EQ(testHand->GetPlayerHands()->RetrieveNode(i)->data->GetWager(), handWager);
//                 EXPECT_EQ(testHand->GetPlayerHands()->RetrieveNode(i)->data->GetBankTotal(), priorBank - testHand->GetPlayerHands()->RetrieveNode(i)->data->GetHandsCurrentlyHeld() * handWager);
//             }
//             testHand->SetBankTotal(priorBank);
//             testHand->ResetHand();
//             dealerHand->ResetHand();
//             testShoe->EmptyShoe();
//             testShoe->CopyShoe(copyShoe);
//         }
//         handWager++;
//     }
//     handWager = 10;
//     // Random Number Generator
//     rankVal = random_int(1, 12);
//     dealerFirst = random_int(1, 12);
//     dealerSecond = random_int(1, 12);
//     // Check for splitting hand
//     testCard = std::make_shared<Card>(Ranks[dealerSecond], Suits[3]);
//     testNode = testShoe->GetCardsInShoe()->InitNode(testCard);
//     testShoe->GetCardsInShoe()->AppendNode(testNode);
//     testCard = std::make_shared<Card>(Ranks[rankVal - 1], Suits[2]);
//     testNode = testShoe->GetCardsInShoe()->InitNode(testCard);
//     testShoe->GetCardsInShoe()->AppendNode(testNode);
//     testCard = std::make_shared<Card>(Ranks[dealerFirst], Suits[1]);
//     testNode = testShoe->GetCardsInShoe()->InitNode(testCard);
//     testShoe->GetCardsInShoe()->AppendNode(testNode);
//     testCard = std::make_shared<Card>(Ranks[rankVal], Suits[0]);
//     testNode = testShoe->GetCardsInShoe()->InitNode(testCard);
//     testShoe->GetCardsInShoe()->AppendNode(testNode);
//     copyShoe->CopyShoe(testShoe);
//     // Max hands split check
//     while (handWager < priorBank) {
//         // Player has chosen to split their hand
//         {
//             deal_hand_sim(testHand, dealerHand, testShoe, handWager);
//             EXPECT_EQ(testHand->GetPlayerHands()->GetSize(), 0);
//             EXPECT_EQ(testHand->GetHandsCurrentlyHeld(), 1);
//             EXPECT_EQ(testHand->GetPlayerCards()->GetSize(), 2);
//             EXPECT_EQ(testHand->GetWager(), handWager);
//             EXPECT_EQ(testHand->GetBankTotal(), priorBank - testHand->GetHandsCurrentlyHeld() * handWager);
//             auto result = same_rank_check_sim(testHand, dealerHand, testShoe, true);
//             EXPECT_EQ(testHand->GetHandsCurrentlyHeld(), testHand->GetPlayerHands()->GetSize());
//             EXPECT_EQ(testHand->GetPlayerHands()->GetSize(), 1);
//             EXPECT_EQ(testHand->GetPlayerHands()->RetrieveNode(0)->data->GetHandsCurrentlyHeld(), 1);
//             EXPECT_EQ(testHand->GetPlayerHands()->RetrieveNode(0)->data->GetPlayerCards()->GetSize(), 2);
//             EXPECT_EQ(testHand->GetPlayerHands()->RetrieveNode(0)->data->GetWager(), handWager);
//             EXPECT_EQ(testHand->GetPlayerHands()->RetrieveNode(0)->data->GetBankTotal(), priorBank - testHand->GetPlayerHands()->RetrieveNode(0)->data->GetHandsCurrentlyHeld() * handWager);
//             EXPECT_EQ(testHand->GetHandsCurrentlyHeld(), 1);
//             EXPECT_EQ(testHand->GetPlayerCards()->GetSize(), 2);
//             EXPECT_EQ(testHand->GetWager(), handWager);
//             EXPECT_EQ(testHand->GetBankTotal(), priorBank - testHand->GetHandsCurrentlyHeld() * handWager);
//             testHand->SetBankTotal(priorBank);
//             testHand->ResetHand();
//             dealerHand->ResetHand();
//             testShoe->EmptyShoe();
//             testShoe->CopyShoe(copyShoe);
//         }
//         // Player has chosen to not split their hand
//         {
//             deal_hand_sim(testHand, dealerHand, testShoe, handWager);
//             EXPECT_EQ(testHand->GetPlayerHands()->GetSize(), 0);
//             EXPECT_EQ(testHand->GetHandsCurrentlyHeld(), 1);
//             EXPECT_EQ(testHand->GetPlayerCards()->GetSize(), 2);
//             EXPECT_EQ(testHand->GetWager(), handWager);
//             EXPECT_EQ(testHand->GetBankTotal(), priorBank - testHand->GetHandsCurrentlyHeld() * handWager);
//             auto result = same_rank_check_sim(testHand, dealerHand, testShoe, false);
//             for (int i = 0; i < testHand->GetPlayerHands()->GetSize(); i++) {
//                 if (i == 0) {
//                     EXPECT_EQ(testHand->GetPlayerHands()->RetrieveNode(i)->data->GetPlayerCards()->GetSize(), 2);
//                 }
//                 else {
//                     EXPECT_EQ(testHand->GetPlayerHands()->RetrieveNode(i)->data->GetPlayerCards()->GetSize(), 1);
//                 }
//                 EXPECT_EQ(testHand->GetPlayerHands()->RetrieveNode(i)->data->GetPlayerHands()->GetSize(), 1);
//                 EXPECT_EQ(testHand->GetPlayerHands()->RetrieveNode(i)->data->GetHandsCurrentlyHeld(), 1);
//                 EXPECT_EQ(testHand->GetPlayerHands()->RetrieveNode(i)->data->GetWager(), handWager);
//                 EXPECT_EQ(testHand->GetPlayerHands()->RetrieveNode(i)->data->GetBankTotal(), priorBank - testHand->GetPlayerHands()->RetrieveNode(i)->data->GetHandsCurrentlyHeld() * handWager);
//             }
//             testHand->SetBankTotal(priorBank);
//             testHand->ResetHand();
//             dealerHand->ResetHand();
//             testShoe->EmptyShoe();
//             testShoe->CopyShoe(copyShoe);
//         }
//         handWager++;
//     }
// }

// // Player Logic check test
// TEST_F(test_x, PlayerLogic) {
//     for (int i = 0; i < random_int(100, 1000); i++) {
//         std::shared_ptr<Hand> testHand(new Hand);
//         std::shared_ptr<Hand> dealerHand(new Hand);
//         std::shared_ptr<Shoe> testShoe(new Shoe);
//         std::shared_ptr<Card> testCard(new Card);
//         std::shared_ptr<node<Card>> testNode;
//         float priorBank = 100;
//         float handWager = 10;
//         testHand->NameSim("Borby");
//         dealerHand->NameSim("Dealer");
//         testHand->BankDepositSim(priorBank);
//         priorBank = testHand->GetBankTotal();
//         testShoe->SetNumOfDecks(1);
//         testShoe->CreateShoeSim();
//         while (testShoe->GetCardsInShoe()->GetSize() >= 13) {
//             auto dsa_result = dealer_showing_ace_sim(testHand, dealerHand, testShoe, handWager, false);
//             // Neither player has blackjack
//             if (std::get<3>(dsa_result)) {
//                 auto pls_result = player_logic_sim(testHand, dealerHand, testShoe, true);
//                 for (int i = 0; i < testHand->GetPlayerHands()->GetSize(); i++) {
//                     // Player doubled down
//                     if (testHand->GetPlayerHands()->RetrieveNode(i)->data->GetHashTable()->Contains(testHand->GetTableMatrix()[2][3])) {
//                         EXPECT_TRUE(testHand->GetPlayerHands()->RetrieveNode(i)->data->GetHashTable()->Contains(testHand->GetTableMatrix()[1][0]));
//                         EXPECT_TRUE(testHand->GetPlayerHands()->RetrieveNode(i)->data->GetHashTable()->Contains(testHand->GetTableMatrix()[1][3]));
//                         EXPECT_EQ(testHand->GetBankTotal(), testHand->GetPlayerHands()->RetrieveNode(i)->data->GetBankTotal());
//                         EXPECT_EQ(testHand->GetPlayerHands()->RetrieveNode(i)->data->GetPlayerCards()->GetSize(), 3);
//                         EXPECT_EQ(dealerHand->GetPlayerCards()->GetSize(), 2);
//                     }
//                     // Player hit hand
//                     else if (testHand->GetPlayerHands()->RetrieveNode(i)->data->GetHashTable()->Contains(testHand->GetTableMatrix()[2][4])) {
//                         EXPECT_FALSE(testHand->GetPlayerHands()->RetrieveNode(i)->data->GetHashTable()->Contains(testHand->GetTableMatrix()[1][0]));
//                         EXPECT_TRUE(testHand->GetPlayerHands()->RetrieveNode(i)->data->GetHashTable()->Contains(testHand->GetTableMatrix()[2][0]));
//                         EXPECT_EQ(testHand->GetBankTotal(), testHand->GetPlayerHands()->RetrieveNode(i)->data->GetBankTotal());
//                         EXPECT_NE(testHand->GetPlayerHands()->RetrieveNode(i)->data->GetPlayerCards()->GetSize(), 2);
//                         EXPECT_EQ(dealerHand->GetPlayerCards()->GetSize(), 2);
//                     }
//                     // Player stood
//                     else {
//                         EXPECT_FALSE(testHand->GetPlayerHands()->RetrieveNode(i)->data->GetHashTable()->Contains(testHand->GetTableMatrix()[1][0]));
//                         EXPECT_FALSE(testHand->GetPlayerHands()->RetrieveNode(i)->data->GetHashTable()->Contains(testHand->GetTableMatrix()[2][0]));
//                         EXPECT_EQ(testHand->GetBankTotal(), testHand->GetPlayerHands()->RetrieveNode(i)->data->GetBankTotal());
//                         EXPECT_TRUE(testHand->GetPlayerHands()->RetrieveNode(i)->data->GetPlayerCards()->GetSize() >= 2);
//                         EXPECT_EQ(dealerHand->GetPlayerCards()->GetSize(), 2);
//                     }
//                 }
//             }
//             // Someone has blackjack
//             else {
//                 EXPECT_FALSE(testHand->GetPlayerHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testHand->GetTableMatrix()[1][0]));
//                 EXPECT_FALSE(testHand->GetPlayerHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testHand->GetTableMatrix()[2][0]));
//                 if (testHand->GetCardsTotal() == 21) {
//                     EXPECT_TRUE(testHand->GetPlayerHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testHand->GetTableMatrix()[1][4]));
//                 }
//                 else {
//                     EXPECT_FALSE(testHand->GetPlayerHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testHand->GetTableMatrix()[1][4]));
//                 }
//                 if (dealerHand->GetCardsTotal() == 21) {
//                     EXPECT_TRUE(dealerHand->GetHashTable()->Contains(dealerHand->GetTableMatrix()[1][4]));
//                 }
//                 else {
//                     EXPECT_FALSE(dealerHand->GetHashTable()->Contains(dealerHand->GetTableMatrix()[1][4]));
//                 }
//                 EXPECT_EQ(testHand->GetPlayerHands()->RetrieveNode(0)->data->GetPlayerCards()->GetSize(), 2);
//                 EXPECT_EQ(dealerHand->GetPlayerCards()->GetSize(), 2);
//                 EXPECT_EQ(testHand->GetPlayerHands()->RetrieveNode(0)->data->GetWager(), testHand->GetWager());
//                 EXPECT_EQ(testHand->GetBankTotal(), testHand->GetPlayerHands()->RetrieveNode(0)->data->GetBankTotal());
//             }
//             testHand->ResetHand();
//             dealerHand->ResetHand();
//             testHand->BankDepositSim(priorBank);
//         }
//     }
// }

// Dealer logic test check
TEST_F(test_x, DealerLogicTest) {
    for (int i = 0; i < random_int(100, 1000); i++) {
        std::shared_ptr<Hand> testHand(new Hand);
        std::shared_ptr<Hand> dealerHand(new Hand);
        std::shared_ptr<Shoe> testShoe(new Shoe);
        std::shared_ptr<Card> testCard(new Card);
        std::shared_ptr<node<Card>> testNode;
        float priorBank = 100;
        float handWager = 10;
        testHand->NameSim("Borby");
        dealerHand->NameSim("Dealer");
        testHand->BankDepositSim(priorBank);
        priorBank = testHand->GetBankTotal();
        testShoe->SetNumOfDecks(1);
        testShoe->CreateShoeSim();
        while (testShoe->GetCardsInShoe()->GetSize() >= 13) {
            auto dsa_result = dealer_showing_ace_sim(testHand, dealerHand, testShoe, handWager, false);
            // Neither player has blackjack
            if (std::get<3>(dsa_result)) {
                EXPECT_EQ(testHand->GetPlayerHands()->GetSize(), 0);
                EXPECT_EQ(testHand->GetPlayerCards()->GetSize(), 2);
                EXPECT_EQ(dealerHand->GetPlayerCards()->GetSize(), 2);
                EXPECT_TRUE(testHand->GetCardsTotal() < 21);
                EXPECT_TRUE(dealerHand->GetCardsTotal() < 21);
                auto pls_result = player_logic_sim(testHand, dealerHand, testShoe, true);
                for (int i = 0; i < testHand->GetPlayerHands()->GetSize(); i++) {
                    EXPECT_TRUE(testHand->GetPlayerHands()->RetrieveNode(i)->data->GetPlayerCards()->GetSize() >= 2);
                    EXPECT_EQ(testHand->GetBankTotal(), testHand->GetPlayerHands()->RetrieveNode(i)->data->GetBankTotal());
                }
                auto dl_result = dealer_logic_sim(testHand, dealerHand, testShoe);
                EXPECT_TRUE(dealerHand->GetPlayerCards()->GetSize() >= 2);
            }
            // Someone has blackjack
            else {
                EXPECT_FALSE(testHand->GetPlayerHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testHand->GetTableMatrix()[1][0]));
                EXPECT_FALSE(testHand->GetPlayerHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testHand->GetTableMatrix()[2][0]));
                if (testHand->GetCardsTotal() == 21) {
                    EXPECT_TRUE(testHand->GetPlayerHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testHand->GetTableMatrix()[1][4]));
                }
                else {
                    EXPECT_FALSE(testHand->GetPlayerHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testHand->GetTableMatrix()[1][4]));
                }
                if (dealerHand->GetCardsTotal() == 21) {
                    EXPECT_TRUE(dealerHand->GetHashTable()->Contains(dealerHand->GetTableMatrix()[1][4]));
                }
                else {
                    EXPECT_FALSE(dealerHand->GetHashTable()->Contains(dealerHand->GetTableMatrix()[1][4]));
                }
                EXPECT_EQ(testHand->GetPlayerHands()->RetrieveNode(0)->data->GetPlayerCards()->GetSize(), 2);
                EXPECT_EQ(dealerHand->GetPlayerCards()->GetSize(), 2);
                EXPECT_EQ(testHand->GetPlayerHands()->RetrieveNode(0)->data->GetWager(), testHand->GetWager());
                EXPECT_EQ(testHand->GetBankTotal(), testHand->GetPlayerHands()->RetrieveNode(0)->data->GetBankTotal());
            }
            testHand->ResetHand();
            dealerHand->ResetHand();
            testHand->BankDepositSim(priorBank);
        }
    }
}

// Hand comparison logic test
TEST_F(test_x, HandComparisonLogic) {
    std::shared_ptr<Hand> testHand(new Hand);
    std::shared_ptr<Hand> dealerHand(new Hand);
    std::shared_ptr<Shoe> testShoe(new Shoe);
    std::shared_ptr<Card> testCard(new Card);
    std::shared_ptr<node<Card>> testNode;
    float priorBank = 100;
    float handWager = 10;
    testHand->NameSim("Borby");
    dealerHand->NameSim("Dealer");
    testHand->BankDepositSim(priorBank);
    priorBank = testHand->GetBankTotal();
    testShoe->SetNumOfDecks(1);
    testShoe->CreateShoeSim();
    testCard = std::make_shared<Card>(Ranks[6], Suits[0]);
    testNode = testShoe->GetCardsInShoe()->InitNode(testCard);
    testShoe->GetCardsInShoe()->AppendNode(testNode);
    testCard = std::make_shared<Card>(Ranks[7], Suits[0]);
    testNode = testShoe->GetCardsInShoe()->InitNode(testCard);
    testShoe->GetCardsInShoe()->AppendNode(testNode);
    testCard = std::make_shared<Card>(Ranks[6], Suits[0]);
    testNode = testShoe->GetCardsInShoe()->InitNode(testCard);
    testShoe->GetCardsInShoe()->AppendNode(testNode);
    testCard = std::make_shared<Card>(Ranks[7], Suits[0]);
    testNode = testShoe->GetCardsInShoe()->InitNode(testCard);
    testShoe->GetCardsInShoe()->AppendNode(testNode);
    while (testShoe->GetCardsInShoe()->GetSize() >= 13) {
        auto dsa_result = dealer_showing_ace_sim(testHand, dealerHand, testShoe, handWager, false);
        // Neither player has blackjack
        if (std::get<3>(dsa_result)) {
            EXPECT_EQ(testHand->GetPlayerHands()->GetSize(), 0);
            EXPECT_EQ(testHand->GetPlayerCards()->GetSize(), 2);
            EXPECT_EQ(dealerHand->GetPlayerCards()->GetSize(), 2);
            EXPECT_TRUE(testHand->GetCardsTotal() < 21);
            EXPECT_TRUE(dealerHand->GetCardsTotal() < 21);
            testHand->ShowHand("Initial");
            dealerHand->ShowHand("Initial");
            std::cout << std::endl;
            auto pls_result = player_logic_sim(testHand, dealerHand, testShoe, true);
            for (int i = 0; i < testHand->GetPlayerHands()->GetSize(); i++) {
                testHand->GetPlayerHands()->RetrieveNode(i)->data->ShowHand("Final");
            }
            std::cout << std::endl;
            dealerHand->ShowHand("Initial", "Show");
            auto dl_result = dealer_logic_sim(testHand, dealerHand, testShoe);
            dealerHand->ShowHand("Final", "Show");
            std::cout << std::endl;
            auto hcl_result = hand_comparison_logic_sim(testHand, dealerHand);
            for (int i = 0; i < testHand->GetPlayerHands()->GetSize(); i++) {
                testHand->GetPlayerHands()->RetrieveNode(i)->data->ShowHand("Final");
            }
            dealerHand->ShowHand("Final", "Show");
            std::cout << std::endl << testHand->GetBankTotal() << std::endl;
            std::cout << "----------------------------------" << std::endl << std::endl;
        }
        // Someone has blackjack
        else {
            EXPECT_FALSE(testHand->GetPlayerHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testHand->GetTableMatrix()[1][0]));
            EXPECT_FALSE(testHand->GetPlayerHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testHand->GetTableMatrix()[2][0]));
            if (testHand->GetCardsTotal() == 21) {
                EXPECT_TRUE(testHand->GetPlayerHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testHand->GetTableMatrix()[1][4]));
            }
            else {
                EXPECT_FALSE(testHand->GetPlayerHands()->RetrieveNode(0)->data->GetHashTable()->Contains(testHand->GetTableMatrix()[1][4]));
            }
            if (dealerHand->GetCardsTotal() == 21) {
                EXPECT_TRUE(dealerHand->GetHashTable()->Contains(dealerHand->GetTableMatrix()[1][4]));
            }
            else {
                EXPECT_FALSE(dealerHand->GetHashTable()->Contains(dealerHand->GetTableMatrix()[1][4]));
            }
            EXPECT_EQ(testHand->GetPlayerHands()->RetrieveNode(0)->data->GetPlayerCards()->GetSize(), 2);
            EXPECT_EQ(dealerHand->GetPlayerCards()->GetSize(), 2);
            EXPECT_EQ(testHand->GetPlayerHands()->RetrieveNode(0)->data->GetWager(), testHand->GetWager());
            EXPECT_EQ(testHand->GetBankTotal(), testHand->GetPlayerHands()->RetrieveNode(0)->data->GetBankTotal());
        }
        csv_generator(testHand);
        testHand->ResetHand();
        dealerHand->ResetHand();
        // testHand->BankDepositSim(priorBank);
    }
}