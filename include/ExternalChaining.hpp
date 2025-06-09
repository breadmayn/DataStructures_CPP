#pragma once

#include <unordered_set>
#include <vector>
#include <optional>
#include <functional>

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
    size_t numBuckets;

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
        , numBuckets(startingCapacity)
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
     *
     * @return the table of the map
     */
    const BackingTable& getTable() const { return table; }

    /**
     * Returns the size of the map.
     *
     * @return the size of the map
     */
    size_t getSize() const { return size; }

    /**
     * Returns the capacity of the map.
     *
     * @return the capacity of the map
     */
    size_t getNumBuckets() const { return numBuckets; }
};

template<typename K, typename V>
void ExternalChaining<K, V>::resizeBackingTable(size_t length)
{
    // check if the length argument is smaller than the number of elements in the table
    if (length < size)
        throw std::invalid_argument("cannot resize because length is smaller than the number of elements in the map");

    // create new table to replace the old table with
    BackingTable newTable { std::make_unique<ExternalChainingEntry<K, V>*[]>(length) };

    // iterate over the old table and re-map to the new table
    size_t count { 0 };
    for (size_t i = 0; i < numBuckets; i++)
    {
        // grab the head of the current bucket
        ExternalChainingEntry<K, V>* current { table[i] };

        // iterate over the list in the current bucket
        while (current)
        {
            // grab the next value before reassignment
            ExternalChainingEntry<K, V>* next = current->getNext();

            // calculate the new index depending on the new table's length
            size_t index = std::hash<K>{}(current->getKey());

            // add to the head of the new bucket
            current->setNext(newTable[index]);
            newTable[index] = current;

            current = next;

            count++;
            if (count == size) break;
        }

        if (count == size) break;
    }

    // update class attributes
    table = std::move(newTable);
    numBuckets = length;
}

template<typename K, typename V>
std::optional<V> ExternalChaining<K, V>::put(K key, V value)
{
    // check if key is null
    if constexpr (std::is_pointer<K>::value)
    {
        if (!key) throw std::invalid_argument("cannot put because key is nullptr (pointer types)");
    }

    // check if value is null
    if constexpr (std::is_pointer<K>::value)
    {
        if (!value) throw std::invalid_argument("cannot put because value is nullptr (pointer types)");
    }

    // check if we need to resize
    if ((static_cast<double>(size + 1) / numBuckets) > MAX_LOAD_FACTOR)
        resizeBackingTable(2 * numBuckets + 1);

    // calculate index to insert at
    size_t index { std::hash<K>{}(key) % numBuckets };

    // check if we already have a list that we need to append to
    if (!table[index]) table[index] = new ExternalChainingEntry<K, V>(key, value);
    else
    {
        // grab the head of the list
        ExternalChainingEntry<K, V>* current = table[index];

        // iterate over all the elements of the list
        while (current)
        {
            // check if we have duplicate key and update the value
            if (current->getKey() == key)
            {
                std::optional<V> removedValue = current->getValue();
                current->setValue(value);
                return removedValue;
            }
            current = current->getNext();
        }

        // if we didn't return (duplicate key) then we should add at the head
        ExternalChainingEntry<K, V>* newEntry = new ExternalChainingEntry<K, V>(key, value, table[index]);
        table[index] = newEntry;
    }
    size++;
    return std::nullopt;
}

template<typename K, typename V>
V ExternalChaining<K, V>::remove(K key)
{
    if constexpr (std::is_pointer<K>::value)
    {
        if (!key) throw std::invalid_argument("Cannot remove nullptr key (pointer types)");
    }

    if (size == 0) throw std::out_of_range("Cannot remove from empty map");

    // calculate the index that this key would exist in
    size_t index { std::hash<K>{}(key) };
    
    if (table[index]) throw std::out_of_range("Cannot remove because key that was not found");

    ExternalChainingEntry<K, V>* current { table[index] };
    ExternalChainingEntry<K, V>* prev { nullptr };

    // iterate over the current bucket and try to find the same key
    while (current)
    {
        if (current->getKey() == key)
        {
            if (!prev) table[index] = current->getNext();
            else
            {
                prev->setNext(current->getNext());
                current->setNext(nullptr);
            }

            V removed = current->getValue();

            delete current;
            size--;
            return removed;
        }

        prev = current;
        current = current->getNext();
    }

    throw new std::out_of_range("Cannot remove because key was not found");
}

template<typename K, typename V>
V ExternalChaining<K, V>::get(K key) const
{

}

template<typename K, typename V>
bool ExternalChaining<K, V>::containsKey(K key) const
{

}

template<typename K, typename V>
std::unordered_set<K> ExternalChaining<K, V>::keySet() const
{

}

template<typename K, typename V>
std::vector<V> ExternalChaining<K, V>::values() const
{

}
