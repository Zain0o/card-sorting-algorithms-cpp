//
// Created by zain_ on 06/03/2024.
//

#ifndef CARDPROGRAM_CARDLIB_H
#define CARDPROGRAM_CARDLIB_H

#include <string> // For string

// These globals will be defined in main.cpp
extern int comparisons; // The number of comparisons
extern int swaps;       // The number of swaps (used by BubbleSort as moves)
// extern std::vector<aCard> thePack; // No, keep it defined in main.cpp

enum Suit { hearts, clubs, diamonds, spades }; // The suits of the cards

struct aCard {                         // A card
    int cardVal;                      // The value of the card
    Suit cardSuit;                      // The suit of the card
};

std::string cardToStr(aCard c);			// Convert a card to a string
aCard getCard(std::string stdno);       // Get a random card
int compareCards(aCard c1, aCard c2); // Compare two cards

// QuickSort prototype - definition will be in main.cpp
void quickSort(int low, int high, int& moves, int& maxDepth, int depth = 0);

#endif //CARDPROGRAM_CARDLIB_H