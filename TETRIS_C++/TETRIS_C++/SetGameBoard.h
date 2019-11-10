#pragma once

#include"SetConsole.h"
#include<iostream>
#define SIZE_X 12
#define SIZE_Y 24

int Board[SIZE_Y][SIZE_X];
enum { MOVEBLOCK = 0, SHADOWBLOCK, FIXBLOCK, WALL, DEADLINE, EMPTY };

void InitGameBoard();
void PrintGameBoard();