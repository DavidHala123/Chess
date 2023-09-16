#pragma once
#include "Figure.h"

class Rook : public Figure
{
public:
	Rook(int colorConstant);
	bool move(int X, int Y, int nX, int nY);
};

