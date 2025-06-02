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