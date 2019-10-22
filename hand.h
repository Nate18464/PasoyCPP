//
// Created by Nathan on 10/19/2019.
//

#ifndef PASOY_HAND_H
#define PASOY_HAND_H

#include <algorithm>
#include <vector>
#include "card.h"

class Hand {
private:
    std::vector<Card> cards;
public:
    Hand(std::vector<int> ranCards);
    void PrintCards();
    bool HasLow();
    int Size();
    Card Get(int i);
    bool HasCards();
    void SortValSmallFirst();
    void SortValLargeFirst();
    void SortSuitSmallFirst();
    void SortSuitLargeFirst();
    void Erase(std::vector<int> indexes);
};

#endif //PASOY_HAND_H
