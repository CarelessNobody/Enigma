// created by Raiden Saunders 08/04/25

#ifndef GUI_WINDOW_H
#define GUI_WINDOW_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

// Forward declare the ShortestPath class to avoid circular include
class ShortestPath;

// Constants for window size
extern const int width;
extern const int height;

// Draws the maze and overlays timing data
void drawMaze(sf::RenderWindow& window,
              const std::vector<std::string>& maze,
              const std::vector<std::pair<int, int>>& path,
              int tileSize,
              int offsetX,
              int offsetY,
              sf::Font& font,
              double timeD,
              double timeAstar);

// Launches the GUI and handles the rendering loop
void launchGUI(const std::vector<std::string>& maze);

#endif // GUI_WINDOW_H