#pragma once

#include <vector>
#include <queue>
#include <iostream>

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

    enum class TraversalEnum {
        PREORDER, INORDER, POSTORDER
    };

    /*
        private helper methods
    */

   /**
     * This is a recursive method that calls itself in order to help us find where we should add the new data.
     * 
     * @param current Current will be the node that the recursive method is currently getting the data and comparing.
     * @param data Data is the information that we want to add to the BST.
     * @return We will be returning another node which will do nothing in the wrapper method, but will return the
     * correct node that we will set left or right regardless if we are adding or just going through the BST.
     */
    Node* recursiveAdd(Node* current, T data);

    /**
     * This is the recursive method that we will call in remove() that will allow us to traverse through the BST
     * and find and remove the data.
     * 
     * @param current Current is the current node that we are observing and comparing the data to the data passed in.
     * @param data Data is the information that was given to the remove method that we will compare node data to.
     * @param dummy Dummy is a Node Object that we will create to store the data that we will remove.
     * @return We will return here a node that we will set the previous current's child as.
     */
    Node* recursiveRemove(Node* current, T data, Node* dummy);

    /**
     * This is another helper method that will find the successor in the case that the data that we want to remove
     * has 2 children.
     * 
     * @param current Current is the current node that we are observing and checking if it has children.
     * @param dummy Dummy here is a different than the other dummy in the rRemove() that will store the data of the
     *              successor.
     * @return We will return the node that we will set the precious current's child with.
     */
    Node* findSuccessor(Node* current, Node* dummy);

    /**
     * Recrusive helper that takes in a a enum to differentiate between traversal types
     * 
     * @param current the current node that we are at during the traversal
     * @param list a reference to the list that we want to populate
     * @param type TraversalEnum which dictates which traversal type
     */
    void traverse(Node* current, std::vector<T>& list, const TraversalEnum& type) const;

    /**
     * This is the recursive method that will traverse to the bottom on the BST and then start calculating the height.
     * 
     * @param current Current is the current node that we are observing.
     * @return We will return the value of height for the root.
     */
    int recursiveHeight(Node* current) const;

    /**
     * This is the recursive helper method that will traverse through all of the nodes
     * and delete them because we have dynamically allocated nodes
     * 
     * The high level is that we will recurse to the bottom and remove nodes from the bottom up
     * 
     * @param current the current node that we are at durring the traversal
     * @return returns for pointer reinforcement (should just return nullptr)
     */
    Node* recursiveClear(Node* current);

    /**
     * This is th recursive method that we will call in pruneGreaterThan() to remove the nodes greater than data.
     * @param current Current is the current node that we are observing.
     * @param data Data is the data that we are trying to find the nodes greater than and remove.
     * @param <T> the generic typing of the data in the BST.
     * @return Returns the node that a previous call needs to set left or right.
     */
    Node* recursivePruneGreaterThan(Node* current, const T& data);

