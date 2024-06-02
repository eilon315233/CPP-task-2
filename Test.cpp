// ID: 315233486
// Email: eilonashwal30@gmail.com

#include "doctest.h"
#include "Algorithms.hpp"
#include "Graph.hpp"

using namespace std;
using namespace ariel;

TEST_CASE("Test graph addition") // g1 = g2 + g3
{
    ariel::Graph g1;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(graph);
    ariel::Graph g2;
    vector<vector<int>> weightedGraph = {
        {0, 1, 1},
        {1, 0, 2},
        {1, 2, 0}};
    g2.loadGraph(weightedGraph);
    ariel::Graph g3 = g1 + g2;
    vector<vector<int>> expectedGraph = {
        {0, 2, 1},
        {2, 0, 3},
        {1, 3, 0}};
    CHECK(g3.printGraph() == "[0, 2, 1]\n[2, 0, 3]\n[1, 3, 0]");

    Graph g4;
    vector<vector<int>> graph2 = {
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0}};
    g4.loadGraph(graph2);
    Graph g5 = g1 + g4;
    CHECK(g5.printGraph() == "[0, 1, 0]\n[1, 0, 1]\n[0, 1, 0]");

    Graph g6;
    vector<vector<int>> graph3 = {
        {0, -1, 0},
        {-1, 0, -1},
        {0, -1, 0}};
    g6.loadGraph(graph3);
    Graph g7 = g1 + g6;
    CHECK(g7.printGraph() == "[0, 0, 0]\n[0, 0, 0]\n[0, 0, 0]");

    // Test algorithms on the g3
    CHECK(g3.isDirected() == false);
    CHECK(ariel::Algorithms::isConnected(g3) == true);
    CHECK(ariel::Algorithms::isContainsCycle(g3) == true);
    CHECK(ariel::Algorithms::isBipartite(g3) == "0");
    CHECK(ariel::Algorithms::shortestPath(g3, 1, 2) == "1->2");
}

TEST_CASE("Test graph += operator") // g1 += g2
{
    ariel::Graph g1;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(graph);
    ariel::Graph g2;
    vector<vector<int>> weightedGraph = {
        {0, 1, 1},
        {1, 0, 2},
        {1, 2, 0}};
    g2.loadGraph(weightedGraph);
    g1 += g2;
    vector<vector<int>> expectedGraph = {
        {0, 2, 1},
        {2, 0, 3},
        {1, 3, 0}};
    CHECK(g1.printGraph() == "[0, 2, 1]\n[2, 0, 3]\n[1, 3, 0]");
}

TEST_CASE("Test graph addition of different sizes")
{
    ariel::Graph g1;
    vector<vector<int>> graph1 = {
        {0, 1},
        {1, 0}};
    g1.loadGraph(graph1);
    ariel::Graph g2;
    vector<vector<int>> graph2 = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g2.loadGraph(graph2);
    CHECK_THROWS(g1 + g2);
}

TEST_CASE("Test graph addition of weighted and unweighted graphs")
{
    ariel::Graph g1;
    vector<vector<int>> graph1 = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(graph1);
    ariel::Graph g2;
    vector<vector<int>> graph2 = {
        {0, 3, 0},
        {3, 0, 3},
        {0, 3, 0}};
    g2.loadGraph(graph2);
    ariel::Graph g3 = g1 + g2;
    CHECK(g3.printGraph() == "[0, 4, 0]\n[4, 0, 4]\n[0, 4, 0]");
}

TEST_CASE("Test operations with single vertex graphs")
{
    ariel::Graph g1;
    vector<vector<int>> graph = {{0}};
    g1.loadGraph(graph);
    ariel::Graph g2 = g1 + g1;
    CHECK(g2.printGraph() == "[0]");
    g2 = g1 * g1;
    CHECK(g2.printGraph() == "[0]");
}

