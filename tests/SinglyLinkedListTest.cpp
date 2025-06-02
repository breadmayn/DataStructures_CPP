#include <gtest/gtest.h>
#include <string>

#include "SinglyLinkedList.hpp"

class SinglyLinkedListTest : public ::testing::Test {
protected:
    SinglyLinkedList<std::string> list;

    void SetUp() override {
        list = SinglyLinkedList<std::string>();
    }

    void TearDown() override {
        
    }

public:
    using Node = SinglyLinkedListNode<std::string>;
};

TEST_F(SinglyLinkedListTest, testInitialization)
{
    ASSERT_EQ(list.getSize(), 0);
    ASSERT_EQ(list.getHead(), nullptr);
    ASSERT_EQ(list.getTail(), nullptr);
}

TEST_F(SinglyLinkedListTest, testAddAtIndex)
{
    list.addAtIndex(0, "2a");
    list.addAtIndex(0, "1a");
    list.addAtIndex(2, "4a");
    list.addAtIndex(2, "3a");
    list.addAtIndex(0, "0a");

    EXPECT_EQ(list.getSize(), 5);

    Node* current = list.getHead();
    ASSERT_NE(current, nullptr);
    EXPECT_EQ(current->data, "0a");

    current = current->next;
    ASSERT_NE(current, nullptr);
    EXPECT_EQ(current->data, "1a");

    current = current->next;
    ASSERT_NE(current, nullptr);
    EXPECT_EQ(current->data, "2a");

    current = current->next;
    ASSERT_NE(current, nullptr);
    EXPECT_EQ(current->data, "3a");

    current = current->next;
    ASSERT_NE(current, nullptr);
    EXPECT_EQ(current->data, "4a");

    current = current->next;
    ASSERT_EQ(current, nullptr);
}

TEST_F(SinglyLinkedListTest, testAddToFront)
{
    list.addToFront("4a");  // 4a
    list.addToFront("3a");  // 3a, 4a
    list.addToFront("2a");  // 2a, 3a, 4a
    list.addToFront("1a");  // 1a, 2a, 3a, 4a
    list.addToFront("0a");  // 0a, 1a, 2a, 3a, 4a

    EXPECT_EQ(list.getSize(), 5);

    Node* current = list.getHead();
    ASSERT_NE(current, nullptr);
    EXPECT_EQ(current->data, "0a");

    current = current->next;
    ASSERT_NE(current, nullptr);
    EXPECT_EQ(current->data, "1a");

    current = current->next;
    ASSERT_NE(current, nullptr);
    EXPECT_EQ(current->data, "2a");

    current = current->next;
    ASSERT_NE(current, nullptr);
    EXPECT_EQ(current->data, "3a");

    current = current->next;
    ASSERT_NE(current, nullptr);
    EXPECT_EQ(current->data, "4a");
    ASSERT_EQ(list.getTail(), current); // checking pointers are the same

    current = current->next;
    ASSERT_EQ(current, nullptr);
}

TEST_F(SinglyLinkedListTest, testAddToBack)
{
    list.addToBack("0a");   // 0a
    list.addToBack("1a");   // 0a, 1a
    list.addToBack("2a");   // 0a, 1a, 2a
    list.addToBack("3a");   // 0a, 1a, 2a, 3a
    list.addToBack("4a");   // 0a, 1a, 2a, 3a, 4a

    EXPECT_EQ(list.getSize(), 5);

    Node* current = list.getHead();
    ASSERT_NE(current, nullptr);
    EXPECT_EQ(current->data, "0a");

    current = current->next;
    ASSERT_NE(current, nullptr);
    EXPECT_EQ(current->data, "1a");

    current = current->next;
    ASSERT_NE(current, nullptr);
    EXPECT_EQ(current->data, "2a");

    current = current->next;
    ASSERT_NE(current, nullptr);
    EXPECT_EQ(current->data, "3a");

    current = current->next;
    ASSERT_NE(current, nullptr);
    EXPECT_EQ(current->data, "4a");
    ASSERT_EQ(list.getTail(), current); // checking pointers are the same

    current = current->next;
    ASSERT_EQ(current, nullptr);
}

