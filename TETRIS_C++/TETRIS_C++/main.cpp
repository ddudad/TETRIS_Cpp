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
		/*for문이 없으면 누르고 1칸 움직일 동안 아무것도 못하지만(딜레이)
		6번으로 나눔으로써 6번의 입력기회(딜레이 사라짐)*/
		for(int i=0; i<6; i++){
			KeyboardController();
			if (FlagNeedNewBlock == 1) {
				NewBlockMaker();
			}
			PrintGameBoard();
			Sleep(50);
		}
		/*내 머리 수준
		if (CrashCheck(0, 1, 0) == TRUE) {
			BlockFix();
		}
		else{
			BlockMove(0, 1, 0);
		}*/
		//다른 사람들 수준
		AutoDrop();
	}


	return 0;
}