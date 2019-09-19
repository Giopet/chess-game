#include "pch.h"
#include "Queen.h"
#include "board.h"

bool Queen::move(Piece* boardMove[8][8], int srcX, int srcY, int destX, int destY)
{

	Piece* src = boardMove[srcX][srcY];
	Piece* dest = boardMove[destX][destY];

	int yIncrement;
	int xIncrement;

	bool invalid = false;
	if (srcX != destX || srcY != destY)
	{

		if (srcX == destX)
		{
			yIncrement = (destY - srcY) / (abs(destY - srcY));
			for (int i = srcY + yIncrement; i != destY; i += yIncrement)
			{

				if (boardMove[destX][i]->getColor() != 'N')
					return false;

			}
		}
		else
			if (srcY == destY)
			{

				xIncrement = (destX - srcX) / (abs(destX - srcX));
				for (int i = srcX + xIncrement; i != destX; i += xIncrement)
				{
					if (boardMove[i][destY]->getColor() != 'N')
						return false;
				}
			}
			else
				if (abs(srcX - destX) == abs(srcY - destY))
				{
					xIncrement = (destX - srcX) / (abs(destX - srcX));
					yIncrement = (destY - srcY) / (abs(destY - srcY));

					for (int i = 1; i < abs(srcX - destX); i++)
					{
						std::cout << "It got here somehow";
						if (boardMove[srcX + xIncrement * i][srcY + yIncrement * i]->getColor() != 'N')
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
			boardMove[destX][destY] = new Rook('W', 'Q');
			return true;
		}
		else //if piece is black
		{
			delete boardMove[srcX][srcY];
			delete boardMove[destX][destY];
			boardMove[srcX][srcY] = new EmptyCell('N', 'E');
			boardMove[destX][destY] = new Rook('B', 'Q');
			return true;
		}
	}
	else
	{
		return false;
	}
}
