#ifndef ASSIGN2_BOARD_H
#define ASSIGN2_BOARD_H

#define INVALID     -1
#define QWIRKLE     6
#define HORIZONTAL  0
#define VERTICAL    1
#define MAX         26
#define MIN         0

#include "Tile.h"
#include <string>

class Board {
public:
   Board();
   Board(std::string savedBoard);
   ~Board();
   int placeTileAt(Tile* tile, std::string position);
   int getScoreAtPosition(int x,int y,Tile* newTile);
   std::string toString();
   int width = 1;
   int height = 1;


private:
  Tile*** board = nullptr;
  bool firstTurn;
  int getFarLeftTile(int x,int y);
  int getHighestUpTile(int x,int y);
  bool matchConditions(Tile* tile, Tile* newTile, int* match);
  int validateLine(int x, int y, int axis, Tile* newTile);
  void insert(Tile* newTile, int x, int y);
};

#endif // ASSIGN2_BOARD_H
