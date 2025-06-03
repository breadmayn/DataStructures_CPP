#pragma once

#include <vector>

#include "AVLNode.hpp"

/**
 * Your implementation of an AVL Tree.
 *
 * @author Brandon Mach
 * @userid bmach3
 * @GTID 903561013
 * @version 1.0
 */
template<typename T>
class AVL {
private:
    using Node = AVLNode<T>;

    Node* root;
    size_t size;

    /*
        private helper methods
    */

    /**
     * This is the recursive add method that will allow us to recursively traverse through the AVL to either find
     * a duplicate of the data passed in or find null which will mean we will add the data.
     * @param current Current is the current node that we are observing.
     * @param data Data is the data of the node that we want to add to the AVL.
     * @return Returns a node that allow us to use pointer reinforcement for the recursion.
     */
    Node* recrusiveAdd(Node* current, T data);

    /**
     * This is the recursive remove method that will recursely traverse through and handle the
     * differet cases for the remove method.
     * @param data Data is the data value that we are trying to find and remove.
     * @param current Current is the current node that we are at in the AVL.
     * @param dummy Dummy is an empty node that we will use to store the value of the data that we are removing.
     * @return
     */
    Node* recursiveRemove(Node* current, T data, Node* dummy);

    /**
     * This is another helper method that will find the predecessor in the case that the data that we want to remove
     * has 2 children.
     * @param current Current is the current node that we are observing and checking if it has children.
     * @param dummy Dummy here is a different than the other dummy in the rRemove() that will store the data of the
     *              successor.
     * @return We will return the node that we will set the precious current's child with.
     */
    Node* findPredecessor(Node* current, Node* temp);

    /**
     * This is the wrapper rotate method which will take the balance factor and decide which rotation will occur
     * @param current Current is the node that we first find to have a balance factor that requires a rotation.
     * @return We will return the node because we are using pointer reinforcement to which will update the left
     * or right every recursive call even if nothing has changed.
     * Pointer reinforcement is where we have the idea of "node.left = recursiveCall(node.left)".
     */
    Node* rotate(Node* current);

    /**
     * This is the helper method that will perform a single left rotate on the passed in node.
     * @param current This is the node that we want to perform a single left rotate on.
     * @return We will return the new root of the subtree created from this rotate.
     */
    Node* leftRotate(Node* current);

    /**
     * This is the helper method that will perform a single right rotate on the passed in node.
     * @param current This is the node that we want to perform a single right rotate on.
     * @return We will return the new root of the subtree created from this rotate.
     */
    Node* rightRotate(Node* current);

    /**
     * <TODO> Recursive lambda function that takes in a function
     */

    /**
     * This is the update method that will take in a node and grab the height data from its children and calculate and
     * update the balance factor and height instance variable of the node.
     * @param current Current is the node that we want to update the balance factor and the height.
     */
    void update(Node* current);

public:
    // default constructor
    AVL()
        : root(nullptr)
        , size(0)
    { }

    /**
     * Initializes the AVL tree with the data in the Collection. The data
     * should be added in the same order it appears in the Collection.
     *
     * @throws IllegalArgumentException if data or any element in data is null
     * @param data the data to add to the tree
     */
    AVL(std::vector<T> data)
    {

    }

    /**
     * Adds the data to the AVL. Start by adding it as a leaf like in a regular
     * BST and then rotate the tree as needed.
     *
     * If the data is already in the tree, then nothing should be done (the
     * duplicate shouldn't get added, and size should not be incremented).
     *
     * Remember to recalculate heights and balance factors going up the tree,
     * rebalancing if necessary.
     *
     * @throws java.lang.IllegalArgumentException if the data is null
     * @param data the data to be added
     */
    void add(T data);

