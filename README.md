# Graph Assignment

## Author
Aviv Neeman  
Email: anksilae@gmail.com

## Overview
This project implements a graph using adjacency list without using STL.  
It includes standard graph algorithms: BFS, DFS, Dijkstra, Prim, Kruskal.

## Structure

- `Graph.hpp / Graph.cpp` – The Graph class and adjacency list logic
- `Algorithms.hpp / Algorithms.cpp` – Graph traversal and MST algorithms
- `Queue.hpp`, `PriorityQueue.hpp`, `UnionFind.hpp` – Custom data structures
- `main.cpp` – Demo of usage
- `tests/` – Unit tests using doctest
- `Makefile` – Build and run automation

## Usage

- `make main` – Run demo
- `make test` – Run unit tests
- `make valgrind` – Run valgrind on main
- `make valgrind-test` – Run valgrind on tests
- `make clean` – Clean all build files
