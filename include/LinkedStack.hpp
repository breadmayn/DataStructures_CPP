#pragma once

#include "LinkedNode.hpp"

/**
 * Your implementation of an ArrayQueue
 * 
 * @author Brandon Mach
 * @version 1.0
 */
template<typename T>
class LinkedStack {
private:
    using Node = LinkedNode<T>;

    Node* head;
    size_t size;

public:
    // default constructor
    LinkedStack()
        : head(nullptr)
        , size(0)
    { }

    /**
     * Adds the data to the top of the stack.
     *
     * Must be O(1).
     *
     * @param data the data to add to the top of the stack
     * @throws std::invalid_argument if data is null
     */
    void push(T data);

    /**
     * Removes and returns the data from the top of the stack.
     *
     * Must be O(1).
     *
     * @return the data formerly located at the top of the stack
     * @throws std::out_of_range if the stack is empty
     */
    T pop();

    /**
     * Returns the data from the top of the stack without removing it.
     *
     * Must be O(1).
     *
     * @return the data from the top of the stack
     * @throws std::out_of_range if the stack is empty
     */
    T peek() const;

    /**
     * Returns the head node of the stack.
     *
     * @return the node at the head of the stack
     */
    Node* getHead() const { return head; }

    /**
     * Returns the size of the stack.
     *
     * @return the size of the stack
     */
    size_t getSize() const { return size; }
};

template<typename T>
void LinkedStack<T>::push(T data)
{

}

template<typename T>
T LinkedStack<T>::pop()
{

}

template<typename T>
T LinkedStack<T>::peek() const
{

}
