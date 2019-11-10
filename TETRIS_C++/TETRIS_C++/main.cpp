#include<iostream>
#include<windows.h>
#include"SetConsole.h"

#define SIZE_X 12
#define SIZE_Y 24
int Board[SIZE_Y][SIZE_X];

using namespace std;

enum { MOVEBLOCK = 0 , SHADOWBLOCK, FIXBLOCK, WALL, DEADLINE, EMPTY};

void InitGameBoard()
{
	for (int y = 0; y < SIZE_Y; y++) {
		for (int x = 0; x < SIZE_X; x++) {
			if (y == 0 || x == (SIZE_X - 1) || x == 0 || y == (SIZE_Y - 1))
				Board[y][x] = WALL;
			else
				Board[y][x] = EMPTY;
		}
	}
}

int main()
{
	InitGameBoard();

	

}