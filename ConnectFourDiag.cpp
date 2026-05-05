#include "ConnectFourDiag.h"

bool HW4::ConnectFourDiag::hasWon() const
{
    return checkDiagonal();         /*win conditions*/
}

bool HW4::ConnectFourDiag::isGameOver() const
{
    return hasWon() || isBoardFull();
}