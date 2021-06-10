#pragma once
	
#include "../binarytree.h"
#include "TreeTraversal.h"

#include <iterator>
#include <stack>

/**
 * A derived, templatized class for inorder traversal algorithms on trees.
 * 
 * Simulates an iterative traversal of a given tree using a stack
 * and a given root node.
 */
template <typename T>
class InorderTraversal : public TreeTraversal<T> {
  public: 
    /**
     * Initializes a Inorder TreeTraversal of a tree,
     * with the traversal storing the tree's root.
     * Hint: See lab handout for guidance
     *
     * @param root The root node of the tree
     */	
    InorderTraversal(typename BinaryTree<T>::Node* root)
	    : root(root)
    {
      // stack.push(root);	
      // your code here
      std::stack<typename BinaryTree<T>::Node*> nodeStack;
      nodeStack.push(root);

      while (nodeStack.size() != 0) {

        // add all possible left sides from the top of the stack of nodes
        while (nodeStack.top()->right != NULL) 
            nodeStack.push( nodeStack.top()->right );

        bool movingUp = true;
        while (movingUp && nodeStack.size() != 0) {
          typename BinaryTree<T>::Node* currNode = nodeStack.top();
          // check left and right ordered
          stack.push( currNode );

          // remove checked node and add its right side if possible
          nodeStack.pop();
          if (currNode->left != NULL) {
              nodeStack.push( currNode->left );
              movingUp = false;
          }
        }
      }
    }

    /**
     * Returns an iterator for the traversal starting at the root node.
     * Important for sake of looping through an iterator's contents.
     * 
     * @return The iterator object pointing to the first node in the traversal
     */	
    typename TreeTraversal<T>::Iterator begin() {
      return typename TreeTraversal<T>::Iterator(this, root);
    }

    /**
     * Returns an iterator for the traversal pointing to the
     * element one past the end of the traversal.
     * Important for the sake of looping through an iterator's contents
     * 
     * @return The iterator object pointing to the elemnt after the end of the traversal.
     */	
    typename TreeTraversal<T>::Iterator end() {
      return typename TreeTraversal<T>::Iterator();
    }

    /**
     * Given a node in the tree, add the next appropriate
     * nodes to the stack such that when popped, and inorder
     * traversal is simulated.
     * Hint: See lab handout for guidance
     * 
     * @param treeNode The subroot that determines what next nodes
     *        should be added to the traversal
     */	
    void add(typename BinaryTree<T>::Node *& treeNode) {
      // your code here
      // if (treeNode->left != NULL) { 
      //     stack.push(treeNode->left);
      // }    
      // if (treeNode->right != NULL) {
      //     stack.push(treeNode->right);
      // }	


      // while (true) {

      //   // add all possible left sides from the top of the stack of nodes
      //   while (stack.top()->left != NULL) 
      //       stack.push( stack.top()->left );

      //   bool movingUp = true;
      //   while (movingUp && stack.size() != 0) {
      //     typename BinaryTree<T>::Node* currNode = stack.top();
      //     // check left and right ordered
      //     // do something

      //     // remove checked node and add its right side if possible
      //     stack.pop();
      //     if (currNode->right != NULL) {
      //         stack.push( currNode->right );
      //         movingUp = false;
      //     }
      //   }
      // }
    }

    /**
     * Removes and returns the current node in the traversal.
     * 
     * @return The current node in the traversal
     */	
    typename BinaryTree<T>::Node* pop() {
      typename BinaryTree<T>::Node* topNode = stack.top();
      stack.pop();
      return topNode;
    }

    /**
     * Returns the current node in the traversal or
     * NULL if the stack is empty.
     * 
     * @return The current node in the traversal
     */	
    typename BinaryTree<T>::Node* peek() const {
      return empty() ? NULL : stack.top();
    }

    /**
     * Returns true if the traversal is empty.
     * 
     * @return true if the traversal is empty.
     */	
    bool empty() const {
      return stack.empty();
    }

  private:
    std::stack<typename BinaryTree<T>::Node*> stack;
    typename BinaryTree<T>::Node* root;
};
