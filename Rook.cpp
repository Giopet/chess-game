#include "pch.h"
#include "Rook.h"
#include "board.h"

bool Rook::move(Piece* boardMove[8][8], int srcX, int srcY, int destX, int destY)
{

	Piece* src = boardMove[srcX][srcY];
	Piece* dest = boardMove[destX][destY];

	bool invalid = false;
	if (srcX != destX || srcY != destY)
	{

		if (srcX == destX)
		{
			int yIncrement = (destY - srcY) / (abs(destY - srcY));
			for (int i = srcY + yIncrement; i != destY; i += yIncrement)
			{

				if (boardMove[destX][i]->getColor() != 'N')
					return false;

			}
		}
		else
			if (srcY == destY)
			{

				int xIncrement = (destX - srcX) / (abs(destX - srcX));
				for (int i = srcX + xIncrement; i != destX; i += xIncrement)
				{
					if (boardMove[i][destY]->getColor() != 'N')
						return false;
				}
			}
			else
				return false;
	}
	if (invalid == false)
	{
		if (src->getColor() == 'W') //if piece is white
		{
			delete boardMove[srcX][srcY];
			delete boardMove[destX][destY];
			boardMove[srcX][srcY] = new EmptyCell('N', 'E');
			boardMove[destX][destY] = new Rook('W', 'R');
			return true;
		}
		else //if piece is black
		{
			delete boardMove[srcX][srcY];
			delete boardMove[destX][destY];
			boardMove[srcX][srcY] = new EmptyCell('N', 'E');
			boardMove[destX][destY] = new Rook('B', 'R');
			return true;
		}
	}
	else
	{//Return some erorr or something. Probably return false;
		std::cout << "That is an invalid move for rook";
		return false;
	}
}