TEST_F(SinglyLinkedListTest, testRemoveAtIndex)
{
    std::string temp { "2a" };

    list.addAtIndex(0, "0a");   // 0a
    list.addAtIndex(1, "1a");   // 0a, 1a
    list.addAtIndex(2, temp);   // 0a, 1a, 2a
    list.addAtIndex(3, "3a");   // 0a, 1a, 2a, 3a
    list.addAtIndex(4, "4a");   // 0a, 1a, 2a, 3a, 4a
    list.addAtIndex(5, "5a");   // 0a, 1a, 2a, 3a, 4a, 5a
    EXPECT_EQ(list.getSize(), 6);

    ASSERT_EQ(temp, list.removeAtIndex(2));
    EXPECT_EQ(list.getSize(), 5);

    Node* current = list.getHead();
    ASSERT_NE(current, nullptr);
    EXPECT_EQ(current->data, "0a");

    current = current->next;
    ASSERT_NE(current, nullptr);
    EXPECT_EQ(current->data, "1a");

    current = current->next;
    ASSERT_NE(current, nullptr);
    EXPECT_EQ(current->data, "3a");

    current = current->next;
    ASSERT_NE(current, nullptr);
    EXPECT_EQ(current->data, "4a");

    current = current->next;
    ASSERT_NE(current, nullptr);
    EXPECT_EQ(current->data, "5a");
    ASSERT_EQ(list.getTail(), current); // checking pointers are the same

    current = current->next;
    ASSERT_EQ(current, nullptr);
}

TEST_F(SinglyLinkedListTest, testRemoveFromFront)
{
    std::string temp { "0a" };

    list.addAtIndex(0, temp);   // 0a
    list.addAtIndex(1, "1a");   // 0a, 1a
    list.addAtIndex(2, "2a");   // 0a, 1a, 2a
    list.addAtIndex(3, "3a");   // 0a, 1a, 2a, 3a
    list.addAtIndex(4, "4a");   // 0a, 1a, 2a, 3a, 4a
    list.addAtIndex(5, "5a");   // 0a, 1a, 2a, 3a, 4a, 5a
    EXPECT_EQ(list.getSize(), 6);

    ASSERT_EQ(temp, list.removeFromFront());
    EXPECT_EQ(list.getSize(), 5);

    Node* current = list.getHead();
    ASSERT_NE(current, nullptr);
    EXPECT_EQ(current->data, "1a");

    current = current->next;
    ASSERT_NE(current, nullptr);
    EXPECT_EQ(current->data, "2a");

    current = current->next;
    ASSERT_NE(current, nullptr);
    EXPECT_EQ(current->data, "3a");

    current = current->next;
    ASSERT_NE(current, nullptr);
    EXPECT_EQ(current->data, "4a");

    current = current->next;
    ASSERT_NE(current, nullptr);
    EXPECT_EQ(current->data, "5a");
    ASSERT_EQ(list.getTail(), current); // checking pointers are the same

    current = current->next;
    ASSERT_EQ(current, nullptr);
}

TEST_F(SinglyLinkedListTest, testRemoveFromBack)
{
    std::string temp { "5a" };

    list.addAtIndex(0, "0a");   // 0a
    list.addAtIndex(1, "1a");   // 0a, 1a
    list.addAtIndex(2, "2a");   // 0a, 1a, 2a
    list.addAtIndex(3, "3a");   // 0a, 1a, 2a, 3a
    list.addAtIndex(4, "4a");   // 0a, 1a, 2a, 3a, 4a
    list.addAtIndex(5, temp);   // 0a, 1a, 2a, 3a, 4a, 5a
    EXPECT_EQ(list.getSize(), 6);

    ASSERT_EQ(temp, list.removeFromBack());
    EXPECT_EQ(list.getSize(), 5);

    Node* current = list.getHead();
    ASSERT_NE(current, nullptr);
    EXPECT_EQ(current->data, "0a");

    current = current->next;
    ASSERT_NE(current, nullptr);
    EXPECT_EQ(current->data, "1a");

    current = current->next;
    ASSERT_NE(current, nullptr);
    EXPECT_EQ(current->data, "2a");

    current = current->next;
    ASSERT_NE(current, nullptr);
    EXPECT_EQ(current->data, "3a");

    current = current->next;
    ASSERT_NE(current, nullptr);
    EXPECT_EQ(current->data, "4a");
    ASSERT_EQ(list.getTail(), current); // checking pointers are the same

    current = current->next;
    ASSERT_EQ(current, nullptr);
}

