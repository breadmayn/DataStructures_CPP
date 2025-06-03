#pragma once

#include <unordered_set>
#include <vector>
#include <optional>

#include "ExternalChainingEntry.hpp"

/**
 * Your implementation of a ExternalChainingHashMap.
 *
 * @author Brandon Mach
 * @version 1.0
 */
template<typename K, typename V>
class ExternalChaining {
private:
    using BackingTable = std::unique_ptr<ExternalChainingEntry<K, V>*[]>;

    BackingTable table;
    size_t size;

public:
    static constexpr size_t INITIAL_CAPACITY { 13 };
    static constexpr double MAX_LOAD_FACTOR { 0.67 };

    // default constructor
    ExternalChaining()
        : ExternalChaining(INITIAL_CAPACITY)
    { }

    // custom capacity constructor
    ExternalChaining(size_t startingCapacity)
        : table(std::make_unique<ExternalChainingEntry<K, V>*[]>(startingCapacity))
        , size(0)
    { }

    /**
     * Adds the given key-value pair to the map. If an entry in the map
     * already has this key, replace the entry's value with the new one
     * passed in.
     *
     * In the case of a collision, use external chaining as your resolution
     * strategy. Add new entries to the front of an existing chain, but don't
     * forget to check the entire chain for duplicate keys first.
     *
     * If you find a duplicate key, then replace the entry's value with the new
     * one passed in. When replacing the old value, replace it at that position
     * in the chain, not by creating a new entry and adding it to the front.
     *
     * Before actually adding any data to the HashMap, you should check to
     * see if the array would violate the max load factor if the data was
     * added. Resize if the load factor is greater than max LF (it is okay
     * if the load factor is equal to max LF). For example, let's say the
     * array is of length 5 and the current size is 3 (LF = 0.6). For this
     * example, assume that no elements are removed in between steps. If
     * another entry is attempted to be added, before doing anything else,
     * you should check whether (3 + 1) / 5 = 0.8 is larger than the max LF.
     * It is, so you would trigger a resize before you even attempt to add
     * the data or figure out if it's a duplicate. Be careful to consider the
     * differences between integer and double division when calculating load
     * factor.
     *
     * When regrowing, resize the length of the backing table to
     * 2 * old length + 1. You must use the resizeBackingTable method to do so.
     *
     * Return null if the key was not already in the map. If it was in the map,
     * return the old value associated with it.
     *
     * @param key   the key to add
     * @param value the value to add
     * @return null if the key was not already in the map. If it was in the
     * map, return the old value associated with it
     * @throws std::invalid_argument if key or value is null
     */
    std::optional<V> put(K key, V value);

    /**
     * Removes the entry with a matching key from the map.
     *
     * @param key the key to remove
     * @return the value previously associated with the key
     * @throws std::invalid_argument if key is null
     * @throws std::out_of_range   if the key is not in the map
     */
    V remove(K key);

    /**
     * Gets the value associated with the given key.
     *
     * @param key the key to search for in the map
     * @return the value associated with the given key
     * @throws std::invalid_argument if key is null
     * @throws std::out_of_range   if the key is not in the map
     */
    V get(K key) const;

    /**
     * Returns whether or not the key is in the map.
     *
     * @param key the key to search for in the map
     * @return true if the key is contained within the map, false
     * otherwise
     * @throws std::invalid_argument if key is null
     */
    bool containsKey(K key) const;

    /**
     * Returns a Set view of the keys contained in this map.
     *
     * Use java.util.HashSet.
     *
     * @return the set of keys in this map
     */
    std::unordered_set<K> keySet() const;

    /**
     * Returns a List view of the values contained in this map.
     *
     * Use java.util.ArrayList or java.util.LinkedList.
     *
     * You should iterate over the table in order of increasing index and add
     * entries to the List in the order in which they are traversed.
     *
     * @return list of values in this map
     */
    std::vector<V> values() const;

    /**
     * Resize the backing table to length.
     *
     * Disregard the load factor for this method. So, if the passed in length is
     * smaller than the current capacity, and this new length causes the table's
     * load factor to exceed MAX_LOAD_FACTOR, you should still resize the table
     * to the specified length and leave it at that capacity.
     *
     * You should iterate over the old table in order of increasing index and
     * add entries to the new table in the order in which they are traversed.
     *
     * Since resizing the backing table is working with the non-duplicate
     * data already in the table, you shouldn't explicitly check for
     * duplicates.
     *
     * Hint: You cannot just simply copy the entries over to the new array.
     *
     * @param length new length of the backing table
     * @throws std::invalid_argument if length is less than the
     *                                            number of items in the hash
     *                                            map
     */
    void resizeBackingTable(size_t length);

    /**
     * Clears the map.
     *
     * Resets the table to a new array of the initial capacity and resets the
     * size.
     */
    void clear();

    /**
     * Returns the table of the map.
     *
     * For grading purposes only. You shouldn't need to use this method since
     * you have direct access to the variable.
     *
     * @return the table of the map
     */
    const BackingTable& getTable() const { return table; }

    /**
     * Returns the size of the map.
     *
     * For grading purposes only. You shouldn't need to use this method since
     * you have direct access to the variable.
     *
     * @return the size of the map
     */
    size_t getSize() const { return size; }
};

template<typename K, typename V>
std::optional<V> ExternalChaining::put(K key, V value)
{

}

template<typename K, typename V>
V ExternalChaining::remove(K key)
{

}

template<typename K, typename V>
V ExternalChaining::get(K key) const
{

}

template<typename K, typename V>
bool ExternalChaining::containsKey(K key) const
{

}

template<typename K, typename V>
std::unordered_set<K> ExternalChaining::keySet() const
{

}

template<typename K, typename V>
std::vector<V> ExternalChaining::values() const
{

}
