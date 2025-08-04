#include "SFML/Graphics.hpp"
#include <chrono>
#include "../Header/gui_window.h"
#include "../Header/ShortestPath.h"

using namespace std;

const int width = 1000;
const int height = 1000;

void drawMaze(sf::RenderWindow& window,
            const vector<string>& maze,
            const vector<pair<int, int>>& path,
            int tileSize,
            int offsetX,
            int offsetY,
            sf::Font& font,
            double timeD,
            double timeAstar)
{
    int rows = maze.size();
    int cols = maze[0].size();

    for (int y = 0; y < rows; y++){
        for (int x = 0; x < cols; x++) {
            sf::RectangleShape rect(sf::Vector2f(static_cast<float>(tileSize - 1),
                                                 static_cast<float>(tileSize - 1)));
            rect.setPosition(static_cast<float>(offsetX + x * tileSize),
                             static_cast<float>(offsetY + y * tileSize));

            if (maze[y][x] == '1'){
                rect.setFillColor(sf::Color::Red);
            } else{
                rect.setFillColor(sf::Color::White);
            }

            if (find(path.begin(), path.end(), make_pair(x, y)) != path.end()){
                rect.setFillColor(sf::Color::Blue);
            }

            window.draw(rect);
        }
    }

    // Draw timing panel background
    sf::RectangleShape panel(sf::Vector2f(static_cast<float>(width), 100.f));
    panel.setPosition(0.f, static_cast<float>(height - 100));
    panel.setFillColor(sf::Color(50, 50, 50));
    window.draw(panel);

    // Draw text
    sf::Text dijText, aStarText;
    dijText.setFont(font);
    dijText.setCharacterSize(18);
    dijText.setFillColor(sf::Color::White);
    dijText.setString("Dijkstra: " + to_string(timeD).substr(0, 5) + " ms");
    dijText.setPosition(20.f, static_cast<float>(height - 85));

    aStarText.setFont(font);
    aStarText.setCharacterSize(18);
    aStarText.setFillColor(sf::Color::White);
    aStarText.setString("A*: " + to_string(timeAstar).substr(0, 5) + " ms");
    aStarText.setPosition(20.f, static_cast<float>(height - 50));

    window.draw(dijText);
    window.draw(aStarText);
}

// Actually renders and launches GUI

void launchGUI(const vector<string>& maze){
    int rows = maze.size();
    int cols = maze[0].size();
    int tileSize = 7; // for fixed resolution of tiles

    int mazeW = cols * tileSize; // maze width
    int mazeH = rows * tileSize; // mase height
    int offsetX = (width - mazeW)/2;
    int offsetY = (width - 100 - mazeH)/2;

    sf::RenderWindow window(sf::VideoMode(width, height), "Maze Visualizer");
    sf::Font font;
    if (!font.loadFromFile("Roboto-VariableFont_wdth,wght.ttf")){
        cerr << "Failed to load font\n";
        return;
    }

    pair<int, int> start = {1, 1};
    pair<int, int> end = {cols -2, rows -2};

    ShortestPath sp(maze);

    auto t1 = chrono::high_resolution_clock::now();
    vector<pair<int, int>> dPath = sp.dijkstra(start, end);
    auto t2 = chrono::high_resolution_clock::now();
    double timeD = chrono::duration<double, milli>(t2 - t1).count();

    auto t3 = chrono::high_resolution_clock::now();
    vector<pair<int, int>> aPath = sp.AStar(start, end);
    auto t4 = chrono::high_resolution_clock::now();
    double timeAstar = chrono::duration<double, milli>(t4 - t3).count();

    // GUI main loop
    while (window.isOpen()){
        sf::Event event;
        while(window.pollEvent(event)){
            if (event.type == sf::Event::Closed) window.close();
        }

        window.clear();
        drawMaze(window, maze, dPath, tileSize, offsetX, offsetY, font, timeD, timeAstar);
        window.display();
    }
}