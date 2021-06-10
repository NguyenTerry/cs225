/**
 * @file avltree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */

#include <algorithm>    // std::max
#include <cmath>        // std::abs

template <class K, class V>
V AVLTree<K, V>::find(const K& key) const
{
    return find(root, key);
}

template <class K, class V>
V AVLTree<K, V>::find(Node* subtree, const K& key) const
{
    if (subtree == NULL)
        return V();
    else if (key == subtree->key)
        return subtree->value;
    else {
        if (key < subtree->key)
            return find(subtree->left, key);
        else
            return find(subtree->right, key);
    }
}

template <class K, class V>
void AVLTree<K, V>::rotateLeft(Node*& t)
{
    functionCalls.push_back("rotateLeft"); // Stores the rotation name (don't remove this)
    // your code here
    if (t != NULL) {
        if (t->right != NULL) {
            Node* newRoot = t->right;
            t->right = newRoot->left;
            newRoot->left = t;

            /* adjust heights */
            t->height = 1 + std::max( heightOrNeg1(t->left), heightOrNeg1(t->right) );
            newRoot->height = 1 + std::max( heightOrNeg1(newRoot->left), heightOrNeg1(newRoot->right) );
            
            /* reset t to the new root */
            t = newRoot;
        }
    } 
}

template <class K, class V>
void AVLTree<K, V>::rotateLeftRight(Node*& t)
{
    functionCalls.push_back("rotateLeftRight"); // Stores the rotation name (don't remove this)
    // Implemented for you:
    rotateLeft(t->left);
    rotateRight(t);
}

template <class K, class V>
void AVLTree<K, V>::rotateRight(Node*& t)
{
    functionCalls.push_back("rotateRight"); // Stores the rotation name (don't remove this)
    // your code here
    if (t != NULL) {
        if (t->left != NULL) {
            Node* newRoot = t->left;
            t->left = newRoot->right;
            newRoot->right = t;

            /* adjust heights */
            t->height = 1 + std::max( heightOrNeg1(t->left), heightOrNeg1(t->right) );
            newRoot->height = 1 + std::max( heightOrNeg1(newRoot->left), heightOrNeg1(newRoot->right) );

            /* reset t to the new root */
            t = newRoot;
        }
    }
}

template <class K, class V>
void AVLTree<K, V>::rotateRightLeft(Node*& t)
{
    functionCalls.push_back("rotateRightLeft"); // Stores the rotation name (don't remove this)
    // your code here
    rotateRight(t->right);
    rotateLeft(t);
}

template <class K, class V>
void AVLTree<K, V>::rebalance(Node*& subtree)
{
    // your code here
    if (subtree != NULL) {
        if ( (heightOrNeg1(subtree->left) - heightOrNeg1(subtree->right)) > 1) {
            Node* subLeft = subtree->left;
            if ( heightOrNeg1(subLeft->left) >= heightOrNeg1(subLeft->right) ) {
                rotateRight(subtree);
            } else {
                rotateLeftRight(subtree);
            }
        } 
        else if ( (heightOrNeg1(subtree->right) - heightOrNeg1(subtree->left)) > 1) {
            Node* subRight = subtree->right;
            if ( heightOrNeg1(subRight->left) <= heightOrNeg1(subRight->right) ) {
                rotateLeft(subtree);
            } else {
                rotateRightLeft(subtree);
            }
        } 
        else {
            subtree->height = 1 + std::max( heightOrNeg1(subtree->left), heightOrNeg1(subtree->right) );
        }
    }
}

template <class K, class V>
void AVLTree<K, V>::insert(const K & key, const V & value)
{
    insert(root, key, value);
}

template <class K, class V>
void AVLTree<K, V>::insert(Node*& subtree, const K& key, const V& value)
{
    // your code here
    if (subtree == NULL) {
        Node* newNode = new Node(key, value);
        subtree = newNode;
    } else {
        if (key >= subtree->key) {
            insert(subtree->right, key, value);
        } else {
            insert(subtree->left, key, value);
        }
    }

    // subtree->height = 1 + std::max( heightOrNeg1(subtree->left), heightOrNeg1(subtree->right) );
    rebalance(subtree);
}

template <class K, class V>
void AVLTree<K, V>::remove(const K& key)
{
    remove(root, key);
}

template <class K, class V>
void AVLTree<K, V>::remove(Node*& subtree, const K& key)
{
    if (subtree == NULL)
        return;

    if (key < subtree->key) {
        // your code here
        remove(subtree->left, key);  
    } else if (key > subtree->key) {
        // your code here
        remove(subtree->right, key);  
    } else {
        if (subtree->left == NULL && subtree->right == NULL) {
            /* no-child remove */
            // your code here
            subtree = NULL;
            return;
        } else if (subtree->left != NULL && subtree->right != NULL) {
            /* two-child remove */
            // your code here
            Node* rootNode = subtree->left;
            while (rootNode->right != NULL)
                rootNode = rootNode->right;
            swap(rootNode, subtree);
            remove(subtree->left, key);
        } else {
            /* one-child remove */
            // your code here
            if (subtree->left != NULL) {
                subtree = subtree->left;
            } else {
                subtree = subtree->right;
            }
        }
        // your code here
    }

    rebalance(subtree);
}
