#ifndef CELL_H
#define CELL_H
#include <iostream>
using namespace std;

namespace HW4
{
    class Cell      
    {
        public:
            char getState() const;                   /*out getters*/
            bool getPlayState() const;
            char getColumnPos() const;
            int getRowNum() const; 
            Cell& setboard(char column, int row, bool statecont);      /*set out cell values with this function*/
            friend bool operator==(const Cell& a, const Cell& b);              /*our friend functions*/
            friend ostream& operator<<(ostream& os, const Cell& cell);
            friend istream& operator>>(istream& is, Cell& cell);
            Cell& operator++();                     /*i think its unnecessary but homework says do it.*/
            Cell operator++(int);
            Cell& operator--();            /*same thing but reverse order*/
            Cell operator--(int);
        private:
            bool playState;              /*is it playable or not playable*/
            char state;                 /*whether its empty, player1 or player2*/
            int statePos;               /*just for ++ and -- operators (*->X->O->X->*) if we cant use this, we cant make X->* */
            char columnPos;            /*column number*/
            int rowNum;                 /*row number*/
    };
}

#endif