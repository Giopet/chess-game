#include "pch.h"
#include "Knight.h"
#include "Board.h"

bool Knight::move(Piece* boardMove[8][8], int srcX, int srcY, int destX, int destY)
{

	Piece* src = boardMove[srcX][srcY];
	Piece* dest = boardMove[destX][destY];

	if ((abs(srcX - destX) == 2 && abs(srcY - destY) == 1) || (abs(srcX - destX) == 1 && abs(srcY - destY) == 2))
	{
		if (src->getColor() == 'W') //if piece is white
		{
			delete boardMove[srcX][srcY];
			delete boardMove[destX][destY];
			boardMove[srcX][srcY] = new EmptyCell('N', 'E');
			boardMove[destX][destY] = new Rook('W', 'H');
			return true;
		}
		else //if piece is black
		{
			delete boardMove[srcX][srcY];
			delete boardMove[destX][destY];
			boardMove[srcX][srcY] = new EmptyCell('N', 'E');
			boardMove[destX][destY] = new Rook('B', 'H');
			return true;
		}
	}
	else
	{
		return false;
	}
}
