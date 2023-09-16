#include "Rook.h"
Rook::Rook(int colorConstant)
{
	render[0] = { "          " };
	render[1] = { "  o oo o  " };
	render[2] = { "  oooooo  " };
	render[3] = { "   oooo   " },
	render[4] = { "  oooooo  " };
	colorC = colorConstant;
	if (colorConstant == 1)
		black = true;
	else
		black = false;
};

bool Rook::move(int X, int Y, int nX, int nY)
{
	if (nX - X == 0 && abs(nY - Y) > 0 || abs(nX - X) > 0 && nY - Y == 0)
		return true;
	else
		return false;
}

