#include "QwirkleBot.h"
QwirkleBot::QwirkleBot(){

}
/* getNextMove()
 * iterates over the bots hand and finds the
 * highest scoring position by iterating over the board
 */
std::string QwirkleBot::getNextMove(LinkedList* hand, Board* board)
{
    std::string botCommand = "";
    bool tileNotFound = true;
    int highScore = INVALID;
    while(tileNotFound)
    {
        for(int t = 0; t < hand->length();t++)
        {
            for(int x = 0; x < board->width;x++)
            {
                for(int y = 0; y < board->height;y++)
                {
                    int score = board->getScoreAtPosition(x,y,hand->getTileAt(t));
                    if(score > INVALID)
                    {
                        if(score > highScore)
                        {
                            highScore = score;
                            tileNotFound = false;
                            std::string charX = std::to_string(x);
                            char charY = y + 'A';
                            botCommand = "place " + hand->getTileAt(t)->toString() + " at " + charY + charX + "\n";
                        }
                    }
                }
            }
        }
        if(tileNotFound)
        {
            botCommand = "replace " + hand->getTileAt(0)->toString() + '\n';
            tileNotFound = false;
        }
  }
  return botCommand;
}
