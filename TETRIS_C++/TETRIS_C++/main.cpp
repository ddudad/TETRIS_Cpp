#include<iostream>
#include<windows.h>
#include"SetConsole.h"
#include"SetGameBoard.h"

using namespace std;

int main()
{
	SetConsole();
	InitGameBoard();
	PrintGameBoard();
}