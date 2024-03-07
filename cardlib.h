//
// Created by zain_ on 06/03/2024.
//

#ifndef CARDPROGRAM_CARDLIB_H
#define CARDPROGRAM_CARDLIB_H


#include <string>
// In cardlib.h, add the function declaration

extern int comparisons;
extern int swaps;

enum Suit { hearts, clubs, diamonds, spades };      // define suits

struct aCard {                          // defines a card
    int cardVal;                        // number 1..13
    Suit cardSuit;                      // suit
};

std::string cardToStr(aCard c);			// declare function to represent a card as a two character string

aCard getCard(std::string stdno);        // declares function to get a card from stdno string
int compareCards(aCard c1, aCard c2);
void quickSort(int low, int high, int& moves, int& maxDepth, int depth = 0);

#endif //CARDPROGRAM_CARDLIB_H
