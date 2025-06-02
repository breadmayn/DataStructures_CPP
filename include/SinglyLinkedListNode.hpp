#pragma once
/**
 * Generic node class for SinglyLinkedListNode
 * 
 * @author Brandon Mach
 * @version 1.0
 */
template<typename T>
class SinglyLinkedListNode {
public:
    T data; // node data
    SinglyLinkedListNode* next; // the next node in the list or nullptr

    // basic constructor with only data -> uses constructor chaining
    SinglyLinkedListNode(T data)
        : SinglyLinkedListNode(data, nullptr)
    { }

    // most complex constructor which is the base of constructor for chaining
    SinglyLinkedListNode(T data, SinglyLinkedListNode* next)
        : data(data)
        , next(next)
    { }
};