#include "Cell.h"
using namespace std;

char HW4::Cell::getState() const         /* getters/setters */
{
    return state;
}

bool HW4::Cell::getPlayState() const
{
    return playState;
}

char HW4::Cell::getColumnPos() const
{
    return columnPos;
}

int HW4::Cell::getRowNum() const
{
    return rowNum;
}

HW4::Cell &HW4::Cell::setboard(char column, int row, bool statecont)
{
    playState = statecont;
    columnPos = column;
    rowNum = row;
    state = '.';
    statePos = 0;
    return *this;
}

HW4::Cell &HW4::Cell::operator++()
{
    if (statePos == 0)
    {
        state = 'X';
        statePos = 1;
    }
    else if (statePos == 1)
    {
        state = 'O';
        statePos = 2;
    }
    else if (statePos == 2)
    {
        state = 'X';
        statePos = 3;
    }
    else if (statePos == 3)
    {
        state = '.';
        statePos = 0;
    }
    return *this;
}

HW4::Cell HW4::Cell::operator++(int)
{
    Cell temp = *this;
    operator++();
    return temp;
}

HW4::Cell &HW4::Cell::operator--()
{
    if (statePos == 0)
    {
        state = 'X';
        statePos = 3;
    }
    else if (statePos == 1)
    {
        state = '.';
        statePos = 0;
    }
    else if (statePos == 2)
    {
        state = 'X';
        statePos = 1;
    }
    else if (statePos == 3)
    {
        state = 'O';
        statePos = 2;
    }
    return *this;
}

HW4::Cell HW4::Cell::operator--(int)
{
    Cell temp = *this;
    operator--();
    return temp;
}

namespace HW4
{
    bool operator==(const Cell &a, const Cell &b)
    {
        return a.state == b.state && a.columnPos == b.columnPos && a.rowNum == b.rowNum;
    }
    
    ostream &operator<<(ostream &os, const Cell &cell)
    {
        if (cell.playState)
        {
            os << cell.state;
        }
        else
        {
            os << " ";
        }
        return os;
    }
    istream &operator>>(istream &is, Cell &cell)
    {
        char input;
        if (is >> input)
        {
            if (input >= 'A' && input <= 'Z')
            {
                cell.columnPos = input;
            }
            else if (input >= 'a' && input <= 'z') /*border control*/
            {
                cell.columnPos = input - ('a' - 'A');
            }
            else
            {
                cout << "Wrong input type. Program terminated" << endl;
                exit(1);
            }
        }
        return is;
    }

}
