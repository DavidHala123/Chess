// chess.cpp : Tento soubor obsahuje funkci main. Provádění programu se tam zahajuje a ukončuje.
//
#include <windows.h> 
#include "drawBoard.h"
#include "Pawn.h"
#include "Bishop.h"
#include "Figure.h";
#include "Queen.h"
#include "King.h"
#include "Rook.h"
#include "Knight.h"
#include<string>
#include <iostream>
#include<optional>
#include<list>
#include<vector>
#include <array> 
int colorChangerB;
int colorChangerW;
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
std::string colorRoundtxt;
std::string fieldInput;
std::string newFieldInput;
bool black;
bool blackRound = false;
bool isCheck(bool playerInput);

//FIGURKY WHITE
King kw = King(-1);
Knight knw = Knight(-1);
Queen qw = Queen(-1);
Bishop bw = Bishop(-1);
Rook rw = Rook(-1);
Pawn pw = Pawn(-1);

//FIGURKY BLACK
King kb = King(1);
Knight knb = Knight(1);
Queen qb = Queen(1);
Bishop bb = Bishop(1);
Rook rb = Rook(1);
Pawn pb = Pawn(1);

Figure* pos1;
Figure* pos2;

std::array<std::array<Figure*, 8>, 8> gameBoard = 
						{ {{&rb, &knb, &bb, &qb, &kb, &bb, &knb, &rb},
						{&pb, &pb, &pb, &pb, &pb, &pb, &pb, &pb},
						{NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL},
						{NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL},
						{NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL},
						{NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL},
						{&pw, &pw, &pw, &pw, &pw, &pw, &pw, &pw},
						{&rw, &knw, &bw, &qw, &kw, &bw, &knw, &rw}}
};

