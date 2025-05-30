/// SortCard.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <cstdlib>    // For srand and rand
#include <ctime>      // For time
#include "cardlib.h"  // For the card library
#include <string>     // For string
#include <iostream>   // For cout and cin
#include <vector>     // For std::vector
#include <algorithm>  // For std::swap, std::max
#include <iomanip>    // For std::setw or printf formatting

// using namespace std; // Prefer std:: prefix or selective 'using' declarations

// Global variables
std::vector<aCard> thePack; // The pack of cards (now a vector)
int comparisons = 0;       // The number of comparisons
int swaps = 0;             // The number of swaps (used by BubbleSort for its "moves")

// Function prototypes for functions defined in this file
void printPack(const std::string& mess);
void bubbleSort();
int partition(int low, int high, int& moves, int& maxDepth, int depth);
// quickSort is declared in cardlib.h, defined here

void swapCards(int n1, int n2) { // Swap two cards in the global thePack
    if (n1 < 0 || static_cast<size_t>(n1) >= thePack.size() || n2 < 0 || static_cast<size_t>(n2) >= thePack.size()) {
        std::cout << "Index out of bounds in swapCards" << std::endl;
        return;
    }
    swaps++; // Increment the global swap counter (for BubbleSort's moves)
    aCard temp = thePack[n1];
    thePack[n1] = thePack[n2];
    thePack[n2] = temp;
}

void printPack(const std::string& mess) { // Print the pack of cards
    if (!mess.empty()) {
        std::cout << mess << " : ";
    }
    for (size_t i = 0; i < thePack.size(); i++) {
        std::cout << cardToStr(thePack[i]);
        if (i < thePack.size() - 1) {
            std::cout << ", ";
        }
    }
    std::cout << "\n";
}

void bubbleSort() { // Sort the pack of cards using bubble sort
    bool swapped_in_pass;
    if (thePack.empty()) return;

    for (size_t i = 0; i < thePack.size() - 1; i++) {
        swapped_in_pass = false;
        for (size_t j = 0; j < thePack.size() - 1 - i; j++) {
            if (compareCards(thePack[j], thePack[j + 1]) > 0) {
                swapCards(j, j + 1); // Uses global swaps counter
                swapped_in_pass = true;
            }
        }
        if (!swapped_in_pass) { // Optimization: if no swaps in a pass, list is sorted
            break;
        }
    }
}

// Partition function for QuickSort, using middle element as pivot
int partition(int low, int high, int& moves, int& maxDepth, int depth) {
    // Select middle element as pivot
    int middle = low + (high - low) / 2;
    std::swap(thePack[middle], thePack[high]); // Swap middle with last to use existing Lomuto logic
    moves++; // Count this swap as a move for QuickSort

    aCard pivot = thePack[high];
    int i = (low - 1); // Index of the smaller element

    for (int j = low; j < high; j++) {
        // comparisons++; // compareCards already increments global comparisons
        if (compareCards(thePack[j], pivot) < 0) {
            i++;
            if (i != j) { // Only swap if necessary
                std::swap(thePack[i], thePack[j]);
                moves++; // Increment the QuickSort move counter
            }
        }
    }
    if ((i + 1) != high) { // Only swap if necessary
        std::swap(thePack[i + 1], thePack[high]);
        moves++; // Increment the QuickSort move counter
    }
    return (i + 1);
}

// QuickSort function (declaration in cardlib.h)
void quickSort(int low, int high, int& moves, int& maxDepth, int depth) {
    if (low < high) {
        maxDepth = std::max(maxDepth, depth + 1); // Update max depth (depth of current call + 1)
        int pi = partition(low, high, moves, maxDepth, depth + 1);
        quickSort(low, pi - 1, moves, maxDepth, depth + 1);
        quickSort(pi + 1, high, moves, maxDepth, depth + 1);
    }
}


