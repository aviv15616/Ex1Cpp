# Ex1-C++

## Author
Aviv Neeman  
Email: anksilae@gmail.com

## Overview

This project implements an undirected graph using an **adjacency list** in C++, strictly without using the STL (no `vector`, `stack`, etc.).  
The focus is on manual memory management, algorithm design, and building supporting data structures from scratch.

The project includes the following components:

- **Graph** – Represents an undirected graph using a linked list–based adjacency list. Supports operations like `addEdge`, `removeEdge`, and `printGraph`. The number of vertices is fixed upon graph creation.
  
- **Algorithms** – Contains static methods implementing classical graph algorithms:
  - `bfs(Graph& g, int start)` – Performs a **Breadth-First Search** from a given start node and returns a **directed rooted tree** representing the BFS traversal. The edges are directed to reflect the parent-to-child relationship.
  - `dfs(Graph& g, int start)` – Performs a **Depth-First Search**, returning a **directed rooted tree (or forest)** that includes only **tree edges**, showing the DFS traversal structure.
  - `dijkstra(Graph& g, int start)` – Computes **shortest paths** from the start node using Dijkstra's algorithm. Returns a **directed tree** rooted at the start node with the minimal-weight paths to each reachable vertex.
  - `prim(Graph& g, int start)` – Computes a **Minimum Spanning Tree** using Prim's algorithm. The result is an **undirected** tree connecting all vertices with minimal total weight.
  - `kruskal(Graph& g)` – Computes a **Minimum Spanning Tree** using Kruskal’s algorithm, based on a Union-Find structure to detect cycles.

- **Data Structures** – The following basic data structures were implemented without STL:
  - `Queue` – For BFS
  - `PriorityQueue` – For Dijkstra and Prim (min-heap based)
  - `UnionFind` – For Kruskal’s algorithm (union by rank and path compression)

- **Memory Management** – All memory allocations are managed with raw pointers. Copy constructors and destructors are carefully implemented to avoid memory leaks. Verified with `valgrind`.

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
