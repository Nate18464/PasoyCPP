//
// Created by Nathan on 10/19/2019.
//

#include "card.h"

Card::Card(int val) {
    value = val;
    num = (val/4);
    suit = (val%4);
    suits = {"Diamonds", "Clubs", "Hearts", "Spades"};
    nums = {"Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Jack", "Queen", "King", "Ace", "Two"};
}

void Card::PrintCards() {
    std::cout << nums[num] << " of " << suits[suit] << std::endl;
}

int Card::Val() {
    return value;
}

int Card::Suit() {
    return suit;
}

int Card::Num() {
    return num;
}