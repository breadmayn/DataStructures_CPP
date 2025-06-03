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
    size_t capacity;

public:
    static constexpr size_t INITIAL_CAPACITY { 9 };

    // default constructor
    ArrayQueue()
        : backingArray(std::make_unique<std::optional<T>[]>(INITIAL_CAPACITY))
        , front(0)
        , size(0)
        , capacity(INITIAL_CAPACITY)
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

    /**
     * Returns the capacity of the queue
     * [NOTE]: technically this is the size of the backing array
     * 
     * @return the capacity of the queue
     */
    size_t getCapacity() const { return capacity; }
};

template<typename T>
void ArrayQueue<T>::enqueue(T data)
{
    // check if data is null
    if constexpr (std::is_pointer<T>::value)
    {
        if (!data) throw std::invalid_argument("cannot enqueue nullptr (pointer types)");
    }

    // check if we need to resize first
    if (size == capacity)
    {
        auto newArr = std::make_unique<std::optional<T>[]>(capacity * 2);
        for (size_t i = 0; i < size; i++)
            newArr[i] = std::move(backingArray[(front + i) % capacity]);

        backingArray = std::move(newArr); // unique pointer will clean itself up

        // update member atrributes from the resizing
        front = 0;
        capacity *= 2;
    }

    // add data to the backingArray
    backingArray[(front + size) % capacity] = data;
    size++;
}

template<typename T>
T ArrayQueue<T>::dequeue()
{
    // check if queue is empty
    if (size == 0) throw std::out_of_range("cannot dequeue because queue is empty");

    // grab and erase the element at the front
    T ret = backingArray[front].value();
    backingArray[front] = std::nullopt;

    // update member attributes from the removal
    front = (front + 1) % capacity;
    size--;

    return ret;
}

template<typename T>
T ArrayQueue<T>::peek() const
{
    // check if queue is empty
    if (size == 0) throw std::out_of_range("cannot peek because queue is empty");

    return backingArray[front].value();
}