    /**
     * Removes the data from the tree. There are 3 cases to consider:
     *
     * 1: the data is a leaf. In this case, simply remove it.
     * 2: the data has one child. In this case, simply replace it with its
     * child.
     * 3: the data has 2 children. Use the predecessor to replace the data,
     * not the successor. As a reminder, rotations can occur after removing
     * the predecessor node.
     *
     * Remember to recalculate heights going up the tree, rebalancing if
     * necessary.
     *
     * @throws IllegalArgumentException if the data is null
     * @throws java.util.NoSuchElementException if the data is not found
     * @param data the data to remove from the tree.
     * @return the data removed from the tree. Do not return the same data
     * that was passed in.  Return the data that was stored in the tree.
     */
    T remove(T data);

    /**
     * Returns the data in the tree matching the parameter passed in (think
     * carefully: should you use value equality or reference equality?).
     *
     * @throws IllegalArgumentException if the data is null
     * @throws java.util.NoSuchElementException if the data is not found
     * @param data the data to search for in the tree.
     * @return the data in the tree equal to the parameter. Do not return the
     * same data that was passed in.  Return the data that was stored in the
     * tree.
     */
    T get(T data) const;

    /**
     * Returns whether or not data equivalent to the given parameter is
     * contained within the tree. The same type of equality should be used as
     * in the get method.
     *
     * @throws IllegalArgumentException if the data is null
     * @param data the data to search for in the tree.
     * @return whether or not the parameter is contained within the tree.
     */
    bool contains(T data) const;

    /**
     * Finds and retrieves the median data of the passed in AVL.
     *
     * This method will not need to traverse the entire tree to
     * function properly, so you should only traverse enough branches of the tree
     * necessary to find the median data and only do so once. Failure to do so will
     * result in an efficiency penalty.
     *
     * Ex:
     * Given the following AVL composed of Integers
     *              50
     *            /    \
     *         25      75
     *        /  \     / \
     *      13   37  70  80
     *    /  \    \      \
     *   12  15    40    85
     *
     * findMedian() should return 40
     *
     * @throws java.util.NoSuchElementException if the tree is empty or contains an even number of data
     * @return the median data of the AVL
     */
    T findMedian() const;

    /**
     * Clears the tree.
     */
    void clear();

    /**
     * Returns the height of the root of the tree.
     *
     * Since this is an AVL, this method does not need to traverse the tree
     * and should be O(1)
     *
     * @return the height of the root of the tree, -1 if the tree is empty
     */
    size_t getHeight() const { return size == 0 ? -1 : root->getHeight(); }

    /**
     * Returns the size of the AVL tree.
     *
     * For grading purposes only. You shouldn't need to use this method since
     * you have direct access to the variable.
     *
     * @return number of items in the AVL tree
     */
    size_t getSize() const { return size; }

    /**
     * Returns the root of the AVL tree.
     *
     * For grading purposes only. You shouldn't need to use this method since
     * you have direct access to the variable.
     *
     * @return the root of the AVL tree
     */
    Node* getRoot() const { return root; }

};

template<typename T>
AVLNode<T>* AVL<T>::recrusiveAdd(AVLNode<T>* current, T data)
{

}

template<typename T>
AVLNode<T>* AVL<T>::recursiveRemove(AVLNode<T>* current, T data, AVLNode<T>* dummy)
{

}

template<typename T>
AVLNode<T>* AVL<T>::findPredecessor(AVLNode<T>* current, AVLNode<T>* temp)
{

}

template<typename T>
AVLNode<T>* AVL<T>::rotate(AVLNode<T>* current)
{

}

template<typename T>
AVLNode<T>* AVL<T>::leftRotate(AVLNode<T>* current)
{

}

template<typename T>
void AVL<T>::update(AVLNode<T>* current)
{

}
 
template<typename T>
void AVL<T>::add(T data)
{

}
 
template<typename T>
T AVL<T>::remove(T data)
{

}

template<typename T>
T AVL<T>::get(T data) const
{

}
 
template<typename T>
bool AVL<T>::contains(T data) const
{

}

template<typename T>
T AVL<T>::findMedian() const
{

}

template<typename T>
void AVL<T>::clear()
{

}
