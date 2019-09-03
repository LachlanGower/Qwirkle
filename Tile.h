
#ifndef ASSIGN2_TILE_H
#define ASSIGN2_TILE_H

#include "TileCodes.h"

#include <string>

class Tile {
public:
   
   Tile(Colour colour, Shape shape);
   Tile(Tile& tile);

   Colour getColour();
   Shape getShape();
   
   bool equals(Tile* tile);
   bool colourMatch(Colour colour);
   bool shapeMatch(Shape shape);
   
   std::string toString();

private:
   
   Colour colour;
   Shape  shape;
   
};

#endif // ASSIGN2_TILE_H
