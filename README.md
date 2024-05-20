# Graphs & Operator Overloading

This assignment is a continuation of the first assignment. Here, we're going to add the option for arithmetic operations by operator overloading.

## Graph

The graph in `Graph.cpp` is represented as an adjacency matrix, where `[i][j] == 0` means no edge between vertices `i` and `j`.

## Operators

### Addition Operators (+, +=)

1. **`+`**: Adds two graphs only if they have the same number of vertices (same size). Allows us to do:  
   `g3 = g1 + g2`

2. **`+=`**: Adds another graph of the same size to the graph itself (otherwise throws an exception).  
   Example: `g1 += g2`

3. **`+g`**: Unary **`+`**, returns the graph itself.

### Subtraction Operators (-, -=)

1. **`-`**: Subtracts two graphs only if they have the same number of vertices (same size). Allows us to do:  
   `g3 = g1 - g2`

2. **`-=`**: Subtracts another graph of the same size from the graph itself (otherwise throws an exception).  
   Example: `g1 -= g2`

3. **`-g`**: Unary **`-`**, switches the sign (like multiplying by -1) of each non-zero element (i.e., where there is an edge).

### Multiplication Operators (*, *=)

We have two types of multiplication:

1. **Multiply two graphs `g1 * g2`**: Multiplies their adjacency matrices, applying rules of linear algebra, then initializes all diagonal elements to 0 to maintain the graph format.

2. **Multiply by a scalar**:  
   - `g * 2`
   - `2 * g`

   The first format will be a class function, and the second requires a function outside the class but within the namespace.  
   This is because the `operator*` function outside the class is needed for a binary operator where the left-hand operand is not of the class type.

### Division Operator (/=)

The division operator is defined only on a graph with a non-zero scalar. It traverses the matrix and divides each edge by this scalar.

### Increment and Decrement Operators (prefix ++, postfix ++)

- **Prefix ++**: Allows us to do `++g` or `--g`, increment or decrement by 1, only if the edge is not 0.  
  This means we're incrementing (or decreasing) `g` before we use it or perform a function on it.  
  Example: `g2 = ++g1` means `g2` will be equal to `g1` after it has been incremented.

- **Postfix ++**: Allows us to do `g++` or `g--`, increment or decrement by 1, only if the edge is not 0.  
  This means we're incrementing (or decreasing) `g` after we use it or perform a function on it.  
  Example: `g2 = g1++` means `g2` will be equal to `g1` before it has been incremented.

### Comparison Operators

Let's define what it means for one graph to be greater than (or less than) another graph:

1. If `g1` is contained in `g2`, then `g1 < g2`.
2. If not, `g1 < g2` if `g2` has more edges than `g1`.
3. If not, `g1 < g2` if `g2` has a greater order (more vertices).

For each other operator, such as `<=` or `>=`, we'll use logical rules to create them.  
For example, to do `g2 >= g1`, we need `!(g1 < g2)`.

### Equality Operators (==, !=)

Two graphs are considered equal if they have the same order (number of vertices) and the same edges and weights between each pair of vertices. Otherwise, they are not equal.

### Printing by << Operator

This operator is not an operation on the graph but allows us to have access to the graph's private members using the `friend` keyword.  
The function signature uses `ostream` from the standard library `std`:

```cpp
friend std::ostream &operator<<(std::ostream &os, const Graph &g);
