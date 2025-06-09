#pragma once

#include <string>

/**
 * Map entry class used for implementing the ExternalChainingHshMap.
 *
 * DO NOT MODIFY THIS FILE!!
 *
 */
template<typename K, typename V>
class ExternalChainingEntry {
private:
    K key;
    V value;
    ExternalChainingEntry<K, V>* next;

public:
    ExternalChainingEntry(K key, V value)
        : ExternalChainingEntry(key, value, nullptr)
    { }

    ExternalChainingEntry(K key, V value, ExternalChainingEntry<K, V>* next)
        : key(key)
        , value(value)
        , next(next)
    { }

    

    /*
        getter methods
    */
    K getKey() const { return key; }
    V getValue() const { return value; }
    ExternalChainingEntry<K, V>* getNext() const { return next; }

    /*
        setter methods
    */
    void setKey(K key) { this->key = key; }
    void setValue(V value) { this->value = value; }
    void setNext(ExternalChainingEntry<K, V>* next) { this->next = next; }

    // misc
    std::string toString() const
    {
        std::string keyStr, valueStr;

        if constexpr (std::is_pointer<K>::value)
        {
            if (key == nullptr) keyStr = "nullptr";
            else keyStr = "[pointer] " + std::to_string(*key);
        }
        else keyStr = std::to_string(key);

        if constexpr (std::is_pointer<V>::value)
        {
            if (value == nullptr) valueStr = "nullptr";
            else valueStr = "[pointer] " + std::to_string(*value);
        }
        else valueStr = std::to_string(value);

        return '(' + keyStr + ", " + valueStr + ")\n";
    }

    bool operator==(const ExternalChainingEntry<K, V>& other) const
    {
        return (key == other.key) && (value == other.value);
    }
};