TEST_F(SinglyLinkedListTest, testGet)
{
    list.addAtIndex(0, "0a");   // 0a
    list.addAtIndex(1, "1a");   // 0a, 1a
    list.addAtIndex(2, "2a");   // 0a, 1a, 2a
    list.addAtIndex(3, "3a");   // 0a, 1a, 2a, 3a
    list.addAtIndex(4, "4a");   // 0a, 1a, 2a, 3a, 4a
    EXPECT_EQ(list.getSize(), 5);

    ASSERT_EQ(list.get(0), "0a");
    ASSERT_EQ(list.get(1), "1a");
    ASSERT_EQ(list.get(2), "2a");
    ASSERT_EQ(list.get(3), "3a");
    ASSERT_EQ(list.get(4), "4a");
}

TEST_F(SinglyLinkedListTest, testIsEmpty)
{
    ASSERT_TRUE(list.isEmpty());

    list.addAtIndex(0, "0a");   // 0a
    list.addAtIndex(1, "1a");   // 0a, 1a
    list.addAtIndex(2, "2a");   // 0a, 1a, 2a
    list.addAtIndex(3, "3a");   // 0a, 1a, 2a, 3a
    list.addAtIndex(4, "4a");   // 0a, 1a, 2a, 3a, 4a
    EXPECT_EQ(list.getSize(), 5);

    ASSERT_FALSE(list.isEmpty());
}

TEST_F(SinglyLinkedListTest, testClear)
{
    list.addAtIndex(0, "0a");   // 0a
    list.addAtIndex(1, "1a");   // 0a, 1a
    list.addAtIndex(2, "2a");   // 0a, 1a, 2a
    list.addAtIndex(3, "3a");   // 0a, 1a, 2a, 3a
    list.addAtIndex(4, "4a");   // 0a, 1a, 2a, 3a, 4a
    EXPECT_EQ(list.getSize(), 5);

    list.clear();

    ASSERT_EQ(list.getSize(), 0);
    ASSERT_EQ(list.getHead(), nullptr);
    ASSERT_EQ(list.getTail(), nullptr);
}

TEST_F(SinglyLinkedListTest, testLastOccurrence)
{
    std::string temp { "2a" };

    list.addAtIndex(0, "0a");   // 0a
    list.addAtIndex(1, "1a");   // 0a, 1a
    list.addAtIndex(2, "2a");   // 0a, 1a, 2a
    list.addAtIndex(3, temp);   // 0a, 1a, 2a, 2a
    list.addAtIndex(4, "3a");   // 0a, 1a, 2a, 2a, 3a
    list.addAtIndex(5, "4a");   // 0a, 1a, 2a, 2a, 3a, 4a
    EXPECT_EQ(list.getSize(), 6);

    ASSERT_EQ(temp, list.removeLastOccurrence("2a"));
    EXPECT_EQ(list.getSize(), 5);

    Node* current = list.getHead();
    ASSERT_NE(current, nullptr);
    EXPECT_EQ(current->data, "0a");

    current = current->next;
    ASSERT_NE(current, nullptr);
    EXPECT_EQ(current->data, "1a");

    current = current->next;
    ASSERT_NE(current, nullptr);
    EXPECT_EQ(current->data, "2a");

    current = current->next;
    ASSERT_NE(current, nullptr);
    EXPECT_EQ(current->data, "3a");

    current = current->next;
    ASSERT_NE(current, nullptr);
    EXPECT_EQ(current->data, "4a");
    ASSERT_EQ(list.getTail(), current); // checking pointers are the same

    current = current->next;
    ASSERT_EQ(current, nullptr);
}

TEST_F(SinglyLinkedListTest, testToArray)
{
    list.addAtIndex(0, "0a");   // 0a
    list.addAtIndex(1, "1a");   // 0a, 1a
    list.addAtIndex(2, "2a");   // 0a, 1a, 2a
    list.addAtIndex(3, "3a");   // 0a, 1a, 2a, 3a
    list.addAtIndex(4, "4a");   // 0a, 1a, 2a, 3a, 4a
    EXPECT_EQ(list.getSize(), 5);

    std::vector<std::string> expected {
        "0a", "1a", "2a", "3a", "4a"
    };

    ASSERT_EQ(expected, list.toArray());
}
