// Chess.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include "Board.h"
#include <windows.h>

using namespace std;
int main()
{
	//prints greek characters
	DWORD written;
	WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE), TEXT("Σκάκι με δύο παίχτες\n"), 22, &written, 0);

	Board board; //define Board object
	string input;

	WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE), TEXT("Πατήστε ένα πλήκτρο για να ξεκινήσει το παιχνίδι\n"), 50, &written, 0);
	WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE), TEXT("Αν θελετε να συνεχίσετε το παιχνίδι σας από το αρχείο δώστε το γράμμα 'y' \n"), 75, &written, 0);
	cin >> input;

	if (input.compare("y") == 0) //if user typed 'y' , then read chess board from file
		board.r_file("./binary.dat");
	while (board.playGame());

	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
