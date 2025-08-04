#include <fstream>
#include <sstream>
#include <iostream>
#include <utility>
#include <vector>
#include <ranges>
#include "Header/gui_window.h"

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
  string mazeFile = "maze0_dim42.txt";
  vector<string> maze = getMaze(mazeFile);
  launchGUI(maze);
  cout << "YOOOOOOOOOOOOOOOO";

  return 0;

  // //Should return no path if starting point is a wall, there is no path, or start and end are the same
  // //Requires valid m x n graph and start and ending point inside graph
  // algorithm.printDijkstra({0,0} , {1,1});
  // algorithm.printAStar({0,0} , {1,1});
}
