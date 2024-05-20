// ID: 315233486
// Email: eilonashwal30@gmail.com


#include "Graph.hpp"
#include <iostream>

using namespace ariel;
using namespace std;

// Load the graph to the object.
void Graph::loadGraph(vector<vector<int>> adjMatrix) 
{
    // Check if the graph is empty.
    if (adjMatrix.empty()) { throw invalid_argument("The graph is empty, please enter a new graph."); } 

    // Check if the graph is a square matrix.
    int size = adjMatrix.size();
    for (const auto& row : adjMatrix) 
    {
        if (row.size() != size) {
            throw std::invalid_argument("Invalid graph: The graph is not a square matrix.");
        }
    }

    // Check if the graph dont have a edge from a vertex to itself.
    for (size_t i = 0; i < adjMatrix.size(); ++i) 
    {
        if (adjMatrix[i][i] != 0) 
        {
            throw std::invalid_argument("Invalid graph: The graph has an edge from a vertex to itself.");
        }
    }

    //load the graph and check if it is directed
    this->adjacencyMatrix = adjMatrix;
    this->directed = isDirected();
}

// Print the number of vertices and edges in the graph and the graph itself.
string Graph::printGraph() 
{
    // Print the matrix like this: [1, 2, 3]\n[4, 5, 6]\n[7, 8, 9]
    string result = "";
    for (size_t i = 0; i < adjacencyMatrix.size(); ++i) 
    {
        if (i == 0) 
        {
            result += "[";
        } 
        else 
        {
            ///pass to the next line
            result += "\n[";
        }
        for (size_t j = 0; j < adjacencyMatrix[i].size(); ++j) 
        {
            if (j == adjacencyMatrix[i].size() - 1) 
            {
                result += to_string(adjacencyMatrix[i][j]);
            } 
            else 
            {
                result += to_string(adjacencyMatrix[i][j]) + ", ";
            }
        }
        result += "]";
    }
    return result;

}

// Check if the graph is directed.
bool Graph::isDirected() 
{
    // Check if the graph is directed by checking if the adjacency matrix is symmetric.
    for (size_t i = 0; i < adjacencyMatrix.size(); ++i) 
    {
        for (size_t j = 0; j < adjacencyMatrix[i].size(); ++j) 
        {
            if (adjacencyMatrix[i][j] != adjacencyMatrix[j][i])
            {
                return true;
            }
        }
    }
    return false;
}

// Get the number of edges in the graph.
size_t Graph::getNumberOfEdges()  
{
    size_t countOfEdge = 0;

    for (size_t i = 0; i < adjacencyMatrix.size(); ++i) 
    {
        for (size_t j = 0; j < adjacencyMatrix[i].size(); ++j) 
        {
            if (adjacencyMatrix[i][j] != 0) // Check if there is an edge between two vertices.
            {
                countOfEdge++;
            }
        }
    }
    return countOfEdge;
}

// Get the neighbors of a vertex.
vector<size_t> Graph::getNeighbors(size_t vertex) 
{
    vector<size_t> neighbors;
    for (size_t i = 0; i < adjacencyMatrix[vertex].size(); ++i) 
    {
        if (adjacencyMatrix[vertex][i] != 0) // Check if there is an edge between two vertices.
        {
            neighbors.push_back(i);
        }
    }
    return neighbors;
}

// Get the number of nodes in the graph.
size_t Graph::getNumberOfVertices() { return adjacencyMatrix.size();}

// Get the weight of an edge.
int Graph::getWeight(int start, int end) 
{
    // Check if the node index is out of range.
    if (start < 0 || static_cast<size_t>(start) >= adjacencyMatrix.size() || end < 0 || static_cast<size_t>(end) >= adjacencyMatrix.size()) 
    {
        throw std::out_of_range("Node index out of range");
    }
    return adjacencyMatrix[static_cast<size_t>(start)][static_cast<size_t>(end)]; // Return the weight of the edge. 
}

