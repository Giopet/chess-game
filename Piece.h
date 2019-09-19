#pragma once
#include <iostream>

class Piece
{
private:
	char color;
	char name;
public:

	Piece(char color, char name) : color(color), name(name) {}

	char getPiece();
	char getColor();

	void setPiece(char name) { this->name = name; };
	void setColor(char color) { this->color = color; };

	virtual bool move(Piece* boardMove[8][8], int srcX, int srcY, int destX, int destY) = 0;

};