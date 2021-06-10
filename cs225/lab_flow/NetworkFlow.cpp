/**
 * @file NetworkFlow.cpp
 * CS 225: Data Structures
 */

#include <vector>
#include <algorithm>
#include <set>

#include "graph.h"
#include "edge.h"

#include "NetworkFlow.h"

int min(int a, int b) {
  if (a<b)
    return a;
  else return b;
}

NetworkFlow::NetworkFlow(Graph & startingGraph, Vertex source, Vertex sink) :
  g_(startingGraph), residual_(Graph(true,true)), flow_(Graph(true,true)), source_(source), sink_(sink) {

  // YOUR CODE HERE
  maxFlow_ = 0;
  for (auto v1 : g_.getVertices()) {
    for (auto v2 : g_.getAdjacent(v1)) {
        string label = g_.getEdgeLabel(v1, v2);
        int weight = g_.getEdgeWeight(v1,v2);

        flow_.insertEdge(v1,v2);
        flow_.setEdgeWeight(v1,v2,0);
        flow_.setEdgeLabel(v1,v2,label);

        residual_.insertEdge(v1,v2);
        residual_.setEdgeWeight(v1,v2,weight);
        residual_.setEdgeLabel(v1,v2,label);

        residual_.insertEdge(v2,v1);
        residual_.setEdgeWeight(v2,v1,0);
        residual_.setEdgeLabel(v2,v1,label);
    }
  }
}

  /**
   * findAugmentingPath - use DFS to find a path in the residual graph with leftover capacity.
   *  This version is the helper function.
   *
   * @param source  The starting (current) vertex
   * @param sink    The destination vertex
   * @param path    The vertices in the path
   * @param visited A set of vertices we have visited
   */

bool NetworkFlow::findAugmentingPath(Vertex source, Vertex sink, 
  std::vector<Vertex> &path, std::set<Vertex> &visited) {

  if (visited.count(source) != 0) //== 1 == true
    return false;
  visited.insert(source);
  
  if (source == sink) {
    // for (unsigned i = 0; i < path.size(); i++) {
    //   cout<<path[i]<<"||";
    // } cout<<endl;

    // Edit flow_ and residual_
    int capacity = pathCapacity(path);
    for(unsigned i = 0; i+1 < path.size(); i++) {
      Vertex v1 = path[i];
      Vertex v2 = path[i+1];

      int oldRes = residual_.getEdgeWeight(v1, v2);
      int oldResRev = residual_.getEdgeWeight(v2, v1);

      residual_.setEdgeWeight(v1, v2, oldRes-capacity);
      residual_.setEdgeWeight(v2, v1, oldResRev+capacity);
      if (flow_.edgeExists(v1, v2))   flow_.setEdgeWeight(v1, v2, oldResRev+capacity);
    }
    // end  

    return true;
  }

  vector<Vertex> adjs = residual_.getAdjacent(source);
  for(auto it = adjs.begin(); it != adjs.end(); it++) {
    if (visited.count(*it) == 0 && residual_.getEdgeWeight(source,*it) > 0) {
      path.push_back(*it);
      if (findAugmentingPath(*it,sink,path,visited))
        return true;
      else {
        path.pop_back();
      }
    }
  }

  return false;
}

  /**
   * findAugmentingPath - use DFS to find a path in the residual graph with leftover capacity.
   *  This version is the main function.  It initializes a set to keep track of visited vertices.
   *
   * @param source The starting (current) vertex
   * @param sink   The destination vertex
   * @param path   The vertices in the path
   */

bool NetworkFlow::findAugmentingPath(Vertex source, Vertex sink, std::vector<Vertex> &path) {
   std::set<Vertex> visited;
   path.clear();
   path.push_back(source);
   return findAugmentingPath(source,sink,path,visited);
}

  /**
   * pathCapacity - Determine the capacity of a path in the residual graph.
   *
   * @param path   The vertices in the path
   */

int NetworkFlow::pathCapacity(const std::vector<Vertex> & path) const {
  // YOUR CODE HERE
  int capacity = -1;
  for(unsigned i = 0; i+1 < path.size(); i++) {
    Vertex v1 = path[i];
    Vertex v2 = path[i+1];

    if (capacity == -1) {
      capacity = residual_.getEdgeWeight(v1,v2);
    } else {
      capacity = std::min( capacity, residual_.getEdgeWeight(v1,v2) );
    }
  }

  return capacity;
}

  /**
   * calculuateFlow - Determine the capacity of a path in the residual graph.
   * Sets the member function `maxFlow_` to be the flow, and updates the
   * residual graph and flow graph according to the algorithm.
   *
   * @return The network flow graph.
   */

const Graph & NetworkFlow::calculateFlow() {
  // YOUR CODE HERE

  std::vector<Vertex> path;
  bool search = true;
  while(search)
    search = findAugmentingPath(source_, sink_, path);


  // cout<<"FLOW_____________________________"<<endl;
  // flow_.print();
  // cout<<"RESI______________________________"<<endl;
  // residual_.print();

  //Set maxFlow_
  for (auto v2 : flow_.getAdjacent(source_)) {
    maxFlow_ += flow_.getEdgeWeight(source_, v2);
  }

  return flow_;
}

int NetworkFlow::getMaxFlow() const {
  return maxFlow_;
}

const Graph & NetworkFlow::getGraph() const {
  return g_;
}

const Graph & NetworkFlow::getFlowGraph() const {
  return flow_;
}

const Graph & NetworkFlow::getResidualGraph() const {
  return residual_;
}

