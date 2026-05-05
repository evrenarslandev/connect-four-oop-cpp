#include "Cell.h"
#include "ConnectFourAbstract.h"
#include "ConnectFourDiag.h"
#include "ConnectFourPlus.h"
#include "ConnectFourPlusUndo.h"


int main()
{
    int choiceStart, choiceMode, row, column, option;
    string filename;
    HW4::ConnectFourAbstract* gamePtr = nullptr;
    cout << "WELCOME TO OUR CONNECT FOUR GAME!" << endl;
    cout << "Please select a start:" << endl;
    cout << "1-Basic(5x5)" << endl << "2-Selected" << endl << "3-From file" << endl;
    cin >> choiceStart;
    if(choiceStart > 3 || choiceStart < 1)
    {
        cout << "Wrong input. Game terminated";
        return 1;
    }
    cout << "Please select a mode:" << endl;
    cout << "1-Plus mode" << endl << "2-Diag mode" << endl << "3-Undo mode" << endl;
    cin >> choiceMode;
    if(choiceMode > 3 || choiceMode < 1)
    {
        cout << "Wrong input. Game terminated";
        return 1;
    }
    if(choiceStart == 1)
    {
        if(choiceMode == 1)
        {
            gamePtr = new HW4::ConnectFourPlus;
        }
        else if(choiceMode == 2)
        {
            gamePtr = new HW4::ConnectFourDiag;
        }
        else
        {
            gamePtr = new HW4::ConnectFourPlusUndo;
        }
    }
    else if(choiceStart == 2)
    {
        cout << "Please enter size(row col): ";
        cin >> row >> column;
        if(row < 5 || column < 5)
        {
            cout << "You need to enter a bigger size than 5x5. Game terminated." << endl;
            return 1;
        }
        if(choiceMode == 1)
        {
            gamePtr = new HW4::ConnectFourPlus(row, column);
        }
        else if(choiceMode == 2)
        {
            gamePtr = new HW4::ConnectFourDiag(row, column);
        }
        else
        {
            gamePtr = new HW4::ConnectFourPlusUndo(row, column);
        }
    }
    else
    {
        cout << "Please enter the file name:";
        cin >> filename;
        if(choiceMode == 1)
        {
            gamePtr = new HW4::ConnectFourPlus(filename);
        }
        else if(choiceMode == 2)
        {
            gamePtr = new HW4::ConnectFourDiag(filename);
        }
        else
        {
            gamePtr = new HW4::ConnectFourPlusUndo(filename);
        }
    }
    cout << "Please select game mode(1 for user vs pc, 2 for user vs user): ";
    cin >> option;
    if(option != 1 && option != 2)    /*error handling*/
    {
        cout << "Wrong input. Program terminated.";
        if (gamePtr) delete gamePtr;        /*to prevent memory leak*/
        return 1;
    }
    gamePtr->playGame(option);        /*play game*/
    if (gamePtr)                /*to prevent memory leak*/
    {
        delete gamePtr;
    }
    return 0;
}