int main() {
    srand(static_cast<unsigned int>(time(nullptr))); // Seed the random number generator

    std::string studentID = "32012344"; // Use your student ID

    // --- Phase 1: Detailed Run for Pack Size 20 ---
    int detailedPackSize = 20;
    std::cout << "--- Detailed Run for Pack Size: " << detailedPackSize << " ---" << std::endl;
    thePack.resize(detailedPackSize); // Resize vector

    // BubbleSort detailed run
    std::cout << "\n== BubbleSort Detailed Run (N=" << detailedPackSize << ") ==" << std::endl;
    comparisons = 0;
    swaps = 0; // BubbleSort uses global 'swaps' for its moves
    std::cout << "Generating pack for BubbleSort..." << std::endl;
    for (int ct = 0; ct < detailedPackSize; ct++) {
        thePack[ct] = getCard(studentID);
    }
    printPack("Unsorted Pack");
    bubbleSort();
    printPack("Sorted with BubbleSort");
    std::cout << "BubbleSort -> Comparisons: " << comparisons << ", Moves (Swaps): " << swaps << std::endl;

    // QuickSort detailed run
    // For a fair comparison, it's best to sort the same initial data.
    // Let's re-generate the same unsorted pack if possible, or just note a new random pack is used.
    // To ensure exact same pack, we would need to store it or reset RNG with same seed.
    // for simplicity, generating a new random pack is often accepted if stated.
    std::cout << "\n== QuickSort Detailed Run (N=" << detailedPackSize << ") ==" << std::endl;
    comparisons = 0; // Reset global comparisons for QuickSort
    int qsMoves = 0;
    int qsMaxDepth = 0;
    std::cout << "Generating new random pack for QuickSort..." << std::endl;
    for (int ct = 0; ct < detailedPackSize; ct++) {
        thePack[ct] = getCard(studentID);
    }
    printPack("Unsorted Pack");
    quickSort(0, detailedPackSize - 1, qsMoves, qsMaxDepth, 0);
    printPack("Sorted with QuickSort");
    std::cout << "QuickSort -> Comparisons: " << comparisons << ", Moves: " << qsMoves << ", Max Depth: " << qsMaxDepth << std::endl;

    // --- Phase 2: Data collection for the table ---
    std::cout << "\n\n--- Statistics for Table (Average of 1 run per pack size) ---" << std::endl;
    // Header for the table
    printf("+-----------+--------------------+------------------+-----------------+-----------------+-------------------+\n");
    printf("| Pack Size | BubbleSort Comps   | BubbleSort Moves | QuickSort Comps | QuickSort Moves | QuickSort MaxDepth|\n");
    printf("+-----------+--------------------+------------------+-----------------+-----------------+-------------------+\n");

    int packSizes[] = {5, 10, 20, 50};
    for (int currentPackSize : packSizes) {
        thePack.resize(currentPackSize); // Resize vector for current pack size

        // BubbleSort stats
        comparisons = 0;
        swaps = 0; // Reset for BubbleSort's moves
        for (int ct = 0; ct < currentPackSize; ct++) {
            thePack[ct] = getCard(studentID);
        }
        bubbleSort();
        int bsComps = comparisons;
        int bsMoves = swaps;

        // QuickSort stats
        comparisons = 0; // Reset global comparisons for QuickSort
        qsMoves = 0;     // Reset QuickSort specific moves
        qsMaxDepth = 0;  // Reset QuickSort specific depth
        for (int ct = 0; ct < currentPackSize; ct++) { // Regenerate pack for QuickSort
            thePack[ct] = getCard(studentID);
        }
        quickSort(0, currentPackSize - 1, qsMoves, qsMaxDepth, 0);
        int qComps = comparisons;
        // qsMoves and qsMaxDepth are already updated by reference

        printf("| %-9d | %-18d | %-16d | %-15d | %-15d | %-17d |\n",
               currentPackSize, bsComps, bsMoves, qComps, qsMoves, qsMaxDepth);
    }
    printf("+-----------+--------------------+------------------+-----------------+-----------------+-------------------+\n");

    return 0;
}