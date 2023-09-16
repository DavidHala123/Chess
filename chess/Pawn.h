#pragma once
#include "Figure.h"

class Pawn : public Figure
{
private:
	bool attacking = false;
public:
	Pawn(int colorConstant);
	bool move(int X, int Y, int nX, int nY);
	bool validMove(int X, int Y, int nX, int nY, std::array<std::array<Figure*, 8>, 8> gameBoard);
};

