# C++ Learning Projects Collection (2016-2017)

A collection of C++ projects developed during my early programming education, **now modernized with C++11-17 features**. These projects demonstrate fundamental concepts in object-oriented programming, data structures, algorithms, and parallel computing with modern C++ best practices.

> **🆕 2024 Update**: All projects have been modernized to use C++11-17 features including smart pointers, lambda expressions, `<chrono>`, `<random>`, RAII, and more. See [CPP_MODERNIZATION.md](CPP_MODERNIZATION.md) for details.

## 📋 Projects Overview

### 1. File Mover
A cross-platform file management utility using C++17 filesystem library.
- **Technologies**: C++17 `<filesystem>`, Modern exception handling
- **Key Features**: Cross-platform support, proper error handling, RAII
- **C++ Standard**: C++17

### 2. Intelligent House Simulator
An object-oriented simulation of a smart home climate control system with multiple rooms and air conditioning units.
- **Technologies**: C++14, OOP Design Patterns, Smart Pointers
- **Key Features**: Temperature control, room management, real-time simulation with `std::chrono`
- **C++ Standard**: C++11/14

### 3. MasterMind Game
A console implementation of the classic code-breaking game with modern random number generation.
- **Technologies**: C++14, `<random>` library, OOP
- **Key Features**: Proper RNG, class-based design, `std::array`, lambda expressions
- **C++ Standard**: C++11/14

### 4. Personal Planner
A command-line event management application with modern date/time handling.
- **Technologies**: C++14, `<chrono>`, Lambda functions
- **Key Features**: Event scheduling, sorting with lambdas, date validation, operator overloading
- **C++ Standard**: C++11/14

### 5. Parallel Quicksort Algorithms
Implementation and comparison of various quicksort algorithms including sequential and parallel versions.
- **Technologies**: MPI, OpenMP, C++14, `<chrono>` for timing
- **Key Features**: Parallel sorting, performance benchmarking, modern timing, `<random>`
- **C++ Standard**: C++11/14

### 6. Simple Matrix Calculator
A console-based matrix calculator with automatic memory management using STL containers.
- **Technologies**: C++11, STL `<vector>`, Operator overloading
- **Key Features**: No raw pointers, exception safety, operator overloading, RAII
- **C++ Standard**: C++11

## 🛠️ Modern C++ Features Demonstrated

### C++17
- ✅ `<filesystem>` library
- ✅ Filesystem error handling

### C++14
- ✅ `std::make_unique`
- ✅ Generic lambdas
- ✅ `constexpr` relaxation
- ✅ `std::chrono` literals

### C++11
- ✅ Smart pointers (`std::unique_ptr`)
- ✅ Lambda expressions
- ✅ Range-based for loops
- ✅ `auto` keyword
- ✅ Move semantics
- ✅ `std::array` and enhanced `std::vector`
- ✅ Member initializer lists
- ✅ `<random>` library (proper RNG)
- ✅ `<chrono>` library (precise timing)
- ✅ `nullptr`
- ✅ `constexpr`
- ✅ RAII principles
- ✅ Exception handling
- ✅ Type aliases with `using`

See [CPP_MODERNIZATION.md](CPP_MODERNIZATION.md) for detailed feature breakdown by project.

## 📁 Repository Structure

```
├── README.md                          # This file
├── CPP_MODERNIZATION.md              # Detailed C++11-17 features guide
├── IMPROVEMENTS.md                   # Repository improvements summary
├── .gitignore                        # C++ project ignore rules
│
├── File_mover/                       # C++17 file management utility
│   ├── README.md
│   ├── file_mover.cpp               # Cross-platform version
│   └── file_mover_windows.cpp       # Windows-specific version
│
├── Intelligent_house/                # C++14 smart home simulation
│   ├── README.md
│   ├── main.cpp
│   ├── AirConditioner.{h,cpp}
│   ├── Controller.{h,cpp}
│   ├── Room.{h,cpp}
│   ├── Sched.{h,cpp}
│   └── Thermometer.{h,cpp}
│
├── MasterMind_game/                  # C++14 logic game
│   ├── README.md
│   └── mastermind.cpp
│
├── Personal_planner/                 # C++14 event scheduler
│   ├── README.md
│   └── personal_planner.cpp
│
├── Quicksort_parallel_algorithm/     # C++14 parallel sorting
│   ├── README.md
│   ├── quicksort_mpi.cpp
│   └── quicksort_seq&omp.cpp
│
└── Simple_matrix_calculator/         # C++11 matrix operations
    ├── README.md
    └── simple_matrix_calculator.cpp
```

## 🚀 Getting Started

Each project directory contains its own README with specific build and run instructions.

### Prerequisites

#### Compilers
- **GCC 5.0+** (full C++14 support)
- **Clang 3.4+** (full C++14 support)
- **MSVC 2017+** (full C++17 support)

#### Additional Requirements
- **For MPI projects**: OpenMPI or MPICH
- **For OpenMP projects**: Compiler with OpenMP support
- **For C++17 projects**: Filesystem library support

### Quick Build Examples

```bash
# File Mover (C++17)
g++ -std=c++17 File_mover/file_mover.cpp -o file_mover

# MasterMind Game (C++14)
g++ -std=c++14 MasterMind_game/mastermind.cpp -o mastermind

# Personal Planner (C++14)
g++ -std=c++14 Personal_planner/personal_planner.cpp -o personal_planner

# Intelligent House (C++14)
g++ -std=c++14 Intelligent_house/*.cpp -o intelligent_house

# Matrix Calculator (C++11)
g++ -std=c++11 Simple_matrix_calculator/simple_matrix_calculator.cpp -o matrix_calc

# Parallel Quicksort - MPI (C++14)
mpic++ -std=c++14 Quicksort_parallel_algorithm/quicksort_mpi.cpp -o quicksort_mpi

# Parallel Quicksort - OpenMP (C++14)
g++ -std=c++14 -fopenmp Quicksort_parallel_algorithm/quicksort_seq\&omp.cpp -o quicksort_seq
```

## 📝 Note on Modernization

These projects were originally created in 2016-2017 as learning exercises. In 2024, they have been modernized to incorporate **C++11 through C++17 features**, reflecting current best practices while maintaining their educational value. The modernization includes:

- ✅ Replaced raw pointers with smart pointers and STL containers
- ✅ Replaced `rand()` with `<random>` library
- ✅ Replaced `clock()` with `<chrono>` library
- ✅ Added proper exception handling
- ✅ Used RAII for resource management
- ✅ Applied const-correctness
- ✅ Utilized move semantics where appropriate
- ✅ Replaced macros with `constexpr`
- ✅ Added lambda expressions for cleaner code

**No C++20/23 features** have been used, as I transitioned to Python before those standards were released.

## 🎓 Learning Outcomes

Through these projects, I gained hands-on experience with:
- **Modern C++ features** (C++11-17)
- **Memory management** with smart pointers and RAII
- **Object-oriented design** principles
- **Data structures** and their applications
- **Parallel and distributed computing** basics
- **STL containers and algorithms**
- **System-level programming**
- **Performance optimization** and benchmarking

## 📄 License

These projects are provided as-is for educational reference.

---

*Originally developed 2016-2017 | Modernized to C++11-17 in 2024*

