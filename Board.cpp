#include "pch.h"
#include "Board.h"
#include <windows.h>
vector<std::string> hist;
DWORD written;

//constructor - creating Pieces
Board::Board()
{
	boardMove[0][0] = new Rook('W', 'R');
	boardMove[1][0] = new Knight('W', 'H');
	boardMove[2][0] = new Bishop('W', 'B');
	boardMove[3][0] = new Queen('W', 'Q');
	boardMove[4][0] = new King('W', 'K');
	boardMove[5][0] = new Bishop('W', 'B');
	boardMove[6][0] = new Knight('W', 'H');
	boardMove[7][0] = new Rook('W', 'R');

	boardMove[0][7] = new Rook('B', 'R');
	boardMove[1][7] = new Knight('B', 'H');
	boardMove[2][7] = new Bishop('B', 'B');
	boardMove[3][7] = new Queen('B', 'Q');
	boardMove[4][7] = new King('B', 'K');
	boardMove[5][7] = new Bishop('B', 'B');
	boardMove[6][7] = new Knight('B', 'H');
	boardMove[7][7] = new Rook('B', 'R');

	for (int i = 0; i < 8; i++)
	{
		boardMove[i][1] = new Pawn('W', 'P');
		boardMove[i][6] = new Pawn('B', 'P');

	}
	for (int i = 2; i < 6; i++)
	{
		for (int j = 0; j < 8; j++)
			boardMove[j][i] = new EmptyCell('N', 'E');

	}
}

//destructor - destroying Pieces
Board::~Board()
{
	for (int i = 0; i < 8; ++i)
	{
		for (int j = 0; j < 8; ++j)
		{
			delete boardMove[i][j];

		}
	}
}

//friend function - displays the history of moves are saved in the vector
void showVector(vector <string> g)
{

	vector <char> ::iterator it;
	vector<std::string>::iterator iter = g.begin();
	while (iter != g.end())
	{
		std::cout << *iter << endl;
		++iter;
	}

}

//print chess board
void Board::printBoard() {
	using namespace std;
	cout << "      1  2  3  4  5  6  7  8 " << endl << "  " << endl;
	for (int i = 0; i < 8; i++)
	{
		cout << " " << (char)(i + 97) << "   ";
		for (int j = 0; j < 8; j++)
		{
			char p = boardMove[i][j]->getPiece();
			char c = boardMove[i][j]->getColor();

			switch (p)
			{
			case 'K': (c == 'W') ? cout << " k " : cout << " K "; 
				break;
			case 'Q': (c == 'W') ? cout << " q " : cout << " Q ";
				break;
			case 'B':(c == 'W') ? cout << " b " : cout << " B ";
				break;
			case 'H':(c == 'W') ? cout << " h " : cout << " H ";
				break;
			case 'R': (c == 'W') ? cout << " r " : cout << " R ";
				break;
			case 'P': (c == 'W') ? cout << " p " : cout << " P ";
				break;
			case 'E': cout << " " << (char)254u << " ";
				break;
			default: cout << "<>";
				break;
			}

		}
		cout << endl;
	}
	cout << endl;
	WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE), TEXT("Iστορικό κινήσεων:\n"), 21, &written, 0);
	if (!hist.empty())
		showVector(hist);
	cout << endl;
}

