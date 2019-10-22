//
// Created by Nathan on 10/19/2019.
//

#ifndef PASOY_PLAYHAND_H
#define PASOY_PLAYHAND_H

#include "card.h"

class PlayHand {
private:
    std::vector<Card> cards;
public:
    void Add(int card);
    int Size();
    Card Get(int i);
    bool AllSame();
    bool FourOfAKind();
    bool FullHouse();
    void SortNum();
    bool Straight();
    bool Flush();
    bool operator > (PlayHand& rhs);
    void Clear();
    void PrintHand();
    void SortVal();
};

#endif //PASOY_PLAYHAND_H
