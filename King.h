#pragma once
#include "Piece.h"

class King : public Piece
{
public:
	King(char color, char name) : Piece(color, name) {}

private:
	virtual bool move(Piece* boardMove[8][8], int srcX, int srcY, int destX, int destY);
};

