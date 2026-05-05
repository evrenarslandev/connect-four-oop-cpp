#include "ConnectFourAbstract.h"
#include <string>
#include <ctime>
#include <fstream>

HW4::ConnectFourAbstract::ConnectFourAbstract()
{
    rows = 5;
    columns = 5;
    gameBoard = new Cell *[rows]; /*dynamic array creation*/
    for (int i = 0; i < rows; i++)
    {
        gameBoard[i] = new Cell[columns];
        for (int j = 0; j < columns; j++)
        {
            gameBoard[i][j].setboard('A' + j, i + 1, true);
        }
    }
}

HW4::ConnectFourAbstract::ConnectFourAbstract(int row, int column)
{
    rows = row;
    columns = column;
    if (row < 5 || column < 5) /*error handling*/
    {
        cout << "Invalid values." << endl;
        exit(1);
    }
    gameBoard = new Cell *[rows];
    for (int i = 0; i < rows; i++)
    {
        gameBoard[i] = new Cell[columns];
        for (int j = 0; j < columns; j++)
        {
            gameBoard[i][j].setboard('A' + j, i + 1, true);
        }
    }
}

HW4::ConnectFourAbstract::ConnectFourAbstract(string filename)
{
    ifstream file(filename);
    string line;
    if (!file.is_open()) /*file open control*/
    {
        cout << "File cannot open." << endl;
        exit(1);
    }
    rows = 0;
    columns = 0;
    while (getline(file, line))
    {
        rows++;                      /*row number getter*/
        if (line.length() > columns) /*column number getter*/
        {
            columns = line.length();
        }
    }
    file.clear();                /*for return to files start*/
    file.seekg(0, ios::beg);     /*for return to files start*/
    if (rows > 0 && columns > 0) /*dynamic memory operations*/
    {
        gameBoard = new Cell *[rows];
        for (int i = 0; i < rows; i++)
        {
            gameBoard[i] = new Cell[columns];
        }
    }
    else
    {
        cout << "File is empty." << endl;
        exit(1);
    }
    int i = 0;
    while (getline(file, line))
    {
        for (int j = 0; j < columns; j++)
        {
            bool is_playable = (j < line.length() && line[j] == '*'); /*for checking if it is playable or not*/
            gameBoard[i][j].setboard('A' + j, i + 1, is_playable);
        }
        i++;
    }
    file.close();
}

void HW4::ConnectFourAbstract::printBoard() const
{
    cout << "  ";
    for (int j = 0; j < columns; j++) /*ABCDE... part*/
    {
        cout << (char)('A' + j) << " ";
    }
    cout << endl;
    for (int i = 0; i < rows; i++) /*row number + game map*/
    {
        cout << i + 1;
        if (i + 1 < 10)
        {
            cout << " ";
        }
        for (int j = 0; j < columns; j++)
        {
            cout << gameBoard[i][j] << " ";
        }
        cout << endl;
    }
}

int HW4::ConnectFourAbstract::play(Cell position, int turn)
{
    int rowCont = 0;
    int targetCol = position.getColumnPos() - 'A';
    if (targetCol < 0 || targetCol >= columns) /*error handling*/
    {
        cout << "Wrong input: Please input between A-" << (char)('A' + columns - 1) << "." << endl;
        return 1; /*we use return 1-0 at playGame function*/
    }

    while (gameBoard[rowCont][targetCol].getPlayState() == false) /*for get first playable place in target column*/
    {
        rowCont++;
    }
    if (rowCont > rows - 1) /*if there is not a playable cell, print error message*/
    {
        cout << "Error: target column is full." << endl;
        return 1;
    }

    if (gameBoard[rowCont][targetCol].getState() != '.') /*if target column is full, print error message*/
    {
        cout << "Error: target column is full." << endl;
        return 1;
    }
    for (int r = rows - 1; r >= 0; r--) /*find bottom playable cell and place user's state with ++ operator*/
    {
        if (gameBoard[r][targetCol].getState() == '.' && gameBoard[r][targetCol].getPlayState() == true)
        {
            if (turn == 2) /*1 ++ means *-->X, 2 ++ means *-->O, user2 is O*/
            {
                ++gameBoard[r][targetCol];
            }
            ++gameBoard[r][targetCol];
            return 0; /*1 = unsuccessful, 0 = successful*/
        }
    }
    return 1;
}

char HW4::ConnectFourAbstract::play()
{
    int colIndex;
    int tries = 0;
    do
    {
        colIndex = rand() % columns; /*random column selector*/
        tries++;
        if (tries > columns * 2) /*to prevent infinite loop*/
        {
            cout << "Board is full." << endl;
            exit(1);
        }
    } while (gameBoard[0][colIndex].getState() != '.' || gameBoard[0][colIndex].getPlayState() == false);
    /*do this while find a suitable place*/

    for (int r = rows - 1; r >= 0; r--) /*find bottom playable cell and place PC's state with ++ operator*/
    {
        if (gameBoard[r][colIndex].getState() == '.' && gameBoard[r][colIndex].getPlayState() == true)
        {
            ++gameBoard[r][colIndex]; /*2 times for O*/
            ++gameBoard[r][colIndex];
            return colIndex;
        }
    }
}

