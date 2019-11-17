#pragma once

#include<time.h>
#include"Tetris.h"
#include"SetGameBoard.h"

void NewBlockMaker();
void BlockMove(int inputX, int inputY);
bool CrashCheck(int inputX, int inputY);
void BlockFix();