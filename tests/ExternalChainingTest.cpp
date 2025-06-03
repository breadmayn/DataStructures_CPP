#include <gtest/gtest.h>
#include <string>

#include "ExternalChaining.hpp"

class ExternalChainingTest : public ::testing::Test {
protected:
    ExternalChaining<int, std::string> map;

    void SetUp() override
    {
        map = ExternalChaining<int, std::string>();
    }

    void TearDown() override
    {

    }

    ~ExternalChainingTest() noexcept override = default;
};

TEST_F(ExternalChainingTest, testInitialization)
{
    ASSERT_EQ(0, map.getSize());

    const ExternalChainingEntry<int, std::string>* const* backingTable = map.getTable().get();
    for (size_t i = 0; i < ExternalChaining<int, std::string>::INITIAL_CAPACITY; i++)
        ASSERT_EQ(backingTable[i], nullptr) << "Expected null at index " << i;
}

TEST_F(ExternalChainingTest, testPut)
{
    // [(0, A), (1, B), (2, C), (3, D), (4, E), _, _, _, _, _, _, _, _]
    ASSERT_FALSE(map.put(0, "A").has_value());
    ASSERT_FALSE(map.put(1, "B").has_value());
    ASSERT_FALSE(map.put(2, "C").has_value());
    ASSERT_FALSE(map.put(3, "D").has_value());
    ASSERT_FALSE(map.put(4, "E").has_value());

    ASSERT_EQ(5, map.getSize());
    ExternalChainingMapEntry<Integer, String>[] expected =
        (ExternalChainingMapEntry<Integer, String>[])
            new ExternalChainingMapEntry[ExternalChainingHashMap
                .INITIAL_CAPACITY];
    expected[0] = new ExternalChainingMapEntry<>(0, "A");
    expected[1] = new ExternalChainingMapEntry<>(1, "B");
    expected[2] = new ExternalChainingMapEntry<>(2, "C");
    expected[3] = new ExternalChainingMapEntry<>(3, "D");
    expected[4] = new ExternalChainingMapEntry<>(4, "E");
    assertArrayEquals(expected, map.getTable());
}

TEST_F(ExternalChainingTest, testRemove)
{
    String temp = "D";

    // [(0, A), (1, B), (2, C), (3, D), (4, E), _, _, _, _, _, _, _, _]
    ASSERT_FALSE(map.put(0, "A").has_value());
    ASSERT_FALSE(map.put(1, "B").has_value());
    ASSERT_FALSE(map.put(2, "C").has_value());
    ASSERT_FALSE(map.put(3, temp).has_value());
    ASSERT_FALSE(map.put(4, "E").has_value());
    ASSERT_EQ(5, map.getSize());

    // [(0, A), (1, B), (2, C), _, (4, E), _, _, _, _, _, _, _, _]
    assertSame(temp, map.remove(3));

    ASSERT_EQ(4, map.getSize());

    ExternalChainingMapEntry<Integer, String>[] expected =
        (ExternalChainingMapEntry<Integer, String>[])
            new ExternalChainingMapEntry[ExternalChainingHashMap
                .INITIAL_CAPACITY];
    expected[0] = new ExternalChainingMapEntry<>(0, "A");
    expected[1] = new ExternalChainingMapEntry<>(1, "B");
    expected[2] = new ExternalChainingMapEntry<>(2, "C");
    expected[4] = new ExternalChainingMapEntry<>(4, "E");
    assertArrayEquals(expected, map.getTable());
}

TEST_F(ExternalChainingTest, testGet)
{
    // [(0, A), (1, B), (2, C), (3, D), (4, E), _, _, _, _, _, _, _, _]
    ASSERT_FALSE(map.put(0, "A").has_value());
    ASSERT_FALSE(map.put(1, "B").has_value());
    ASSERT_FALSE(map.put(2, "C").has_value());
    ASSERT_FALSE(map.put(3, "D").has_value());
    ASSERT_FALSE(map.put(4, "E").has_value());
    ASSERT_EQ(5, map.getSize());

    ASSERT_EQ("A", map.get(0));
    ASSERT_EQ("B", map.get(1));
    ASSERT_EQ("C", map.get(2));
    ASSERT_EQ("D", map.get(3));
    ASSERT_EQ("E", map.get(4));
}

