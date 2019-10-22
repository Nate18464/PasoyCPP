//
// Created by Nathan on 10/19/2019.
//

#ifndef PASOY_CARD_H
#define PASOY_CARD_H
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>

class Card {
private:
    int suit;
    int num;
    int value;
    std::vector<std::string> suits;
    std::vector<std::string> nums;
public:
    Card() = delete;
    Card(int val);
    void PrintCards();
    int Val();
    int Suit();
    int Num();
};

#endif //PASOY_CARD_H
