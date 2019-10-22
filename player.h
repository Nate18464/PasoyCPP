//
// Created by Nathan on 10/19/2019.
//

#ifndef PASOY_PLAYER_H
#define PASOY_PLAYER_H

#include "hand.h"
#include "playhand.h"

class Player {
private:
    Hand cards;
    bool sortHighL = true;
    bool sortVal = true;
public:
    Player() = delete;
    Player(std::vector<int> ranCards);
    void PrintCards();
    bool HasLow();
    bool HasCards();
    int NumCards();
    bool ValidPlay(int numCards, PlayHand hand, bool first = false);
    bool CheckPlay(PlayHand turn, PlayHand prevplay);
    PlayHand GetPlay(int numCards, PlayHand prevplay);
    PlayHand GetFirstPlay(int numCards, bool first);
    void DoPlay(std::vector<int> indexes);
    int GetNumCards();
    void Turn(int& numCards, std::vector<PlayHand>& play, bool first = false);
    bool TurnArg(const int numcards, std::vector<PlayHand>& prevplays);
    void SortValSmallFirst();
    void SortValLargeFirst();
    void SortSuitSmallFirst();
    void SortSuitLargeFirst();
    void ChangeOrientation();
    int LastPlay(std::vector<PlayHand> prevPlays);
};

#endif //PASOY_PLAYER_H
