#include <gtest/gtest.h>

#include "BST.hpp"

class BSTTest : public ::testing::Test {
protected:
    BST<int> tree;

    void SetUp() override
    {
        tree = BST<int>();
    }

    void TearDown() override
    {

    }
};

TEST_F(BSTTest, testInitialization)
{
    ASSERT_EQ(0, tree.getSize());
    ASSERT_EQ(tree.getRoot(), nullptr);
}

TEST_F(BSTTest, testConstructor)
{
    /*
            2
            /
        0
            \
            1
    */

    std::vector<int> data;
    data.push_back(2);
    data.push_back(0);
    data.push_back(1);
    tree = BST<int>(data);

    ASSERT_EQ(3, tree.getSize());

    ASSERT_EQ(2, tree.getRoot()->getData());
    ASSERT_EQ(0, tree.getRoot()->getLeft()->getData());
    ASSERT_EQ(1, tree.getRoot()->getLeft()->getRight()->getData());
}

TEST_F(BSTTest, testAdd)
{
    /*
            1
            / \
        0   2
    */

    tree.add(1);
    tree.add(0);
    tree.add(2);

    ASSERT_EQ(3, tree.getSize());

    ASSERT_EQ(1, tree.getRoot()->getData());
    ASSERT_EQ(0, tree.getRoot()->getLeft()->getData());
    ASSERT_EQ(2, tree.getRoot()->getRight()->getData());
}

TEST_F(BSTTest, testRemove)
{
    int temp { 2 };

    /*
            1
            / \
        0   2
                \
                3
                \
                4

        ->

            1
            / \
        0   3
                \
                4
    */

    tree.add(1);
    tree.add(0);
    tree.add(temp);
    tree.add(3);
    tree.add(4);
    ASSERT_EQ(5, tree.getSize());

    ASSERT_EQ(temp, tree.remove(2));

    ASSERT_EQ(4, tree.getSize());

    ASSERT_EQ(1, tree.getRoot()->getData());
    ASSERT_EQ(0, tree.getRoot()->getLeft()->getData());
    ASSERT_EQ(3, tree.getRoot()->getRight()->getData());
    ASSERT_EQ(4, tree.getRoot()->getRight()->getRight()->getData());

    temp = 1;
    tree = BST<int>();

    /*
            1
            / \
        0   2
                \
                3
                \
                4

        ->

            2
            / \
        0   3
                \
                4
    */

    tree.add(temp);
    tree.add(0);
    tree.add(2);
    tree.add(3);
    tree.add(4);
    ASSERT_EQ(5, tree.getSize());

    ASSERT_EQ(temp, tree.remove(1));

    ASSERT_EQ(4, tree.getSize());

    ASSERT_EQ(2, tree.getRoot()->getData());
    ASSERT_EQ(0, tree.getRoot()->getLeft()->getData());
    ASSERT_EQ(3, tree.getRoot()->getRight()->getData());
    ASSERT_EQ(4, tree.getRoot()->getRight()->getRight()->getData());
}

TEST_F(BSTTest, testGet)
{
    int temp200 { 200 };
    int temp185 { 185 };
    int temp190 { 190 };
    int temp195 { 195 };
    int temp215 { 215 };
    int temp205 { 205 };
    int temp210 { 210 };

    /*
                200
            /        \
        185         215
            \         /
            190     205
            \       \
            195     210
    */

    tree.add(temp200);
    tree.add(temp185);
    tree.add(temp190);
    tree.add(temp195);
    tree.add(temp215);
    tree.add(temp205);
    tree.add(temp210);
    ASSERT_EQ(7, tree.getSize());

    // We want to make sure the data we retrieve is the one from the tree,
    // not the data that was passed in. The ints need to b{ outside } of
    // the range [-128, 127] so that they are not cached.
    ASSERT_EQ(temp185, tree.get(185));
    ASSERT_EQ(temp190, tree.get(190));
    ASSERT_EQ(temp195, tree.get(195));
    ASSERT_EQ(temp200, tree.get(200));
    ASSERT_EQ(temp205, tree.get(205));
    ASSERT_EQ(temp210, tree.get(210));
    ASSERT_EQ(temp215, tree.get(215));
}

TEST_F(BSTTest, testContains)
{
    /*
            3
            /     \
        0       6
            \     /
            1   4
            \   \
            2   5
    */

    tree.add(3);
    tree.add(0);
    tree.add(1);
    tree.add(2);
    tree.add(6);
    tree.add(4);
    tree.add(5);
    ASSERT_EQ(7, tree.getSize());

    ASSERT_TRUE(tree.contains(0));
    ASSERT_TRUE(tree.contains(1));
    ASSERT_TRUE(tree.contains(2));
    ASSERT_TRUE(tree.contains(3));
    ASSERT_TRUE(tree.contains(4));
    ASSERT_TRUE(tree.contains(5));
    ASSERT_TRUE(tree.contains(6));
}

