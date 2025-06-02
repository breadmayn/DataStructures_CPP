#pragma once

#include <optional>

/**
 * Your implementation of an ArrayQueue
 * 
 * @author Brandon Mach
 * @version 1.0
 */
template<typename T>
class ArrayStack {
private:
    using BackingArray = std::unique_ptr<std::optional<T>[]>;

    BackingArray backingArray;
    size_t size;

public:
    static constexpr size_t INITIAL_CAPACITY { 9 };

    // default constructor
    ArrayStack()
        : backingArray(std::make_unique<std::optional<T>[]>(INITIAL_CAPACITY))
        , size(0)
    { }

    /**
     * Adds the data to the back of the stack
     * 
     * If sufficient space is not available in the backing array, resize it to
     * double the current length
     * 
     * Must be amortized O(1)
     * 
     * @param data the data to add to the back of the stack
     * @throws std::invalid_argument if data is nullptr (pointer types)
     */
    void push(T data);

    /**
     * Removes and returns the data from the top of the stack
     * 
     * Do not shrink the backing array
     * 
     * Replace any spots that you pop from with null
     * 
     * Must be O(1)
     * 
     * @return the data formerly located at the top of the stack
     * @throws std::out_of_range if the stack is empty
     */
    T pop();

    /**
     * Returns the data from the top of the stack without removing it
     * 
     * Must be O(1)
     * 
     * @return the data from the top of the stack
     * @throws std::out_of_range if the stack is empty
     */
    T peek() const;

    /**
     * Returns the backing array of the stack
     * 
     * @return the backing array of the stack
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
void ArrayStack<T>::push(T data)
{

}

template<typename T>
T ArrayStack<T>::pop()
{
    
}

template<typename T>
T ArrayStack<T>::peek() const
{
    
}