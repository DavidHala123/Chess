#pragma once
#include "Figure.h"
#include <array>

class Knight : public Figure
{
public:
	Knight(int colorConstant);
	bool move(int X, int Y, int nX, int nY);
	bool validMove(int X, int Y, int nX, int nY, std::array<std::array<Figure*, 8>, 8> gameBoard);
};