TEST_CASE("Test operations with disconnected graphs")
{
    ariel::Graph g1;
    vector<vector<int>> graph = {
        {0, 1, 0, 0},
        {1, 0, 0, 0},
        {0, 0, 0, 1},
        {0, 0, 1, 0}};
    g1.loadGraph(graph);
    ariel::Graph g2 = g1 + g1;
    vector<vector<int>> expectedGraph = {
        {0, 2, 0, 0},
        {2, 0, 0, 0},
        {0, 0, 0, 2},
        {0, 0, 2, 0}};
    CHECK(g2.printGraph() == "[0, 2, 0, 0]\n[2, 0, 0, 0]\n[0, 0, 0, 2]\n[0, 0, 2, 0]");
}

TEST_CASE("Test graph self-addition and self-subtraction")
{
    ariel::Graph g1;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(graph);
    ariel::Graph g2 = g1 + g1;
    CHECK(g2.printGraph() == "[0, 2, 0]\n[2, 0, 2]\n[0, 2, 0]");
    ariel::Graph g3 = g1 - g1;
    CHECK(g3.printGraph() == "[0, 0, 0]\n[0, 0, 0]\n[0, 0, 0]");
}

// Multiplication-related tests
TEST_CASE("Test graph multiplication") // g1 = g2 * g3
{
    ariel::Graph g1;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(graph);
    ariel::Graph g2;
    vector<vector<int>> weightedGraph = {
        {0, 1, 1},
        {1, 0, 2},
        {1, 2, 0}};
    g2.loadGraph(weightedGraph);
    ariel::Graph g4 = g1 * g2;
    vector<vector<int>> expectedGraph = {
        {0, 0, 2},
        {1, 0, 1},
        {1, 0, 0}};
    CHECK(g4.printGraph() == "[0, 0, 2]\n[1, 0, 1]\n[1, 0, 0]");

    ariel::Graph g5;
    vector<vector<int>> graph2 = {
        {0, 1, 2, 0},
        {3, 0, 1, 0},
        {0, 0, 0, 4},
        {0, 0, 2, 0}};
    g5.loadGraph(graph2);
    ariel::Graph g6;
    vector<vector<int>> graph3 = {
        {0, 1, 3, 0},
        {1, 0, 1, 2},
        {1, 1, 0, 1},
        {4, 0, 1, 0}};
    g6.loadGraph(graph3);
    ariel::Graph g7 = g5 * g6;
    vector<vector<int>> expectedGraph2 = {
        {0, 2, 1, 4},
        {1, 0, 9, 1},
        {16, 0, 0, 0},
        {2, 2, 0, 0}};
    CHECK(g7.printGraph() == "[0, 2, 1, 4]\n[1, 0, 9, 1]\n[16, 0, 0, 0]\n[2, 2, 0, 0]");
}

TEST_CASE("Test graph multiplication by scalar") // g1 = g2 * 2
{
    ariel::Graph g1;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(graph);
    ariel::Graph g2 = g1 * 2;
    CHECK(g2.printGraph() == "[0, 2, 0]\n[2, 0, 2]\n[0, 2, 0]");
    g2 *= 2;
    CHECK(g2.printGraph() == "[0, 4, 0]\n[4, 0, 4]\n[0, 4, 0]");

    ariel::Graph g3 = g1 * 0;
    CHECK(g3.printGraph() == "[0, 0, 0]\n[0, 0, 0]\n[0, 0, 0]");
}

TEST_CASE("Test graph multiplication of different sizes")
{
    ariel::Graph g1;
    vector<vector<int>> graph1 = {
        {0, 1},
        {1, 0}};
    g1.loadGraph(graph1);
    ariel::Graph g2;
    vector<vector<int>> graph2 = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g2.loadGraph(graph2);
    CHECK_THROWS(g1 * g2);
}

TEST_CASE("Test graph scalar multiplication by zero")
{
    ariel::Graph g1;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(graph);
    ariel::Graph g2 = g1 * 0;
    CHECK(g2.printGraph() == "[0, 0, 0]\n[0, 0, 0]\n[0, 0, 0]");
}

