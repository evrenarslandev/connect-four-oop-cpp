#ifndef CONNECTFOURDIAG_H
#define CONNECTFOURDIAG_H
#include "ConnectFourAbstract.h"
#include <iostream>
#include <string>
using namespace std;

namespace HW4
{
    class ConnectFourDiag : public ConnectFourAbstract
    {
        public:
            ConnectFourDiag() : ConnectFourAbstract() {}
            ConnectFourDiag(int r, int c) : ConnectFourAbstract(r, c) {}
            ConnectFourDiag(string filename) : ConnectFourAbstract(filename) {}
            virtual bool hasWon() const override; 
            virtual bool isGameOver() const override;
    };
}


#endif