#include "pch.h"
#include "Bishop.h"
#include "Board.h"

bool Bishop::move(Piece* boardMove[8][8], int srcX, int srcY, int destX, int destY)
{
	Piece* src = boardMove[srcX][srcY];
	Piece* dest = boardMove[destX][destY];
	bool invalid = false;

	if (abs(srcX - destX) == abs(srcY - destY))
	{
		int xIncrement = (destX - srcX) / (abs(destX - srcX));
		int yIncrement = (destY - srcY) / (abs(destY - srcY));

		for (int i = 1; i < abs(srcX - destX); i++)
		{
			if (boardMove[srcX + xIncrement * i][srcY + yIncrement * i]->getColor() != 'N')
				return false;

		}
	}
	else
		return false;

	/*if (invalid == false)
	{*/
		if (src->getColor() == 'W') //if piece is white
		{
			delete boardMove[srcX][srcY];
			delete boardMove[destX][destY];
			boardMove[srcX][srcY] = new EmptyCell('N', 'E');
			boardMove[destX][destY] = new Rook('W', 'B');
			return true;
		}
		else //if piece is black
		{
			delete boardMove[srcX][srcY];
			delete boardMove[destX][destY];
			boardMove[srcX][srcY] = new EmptyCell('N', 'E');
			boardMove[destX][destY] = new Rook('B', 'B');
			return true;
		}
	//}
	//else
	//{
	//	return false;
	//}
}