TEST_CASE("Test operations with a complete graph")
{
    ariel::Graph g1;
    vector<vector<int>> graph = {
        {0, 1, 1},
        {1, 0, 1},
        {1, 1, 0}};
    g1.loadGraph(graph);
    ariel::Graph g2 = g1 * 2;
    CHECK(g2.printGraph() == "[0, 2, 2]\n[2, 0, 2]\n[2, 2, 0]");
}

// Invalid operations
TEST_CASE("Invalid operations")
{
    ariel::Graph g1;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(graph);
    ariel::Graph g2;
    vector<vector<int>> weightedGraph = {
        {0, 1, 1, 1},
        {1, 0, 2, 1},
        {1, 2, 0, 1},
        {1, 1, 1, 0}};
    g2.loadGraph(weightedGraph);
    ariel::Graph g5;
    vector<vector<int>> graph2 = {
        {0, 1, 0, 0, 1},
        {1, 0, 1, 0, 0},
        {0, 1, 0, 1, 0},
        {0, 0, 1, 0, 1},
        {1, 0, 0, 1, 0}};
    g5.loadGraph(graph2);
    CHECK_THROWS(g5 * g1);
    CHECK_THROWS(g1 * g2);

    // Addition of two graphs with different dimensions
    ariel::Graph g6;
    vector<vector<int>> graph3 = {
        {0, 1, 0, 0, 1},
        {1, 0, 1, 0, 0},
        {0, 1, 0, 1, 0},
        {0, 0, 1, 0, 1},
        {1, 0, 0, 1, 0}};
    g6.loadGraph(graph3);
    CHECK_THROWS(g1 + g6);

    // Subtraction of two graphs with different dimensions
    ariel::Graph g7;
    vector<vector<int>> graph4 = {
        {0, 2, 0, 0},
        {2, 0, 2, 0},
        {0, 2, 0, 2},
        {0, 0, 2, 0}};
    g7.loadGraph(graph4);
    CHECK_THROWS(g1 - g7);
}

TEST_CASE("Test invalid graph arithmetic operations")
{
    ariel::Graph g1;
    vector<vector<int>> graph1 = {
        {0, 1},
        {1, 0}};
    g1.loadGraph(graph1);
    ariel::Graph g2;
    vector<vector<int>> graph2 = {
        {0, 1, 1},
        {1, 0, 1},
        {1, 1, 0}};
    g2.loadGraph(graph2);
    CHECK_THROWS(g1 * g2);
}

// Increment and decrement operators
TEST_CASE("Test graph increment and decrement operators") // g1 = g2++
{
    ariel::Graph g1;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(graph);
    ariel::Graph g2;
    vector<vector<int>> weightedGraph = {
        {0, 1, 1},
        {1, 0, 2},
        {1, 2, 0}};
    g2.loadGraph(weightedGraph);
    ariel::Graph g3 = g2++;
    CHECK(g3.printGraph() == "[0, 1, 1]\n[1, 0, 2]\n[1, 2, 0]");
    CHECK(g2.printGraph() == "[0, 2, 2]\n[2, 0, 3]\n[2, 3, 0]");
    ariel::Graph g4 = g2--;
    CHECK(g4.printGraph() == "[0, 2, 2]\n[2, 0, 3]\n[2, 3, 0]");
    CHECK(g2.printGraph() == "[0, 1, 1]\n[1, 0, 2]\n[1, 2, 0]");
}

TEST_CASE("Test graph ++g --g operators") // g1 = ++g2
{
    ariel::Graph g1;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(graph);
    ariel::Graph g2;
    vector<vector<int>> weightedGraph = {
        {0, 1, 1},
        {1, 0, 2},
        {1, 2, 0}};
    g2.loadGraph(weightedGraph);
    ariel::Graph g3 = ++g2;
    CHECK(g3.printGraph() == "[0, 2, 2]\n[2, 0, 3]\n[2, 3, 0]");
    CHECK(g2.printGraph() == "[0, 2, 2]\n[2, 0, 3]\n[2, 3, 0]");
    ariel::Graph g4 = --g2;
    CHECK(g4.printGraph() == "[0, 1, 1]\n[1, 0, 2]\n[1, 2, 0]");
    CHECK(g2.printGraph() == "[0, 1, 1]\n[1, 0, 2]\n[1, 2, 0]");
}

