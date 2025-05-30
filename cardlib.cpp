//
// Created by zain_ on 06/03/2024.
//
//
// 6/2/24

#include "cardlib.h" // For the card library
#include <cstdlib>  // For srand and rand
#include <ctime>   // For time
#include <string> // For string
// using namespace std; // Avoid 'using namespace std;' in header or .cpp files if possible, prefer std::

// generateCards() was empty and unused, so it has been removed.

std::string cardToStr(aCard c) { // Convert a card to a string
    std::string cardValue; // The value of the card

    if (c.cardVal == 1) cardValue = "A"; // Ace
    else if (c.cardVal == 11) cardValue = "J"; // Jack
    else if (c.cardVal == 12) cardValue = "Q"; // Queen
    else if (c.cardVal == 13) cardValue = "K"; // King
    else cardValue = std::to_string(c.cardVal); // Numeric values 2-10

    // The suits of the cards (Corrected order for H, C, D, S)
    // Assuming enum Suit { hearts=0, clubs=1, diamonds=2, spades=3 };
    std::string suitChars = "HCDS"; // Hearts, Clubs, Diamonds, Spades
    char suitChar = suitChars[c.cardSuit]; // The suit of the card

    // Combine the value and suit for the final card representation.
    return cardValue + suitChar; // Return the card as a string
}

aCard getCard(std::string stdno) { // Get a random card from stdno
    static bool seeded = false; // Whether the random number generator has been seeded
    if (!seeded) { // If the random number generator has not been seeded
        srand(static_cast<unsigned>(time(nullptr))); // Seed the random number generator
        seeded = true; // The random number generator has been seeded
    }

    aCard ans; // The card to return
    // Ensure stdno has at least 1 character to avoid issues if it's empty, though assignment implies it's your student number
    if (stdno.empty()) {
        // Fallback or error, though problem implies stdno is provided
        // For now, let's make a simple fallback to avoid crash, but ideally stdno is always valid
        stdno = "00000000";
    }
    // The original logic for rcardstr could lead to issues if stdno.length() < 8.
    // A safer way if stdno can be short or to use all its digits:
    unsigned int hash = 0;
    for (char ch : stdno) {
        hash = hash * 31 + ch; // Simple hash
    }
    // Use two different random numbers to ensure more variability than just one.
    int r1 = rand();
    int r2 = rand();
    int rcard = (hash + r1 + r2) % 52; // Combine hash with rand() for better randomness from stdno

    ans.cardVal = 1 + rcard % 13; // Give cardVal 1-13
    ans.cardSuit = static_cast<Suit>(rcard / 13); // Determine the suit

    return ans;
}

int compareCards(aCard c1, aCard c2) { // Compares two cards
    comparisons++; // Increment comparison counter
    // First, compare by suit
    if (c1.cardSuit < c2.cardSuit) return -1; // If c1's suit is less than c2's suit
    if (c1.cardSuit > c2.cardSuit) return 1; // If c1's suit is greater than c2's suit

    // If suits are the same, then compare by card value
    // Assuming Ace is high (1) for comparison, or low. Current code treats 1 as low.
    // If Ace should be high (value 14 for sorting purposes), this logic needs adjustment:
    // int val1 = (c1.cardVal == 1) ? 14 : c1.cardVal;
    // int val2 = (c2.cardVal == 1) ? 14 : c2.cardVal;
    // if (val1 < val2) return -1;
    // if (val1 > val2) return 1;
    // Sticking to current: Ace (1) is the lowest value.
    if (c1.cardVal < c2.cardVal) return -1; // If c1's value is less than c2's value
    if (c1.cardVal > c2.cardVal) return 1; // If c1's value is greater than c2's value

    // Cards are identical
    return 0;
}