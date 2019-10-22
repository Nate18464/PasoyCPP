//
// Created by Nathan on 10/19/2019.
//

#ifndef PASOY_BOARD_H
#define PASOY_BOARD_H

#include "player.h"

class Board {
private:
    std::vector<Player> players;
    int turn = 0;
    int numcards;
public:
    Board();
    void PrintCards();
    void SortCardsSmallFirst();
    void SortCardsLargeFirst();
    void SortCardsSuitSmallFirst();
    void SortCardsSuitLargeFirst();
    void NextTurn();
    void Play();
    void Win();
    void PrintPrev(std::vector<PlayHand> prevPlays);
};

#endif //PASOY_BOARD_H