void HW4::ConnectFourAbstract::playGame(int mode)
{
    Cell user_input;
    bool control = false;
    int turn = 1;
    srand(time(0));
    cout << "-----Game starts-----" << endl;
    printBoard();
    if (mode == 1)
    {
        cout << "Players: User 1(X) and PC(O)" << endl;
    }
    else if (mode == 2)
    {
        cout << "Players: User 1(X) and User 2(O)" << endl;
    }
    while (!control) /*while game is not over, play the game*/
    {
        if (isGameOver())
        {
            control = true;
            break;
        }
        if (turn == 1)
        {
            int validCont;
            do /*get input while have a valid input, play functions 1 or 0 value used here*/
            {
                cout << "User1(X): Select a column:";
                cin >> user_input; /*>> overload*/
                if (cin.fail())
                {
                    cout << "Wrong input." << endl;
                    cin.clear();
                    cin.ignore(1000, '\n'); /*for clear input stream*/
                    continue;
                }
                validCont = play(user_input, turn);
            } while (validCont);
            turn = 2;
        }
        else
        {
            if (mode == 1) /*mode 1 = pc vs user, mode 2 = user vs user*/
            {
                cout << "PC(O)'s turn..." << endl;
                play();
            }
            else if (mode == 2) /*same with turn==1 part*/
            {
                int validCont;
                do
                {
                    cout << "User2(O): Select a column:";
                    cin >> user_input;
                    if (cin.fail())
                    {
                        cout << "Wrong input." << endl;
                        cin.clear();
                        cin.ignore(1000, '\n');
                        continue;
                    }
                    validCont = play(user_input, turn);
                } while (validCont);
            }
            turn = 1;
        }
        printBoard();
        if (isGameOver())
        {
            control = true;
            char winner;
            if (turn == 1)
            {
                winner = 'O';
            }
            else
            {
                winner = 'X';
            }
            if (!hasWon()) /*game over, but there is no winner, it means tie*/
            {
                cout << "Game is over! It's a tie." << endl;
            }
            else
            {
                cout << "Game is over! Winner is: " << winner << endl;
            }
        }
    }
}

bool HW4::ConnectFourAbstract::operator==(const ConnectFourAbstract &other) const
{
    if (rows != other.rows || columns != other.columns)
    {
        return false;
    }

    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < columns; ++j)
        {
            if (!(gameBoard[i][j] == other.gameBoard[i][j])) /*check cell by cell*/
            {
                return false;
            }
        }
    }
    return true;
}

bool HW4::ConnectFourAbstract::operator!=(const ConnectFourAbstract &other) const
{
    return !(*this == other);
}

HW4::ConnectFourAbstract::~ConnectFourAbstract()
{
    for (int i = 0; i < rows; i++)
    {
        delete[] gameBoard[i];
    }
    delete[] gameBoard;
    gameBoard = nullptr;
}

bool HW4::ConnectFourAbstract::isBoardFull() const
{
    for (int i = 0; i < rows; ++i)
        for (int j = 0; j < columns; ++j)
            if (gameBoard[i][j].getState() == '.' && gameBoard[i][j].getPlayState())
                return false;
    return true;
}

bool HW4::ConnectFourAbstract::checkHorizontal() const
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns - 3; j++)
        { 
            if (gameBoard[i][j].getState() == '.' || !gameBoard[i][j].getPlayState())
                continue;
            char p = gameBoard[i][j].getState();
            if (gameBoard[i][j + 1].getState() == p && gameBoard[i][j + 2].getState() == p && gameBoard[i][j + 3].getState() == p)
                return true;
        }
    }
    return false;
}

bool HW4::ConnectFourAbstract::checkVertical() const
{
    for (int i = 0; i < rows - 3; i++)
    { 
        for (int j = 0; j < columns; j++)
        {
            if (gameBoard[i][j].getState() == '.' || !gameBoard[i][j].getPlayState())
                continue;
            char p = gameBoard[i][j].getState();
            if (gameBoard[i + 1][j].getState() == p && gameBoard[i + 2][j].getState() == p && gameBoard[i + 3][j].getState() == p)
                return true;
        }
    }
    return false;
}

bool HW4::ConnectFourAbstract::checkDiagonal() const
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            if (gameBoard[i][j].getState() == '.' || !gameBoard[i][j].getPlayState())
                continue;
            char p = gameBoard[i][j].getState();

            if (i + 3 < rows && j + 3 < columns)
            {
                if (gameBoard[i + 1][j + 1].getState() == p && gameBoard[i + 2][j + 2].getState() == p && gameBoard[i + 3][j + 3].getState() == p)
                    return true;
            }
            if (i + 3 < rows && j - 3 >= 0)
            {
                if (gameBoard[i + 1][j - 1].getState() == p && gameBoard[i + 2][j - 2].getState() == p && gameBoard[i + 3][j - 3].getState() == p)
                    return true;
            }
        }
    }
    return false;
}
