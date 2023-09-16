#pragma once
#include<string>
#include<iostream>
#include <array>

class Figure
{
public:
	bool black;
	bool enPassant = false;
	int posX, posY, colorC;
	virtual bool move(int X, int Y, int nX, int nY)
	{
		return false;
	};
	virtual bool validMove(int X, int Y, int nX, int nY, std::array<std::array<Figure*, 8>, 8> gameBoard)
	{
		if(move(X, Y, nX, nY))
		{
			try
			{
				int currentX = X;
				int currentY = Y;
				int stepX = 0;
				int stepY = 0;
				int margin = 0;
				if (abs(X - nX) > abs(Y - nY))
					margin = abs(X - nX);
				else
					margin = abs(Y - nY);
				if(abs(nX - X) > 0)
					stepX = (nX - X) / abs(nX - X);
				if(abs(nY - Y) > 0)
					stepY = (nY - Y) / abs(nY - Y);
				for (int i = 0; i < margin - 1; i++)
				{
					if (i < abs(X - nX) && abs(X - nX) == abs(Y - nY))
					{
						currentX += stepX;
						currentY += stepY;
					}
					else 
					{
						if (i < abs(X - nX))
							currentX += stepX;
						else if (i < abs(Y - nY))
							currentY += stepY;
					}
					if (gameBoard.at(currentY).at(currentX) == NULL)
						continue;
					else
						return false;
				}
				if (gameBoard.at(nY).at(nX) != NULL && gameBoard.at(nY).at(nX)->black == black)
					return false;
				else
					return true;
			}
			catch(const std::out_of_range & e)
			{
				return false;
			}
		}
	}


	std::string render[5];
};

