.default: all

all: qwirkle

clean:
	rm -rf qwirkle *.o *.dSYM

qwirkle: Bag.o Board.o GameEngine.o LinkedList.o Node.o Player.o qwirkle.o Tile.o QwirkleBot.o UI.o SharedFunction.o

	g++ -Wall -Werror -std=c++14 -g -O -o $@ $^

%.o: %.cpp
	g++ -Wall -Werror -std=c++14 -g -O -c $^
