// created and worked on by Ruihan Weng, Raiden Saunders, and Federico Camargo Balaguera

#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <vector>
#include "Header/gui_window.h"

using namespace std;

vector<string> getMaze(const string& filepath) {
  ifstream inputFile(filepath);
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
  string filename;
  cout << "Enter the name of the maze file (e.g., perfectMazes/maze0.txt): ";
  getline(cin, filename);

  ifstream testFile(filename);
  if (!testFile.is_open()) {
    cerr << "Error: Could not open '" << filename<< "'\n";
    return 1;
  }
  testFile.close(); // We only checked for existence

  vector<string> maze = getMaze(filename);
  launchGUI(maze);

  return 0;
}