#include "board.h"
#include <random>
Board::Board() {
    std::vector<std::vector<int>> ranCards;
    for (int c = 0; c < 4; c++) {
        ranCards.push_back(std::vector<int>());
    }
    std::vector<int> ranInts;
    std::vector<int> sortInts;
    for (int c = 1; c <= 52; c++) {
        std::random_device rd;
        std::mt19937 eng(rd());
        std::uniform_int_distribution<> distr(0, 52 - c);
        int ranNum = distr(eng);
        ranInts.push_back(ranNum);
        sortInts.push_back(c - 1);
    }
    for (int c = 0; c <= 51; c++) {
        ranCards[c / 13].push_back(sortInts[ranInts[c]]);
        sortInts.erase(sortInts.begin() + ranInts[c]);
    }
    players.push_back(Player(ranCards[0]));
    players.push_back(Player(ranCards[1]));
    players.push_back(Player(ranCards[2]));
    players.push_back(Player(ranCards[3]));
    for (int c = 0; c <= 3; c++) {
        if (players[c].HasLow()) {
            turn = c;
            break;
        }
    }
    numcards = 0;
}

void Board::PrintCards() {
    int count = 1;
    for (unsigned int c = 0; c < players.size(); c++) {
        std::cout << "Player: " << count << std::endl;
        players[c].PrintCards();
        count += 1;
        std::cout << std::endl;
    }
}
void Board::SortCardsSmallFirst() {
    for (int c = 0; c < 4; c++) {
        players[c].SortValSmallFirst();
    }
}

void Board::SortCardsLargeFirst() {
    for (int c = 0; c < 4; c++) {
        players[c].SortValLargeFirst();
    }
}

void Board::SortCardsSuitSmallFirst() {
    for (int c = 0; c < 4; c++) {
        players[c].SortSuitSmallFirst();
    }
}

void Board::SortCardsSuitLargeFirst() {
    for (int c = 0; c < 4; c++) {
        players[c].SortSuitLargeFirst();
    }
}

void Board::NextTurn() {
    turn += 1;
    if (turn == 4) {
        turn = 0;
    }
    for (int c = 0; c < 50; c++) {
     std::cout << std::endl;
     }
     int nextPlayer;
     do {
     std::cout << "Are you player " << turn+1 << "? If so, type 1.\n";
     std::cin >> nextPlayer;
    } while (nextPlayer != 1);
}

void Board::Play() {
    bool first = true;
    while (true) {
        int numcards;
        std::vector<PlayHand> prevPlays;
        bool leave = false;
        if (!first) {
            std::cout << "You gained control.\n\n";
        } else {
            int startGame;
            do {
                std::cout << "Player " << turn+1 << " starts. (type 1 to start)\n";
                std::cin >> startGame;
            } while (startGame != 1);
        }
        players[turn].Turn(numcards, prevPlays, first);
        first = false;
        int countPass = 0;
        while ((countPass < 3) && players[turn].HasCards()) {
            for (int c = 0; c < 4; c++) {
                if (!players[c].HasCards()) {
                    leave = true;
                }
            }
            if (leave) {
                break;
            }
            NextTurn();
            if (prevPlays.size() != 0) {
                std::cout << "You must play a " << numcards << " card hand." << std::endl << std::endl;
            }
            PrintPrev(prevPlays);
            bool pass = players[turn].TurnArg(numcards, prevPlays);
            if (prevPlays.size() > 3) {
                prevPlays.erase(prevPlays.begin() + 3);
            }
            if (pass) {
                countPass += 1;
            } else {
                countPass = 0;
            }
        }
        for (int c = 0; c < 4; c++) {
            if (!players[c].HasCards()) {
                leave = true;
            }
        }
        if (leave) {
            break;
        }
        NextTurn();
    }
}

void Board::Win() {
    for (int c = 0; c < 4; c++) {
        if (!players[c].HasCards()) {
            std::cout << "Player " << c+1 << " won!";
        }
    }
}

void Board::PrintPrev(std::vector<PlayHand> prevPlays) {
    int player = turn;
    player -= prevPlays.size();
    if (player <= 0) {
        player += 4;
    }
    for (int c = prevPlays.size()-1; c >= 0; c--) {
        player++;
        if (player >= 5) {
            player -= 4;
        }
        if (prevPlays[c].Size() > 0) {
            std::cout << "Player " << player << " played:\n";
            prevPlays[c].PrintHand();
        } else {
            std::cout << "Player " << player << " passed.\n\n";
        }
    }
}
