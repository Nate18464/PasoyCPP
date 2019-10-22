//
// Created by Nathan on 10/19/2019.
//

#include "hand.h"

Hand::Hand(std::vector<int> ranCards) {
    for (unsigned int c = 0; c < ranCards.size(); c++) {
        cards.push_back(Card(ranCards[c]));
    }
}

void Hand::PrintCards() {
    for (int c = 0; c < Size(); c++) {
        std::cout << "Card #" << c+1 << ": ";
        cards[c].PrintCards();
    }
}

bool Hand::HasLow() {
    for(int c = 0; c < Size(); c++) {
        if(cards[c].Val() == 0) {
            return true;
        }
    }
    return false;
}

int Hand::Size() {
    return cards.size();
}

Card Hand::Get(int i) {
    return cards[i];
}

bool Hand::HasCards() {
    return Size() != 0;
}

void Hand::SortValSmallFirst() {
    for(unsigned int c = 0; c < cards.size()-1; c++) {
        unsigned int min = c;
        for(unsigned int i = (c+1); i < cards.size(); i++) {
            if (Get(min).Val() > Get(i).Val()) {
                min = i;
            }
        }
        if (min != c) {
            std::swap(cards[min], cards[c]);
        }
    }
}

void Hand::SortValLargeFirst() {
    for(unsigned int c = 0; c < cards.size()-1; c++) {
        unsigned int max = c;
        for(unsigned int i = (c+1); i < cards.size(); i++) {
            if (Get(max).Val() < Get(i).Val()) {
                max = i;
            }
        }
        if (max != c) {
            std::swap(cards[max], cards[c]);
        }
    }
}

void Hand::SortSuitSmallFirst() {
    for (unsigned int c = 0; c < cards.size()-1; c++) {
        unsigned int min = c;
        for (unsigned int i = (c+1); i < cards.size(); i++) {
            if (Get(min).Suit() > Get(i).Suit()) {
                min = i;
            } else if (Get(min).Suit() == Get(i).Suit()) {
                if (Get(min).Num() > Get(i).Num()) {
                    min = i;
                }
            }
        }
        if (min != c) {
            std::swap(cards[min], cards[c]);
        }
    }
}

void Hand::SortSuitLargeFirst() {
    for (unsigned int c = 0; c < cards.size(); c++) {
        unsigned int max = c;
        for (unsigned int i = (c+1); i < cards.size(); i++) {
            if (Get(max).Suit() < Get(i).Suit()) {
                max = i;
            } else if (Get(max).Suit() == Get(i).Suit()) {
                if (Get(max).Num() < Get(i).Num()) {
                    max = i;
                }
            }
        }
        if (max != c) {
            std::swap(cards[max], cards[c]);
        }
    }
}

void Hand::Erase(std::vector<int> indexes) {
    std::sort(indexes.begin(), indexes.end());
    for (unsigned int c = indexes.size() - 1; c >= 0; c--) {
        cards.erase(cards.begin() + indexes[c]);
    }
}