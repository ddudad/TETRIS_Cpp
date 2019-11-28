#pragma once

#include<iostream>
#include<time.h>
#include<conio.h>
#include"Tetris.h"
#include"SetGameBoard.h"
#define LEFT 75
#define RIGHT 77
#define DOWN 80
#define UP 72
#define SPACE 32

using namespace std;

void NewBlockMaker();
void BlockMove(int inputX, int inputY, int inputZ);	//x,y�� �̵���, zȸ����
bool CrashCheck(int inputX, int inputY, int inputZ);	//x,y�� �̵���, z ȸ����
void BlockFix();
void KeyboardController();
void AutoDrop();
void LineCheckDestroy();
void SpeedManager();
void ScoreManager();
void ResetInformation();
void PrintInformation();
void GameOverCheck();
void PrintGameOver();