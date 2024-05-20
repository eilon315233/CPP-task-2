// ID: 315233486
// Email: eilonashwal30@gmail.com

#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector>
#include <iostream>
#include <utility>
using namespace std;

namespace ariel
{
    class Graph
    {
       private:
        vector<vector<int>> adjacencyMatrix; // The adjacency matrix of the graph
        bool directed; // Check if the graph is directed

       public:
        void loadGraph(vector<vector<int>> adjMatrix); // Load the graph to the object.

        string printGraph(); // Print the number of vertices and edges in the graph.
        
        size_t getNumberOfEdges(); // Get the number of edges in the graph.

        int getWeight(int start, int end); // Get the weight of an edge.

        vector<size_t> getNeighbors(size_t vertex); // Get the neighbors of a vertex.

        bool isDirected(); // Check if the graph is directed.

        size_t getNumberOfVertices(); // Get the number of nodes in the graph.

        vector<vector<int>> getMatrix() const {return adjacencyMatrix;} // Get the adjacency matrix of the graph.(inlined)
        
        vector<pair<int,pair<int, int>>> getEdges() const; // Get the edges of the graph.(inlined)

        bool isEdge(size_t from, size_t to) { return adjacencyMatrix[from][to] != 0;} // Check if there is an edge between two vertices.(inlined)

        vector<vector<int>> getMatrix() { return adjacencyMatrix;} // Get the adjacency matrix of the graph.(inlined)

        bool hasNegativeWeight(); // Check if the graph has a negative weight.
        
        void setDirect(bool directed); // Set the graph to be directed or not.

        int getEdge(unsigned int s, unsigned int t); // Get the weight of an edge.

        unsigned int getNumV() const{ return adjacencyMatrix.size(); } // Get the number of vertices in the graph.(inlined)


        // Arithmetic operators
        Graph operator+( Graph &g); // Aadd two matrices.
        Graph operator+=( Graph &g); // add two matrices.
        Graph operator+() ; // Unary plus operator. 
        Graph operator-( Graph &g); // Subtract two matrices.
        Graph operator-=( Graph &g); // Subtract two matrices.
        Graph operator-() ; // Unary minus operator.

        //comparison operators
        bool operator==( Graph &g); // Check if two matrices are equal.
        bool operator!=( Graph &g); // Check if two matrices are not equal.
        bool operator<( Graph &g); // Check if the first matrix is less than the second matrix.
        bool operator<=( Graph &g); // Check if the first matrix is less than or equal to the second matrix.
        bool operator>( Graph &g); // Check if the first matrix is greater than the second matrix.
        bool operator>=( Graph &g); // Check if the first matrix is greater than or equal to the second matrix.

        // Assignment operators
        Graph operator++(); // increment operator (before the variable)
        Graph operator++(int); // increment operator (after the variable)
        Graph operator--(); // decrement operator (before the variable)
        Graph operator--(int); // decrement operator (after the variable)

        // Multiplication operators
        Graph operator*(int scalar); // Multiply a matrix by a scalar.
        Graph operator*=( int scalar); // Multiply a matrix by a scalar and assign the result to the matrix.
        Graph operator*( Graph &g); // Multiply two matrices.
        Graph operator*=( Graph &g); // Multiply two matrices and assign the result to the matrix.

        // Division operators
        Graph operator/(int scalar); // Divide a matrix by a scalar.
        Graph operator/=(int scalar); // Divide a matrix by a scalar and assign the result to the matrix.
        Graph operator/( Graph &g); // Divide two matrices.
        Graph operator/=( Graph &g); // Divide two matrices and assign the result to the matrix.

        // friend functions
        friend ostream& operator<<(ostream &out,Graph &g); // Print the matrix.
        friend istream& operator>>(istream &in, Graph &g); // Read the matrix.
        friend Graph operator*(int scalar, Graph &g); // Multiply a matrix by a scalar.
        friend Graph operator/(int scalar, Graph &g); // Divide a matrix by a scalar.
        
    };    
}

#endif // GRAPH_HPP