TEST_CASE("Testing devrement prefix and postfix with algorithm")
{
    ariel::Graph g1;
    vector<vector<int>> graph = {
        {0, -8, 1, -1, 0},
        {1, 0, -7, 1, 4},
        {-10, 1, 0, 6, 0},
        {1, 0, 4, 0, 2},
        {9, 1, -2, 3, 0}};
    g1.loadGraph(graph);
    ariel::Graph g2 = g1--;

    CHECK(ariel::Algorithms::isConnected(g2) == true);
    CHECK(ariel::Algorithms::isContainsCycle(g2) == true);
    CHECK(ariel::Algorithms::isBipartite(g2) == "0");
    CHECK(ariel::Algorithms::shortestPath(g2, 4, 2) == "The graph contains a negative cycle");
    CHECK(ariel::Algorithms::negativeCycle(g2) == "The cycle is: 0->1->2->0");

    vector<vector<int>> graph2 = {
        {0, -9, 0, -2, 0},
        {0, 0, -8, 0, 3},
        {-11, 0, 0, 5, 0},
        {0, 0, 3, 0, 1},
        {8, 0, -3, 2, 0}};
    ariel::Graph g3;
    g3.loadGraph(graph2);
    ariel::Graph g4;
    g4.loadGraph(graph);

    CHECK((g3 == g1) == true);
    CHECK((g2 == g4) == true);

    ariel::Graph g5 = --g1;
    vector<vector<int>> graph3 = {
        {0, -10, 0, -3, 0},
        {0, 0, -9, 0, 2},
        {-12, 0, 0, 4, 0},
        {0, 0, 2, 0, 0},
        {7, 0, -4, 1, 0}};
    ariel::Graph g6;
    g6.loadGraph(graph3);

    CHECK((g5 == g6) == true);
    CHECK((g1 != g3) == true); // g1 changed

    CHECK(ariel::Algorithms::isConnected(g5) == true);
    CHECK(ariel::Algorithms::isContainsCycle(g5) == true);
    CHECK(ariel::Algorithms::isBipartite(g5) == "0");
    CHECK(ariel::Algorithms::shortestPath(g5, 1, 2) == "The graph contains a negative cycle");
    CHECK(ariel::Algorithms::shortestPath(g5, 4, 2) == "The graph contains a negative cycle");
    CHECK(ariel::Algorithms::negativeCycle(g5) == "The cycle is: 0->1->2->0");
}

// Scalar operations
TEST_CASE("Test graph division by scalar") // g1 = g2 / 2
{
    ariel::Graph g1;
    vector<vector<int>> graph = {
        {0, 2, 0},
        {2, 0, 2},
        {0, 2, 0}};
    g1.loadGraph(graph);
    ariel::Graph g2 = g1 / 2;
    CHECK(g2.printGraph() == "[0, 1, 0]\n[1, 0, 1]\n[0, 1, 0]");
    g2 /= 2;
    CHECK(g2.printGraph() == "[0, 0, 0]\n[0, 0, 0]\n[0, 0, 0]");
    CHECK_THROWS(g1 / 0);
    CHECK_THROWS(g2 /= 0);
}

TEST_CASE("Test graph division by negative scalar")
{
    ariel::Graph g1;
    vector<vector<int>> graph = {
        {0, 2, 0},
        {2, 0, 2},
        {0, 2, 0}};
    g1.loadGraph(graph);
    ariel::Graph g2 = g1 / -2;
    CHECK(g2.printGraph() == "[0, -1, 0]\n[-1, 0, -1]\n[0, -1, 0]");
}