bool gameOn= true;
int posKing[] = {4,7,4,0 }; // WHITE, BLACK X,Y,X,Y
bool checkRound[] = {false, false}; //WHITE, BLACK
char abcd[] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H' };
int posKingIndex = 0;
void checkIfEmpty(int i, int j)
{
	if (gameBoard[i / 5][j] == NULL)
	{
		if (black)
		{
			SetConsoleTextAttribute(hConsole, 7);
		}
		else
		{
			SetConsoleTextAttribute(hConsole, BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
		}
		std::cout << std::string(10, ' ');
	}
	else
	{
		std::string renderLine = gameBoard[i/5][j]->render[i%5];
		if (gameBoard[i / 5][j]->colorC == -1)
		{
			colorChangerB = 8;
			colorChangerW = 248;
		}
		else
		{
			colorChangerB = 1;
			colorChangerW = 241;
		}
		for(char letter : renderLine)
		{
			if(!black)
				SetConsoleTextAttribute(hConsole, colorChangerW);
			else
				SetConsoleTextAttribute(hConsole, colorChangerB);
			std::cout << letter;
		}
	}
	black = !black;
}

void drawBoard()
{
	SetConsoleTextAttribute(hConsole, 10);
	std::cout.width(87);
	std::cout << std::string(84, '=') << std::endl;
	black = false;
	for (int i = 0; i < sizeof(gameBoard) / sizeof(gameBoard[0]) * 5; i++)
	{
		SetConsoleTextAttribute(hConsole, 10);
		if(i % 5 == 2)
		{
			std::cout.width(2);
			std::cout << i / 5 << " ||";
		}
		else
		{
			std::cout.width(5);
			std::cout << "||";
		}
		if (i % 5 == 0 && i != 0)
		{
			black = !black;
		}
		for (int j = 0; j < sizeof(gameBoard[0]) / sizeof(gameBoard[0][0]); j++)
		{
			checkIfEmpty(i,j);
		}
		SetConsoleTextAttribute(hConsole, 10);
		std::cout << "||" << std::endl;
	}
	SetConsoleTextAttribute(hConsole, 10);
	std::cout.width(87);
	std::cout << std::string(84, '=') << std::endl;
	for(int i=0; i < sizeof(abcd); i++)
	{
		SetConsoleTextAttribute(hConsole, 10);
		std::cout.width(10);
		std::cout << abcd[i];

	}
}

bool isCheckMate(int attackY, int attackX)
{
	int initX = 0;
	int initY = 0;
	std::array<std::array<Figure*, 8>, 8> gameBoardCpy = gameBoard;
	Figure* king;
	if (checkRound[0])
	{
		posKingIndex = 0;
		initX = posKing[0];
		initY = posKing[1];
		king = gameBoard[initY][initX];
	}
	else if (checkRound[1])
	{
		posKingIndex = 2;
		initX = posKing[2];
		initY = posKing[3];
		king = gameBoard[initY][initX];
	}
	else
		return false;
	for (int i = -1; i <= 1; i++)
	{
		for (int j = -1; j <= 1; j++)
		{
			try
			{
				if (king->validMove(initX, initY, initX + j, initY + i, gameBoardCpy))
				{
					posKing[posKingIndex] += j;
					posKing[posKingIndex + 1] += i;
					gameBoardCpy.at(initY + i).at(initX + j) = king;
					gameBoardCpy.at(initY).at(initX) = NULL;
					if (!isCheck(false))
					{
						posKing[posKingIndex] = initX;
						posKing[posKingIndex + 1] = initY;
						gameBoardCpy.at(initY + i).at(initX + j) = NULL;
						gameBoardCpy.at(initY).at(initX) = king;
						return false;
					}
					posKing[posKingIndex] = initX;
					posKing[posKingIndex + 1] = initY;
					gameBoardCpy.at(initY + i).at(initX + j) = NULL;
					gameBoardCpy.at(initY).at(initX) = king;
				}
			}
			catch (const std::out_of_range & e)
			{
				continue;
			}
		}
	}
	for (int k = 0; k < 8; k++)
	{
		for (int l = 0; l < 8; l++)
		{
			if (gameBoard[k][l] != NULL)
			{
				if (gameBoard[attackY][attackX]->black != gameBoard[k][l]->black && gameBoard[k][l]->validMove(l, k, attackX, attackY, gameBoard))
				{
					return false;
				}

			}
		}
	}
	gameOn = false;
	return true;
}

bool isCheck(bool playerInput)
{
	for(int k=0;k<8;k++)
	{
		for(int l=0;l<8;l++)
		{
			if(gameBoard[k][l] != NULL)
			{
				if (gameBoard[k][l]->black && gameBoard[k][l]->validMove(l, k, posKing[0], posKing[1], gameBoard))
				{
					checkRound[0] = true;
					if(playerInput && isCheckMate(k, l))
					{
						gameOn = false;
					}
					return true;
				}
				if (!gameBoard[k][l]->black && gameBoard[k][l]->validMove(l, k, posKing[2], posKing[3], gameBoard))
				{
					checkRound[1] = true;
					if (playerInput)
					{
						gameOn = false;
					}
					return true;
				}
			}
		}
	}
	return false;
}


int findIndex(char pos)
{

	for(int i=0; i < sizeof(abcd)/sizeof(abcd[0]); i++)
	{
		if (pos == abcd[i])
			return i;
	}
}

int main()
{
	std::string field;
	std::string nField;
	while (gameOn)
	{
		system("cls");
		drawBoard();
		SetConsoleTextAttribute(hConsole, 7);
		if (blackRound)
			colorRoundtxt = "BLACK: ";
		else
			colorRoundtxt = "WHITE: ";
		if (checkRound[0] == true || checkRound[1] == true)
		{
			std::cout << "\nCHECK";

		}
		std::cout << "\n" << colorRoundtxt << "Select figure to move: ";
		std::cin >> field;
		std::cout << "\n" << colorRoundtxt << "Where you want to move to: ";
		std::cin >> nField;
		try
		{
			int X = findIndex(field[0]);
			int Y = stoi(field.erase(0, 1));
			int nX = findIndex(nField[0]);
			int nY = stoi(nField.erase(0, 1));
			if (gameBoard[Y][X] != NULL && gameBoard[Y][X]->black == blackRound)
			{
				if (gameBoard[Y][X]->validMove( X, Y, nX, nY, gameBoard))
				{
					if (gameBoard[Y][X]->enPassant)
					{
						gameBoard[Y][X]->enPassant = false;
						if (blackRound)
						{
							if (gameBoard[nY - 1][nX] == &pw)
								gameBoard[nY - 1][nX] = NULL;
							else
								continue;
						}
						else
						{
							if (gameBoard[nY + 1][nX] == &pb)
								gameBoard[nY + 1][nX] = NULL;
							else
								continue;
						}
					}
					pos1 = gameBoard[Y][X];
					pos2 = gameBoard[nY][nX];
					gameBoard[nY][nX] = gameBoard[Y][X];
					gameBoard[Y][X] = NULL;
					if (gameBoard[nY][nX] == &kw)
					{
						posKing[0] = nX;
						posKing[1] = nY;
						posKingIndex = 0;
					}
					if (gameBoard[nY][nX] == &kb)
					{
						posKing[2] = nX;
						posKing[3] = nY;
						posKingIndex = 2;
					}
					if (isCheck(true) && checkRound[int(blackRound)])
					{
						gameBoard[Y][X] = pos1;
						gameBoard[nY][nX] = pos2;
						posKing[posKingIndex] = X;
						posKing[posKingIndex + 1] = Y;
						continue;
					}
					else
					{
						checkRound[int(blackRound)] = false;
						blackRound = !blackRound;
					}
				}
			}
		}
		catch (...)
		{

		}

	}
	system("cls");
	drawBoard();
	SetConsoleTextAttribute(hConsole, 7);
	std::cout << "\nCHECKMATE! GAME OVER";
}
