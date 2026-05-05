#include "ConnectFourPlusUndo.h"
#include <iostream>
#include <ctime>
#include <sstream>
using namespace std;

bool HW4::ConnectFourPlusUndo::hasWon() const
{
    return checkHorizontal() || checkVertical();           /*win conditions*/
}

bool HW4::ConnectFourPlusUndo::isGameOver() const
{
    return hasWon() || isBoardFull();
}

void HW4::ConnectFourPlusUndo::playGame(int mode)
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
            int yoruldum = 0;       /*for turn. 1 means user turn, 0 means user2 turn*/
            do /*get input while have a valid input, play functions 1 or 0 value used here*/
            {
                char temp;
                cout << "User1(X): Select a column(or '.' for undo):";     /*i use . for undo*/
                cin >> temp;
                if (temp == '.')
                {
                    if(mode == 1)       /*pc vs user*/
                    {
                        if(moves.size() >= 2)     /*check if there is moves for undoing or not*/
                        {
                            undo(turn);      /*pc undo*/
                            undo(2);         /*user undo*/
                            yoruldum = 1;    /*users turn again*/
                            continue;
                        }
                    }
                    else       /*user vs user*/
                    {
                        if(moves.size() >= 1)
                        {
                            undo(turn);
                            break;
                        }
                    }
                    cout << "No move to undo." << endl;
                    yoruldum = 1;
                }
                else
                {
                    string s(1, temp);
                    stringstream ss(s);
                    ss >> user_input; /*>> overload*/
                    moves.push_back(temp);
                    validCont = play(user_input, turn);
                }
            } while (validCont);
            if(yoruldum)
            {
                turn = 1;
            }
            else
            {
                turn = 2;
            }
        }
        else
        {
            if (mode == 1) /*mode 1 = pc vs user, mode 2 = user vs user*/
            {
                cout << "PC(O)'s turn..." << endl;
                char pcplay = play() + 'a'; /*play return column num in int*/
                moves.push_back(pcplay);
            }
            else if (mode == 2) /*same with turn==1 part*/
            {
                int validCont;
                do
                {
                    char temp;
                    cout << "User2(O): Select a column(or '.' for undo):";
                    cin >> temp;
                    if (temp == '.')
                    {
                        if(moves.size() >= 1)
                        {
                            undo(turn);
                            break;
                        }
                        else
                        {
                            cout << "No move to undo." << endl;
                        }
                    }
                    else
                    {
                        string s(1, temp);
                        stringstream ss(s);
                        ss >> user_input; /*>> overload*/
                        moves.push_back(temp);
                        validCont = play(user_input, turn);
                    }
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

void HW4::ConnectFourPlusUndo::undo(int mode)
{
    if (!moves.empty())
    {
        char lastPlay = moves.back();
        moves.pop_back();
        lastPlay = toupper(lastPlay);
        int targetCol = lastPlay - 'A';
        int rowCont = 0;
        while (gameBoard[rowCont][targetCol].getPlayState() == false)
        {
            rowCont++;
        }
        for (int r = rowCont; r < rows; r++) /*find bottom playable cell and place user's state with ++ operator*/
        {
            if (gameBoard[r][targetCol].getState() != '.' && gameBoard[r][targetCol].getPlayState() == true)
            {
                if (mode == 1) /*1 -- means X-->*, 2 -- means O-->*, user2/pc is O*/ 
                {
                    --gameBoard[r][targetCol];        /*mode 1 means its user1's turn so undo is on user2, so we do 2 times --*/
                }
                --gameBoard[r][targetCol];
                return;
            }
        }
    }
}
