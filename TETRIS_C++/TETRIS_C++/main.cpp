#include<iostream>
#include"SetConsole.h"
#include"SetGameBoard.h"
#include"Tetris.h"

using namespace std;

extern bool FlagNeedNewBlock;

int main()
{
	srand(time(NULL));

	SetConsole();
	InitGameBoard();
	NewBlockMaker();
	PrintGameBoard();
	while (1) {
		if (FlagNeedNewBlock == 1) {
			NewBlockMaker();
		}
		PrintGameBoard();
		Sleep(50);
	}


	return 0;
}