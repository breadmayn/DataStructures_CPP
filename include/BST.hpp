#pragma once

#include <vector>

#include "BSTNode.hpp"

/**
 * Your implementation of a BST.
 *
 * @author Brandon Mach
 * @version 1.0
 */
template<typename T>
class BST {
private:
    using Node = BSTNode<T>;

    Node* root;
    size_t size;

    /*
        private helper methods
    */

   /**
     * This is a recursive method that calls itself in order to help us find where we should add the new data.
     * @param current Current will be the node that the recursive method is currently getting the data and comparing.
     * @param data Data is the information that we want to add to the BST.
     * @return We will be returning another node which will do nothing in the wrapper method, but will return the
     * correct node that we will set left or right regardless if we are adding or just going through the BST.
     */
    Node* recursiveAdd(Node* current, T data);

    /**
     * This is the recursive method that we will call in remove() that will allow us to traverse through the BST
     * and find and remove the data.
     * @param current Current is the current node that we are observing and comparing the data to the data passed in.
     * @param data Data is the information that was given to the remove method that we will compare node data to.
     * @param dummy Dummy is a Node Object that we will create to store the data that we will remove.
     * @return We will return here a node that we will set the previous current's child as.
     */
    Node* recursiveRemove(Node* current, T data, Node* dummy);

    /**
     * Recrusive helper lambda that will handle all of the traversals
     */
    template<typename Func>
    void traverse(Node* current, Func&& fn) const
    {
        if (!current) return;

        traverse(current->getLeft(), fn);
        fn(current);
        traverse(current->getRight(), fn);
    }

public:
    // default constructor
    BST()
        : root(nullptr)
        , size(0)
    { }

    // list constructor
    BST(std::vector<T> list)
    {
        
    }

    /**
     * Adds the data to the tree.
     *
     * This must be done recursively.
     *
     * The data becomes a leaf in the tree.
     *
     * Traverse the tree to find the appropriate location. If the data is
     * already in the tree, then nothing should be done (the duplicate
     * shouldn't get added, and size should not be incremented).
     *
     * Must be O(log n) for best and average cases and O(n) for worst case.
     *
     * @param data the data to add
     * @throws std::invalid_argument if data is nullptr (pointer types)
     */
    void add(T data);

    /**
     * Removes and returns the data from the tree matching the given parameter.
     *
     * This must be done recursively.
     *
     * There are 3 cases to consider:
     * 1: The node containing the data is a leaf (no children). In this case,
     * simply remove it.
     * 2: The node containing the data has one child. In this case, simply
     * replace it with its child.
     * 3: The node containing the data has 2 children. Use the successor to
     * replace the data. You MUST use recursion to find and remove the
     * successor (you will likely need an additional helper method to
     * handle this case efficiently).
     *
     * Do not return the same data that was passed in. Return the data that
     * was stored in the tree.
     *
     * Hint: Should you use value equality or reference equality?
     *
     * Must be O(log n) for best and average cases and O(n) for worst case.
     *
     * @param data the data to remove
     * @return the data that was removed
     * @throws std::invalid_argument if data is nullptr (pointer types)
     * @throws std::out_of_range if the data does not exist in the BST
     */
    T remove(T data);

    /**
     * Returns the data from the tree matching the given parameter.
     *
     * This must be done recursively.
     *
     * Do not return the same data that was passed in. Return the data that
     * was stored in the tree.
     *
     * Hint: Should you use value equality or reference equality?
     *
     * Must be O(log n) for best and average cases and O(n) for worst case.
     *
     * @param data the data to search for
     * @return the data in the tree equal to the parameter
     * @throws std::invalid_argument if data is nullptr (pointer types)
     * @throws std::out_of_range if the data does not exist in the BST
     */
    T get(T data) const;

    /**
     * Returns whether or not data matching the given parameter is contained
     * within the tree.
     *
     * This must be done recursively.
     *
     * Hint: Should you use value equality or reference equality?
     *
     * Must be O(log n) for best and average cases and O(n) for worst case.
     *
     * @param data the data to search for
     * @return true if the parameter is contained within the tree, false
     * otherwise
     * @throws std::invalid_argument if data is nullptr (pointer types)
     */
    bool contains(T data) const;

