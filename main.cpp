/// SortCard.cpp : This file contains the 'main' function. Program execution begins and ends there.
// RJM 6/2/24
#include <cstdlib>
#include <ctime>
#include "cardlib.h"
#include <string>
#include <iostream>
using namespace std;


// Make sure these functions are declared in cardlib.h and defined in cardlib.cpp
extern void generateCards(); // Fills 'thePack' with cards
extern void printPack(const string& mess);
extern void bubbleSort(); // Assume this sorts 'thePack'
// Remove the default argument here since it's already in the header file
extern void quickSort(int low, int high, int& moves, int& maxDepth, int depth);



const int maxCard = 20;
aCard thePack[maxCard];

int comparisons = 0;
int swaps = 0;

int partition(int low, int high, int& moves, int& maxDepth, int depth) {
    aCard pivot = thePack[high];
    int i = (low - 1);
    for (int j = low; j < high; j++) {
        comparisons++;
        if (compareCards(thePack[j], pivot) < 0) {
            i++;
            swap(thePack[i], thePack[j]);
            moves++;
        }
    }
    swap(thePack[i + 1], thePack[high]);
    moves++;
    return (i + 1);
}

void quickSort(int low, int high, int& moves, int& maxDepth, int depth) {
    if (low < high) {
        int pi = partition(low, high, moves, maxDepth, depth + 1);
        quickSort(low, pi - 1, moves, maxDepth, depth + 1);
        quickSort(pi + 1, high, moves, maxDepth, depth + 1);
        maxDepth = max(maxDepth, depth); // Track maximum recursion depth
    }
}







void swapCards(int n1, int n2) {
    if (n1 < 0 || n1 >= maxCard || n2 < 0 || n2 >= maxCard) {
        cout << "Index out of bounds" << endl;
        return;
    }
    swaps++; // Increment swap counter
    aCard temp = thePack[n1];
    thePack[n1] = thePack[n2];
    thePack[n2] = temp;
}








void printPack(const string& mess) {
    cout << mess << " : ";
    for (int i = 0; i < maxCard; i++) {
        cout << cardToStr(thePack[i]);
        if (i < maxCard - 1) {
            cout << ", ";
        }
    }
    cout << "\n";
}

void bubbleSort() {
    bool swapped;
    do {
        swapped = false;
        for (int i = 0; i < maxCard - 1; i++) {
            // Use compareCards to decide if a swap is needed
            if (compareCards(thePack[i], thePack[i + 1]) > 0) {
                swapCards(i, i + 1);
                swapped = true;
            }
        }
    } while (swapped);
}


int main() {


    cout << "Card Sorting!\n";
    srand(static_cast<unsigned int>(time(nullptr))); // Seed RNG once at the beginning


    for (int run = 0; run < 20; run++) {
        // Reset counters
        comparisons = 0;
        swaps = 0;


        // Populate 'thePack' with cards once
        for (int ct = 0; ct < maxCard; ct++) {
            thePack[ct] = getCard("32019071");
        }

        // Print each card's string representation
        for (int ct = 0; ct < maxCard; ct++) {
            cout << "Card " << ct + 1 << ": " << cardToStr(thePack[ct]) << "\n";
        }

        // Call 'printPack' to display the unsorted cards
        printPack("Unsorted");
        // Sort the pack using BubbleSort

        bubbleSort();

        // Print the sorted pack of cards
        printPack("Sorted");

        // Further actions like swapping cards and displaying sorted packs can be added here
        cout << "Total comparisons made: " << comparisons << endl;
        cout << "Total swaps made: " << swaps << endl;
        // Report the number of comparisons and swaps for this run
        cout << "Run " << (run + 1) << ": ";
        cout << "Comparisons: " << comparisons << ", Swaps: " << swaps << endl;


        cout << "Card Sorting with QuickSort!\n";
        comparisons = 0; // Reset comparisons
        int moves = 0; // Initialize move counter
        int maxDepth = 0; // Initialize maximum recursion depth counter

        quickSort(0, maxCard - 1, moves, maxDepth);
// Report metrics
        cout << "Total comparisons: " << comparisons << endl;
        cout << "Total moves: " << moves << endl;
        cout << "Maximum recursion depth: " << maxDepth << endl;


        cout << "Card Sorting Comparison between BubbleSort and QuickSort!\n";

        for (int seed = 100; seed < 110; seed++) { // Example seeds from 100 to 109
            srand(seed); // Set the seed for random number generator
            generateCards(); // Fill the pack with cards

            // BubbleSort
            cout << "Seed: " << seed << " - BubbleSort\n";
            bubbleSort(); // Sorts 'thePack' using BubbleSort algorithm
            printPack("Sorted with BubbleSort");

            // Reset for QuickSort with the same set of cards
            srand(seed); // Reset the seed to ensure same cards for QuickSort
            generateCards(); // Refill the pack with the same cards

            // QuickSort
            cout << "Seed: " << seed << " - QuickSort\n";
            int moves = 0, maxDepth = 0; // Variables to track QuickSort performance
            quickSort(0, maxCard - 1, moves, maxDepth); // Sorts 'thePack' using QuickSort algorithm
            printPack("Sorted with QuickSort");
            cout << "QuickSort Moves: " << moves << ", Max Depth: " << maxDepth << endl;
            // Ensure the random number generator is seeded.
            // Note: You usually only need to seed once, so consider moving srand() to the beginning of your main() if it's not already there.

            for (int i = 0; i < maxCard; i++) {
                thePack[i] = getCard("Some seed or unique identifier");
                // You'll need to adjust getCard() if it's supposed to use random values without specific input.
            }
        }
    }
}