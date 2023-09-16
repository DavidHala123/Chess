#include "Bishop.h"
#include<iostream>
Bishop::Bishop(int colorConstant)
{
	render[0] = { "    oo    " };
	render[1] = { "  oooooo  " };
	render[2] = { "   oooo   " };
	render[3] = { "    oo    " },
	render[4] = { "  oooooo  " };
	colorC = colorConstant;
	if (colorConstant == 1)
		black = true;
	else
		black = false;
};

bool Bishop::move(int X, int Y, int nX, int nY)
{
	if (abs(nX - X) == abs(nY - Y))
		return true;
	else
		return false;
}
