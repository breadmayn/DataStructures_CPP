#pragma once

#include "LinkedNode.hpp"

/**
 * Your implementation of an ArrayQueue
 * 
 * @author Brandon Mach
 * @version 1.0
 */
template<typename T>
class LinkedQueue {
private:
    using Node = LinkedNode<T>;

    Node* head;
    Node* tail;
    size_t size;

public: 
    // default constructor
    LinkedQueue()
        : head(nullptr)
        , tail(nullptr)
        , size(0)
    { }

    /**
     * Adds the data to the back of the queue
     * 
     * Must be O(1)
     * 
     * @param data the data to add to the back of the queue
     * @throws std::invalid_argument if data is null
     */
    void enqueue(T data);

    /**
     * Removes and returns the data from the front of the queue
     * 
     * Must be O(1)
     * 
     * @return the data formerly located at the front of the queue
     * @throws std::out_of_range if the queue is empty
     */
    T dequeue();

    /**
     * Returns the data from the front of the queue without removing it
     * 
     * Must be O(1)
     * 
     * @return the data located at the front of the queue
     * @throws std::out_of_range if the queue is empty
     */
    T peek() const;

    /**
     * Returns the head node of the queue
     * 
     * @return the node at the head of the queue
     */
    Node* getHead() const { return head; }

    /**
     * Returns the tail node of the queue
     * 
     * @return the node at the tail of the queue
     */
    Node* getTail() const { return tail; }

    /**
     * Returns the size of the queue
     * 
     * @return the size of the queue
     */
    size_t getSize() const { return size; }
};

template<typename T>
void LinkedQueue<T>::enqueue(T data)
{
    
}

template<typename T>
T LinkedQueue<T>::dequeue()
{

}

template<typename T>
T LinkedQueue<T>::peek() const
{

}
