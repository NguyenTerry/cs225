/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */

#include <utility>
#include <algorithm>

using namespace std;

template <int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim>& first,
                                const Point<Dim>& second, int curDim) const
{
    /**
     * @todo Implement this function!
     */
    int n = first[curDim];
    int m = second[curDim];

    if (n < m) {
      return true;
    } else if (n > m) {
      return false;
    } else {
      return (first<second);
    }
}

template <int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim>& target,
                                const Point<Dim>& currentBest,
                                const Point<Dim>& potential) const
{
    /**
     * @todo Implement this function!
     */

    // std::cout<<"target: "<<target<<" :curr: "<<currentBest<<" :pot: "<<potential;

    double cbDistance = 0;
    double ptDistance = 0;
    for (size_t i = 0; i < Dim; i++) {
      cbDistance += ( (target[i] - currentBest[i])*(target[i] - currentBest[i]) );
      ptDistance += ( (target[i] - potential[i])*(target[i] - potential[i]) );
    }
    // std::cout<<" :curr: "<<cbDistance<<" :pot: "<<ptDistance<<std::endl;

    if (ptDistance == cbDistance) 
      return (potential < currentBest); 
    return (ptDistance < cbDistance);
}

template <int Dim>
KDTree<Dim>::KDTree(const vector<Point<Dim>>& newPoints)
{
    /**
     * @todo Implement this function!
     */
    vector<Point<Dim>> pts = newPoints;

    size = 0;
    root = makeTree(pts, 0);
    // std::cout<<std::endl;
}

template <int Dim>
typename KDTree<Dim>::KDTreeNode* KDTree<Dim>::makeTree(const vector<Point<Dim>>& _pts, int d) 
{
  if (_pts.size() == 0) {
    return NULL;
  }

  vector<Point<Dim>> pts = _pts;
  
  vector<Point<Dim>> left;
  vector<Point<Dim>> right;
  Point<Dim> midPt = pts[0];

  unsigned median =( pts.size() )/2;
  bool halfway = (median==0);

  while (!halfway) {
    vector<Point<Dim>> tempLeft;
    vector<Point<Dim>> tempRight;
    for (unsigned i = 1; i < pts.size(); i++) {
      Point<Dim> pt = pts[i];
      if ( pt==midPt || smallerDimVal(pt,midPt,d) ) {
        tempLeft.push_back(pt);
      } else {
        tempRight.push_back(pt);        
      }
    }

    unsigned rightSize = tempRight.size() + right.size();
    if (rightSize > median) {
      for (Point<Dim> p : tempLeft) {
        left.push_back(p);
      }
      left.push_back(midPt);
      pts = tempRight;
      midPt = pts[0];
    } 
    else if (rightSize < median) {
      for (Point<Dim> p : tempRight) {
        right.push_back(p);
      }
      right.push_back(midPt);
      pts = tempLeft;
      midPt = pts[0];
    } 
    else {
      for (Point<Dim> p : tempLeft) {
        left.push_back(p);
      }
      for (Point<Dim> p : tempRight) {
        right.push_back(p);
      }
      halfway = true;
    }
  }    

  KDTreeNode* node = new KDTreeNode(midPt);
  d = (d+1) % Dim;
  node->left = makeTree(left,d);
  node->right = makeTree(right,d);
  // delete left;
  // delete right;

  size += 1;
  return node;
}

template <int Dim>
KDTree<Dim>::KDTree(const KDTree<Dim>& other) {
  /**
   * @todo Implement this function!
   */
  size = Dim;
  root = copy( other.getRoot() );
}

template <int Dim>
const KDTree<Dim>& KDTree<Dim>::operator=(const KDTree<Dim>& rhs) {
  /**
   * @todo Implement this function!
   */
  KDTreeNode* node = copy( rhs.getRoot() );
  return *node;
  // return NULL;
}

template <int Dim>
typename KDTree<Dim>::KDTreeNode* KDTree<Dim>::getRoot() {
  return root;
}

template <int Dim>
typename KDTree<Dim>::KDTreeNode* KDTree<Dim>::copy(KDTreeNode* node) {
  if (node == NULL) return;

  KDTreeNode* nodeCopy = new KDTreeNode();
  nodeCopy->point = node->point;

  KDTreeNode leftCopy = *( copy(node->left) );
  KDTreeNode rightCopy = *( copy(node->right) );

  nodeCopy->left = &leftCopy;
  nodeCopy->right = &rightCopy;

  return nodeCopy;
}

template <int Dim>
KDTree<Dim>::~KDTree() {
  /**
   * @todo Implement this function!
   */
  deleteNode(root);
}

template <int Dim>
void KDTree<Dim>::deleteNode(KDTreeNode* node) {
  if (node == NULL) return;

  deleteNode(node->left);
  deleteNode(node->right);
  delete node;
}

template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const
{
    /**
     * @todo Implement this function!
     */

  return findNeighbor(root, query, 0);
}

template <int Dim>
Point<Dim> KDTree<Dim>::findNeighbor(KDTreeNode* node, const Point<Dim>& query, int d) const
{
  Point<Dim> currentBest = node->point;

  Point<Dim> targetPot;
  bool hasTarget = false;
  Point<Dim> otherPot;
  bool hasOther = false;

  int newDim = (d+1) % Dim;

  if (query==currentBest) {
    return currentBest;
  }
  else if ( smallerDimVal(query,currentBest,d) ) {
    if (node->left != NULL && ((node->left)->point).isMine() == false) {
      targetPot = findNeighbor(node->left, query, newDim);
      hasTarget = true;
    }  
    if (node->right != NULL && ((node->right)->point).isMine() == false) {
      otherPot = findNeighbor(node->right, query, newDim);
      hasOther = true;
    }    
  }
  else {
    if (node->right != NULL && ((node->right)->point).isMine() == false) {
      targetPot = findNeighbor(node->right, query, newDim);
      hasTarget = true;
    } 
    if (node->left != NULL && ((node->left)->point).isMine() == false) {
      otherPot = findNeighbor(node->left, query, newDim);
      hasOther = true;
    }
  }


  if (hasTarget) {
    if ( shouldReplace(query, currentBest, targetPot) ) {
      currentBest = targetPot;
    } 
  }  
  if (hasOther) {
    if ( shouldReplace(query, currentBest, otherPot) ) {
      currentBest = otherPot;
    }
  }
  return currentBest;

}
