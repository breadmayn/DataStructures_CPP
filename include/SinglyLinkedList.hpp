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
     * Must be O(1) for head and O(n) for all others
     * 
     * @param index the index of the element to remove
     * @return the data that was removed at the specified index
     * @throws std::out_of_range if index < 0 or index >= size
     */
    T removeAtIndex(int index);

    /**
     * Removes and returns the first element of the list
     * 
     * Must be O(1)
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
    T get(int index) const;

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
    // checking index bounds
    if (index < 0 || index > size)
        throw std::out_of_range("addAtIndex(): cannot add at out of bounds index");

    // checking for null data
    if constexpr (std::is_pointer<T>::value)
    {
        if (data == nullptr)
            throw std::invalid_argument("addAtIndex(): cannot add nullptr data");
    }

    if (index == 0) return addToFront(data);
    else if (index == size) return addToBack(data);

    // handle adding in the middle of the list
    Node* newNode = new Node(data);
    
    // iterate until we have the node before index
    Node* current = head;
    for (size_t i = 0; i < index - 1; i++) current = current->next;

    // insert newNode
    newNode->next = current->next;
    current->next = newNode;

    size++;
}

template<typename T>
void SinglyLinkedList<T>::addToFront(T data)
{
    // check for null data
    if constexpr (std::is_pointer<T>::value)
    {
        if (data == nullptr)
            throw std::invalid_argument("addToFront(): cannot add nullptr data");
    }

    // create new node with the data given
    Node* newNode = new Node(data);

    if (size == 0) tail = newNode;
    else newNode->next = head;

    head = newNode;
    size++;
}

template<typename T>
void SinglyLinkedList<T>::addToBack(T data)
{
    // check for null data
    if constexpr (std::is_pointer<T>::value)
    {
        if (data == nullptr)
            throw std::invalid_argument("addToBack(): cannot add nullptr data");
    }

    // create new node with the data given
    Node* newNode = new Node(data);

    if (size == 0) head = newNode;
    else tail->next = newNode;

    tail = newNode;
    size++;
}

template<typename T>
T SinglyLinkedList<T>::removeAtIndex(int index)
{
    // check for index out of bounds
    if (index < 0 || index >= size)
        throw std::out_of_range("removeAtIndex(): cannot remove because index is out of bounds");

    if (index == 0) return removeFromFront();
    else if (index == size - 1) return removeFromBack();

    // iterate until we have the node before index
    Node* current = head;
    for (size_t i = 0; i < index - 1; i++) current = current->next;

    // capture the node to remove
    Node* removed = current->next;
    T ret = removed->data;

    // remove from list
    current->next = removed->next;

    delete removed; // garbage collection
    size--;
    return ret;
}

template<typename T>
T SinglyLinkedList<T>::removeFromFront()
{
    // check for empty list
    if (size == 0)
        throw std::out_of_range("removeFromFront(): cannot remove because list is empty");

    // grab node at the head
    Node* removed = head;
    T ret = removed->data;

    if (size == 1)
    {
        head = nullptr;
        tail = nullptr;
    }
    else head = head->next;

    delete removed; // garbage collection
    size--;
    return ret;
}

template<typename T>
T SinglyLinkedList<T>::removeFromBack()
{
    // check for empty list
    if (size == 0)
        throw std::out_of_range("removeFromFront(): cannot remove because list is empty");

    // grab node at the tail
    Node* removed = tail;
    T ret = removed->data;

    if (size == 1)
    {
        head = nullptr;
        tail = nullptr;
    }
    else
    {
        Node* current = head;
        for (size_t i = 0; i < size - 2; i++) current = current->next;

        current->next = nullptr;
        tail = current;
    }

    delete removed; // garbage collection
    size--;
    return ret;
}

template<typename T>
T SinglyLinkedList<T>::get(int index) const
{
    // iterate to the node at index
    Node* current = head;
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
    Node* current = head;

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
    // check for null data
    if constexpr (std::is_pointer<T>::value)
    {
        if (data == nullptr)
            throw std::invalid_argument("removeLastOccurrence(): cannot remove nullptr data");
    }

    Node* removed { nullptr };
    Node* removedPrev { nullptr };

    Node* current = head;
    Node* prev { nullptr };

    while (current)
    {
        if (current->data == data)
        {
            removed = current;
            removedPrev = prev;
        }

        prev = current;
        current = current->next;
    }

    if (removed == nullptr)
        throw std::invalid_argument("removeLastOccurrence(): cannot remove data that does not exist in list");

    if (removed == head) return removeFromFront();

    T ret = removed->data;
    removedPrev->next = removed->next;

    delete removed;
    size--;
    return ret;
}

template<typename T>
std::vector<T> SinglyLinkedList<T>::toArray() const
{
    // return container
    std::vector<T> ret;

    // iterate over all nodes and add to container
    Node* current = head;
    while (current)
    {
        ret.push_back(current->data);
        current = current->next;
    }

    return ret;
}
