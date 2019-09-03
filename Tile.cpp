
#include "Tile.h"


Tile::Tile(Colour colour, Shape shape){
    this->colour = colour;
    this->shape = shape;
}

Tile::Tile(Tile& tile){
    colour = tile.colour;
    shape = tile.shape;
}

Colour Tile::getColour(){
    return colour;
}

Shape Tile::getShape(){
    return shape;
}

bool Tile::equals(Tile* tile){
    bool match = false;
    if(colourMatch(tile->getColour()) && shapeMatch(tile->getShape())){
        match = true;
    }

    return match;
}

bool Tile::colourMatch(Colour colour){
    bool match = false;
    if(this->colour == colour){
        match = true;
    }

    return match;
}

bool Tile::shapeMatch(Shape shape){
    bool match = false;
    if(this->shape == shape){
        match = true;
    }

    return match;
}

std::string Tile::toString(){
    std::string returnString = "";
    returnString += colour;
    returnString += std::to_string(shape);
    return returnString;
}
