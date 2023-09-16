#include "drawBoard.h"
#include<iostream>

drawBoard::drawBoard(std::string gameBoard[8][8])
{
	bool black = true;
	for (int i = 0; i < sizeof(gameBoard) / sizeof(gameBoard[0]) * 3; i++)
	{
		if (i % 3 == 0 && i != 0)
		{
			black = !black;
		}
		for (int j = 0; j < sizeof(gameBoard[0]) / sizeof(std::string); j++)
		{
			if (black)
			{
				std::cout << std::string(6, '*');
				black = !black;
			}
			else
			{
				std::cout << std::string(6, ' ');
				black = !black;
			}
		}
		std::cout << "\n";
	}
}

