#ifndef ASSIGN2_BOT_H
#define ASSIGN2_BOT_H

#include "LinkedList.h"
#include "Board.h"
#include "Tile.h"
#include <string>

class QwirkleBot {
public:
   std::string getNextMove(LinkedList* hand, Board* board);
   QwirkleBot();
};

#endif // ASSIGN2_BOT_H
