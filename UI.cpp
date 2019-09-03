#include "UI.h"

UI::UI()
{
    this->engine = new GameEngine();
}

UI::~UI()
{
    delete engine;
    engine = nullptr;
}

void UI::menuOut(){
    cout << " Welcome to Qwirkle!" << endl
    << "--------------------" << endl
    << " Menu" << endl
    << "----" << endl
    << " 1 - New Game" << endl
    << " 2 - Load Game" << endl
    << " 3 - Show student information" << endl
    << " 4 - Quit" << endl
    << " Enter your choice and press return: " << endl
    << "> ";
}

void UI::newGame(){
    cout << "Starting a New Game" << endl << endl;
    bool endProgram = false;
    bool playersChosen = false;
    int players = 0;
    string input = "";
    while(!playersChosen && !endProgram)
    {
        cout << "How many Players?" << endl
        << "> ";
        cin >> input;
        if(cin.eof())
        {
            endProgram = true;
        }
        else if(input == "help")
        {
            cout << "Enter the numbers of human players that will be in the game as a single number from 0-4"
            << endl << "eg. 2" << endl;
        }
        else
        {
            players = input.at(0) - '0';
            if(cin.fail() || players < 0 || players > 4)
            {
                cout << "Invalid Number of Players, please enter a number between 0 and 4\n";
                cin.clear();
                cin.ignore();
            }
            else
            {
                playersChosen = true;
            }
        }
    }
    int bots = 0;
    input = "";
    bool botsChosen = false;
    while(!botsChosen && !endProgram)
    {
        cout << "How many Bots?" << endl
        << "> ";
        cin >> input;
        if(cin.eof())
        {
            endProgram = true;
        }
        else if(input == "help")
        {
            cout << "Enter the numbers of bots that will be in the game as a single number from 0-4 eg. 2"
            << endl << "eg. 2"
            << endl << "number of bots and players cannot exceed 4" << endl;
        }

        else
        {
            bots = input.at(0) - '0';
            if(cin.fail() || players + bots > 4 || bots + players < 2)
            {
                cout << "Invalid Number of Bots\n";
                cin.clear();
                cin.ignore();
            }
            else
            {
                botsChosen = true;
            }
        }
    }

    int i = 0;
    while(i != players + bots && !endProgram)
    {
        if(i < players)
        {
            string playerName;
            cout << "Enter a name for player " << (i+1) << "(uppercase characters only)" << endl
            << "> ";;
            cin >> playerName;
            if(cin.eof())
            {
                endProgram = true;
            }
            else if(playerName == "help")
            {
                cout << "Input name that the game will use to identify this player" << endl <<
                "Name can only include capitalised letters" << endl;
            }
            else if(engine->addPlayer(playerName))
            {
                ++i;
            }
        }
        else if(i >= players)
        {
            engine->addBot();
            ++i;
        }
    }
    if(!endProgram)
    {
        cout << "Let's Play" << endl << endl;
        engine->startGame();
        if(players > 0)
        {
            string clearline = "";
            std::getline(cin,clearline);
        }
        game();
    }
}

int UI::loadGame(){
    int loaded = 0;
    string filename;
    cout << "Enter the filename from which load a game" << endl
    << "> ";;
    cin >> filename;
    if(!cin.eof())
    {
        if(filename == "help"){
            cout << "Enter the filename for the save" << endl
            << "The filename will match what was set when the game was saved"
            << endl << "Look inside the saves folder if you are unsure of its name"
            << endl;
        }
        else if(engine->loadGame(filename))
        {
            cout << "Qwirkle game successfully loaded" << endl;
            loaded = 1;
        }
        else
        {
            cout << "Invalid File: does not exist/tampered with" << endl << endl;
        }
    }
    else
    {
        loaded = -1;
    }
    string clearline = "";
    std::getline(cin,clearline);
    return loaded;
}

void UI::showStudentInfo()
{
    cout << "---------------------------------\n";
    cout << "Name: Lachlan Gower\nStudent ID: s3723825\nEmail: s3723825@student.rmit.edu.au\n\n";
    cout << "Name: Will Ireland\nStudent ID: s3719036\nEmail: s3719036@student.rmit.edu.au\n\n";
    cout << "Name: Josephine Wong\nStudent ID: s3597422\nEmail: s3597422@student.rmit.edu.au\n\n";
    cout << "Name: Matthew Eletva\nStudent ID: s3716853\nEmail: s3716853@student.rmit.edu.au\n\n";
    cout << "---------------------------------\n";
}

