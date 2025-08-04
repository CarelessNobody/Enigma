#include <fstream>
#include <sstream>
#include <iostream>
#include <utility>
#include <vector>
#include <ranges>
#include "Header/ShortestPath.h"

using namespace std;

vector<string> getMaze(string filename) {
  ifstream inputFile(filename);

  vector<string> maze;
  string line;

  while (getline(inputFile, line)) {
    stringstream ss(line);
    char val;
    string row = "";
    while (ss >> val) {
      row += val;
    }
    if (!row.empty())
      maze.push_back(row);

  }
  inputFile.close();

  return maze;
}


int main() {
  vector<string> maze = getMaze("test.txt");
  ShortestPath algorithm = ShortestPath(maze);

  //Should return no path if starting point is a wall, there is no path, or start and end are the same
  //Requires valid m x n graph and start and ending point inside graph
  algorithm.printDijkstra({0,0} , {1,1});
  algorithm.printAStar({0,0} , {1,1});
}