TEST_F(ExternalChainingTest, testContainsKey)
{
    // [(0, A), (1, B), (2, C), (3, D), (4, E), _, _, _, _, _, _, _, _]
    ASSERT_FALSE(map.put(0, "A").has_value());
    ASSERT_FALSE(map.put(1, "B").has_value());
    ASSERT_FALSE(map.put(2, "C").has_value());
    ASSERT_FALSE(map.put(3, "D").has_value());
    ASSERT_FALSE(map.put(4, "E").has_value());
    ASSERT_EQ(5, map.getSize());

    assertTrue(map.containsKey(3));
    assertFalse(map.containsKey(5));
}

TEST_F(ExternalChainingTest, testKeySet)
{
    // [(0, A), (1, B), (2, C), (3, D), (4, E), _, _, _, _, _, _, _, _]
    ASSERT_FALSE(map.put(0, "A").has_value());
    ASSERT_FALSE(map.put(1, "B").has_value());
    ASSERT_FALSE(map.put(2, "C").has_value());
    ASSERT_FALSE(map.put(3, "D").has_value());
    ASSERT_FALSE(map.put(4, "E").has_value());
    ASSERT_EQ(5, map.getSize());

    Set<Integer> expected = new HashSet<>();
    expected.add(0);
    expected.add(1);
    expected.add(2);
    expected.add(3);
    expected.add(4);
    ASSERT_EQ(expected, map.keySet());
}

TEST_F(ExternalChainingTest, testValues)
{
    // [(0, A), (1, B), (2, C), (3, D), (4, E), _, _, _, _, _, _, _, _]
    ASSERT_FALSE(map.put(0, "A").has_value());
    ASSERT_FALSE(map.put(1, "B").has_value());
    ASSERT_FALSE(map.put(2, "C").has_value());
    ASSERT_FALSE(map.put(3, "D").has_value());
    ASSERT_FALSE(map.put(4, "E").has_value());
    ASSERT_EQ(5, map.getSize());

    List<String> expected = new LinkedList<>();
    expected.add("A");
    expected.add("B");
    expected.add("C");
    expected.add("D");
    expected.add("E");
    ASSERT_EQ(expected, map.values());
}

TEST_F(ExternalChainingTest, testResize)
{
    // [(0, A), (1, B), (2, C), (3, D), (4, E), _, _, _, _, _, _, _, _]
    ASSERT_FALSE(map.put(0, "A").has_value());
    ASSERT_FALSE(map.put(1, "B").has_value());
    ASSERT_FALSE(map.put(2, "C").has_value());
    ASSERT_FALSE(map.put(3, "D").has_value());
    ASSERT_FALSE(map.put(4, "E").has_value());
    ASSERT_EQ(5, map.getSize());

    // [(0, A), (1, B), (2, C), (3, D), (4, E)]
    map.resizeBackingTable(5);

    ASSERT_EQ(5, map.getSize());

    ExternalChainingMapEntry<Integer, String>[] expected =
        (ExternalChainingMapEntry<Integer, String>[])
            new ExternalChainingMapEntry[5];
    expected[0] = new ExternalChainingMapEntry<>(0, "A");
    expected[1] = new ExternalChainingMapEntry<>(1, "B");
    expected[2] = new ExternalChainingMapEntry<>(2, "C");
    expected[3] = new ExternalChainingMapEntry<>(3, "D");
    expected[4] = new ExternalChainingMapEntry<>(4, "E");
    assertArrayEquals(expected, map.getTable());
}

TEST_F(ExternalChainingTest, testClear)
{
    // [(0, A), (1, B), (2, C), (3, D), (4, E), _, _, _, _, _, _, _, _]
    ASSERT_FALSE(map.put(0, "A").has_value());
    ASSERT_FALSE(map.put(1, "B").has_value());
    ASSERT_FALSE(map.put(2, "C").has_value());
    ASSERT_FALSE(map.put(3, "D").has_value());
    ASSERT_FALSE(map.put(4, "E").has_value());
    ASSERT_EQ(5, map.getSize());

    map.clear();
    ASSERT_EQ(0, map.getSize());
    assertArrayEquals(new ExternalChainingMapEntry[ExternalChainingHashMap
        .INITIAL_CAPACITY], map.getTable());
}