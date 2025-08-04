//
// Created by weng2 on 8/3/2025.
//

#ifndef SHORTESTPATH_H
#define SHORTESTPATH_H

#include <algorithm>
#include <fstream>
#include <sstream>
#include <iostream>
#include <utility>
#include <vector>
#include <set>
#include <climits>
#include <unordered_map>
#include <math.h>
#include <ranges>
#include <valarray>

using namespace std;

class ShortestPath {
    vector<string> graph;

    void init(set<pair<int, int> > &s, vector<string> &graph) {
        //Initialize set with locations to visit
        for (int i = 0; i < graph.size(); i++) {
            for (int j = 0; j < graph[0].length(); j++) {
                if (graph[i][j] != '1') //Not including walls
                    s.insert({j, i});
            }
        }
    }

    int convertToIndex(pair<int, int> location, vector<string> &graph) {
        //Turns (x,y) into an index for 1D vector
        return (location.second * graph[0].length()) + location.first;
    }

    float calcDistance(pair<int, int> start, pair<int, int> end) {
        //The heuristic
        return sqrt(pow(end.first - start.first, 2) + pow(end.second - start.second, 2)); //Just pythagorean theorem
    }

public:
    ShortestPath(vector<string> &graph) : graph(graph) {}

    vector<pair<int, int> > dijkstra(pair<int, int> start, pair<int, int> end) {
        if (graph[start.second][start.first] == '1' || graph[end.second][end.first] == '1')
            return {};

        //Set up
        pair<int, int> location; //x, y
        set<pair<int, int> > visited;
        set<pair<int, int> > pendingVisit;

        init(pendingVisit, graph);

        int graphSize = graph.size() * graph[0].length();
        vector<int> distance(graphSize, INT_MAX - 1); //To prevent overflow
        vector<pair<int, int> > predecessor(graphSize, {-1, -1});

        distance[convertToIndex(start, graph)] = 0;

        while (!pendingVisit.empty()) {
            location = {-1, -1};

            //Find the smallest distance still in pendingVisit to put into location
            for (auto p: pendingVisit) {
                int x = p.first;
                int y = p.second;
                int index = convertToIndex({x, y}, graph);
                int currIndex = convertToIndex(location, graph);
                if (location == pair{-1, -1} || distance[index] < distance[currIndex])
                    location = {x, y};
            }

            pendingVisit.erase(location);
            visited.insert(location);

            //Get adjacent
            set<pair<int, int> > adj;
            if (location.second != 0)
                adj.insert({location.first, location.second - 1}); //Top
            if (location.second != graph.size() - 1)
                adj.insert({location.first, location.second + 1}); //Down
            if (location.first != 0)
                adj.insert({location.first - 1, location.second}); //Left
            if (location.first != graph[location.second].size() - 1)
                adj.insert({location.first + 1, location.second}); //Right

            for (auto p: adj) {
                if (graph[p.second][p.first] == '1')
                    continue; //Ignoring invalid spaces to go

                //Finding the shortest path to adj
                int index = convertToIndex(p, graph);
                int currIndex = convertToIndex(location, graph);

                if (distance[currIndex] + 1 < distance[index]) {
                    distance[index] = distance[currIndex] + 1;
                    predecessor[index] = location;
                }
            }
        }

        vector<pair<int, int> > path;
        path.push_back(end); //To include the end point in the path to itself

        int i = convertToIndex(end, graph);
        while (predecessor[i] != pair<int, int>{-1, -1}) {
            //Only starting node will have this predecessor
            //Construct path from predecessor l
            path.push_back(predecessor[i]);
            i = convertToIndex(predecessor[i], graph);
        }

        if (path.size() == 1)
            return {}; //We didn't find a path

        ranges::reverse(path); //Otherwise it will go in reverse from end to start
        return path;
    }

    vector<pair<int, int> > AStar(pair<int, int> start, pair<int, int> end) {
        if (graph[start.second][start.first] == '1' || graph[end.second][end.first] == '1' || start == end)
            return {};

        set<pair<int, int> > openSet; //To be visited
        set<pair<int, int> > closedSet; //Visited
        unordered_map<int, pair<int, int> > parent;
        //Key has to be an int since I will have to provide hash func otherwise
        //key is child, parent is val
        vector<pair<int, int> > path; //Path

        openSet.insert(start);

        while (!openSet.empty()) {
            pair location = {-1, -1}; //Finding location with the smallest cost
            for (auto p: openSet) {
                if (location == pair{-1, -1} ||
                    calcDistance(p, end) + calcDistance(start, p) < calcDistance(location, end) + calcDistance(
                        start, location))
                    location = {p.first, p.second};
            }

            closedSet.insert(location);
            openSet.erase(location);

            if (location == end) {
                //Found location, return path
                path.push_back(location);
                while (parent[convertToIndex(location, graph)] != start) {
                    location = parent[convertToIndex(location, graph)];
                    path.push_back(location);
                }
                path.push_back(start);

                reverse(path.begin(), path.end()); //To get it in the order from start to end
                return path;
            }

            //Get adjacent
            set<pair<int, int> > adj;
            if (location.second != 0)
                adj.insert({location.first, location.second - 1}); //Top
            if (location.second != graph.size() - 1)
                adj.insert({location.first, location.second + 1}); //Down
            if (location.first != 0)
                adj.insert({location.first - 1, location.second}); //Left
            if (location.first != graph[location.second].size() - 1)
                adj.insert({location.first + 1, location.second}); //Right

            for (auto p: adj) {
                if (closedSet.contains(p) || graph[p.second][p.first] == '1') //Already checked or a wall
                    continue;
                if (!openSet.contains(p)) {
                    //Needs to be checked
                    parent[convertToIndex(p, graph)] = location;
                    openSet.insert(p);
                }

                //Seeing if distance is shorter from start
                if (calcDistance(p, start) < calcDistance(location, start)) {
                    parent[convertToIndex(p, graph)] = location;
                }
            }
        }

        return {}; //No path found;
    }

    void printDijkstra(pair<int, int> start, pair<int, int> end) {
        vector<pair<int, int> > path = dijkstra(start, end);

        cout << "Dijkstra Path" << endl;
        for (auto p: path) {
            cout << p.first << ", " << p.second << endl;
        }
    }

    void printAStar(pair<int, int> start, pair<int, int> end) {
        vector<pair<int, int> > path = AStar(start, end);

        cout << "A* Path" << endl;
        for (auto p: path) {
            cout << p.first << ", " << p.second << endl;
        }
    }

    vector<string> getGraph() {
        return graph;
    }
};


#endif SHORTESTPATH_H
