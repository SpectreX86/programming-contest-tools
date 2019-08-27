# programming-contest-tools
tools for programming contests just for fun

- flow: tools for network flow algorithms.
  - EdmonsKarp.cpp: estimates the maximum flow in the network with Edmons-Karp algorithm.
  - FordFulkerson.cpp: estimates the maximum flow in the network with Ford-Fulkerson algorithm.
  - MaxFlowMinCost.cpp: estimates the minimum cost under the maximum flow in the network with Edmons-Karp+Dijkstra-like algorithm.
- graph: tools for algorithms involving graph.
  - DijkstraSparse.cpp: calculates the shortest path and its distance for sparse graph (a single start and a single goals).
  - BellmanFord.cpp: calculates the shortest paths and their distance (a single start and plural goals).
  - FloydWarshall.cpp: calculates the shortest paths and their distance (plural starts and plural goals).
  - Prim.cpp: calculates the minimim spanning tree of a graph.
- integer: tools for integer problems.
  - gcd.cpp: calculates gcd.
  - lcm.cpp: calculates lcm.
- modulo: tools for modulo operation.
  - inverse.cpp: calculates array of x^{-1}  modulo a prime m for x in [1, N] as compile time constant.
- print: tools for printing classes.
  - vector.cpp: prints a vector in a line.
- tree: tools for algorithms involving tree.
  - distance.cpp: calculates the distance of each node from the root.
  - parent.cpp: find the parents of each node.
