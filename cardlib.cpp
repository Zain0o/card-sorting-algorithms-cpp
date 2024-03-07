//
// Created by zain_ on 06/03/2024.
//
// RJM's file for getting a random card
// 6/2/24

#include "cardlib.h"
#include <cstdlib> // For rand()
#include <ctime>   // For time()
#include <string>
using namespace std;

void generateCards() {

}




string cardToStr(aCard c) {
    string cardValue;
    // Convert the card's value to its string representation.
    if (c.cardVal == 1) cardValue = "A"; // Ace
    else if (c.cardVal == 11) cardValue = "J"; // Jack
    else if (c.cardVal == 12) cardValue = "Q"; // Queen
    else if (c.cardVal == 13) cardValue = "K"; // King
    else cardValue = to_string(c.cardVal); // Numeric values 2-10

    // Convert the card's suit to its string representation.
    string suits = "SHDC"; // Hearts, Clubs, Diamonds, Spades
    char suitChar = suits[c.cardSuit];

    // Combine the value and suit for the final card representation.
    return cardValue + suitChar;
}


aCard getCard(string stdno) {
    // Ensure the random number generator is seeded.
    static bool seeded = false;
    if (!seeded) {
        srand(static_cast<unsigned>(time(nullptr)));
        seeded = true;
    }

    aCard ans;
    string rcardstr = stdno.substr(rand() % 8, 1) + stdno.substr(rand() % 8, 1); // Two random characters from stdno
    int rcard = stoi(rcardstr) % 52; // Get integer in range 0-51

    ans.cardVal = 1 + rcard % 13; // Give cardVal 1-13
    ans.cardSuit = static_cast<Suit>(rcard / 13); // Determine the suit

    return ans;
}
int compareCards(aCard c1, aCard c2) {
    comparisons++; // Increment comparison counter
    // First, compare by suit
    if (c1.cardSuit < c2.cardSuit) return -1;
    if (c1.cardSuit > c2.cardSuit) return 1;

    // If suits are the same, then compare by card value
    if (c1.cardVal < c2.cardVal) return -1;
    if (c1.cardVal > c2.cardVal) return 1;

    // Cards are identical
    return 0;
}
