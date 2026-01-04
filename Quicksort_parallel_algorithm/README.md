# Parallel Quicksort Algorithms

A comprehensive implementation and performance comparison of various quicksort algorithms, including sequential and parallel versions using MPI and OpenMP.

## Description

This project contains two main implementations that explore different approaches to the quicksort algorithm:

1. **MPI-based Parallel Quicksort** (`quicksort_mpi.cpp`): Distributed memory parallel implementation
2. **Sequential and OpenMP Quicksort** (`quicksort_seq&omp.cpp`): Shared memory implementations with benchmarking

The project demonstrates the performance characteristics of different sorting approaches and the benefits of parallelization for large datasets.

## Files

- `quicksort_mpi.cpp`: MPI implementation using PSRS (Parallel Sorting by Regular Sampling)
- `quicksort_seq&omp.cpp`: Multiple quicksort variants and OpenMP parallelization

## Features

### MPI Implementation
- **PSRS Algorithm**: Parallel Sorting by Regular Sampling
- **Regular Sampling**: Selects representative elements for load balancing
- **Pivot Selection**: Distributed pivot computation
- **Data Distribution**: Efficient all-to-all communication
- **Performance Metrics**: Execution time measurement

### Sequential/OpenMP Implementation
- **Five Different Implementations**:
  1. Standard library `std::sort` (baseline)
  2. While-loop based quicksort
  3. For-loop based recursive quicksort
  4. Optimized iterative quicksort (using stack)
  5. OpenMP parallel quicksort
- **Performance Benchmarking**: Averages over multiple runs
- **Timing Comparison**: Side-by-side performance analysis

## Prerequisites

### For MPI Version
- MPI implementation (OpenMPI or MPICH)
- C++11 compatible compiler
- Multiple CPU cores or distributed computing environment

### For Sequential/OpenMP Version
- C++11 compatible compiler
- OpenMP support (included in modern GCC, Clang, MSVC)

## How to Build

### MPI Version

#### Using mpic++ (OpenMPI/MPICH)

```bash
mpic++ -std=c++11 quicksort_mpi.cpp -o quicksort_mpi
```

### Sequential/OpenMP Version

#### Using g++ with OpenMP

```bash
g++ -std=c++11 -fopenmp quicksort_seq\&omp.cpp -o quicksort_seq
```

#### Using clang++ with OpenMP

```bash
clang++ -std=c++11 -fopenmp quicksort_seq\&omp.cpp -o quicksort_seq
```

#### Using MSVC

```bash
cl /EHsc /openmp quicksort_seq^&omp.cpp /Fe:quicksort_seq.exe
```

## How to Run

### MPI Version

Run with multiple processes (e.g., 4 processes):

```bash
mpirun -np 4 ./quicksort_mpi
```

**Output Example:**
```
Available processors: 4

 General before sort:
    523 456 789 123 ...

 Gathered after sort:
    12 23 45 67 ...

 Processing time:
    0.00234
```

**Important**: The initial condition requires: `size >= num_processes²`

### Sequential/OpenMP Version

Simply run the executable:

```bash
./quicksort_seq           # Linux/Mac
quicksort_seq.exe         # Windows
```

**Output Example:**
```
 Repetition number: 50
1. std::sort                    : 0.0012
2. while loop                   : 0.0015
3. for loop                     : 0.0016
4. for loop optimized           : 0.0014
5. for loop optimized, parallel : 0.0008
```

## Algorithm Details

### PSRS (Parallel Sorting by Regular Sampling) - MPI

1. **Local Sort**: Each process sorts its portion of data
2. **Regular Sampling**: Select p-1 equally spaced samples from each process
3. **Pivot Selection**: Gather samples, sort them, and select p-1 global pivots
4. **Partitioning**: Partition local data based on pivots
5. **All-to-All Exchange**: Redistribute data so each process gets its range
6. **Final Sort**: Each process sorts its received data
7. **Gather**: Collect sorted data at root process

### Quicksort Variants

