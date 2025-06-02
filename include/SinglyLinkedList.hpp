#pragma once

#include "SinglyLinkedListNode.hpp"

#include <vector>
#include <exception>

/**
 * Your implementation of a non-circular SinglyLinkedList with a tail pointer.
 * 
 * @author Brandon Mach
 * @version 1.0
 */
template<typename T>
class SinglyLinkedList {
private:
    // making type alias for the SinglyLinkedListNode
    using Node = SinglyLinkedListNode<T>; 
    
    /*
        SinglyLinkedList member attributes
    */
    Node* head;
    Node* tail;
    size_t size;

public:
    // default constructor for the SinglyLinkedList
    SinglyLinkedList()
        : head(nullptr)
        , tail(nullptr)
        , size(static_cast<size_t>(0))
    { }

    // constructor that will take in an array and will create the SLL to match the array
    SinglyLinkedList(std::vector<T> list)
    {
        Node* prev = nullptr;

        size_t listSize = list.size();

        for (size_t i = 0; i < listSize; i++)
        {
            Node* newNode(list[i]);

            if (i == 0)
            {
                head = newNode;
                prev = newNode;
            }
            else if (i == listSize - 1) tail = newNode;
            else
            {
                prev->next = newNode;
                prev = newNode;
            }
        }

        size = listSize;
    }

    // default destructor
    ~SinglyLinkedList()
    {
        clear();
    }

    /**
     * Adds the element to the specified index
     * This will increase the size of the list by 1
     * 
     * Must be O(1) for head and tail and O(n) for all other cases
     * 
     * @param index the index to add the next element
     * @param data generic type data to be added at the given index
     * @throws std::out_of_range if index < 0 or index > size
     * @throws std::invalid_argument if data is a nullptr (for pointer types)
     */
    void addAtIndex(int index, T data);

    /**
     * Adds the element to the front of the list
     * This will increase the size of the list by 1
     * 
     * Must be O(1)
     * 
     * @param data generic type data to be added at the head of the list
     * @throws std::invalid_argument if the data is a nullptr (for pointer types)
     */
    void addToFront(T data);

    /**
     * Adds the element to the back of the list
     * This will increase the size of the list by 1
     * 
     * Must be O(1)
     * 
     * @param data generic type data to be added at the head of the list
     * @throws std::invalid_argument if the data is a nullptr (for pointer types)
     */
    void addToBack(T data);

    /**
     * Removes and returns the element at the specified index
     * 
     * Must be O(1) for head and tail and O(n) for all others
     * 
     * @param index the index of the element to remove
     * @return the data that was removed at the specified index
     * @throws std::out_of_range if index < 0 or index >= size
     */
    T removeAtIndex(int index);

    /**
     * Removes and returns the first element of the list
     * 
     * Must be O(n)
     * 
     * @return the data formerly located at the front of the list
     * @throws std::out_of_range if the list is empty
     */
    T removeFromFront();

    /**
     * Removes and returns the last element of the list
     * 
     * Must be O(n)
     * 
     * @return the data formerly located at the back of the list
     * @throws std::out_of_range if the list is empty
     */
    T removeFromBack();

    /**
     * Returns the element at the specified index.
     *
     * Must be O(1) for indices for head and tail and O(n) for all other cases.
     *
     * @param index the index of the element to get
     * @return the data stored at the index in the list
     * @throws std::out_of_range if index < 0 or index >= size
     */
    T get(int index);

    /**
     * Returns whether or not the list is empty
     * 
     * Must be O(1)
     * 
     * @return true if empty, false otherwise
     */
    bool isEmpty() const;

    /**
     * Clears the list
     * Clears all data and resets the size
     * 
     * Must be O(n) - because of garbage collection
     */
    void clear();

    /**
     * Removes and returns the last copy of the given data from the list
     * 
     * Do not return the same data that was passed in
     * Return the data that was stored in the list
     * 
     * Must be O(n)
     * 
     * @param data the data to be removed from the list
     * @return the data that was removed
     * @throws std::invalid_argument if the data is nullptr (for pointer types)
     * @throws std::invalid_argument if the data is not found in the list
     */
    T removeLastOccurrence(T data);

    /**
     * Returns an vector representation of the linked list
     * 
     * Must be O(n) for all cases
     * 
     * @return the array of length SinglyLinkedList::size holding all the data
     * in the same order was the list
     */
    std::vector<T> toArray() const;

    /**
     * Returns the head node of the list
     * 
     * @return the node at the head of the list
     */
    Node* getHead() const { return head; }

