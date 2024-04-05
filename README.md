# Randomized Prim's
Prim's Algorithm is a graphing algorithm used to find Minimum Spanning Trees (MST). The algorithm starts by picking a given node in the graph, with which it begins the MST. It then finds the shortest edge from the MST to a node that is not in the MST, and adds that node. 
You can read more on Randomized Prim's algoirthm at: https://en.wikipedia.org/wiki/Maze_generation_algorithm

Screenshot of my implementation of Prim's
![gif](/docs/assets/gif1.gif)

# Implementation
In my implementation the black tiles repersent walls and the white tiles are the paths. The red tiles are the frontier cells and theses are the neighbouring cells to the paths, the frontier cells are the cells that are randomly picked to become passages and are connected with their a neighbouring cell.

![screenshot](/docs/assets/screenshot2.png)


# Development
Coded in c++ with SDL2 for rendering.
