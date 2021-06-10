/**
 * @file binarytree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */
#include "TreeTraversals/InorderTraversal.h"
#include <iostream>
#include <stack>
using std::stack;

/**
 * @return The height of the binary tree. Recall that the height of a binary
 *  tree is just the length of the longest path from the root to a leaf, and
 *  that the height of an empty tree is -1.
 */
template <typename T>
int BinaryTree<T>::height() const
{
    // Call recursive helper function on root
    return height(root);
}

/**
 * Private helper function for the public height function.
 * @param subRoot
 * @return The height of the subtree
 */
template <typename T>
int BinaryTree<T>::height(const Node* subRoot) const
{
    // Base case
    if (subRoot == NULL)
        return -1;

    // Recursive definition
    return 1 + std::max(height(subRoot->left), height(subRoot->right));
}

/**
 * Prints out the values of the nodes of a binary tree in order.
 * That is, everything to the left of a node will be printed out before that
 * node itself, and everything to the right of a node will be printed out after
 * that node.
 */
template <typename T>
void BinaryTree<T>::printLeftToRight() const
{
    // Call recursive helper function on the root
    printLeftToRight(root);

    // Finish the line
    std::cout << std::endl;
}

/**
 * Private helper function for the public printLeftToRight function.
 * @param subRoot
 */
template <typename T>
void BinaryTree<T>::printLeftToRight(const Node* subRoot) const
{
    // Base case - null node
    if (subRoot == NULL)
        return;

    // Print left subtree
    printLeftToRight(subRoot->left);

    // Print this node
    std::cout << subRoot->elem << ' ';

    // Print right subtree
    printLeftToRight(subRoot->right);
}

/**
 * Flips the tree over a vertical axis, modifying the tree itself
 *  (not creating a flipped copy).
 */
template <typename T>
void BinaryTree<T>::mirror()
{
    //your code here

    root->mirror();
}

template <typename T>
void BinaryTree<T>::Node::mirror() {
    Node* holderNode = left;
    left = right;
    right = holderNode;

    if (left != NULL) {
        left->mirror();
    }
    if (right != NULL) {
        right->mirror();
    }
}

/**
 * isOrdered() function iterative version
 * @return True if an in-order traversal of the tree would produce a
 *  nondecreasing list output values, and false otherwise. This is also the
 *  criterion for a binary tree to be a binary search tree.
 */
template <typename T>
bool BinaryTree<T>::isOrderedIterative() const
{
    // your code here
    bool ordered = true;

    stack<Node*> nodeStack;
    nodeStack.push(root);

    while (ordered && nodeStack.size() != 0) {

        // add all possible left sides from the top of the stack of nodes
        while (nodeStack.top()->left != NULL) 
            nodeStack.push( nodeStack.top()->left );

        bool movingUp = true;
        while (ordered && movingUp && nodeStack.size() != 0) {
            Node* currNode = nodeStack.top();
            // check left and right ordered
            if (currNode->left != NULL) { 
                if (currNode->left->maxNode() > currNode->elem) 
                    ordered = false;
            }
            if (currNode->right != NULL) { 
                if (currNode->elem > currNode->right->minNode()) 
                    ordered = false;
            }

            // remove checked node and add its right side if possible
            nodeStack.pop();
            if (currNode->right != NULL) {
                nodeStack.push( currNode->right );
                movingUp = false;
            }
        }
    }

    return ordered;
}

/**
 * isOrdered() function recursive version
 * @return True if an in-order traversal of the tree would produce a
 *  nondecreasing list output values, and false otherwise. This is also the
 *  criterion for a binary tree to be a binary search tree.
 */
template <typename T>
bool BinaryTree<T>::isOrderedRecursive() const
{
    // your code here
    return root->isOrdered();
}

template <typename T>
bool BinaryTree<T>::Node::isOrdered() {

    bool leftBool = true;
    bool rightBool = true;

    if (left != NULL) {
        T maxLeft = left->maxNode();

        leftBool = left->isOrdered();

        if (maxLeft > elem)
            leftBool = false;
    }

    if (right != NULL) {
        T minRight = right->minNode();

        rightBool = right->isOrdered();

        if (elem > minRight)
            rightBool = false;
    }

    return (leftBool && rightBool);
}


template <typename T>
T BinaryTree<T>::Node::maxNode() {
    T max1 = elem;
    T max2 = elem;
    if (left != NULL) {
        max1 = std::max(left->maxNode(), elem);
    }
    if (right != NULL) {
        max2 = std::max(right->maxNode(), elem);
    }
    return std::max(max1, max2);
}

template <typename T>
T BinaryTree<T>::Node::minNode() {
    T min1 = elem;
    T min2 = elem;
    if (left != NULL) {
        min1 = std::min(left->minNode(), elem);
    }
    if (right != NULL) {
        min2 = std::min(right->minNode(), elem);
    }
    return std::min(min1, min2);
}