//responsible method for taking player's input and uses it
bool Board::doMove() {
	using namespace std;
	string move = "    ";
	string undo = "    ";
	int x1, x2, y1, y2;
	bool stop = false;
	char p;
	char c;

	while (!stop) 
	{
		if (player == 'W')
		{
			WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE), TEXT("Η σειρά του Λευκού: \n"), 21, &written, 0);
			w_file("./binary.dat"); // write in file when it is white's turn
		}
		else
		{
			WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE), TEXT("Η σειρά του Μαύρου: \n"), 21, &written, 0);
		}
		WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE), TEXT("Δώσε τις συντεταγμένες της κίνησης (π.χ. a2a3).\n Για τερματισμό πληκτρολόγησε 'exit'. \n"), 88, &written, 0);
		cin >> move; 

		//if user give exit then game is over.
		if (move.compare("exit") == 0) 
			exit(0);

		//convert the characters into numbers so we can find the positions inside boardMove
		x1 = move[0] - 97; //from character to number
		y1 = move[1] - 49; //e.g. convert 1 into 0
		x2 = move[2] - 97;
		y2 = move[3] - 49;

		p = boardMove[x2][y2]->getPiece();
		c = boardMove[x1][y1]->getColor();

		if (boardMove[x1][y1]->getColor() == player) //if the color of piece is the same with player's turn
		{
			if (makeMove(x1, y1, x2, y2) == false) 
			{

				WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE), TEXT("Μη έγκυρη κίνηση, προσπάθησε ξανά\n"), 36, &written, 0);
			}
			else //if move done with success
				hist.insert(hist.begin(), move); //insert move into history vector
			stop = true;
		}
		else
			WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE), TEXT("Αυτό δεν είναι το πιόνι σου, προσπάθησε ξανά\n"), 46, &written, 0);
	}

	if (p == 'K') { //piece is king
		if (c == 'W') 
		{
			WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE), TEXT("Ο ΛΕΥΚΟΣ ΚΕΡΔΙΣΕ!\n"), 19, &written, 0);
			return false;
		}
		else if (c == 'B')
		{
			WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE), TEXT("Ο ΜΑΥΡΟΣ ΚΕΡΔΙΣΕ!\n"), 19, &written, 0);
			return false;
		}
	}

	//change player
	if (player == 'B') {

		player = 'W';
	}
	else
		player = 'B';

	return true;

}


//set chess board after reading from a file
void Board::setBoard(int x, int y, char p)
{
	delete boardMove[x][y];
	switch (p)
	{
	case 'K': boardMove[x][y] = new King('B', 'K');
		break;
	case 'Q': boardMove[x][y] = new Queen('B', 'Q');
		break;
	case 'B': boardMove[x][y] = new Bishop('B', 'B');
		break;
	case 'H': boardMove[x][y] = new Knight('B', 'H');
		break;
	case 'R': boardMove[x][y] = new Rook('B', 'R');
		break;
	case 'P': boardMove[x][y] = new Pawn('B', 'P');
		break;
	case 'k': boardMove[x][y] = new King('W', 'K');
		break;
	case 'q': boardMove[x][y] = new Queen('W', 'Q');
		break;
	case 'b': boardMove[x][y] = new Bishop('W', 'B');
		break;
	case 'h': boardMove[x][y] = new Knight('W', 'H');
		break;
	case 'r': boardMove[x][y] = new Rook('W', 'R');
		break;
	case 'p': boardMove[x][y] = new Pawn('W', 'P');
		break;
	case 'E': boardMove[x][y] = new EmptyCell('N', 'E');
		break;
	default: cout << "sth went wrong";
		break;
	}

}

//method responsible for gameplay of chess
bool Board::playGame()
{
	system("cls"); //clean screen

	printBoard();
	return doMove();

}

//method responsible for the move
bool Board::makeMove(int x1, int y1, int x2, int y2) {
	//Checking for turns will be done previous to this
	using namespace std;
	if (x1 < 0 || x1>7 || y1 < 0 || y1>7 || x2 < 0 || x2>7 || y2 < 0 || y2>8)
	{
		WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE), TEXT("Η κίνησή σου είναι εκτός ορίων των συντεταγμένων\n"), 50, &written, 0);
		return false;
	}
	Piece* src = boardMove[x1][y1];
	Piece* dest = boardMove[x2][y2];

	//if in destinations there is a Piece with the same colour and the cell is not empty
	if (src->getColor() == dest->getColor() && src->getColor() != 'E' && dest->getColor() != 'N')
	{
		WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE), TEXT("Μη έγκυρη κίνηση. Στην θέση αυτή υπάρχει ήδη δικό σου πιόνι.\n"), 62, &written, 0);
		return false;
	}

	char p = src->getPiece();
	char c = src->getColor();
	char p_dest = dest->getPiece();
	char c_dest = dest->getColor();
	if (p == 'K' || p == 'Q' || p == 'B' || p == 'H' || p == 'R' || p == 'P')
	{
		bool ans = src->move(boardMove, x1, y1, x2, y2);
		return ans; //we call the same virtual function
	}

	else if (p == 'E')
	{
		WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE), TEXT("Δεν έχεις πιόνι σε αυτή τη θέση\n"), 20, &written, 0);
		return false;
	}
	else {

		WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE), TEXT("Βρέθηκε σφάλμα στο switch statement in makeMove() \n"), 20, &written, 0);
	}

	return false;
}

