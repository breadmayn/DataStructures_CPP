#include <gtest/gtest.h>
#include <string>
#include <optional>

#include "ArrayQueue.hpp"
#include "LinkedQueue.hpp"

class QueueTest : public ::testing::Test {
protected:
    ArrayQueue<std::string> array;
    LinkedQueue<std::string> linked;

    void SetUp() override
    {
        array = ArrayQueue<std::string>();
        linked = LinkedQueue<std::string>();
    }

    void TearDown() override
    {

    }
};

TEST_F(QueueTest, testInitialization)
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

TEST_F(QueueTest, testArrayEnqueue)
{
    array.enqueue("0a");    // 0a
    array.enqueue("1a");    // 0a, 1a
    array.enqueue("2a");    // 0a, 1a, 2a
    array.enqueue("3a");    // 0a, 1a, 2a, 3a
    array.enqueue("4a");    // 0a, 1a, 2a, 3a, 4a
    EXPECT_EQ(array.getSize(), 5);

    std::array<std::string, 5> expected {{
        "0a", "1a", "2a", "3a", "4a"
    }};

    const std::optional<std::string>* arrBacking = array.getBackingArray().get();

    for (size_t i = 0; i < expected.size(); i++)
        ASSERT_EQ(arrBacking[i], expected[i]);
}

TEST_F(QueueTest, testLinkedEnqueue)
{
    linked.enqueue("0a");   // 0a
    linked.enqueue("1a");   // 0a, 1a
    linked.enqueue("2a");   // 0a, 1a, 2a
    linked.enqueue("3a");   // 0a, 1a, 2a, 3a
    linked.enqueue("4a");   // 0a, 1a, 2a, 3a, 4a
    EXPECT_EQ(linked.getSize(), 5);

    LinkedNode<std::string>* current = linked.getHead();
    ASSERT_NE(current, nullptr);
    ASSERT_EQ(current->getData(), "0a");

    current = current->getNext();
    ASSERT_NE(current, nullptr);
    ASSERT_EQ(current->getData(), "1a");

    current = current->getNext();
    ASSERT_NE(current, nullptr);
    ASSERT_EQ(current->getData(), "2a");

    current = current->getNext();
    ASSERT_NE(current, nullptr);
    ASSERT_EQ(current->getData(), "3a");

    current = current->getNext();
    ASSERT_NE(current, nullptr);
    ASSERT_EQ(current->getData(), "4a");

    current = current->getNext();
    ASSERT_EQ(current, nullptr);
}

TEST_F(QueueTest, testArrayDequeue)
{
    std::string temp { "0a" };

    array.enqueue(temp);    // 0a
    array.enqueue("1a");    // 0a, 1a
    array.enqueue("2a");    // 0a, 1a, 2a
    array.enqueue("3a");    // 0a, 1a, 2a, 3a
    array.enqueue("4a");    // 0a, 1a, 2a, 3a, 4a
    array.enqueue("5a");    // 0a, 1a, 2a, 3a, 4a, 5a
    EXPECT_EQ(array.getSize(), 6);

    ASSERT_EQ(array.dequeue(), temp);
    EXPECT_EQ(array.getSize(), 5);

    std::array<std::optional<std::string>, 6> expected {{
        std::nullopt, "1a", "2a", "3a", "4a", "5a"
    }};

    const std::optional<std::string>* arrBacking = array.getBackingArray().get();

    for (size_t i = 0; i < expected.size(); i++)
        ASSERT_EQ(arrBacking[i], expected[i]);
}

TEST_F(QueueTest, testLinkedDequeue)
{
    std::string temp { "0a" };

    linked.enqueue(temp);   // 0a
    linked.enqueue("1a");   // 0a, 1a
    linked.enqueue("2a");   // 0a, 1a, 2a
    linked.enqueue("3a");    // 0a, 1a, 2a, 3a
    linked.enqueue("4a");    // 0a, 1a, 2a, 3a, 4a
    linked.enqueue("5a");    // 0a, 1a, 2a, 3a, 4a, 5a
    EXPECT_EQ(linked.getSize(), 6);

    ASSERT_EQ(linked.dequeue(), temp);
    EXPECT_EQ(linked.getSize(), 5);

    LinkedNode<std::string>* current = linked.getHead();
    ASSERT_NE(current, nullptr);
    ASSERT_EQ(current->getData(), "1a");

    current = current->getNext();
    ASSERT_NE(current, nullptr);
    ASSERT_EQ(current->getData(), "2a");

    current = current->getNext();
    ASSERT_NE(current, nullptr);
    ASSERT_EQ(current->getData(), "3a");

    current = current->getNext();
    ASSERT_NE(current, nullptr);
    ASSERT_EQ(current->getData(), "4a");

    current = current->getNext();
    ASSERT_NE(current, nullptr);
    ASSERT_EQ(current->getData(), "5a");

    current = current->getNext();
    ASSERT_EQ(current, nullptr);
}

TEST_F(QueueTest, testArrayPeek)
{
    std::string temp { "0a" };

    array.enqueue(temp);    // 0a
    array.enqueue("1a");    // 0a, 1a
    array.enqueue("2a");    // 0a, 1a, 2a
    array.enqueue("3a");    // 0a, 1a, 2a, 3a
    array.enqueue("4a");    // 0a, 1a, 2a, 3a, 4a
    EXPECT_EQ(array.getSize(), 5);

    ASSERT_EQ(temp , array.peek());
}

TEST_F(QueueTest, testLinkedPeek)
{
    std::string temp { "0a" };

    linked.enqueue(temp);   // 0a
    linked.enqueue("1a");   // 0a, 1a
    linked.enqueue("2a");   // 0a, 1a, 2a
    linked.enqueue("3a");    // 0a, 1a, 2a, 3a
    linked.enqueue("4a");    // 0a, 1a, 2a, 3a, 4a
    EXPECT_EQ(linked.getSize(), 5);

    ASSERT_EQ(linked.peek(), temp);
}
