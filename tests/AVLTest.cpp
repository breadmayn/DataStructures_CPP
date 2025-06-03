#include <gtest/gtest.h>
// #include <vector>

#include "AVL.hpp"

class AVLTest : public ::testing::Test {
protected:
    AVL<int> avlTree;

    void SetUp() override
    {
        avlTree = AVL<int>();
    }

    void TearDown() override
    {

    }
};

TEST_F(AVLTest, testAddRightRotation)
{
    /*
            5                   4
           /                   / \
          4         ->        3   5
        /
       3
    */
    avlTree.add(5);
    avlTree.add(4);
    avlTree.add(3);

    EXPECT_EQ(3, avlTree.getSize());

    AVLNode<int>* root = avlTree.getRoot();
    ASSERT_EQ(4, root->getData());
    ASSERT_EQ(1, root->getHeight());
    ASSERT_EQ(0, root->getBalanceFactor());
    ASSERT_EQ(3, root->getLeft()->getData());
    ASSERT_EQ(0, root->getLeft()->getHeight());
    ASSERT_EQ(0, root->getLeft()->getBalanceFactor());
    ASSERT_EQ(5, root->getRight()->getData());
    ASSERT_EQ(0, root->getRight()->getHeight());
    ASSERT_EQ(0, root->getRight()->getBalanceFactor());
}

TEST_F(AVLTest, testAddRightLeftRotationRoot)
{
    /*
        3               4
         \             / \
          5     ->    3   5
        /
       4
    */
    avlTree.add(3);
    avlTree.add(5);
    avlTree.add(4);

    EXPECT_EQ(3, avlTree.getSize());

    AVLNode<int>* root = avlTree.getRoot();
    ASSERT_EQ(4, root->getData());
    ASSERT_EQ(1, root->getHeight());
    ASSERT_EQ(0, root->getBalanceFactor());
    ASSERT_EQ(3, root->getLeft()->getData());
    ASSERT_EQ(0, root->getLeft()->getHeight());
    ASSERT_EQ(0, root->getLeft()->getBalanceFactor());
    ASSERT_EQ(5, root->getRight()->getData());
    ASSERT_EQ(0, root->getRight()->getHeight());
    ASSERT_EQ(0, root->getRight()->getBalanceFactor());
}

TEST_F(AVLTest, testRemove)
{
    /*
            646                     646
           /   \                   /   \
         477   856      ->       386   856
         / \                       \
       386 526                      526
    */
    int toBeRemoved { 477 };
    avlTree.add(646);
    avlTree.add(toBeRemoved);
    avlTree.add(856);
    avlTree.add(386);
    avlTree.add(526);

    ASSERT_EQ(toBeRemoved, avlTree.remove(toBeRemoved));

    EXPECT_EQ(4, avlTree.getSize());

    AVLNode<int>* root = avlTree.getRoot();
    ASSERT_EQ(646, root->getData());
    ASSERT_EQ(2, root->getHeight());
    ASSERT_EQ(1, root->getBalanceFactor());
    ASSERT_EQ(386, root->getLeft()->getData());
    ASSERT_EQ(1, root->getLeft()->getHeight());
    ASSERT_EQ(-1, root->getLeft()->getBalanceFactor());
    ASSERT_EQ(856, root->getRight()->getData());
    ASSERT_EQ(0, root->getRight()->getHeight());
    ASSERT_EQ(0, root->getRight()->getBalanceFactor());
    ASSERT_EQ(526, root->getLeft()->getRight()->getData());
    ASSERT_EQ(0, root->getLeft()->getRight()->getHeight());
    ASSERT_EQ(0, root->getLeft()->getRight()->getBalanceFactor());
}

TEST_F(AVLTest, testGet)
{
    /*
            477
           /   \
          386   526
                  \
                  646
    */
    int maximum { 646 };
    avlTree.add(477);
    avlTree.add(526);
    avlTree.add(386);
    avlTree.add(maximum);

    ASSERT_EQ(maximum, avlTree.get(maximum));
}

TEST_F(AVLTest, testContains)
{
    /*
            477
           /   \
          386   526
                  \
                  646
    */
    avlTree.add(477);
    avlTree.add(526);
    avlTree.add(386);
    avlTree.add(646);

    ASSERT_TRUE(avlTree.contains(477));
    ASSERT_TRUE(avlTree.contains(386));
    ASSERT_TRUE(avlTree.contains(646));
    ASSERT_TRUE(avlTree.contains(387));
    ASSERT_TRUE(avlTree.contains(700));
    ASSERT_TRUE(avlTree.contains(500));
}



TEST_F(AVLTest, testHeight)
{
    /*
                646
               /   \
             477   856
             / \
           386 526
    */
    avlTree.add(646);
    avlTree.add(386);
    avlTree.add(856);
    avlTree.add(526);
    avlTree.add(477);

    ASSERT_EQ(2, avlTree.getHeight());
}

TEST_F(AVLTest, testFindMedian)
{
    /*
             76
          /      \
        34        90
       /  \
     20    40

    median: 40
    */

    avlTree.add(76);
    avlTree.add(34);
    avlTree.add(90);
    avlTree.add(20);
    avlTree.add(40);

    AVLNode<int>* root = avlTree.getRoot();
    ASSERT_EQ(root->getLeft()->getRight()->getData(), avlTree.findMedian());

    /*
               76
            /      \
          34        90
         /  \      /   \
        20    40  81    100

    median: 76
    */
    avlTree.add(81);
    avlTree.add(100);
    ASSERT_EQ(root->getData(), avlTree.findMedian());
}

TEST_F(AVLTest, testConstructorAndClear)
{
    /*
             7
            / \
           1   24
    */

    std::vector<int> toAdd;
    toAdd.push_back(7);
    toAdd.push_back(24);
    toAdd.push_back(1);
    avlTree = AVL<int>(toAdd);

    avlTree.clear();
    ASSERT_EQ(nullptr, avlTree.getRoot());
    EXPECT_EQ(0, avlTree.getSize());
}
