//
// Created by Nathan on 10/19/2019.
//

#include "playhand.h"

    void PlayHand::Add(int card) {
        cards.push_back(Card(card));
    }
    int PlayHand::Size() {
        return cards.size();
    }
    Card PlayHand::Get(int i) {
        return cards[i];
    }
    bool PlayHand::AllSame() {
        for(unsigned int c = 1; c < cards.size(); c++) {
            if (Get(0).Num() != Get(c).Num()) {
                return false;
            }
        }
        return true;
    }
    bool PlayHand::FourOfAKind() {
        int same = 0;
        int numCheck = Get(0).Num();
        if (Get(2).Num() == Get(1).Num()) {
            numCheck = Get(1).Num();
        }
        for (int c = 0; c<=4; c++) {
            if (Get(c).Num() == numCheck) {
                same += 1;
            }
        }
        return same == 4;
    }
    bool PlayHand::FullHouse() {
        int countFirst = 1;
        for(int c = 1; c <= 4; c++) {
            if (Get(c).Num() == Get(0).Num()) {
                countFirst += 1;
            }
        }
        int countSecond = 1;
        int secondStart = 0;
        for(int c = 1; c <= 4; c++) {
            if (Get(0).Num() != Get(c).Num()) {
                secondStart = c;
                break;
            }
        }
        for(int c = secondStart+1; c <= 4; c++) {
            if (Get(secondStart).Num() == Get(c).Num()) {
                countSecond += 1;
            }
        }
        return ((countFirst == 3) && (countSecond == 2)) || ((countFirst == 2) && (countSecond == 3));
    }
    void PlayHand::SortNum() {
        for(int c = 0; c < Size(); c++) {
            int min = c;
            for(int i = c+1; i < Size(); i++) {
                if (Get(min).Num() > Get(i).Num()) {
                    min = i;
                }
            }
            if (c != min) {
                std::swap(cards[c], cards[min]);
            }
        }
    }
    bool PlayHand::Straight() {
        SortNum();
        int prev = Get(0).Num();
        bool b = true;
        for(int c = 1; c <= 4; c++) {
            if ((prev+1) != Get(c).Num()) {
                b = false;
            }
            prev = Get(c).Num();
        }
        if (b) {
            return Get(4).Num() != 12;
        }
        if (((Get(0).Num() != 0) || (Get(1).Num() != 1)) || (Get(2).Num() != 2)) {
            return false;
        }
        if ((Get(3).Num() == 11) && (Get(4).Num() == 12)) {
            return true;
        }
        if ((Get(4).Num() == 12) && (Get(3).Num() == 3)) {
            return true;
        }
        return false;
    }
    bool PlayHand::Flush() {
        int suit = Get(0).Suit();
        for(int c = 1; c <= 4; c++) {
            if (Get(c).Suit() != suit) {
                return false;
            }
        }
        return true;
    }
    bool PlayHand::operator > (PlayHand& rhs) {
        SortVal();
        rhs.SortVal();
        if (Size() != 5) {
            return Get(Size() - 1).Val() > rhs.Get(Size() - 1).Val();
        }
        int vallhs = 0;
        int valrhs = 0;
        if (Straight()) {
            vallhs = 1;
        } else if (Flush()) {
            vallhs = 2;
        } else if (FullHouse()) {
            vallhs = 3;
        } else {
            vallhs = 4;
        }
        if (rhs.Straight()) {
            valrhs = 1;
        } else if (rhs.Flush()) {
            valrhs = 2;
        } else if (rhs.FullHouse()) {
            valrhs = 3;
        } else {
            valrhs = 4;
        }
        if (vallhs > valrhs) {
            return true;
        } else if (vallhs < valrhs) {
            return false;
        }
        return Get(Size() - 1).Val() > rhs.Get(Size() - 1).Val();
    }

void PlayHand::Clear() {
    for (int c = Size()-1; c >= 0; c--) {
        cards.pop_back();
    }
}

void PlayHand::PrintHand() {
    if (Size() == 2) {
        std::cout << "A Pair:\n";
    } else if (Size() == 3) {
        std::cout << "A Three of a Kind:\n";
    } else if (Size() == 5) {
        if (Straight()) {
            std::cout << "A Straight:\n";
        } else if (Flush()) {
            std::cout << "A Flush:\n";
        } else if (FullHouse()) {
            std::cout << "A Full House:\n";
        } else {
            std::cout << "A Four of a Kind:\n";
        }
    }
    for (int c = 0; c < Size(); c++) {
        cards[c].PrintCards();
    }
    std::cout << std::endl;
}

void PlayHand::SortVal() {
    for(int c = 0; c < Size(); c++) {
        int min = c;
        for(int i = c+1; i < Size(); i++) {
            if (Get(min).Val() > Get(i).Val()) {
                min = i;
            }
        }
        if (c != min) {
            std::swap(cards[c], cards[min]);
        }
    }
}
