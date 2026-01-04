# Simple Matrix Calculator

A console-based C++ matrix calculator that performs fundamental linear algebra operations including addition, subtraction, multiplication, and display of matrices.

## Description

This interactive command-line application allows users to create and manipulate matrices with custom dimensions. The calculator implements dynamic memory allocation for efficient matrix storage and supports basic matrix operations commonly used in linear algebra.

## Features

- **Dynamic Matrix Creation**: Create matrices of any size (limited by available memory)
- **Matrix Operations**:
  - Addition
  - Subtraction
  - Multiplication
  - Display/Printing
- **Flexible Matrix Sizes**: Support for both square and rectangular matrices
- **Input Validation**: Ensures mathematical validity of operations
- **Memory Management**: Proper allocation and deallocation of dynamic memory
- **User-Friendly Interface**: Interactive prompts and clear error messages

## Prerequisites

- C++ compiler with C++11 support
- Standard C++ Library
- Windows OS (uses `windows.h` and `conio.h`)

## How to Build

### Using g++ (MinGW on Windows)

```bash
g++ -std=c++11 simple_matrix_calculator.cpp -o matrix_calc.exe
```

### Using MSVC (Visual Studio)

```bash
cl /EHsc simple_matrix_calculator.cpp /Fe:matrix_calc.exe
```

### Using clang++ (Windows)

```bash
clang++ -std=c++11 simple_matrix_calculator.cpp -o matrix_calc.exe
```

## How to Run

1. Execute the program:
   ```bash
   matrix_calc.exe    # Windows
   ```

2. Choose whether matrices should have the same size:
   ```
   Enter size of your matrices. Do you want them to have same size? Enter Y/N
   ```

3. Enter matrix dimensions:
   - If same size (Y): Enter length and width once
   - If different (N): Enter dimensions for each matrix separately

4. Input matrix values when prompted

5. Choose the operation:
   ```
   1 - printing
   2 - multiplication
   3 - addition      (only if same size)
   4 - subtraction   (only if same size)
   ```

## Example Usage

### Example 1: Matrix Multiplication

```
Enter size of your matrices. Do you want them to have same size? Enter Y/N
N

First matrix:
  Length: 2
  Width:  3

Second matrix:
  Length: 3
  Width:  2

Enter the numbers into matrix: 1 2 3 4 5 6
Enter the numbers into matrix: 7 8 9 10 11 12

What do you want to do with matrices?
1 - printing,  2 - multiplication
2

|22 28|
|49 64|
```

### Example 2: Matrix Addition

```
Enter size of your matrices. Do you want them to have same size? Enter Y/N
Y

Length: 2
Width:  2

Enter the numbers into matrix: 1 2 3 4
Enter the numbers into matrix: 5 6 7 8

What do you want to do with matrices?
1 - printing,  2 - multiplication,  3 - addition,  4 - subtraction
3

|6 8|
|10 12|
```

## Matrix Operations

### 1. Printing
Displays both matrices in formatted output:
```
|1 2 3|
|4 5 6|

|7 8 9|
|10 11 12|
```

### 2. Multiplication
Performs matrix multiplication (A × B):
- **Requirement**: Number of columns in first matrix = number of rows in second matrix
- **Result size**: (rows of A) × (columns of B)

### 3. Addition
Adds corresponding elements (A + B):
- **Requirement**: Both matrices must have same dimensions
- **Result**: Matrix with same dimensions

### 4. Subtraction
Subtracts corresponding elements (A - B):
- **Requirement**: Both matrices must have same dimensions
- **Result**: Matrix with same dimensions

## Technical Details

### Matrix Class

```cpp
class Matrix {
    public:
        int rows, cols;
        double** mat;
        
        Matrix(int s1=1, int s2=1);    // Constructor
        void Print();                   // Display matrix
        ~Matrix();                      // Destructor
};
```

### Memory Management

