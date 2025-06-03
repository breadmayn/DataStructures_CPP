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

    // default destructor
    ~LinkedQueue()
    {
        Node* current = head;

        while (current)
        {
            Node* next = current->getNext();

            delete current;
            current = next;
        }

        head = nullptr;
        tail = nullptr;
    }

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
    // check if data is null
    if constexpr (std::is_pointer<T>::value)
    {
        if (!data) throw std::invalid_argument("cannot enqueue nullptr data (pointer types)");
    }

    Node* newNode = new Node(data);

    if (size == 0) head = newNode;
    else tail->setNext(newNode);

    tail = newNode;
    size++;
}

template<typename T>
T LinkedQueue<T>::dequeue()
{
    // check if queue is empty
    if (size == 0) throw std::out_of_range("cannot dequeue because queue is empty");

    // grab node to remove
    Node* removed = head;
    T ret = removed->getData();

    // remove node
    head = head->getNext();
    delete removed;
    size--;

    return ret;
}

template<typename T>
T LinkedQueue<T>::peek() const
{
    // check if queue is empty
    if (size == 0) throw std::out_of_range("cannot dequeue because queue is empty");

    return head->getData();
}
