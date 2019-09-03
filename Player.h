#ifndef ASSIGN2_PLAYER_H
#define ASSIGN2_PLAYER_H

#include "LinkedList.h"
#include "Tile.h"

#include <string>

typedef LinkedList* Hand;

class Player{
public:

    Player(std::string name);
    Player(std::string name, bool bot);
    Player(Player& other);
    Player(std::string name, std::string score, std::string newHand, std::string isBot);
    ~Player();

    void increaseScore(int increaseAmount);
    bool inHand(Tile* tile);
    bool removeFromHand(Tile* tile);
    void addToHand(Tile* tile);
    int handLength();
    
    std::string getName();
    int getScore();
    std::string getHandAsString();
    Hand getHand();
    bool isBot();

private:

    bool bot;
    std::string name;
    int score;
    Hand hand;

};

#endif
