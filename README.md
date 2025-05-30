# C++ Card Sorting Program

A C++ program to demonstrate and compare BubbleSort and QuickSort algorithms on randomly generated packs of cards. 

## Features

*   Sorts a pack of cards using BubbleSort and QuickSort (middle element pivot).
*   Generates cards pseudo-randomly based on an input string.
*   Outputs unsorted/sorted card lists and performance metrics (comparisons, moves, recursion depth).
*   Collects statistics for different pack sizes (5, 10, 20, 50).

## Building and Running

1.  **Prerequisites:** C++ Compiler (C++23), CMake.
2.  **Clone:** `git clone https://github.com/Zain0o/cardprogram.git && cd cardprogram`
3.  **Build:** `mkdir build && cd build && cmake .. && cmake --build .`
4.  **Run:** Execute `cardprogram` (or `cardprogram.exe`) from the build directory.

## Code Structure

*   `main.cpp`: Main logic, sorting algorithms, experiments.
*   `cardlib.h`/`.cpp`: Card structure, suit enum, and utility functions.
*   `CMakeLists.txt`: Build script.
