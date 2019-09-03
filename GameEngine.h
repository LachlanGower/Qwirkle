
#ifndef ASSIGN2_GAMEENGINE_H
#define ASSIGN2_GAMEENGINE_H

#include "Player.h"
#include "Board.h"
#include "Bag.h"
#include "QwirkleBot.h"
#include <vector>
#include <tuple>
#include <string>
#include <functional>

//used when retrieving players from vector
#define PLAYER_ONE 0
#define PLAYER_TWO 1
#define PLAYER_THREE 2
#define PLAYER_FOUR 3
#define MAX_PLAYERS 4
#define QWIRKLE_SCORE 12

#define HAND_SIZE 6

using std::string;

class GameEngine
{
public:
    GameEngine();
    ~GameEngine();

    bool addPlayer(string name);
    bool addBot();
    bool loadGame(string filepath);
    bool saveGame(string filename);
    void startGame();

    std::tuple<bool, bool, bool> placeTile(string tile, string location);
    bool replace(string tile);
    bool endTurn();

    bool botTurn();
    std::string getBotMove();

    unsigned int getCurrentPlayer();
    string getPlayerName(unsigned int player);
    int getPlayerScore(unsigned int player);
    string getPlayerHand(unsigned int player);
    unsigned int getAmountOfPlayers();
    string getBag();
    string getBoard();
    string getHighestScore();

private:
    QwirkleBot *bot;
    std::vector<Player *> players;
    int botAmount;
    Bag *bag;
    Board *board;
    int currentPlayer;

    bool possibleMove(Tile * tile);

    bool nameAllowed(string name);
    bool checkHash(string filepath);

    bool colourCheck(Colour tileColour);
    bool shapeCheck(Shape tileShape);
};

#endif // ASSIGN2_GAMEENGINE_H