    /**
     * Returns the tail node of the list
     * 
     * @return the node at the tail of the list
     */
    Node* getTail() const { return tail; }

    /**
     * Returns the size of the list
     * 
     * @return the size of the list
     */
    size_t getSize() const { return size; }
};

template<typename T>
void SinglyLinkedList<T>::addAtIndex(int index, T data)
{
    // checking if index arg is out of bounds
    if (index < 0 || index > size)
        throw std::out_of_range("addAtIndex(): out of bounds");

    // checking if data arg is out of bounds
    if constexpr (std::is_pointer<T>::value)
    {
        if (data == nullptr)
            throw std::invalid_argument("addAtIndex(): data is null");
    }

    if (index == 0) addToFront(data);
    else if (index == size) addToBack(data);
    else
    {
        Node* newNode = new Node(data);

        Node* current { head };
        for (size_t i = 0; i < index - 1; i++) current = current->next;

        newNode->next = current->next;
        current->next = newNode;

        size++;
    }
}

template<typename T>
void SinglyLinkedList<T>::addToFront(T data)
{
    if constexpr (std::is_pointer<T>::value)
    {
        if (data == nullptr)
            throw std::invalid_argument("addToFront(): data is null");
    }

    Node* newNode = new Node(data);

    if (size > 0) newNode->next = head;
    else if (size == 0) tail = newNode; // dont forget this
    head = newNode;

    size++;
}

template<typename T>
void SinglyLinkedList<T>::addToBack(T data)
{
    if constexpr (std::is_pointer<T>::value)
    {
        if (data == nullptr)
            throw std::invalid_argument("addToBack(): data is null");
    }

    Node* newNode = new Node(data);

    if (size > 0) tail->next = newNode;
    else if (size == 0) head = newNode; // dont forget this
    tail = newNode;

    size++;
}

template<typename T>
T SinglyLinkedList<T>::removeAtIndex(int index)
{
    if (index < 0 || index >= size)
        throw std::out_of_range("removeAtIndex(): out of bounds");

    if (index == 0) removeFromFront();
    else if (index == size - 1) removeFromBack();
    else
    {
        Node* current { head };
        for (size_t i = 0; i < index - 1; i++) current = current->next;

        Node* removed = current->next;
        T ret = removed->data;

        current->next = removed->next;
        size--;

        delete removed; // garbage collection
        return ret;
    }
}

template<typename T>
T SinglyLinkedList<T>::removeFromFront()
{
    if (size == 0)
        throw std::out_of_range("removeFromFront(): the list is empty");

    Node* removed { head };
    T ret = removed->data;

    head = head->next;
    size--;

    delete removed; // garbage collection
    return ret;
}

template<typename T>
T SinglyLinkedList<T>::removeFromBack()
{
    if (size == 0)
        throw std::out_of_range("removeFromBack(): the list is empty");

    Node* removed { tail };
    T ret = removed->data;

    Node* current { head };
    for (size_t i = 0; i < size - 1; i++) current = current->next;

    tail = current;
    size--;

    delete removed; // garbage collection
    return ret;
}

template<typename T>
T SinglyLinkedList<T>::get(int index)
{
    if (index < 0 || index >= size)
        throw std::out_of_range("get(): out of bounds");
    
    Node* current { head };
    for (size_t i = 0; i < index; i++) current = current->next;

    return current->data;
}

template<typename T>
bool SinglyLinkedList<T>::isEmpty() const
{
    return size == 0;
}

template<typename T>
void SinglyLinkedList<T>::clear()
{
    Node* current { head };
    while (current)
    {
        Node* next = current->next;

        delete current;
        current = next;
    }

    head = nullptr;
    tail = nullptr;
    size = 0;
}

template<typename T>
T SinglyLinkedList<T>::removeLastOccurrence(T data)
{
    if constexpr (std::is_pointer<T>::value)
    {
        if (data == nullptr)
            throw std::invalid_argument("removeLastOccurrence(): data is null");
    }

    if (size == 0)
        throw std::invalid_argument("removeLastOccurrence(): the list is empty");

    int removeInd { -1 };

    int i = 0;
    Node* current { head };
    while (current)
    {
        if (current->data == data) removeInd = i;

        current = current->next;
        i++;
    }

    if (removeInd == -1)
        throw std::invalid_argument("removeLastOccurrence(): data not found in list");

    return removeAtIndex(removeInd);
}

template<typename T>
std::vector<T> SinglyLinkedList<T>::toArray() const
{
    return {};
}
