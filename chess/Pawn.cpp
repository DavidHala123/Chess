#include "Pawn.h"
#include<iostream>
Pawn::Pawn(int colorConstant)
{
	render[0] = { "          " };
	render[1] = { "    oo    " };
	render[2] = { "   oooo   " };
	render[3] = { "  oooooo  " },
	render[4] = { "          " };
	colorC = colorConstant;
	if (colorConstant == 1)
		black = true;
	else
		black = false;
};

bool Pawn::move(int X, int Y, int nX, int nY) //Checks if the move is amongs the valid moves by rules (saves CPU)
{
	if (abs(nX - X) == 1 && (nY - Y) == 1*colorC)
	{
		attacking = true;
		return true;
	}
	if (nX - X == 0 && nY - Y == 1*colorC)
		return true;
	else if (nX - X == 0 && nY - Y == 2*colorC)
	{
		if (Pawn::black && Y == 1 || !Pawn::black && Y == 6)
			return true;
		return false;
	}
	else
		return false;
}

bool Pawn::validMove(int X, int Y, int nX, int nY, std::array<std::array<Figure*, 8>, 8> gameBoard) //Checks if anything is in the way of the move
{
	if(move(X, Y, nX, nY))
	{
		int currentX = X;
		int currentY = Y;
		if (attacking)
		{
			attacking = false;
			if (gameBoard[nY][nX] != NULL && gameBoard[nY][nX]->black != gameBoard[Y][X]->black)
				return true;
			else if (gameBoard[nY - 1 * colorC][nX] != NULL && gameBoard[nY - 1 * colorC][nX]->black != gameBoard[Y][X]->black)
			{
				enPassant = true;
				return true;
			}
			else
				return false;
		}
		else
		{
			for (int i = 0; i < abs(Y - nY); i++)
			{
				currentY += 1 * colorC;
				if (gameBoard[currentY][currentX] == NULL)
					continue;
				else
					return false;
			}
			return true;
		}
	}
	return false;
}