TEST_CASE("Test operations with graphs containing negative weights")
{
    ariel::Graph g1;
    vector<vector<int>> graph = {
        {0, -1, 0},
        {-1, 0, -1},
        {0, -1, 0}};
    g1.loadGraph(graph);
    ariel::Graph g2 = g1 + g1;
    CHECK(g2.printGraph() == "[0, -2, 0]\n[-2, 0, -2]\n[0, -2, 0]");
    ariel::Graph g3 = g1 * 2;
    CHECK(g3.printGraph() == "[0, -2, 0]\n[-2, 0, -2]\n[0, -2, 0]");
}

TEST_CASE("Test operations with sparse graphs")
{
    ariel::Graph g1;
    vector<vector<int>> sparseGraph = {
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}};
    g1.loadGraph(sparseGraph);
    ariel::Graph g2 = g1 + g1;
    CHECK(g2.printGraph() == "[0, 0, 0, 0]\n[0, 0, 0, 0]\n[0, 0, 0, 0]\n[0, 0, 0, 0]");
}

// Unary operations
TEST_CASE("Test graph + unary") // g1 = +g2
{
    ariel::Graph g1;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(graph);
    ariel::Graph g2 = +g1;
    CHECK(g2.printGraph() == "[0, 1, 0]\n[1, 0, 1]\n[0, 1, 0]");
}

TEST_CASE("Test graph - unary") // g1 = -g2
{
    ariel::Graph g1;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(graph);
    ariel::Graph g2 = -g1;
    CHECK(g2.printGraph() == "[0, -1, 0]\n[-1, 0, -1]\n[0, -1, 0]");
}

// Comparison operations
TEST_CASE("Test graph comparison operators") // compare g1 and g2
{
    ariel::Graph g1;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(graph);
    ariel::Graph g2;
    vector<vector<int>> weightedGraph = {
        {0, 1, 1},
        {1, 0, 2},
        {1, 2, 0}};
    g2.loadGraph(weightedGraph);
    ariel::Graph g3;
    vector<vector<int>> weightedGraph2 = {
        {0, 1, 1},
        {1, 0, 2},
        {1, 2, 0}};
    g3.loadGraph(weightedGraph2);
    CHECK(g1 == g1);
    CHECK(g2 == g3);
    CHECK(g1 != g2);
    CHECK(g1 < g2);
    CHECK(g1 <= g2);
    CHECK(g2 > g1);
    CHECK(g2 >= g1);
}

TEST_CASE("Test graph equality with different structures but same values")
{
    ariel::Graph g1;
    vector<vector<int>> graph1 = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(graph1);
    ariel::Graph g2;
    vector<vector<int>> graph2 = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g2.loadGraph(graph2);
    CHECK(g1 == g2);
}

// Miscellaneous
TEST_CASE("Test graph with directed edges")
{
    ariel::Graph g1;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {0, 0, 1},
        {0, 0, 0}};
    g1.loadGraph(graph);
    CHECK(g1.printGraph() == "[0, 1, 0]\n[0, 0, 1]\n[0, 0, 0]");
}

TEST_CASE("Test graph with varying edge weights")
{
    ariel::Graph g1;
    vector<vector<int>> graph = {
        {0, 1, -1},
        {1, 0, 2},
        {-1, 2, 0}};
    g1.loadGraph(graph);
    ariel::Graph g2 = g1 * 2;
    CHECK(g2.printGraph() == "[0, 2, -2]\n[2, 0, 4]\n[-2, 4, 0]");
    g2 /= 2;
    CHECK(g2.printGraph() == "[0, 1, -1]\n[1, 0, 2]\n[-1, 2, 0]");
}

TEST_CASE("Test operations with weighted edges")
{
    ariel::Graph g1;
    vector<vector<int>> graph = {
        {0, 3, 0},
        {3, 0, 4},
        {0, 4, 0}};
    g1.loadGraph(graph);
    ariel::Graph g2 = g1 * 2;
    CHECK(g2.printGraph() == "[0, 6, 0]\n[6, 0, 8]\n[0, 8, 0]");
    g2 /= 2;
    CHECK(g2.printGraph() == "[0, 3, 0]\n[3, 0, 4]\n[0, 4, 0]");
}
