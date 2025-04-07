# Ex1-C++

## Author
Aviv Neeman  
Email: anksilae@gmail.com

## Overview

The project includes the following components:

- **Graph** – Represents an undirected graph using a linked list–based adjacency list. Supports operations like `addEdge`, `removeEdge`, and `printGraph`. The number of vertices is fixed upon graph creation.

- **Algorithms** – Contains static methods implementing classical graph algorithms from a given undirected graph:
  - **BFS** – Performs a **Breadth-First Search** from a given start node and returns a **directed rooted tree/forest** representing the BFS traversal. 
  - **DFS** – Performs a **Depth-First Search**, returning a **directed rooted tree/forest** that includes only **tree edges**, showing the DFS traversal structure.
  - **Dijkstra** – Computes **shortest paths** from the start node using Dijkstra's algorithm. Returns a **directed rooted tree** rooted at the start node with the minimal-weight paths to each reachable vertex.
  - **Prim** – Computes a **Minimum Spanning Tree** using Prim's algorithm. The result is an **undirected** MST.
  - **Kruskal** – Computes a **Minimum Spanning Tree** using Kruskal’s algorithm, The result is an **undirected** MST.

- **Data Structures** – The following basic data structures were implemented without STL:
  - `Queue` – For BFS
  - `Stack` - For DFS
  - `PriorityQueue` – For Dijkstra and Prim (min-heap based)
  - `UnionFind` – For Kruskal’s algorithm (union by rank and path compression)

- **Testing** – Comprehensive **unit tests** are written using the `doctest` framework to cover all functionality and edge cases.

- **Demo (main.cpp)** – Demonstrates how to build a graph, run each algorithm, and view the output via `printGraph()`. This includes how the tree structures are represented.

### Note on Directed Trees

Although the input graph is undirected, the graphs returned by `bfs`, `dfs`, and `dijkstra` are **directed**. This is done deliberately to represent **parent-child relationships** in the rooted trees that result from each algorithm. This approach also makes it easier to visualize and validate the traversal paths.


## Usage

- `make main` – Run demo
- `make test` – Run unit tests
- `make valgrind` – Run valgrind on main
- `make valgrind-test` – Run valgrind on tests
- `make clean` – Clean all build files
