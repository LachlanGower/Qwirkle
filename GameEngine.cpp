#include "GameEngine.h"
#include <fstream>
#include <iostream>

GameEngine::GameEngine()
{
    botAmount = 0;
    bot = new QwirkleBot();
}

GameEngine::~GameEngine()
{
    //if (!players.empty())
    {
        for (Player *player : players)
        {
            delete player;
        }
        players.clear();
    }
    if (board != nullptr)
    {
        delete board;
        board = nullptr;
    }
    if (bag != nullptr)
    {
        delete bag;
        bag = nullptr;
    }
    if (bot != nullptr)
    {
        delete bot;
        bot = nullptr;
    }
}

bool GameEngine::addPlayer(string name)
{
    bool check = true;
    if (nameAllowed(name))
    {
        //players.size() returns an unsigned int
        for (unsigned int i = 0; i < players.size(); ++i)
        {
            //only adds unique players
            if (players.at(i)->getName() == name)
            {
                check = false;
            }
        }
        if (check)
        {
            players.push_back(new Player(name));
        }
    }
    else
    {
        check = false;
    }
    return check;
}

bool GameEngine::addBot()
{
    bool botAdded = true;
    string name = "BOT" + std::to_string(botAmount);
    botAmount++;
    players.push_back(new Player(name, true));

    return botAdded;
}

bool GameEngine::nameAllowed(string name)
{
    return name.find_first_not_of("ABCDEFGHIJKLMNOPQRSTUVWXYZ") == std::string::npos;
}

void GameEngine::startGame()
{
    board = new Board();
    bag = new Bag();
    currentPlayer = PLAYER_ONE;
    //drawing player's hands from the bag
    for (Player *player : players)
    {
        while (player->handLength() < HAND_SIZE)
            player->addToHand(bag->takeFront());
    }
}

std::tuple<bool, bool, bool> GameEngine::placeTile(string tileString, string location)
{
    //if the move was valid
    bool validMove = false;
    //if there were any qwirkles
    bool qwirkle = false;
    //if the player's hand has been depleted
    bool gameOver = false;

    Tile *tile = new Tile(tileString.front(), tileString[1] - '0');
    if (players.at(currentPlayer)->inHand(tile))
    {
        int score = board->placeTileAt(tile, location);
        if (score > 0)
        {
            players.at(currentPlayer)->removeFromHand(tile);
            validMove = true;

            //max amount of points for a single tile placement (no qwirkle) = 10
            //min amount of points for a single tile placement (w/ qwirkle) = 12
            if (score >= QWIRKLE_SCORE)
                qwirkle = true;
            players.at(currentPlayer)->increaseScore(score);
            gameOver = endTurn();
        }
    }
    tile = nullptr;
    return std::make_tuple(validMove, qwirkle, gameOver);
}

bool GameEngine::replace(string tileString)
{
    bool check = false;
    Tile *tile = new Tile(tileString[0], tileString[1] - '0');
    if (players.at(currentPlayer)->inHand(tile) && bag->length() > 0)
    {
        players.at(currentPlayer)->removeFromHand(tile);
        bag->addBack(tile);
        players.at(currentPlayer)->addToHand(bag->takeFront());
        endTurn();
        check = true;
    }
    tile = nullptr;
    return check;
}

bool GameEngine::endTurn()
{

    bool gameOver = false;
    if (bag->length() == 0)
    {
        //if any player's have an empty hand, game is over
        for (unsigned int i = 0; i < players.size() && !gameOver; ++i)
        {
            if (players.at(i)->handLength() == 0)
            {
                gameOver = true;
            }
        }
    }
    else
    {
        //refill hand
        while (players.at(currentPlayer)->handLength() < HAND_SIZE && bag->length() > 0)
        {
            players.at(currentPlayer)->addToHand(bag->takeFront());
        }
    }
    //next players turn, circles around back to player 1
    currentPlayer = (currentPlayer + 1) % players.size();

    bool tileNotFound = true;
    if(!gameOver)
    {
        for (int i = 0; i < players.at(currentPlayer)->handLength() && tileNotFound; ++i)
        {
            tileNotFound = possibleMove(players.at(currentPlayer)->getHand()->getTileAt(i));
        }
        for (int j = 0; j < bag->length() && tileNotFound; ++j)
        {
            tileNotFound = possibleMove(bag->getTileAt(j));
        }
        if (tileNotFound)
        {
            gameOver = true;
        }
    }
    return gameOver;
}

bool GameEngine::possibleMove(Tile * tile)
{
    bool tileNotFound = true;
    for (int x = 0; x < board->width && tileNotFound; x++)
    {
        for (int y = 0; y < board->height && tileNotFound; y++)
        {
            int score = board->getScoreAtPosition(x, y, tile);
            if (score > INVALID)
            {
                tileNotFound = false;
            }
        }
    }
    return tileNotFound;
}

