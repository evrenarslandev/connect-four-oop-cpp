#ifndef CONNECTFOURPLUS_H
#define CONNECTFOURPLUS_H
#include "ConnectFourAbstract.h"
#include <iostream>
#include <string>
using namespace std;

namespace HW4
{
    class ConnectFourPlus : public ConnectFourAbstract
    {
        public:
            ConnectFourPlus() : ConnectFourAbstract() {}
            ConnectFourPlus(int r, int c) : ConnectFourAbstract(r, c) {}
            ConnectFourPlus(string filename) : ConnectFourAbstract(filename) {}
            virtual bool hasWon() const override; 
            virtual bool isGameOver() const override;
    };
}


#endif