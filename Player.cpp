#include "Player.h"

Player::~Player(){
    delete hand;
}

Player::Player(Player& other){
    this->name = other.name;
    this->score = other.score;
    this->hand = new LinkedList(*(other.hand));
    this->bot = other.bot;
}

Player::Player(std::string name){
    this->name= name;
    score = 0;
    hand = new LinkedList();
    bot = false;
}

Player::Player(std::string name, bool bot){
    this->name= name;
    score = 0;
    hand = new LinkedList();
    this->bot = bot;
}

Player::Player(std::string name, std::string score, std::string newHand, std::string isBot){
    this->name= name;
    this->score = std::stoi(score);
    hand = new LinkedList(newHand);
    bot = std::stoi(isBot);
}

std::string Player::getName(){
    return name;
}

int Player::getScore(){
    return score;
}

void Player::increaseScore(int increaseAmount){
    score += increaseAmount;
}

bool Player::inHand(Tile* tile){
    return hand->contains(tile);
}

bool Player::removeFromHand(Tile* tile){
    return hand->takeTile(tile);
}

void Player::addToHand(Tile* tile){
    hand->addBack(tile);
}

std::string Player::getHandAsString(){
    return hand->toString();
}

Hand Player::getHand(){
    return hand;
}

int Player::handLength(){
    return hand->length();
}

bool Player::isBot(){
    return bot;
}
