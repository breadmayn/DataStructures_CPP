#pragma once

#include <optional>

/**
 * Your implementation of an ArrayQueue
 * 
 * @author Brandon Mach
 * @version 1.0
 */
template<typename T>
class ArrayQueue {
private:
    using BackingArray = std::unique_ptr<std::optional<T>[]>;

    BackingArray backingArray;
    size_t front;
    size_t size;

public:
    static constexpr size_t INITIAL_CAPACITY { 9 };

    // default constructor
    ArrayQueue()
        : backingArray(std::make_unique<std::optional<T>[]>(INITIAL_CAPACITY))
        , front(0)
        , size(0)
    { }

    /**
     * Adds the data to the back of the queue
     * 
     * If sufficient space is not available in the backing array, resize it to
     * double the current length. When resizing, copy elements to the 
     * beginning of the new array and reset front to 0.
     * 
     * Must be amortized O(1)
     * 
     * @param data the data to add to the back of the queue
     * @throws std::invalid_argument if data is nullptr (pointer types)
     */
    void enqueue(T data);

    /**
     * Removes and returns the data from the front of the queue
     * 
     * Do not shrink the backing array
     * 
     * Replace any spots that you dequeue from with nullptr
     * 
     * If the queue becomes empty as a result of this call, do not reset
     * front to 0
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
     * Returns the backing array of the queue
     * 
     * @return the backing array of the queue
     */
    const BackingArray& getBackingArray() const { return backingArray; }

    /**
     * Returns the size of the queue
     * 
     * @return the size of the queue
     */
    size_t getSize() const { return size; }
};

template<typename T>
void ArrayQueue<T>::enqueue(T data)
{

}

template<typename T>
T ArrayQueue<T>::dequeue()
{

}

template<typename T>
T ArrayQueue<T>::peek() const
{

}
