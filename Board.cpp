#include "Board.h"

Board::Board()
{
    firstTurn = true;
    board = new Tile **[height];
    for(int i = 0; i < height;i++)
    {
        board[i] = new Tile*[width];
        for(int j = 0; j < width;j++)
            board[i][j] = nullptr;
        {
    }
}
/*  Board(string savedBoard)
 *  This function takes a string of a certain format and constructs a board from it
 *  The format must be "randomline\nrandomline\nA\n|  |\netc"
 *  |  | defines an empty tile, there must be the same amount of |  | on each Line
 *  the first line of tiles defines the width of this Board
 *  the every \n increments the height of this Board
 * no validation checks are done, invalid boards can be used for testing
 */
Board::Board(std::string savedBoard)
{
    firstTurn = true;
    width = 0;
    height = -1;
    bool tile = false;
    int length = savedBoard.length();
    //Set height and Width of Board
    for(int i = 0; i < length;i++)
    {
        if(savedBoard[i] == '|' && height < 2)
        {
            tile = !tile;
            if(tile == false)
            {
                width++;
            }
        }
        else if (savedBoard[i] == '\n')
        {
            height++;
            if(height < 1)
            {
                width = 0;
            }
        }
    }
    //Create Memory for Board, set all memory to nullptr
    board = new Tile **[height];
    for(int i = 0; i < height;i++)
    {
        board[i] = new Tile*[width];
        for(int j = 0; j < width;j++)
        {
            board[i][j] = nullptr;
        }
    }

    tile = false;
    int x = 0;
    int y = -2;
    int count = 0;
    char colour = 'A';
    //Add tiles to new board
    for(int i = 0; i < length;i++){
        if(tile == true && savedBoard[i] != '|')
        {
            //not an empty tile
            if(savedBoard[i] != ' ')
            {
                count++;
            }
            if(count == 1)
            {
                colour = savedBoard[i];
            }
            else if(count == 2)
            {
                board[y][x] = new Tile (colour, savedBoard[i] - '0');
                firstTurn = false;
                count = 0;
            }
        }
        //defines when a tile is found
        else if(savedBoard[i] == '|')
        {
            tile = !tile;
            if(tile == false)
            {
                x++;
            }
        }
        else if (savedBoard[i] == '\n')
        {
            y++;
            x = 0;
        }
    }
}

/* ~Board();
 * ~Boards main perogative is to delete Tiles and free the board array from memory
 */
Board::~Board()
{
    for(int j = 0; j < height; j++)
    {
        for(int i = 0; i < width; i++)
        {
            delete board[j][i];
        }
        delete[] board[j];
    }
    delete[] board;
}

/* placeTileAt(Tile,string)
 * Built for use by GameEngine
 * placeTileAt checks if a score at a position is greater than 0 (a valid move)
 * after this validation it will insert a tile into the board[][];
 */
int Board::placeTileAt(Tile* newTile, std::string position)
{
    int y = position[0] - (int) 'A';
    int x = stoi(position.substr(1,position.npos));
    int score = getScoreAtPosition(x,y,newTile);
    if(score > INVALID)
    {
        insert(newTile,x,y);
        firstTurn = false;
    }
    return score;
}
/* getScoreAtPosition(int,int,Tile)
 * Built for use by Board and QwirkleBot
 * this method prechecks position input and
 * calculates score based on validated lines
 * an invalid input will always return INVALID
 */
int Board::getScoreAtPosition(int x,int y,Tile* newTile)
{
    int score = 0;
    //if input is out of the bounds of the board
    if(width >= MAX && (x == MIN || x == MAX - 1))
    {
        score = INVALID;
    }
    else if(height >= MAX && (y == MIN || y == MAX - 1))
    {
        score = INVALID;
    }
    else if(x > width - 1 || y > height - 1 || y < 0 || x < 0)
    {
        score = INVALID;
    }
    //firstTurn, place anywhere(A0)
    if(score != INVALID && firstTurn)
    {
        score = 1;
    }
    else if(score != INVALID && board[y][x] == nullptr)
    {
        //get Length of Lines that Tile creates
        int length1 = validateLine(x,y,HORIZONTAL, newTile);
        int length2 = validateLine(x,y,VERTICAL, newTile);
        //tried to place a tile by itself
        if(length1 < 2 && length2 < 2)
        {
            length1 = INVALID;
            length2 = INVALID;
        }
        //calculate score
        if(length1 != INVALID && length2 != INVALID){
            score = length1 + length2;
            if(length1 == QWIRKLE)
            {
                score += QWIRKLE;
            }
            if(length2 == QWIRKLE)
            {
                score += QWIRKLE;
            }
        }
    }
    else
    {
        score = INVALID;
    }
    //Consolidate Output
    if(score == 0)
    {
      score = INVALID;
    }
    return score;
}

//returns the offset from x,y to the furthest left tile
int Board::getFarLeftTile(int x,int y)
{
    int i = 0;
    while(x + i - 1 > -1 && board[y][x + i - 1] != nullptr)
    {
        --i;
    }
    return i;
}

//returns the offset from x,y to the Highest Up tile
int Board::getHighestUpTile(int x,int y)
{
    int i = 0;
    while(y + i - 1 > -1 && board[y + i - 1][x] != nullptr)
    {
        --i;
    }
    return i;
}

/* validateLine()
 * This function is used to validate two important factors of a Line, its length and its matchCondition
 * the method begins by searching for the LEFT/UP-most tile from the x,y given
 * then to the RIGHT/DOWN-most tile while keeping count of the length of the line.
 * As the line is iterated over a matchCondition must be found,
 * if none are found or one is violated, validateLine is will return an invalid length value.
 */
int Board::validateLine(int x, int y, int axis, Tile* newTile)
{
    int i = 0;
    int j = 0;
    if(axis == HORIZONTAL)
    {
        i = getFarLeftTile(x,y);
    }
    else if(axis == VERTICAL)
    {
        j = getHighestUpTile(x,y);
    }
    int length = 0;
    int* match = new int(INVALID);
    while(y + j < height && x + i < width && (board[y + j][x + i] != nullptr || (y + j == y && x + i == x)))
    {
        if(y + j != y || x + i != x)
        {
            if(length == INVALID || !matchConditions(board[y+j][x+i], newTile, match))
            {
                length = INVALID;
            }
        }
        if(axis == HORIZONTAL)
        {
            ++i;
        }
        else if(axis == VERTICAL)
        {
            ++j;
        }

        if(length != INVALID)
        {
            ++length;
        }
    }
    if(length == 1)
    {
        length = 0;
    }
    delete match;
    return length;
}
/* matchConditions()
 * if the new tile matches a tile return false
 * if no matchCondition has been specified yet, find a matchCondition, if a matchCondition can't be found return false
 * if a matchCondition is already specified, but this tile does not match it return false
 * else return true.
 */
bool Board::matchConditions(Tile* tile, Tile* newTile, int* match)
{
    bool isValid = true;
    if(tile->colourMatch(newTile->getColour()) && tile->shapeMatch(newTile->getShape()))
    {
        isValid = false;
    }
    else if(*match == INVALID )
    {
        if(tile->colourMatch(newTile->getColour()))
        {
            *match = newTile->getColour();
        }
        else if(tile->shapeMatch(newTile->getShape()))
        {
            *match = newTile->getShape();
        }
        else
        {
            isValid = false;
        }
    }
    else
    {
        if(! (tile->colourMatch(*match) || tile->shapeMatch(*match) ) )
        {
            isValid = false;
        }
    }
    return isValid;
}

/*  insert()
 *  private method to insert on tiles in board[][]
 *  basically my own implementation of a 2D vector, more on this in report
 *
 */
void Board::insert(Tile* newTile, int x, int y)
{
    Tile*** tempBoard = nullptr;
    int xOffset = 0;
    int yOffset = 0;
    int widthOffset = 0;
    int heightOffset = 0;
    if(x == width - 1)
    {
        widthOffset++;
    }
    if(x == 0)
    {
        widthOffset++;
        xOffset = 1;
    }
    if(y == height - 1)
    {
        heightOffset++;
    }
    if(y == 0)
    {
        heightOffset++;
        yOffset = 1;
    }
    if(heightOffset > 0 || widthOffset > 0)
    {
        tempBoard = board;
        //set aside new place in memory
        board = new Tile **[height + heightOffset];
        for(int i = 0;i < height + heightOffset;i++)
        {
            board[i] = new Tile*[width + widthOffset];
            for(int j = 0;j < width + widthOffset;j++)
            {
                board[i][j] = nullptr;
            }
        }

        for(int i = 0; i < height; i++)
        {
            for(int j = 0; j < width; j++)
            {
                board[i+yOffset][j+xOffset] = tempBoard[i][j];
            }
        }
        //delete tempBoard from memory;
        //careful not to delete the Tile* as board needs them.
        for(int j = 0; j < height;j++)
        {
            delete[] tempBoard[j];
        }
        delete[] tempBoard;

        width = width + widthOffset;
        height = height + heightOffset;
    }
    board[y+yOffset][x+xOffset] = newTile;
}

/* toString()
 * returns a String in the exact way need to load this board back again
 */
std::string Board::toString(){
    std::string boardString = "  ";
    for(int i = 0;i < width;i++)
    {
        boardString += " ";
        boardString += std::to_string(i);
        if(i < 10)
        {
            boardString += " ";
        }
        boardString += " ";
    }
    boardString +="\n  ";
    for(int i = 0;i < width;i++)
    {
        boardString += "----";
    }
    boardString +="\n";
    for(int i = 0;i < height;i++)
    {
        char side = 'A' + i;
        boardString += side;
        boardString += " ";
        for(int j = 0;j < width;j++)
        {
            if(board[i][j] != nullptr)
            {
                boardString += "|" + board[i][j]->toString() + "|";
            }
            else
            {
                boardString += "|  |";
            }
        }
        boardString += "\n";
    }
    return boardString;
}
