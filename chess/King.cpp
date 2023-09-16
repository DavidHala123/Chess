#include "King.h"
King::King(int colorConstant)
{
	render[0] = { "          " };
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

bool King::move(int X, int Y, int nX, int nY)
{
	if (abs(nX - X) < 2 && abs(nY - Y) < 2)
		return true;
	else
		return false;
}