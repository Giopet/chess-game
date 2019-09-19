#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include "Pawn.h"
#include "Rook.h"
#include "Bishop.h"
#include "King.h"
#include "Knight.h"
#include "Queen.h"
#include "EmptyCell.h"
#include <vector>
#include <iterator> 

class Board
{
	char player = 'W'; // white plays first
	bool makeMove(int x1, int y1, int x2, int y2); //method responsible for the move
	void printBoard(); //prints chess board
	void w_file(string filename);
public:
	Board();
	~Board();

	char pieceIdentity(int i, int j, char c); //finds the identity of the piece
	bool hasMoved(int i, int j, char c); //finds if the piece has moved from the start position

	bool doMove(); //responsible method for taking player's input and uses it
	void setBoard(int x, int y, char p); //set chess board after reading from a file

	bool playGame();
	friend void showVector(vector <string> g); //displays the history of moves are saved in the vector

	void r_file(string filename);

	Piece* boardMove[8][8];
};

