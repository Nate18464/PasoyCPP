//
// Created by Nathan on 10/19/2019.
//
#include "player.h"
Player::Player(std::vector<int> ranCards): cards(Hand(ranCards)) {}
void Player::PrintCards() {
    cards.PrintCards();
}
bool Player::HasLow() {
    return cards.HasLow();
}
bool Player::HasCards() {
    return cards.HasCards();
}
int Player::NumCards() {
    return cards.Size();
}
bool Player::ValidPlay(int numCards, PlayHand hand, bool first)  {
    if (hand.Size() != numCards) {
        return false;
    }
    hand.SortVal();
    if (first) {
        if (hand.Get(0).Val() != 0) {
            return false;
        }
    }
    if (numCards == 1) {
        return true;
    }
    if (numCards == 2) {
        return hand.AllSame();
    }
    if (numCards == 3) {
        return hand.AllSame();
    }
    if (numCards == 5) {
        if (hand.FourOfAKind()) {
            return true;
        }
        if (hand.Straight()) {
            return true;
        }
        if (hand.Flush()) {
            return true;
        }
        if (hand.FullHouse()) {
            return true;
        }
    }
    return false;
} bool Player::CheckPlay(PlayHand turn, PlayHand prevplay) {
    if (turn.Size()!= prevplay.Size()) {
        return false;
    }
    return turn > prevplay;
}

PlayHand Player::GetPlay(int numCards, PlayHand prevplay) {
    PlayHand play = PlayHand();
    std::vector<int> indexes;
    std::cout << "What cards do you want to play? (Please type one number, enter, and continue for however many cards you want.\n"
                 << "Or do you want to switch the organization of your cards (type \"-1\")\n";
    std::cout << "If you messed up and would like to pass, type -2.\n";
    for (int c = 1; c <= numCards; c++) {
        int card;
        std::cin >> card;
        if (card == -1) {
            return GetPlay(numCards,prevplay);
        }
        if (card == -2) {
            throw std::exception();
        }
        if (--card >= 0 && card < cards.Size()) {
            play.Add(cards.Get(card).Val());
            indexes.push_back(card);
        }
    }
    while (!ValidPlay(numCards, play) || !CheckPlay(play, prevplay)) {
        play.Clear();
        std::cout << "Invalid Play, try again.\n";
        for (int c = indexes.size()-1; c >= 0; c--) {
            indexes.pop_back();
        }
        for (int c = 1; c <= numCards; c++) {
            int card;
            std::cin >> card;
            if (card == -1) {
                return GetPlay(numCards, prevplay);
            }
            if (card == -2) {
                throw std::exception();
            }
            if (--card >= 0 && card < cards.Size()) {
                play.Add(cards.Get(card).Val());
                indexes.push_back(card);
            }
        }
    }
    DoPlay(indexes);
    return play;
}

PlayHand Player::GetFirstPlay(int numCards, bool first) {
    PlayHand play = PlayHand();
    std::vector<int> indexes;
    std::cout << "What cards do you want to play? (Please type one number, enter, and continue for however many cards you want.\n"
              << "Or do you want to switch the organization of your cards? (type -1)\n";
    std::cout << "If you messed up on how many cards you wanted, type -2.\n";
    for (int c = 1; c <= numCards; c++) {
        int card;
        std::cin >> card;
        if (card == -1) {
            return GetFirstPlay(numCards, first);
        }
        if (card == -2) {
            throw std::exception();
        }
        if (--card >= 0 && card < cards.Size()) {
            play.Add(cards.Get(card).Val());
            indexes.push_back(card);
        }
    }
    while (!ValidPlay(numCards, play, first)) {
        play.Clear();
        for (int c = indexes.size()-1; c >= 0; c--) {
            indexes.pop_back();
        }
        std::cout << "Invalid play try again." << std::endl;
        for (int c = 1; c <= numCards; c++) {
            int card;
            std::cin >> card;
            if (card == -1) {
                return GetFirstPlay(numCards, first);
            }
            if (card == -2) {
                throw std::exception();
            }
            if (--card >= 0 && card < cards.Size()) {
                play.Add(cards.Get(card).Val());
                indexes.push_back(card);
            }
        }
    }
    DoPlay(indexes);
    return play;
}

void Player::DoPlay(std::vector<int> indexes) {
    cards.Erase(indexes);
}

int Player::GetNumCards() {
    std::cout << "These are your cards:\n";
    PrintCards();
    std::string numCards;
    std::cout << "Please enter the number of cards you want to use or to switch the organization of your cards, type \"swap\".\n";
    std::cin >> numCards;
    while(numCards != "1" && numCards != "2" && numCards != "3" && numCards != "5" ) {
        if (numCards == "swap") {
            ChangeOrientation();
            return GetNumCards();
        } else {
            std::cout << "Invalid Input try again\n";
            std::cin >> numCards;
        }
    }
    return stoi(numCards);
}

void Player::Turn(int& numCards, std::vector<PlayHand>& play, bool first) {
    numCards = GetNumCards();
    if (play.size() == 0) {
        try {
            play.insert(play.begin(), GetFirstPlay(numCards, first));
        } catch(...) {
            Turn(numCards, play, first);
        }
    } else {
        play.insert(play.begin(), GetPlay(numCards, play[0]));
    }
}

bool Player::TurnArg(const int numcards, std::vector<PlayHand>& prevplays) {
    std::cout << "These are your cards:\n";
    PrintCards();
    std::cout << "Do you want to play? (1 to play, 0 to pass) Or do you want to switch the organization of your cards (type -1)" << std::endl;
    int pass;
    std::cin >> pass;
    while (pass != 1) {
        if (pass == 0) {
            prevplays.insert(prevplays.begin(), PlayHand());
            return true;
        } else if (pass == -1) {
            ChangeOrientation();
            return TurnArg(numcards, prevplays);
        }
        std::cout << "Invalid input try again.\n";
        std::cin >> pass;
    }
    int lastPlay = LastPlay(prevplays);
    try {
        prevplays.insert(prevplays.begin(), GetPlay(numcards, prevplays[lastPlay]));
    } catch(...) {
        return TurnArg(numcards, prevplays);
    }
    return false;
}

void Player::SortValSmallFirst() {
    cards.SortValSmallFirst();
}

void Player::SortValLargeFirst() {
    cards.SortValLargeFirst();
}

void Player::SortSuitSmallFirst() {
    cards.SortSuitSmallFirst();
}

void Player::SortSuitLargeFirst() {
    cards.SortSuitLargeFirst();
}

void Player::ChangeOrientation() {
    std::cout << "Enter 1 for Large value first, 2 for Small value first, 3 for Large Suit first, or 4 for Small Suit first\n";
    std::string input;
    std::cin >> input;
    while (input != "1" && input != "2" && input != "3" && input != "5") {
        std::cout << "Invalid input try again" << std::endl;
        std::cin >> input;
    }
    if (input == "1") {
        SortValLargeFirst();
    } else if (input == "2") {
        SortValSmallFirst();
    } else if (input == "3") {
        SortSuitLargeFirst();
    } else {
        SortSuitSmallFirst();
    }
}

int Player::LastPlay(std::vector<PlayHand> prevPlays) {
    for (unsigned int c = 0; c < prevPlays.size(); c++) {
        if (prevPlays[c].Size() != 0) {
            return c;
        }
    }
    throw std::exception();
}
