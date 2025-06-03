#pragma once

#include <optional>

/**
 * Your implementation of an ArrayStack
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
    size_t capacity;

public:
    static constexpr size_t INITIAL_CAPACITY { 9 };

    // default constructor
    ArrayStack()
        : backingArray(std::make_unique<std::optional<T>[]>(INITIAL_CAPACITY))
        , size(0)
        , capacity(INITIAL_CAPACITY)
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
    // check if data is null
    if constexpr (std::is_pointer<T>::value)
    {
        if (!data) throw std::invalid_argument("cannot push nullptr data (pointer types)");
    }

    // check if we need to resize first
    if (size == capacity)
    {
        auto newArr = std::make_unique<std::optional<T>[]>(capacity * 2);
        for (size_t i = 0; i < size; i++)
            newArr[i] = std::move(backingArray[i]);

        backingArray = std::move(newArr); // unique pointer will clean up itself

        // update member attributes from the resizing
        capacity *= 2;
    }

    // add to the stack
    backingArray[size] = data;
    size++;
}

template<typename T>
T ArrayStack<T>::pop()
{
    // check for empty list
    if (size == 0) throw std::out_of_range("cannot pop if stack is empty");

    // grab the element to remove
    T ret = backingArray[size - 1].value();
    backingArray[size - 1] = std::nullopt;

    // update member attributes from the removal
    size--;

    return ret;
}

template<typename T>
T ArrayStack<T>::peek() const
{
    // check for empty list
    if (size == 0) throw std::out_of_range("cannot peek if stack is empty");

    return backingArray[size - 1].value();
}