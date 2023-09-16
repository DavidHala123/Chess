#pragma once
#include "Figure.h"

class Queen : public Figure
{
public:
	Queen(int colorConstant);
	bool move(int X, int Y, int nX, int nY);
};