#### 1. While-Loop Quicksort
- Classic Hoare partition scheme
- Recursive implementation
- Pivot selected as middle element

#### 2. For-Loop Quicksort
- Lomuto partition scheme
- Simple recursive structure
- Pivot is last element

#### 3. Optimized Iterative Quicksort
- Uses explicit stack instead of recursion
- Eliminates recursion overhead
- Better cache performance

#### 4. OpenMP Parallel Quicksort
- Divides array into chunks
- Sorts chunks in parallel using OpenMP sections
- Merges results using `std::merge`
- Uses 4 threads by default

## Configuration

### Adjustable Parameters

#### MPI Version (`quicksort_mpi.cpp`)
```cpp
const int size = 20;      // Array size (must be >= numOfProc²)
const int m = 1000;       // Maximum random value
```

#### Sequential/OpenMP Version (`quicksort_seq&omp.cpp`)
```cpp
const int n = 50;         // Number of repetitions for averaging
const int s = 500;        // Array size
const int m = 1024;       // Maximum random value
int num_threads = 4;      // Number of OpenMP threads
```

## Performance Characteristics

### Expected Speedup (OpenMP)
- **Best case**: ~3-4x speedup with 4 threads
- **Depends on**: Array size, data distribution, hardware

### MPI Scalability
- **Strong scaling**: Fixed problem size, increasing processes
- **Weak scaling**: Problem size grows with processes
- **Communication overhead**: Significant for small arrays

## Learning Objectives

This project demonstrates:
- **Algorithm analysis**: Different quicksort implementations
- **Parallel computing**: MPI and OpenMP paradigms
- **Performance benchmarking**: Timing and comparison
- **Distributed algorithms**: PSRS algorithm
- **Load balancing**: Regular sampling technique
- **Memory management**: Efficient data structures
- **C++ STL**: Vectors, algorithms, iterators

## Technical Insights

### When to Use Each Approach

| Approach | Best For |
|----------|----------|
| `std::sort` | General purpose, guaranteed performance |
| Recursive | Educational, small datasets |
| Iterative | Avoiding stack overflow |
| OpenMP | Shared memory systems, medium datasets |
| MPI | Distributed systems, very large datasets |

### Performance Tips

1. **Array Size Matters**: Small arrays may not benefit from parallelization
2. **Data Distribution**: Uniform data distribution helps load balancing
3. **Number of Processes**: Use p² ≤ array_size for MPI version
4. **Cache Effects**: Iterative versions may have better cache performance

## Common Issues

### MPI Version

**Problem**: "Initial condition not fulfilled!"
- **Solution**: Increase array size or reduce number of processes
- **Formula**: Ensure `size >= num_processes²`

**Problem**: Incorrect sorted output
- **Solution**: Check MPI installation and process synchronization

### OpenMP Version

**Problem**: No speedup with parallel version
- **Solution**: Increase array size (current default may be too small)
- **Solution**: Verify OpenMP is enabled during compilation

**Problem**: Compilation error with `-fopenmp`
- **Solution**: Ensure compiler supports OpenMP

## Future Improvements

Potential enhancements:
- Adaptive thread count based on array size
- GPU acceleration using CUDA
- Hybrid MPI + OpenMP implementation
- More sorting algorithms (merge sort, heap sort)
- Visualization of sorting process
- Memory usage profiling
- Better load balancing strategies
- Support for different data types (templates)

## Benchmarking

To get meaningful results:
1. Run on a dedicated system (no other heavy processes)
2. Use large array sizes (> 10,000 elements)
3. Average over many repetitions (> 50)
4. Warm up the CPU before measurements
5. Disable CPU frequency scaling if possible

## References

- PSRS: Li, Xiaojun, et al. "Parallel sorting by regular sampling." *Journal of Parallel and Distributed Computing* 14.4 (1992): 361-372.
- OpenMP: https://www.openmp.org/
- MPI: https://www.mpi-forum.org/

---

*Part of C++ Learning Projects Collection (2016-2017)*
