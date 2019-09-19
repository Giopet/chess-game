#pragma once
#include "Piece.h"
#include <stdio.h>
using namespace std;

class EmptyCell : public Piece
{
public:
	EmptyCell(char color, char name) : Piece(color, name) {}

private:
	virtual bool move(Piece* boardMove[8][8], int srcX, int srcY, int destX, int destY) {
		return false;
	};
};