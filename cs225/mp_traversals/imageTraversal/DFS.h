/**
 * @file DFS.h
 */

#pragma once

#include <iterator>
#include <cmath>
#include <list>
#include <stack>
#include <queue>


#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"

using namespace cs225;

/**
 * A depth-first ImageTraversal.
 * Derived from base class ImageTraversal
 */
class DFS : public ImageTraversal {
public:
  DFS(const PNG & png, const Point & start, double tolerance);

  ImageTraversal::Iterator begin();
  ImageTraversal::Iterator end();

  void add(const Point & point);
  Point pop();
  Point peek() const;
  bool empty() const;

  void dfsLoop(Point p);
  bool isValid(Point p);
  std::vector<Point> getNeighbors(Point p);

private:
	/** @todo [Part 1] */
	/** add private members here*/
  std::list<Point> pointList;
  PNG png;
  double tolerance;
  Point startPoint;
};