    /**
     * Generate a pre-order traversal of the tree.
     *
     * This must be done recursively.
     *
     * Must be O(n).
     *
     * @return the preorder traversal of the tree
     */
    std::vector<T> preorder() const;

    /**
     * Generate an in-order traversal of the tree.
     *
     * This must be done recursively.
     *
     * Must be O(n).
     *
     * @return the inorder traversal of the tree
     */
    std::vector<T> inorder() const;

    /**
     * Generate a post-order traversal of the tree.
     *
     * This must be done recursively.
     *
     * Must be O(n).
     *
     * @return the postorder traversal of the tree
     */
    std::vector<T> postorder() const;

    /**
     * Generate a level-order traversal of the tree.
     *
     * This does not need to be done recursively.
     *
     * Hint: You will need to use a queue of nodes. Think about what initial
     * node you should add to the queue and what loop / loop conditions you
     * should use.
     *
     * Must be O(n).
     *
     * @return the level order traversal of the tree
     */
    std::vector<T> levelorder() const;

    /**
     * Returns the height of the root of the tree.
     *
     * This must be done recursively.
     *
     * A node's height is defined as max(left.height, right.height) + 1. A
     * leaf node has a height of 0 and a null child has a height of -1.
     *
     * Must be O(n).
     *
     * @return the height of the root of the tree, -1 if the tree is empty
     */
    size_t height() const;

    /**
     * Clears the tree.
     *
     * Clears all data and resets the size.
     *
     * Must be O(n). for garbage collection
     */
    void clear();

    /**
     * Removes all elements strictly greater than the passed in data.
     *
     * This must be done recursively.
     *
     * In most cases, this method will not need to traverse the entire tree to
     * function properly, so you should only traverse the branches of the tree
     * necessary to get the data and only do so once. Failure to do so will
     * result in an efficiency penalty.
     *
     *
     * EXAMPLE: Given the BST below composed of Integers:
     *
     *                50
     *              /    \
     *            25      75
     *           /  \
     *          12   37
     *         /  \    \
     *        10  15    40
     *           /
     *          13
     *
     * pruneGreaterThan(27) should remove 37, 40, 50, 75. Below is the resulting BST
     *             25
     *            /
     *          12
     *         /  \
     *        10  15
     *           /
     *          13
     *
     * Should have a running time of O(log(n)) for balanced tree. O(n) for a degenerated tree.
     *
     * @throws std::invalid_argument if data is nullptr (pointer types)
     * @param data the threshold data. Elements greater than data should be removed
     * @param <T> the generic typing of the data in the BST
     * @return the root of the tree with all elements greater than data removed
     */
    Node* pruneGreaterThan(T data);

    /**
     * Returns the root of the tree.
     *
     * For grading purposes only. You shouldn't need to use this method since
     * you have direct access to the variable.
     *
     * @return the root of the tree
     */
    Node* getRoot() const { return root; }

    /**
     * Returns the size of the tree.
     *
     * For grading purposes only. You shouldn't need to use this method since
     * you have direct access to the variable.
     *
     * @return the size of the tree
     */
    size_t getSize() const { return size; }
};

template<typename T>
BSTNode<T>* BST<T>::recursiveAdd(BSTNode<T>* current, T data)
{

}

template<typename T>
BSTNode<T>* BST<T>::recursiveRemove(BSTNode<T>* current, T data, BSTNode<T>* dummy)
{

}

template<typename T>
void BST<T>::add(T data)
{

}

template<typename T>
T BST<T>::remove(T data)
{

}

template<typename T>
T BST<T>::get(T data) const
{

}

template<typename T>
bool BST<T>::contains(T data) const
{

}

template<typename T>
std::vector<T> BST<T>::preorder() const
{

}

template<typename T>
std::vector<T> BST<T>::inorder() const
{

}
template<typename T>
std::vector<T> BST<T>::postorder() const
{

}

template<typename T>
std::vector<T> BST<T>::levelorder() const
{

}

template<typename T>
size_t BST<T>::height() const
{

}

template<typename T>
void BST<T>::clear()
{

}

template<typename T>
BSTNode<T>* BST<T>::pruneGreaterThan(T data)
{

}

