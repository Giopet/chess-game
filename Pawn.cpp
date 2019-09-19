#include "pch.h"
#include "Pawn.h"
#include "Board.h"

bool Pawn::move(Piece* boardMove[8][8], int srcX, int srcY, int destX, int destY)
{
	using namespace std;
	bool invalid = false;

	Piece* src = boardMove[srcX][srcY];
	Piece* dest = boardMove[destX][destY];

	if (src->getColor() == 'W')
	{
		if (srcX == destX && (destY == srcY + 1 || (destY == srcY + 2 && destX != 3)) && dest->getColor() == 'N')
		{
			//Ι use delete and new because they are different Pieces and do different moves
			//where the piece was in the source position , we put the empty cell
			delete boardMove[srcX][srcY];
			delete boardMove[destX][destY];
			boardMove[srcX][srcY] = new EmptyCell('N', 'E');
			boardMove[destX][destY] = new Pawn('W', 'P');
			return true;
		}
		else
			if ((srcX + 1 == destX || srcX - 1 == destX) && srcY + 1 == destY && dest->getColor() == 'B')
			{
				delete boardMove[srcX][srcY];
				delete boardMove[destX][destY];
				boardMove[srcX][srcY] = new EmptyCell('N', 'E');
				boardMove[destX][destY] = new Pawn('W', 'P');
				return true;
			}
			else
				return false;
	}
	else
		if (src->getColor() == 'B')
		{
			if (srcX == destX && (destY == srcY - 1 || (destY == srcY - 2 && destX != 4)) && dest->getColor() == 'N')
			{
				delete boardMove[srcX][srcY];
				delete boardMove[destX][destY];
				boardMove[srcX][srcY] = new EmptyCell('N', 'E');
				boardMove[destX][destY] = new Pawn('B', 'P');
				return true;
			}
			else
				if ((srcX + 1 == destX || srcX - 1 == destX) && srcY - 1 == destY && dest->getColor() == 'W')
				{
					delete boardMove[srcX][srcY];
					delete boardMove[destX][destY];
					boardMove[srcX][srcY] = new EmptyCell('N', 'E');
					boardMove[destX][destY] = new Pawn('B', 'P');

					return true;
				}
				else
					return false;
		}
		else
			return false;
}