//write in file the chess board
void Board::w_file(string filename)
{
	char p; //piece name
	char c; //piece color
	bool m = false; //has moved 
	using namespace std;
	ofstream fs;	//The ofstream class provides a member function named write that allows for information to be written in binary form to the stream. 
	fs.open(filename, ios::out | ios::binary);
	if (!fs.is_open()) {
		WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE), TEXT("Παρουσιάστηκε πρόβλημα με το άνοιγμα του αρχείου"), 50, &written, 0);
		cout << filename << endl;
	}
	else {
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				c = boardMove[i][j]->getColor();
				p = pieceIdentity(i, j, c); //return the name of the piece for these coordinates
				m = hasMoved(i, j, c); //return true if piece has moved

				fs.write(reinterpret_cast<char*>(&i), sizeof(i));
				fs.write(reinterpret_cast<char*>(&j), sizeof(j));
				fs.write(reinterpret_cast<char*>(&p), sizeof(p));
				fs.write(reinterpret_cast<char*>(&m), sizeof(m));
			}
		}
	}
	fs.close();
}

//finds the identity of the piece
char Board::pieceIdentity(int i, int j, char c) {

	char p = boardMove[i][j]->getPiece();
	switch (p)
	{
	case 'K': (c == 'W') ? p = 'k' : p = 'K';
		break;
	case 'Q': (c == 'W') ? p = 'q' : p = 'Q';
		break;
	case 'B':(c == 'W') ? p = 'b' : p = 'B';
		break;
	case 'H':(c == 'W') ? p = 'h' : p = 'H';
		break;
	case 'R': (c == 'W') ? p = 'r' : p = 'R';
		break;
	case 'P': (c == 'W') ? p = 'p' : p = 'P';
		break;
	case 'E': p = 'E';
		break;
	default: p = 'E'; //empty cell
		break;
	}
	return p;
}

//finds if the piece has moved from the start position
bool Board::hasMoved(int i, int j, char c) {
	char p = boardMove[i][j]->getPiece();
	bool m = true; //has moved
	switch (p)
	{
	case 'K': if ((c == 'W' && i == 4 && j == 0) || (c == 'B' && i == 4 && j == 7))
		m = false;
		break;
	case 'Q': if ((c == 'W' && i == 3 && j == 0) || (c == 'B' && i == 3 && j == 7))
		m = false;
		break;
	case 'B':if ((c == 'W' && i == 2 && j == 0) || (c == 'W' && i == 5 && j == 0) || (c == 'B' && i == 2 && j == 7) || (c == 'B' && i == 5 && j == 7))
		m = false;
		break;
	case 'H':if ((c == 'W' && i == 1 && j == 0) || (c == 'W' && i == 6 && j == 0) || (c == 'B' && i == 1 && j == 7) || (c == 'B' && i == 6 && j == 7))
		m = false;
		break;
	case 'R': if ((c == 'W' && i == 0 && j == 0) || (c == 'W' && i == 7 && j == 0) || (c == 'B' && i == 0 && j == 7) || (c == 'B' && i == 7 && j == 7))
		m = false;
		break;
	case 'P': if ((c == 'W' && (i == 0 || i == 1 || i == 2 || i == 3 || i == 4 || i == 5 || i == 6 || i == 7) && j == 1) || (c == 'B' && (i == 0 || i == 1 || i == 2 || i == 3 || i == 4 || i == 5 || i == 6 || i == 7) && j == 6))
		m = false;
		break;
	case 'E': m = false;
	default: m = true;
		break;
	}
	return m;
}

//read from file
void Board::r_file(string strFile)
{
	int x, y;
	char p;
	bool m;
	ifstream binaryFile;
	int size = 0;

	binaryFile.open(strFile, ios::in | ios::binary);
	binaryFile.seekg(0, ios::end); // check where the file is ending
	size = (int)binaryFile.tellg();
	binaryFile.seekg(0, ios::beg); //put the pointer in the begining of the file 

	cout << "Table: ";
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (binaryFile.tellg() >= size)
			{
				break;
			}

			binaryFile.read((char*)(&x), sizeof(x));
			binaryFile.read((char*)(&y), sizeof(y));
			binaryFile.read((char*)(&p), sizeof(p)); //piece name
			binaryFile.read((char*)(&m), sizeof(m)); //is moved?
			//set board 
			setBoard(x, y, p);


			cout << x << y << p << m << " ";
		}
		if (binaryFile.tellg() >= size)
		{
			break;
		}
	}
	binaryFile.close();


}

