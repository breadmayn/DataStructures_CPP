#pragma once

#include <string>

/**
 * Node class used for implementing the BST.
 *
 * DO NOT MODIFY THIS FILE!!
 */
template<typename T>
class BSTNode {
private:
    using Node = BSTNode<T>;

    T data;
    BSTNode<T>* left;
    BSTNode<T>* right;

public:
    // constructor
    BSTNode(T data)
        : data(data)
        , left(nullptr)
        , right(nullptr)
    { }

    /*
        getter methods
    */
    T getData() const { return data; }
    Node* getLeft() const { return left; }
    Node* getRight() const { return right; }

    /*
        setter methods
    */
   void setData(T data) { this->data = data; }
   void setLeft(Node* node) { this->left = node; }
   void setRight(Node* node) { this->right = node; }

   // misc
   std::string toString() const { return "Node containing: " + std::to_string(data); }
};