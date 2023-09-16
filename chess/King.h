#pragma once
#include "Figure.h"

class King : public Figure
{
public:
	King(int colorConstant);
	bool move(int X, int Y, int nX, int nY);
};

