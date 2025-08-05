Project 3:
Our project is based on the algorithms A* and Dijkstra, and compares their speed in determining the shortest path between two points. 

Instructions:
To run the code, pull the repository and run it in CLion.
1. After running the code, it should ask for the filepath for any of the mazes.
2. Look at any of the mazes inside cmake-build-debug and give it a filepath based on the maze you want
  -The mazes are stored as txt files, 1 stands for a wall, 0 stands for open space
  -There are two types of mazes, imperfect (has loops) and perfect (only one true path). They are in the imperfectMazes folder and the perfectMazes folder
  -EXAMPLE INPUT: perfectMazes/maze0_dim42.txt or imperfectMazes/maze0_dim52.txt
3. Wait a few seconds for the path to be determined; it might take up to 10+ seconds since Dijkstra can be slow
   -Do not worry about the unresponsive window; it will load
   -The walls are red, the open space is white, and the path is blue
5. Done! 
