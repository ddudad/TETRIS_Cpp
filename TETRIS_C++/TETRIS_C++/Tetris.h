#pragma once

#include<time.h>
#include<conio.h>
#include"Tetris.h"
#include"SetGameBoard.h"
#define LEFT 75
#define RIGHT 77
#define DOWN 80
#define UP 72
#define SPACE 32

void NewBlockMaker();
void BlockMove(int inputX, int inputY, int inputZ);	//x,y축 이동값, z회전값
bool CrashCheck(int inputX, int inputY, int inputZ);	//x,y축 이동값, z 회전값
void BlockFix();
void KeyboardController();
void AutoDrop();
void LineCheckDestroy();