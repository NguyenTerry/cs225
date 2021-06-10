#include <iterator>
#include <cmath>

#include <list>
#include <queue>
#include <stack>
#include <vector>

#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"
#include "DFS.h"


/**
 * Initializes a depth-first ImageTraversal on a given `png` image,
 * starting at `start`, and with a given `tolerance`.
 * 
 * @param png The image this DFS is going to traverse
 * @param start The start point of this DFS
 * @param tolerance If the current point is too different (difference larger than tolerance) with the start point,
 * it will not be included in this DFS
 */
DFS::DFS(const PNG & png_, const Point & start, double tolerance_) {  
  /** @todo [Part 1] */
  png = png_;
  tolerance = tolerance_;
  startPoint = start;

  dfsLoop(start);
}

void DFS::dfsLoop(Point p) {
  if (isValid(p)) {
    add(p);
  }

  std::vector<Point> neighbors = getNeighbors(p);
  for (int i = neighbors.size()-1; i >= 0; i--) {
    dfsLoop(neighbors[i]); 
  }
}

std::vector<Point> DFS::getNeighbors(Point p) {
  std::vector<Point> neighbors;

  Point right = Point(p.x+1, p.y);
  Point down = Point(p.x, p.y+1);
  Point left = Point(p.x-1, p.y);
  Point up = Point(p.x, p.y-1);

  if (isValid(right))
    neighbors.push_back(right);
  if (isValid(down))
    neighbors.push_back(down);
  if (isValid(left))
    neighbors.push_back(left);
  if (isValid(up))
    neighbors.push_back(up);

  return neighbors;
}

bool DFS::isValid(Point p) {

  if (p.x < 0 || png.width()-1 < p.x) {
    return false;
  }

  if (p.y < 0 || png.height()-1 < p.y) {
    return false;
  }

  if (calculateDelta(png.getPixel(p.x,p.y), png.getPixel(startPoint.x,startPoint.y)) > tolerance) {
    return false;
  }

  for (Point n: pointList) {
    if (n == p) {
      return false;
    }
  }

  return true;
}

/**
 * Returns an iterator for the traversal starting at the first point.
 */
ImageTraversal::Iterator DFS::begin() {
  /** @todo [Part 1] */
  // ImageTraversal::Iterator iter(this);
  ImageTraversal::Iterator iter;
  iter.value = pointList.begin();
  return iter;
}

/**
 * Returns an iterator for the traversal one past the end of the traversal.
 */
ImageTraversal::Iterator DFS::end() {
  /** @todo [Part 1] */
  // ImageTraversal::Iterator iter(this);
  ImageTraversal::Iterator iter;
  iter.value = pointList.end();
  return iter;
}

/**
 * Adds a Point for the traversal to visit at some point in the future.
 */
void DFS::add(const Point & point) {
  /** @todo [Part 1] */
  pointList.push_back(point);
}

/**
 * Removes and returns the current Point in the traversal.
 */
Point DFS::pop() { // front?
  /** @todo [Part 1] */
  Point p = pointList.back();
  pointList.pop_back();
  return p;
}

/**
 * Returns the current Point in the traversal.
 */
Point DFS::peek() const {
  /** @todo [Part 1] */
  return pointList.back(); // front?
}

/**
 * Returns true if the traversal is empty.
 */
bool DFS::empty() const {
  /** @todo [Part 1] */
  return pointList.empty();
}