// this function return the edges of the graph
vector<pair<int,pair<int, int>>> Graph::getEdges() const {
    vector<pair<int,pair<int, int>>> edges;
    for (size_t i = 0; i < adjacencyMatrix.size(); ++i) {
        for (size_t j = 0; j < adjacencyMatrix[i].size(); ++j) {
            if (adjacencyMatrix[i][j] != 0) {
                edges.push_back({i, {j, adjacencyMatrix[i][j]}});
            }
        }
    }
    return edges;
}

// Check if the graph has a negative weight.
bool Graph::hasNegativeWeight() 
{
    for (size_t i = 0; i < adjacencyMatrix.size(); ++i) 
    {
        for (size_t j = 0; j < adjacencyMatrix[i].size(); ++j) 
        {
            if (adjacencyMatrix[i][j] < 0) // Check if the weight of the edge is negative.
            {
                return true;
            }
        }
    }
    return false;
}

// Get the weight of an edge.
int Graph::getEdge(unsigned int s, unsigned int t)
{   
        // Check if the node index is out of range.
        if (s<0 && s>=getNumV() && t < 0 && t>=getNumV())
        {
            return -1;
        }
        return adjacencyMatrix[s][t]; 
}

// Set the graph to be directed or not.
void Graph::setDirect(bool directed)
    {
        directed = directed;
        for (size_t i = 0; i < adjacencyMatrix.size(); i++)
        {
            for (size_t j = i; j < adjacencyMatrix[i].size(); j++)
            {
                if (!directed) // if not directed need to make the matrix symmetric
                {
                    if (adjacencyMatrix[i][j] != adjacencyMatrix[j][i])
                    {
                        if (adjacencyMatrix[i][j] == 0)
                        {
                            adjacencyMatrix[i][j] = adjacencyMatrix[j][i];
                        }
                        else if (adjacencyMatrix[j][i] == 0)
                        {
                            adjacencyMatrix[j][i] = adjacencyMatrix[i][j];
                        }
                        else
                        {
                            throw invalid_argument("Invalid graph: The graph is not symmetric.");
                        }
                    }
                }
            }
        }
    }

// Add two matrices.
Graph Graph::operator+( Graph &g) 
{
    // Check if the matrices on the same size.
    if (adjacencyMatrix.size() != g.adjacencyMatrix.size()) 
    {
        throw invalid_argument("Invalid operation: The dimensions of the two matrices are not equal.");
    }

    // Add the two matrices together using Graph object a
    Graph result;
    result.adjacencyMatrix = adjacencyMatrix;
    for (size_t i = 0; i < adjacencyMatrix.size(); ++i) 
    {
        for (size_t j = 0; j < adjacencyMatrix[i].size(); ++j) 
        {
            result.adjacencyMatrix[i][j] += g.adjacencyMatrix[i][j];
        }
    }

    //resized the diagonal to 0
    for (size_t i = 0; i < result.adjacencyMatrix.size(); ++i) 
    {
        result.adjacencyMatrix[i][i] = 0;
    }

    return result;
}

// Add two matrices and assign the result to the first matrix.
Graph Graph::operator+=( Graph &g) 
{
    // Check if the dimensions of the two matrices are equal.
    if (adjacencyMatrix.size() != g.adjacencyMatrix.size()) 
    {
        throw invalid_argument("Invalid operation: The dimensions of the two matrices are not equal.");
    }

    // Add the two matrices together.
    for (size_t i = 0; i < adjacencyMatrix.size(); ++i) 
    {
        for (size_t j = 0; j < adjacencyMatrix[i].size(); ++j) 
        {
            adjacencyMatrix[i][j] += g.adjacencyMatrix[i][j];
        }
    }

    //resized the diagonal to 0
    for (size_t i = 0; i < adjacencyMatrix.size(); ++i) 
    {
        adjacencyMatrix[i][i] = 0;
    }

    return *this;
}

// Unary plus operator.
Graph Graph::operator+() { return *this; }

