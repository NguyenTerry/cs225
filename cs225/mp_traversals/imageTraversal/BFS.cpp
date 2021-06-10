#include <iterator>
#include <cmath>

#include <list>
#include <queue>
#include <stack>
#include <vector>

#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"
#include "BFS.h"

using namespace cs225;

/**
 * Initializes a breadth-first ImageTraversal on a given `png` image,
 * starting at `start`, and with a given `tolerance`.
 * @param png The image this BFS is going to traverse
 * @param start The start point of this BFS
 * @param tolerance If the current point is too different (difference larger than tolerance) with the start point,
 * it will not be included in this BFS
 */
BFS::BFS(const PNG & png_, const Point & start, double tolerance_) : visited(png_.width() * png_.height(), false) {  
  /** @todo [Part 1] */
  png = png_;
  tolerance = tolerance_;
  startPoint = start;

  add(startPoint);
  visited[index(startPoint.x, startPoint.y)] = true;
  bfsLoop(getNeighbors(startPoint));
}

void BFS::bfsLoop(std::vector<Point> neighbors) {
  std::vector<Point> neighbors2;

  for (Point n: neighbors) {
    if (isValid(n)) {
      // std::cout << n.x << " " << n.y;
      // std::cout << " valid" << std::endl;
      add(n);
      visited[index(n.x, n.y)] = true;

      for (Point m : getNeighbors(n))
        neighbors2.push_back(m);
      }
  }

  if (neighbors2.size() != 0)
    bfsLoop(neighbors2);
}

int BFS::index(int x, int y) {
  return x+png.width()*y;
}

std::vector<Point> BFS::getNeighbors(const Point & p1) {
  std::vector<Point> neighbors;

  Point right = Point(p1.x+1, p1.y);
  Point down = Point(p1.x, p1.y+1);
  Point left = Point(p1.x-1, p1.y);
  Point up = Point(p1.x, p1.y-1);

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

bool BFS::isValid(Point p) {
  if (p.x < 0 || png.width()-1 < p.x) 
    return false;
  if (p.y < 0 || png.height()-1 < p.y) 
    return false;
  if (calculateDelta(png.getPixel(p.x,p.y), png.getPixel(startPoint.x,startPoint.y)) > tolerance) {
    visited[index(p.x, p.y)] = true;
    return false;
  }
  if (visited[index(p.x, p.y)]) 
    return false;
  
  return true;
}

/**
 * Returns an iterator for the traversal starting at the first point.
 */
ImageTraversal::Iterator BFS::begin() {
  /** @todo [Part 1] */
  // ImageTraversal::Iterator iter(this);
  ImageTraversal::Iterator iter;
  iter.value = pointList.begin();
  return iter;
}

/**
 * Returns an iterator for the traversal one past the end of the traversal.
 */
ImageTraversal::Iterator BFS::end() {
  /** @todo [Part 1] */
  // ImageTraversal::Iterator iter(this);
  ImageTraversal::Iterator iter;
  iter.value = pointList.end();
  return iter;
}

/**
 * Adds a Point for the traversal to visit at some point in the future.
 */
void BFS::add(const Point & point) {
  /** @todo [Part 1] */
  pointList.push_back(point);
}

/**
 * Removes and returns the current Point in the traversal.
 */
Point BFS::pop() {
  /** @todo [Part 1] */
  Point p = pointList.front();
  pointList.pop_front();
  return p;
}

/**
 * Returns the current Point in the traversal.
 */
Point BFS::peek() const {
  /** @todo [Part 1] */
  return pointList.front();
}

/**
 * Returns true if the traversal is empty.
 */
bool BFS::empty() const {
  /** @todo [Part 1] */
  return pointList.empty();
}
