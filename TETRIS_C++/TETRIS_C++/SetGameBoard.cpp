#include"SetGameBoard.h"

using namespace std;

int Board[SIZE_Y][SIZE_X];
enum { EMPTY = 0, MOVEBLOCK, DEADLINE, SHADOWBLOCK, WALL, FIXBLOCK };

void InitGameBoard()
{
	for (int y = 0; y < SIZE_Y; y++) {
		for (int x = 0; x < SIZE_X; x++) {
			if (x == (SIZE_X - 1) || x == 0 || y == (SIZE_Y - 1))
				Board[y][x] = WALL;
			else
				Board[y][x] = EMPTY;
		}
	}

	for (int y = 0; y < SIZE_Y; y++) {
		for (int x = 0; x < SIZE_X; x++) {
			if (y == 1 && x != 0 && x != (SIZE_X - 1))
				Board[y][x] = DEADLINE;
		}
	}
}

void PrintGameBoard()
{
	for (int y = 0; y < SIZE_Y; y++) {
		for (int x = 0; x < SIZE_X; x++) {
			if ( y == 1 && x != 0 && x != (SIZE_X - 1) && Board[y][x] == EMPTY) {
				Board[y][x] = DEADLINE;
			}
			switch (Board[y][x]) {
			case EMPTY:
				Gotoxy(x, y);
				cout << "  ";
				break;
			case WALL:
				Gotoxy(x, y);
				cout << "в╠";
				break;
			case DEADLINE:
				Gotoxy(x, y);
				cout << ". ";
				break;
			case SHADOWBLOCK:
				Gotoxy(x, y);
				cout << "@";
				break;
			case MOVEBLOCK:
				Gotoxy(x, y);
				cout << "бс";
				break;
			case FIXBLOCK:
				Gotoxy(x, y);
				cout << "бр";
				break;
			}
		}
	}
}