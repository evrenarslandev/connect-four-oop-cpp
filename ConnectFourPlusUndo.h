#ifndef CONNECTFOURPLUSUNDO_H
#define CONNECTFOURPLUSUNDO_H

#include "ConnectFourAbstract.h"
#include <vector>

namespace HW4
{
    class ConnectFourPlusUndo : public ConnectFourAbstract
    {
    public:
        ConnectFourPlusUndo() : ConnectFourAbstract(), capacity(rows * columns) {}
        ConnectFourPlusUndo(int r, int c) : ConnectFourAbstract(r, c), capacity(rows * columns) {}
        ConnectFourPlusUndo(string filename) : ConnectFourAbstract(filename), capacity(rows * columns) {}

        virtual bool hasWon() const override;
        virtual bool isGameOver() const override;
        void playGame(int mode) override;

        void undo(int mode); /*our undo function*/

    private:
        vector<char> moves; /*for undo, we need to store our moves*/
        int capacity;       /*capacity = row*column*/
    };
}

#endif