# C++ Modernization Summary (C++11 to C++17)

This document outlines all the modern C++ features (C++11-17) implemented across the projects in this repository.

## Project-by-Project Modernization

### 1. File Mover

**C++17 Features:**
- `<filesystem>` library for cross-platform file operations
- `fs::rename()` instead of platform-specific APIs
- `fs::filesystem_error` for modern exception handling

**C++11 Features:**
- `std::system_error` for proper error handling
- `nullptr` instead of NULL
- Range-based for loops
- `constexpr` for compile-time constants

**Build Commands:**
```bash
# C++17 version (cross-platform)
g++ -std=c++17 file_mover.cpp -o file_mover

# Windows-specific version (C++11)
g++ -std=c++11 file_mover_windows.cpp -o file_mover_windows
```

### 2. MasterMind Game

**C++14 Features:**
- `<random>` library with `std::mt19937` and `std::random_device`
- `constexpr` for compile-time constants
- Modern class design with private members

**C++11 Features:**
- `std::array` instead of C-style arrays
- Range-based for loops
- `auto` keyword for type deduction
- Lambda expressions
- `nullptr`
- Uniform initialization
- `std::find` algorithm
- Move semantics

**Key Improvements:**
- Better random number generation (not `rand()`)
- Object-oriented design with MasterMind class
- RAII principles
- Const-correctness

**Build Command:**
```bash
g++ -std=c++14 mastermind.cpp -o mastermind
```

### 3. Personal Planner

**C++14 Features:**
- `std::chrono` for time handling (ready for future date/time features)
- Enhanced type deduction

**C++11 Features:**
- Class-based architecture (PersonalPlanner class)
- `std::vector` for dynamic event storage
- Move semantics (`std::move`)
- Lambda functions for sorting
- Operator overloading (`operator<`)
- Template functions
- `constexpr`
- Range-based for loops
- `auto` keyword
- `<iomanip>` for formatted output

**Key Improvements:**
- Proper date validation with leap year support
- Template-based input validation
- Better memory management (no raw pointers)
- Cross-platform screen clearing
- Enhanced user experience

**Build Command:**
```bash
g++ -std=c++14 personal_planner.cpp -o personal_planner
```

### 4. Intelligent House

**C++14 Features:**
- `std::chrono::literals` for time durations
- Enhanced member initialization

**C++11 Features:**
- Member initializer lists in constructors
- `std::unique_ptr` for smart pointers
- `std::array` for fixed-size collections
- `std::make_unique` (C++14)
- `std::thread` and `<chrono>` instead of Windows Sleep
- Range-based for loops
- `auto` keyword
- `nullptr`
- `constexpr`
- Uniform initialization
- Default and deleted functions (commented, ready to use)

**Key Improvements:**
- RAII with member initializer lists
- Const-correctness (`const` member functions)
- Better encapsulation (private members)
- Cross-platform timing
- Formatted output with `<iomanip>`
- Smart resource management

**Build Commands:**
```bash
# Modern version
g++ -std=c++14 main.cpp AirConditioner.cpp Controller.cpp Room.cpp Sched.cpp Thermometer.cpp -o intelligent_house

# With CMake
cmake -DCMAKE_CXX_STANDARD=14 ..
make
```

### 5. Simple Matrix Calculator

**C++11 Features:**
- `std::vector` instead of raw pointers (No `new`/`delete` needed!)
- Exception handling with `std::invalid_argument`
- `std::runtime_error`
- Operator overloading (`+`, `-`, `*`)
- RAII (automatic memory management)
- Move semantics
- Range-based for loops
- `auto` keyword
- `nullptr`
- Member initializer lists
- Uniform initialization
- `constexpr`

**Key Improvements:**
- **No memory leaks** - automatic memory management
- **Exception safety** - proper error handling
- **Modern design** - uses standard containers
- **Operator overloading** - natural syntax for operations
- **Const-correctness** throughout

**Build Command:**
```bash
g++ -std=c++11 simple_matrix_calculator.cpp -o matrix_calc
```

### 6. Parallel Quicksort Algorithms

#### MPI Version

**C++14 Features:**
- `<random>` with better random number generation
- `constexpr` functions for compile-time calculations

**C++11 Features:**
- `constexpr` for index calculations (replacing macros)
- `std::random_device` and `std::mt19937`
- `std::uniform_int_distribution`
- Lambda expressions
- Range-based for loops
- `auto` keyword
- `std::pow` from `<cmath>`

**Key Improvements:**
- Replaced preprocessor macros with `constexpr` functions
- Better random number generation
- Modern error handling