- **Dynamic Allocation**: Uses `new` for 2D array allocation
- **Proper Cleanup**: Destructor ensures no memory leaks
- **RAII Pattern**: Resource management tied to object lifetime

### Operation Functions

#### `AddSub(Matrix O1, Matrix O2, int sign, int s1, int s2)`
- Performs addition (sign=3) or subtraction (sign=4)
- Modifies first matrix in-place
- Displays result

#### `Mul(Matrix O1, Matrix O2, int r1, int c1, int r2, int c2)`
- Performs matrix multiplication
- Creates temporary result matrix
- Handles rectangular matrices
- Proper memory cleanup

## Input Validation

The program validates:
- **Positive Dimensions**: Matrix size must be > 0
- **Multiplication Compatibility**: Columns of A = Rows of B
- **Operation Validity**: Addition/subtraction only for same-size matrices

## Operation Compatibility Table

| Matrix A | Matrix B | Print | Multiply | Add | Subtract |
|----------|----------|-------|----------|-----|----------|
| m×n | m×n | ✓ | ✓ (if n=m) | ✓ | ✓ |
| m×n | n×p | ✓ | ✓ | ✗ | ✗ |
| m×n | p×q | ✓ | ✗ | ✗ | ✗ |

## Learning Objectives

This project demonstrates:
- **Dynamic Memory Management**: 2D array allocation/deallocation
- **Object-Oriented Programming**: Class design and encapsulation
- **Constructor/Destructor**: Resource management
- **Matrix Algorithms**: Linear algebra operations
- **Input Validation**: Error checking and user feedback
- **Memory Safety**: Preventing memory leaks

## Known Limitations

- **Windows-only**: Uses Windows-specific headers
- **No Matrix Persistence**: Cannot save/load matrices
- **Limited Operations**: Only basic operations supported
- **Integer Dimensions**: Cannot handle fractional sizes (obviously)
- **No Matrix Naming**: Cannot store and reference multiple matrices
- **Basic Date Validation**: Accepts invalid dates like 31/02

## Common Issues

**Problem**: "Size of matrix can't be negative or zero!"
- **Solution**: Enter positive integers for dimensions

**Problem**: "Column of first matrix not equal to row of second..."
- **Solution**: For multiplication, ensure matrix dimensions are compatible
- **Example**: (3×2) matrix can multiply with (2×4) matrix

**Problem**: "Addition can't be executed!"
- **Solution**: Choose same size (Y) when creating matrices for add/subtract operations

## Future Improvements

Potential enhancements:
1. **Advanced Operations**:
   - Transpose
   - Determinant
   - Inverse
   - Eigenvalues/eigenvectors
   - Matrix power
   
2. **Features**:
   - Save/load matrices from files
   - Matrix library (store multiple matrices)
   - Expression parsing (e.g., "A*B + C")
   - Complex number support
   - Sparse matrix optimization
   
3. **UI/UX**:
   - Cross-platform support
   - Better visualization
   - Command-line arguments
   - GUI interface
   
4. **Performance**:
   - SIMD optimization
   - Parallel multiplication
   - Block matrix algorithms

## Mathematical Notes

### Matrix Multiplication Algorithm

For C = A × B where A is m×n and B is n×p:

```
C[i][j] = Σ(k=0 to n-1) A[i][k] × B[k][j]
```

Time Complexity: O(m × n × p)

### Memory Complexity

For two matrices of size m×n and p×q:
- **Storage**: O(mn + pq)
- **Multiplication Result**: O(mp) additional space

## Troubleshooting

**Problem**: Program crashes during input
- **Solution**: Ensure you enter numbers (not letters) for matrix values

**Problem**: Unexpected results in multiplication
- **Solution**: Verify input values and remember matrix multiplication is not commutative (A×B ≠ B×A)

**Problem**: Memory errors
- **Solution**: Avoid extremely large matrices (> 10,000 × 10,000)

---

*Part of C++ Learning Projects Collection (2016-2017)*
