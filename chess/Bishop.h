#pragma once
#include "Figure.h"

class Bishop : public Figure
{
public:
	Bishop(int colorConstant);
	bool move(int X, int Y, int nX, int nY);
};

