#pragma once

#include <string>
#include <format>
#include <ostream>

/**
 * Node class used for implementing your linked data structures
 * 
 * DO NOT MODIFY THIS FILE!!
 */
template<typename T>
class LinkedNode {
private:
    T data;
    LinkedNode<T>* next;

public:
    LinkedNode(T data)
        : LinkedNode(data, nullptr)
    { }

    LinkedNode(T data, LinkedNode<T>* next)
        : data(data)
        , next(next)
    { }

    T getData() const { return data; }

    LinkedNode<T>* getNext() const { return next; }

    void setNext(LinkedNode<T>* next) { this->next = next; }

    std::string toString() const
    {
        std::ostringstream oss;
        oss << "Node containing " << data << '\n';

        return oss.str();
    }
};