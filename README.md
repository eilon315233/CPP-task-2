

# Graph Library and Algorithms
This project features a versatile Graph class along with a collection of advanced graph algorithms. Implemented in C++, it accommodates both directed and undirected graphs and can handle both weighted and unweighted edges.

Graph Class
Overview
The Graph class manages graphs using adjacency matrices. It provides functionalities to load, display, and manipulate graph properties effectively.

Functions
Constructor: Graph()

Initializes a new Graph instance.
loadGraph(std::vector<std::vector<int>> graph, bool directed)

Loads a graph from a square matrix, validates the input, and sets whether the graph is directed.
printGraph()

Returns a string representation of the adjacency matrix of the graph.
getEdgesCount()

Returns the number of edges, considering if the graph is directed or undirected.
getVerticesCount()

Returns the number of vertices, which corresponds to the dimensions of the adjacency matrix.
isWeighted()

Checks if the graph contains any weights other than 1 or -1, indicating it is weighted.
haveNegativeWeight()

Determines if there are any edges with negative weights.
getNeighbors(size_t vertex)

Lists all vertices that are directly connected by an edge to the specified vertex.
isDirected()

Indicates whether the graph is directed.
getWeight(size_t src, size_t dest)

Retrieves the weight of the edge between the specified vertices.
setDirect(bool directed)

Sets the graph to be directed or undirected, ensuring symmetry in the adjacency matrix for undirected graphs.
Operator Overloading
operator+ (const Graph &g1, const Graph &g2)
Adds the weights of corresponding edges of two graphs.
operator+= (const Graph &g)
Adds the weights of corresponding edges to the current graph.
operator- (const Graph &g1, const Graph &g2)
Subtracts the weights of corresponding edges of two graphs.
operator-= (const Graph &g)
Subtracts the weights of corresponding edges from the current graph.
operator (int scalar)*
Multiplies the weights of the graph by a scalar.
operator/ (int scalar)
Divides the weights of the graph by a scalar.
operator= (int scalar)*
Multiplies the weights of the graph by a scalar.
operator/= (int scalar)
Divides the weights of the graph by a scalar.
operator> (const Graph &g1, const Graph &g2)
Compares two graphs to check if the first graph has more edges or vertices than the second.
operator>= (const Graph &g1, const Graph &g2)
Compares two graphs to check if the first graph has more or equal edges or vertices than the second.
operator< (const Graph &g1, const Graph &g2)
Compares two graphs to check if the first graph has fewer edges or vertices than the second.
operator<= (const Graph &g1, const Graph &g2)
Compares two graphs to check if the first graph has fewer or equal edges or vertices than the second.
operator== (const Graph &g1, const Graph &g2)
Checks if two graphs are equal.
operator!= (const Graph &g1, const Graph &g2)
Checks if two graphs are not equal.
operator++ ()
Prefix increment operator to increase all edge weights by 1.
operator++ (int)
Postfix increment operator to increase all edge weights by 1.
operator-- ()
Prefix decrement operator to decrease all edge weights by 1.
operator-- (int)
Postfix decrement operator to decrease all edge weights by 1.
operator (const Graph &g) const*
Multiplies the adjacency matrices of two graphs.
operator<< (std::ostream &os, const Graph &g)
Outputs the graph's adjacency matrix to an output stream.
Graph Algorithms Library
Features
Connectivity Functions

isConnected(Graph graph)
For undirected graphs, checks if all nodes are reachable from any node using DFS.
For directed graphs, checks strong and weak connectivity by temporarily adjusting edge directions.
Bipartiteness Check

isBipartite(Graph &graph)
Uses BFS to determine if the graph can be two-colored, confirming it as bipartite and identifying vertex sets for each color.
Shortest Path Algorithms

shortestPath(Graph graph, size_t src, size_t dest)
Finds the shortest path using Dijkstra's algorithm for non-negative weights, Bellman-Ford for negative weights, and BFS for unweighted graphs.
Cycle Detection

isContainsCycle(Graph &graph)
Uses DFS to detect cycles, returning the cycle path if found.
Negative Cycle Detection

negativeCycle(Graph graph)
Employs a modified Bellman-Ford algorithm to detect negative weight cycles, important for the accuracy of certain shortest path algorithms.