public:
    // default constructor
    BST()
        : root(nullptr)
        , size(0)
    { }

    // list constructor
    BST(std::vector<T> list)
        : BST()
    {
        for (const auto& element : list)
        {
            std::cout << element << '\n';
            add(element);
        }
    }

    // default destructor
    ~BST() { clear(); }

    // define safe move assignment operator
    BST& operator=(BST&& other) noexcept
    {
        if (this != &other)
        {
            clear();
            root = other.root;
            size = other.size;

            other.root = nullptr;
            other.size = 0;
        }

        return *this;
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
    const T& get(T data) const;

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
    int height() const;

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
     * Should have a running time of O(n) - for garbage cleanup
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
BSTNode<T>* BST<T>::recursiveAdd(Node* current, T data)
{
    // base case: at a nullptr node from a leaf node
    if (!current)
    {
        size++;
        return new Node(data);
    }

    // grab current node's data for comparision
    T currentData = current->getData();

    // recurse
    if (currentData > data) current->setLeft(recursiveAdd(current->getLeft(), data));
    else if (currentData < data) current->setRight(recursiveAdd(current->getRight(), data));

    // this handles the case where we have a duplicate by just passing back a pointer to the node with the same data
    return current;
}

template<typename T>
BSTNode<T>* BST<T>::recursiveRemove(Node* current, T data, Node* dummy)
{
    // base case: we recursed through and didnt find the data that we want to remove
    if (!current) throw std::out_of_range("we couldn't find the data that we want to remove");

    // grab the current node's data for comparisons
    T currentData = current->getData();

    // recurse or found the node
    if (currentData > data) current->setLeft(recursiveRemove(current->getLeft(), data, dummy));
    else if (currentData < data) current->setRight(recursiveRemove(current->getRight(), data, dummy));
    else
    {
        // found the node so store the data into dummy node
        dummy->setData(currentData); // no default constructor: will overwrite this value
        size--;

        // checking for children
        if (!current->getLeft() && !current->getRight()) return nullptr; // no children
        else if (current->getLeft() && !current->getRight()) return current->getLeft(); // left child
        else if (!current->getLeft() && current->getRight()) return current->getRight(); // right child
        else // both children
        {
            // create dummy for findSuccessor to use and store data
            Node otherDummy(data);
            current->setRight(findSuccessor(current->getRight(), &otherDummy));
            current->setData(otherDummy.getData());

            return current;
        }
    }

    // this is only ran after the recurse left or right and come back
    return current;
}

template<typename T>
BSTNode<T>* BST<T>::findSuccessor(Node* current, Node* dummy)
{
    // current will start off as a valid node
    if (current->getLeft()) current->setLeft(findSuccessor(current->getLeft(), dummy));
    else
    {
        // we are at the last node going left so set dummy data
        dummy->setData(current->getData());

        // check and return the right child if exists
        return current->getRight() ? current->getRight() : nullptr;
    }

    // this runs once the left recursion comes back
    return current;
}

template<typename T>
void BST<T>::traverse(Node* current, std::vector<T>& list, const TraversalEnum& type) const
{
    if (!current) return;

    if (type == TraversalEnum::PREORDER) list.push_back(current->getData());
    traverse(current->getLeft(), list, type);
    if (type == TraversalEnum::INORDER) list.push_back(current->getData());
    traverse(current->getRight(), list, type);
    if (type == TraversalEnum::POSTORDER) list.push_back(current->getData());
}

template<typename T>
int BST<T>::recursiveHeight(Node* current) const
{
    if (!current) return -1;

    int leftHeight { recursiveHeight(current->getLeft()) };
    int rightHeight { recursiveHeight(current->getRight()) };

    return std::max(leftHeight, rightHeight) + 1;
}

template<typename T>
BSTNode<T>* BST<T>::recursiveClear(Node* current)
{
    if (!current) return nullptr;

    current->setLeft(recursiveClear(current->getLeft()));
    current->setRight(recursiveClear(current->getRight()));

    delete current;
    size--;
    return nullptr;
}

template<typename T>
BSTNode<T>* BST<T>::recursivePruneGreaterThan(Node* current, const T& data)
{
    if (!current) return nullptr;

    current->setLeft(recursivePruneGreaterThan(current->getLeft(), data));
    current->setRight(recursivePruneGreaterThan(current->getRight(), data));

    if (current->getData() <= data) return current;

    Node* leftChild = current->getLeft();
    Node* rightChild = current->getRight();

    delete current;
    size--;

    recursiveClear(rightChild);

    return leftChild;
}

template<typename T>
void BST<T>::add(T data)
{
    // check if data is null
    if constexpr (std::is_pointer<T>::value)
    {
        if (!data) throw std::invalid_argument("cannot add nullptr data (pointer types)");
    }

    // check if we already have a root
    if (!root)
    {
        root = new Node(data);
        size++;
    }
    else recursiveAdd(root, data);
}

template<typename T>
T BST<T>::remove(T data)
{
    // check if data is null
    if constexpr (std::is_pointer<T>::value)
    {
        if (!data) throw std::invalid_argument("cannot remove nullptr data (pointer types)");
    }

    if (!root) throw std::out_of_range("cannot remove from empty tree");

    // make dummy data to store the value that we are removing
    Node dummy(data); // no default constructor: overwrite data once we find the node

    root = recursiveRemove(root, data, &dummy);

    return dummy.getData();
}

template<typename T>
const T& BST<T>::get(T data) const
{
    // check for null data
    if constexpr (std::is_pointer<T>::value)
    {
        if (!data) throw std::invalid_argument("cannot find nullptr data (pointer types)");
    }

    Node* current = root;
    while (current)
    {
        const T& currentData = current->getData();

        if (currentData > data) current = current->getLeft();
        else if (currentData < data) current = current->getRight();
        else return current->getData();
    }

    throw std::out_of_range("data not found in the tree");
}

template<typename T>
bool BST<T>::contains(T data) const
{
    // check for null data
    if constexpr (std::is_pointer<T>::value)
    {
        if (!data) throw std::invalid_argument("cannot find nullptr data (pointer types)");
    }

    Node* current = root;
    while (current)
    {
        T currentData = current->getData();

        if (currentData > data) current = current->getLeft();
        else if (currentData < data) current = current->getRight();
        else return true;
    }

    return false;
}

template<typename T>
std::vector<T> BST<T>::preorder() const
{
    std::vector<T> ret;
    ret.reserve(size); // [optimization] pre-allocating space for ret

    traverse(root, ret, TraversalEnum::PREORDER);

    return ret;
}

template<typename T>
std::vector<T> BST<T>::inorder() const
{
    std::vector<T> ret;
    ret.reserve(size); // [optimization] pre-allocating space for ret

    traverse(root, ret, TraversalEnum::INORDER);

    return ret;
}
template<typename T>
std::vector<T> BST<T>::postorder() const
{
    std::vector<T> ret;
    ret.reserve(size); // [optimization] pre-allocating space for ret

    traverse(root, ret, TraversalEnum::POSTORDER);

    return ret;
}

template<typename T>
std::vector<T> BST<T>::levelorder() const
{
    std::vector<T> ret;
    ret.reserve(size); // [optimization] pre-allocating space for ret
    if (!root) return ret; // check for empty tree

    // create queue and add root
    std::queue<Node*> fifo;
    fifo.push(root);

    while (!fifo.empty())
    {
        // grab and remove the front value of the queue
        Node* current = fifo.front();
        fifo.pop();

        // add data to vector
        ret.push_back(current->getData());

        // add children to queue if possible
        if (current->getLeft()) fifo.push(current->getLeft());
        if (current->getRight()) fifo.push(current->getRight());
    }

    return ret;
}

template<typename T>
int BST<T>::height() const
{
    if (!root) return -1;

    return recursiveHeight(root);
}

template<typename T>
void BST<T>::clear()
{
    root = recursiveClear(root);
}

template<typename T>
BSTNode<T>* BST<T>::pruneGreaterThan(T data)
{
    // check for empty tree
    if (!root) return nullptr;

    // check if we can even remove
    root = recursivePruneGreaterThan(root, data);
    return root;
}

