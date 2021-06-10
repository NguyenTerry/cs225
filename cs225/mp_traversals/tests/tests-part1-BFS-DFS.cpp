#include "../cs225/catch/catch.hpp"

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#include "../cs225/PNG.h"
#include "../cs225/HSLAPixel.h"

#include "../imageTraversal/BFS.h"
#include "../imageTraversal/DFS.h"

using namespace cs225;



TEST_CASE("DFS maintains the deepest point on top", "[weight=0][part=1][part=1a]") {
  PNG png(40, 40);
  Point startPoint(20, 20);
  DFS dfs(png, startPoint, 0.2);

  dfs.add( Point(2, 2) );
  dfs.add( Point(2, 3) );
  dfs.add( Point(2, 4) );

  REQUIRE( dfs.peek() == Point(2, 4) );
}

TEST_CASE("DFS maintains a depth-first ordering", "[weight=0][part=1][part=1a]") {
  PNG png(40, 40);
  Point startPoint(20, 20);
  DFS dfs(png, startPoint, 0.2);

  dfs.add( Point(2, 2) );
  dfs.add( Point(2, 3) );
  dfs.add( Point(2, 4) );

  REQUIRE( dfs.pop() == Point(2, 4) );
  REQUIRE( dfs.pop() == Point(2, 3) );
  REQUIRE( dfs.pop() == Point(2, 2) );
  REQUIRE( dfs.pop() == Point(20, 20) );
}

TEST_CASE("BFS maintains the correct point on top", "[weight=0][part=1][part=1b]") {
  PNG png(40, 40);
  Point startPoint(20, 20);
  BFS bfs(png, startPoint, 0.2);

  bfs.add( Point(2, 2) );
  bfs.add( Point(2, 3) );
  bfs.add( Point(2, 4) );

  REQUIRE( bfs.peek() == Point(20, 20) );
}

TEST_CASE("BFS maintains the BFS ordering", "[weight=0][part=1][part=1b]") {
  PNG png(40, 40);
  Point startPoint(20, 20);
  BFS bfs(png, startPoint, 0.2);

  bfs.add( Point(2, 2) );
  bfs.add( Point(2, 3) );
  bfs.add( Point(2, 4) );

  REQUIRE( bfs.pop() == Point(20, 20) );
  REQUIRE( bfs.pop() == Point(2, 2) );
  REQUIRE( bfs.pop() == Point(2, 3) );
  REQUIRE( bfs.pop() == Point(2, 4) );
}



  // std::list<int> ints = {1, 2, 4, 8, 16};
  
  // int sum = 0;
	// for (auto it = ints.begin(); it != ints.end(); it++)
	// 	sum += *it;
	// std::cout << "Sum of ints: " << sum << "\n";

  // auto a = ints.begin();
  // ints.pop_front();
  // ints.pop_front();
  // ints.push_front(7);

	// for (auto it = ints.begin(); it != ints.end(); it++)
  //   std::cout<< *it << " ho"<<std::endl;

  // a++;
  // a++;
  // std::cout<< *a << " hip"<<std::endl;

  // sum = 0;
  // int i = 0;
	// for (auto it = ints.begin(); it != ints.end(); it++) {
	// 	sum += *it;
  //   i++;
  //   std::cout<< i <<" hi" <<std::endl;
  //   if (i == 2) 
  //     ints.push_back(7);
  // }



	// for (auto it = ints.begin(); it != ints.end(); it++)
  //   std::cout<< *it << " ho"<<std::endl;

	// std::cout << "Sum of ints: " << sum << "\n";