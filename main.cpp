#include "card.h"
#include "hand.h"
#include "player.h"
#include "board.h"
#include "playhand.h"

int main() {
    Board board = Board();
    board.SortCardsLargeFirst();
    board.Play();
    board.Win();
    return 0;
}