TEST_F(BSTTest, testPreorder)
{
    /*
            3
            /     \
        0       8
            \     /
            1   4
            \   \
            2   6
                / \
                5   7
    */

    tree.add(3);
    tree.add(0);
    tree.add(1);
    tree.add(2);
    tree.add(8);
    tree.add(4);
    tree.add(6);
    tree.add(5);
    tree.add(7);
    ASSERT_EQ(9, tree.getSize());

    std::vector<int> preorder {
        3, 0, 1, 2, 8, 4, 6, 5, 7
    };

    // Should be [3, 0, 1, 2, 8, 4, 6, 5, 7]
    ASSERT_EQ(preorder, tree.preorder());
}

TEST_F(BSTTest, testInorder)
{
    /*
            3
            /     \
        0       8
            \     /
            1   4
            \   \
            2   6
                / \
                5   7
    */

    tree.add(3);
    tree.add(0);
    tree.add(1);
    tree.add(2);
    tree.add(8);
    tree.add(4);
    tree.add(6);
    tree.add(5);
    tree.add(7);
    ASSERT_EQ(9, tree.getSize());

    std::vector<int> inorder {
        0, 1, 2, 3, 4, 5, 6, 7, 8
    };

    // Should be [0, 1, 2, 3, 4, 5, 6, 7, 8]
    ASSERT_EQ(inorder, tree.inorder());
}

TEST_F(BSTTest, testPostorder)
{
    /*
            3
            /     \
        0       8
            \     /
            1   4
            \   \
            2   6
                / \
                5   7
    */

    tree.add(3);
    tree.add(0);
    tree.add(1);
    tree.add(2);
    tree.add(8);
    tree.add(4);
    tree.add(6);
    tree.add(5);
    tree.add(7);
    ASSERT_EQ(9, tree.getSize());

    std::vector<int> postorder {
        2, 1, 0, 5, 7, 6, 4, 8, 3
    };

    // Should be [2, 1, 0, 5, 7, 6, 4, 8, 3]
    ASSERT_EQ(postorder, tree.postorder());
}

TEST_F(BSTTest, testLevelorder)
{
    /*
            3
            /     \
        0       8
            \     /
            1   4
            \   \
            2   6
                / \
                5   7
    */

    tree.add(3);
    tree.add(0);
    tree.add(1);
    tree.add(2);
    tree.add(8);
    tree.add(4);
    tree.add(6);
    tree.add(5);
    tree.add(7);
    ASSERT_EQ(9, tree.getSize());

    std::vector<int> levelorder {
        3, 0, 8, 1, 4, 2, 6, 5, 7
    };

    // Should be [3, 0, 8, 1, 4, 2, 6, 5, 7]
    ASSERT_EQ(levelorder, tree.levelorder());
}

TEST_F(BSTTest, testHeight)
{
    /*
            2
            /
        0
            \
            1
    */

    tree.add(2);
    tree.add(0);
    tree.add(1);
    ASSERT_EQ(3, tree.getSize());

    ASSERT_EQ(2, tree.height());
}

TEST_F(BSTTest, testClear)
{
    /*
            2
            /
        0
            \
            1
    */

    tree.add(2);
    tree.add(0);
    tree.add(1);
    ASSERT_EQ(3, tree.getSize());

    tree.clear();
    ASSERT_EQ(0, tree.getSize());
    ASSERT_EQ(tree.getRoot(), nullptr);
}

TEST_F(BSTTest, testPruneGreaterThan)
{
    /*
                50
                /    \
            25      75
            /  \
            12   37
            /  \    \
        10  15    40
            /
            13
    */

    tree.add(50);
    tree.add(25);
    tree.add(75);
    tree.add(12);
    tree.add(37);
    tree.add(10);
    tree.add(15);
    tree.add(40);
    tree.add(13);
    ASSERT_EQ(9, tree.getSize());

    /*
                    25
                    /
                12
                /  \
                10   15
                    /
                    13
        */

    BSTNode<int>* newRoot = tree.pruneGreaterThan(30);
    ASSERT_EQ(25, newRoot->getData());
    ASSERT_EQ(12, newRoot->getLeft()->getData());
    ASSERT_EQ(10, newRoot->getLeft()->getLeft()->getData());
    ASSERT_EQ(15, newRoot->getLeft()->getRight()->getData());
    ASSERT_EQ(13, newRoot->getLeft()->getRight()->getLeft()->getData());
    ASSERT_EQ(newRoot->getRight(), nullptr);
}