// Subtract two matrices.
Graph Graph::operator-( Graph &g) 
{
    // Check if the dimensions of the two matrices are equal.
    if (adjacencyMatrix.size() != g.adjacencyMatrix.size()) 
    {
        throw invalid_argument("Invalid operation: The dimensions of the two matrices are not equal.");
    }

    // Subtract the two matrices.
    Graph result;
    result.adjacencyMatrix = adjacencyMatrix;
    for (size_t i = 0; i < adjacencyMatrix.size(); ++i) 
    {
        for (size_t j = 0; j < adjacencyMatrix[i].size(); ++j) 
        {
            result.adjacencyMatrix[i][j] -= g.adjacencyMatrix[i][j];
        }
    }

    //resized the diagonal to 0
    for (size_t i = 0; i < result.adjacencyMatrix.size(); ++i) 
    {
        result.adjacencyMatrix[i][i] = 0;
    }

    return result;
}

// Subtract two matrices and assign the result to the first matrix.
Graph Graph::operator-=( Graph &g) 
{
    // Check if the dimensions of the two matrices are equal.
    if (adjacencyMatrix.size() != g.adjacencyMatrix.size()) 
    {
        throw invalid_argument("Invalid operation: The dimensions of the two matrices are not equal.");
    }

    // Subtract the two matrices.
    for (size_t i = 0; i < adjacencyMatrix.size(); ++i) 
    {
        for (size_t j = 0; j < adjacencyMatrix[i].size(); ++j) 
        {
            adjacencyMatrix[i][j] -= g.adjacencyMatrix[i][j];
        }
    }

    //resized the diagonal to 0
    for (size_t i = 0; i < adjacencyMatrix.size(); ++i) 
    {
        adjacencyMatrix[i][i] = 0;
    }

    return *this;
}

// Unary minus operator.
Graph Graph::operator-()  
{
    Graph result;
    result.adjacencyMatrix = adjacencyMatrix;
    for (size_t i = 0; i < adjacencyMatrix.size(); ++i) 
    {
        for (size_t j = 0; j < adjacencyMatrix[i].size(); ++j) 
        {
            result.adjacencyMatrix[i][j] = -result.adjacencyMatrix[i][j];
        }
    }

    //resized the diagonal to 0
    for (size_t i = 0; i < result.adjacencyMatrix.size(); ++i) 
    {
        result.adjacencyMatrix[i][i] = 0;
    }

    return result;
}

// Check if two matrices are equal.
bool Graph::operator==( Graph &g) 
{
    // Check if the dimensions of the two matrices are equal.
    if (adjacencyMatrix.size() != g.adjacencyMatrix.size()) 
    {
        return false;
    }

    // Check if the two matrices are equal.
    for (size_t i = 0; i < adjacencyMatrix.size(); ++i) 
    {
        for (size_t j = 0; j < adjacencyMatrix[i].size(); ++j) 
        {
            if (adjacencyMatrix[i][j] != g.adjacencyMatrix[i][j]) 
            {
                return false;
            }
        }
    }
    return true;
}

// Check if two matrices are not equal.
bool Graph::operator!=( Graph &g) { return !(*this == g); }

// Check if the first matrix is less than the second matrix.
bool Graph::operator<( Graph &g) 
{
    // Check if the Graph object has more vertices than the other Graph object.
    if (getNumberOfVertices() > g.getNumberOfVertices())
    {
        return false;
    }

    // Check if the Graph object is contained in the other Graph object.
    if(getNumberOfVertices() < g.getNumberOfVertices())
    {
        for (size_t i = 0; i < adjacencyMatrix.size(); ++i) 
        {
            for (size_t j = 0; j < adjacencyMatrix[i].size(); ++j) 
            {
                if (adjacencyMatrix[i][j] != 0 && g.adjacencyMatrix[i][j] == 0) // Check if there is an edge between two vertices in the first graph and if there is no edge between two vertices in the second graph. 
                {
                    return false;
                }
            }
        }
    }

    // Check if the number of edges in the first graph is less than the number of edges in the second graph.
    if (getNumberOfEdges() > g.getNumberOfEdges()) 
    {
        return false;
    }

    return true;
}

// Check if the first matrix is less than or equal to the second matrix.
bool Graph::operator<=( Graph &g) { return *this < g || *this == g; }

// Check if the first matrix is greater than the second matrix.
bool Graph::operator>( Graph &g) { return !(*this <= g); }

// Check if the first matrix is greater than or equal to the second matrix.
bool Graph::operator>=( Graph &g) { return !(*this < g); }