string GameEngine::getHighestScore()
{
    string winnerName = "";
    Player *winner = nullptr;
    int highscore = 0;
    for (Player *player : players)
    {
        if (player->getScore() > highscore)
        {
            highscore = player->getScore();
            winner = player;
        }
    }
    if (winner != nullptr)
    {
        winnerName = winner->getName();
    }
    return winnerName;
}

unsigned int GameEngine::getCurrentPlayer()
{
    return currentPlayer;
}

unsigned int GameEngine::getAmountOfPlayers()
{
    return players.size();
}

string GameEngine::getPlayerName(unsigned int player)
{
    return players.at(player)->getName();
}

int GameEngine::getPlayerScore(unsigned int player)
{
    return players.at(player)->getScore();
}

string GameEngine::getPlayerHand(unsigned int player)
{
    return players.at(player)->getHandAsString();
}

string GameEngine::getBoard()
{
    return board->toString();
}

string GameEngine::getBag()
{
    return bag->toString();
}

bool GameEngine::botTurn()
{
    return players.at(currentPlayer)->isBot();
}

// bool GameEngine::isPlayerBot(unsigned int i){
//     return players.at(i)->isBot();
// }

std::string GameEngine::getBotMove()
{
    return bot->getNextMove(players.at(currentPlayer)->getHand(), board);
}

bool GameEngine::saveGame(string filename)
{
    //stops tests from creating a file name ending in \r
    if(filename.find_first_of("\r") == filename.length()-1){
        filename.replace(filename.length()-1,filename.length(),"");
    }
    string fileString = "";
    std::ofstream myfile;
    myfile.open("saves/" + filename);
    for (unsigned int i = 0; i < getAmountOfPlayers(); i++)
    {
        myfile << getPlayerName(i) << std::endl
               << getPlayerScore(i) << std::endl
               << getPlayerHand(i) << std::endl
               << players.at(i)->isBot() << std::endl;

        fileString += getPlayerName(i);
        fileString += "\n";
        fileString += std::to_string(getPlayerScore(i));
        fileString += "\n";
        fileString += getPlayerHand(i);
        fileString += "\n";
        fileString += std::to_string(players.at(i)->isBot());
        fileString += "\n";
    }
    fileString += getBoard();
    fileString += getBag();
    fileString += "\n";
    fileString += getPlayerName(currentPlayer);

    std::hash<std::string> hash_fn;
    size_t hash = hash_fn(fileString);

    myfile << getBoard() << getBag() << std::endl
           << getPlayerName(currentPlayer) << std::endl
           << hash;
    myfile.close();

    return true;
}

//loads a save, hashing the contents of the file and comparing it to the hash at the bottom
bool GameEngine::checkHash(string filepath)
{
    string fileString = "";
    string line = "";
    std::ifstream myfile("saves/" + filepath);
    int fileLength = 0;
    if (myfile.is_open())
    {
        while (!myfile.eof())
        {
            getline(myfile, line);
            fileLength++;
        }
    }
    myfile.clear();
    myfile.seekg(0);

    if (myfile.is_open())
    {
        int i = 0;
        while (i < fileLength - 1)
        {
            getline(myfile, line);
            fileString += line;
            i++;
            if (i != fileLength - 1)
            {
                fileString += "\n";
            }
        }
    }

    std::hash<std::string> hash_fn;
    size_t hash = hash_fn(fileString);

    getline(myfile, line);
    bool hashMatch = false;
    if (line == "TEST")
    {
        hashMatch = true;
    }
    else if (line == std::to_string(hash))
    {
        hashMatch = true;
    }
    else
    {
        hashMatch = false;
    }

    myfile.close();

    return hashMatch;
}

bool GameEngine::loadGame(string filepath)
{
    bool check = false;
    if (checkHash(filepath))
    {
        string line = "";
        std::ifstream myfile("saves/" + filepath);
        if (myfile.is_open())
        {
            bool loadingPlayers = true;
            while (loadingPlayers)
            {
                getline(myfile, line);
                string name = line;
                if (line[0] != ' ')
                {
                    getline(myfile, line);
                    string score = line;
                    getline(myfile, line);
                    string hand = line;
                    getline(myfile, line);
                    string isbot = line;
                    players.push_back(new Player(name, score, hand, isbot));
                }
                else
                {
                    loadingPlayers = false;
                }
            }

            string boardString = line;
            getline(myfile, line);
            boardString += '\n' + line;
            bool loadingBoard = true;
            while (loadingBoard)
            {
                if (getline(myfile, line))
                {
                    if(line.length() > 5)
                    {
                        if (line[2] == '|')
                        {
                            boardString += '\n' + line;
                        }
                        else
                        {
                            loadingBoard = false;
                        }
                    }
                    else
                    {
                        loadingBoard = false;
                    }
                }
            }
            board = new Board(boardString);

            bag = new Bag(line);

            getline(myfile, line);
            for (unsigned int i = 0; i < getAmountOfPlayers(); i++)
            {
                if (line == getPlayerName(i))
                    currentPlayer = i;
            }
            check = true;
        }
    }
    else
    {
        check = false;
    }
    return check;
}