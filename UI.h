#ifndef ASSIGN2_UI_H
#define ASSIGN2_UI_H

#include "GameEngine.h"
#include <vector>
#include "SharedFunction.h"
#include "QwirkleBot.h"
#include <iostream>
#include <string>
#include <sstream>

using std::cout;
using std::cin;
using std::string;
using std::endl;


class UI{
public:

   UI();
   ~UI();
   void menu();
private:
   GameEngine * engine;
   void game();
   bool newTurn();
   string getCommand();
   void menuOut();
   void newGame();
   int loadGame();
   void showStudentInfo();
   void help();
   void printScore();
   std::vector<string> split(std::string stringToSplit, char delim);

};

#endif // ASSIGN2_UI_H
