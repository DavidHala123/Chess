#include "Knight.h"
#include <array>
Knight::Knight(int colorConstant)
{
	render[0] = { "   oOOOO  " };
	render[1] = { "  oooOOOO " };
	render[2] = { "  ooo  OO " };
	render[3] = { "   ooo    " },
	render[4] = { "  oooooo  " };
	colorC = colorConstant;
	if (colorConstant == 1)
		black = true;
	else
		black = false;
};

bool Knight::move(int X, int Y, int nX, int nY)
{
	if (abs(X - nX) == 1 && abs(Y - nY) == 2 || abs(X - nX) == 2 && abs(Y - nY) == 1)
		return true;
	else
		return false;
}

bool Knight::validMove(int X, int Y, int nX, int nY, std::array<std::array<Figure*, 8>, 8> gameBoard)
{
	if(move(X, Y, nX, nY))
	{
		if (gameBoard[nY][nX] != NULL && gameBoard[nY][nX]->black == black)
			return false;
		else
			return true;
	}
}