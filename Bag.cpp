
#include "Bag.h"


Bag::Bag() : LinkedList(){
    fill();
    randomise();
}

Bag::Bag(LinkedList& otherBag) : LinkedList(otherBag){

}

Bag::Bag(std::string load) : LinkedList(load){

}

Bag::~Bag(){

}

void Bag::fill(){
    Colour colours[6] = {RED, ORANGE, YELLOW, GREEN, BLUE, PURPLE};
    Shape shapes[6] = {CIRCLE, STAR_4, DIAMOND, SQUARE, STAR_6, CLOVER};

    for(int i = 0; i < DUPLICATE_PIECE_AMOUNT; i++){
        for(Colour colour : colours){
            for(Shape shape : shapes){
                addFront(new Tile(colour, shape));
            }
        }
    }
}

void Bag::randomise(){
    //https://www.rosettacode.org/wiki/Knuth_shuffle

    int size = length();
    std::vector<Tile*> tiles;
    for (int i = 0; i < size; i++){
        tiles.push_back(takeFront());
    }

    std::random_device engine;
    std::uniform_int_distribution<int> uniform_dist(0, size-1);

    for (int i = 0; i < size; i++){
        int swapLocation = uniform_dist(engine);
        std::swap(tiles[i], tiles[swapLocation]);
    }

    for (int i = 0; i < size; i++){
        addFront(tiles.at(i));
    }

}

//testing method
void Bag::randomise(int seed){
    //https://www.rosettacode.org/wiki/Knuth_shuffle

    int size = length();
    std::vector<Tile*> tiles;
    for (int i = 0; i < size; i++){
        tiles.push_back(takeFront());
    }

    std::default_random_engine engine(seed);
    std::uniform_int_distribution<int> uniform_dist(0, size-1);

    for (int i = 0; i < size; i++){
        int swapLocation = uniform_dist(engine);
        std::swap(tiles[i], tiles[swapLocation]);
    }

    for (int i = 0; i < size; i++){
        addFront(tiles.at(i));
    }

}