#ifndef CONNECTFOURABSTRACT_H
#define CONNECTFOURABSTRACT_H
#include "Cell.h"
#include <iostream>
using namespace std;

namespace HW4
{
    class ConnectFourAbstract /*our main class*/
    {
    public:
        ConnectFourAbstract();
        ConnectFourAbstract(int row, int column);

        ConnectFourAbstract(string filename);
        void printBoard() const;
        int play(Cell position, int turn);         /*player play*/
        char play();                               /*pc play*/
        virtual bool isGameOver() const = 0;        /*different for plus/diag*/
        virtual bool hasWon() const = 0;            /*different for plus/diag*/
        virtual void playGame(int mode);            /*virtual for undo*/
        bool operator==(const ConnectFourAbstract &other) const;
        bool operator!=(const ConnectFourAbstract &other) const;
        virtual ~ConnectFourAbstract();

    protected:
        Cell **gameBoard; /*our 2d board*/
        int rows;         /*row num*/
        int columns;      /*column num*/
        bool isBoardFull() const;        /*full(for tie) control*/
        bool checkHorizontal() const;    /*for plus*/
        bool checkVertical() const;      /*for plus*/
        bool checkDiagonal() const;      /*for diag*/
    };
}

#endif