// increment operator (before the variable)
Graph Graph::operator++() 
{
    for (size_t i = 0; i < adjacencyMatrix.size(); ++i) 
    {
        for (size_t j = 0; j < adjacencyMatrix[i].size(); ++j) 
        {
            if (i != j && adjacencyMatrix[i][j] != 0) // Check if the edge is not from a vertex to itself and if there is an edge between two vertices.
            {
            adjacencyMatrix[i][j]++;
            }
        }
    }   
    return *this;
}

// increment operator (after the variable)
Graph Graph::operator++(int) 
{
    Graph temp = *this;
    ++*this;
    return temp;
}

// decrement operator (before the variable)
Graph Graph::operator--() 
{
    for (size_t i = 0; i < adjacencyMatrix.size(); ++i) 
    {
        for (size_t j = 0; j < adjacencyMatrix[i].size(); ++j) 
        {
            if (i != j && adjacencyMatrix[i][j] != 0) // Check if the edge is not from a vertex to itself and if there is an edge between two vertices.
            {
            adjacencyMatrix[i][j]--;
            }
        }
    }
    return *this;
}

// decrement operator (after the variable)
Graph Graph::operator--(int) 
{
    Graph temp = *this;
    --*this;
    return temp;
}

// Multiply a matrix by a scalar.
Graph Graph::operator*(int scalar) 
{
    Graph result;
    result.adjacencyMatrix = adjacencyMatrix;
    for (size_t i = 0; i < adjacencyMatrix.size(); ++i) 
    {
        for (size_t j = 0; j < adjacencyMatrix[i].size(); ++j) 
        {
            result.adjacencyMatrix[i][j] *= scalar;
        }
    }
    return result;
}

// Multiply a matrix by a scalar and assign the result to the matrix.
Graph Graph::operator*=(int scalar) 
{
    for (size_t i = 0; i < adjacencyMatrix.size(); ++i) 
    {
        for (size_t j = 0; j < adjacencyMatrix[i].size(); ++j) 
        {
            adjacencyMatrix[i][j] *= scalar;
        }
    }
    return *this;
}

// Multiply two matrices.
Graph Graph::operator*( Graph &g) 
{
    size_t adj_length = adjacencyMatrix.size();
    size_t adj_width = adjacencyMatrix[0].size();
    size_t g_length = g.adjacencyMatrix.size();
    size_t g_width = g.adjacencyMatrix[0].size();
    
    // Check if the number of columns in the first matrix is equal to the number of rows in the second matrix.
    if (adj_width != g_length) 
    {
        throw invalid_argument("The number of columns in the first matrix must be equal to the number of rows in the second matrix.");
    }

    // Multiply the two matrices.
    Graph result;
    result.adjacencyMatrix.resize(adj_length, vector<int>(g_width, 0));

    for (size_t i = 0; i < adj_length; ++i) 
    {
        for (size_t j = 0; j < g_width; ++j) 
        {
            for (size_t k = 0; k < adj_width; ++k) 
            {
                result.adjacencyMatrix[i][j] += adjacencyMatrix[i][k] * g.adjacencyMatrix[k][j];
            }
        }
    }

    // put 0 in the diagonal
    for (size_t i = 0; i < result.adjacencyMatrix.size(); ++i) 
    {
        result.adjacencyMatrix[i][i] = 0;
    }

    return result;

}

// Multiply two matrices.
Graph Graph::operator*=( Graph &g) 
{
    // Check if the dimensions of the two matrices are equal.
    if (adjacencyMatrix.size() != g.adjacencyMatrix.size()) 
    {
        throw invalid_argument("Invalid operation: The dimensions of the two matrices are not equal.");
    }

    // Multiply the two matrices.
    for (size_t i = 0; i < adjacencyMatrix.size(); ++i) 
    {
        for (size_t j = 0; j < adjacencyMatrix[i].size(); ++j) 
        {
            adjacencyMatrix[i][j] *= g.adjacencyMatrix[i][j];
        }
    }
    return *this;
}

