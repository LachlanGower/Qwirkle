#ifndef ASSIGN2_BAG_H
#define ASSIGN2_BAG_H

#include "Tile.h"
#include "TileCodes.h"
#include "LinkedList.h"

#include <string>
#include <random>

#define DUPLICATE_PIECE_AMOUNT     2

class Bag : public LinkedList{
public:

    Bag();
    Bag(LinkedList& other);
    Bag(std::string load);
    ~Bag();

private:
  
    void fill();
    void randomise();
    void randomise(int seed);

};
#endif