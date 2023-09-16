#include "Queen.h"
#include<iostream>
Queen::Queen(int colorConstant)
{
	render[0] = { "    oo    " };
	render[1] = { "   WWWW   " };
	render[2] = { "    oo    " };
	render[3] = { "   oooo   " },
	render[4] = { "  oooooo  " };
	colorC = colorConstant;
	if (colorConstant == 1)
		black = true;
	else
		black = false;
};

bool Queen::move(int X, int Y, int nX, int nY)
{
	if (nX - X == 0 && abs(nY - Y) > 0 || abs(nX - X) > 0 && nY - Y == 0 || abs(nX - X) == abs(nY - Y)) 
		return true;
	else
		return false;
}

