# Octave Matrix Simulator

This project is a Matrix Simulator inspired by GNU Octave, implementing various matrix operations using dynamic, resizable arrays. The simulator allows users to manage and manipulate matrices through commands, offering functionalities like loading matrices, resizing, multiplying, transposing, and more.

## Features
* Load Matrices: Dynamically allocate memory to store matrices. If matrices are already present, resources are reallocated to accommodate new ones.
* Matrix Dimensions: Retrieve and display matrix dimensions.
* Print Matrix: Display matrix contents based on a given index.
* Resize Matrix: Reshape matrices by specifying new row and column indices.
* Matrix Multiplication: Multiply two matrices (standard method and Strassen’s algorithm).
* Sort Matrices: Sort matrices based on the sum of their elements.
* Transpose Matrix: Transpose matrices efficiently by reallocating memory.
* Matrix Power Calculation: Raise matrices to a power using a logarithmic time complexity algorithm.
* Free Memory: Release allocated resources for specific or all matrices.

## Usage Instructions

1. Loading a Matrix
Command: L (Load Function)
Allocates memory for the first matrix or reallocates for subsequent matrices.
Dimensions are stored in the dims array.

2. Determining Matrix Dimensions
Command: D (Dimensions Function)
Validates the index and prints matrix dimensions (dims[index][0] for rows and dims[index][1] for columns).

3. Displaying a Matrix
Command: P (Print Function)
Validates the index and prints the values stored in the matrix at a[index].

4. Resizing a Matrix
Command: C (Redim Function)
Reads row and column indices for resizing.
Uses an auxiliary matrix to store and copy values based on the new dimensions.

5. Multiplying Two Matrices
Command: M (Multiply Function)
Checks if matrix dimensions are compatible.
Allocates memory for the result and calculates the product (modulo 10007).

6. Sorting Matrices
Command: O (Sort Matrices Function)
Computes the sum of elements (modulo 10007) for each matrix and sorts matrices using Bubble Sort.

7. Transposing a Matrix
Command: T (Transpose Function)
Allocates an auxiliary matrix for the transpose and reallocates the original with new dimensions.

8. Raising a Matrix to a Power
Command: R (Power Function)
Checks if the matrix is square and power is positive.
Utilizes a logarithmic algorithm for efficient calculation.

9. Freeing Memory for a Matrix
Command: F (Free Matrix Function)
Validates the index, releases memory, and shifts remaining matrices in the array.

10. Freeing All Resources
Command: Q (Quit Function)
Frees all memory allocated for matrices and dimensions arrays.

11. Multiplying Matrices Using Strassen's Algorithm
Command: S (Strassen Function)
Implements Strassen's algorithm for optimized matrix multiplication.
Implementation Notes
The simulator relies on dynamic memory allocation using malloc and realloc for flexible management of matrices.
Modular arithmetic (modulo 10007) ensures integer overflow is handled during matrix operations.
Sorting, multiplication, and power calculations utilize efficient algorithms for optimal performance.

License
Copyright © 2023-2024 Teodora-Anca Plopeanu

This project is designed for educational purposes, simulating a GNU Octave-like environment for matrix operations.
