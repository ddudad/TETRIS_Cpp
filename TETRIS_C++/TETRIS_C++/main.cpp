#include<iostream>
#include"SetConsole.h"
#include"SetGameBoard.h"
#include"Tetris.h"

using namespace std;

int main()
{
	srand(time(NULL));

	SetConsole();
	InitGameBoard();
	NewBlockMaker();
	PrintGameBoard();
}