void UI::menu()
{
    bool choiceNotMade = true;
    while(choiceNotMade)
    {
        menuOut();
        string choice;
        cin >> choice;
        if(!cin.eof())
        {
            if (choice.compare("1") == 0)
            {
                choiceNotMade = false;
                newGame();
            }
            else if (choice.compare("2") == 0)
            {
                int lg = loadGame();
                if(lg == 1)
                {
                    choiceNotMade = false;
                    game();
                }
                if(lg == -1){
                    choiceNotMade = false;
                }
            }
            else if (choice.compare("3") == 0)
            {
                showStudentInfo();
            }
            else if (choice.compare("4") == 0)
            {
                choiceNotMade = false;
            }
            else if (choice.compare("help") == 0)
            {
                cout<< "Enter \"1\" to start a new game!\n"
                    << "Enter \"2\" to load a file into the game\n"
                    << "Enter \"3\" to show the list of Students who worked on the game\n"
                    << "Enter \"4\" to Quit the Game\n"
                    << "Enter \"help\" to see this again\n"
                    << "Enter \"Ctrl-D\" to Exit the Game at anytime\n";
            }
            else
            {
                cout<< "Invalid Choice." << endl
                    << "Please use \"help\" to get a list of commands." << endl;
            }
        }
        else
        {
            choiceNotMade = false;
        }
    }
}

void UI::game()
{
    bool endGame = false;
    while(!endGame){
      endGame = newTurn();
    }
}
void UI::help()
{
    cout << "Commands\n" <<
            "place <tile> at <position> - E.g place R5 at A0\n"<<
            "replace <tile> - E.g replace R5\n"<<
            "save <filename> - save the current state of the game\n"<<
            "help - show this menu\n" <<
            "^D - exit program from command line\n";
}

bool UI::newTurn()
{
    unsigned int currentPlayer = engine->getCurrentPlayer();
    bool endgame = false;
    string input = "";
    cout << endl << engine->getPlayerName(currentPlayer) << ", it's your turn" << endl;
    printScore();
    cout<< engine->getBoard() << endl
        << "Your hand is" << endl << engine->getPlayerHand(currentPlayer) << endl << endl
        << "> ";;
    if(engine->botTurn())
    {
        input = engine->getBotMove();
        cout << input;
    }
    else
    {
        std::getline (cin, input);
    }
    std::vector<string> command = SharedFunction::split(input, ' ');
    if(!cin.eof())
    {
        if (command.front().compare("place") == 0 && command.size() == 4 && command.at(2).compare("at") == 0)
        {
            std::tuple<bool, bool, bool> result = engine->placeTile(command.at(1), command.at(3));
            if(!std::get<0>(result))
            {
                cout << input << ": ";
                cout << "Invalid move\n";
            }
            if(std::get<1>(result))
            {
                cout << "QWIRKLE!!!\n";
            }
            if(std::get<2>(result))
            {
                cout << engine->getBoard() << "Game over" << endl;
                printScore();
                cout << "Player " << engine->getHighestScore() << " wins!" << endl;
                endgame = true;
            }
        }
        else if (command.front().compare("replace") == 0 && command.size() == 2)
        {
            if(!engine->replace(command.at(1)))
            {
                cout << "Invalid Move" << endl;
            }
        }
        else if (command.front().compare("save") == 0 && command.size() == 2)
        {
            engine->saveGame(command.at(1));
            cout << "Game Saved.." << endl;
        }
        else if (command.front().compare("help") == 0)
        {
            help();
        }
        else
        {
            cout << input <<": ";
            cout << "Command Invalid, type \"help\" to get a list of commands\n";
        }
    }
    else
    {
      endgame = true;
    }
    return endgame;
}

void UI::printScore()
{
    for (unsigned int i = 0; i < engine->getAmountOfPlayers(); ++i)
    {
        cout<< "Score for " << engine->getPlayerName(i) << ": "
            << engine->getPlayerScore(i) << endl;
    }
}
