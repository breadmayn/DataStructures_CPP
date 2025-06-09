#include <gtest/gtest.h>
#include <string>

#include "ExternalChaining.hpp"

class ExternalChainingTest : public ::testing::Test {
protected:
    using string = std::string;
    using ExpectedArr = ExternalChainingEntry<int, string>*;

    ExternalChaining<int, string> map;
    ExpectedArr* expected;

    void SetUp() override
    {
        map = ExternalChaining<int, string>();
        expected = new ExpectedArr[ExternalChaining<int, string>::INITIAL_CAPACITY];
    }

    void TearDown() override
    {
        delete[] expected;
    }

    // ~ExternalChainingTest() noexcept override = default;
};

TEST_F(ExternalChainingTest, testInitialization)
{
    ASSERT_EQ(map.getSize(), 0);

    const auto& table { map.getTable() };
    
    for (size_t i = 0; i < map.getNumBuckets(); i++)
        ASSERT_EQ(table[i], expected[i]);
}

TEST_F(ExternalChainingTest, testPut)
{
    // [(0, A), (1, B), (2, C), (3, D), (4, E), _, _, _, _, _, _, _, _]
    ASSERT_EQ(std::nullopt, map.put(0, "A"));
    ASSERT_EQ(std::nullopt, map.put(1, "B"));
    ASSERT_EQ(std::nullopt, map.put(2, "C"));
    ASSERT_EQ(std::nullopt, map.put(3, "D"));
    ASSERT_EQ(std::nullopt, map.put(4, "E"));

    EXPECT_EQ(5, map.getSize());

    const auto& table { map.getTable() };

    expected[0] = new ExternalChainingEntry<int, string>(0, "A");
    expected[1] = new ExternalChainingEntry<int, string>(1, "B");
    expected[2] = new ExternalChainingEntry<int, string>(2, "C");
    expected[3] = new ExternalChainingEntry<int, string>(3, "D");
    expected[4] = new ExternalChainingEntry<int, string>(4, "E");

    for (size_t i = 0; i < map.getNumBuckets(); i++)
        ASSERT_EQ(*expected[i], *table[i]);
}

TEST_F(ExternalChainingTest, testRemove)
{
    string temp = "D";

    // [(0, A), (1, B), (2, C), (3, D), (4, E), _, _, _, _, _, _, _, _]
    ASSERT_EQ(std::nullopt, map.put(0, "A"));
    ASSERT_EQ(std::nullopt, map.put(1, "B"));
    ASSERT_EQ(std::nullopt, map.put(2, "C"));
    ASSERT_EQ(std::nullopt, map.put(3, temp));
    ASSERT_EQ(std::nullopt, map.put(4, "E"));

    EXPECT_EQ(5, map.getSize());

    ASSERT_EQ(temp, map.remove(3));
    EXPECT_EQ(4, map.getSize());

    expected[0] = new ExternalChainingEntry<int, string>(0, "A");
    expected[1] = new ExternalChainingEntry<int, string>(1, "B");
    expected[2] = new ExternalChainingEntry<int, string>(2, "C");
    expected[4] = new ExternalChainingEntry<int, string>(4, "E");

    const auto& table { map.getTable() };

    for (size_t i = 0; i < map.getNumBuckets(); i++)
        ASSERT_EQ(*expected[i], *table[i]);
}