// Divide a matrix by a scalar.
Graph Graph::operator/(int scalar) 
{
    // Check if the scalar is zero.
    if (scalar == 0) 
    {
        throw invalid_argument("Invalid operation: Division by zero.");
    }

    // Divide the matrix by the scalar.
    Graph result;
    result.adjacencyMatrix = adjacencyMatrix;
    for (size_t i = 0; i < adjacencyMatrix.size(); ++i) 
    {
        for (size_t j = 0; j < adjacencyMatrix[i].size(); ++j) 
        {
            result.adjacencyMatrix[i][j] /= scalar;
        }
    }
    return result;
}

// Divide a matrix by a scalar and assign the result to the matrix.
Graph Graph::operator/=(int scalar) 
{
    // Check if the scalar is zero.
    if (scalar == 0) 
    {
        throw invalid_argument("Invalid operation: Division by zero.");
    }

    // Divide the matrix by the scalar.
    for (size_t i = 0; i < adjacencyMatrix.size(); ++i) 
    {
        for (size_t j = 0; j < adjacencyMatrix[i].size(); ++j) 
        {
            adjacencyMatrix[i][j] /= scalar;
        }
    }
    return *this;
}

// Divide two matrices.
Graph Graph::operator/( Graph &g) 
{
    // Check if the dimensions of the two matrices are equal.
    if (adjacencyMatrix.size() != g.adjacencyMatrix.size()) 
    {
        throw invalid_argument("Invalid operation: The dimensions of the two matrices are not equal.");
    }

    // Divide the two matrices.
    Graph result;
    result.adjacencyMatrix = adjacencyMatrix;
    for (size_t i = 0; i < adjacencyMatrix.size(); ++i) 
    {
        for (size_t j = 0; j < adjacencyMatrix[i].size(); ++j) 
        {
            // Check if the scalar is zero.
            if (g.adjacencyMatrix[i][j] == 0) 
            {
                throw invalid_argument("Invalid operation: Division by zero.");
            }
            result.adjacencyMatrix[i][j] /= g.adjacencyMatrix[i][j];
        }
    }
    return result;
}

// Divide two matrices and assign the result to the matrix.
Graph Graph::operator/=( Graph &g) 
{
    // Check if the dimensions of the two matrices are equal.
    if (adjacencyMatrix.size() != g.adjacencyMatrix.size()) 
    {
        throw invalid_argument("Invalid operation: The dimensions of the two matrices are not equal.");
    }

    // Divide the two matrices.
    for (size_t i = 0; i < adjacencyMatrix.size(); ++i) 
    {
        for (size_t j = 0; j < adjacencyMatrix[i].size(); ++j) 
        {
            // Check if the scalar is zero.
            if (g.adjacencyMatrix[i][j] == 0) 
            {
                throw invalid_argument("Invalid operation: Division by zero.");
            }
            adjacencyMatrix[i][j] /= g.adjacencyMatrix[i][j];
        }
    }
    return *this;
}


// friend functions
namespace ariel
{

    // Print the matrix using the << operator (friend function).
    ostream& operator<<(ostream& out, Graph& g) 
    {
        for (size_t i = 0; i < g.getMatrix().size(); ++i) 
        {
            if (i == 0) 
            {
                out << "[";
            } 
            else 
            {
                out << ", [";
            }
            for (size_t j = 0; j < g.getMatrix()[i].size(); ++j) 
            {
                if (j == g.getMatrix()[i].size() - 1) 
                {
                    out << g.getMatrix()[i][j];
                } 
                else 
                {
                    out << g.getMatrix()[i][j] << ", ";
                }
            }
            out << "]";
        }
        out << endl;
        return out;
    }

// Read the matrix using the >> operator (friend function).
istream& operator>>(istream &in, Graph &g) 
{
    for (size_t i = 0; i < g.getMatrix().size(); ++i) 
    {
        for (size_t j = 0; j < g.getMatrix()[i].size(); ++j) 
        {
            in >> g.getMatrix()[i][j];
        }
    }
    return in;
}

// Multiply a matrix by a scalar outside the class(friend function).
Graph operator*(int scalar, Graph &g) { return g * scalar; }

// Divide a matrix by a scalar outside the class(friend function).
Graph operator/(int scalar, Graph &g) { return g / scalar; }

}






