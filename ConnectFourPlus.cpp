#include "ConnectFourPlus.h"

bool HW4::ConnectFourPlus::hasWon() const
{
    return checkHorizontal() || checkVertical();     /*win conditions*/
}

bool HW4::ConnectFourPlus::isGameOver() const
{
    return hasWon() || isBoardFull();
}
