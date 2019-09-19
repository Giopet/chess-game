#pragma once

#include "Piece.h"

class Pawn : public Piece
{
public:
	Pawn(char color, char name) : Piece(color, name) {}
private:
	virtual bool move(Piece* boardMove[8][8], int srcX, int srcY, int destX, int destY);
};
