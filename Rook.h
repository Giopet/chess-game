#pragma once
#include "Piece.h"

class Rook : public Piece
{
public:
	Rook(char color, char name) : Piece(color, name) {}

private:
	virtual bool move(Piece* boardMove[8][8], int srcX, int srcY, int destX, int destY);
};