**Build Command:**
```bash
mpic++ -std=c++14 quicksort_mpi.cpp -o quicksort_mpi
```

#### Sequential/OpenMP Version

**C++11/14 Features:**
- `std::chrono::high_resolution_clock` for precise timing
- `std::chrono::duration` for time measurements
- `<random>` library for better RNG
- `std::swap` instead of custom swap
- `std::vector` for stack (instead of raw arrays)
- `constexpr` for constants
- Range-based for loops
- `auto` keyword
- Lambda expressions

**Key Improvements:**
- Precise timing with `<chrono>` instead of `clock()`
- Uses standard `std::swap`
- Vector-based stack (safer than raw arrays)
- Pass by reference (avoiding copies)
- Modern random number generation

**Build Command:**
```bash
g++ -std=c++14 -fopenmp quicksort_seq\&omp.cpp -o quicksort_seq
```

## Summary of C++ Features Used

### C++17
- ✅ `<filesystem>` library
- ✅ Filesystem error handling
- ✅ Structured bindings (ready for use)

### C++14
- ✅ `std::make_unique`
- ✅ Binary literals
- ✅ Generic lambdas
- ✅ Return type deduction
- ✅ `constexpr` relaxation
- ✅ `std::chrono` user-defined literals

### C++11
- ✅ `auto` keyword
- ✅ `nullptr`
- ✅ Range-based for loops
- ✅ Lambda expressions
- ✅ Smart pointers (`std::unique_ptr`)
- ✅ Move semantics
- ✅ `std::array`
- ✅ `std::vector` improvements
- ✅ Member initializer lists
- ✅ Uniform initialization `{}`
- ✅ `constexpr`
- ✅ `<random>` library
- ✅ `<chrono>` library
- ✅ Exception handling improvements
- ✅ `std::thread`
- ✅ Type aliases (`using`)
- ✅ Deleted/defaulted functions
- ✅ Rvalue references
- ✅ `std::move` and `std::forward`
- ✅ STL algorithms enhancements

## Benefits of Modernization

### Memory Safety
- **Before**: Manual `new`/`delete`, potential memory leaks
- **After**: Smart pointers, RAII, automatic cleanup

### Type Safety
- **Before**: C-style casts, NULL
- **After**: `nullptr`, strong typing, `auto`

### Performance
- **Before**: Unnecessary copies
- **After**: Move semantics, perfect forwarding

### Readability
- **Before**: Complex iterator loops
- **After**: Range-based for loops, lambdas

### Maintainability
- **Before**: Macros, magic numbers
- **After**: `constexpr`, named constants

### Random Numbers
- **Before**: `rand()` and `srand(time(NULL))`
- **After**: `<random>` with proper distributions

### Timing
- **Before**: `clock()` with CLOCKS_PER_SEC
- **After**: `std::chrono` with high resolution

## Compiler Requirements

All projects now require:
- **Minimum**: C++11
- **Recommended**: C++14 or C++17
- **Compilers**: 
  - GCC 5.0+ (full C++14 support)
  - Clang 3.4+ (full C++14 support)
  - MSVC 2015+ (good C++14 support)
  - MSVC 2017+ (full C++17 support)

## Building All Projects

```bash
# File Mover (C++17)
g++ -std=c++17 File_mover/file_mover.cpp -o file_mover

# MasterMind (C++14)
g++ -std=c++14 MasterMind_game/mastermind.cpp -o mastermind

# Personal Planner (C++14)
g++ -std=c++14 Personal_planner/personal_planner.cpp -o personal_planner

# Intelligent House (C++14)
g++ -std=c++14 Intelligent_house/*.cpp -o intelligent_house

# Matrix Calculator (C++11)
g++ -std=c++11 Simple_matrix_calculator/simple_matrix_calculator.cpp -o matrix_calc

# Quicksort MPI (C++14)
mpic++ -std=c++14 Quicksort_parallel_algorithm/quicksort_mpi.cpp -o quicksort_mpi

# Quicksort OpenMP (C++14)
g++ -std=c++14 -fopenmp Quicksort_parallel_algorithm/quicksort_seq\&omp.cpp -o quicksort_seq
```

## Learning Resources

To learn more about these C++ features:
- [C++ Reference](https://en.cppreference.com/)
- [Modern C++ Best Practices](https://github.com/isocpp/CppCoreGuidelines)
- [Effective Modern C++ by Scott Meyers](https://www.oreilly.com/library/view/effective-modern-c/9781491908419/)

---

*All code modernized to follow C++11-17 standards without using C++20/23 features*
