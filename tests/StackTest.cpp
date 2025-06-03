#include <gtest/gtest.h>
#include <string>
#include <optional>

#include "ArrayStack.hpp"
#include "LinkedStack.hpp"

class StackTest : public ::testing::Test {
protected:
    ArrayStack<std::string> array;
    LinkedStack<std::string> linked;

    void SetUp() override
    {
        array = ArrayStack<std::string>();
        linked = LinkedStack<std::string>();
    }

    void TearDown() override
    {

    }
};

TEST_F(StackTest, testInitialization)
{
    // testing array backed queue
    EXPECT_EQ(array.getSize(), 0);

    const std::optional<std::string>* arrBacking = array.getBackingArray().get();
    for (size_t i = 0; i < array.getSize(); i++)
        ASSERT_EQ(arrBacking[i], std::nullopt) << "expected nullopt at index " << i;

    // testing linked list backed queue
    EXPECT_EQ(linked.getSize(), 0);
    ASSERT_EQ(linked.getHead(), nullptr);
}

TEST_F(StackTest, testArrayPush)
{
    array.push("0a");    // 0a
    array.push("1a");    // 0a, 1a
    array.push("2a");    // 0a, 1a, 2a
    array.push("3a");    // 0a, 1a, 2a, 3a
    array.push("4a");    // 0a, 1a, 2a, 3a, 4a
    EXPECT_EQ(array.getSize(), 5);

    std::array<std::string, 5> expected {{
        "0a", "1a", "2a", "3a", "4a"
    }};

    const std::optional<std::string>* arrBacking = array.getBackingArray().get();

    for (size_t i = 0; i < expected.size(); i++)
        ASSERT_EQ(arrBacking[i], expected[i]);
}

TEST_F(StackTest, testLinkedPush)
{
    linked.push("0a");   // 0a
    linked.push("1a");   // 0a, 1a
    linked.push("2a");   // 0a, 1a, 2a
    linked.push("3a");   // 0a, 1a, 2a, 3a
    linked.push("4a");   // 0a, 1a, 2a, 3a, 4a
    EXPECT_EQ(linked.getSize(), 5);

    LinkedNode<std::string>* current = linked.getHead();
    ASSERT_NE(current, nullptr);
    ASSERT_EQ(current->getData(), "4a");

    current = current->getNext();
    ASSERT_NE(current, nullptr);
    ASSERT_EQ(current->getData(), "3a");

    current = current->getNext();
    ASSERT_NE(current, nullptr);
    ASSERT_EQ(current->getData(), "2a");

    current = current->getNext();
    ASSERT_NE(current, nullptr);
    ASSERT_EQ(current->getData(), "1a");

    current = current->getNext();
    ASSERT_NE(current, nullptr);
    ASSERT_EQ(current->getData(), "0a");

    current = current->getNext();
    ASSERT_EQ(current, nullptr);
}

TEST_F(StackTest, testArrayPop)
{
    std::string temp { "5a" };

    array.push("0a");    // 0a
    array.push("1a");    // 0a, 1a
    array.push("2a");    // 0a, 1a, 2a
    array.push("3a");    // 0a, 1a, 2a, 3a
    array.push("4a");    // 0a, 1a, 2a, 3a, 4a
    array.push(temp);    // 0a, 1a, 2a, 3a, 4a, 5a
    EXPECT_EQ(array.getSize(), 6);

    ASSERT_EQ(array.pop(), temp);
    EXPECT_EQ(array.getSize(), 5);

    std::array<std::optional<std::string>, 6> expected {{
        "0a", "1a", "2a", "3a", "4a", std::nullopt
    }};

    const std::optional<std::string>* arrBacking = array.getBackingArray().get();

    for (size_t i = 0; i < expected.size(); i++)
        ASSERT_EQ(arrBacking[i], expected[i]);
}

TEST_F(StackTest, testLinkedPop)
{
    std::string temp { "5a" };

    linked.push("0a");    // 0a
    linked.push("1a");    // 0a, 1a
    linked.push("2a");    // 0a, 1a, 2a
    linked.push("3a");    // 0a, 1a, 2a, 3a
    linked.push("4a");    // 0a, 1a, 2a, 3a, 4a
    linked.push(temp);    // 0a, 1a, 2a, 3a, 4a, 5a
    EXPECT_EQ(linked.getSize(), 6);

    ASSERT_EQ(linked.pop(), temp);
    EXPECT_EQ(linked.getSize(), 5);

    LinkedNode<std::string>* current = linked.getHead();
    ASSERT_NE(current, nullptr);
    ASSERT_EQ(current->getData(), "4a");

    current = current->getNext();
    ASSERT_NE(current, nullptr);
    ASSERT_EQ(current->getData(), "3a");

    current = current->getNext();
    ASSERT_NE(current, nullptr);
    ASSERT_EQ(current->getData(), "2a");

    current = current->getNext();
    ASSERT_NE(current, nullptr);
    ASSERT_EQ(current->getData(), "1a");

    current = current->getNext();
    ASSERT_NE(current, nullptr);
    ASSERT_EQ(current->getData(), "0a");

    current = current->getNext();
    ASSERT_EQ(current, nullptr);
}

TEST_F(StackTest, testArrayPeek)
{
    std::string temp { "4a" };

    array.push("0a");    // 0a
    array.push("1a");    // 0a, 1a
    array.push("2a");    // 0a, 1a, 2a
    array.push("3a");    // 0a, 1a, 2a, 3a
    array.push(temp);    // 0a, 1a, 2a, 3a, 4a
    EXPECT_EQ(array.getSize(), 5);

    ASSERT_EQ(temp , array.peek());
}

TEST_F(StackTest, testLinkedPeek)
{
    std::string temp { "4a" };

    linked.push("0a");    // 0a
    linked.push("1a");    // 0a, 1a
    linked.push("2a");    // 0a, 1a, 2a
    linked.push("3a");    // 0a, 1a, 2a, 3a
    linked.push(temp);    // 0a, 1a, 2a, 3a, 4a
    EXPECT_EQ(linked.getSize(), 5);

    ASSERT_EQ(linked.peek(), temp);
}
