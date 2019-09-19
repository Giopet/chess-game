#include "pch.h"
#include "King.h"
#include "Board.h"

bool King::move(Piece* boardMove[8][8], int srcX, int srcY, int destX, int destY)
{
	int calcRow = destX - srcX;
	int calcDest = destY - srcY;

	Piece* src = boardMove[srcX][srcY];
	Piece* dest = boardMove[destX][destY];

	if (((calcRow >= -1) && (calcRow <= 1)) && ((calcDest >= -1) && (calcDest <= 1)))
	{
		if (src->getColor() == 'W') //if piece is white
		{
			delete boardMove[srcX][srcY];
			delete boardMove[destX][destY];
			boardMove[srcX][srcY] = new EmptyCell('N', 'E');
			boardMove[destX][destY] = new King('W', 'K');
			return true;
		}
		else if (src->getColor() == 'B')//if piece is black
		{
			delete boardMove[srcX][srcY];
			delete boardMove[destX][destY];
			boardMove[srcX][srcY] = new EmptyCell('N', 'E');
			boardMove[destX][destY] = new King('B', 'K');
			return true;
		}
		else return false;
	}
	else return false;

}
