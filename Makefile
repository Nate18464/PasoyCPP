Pasoy: main.cpp board.cpp board.h card.cpp card.h hand.cpp hand.h player.cpp player.h playhand.cpp playhand.h
	g++ -Wall -Werror -std=c++11 -o Pasoy main.cpp board.cpp board.h card.cpp card.h hand.cpp hand.h player.cpp player.h playhand.cpp playhand.h -lm

clean:
	rm Pasoy