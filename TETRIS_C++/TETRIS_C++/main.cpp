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
		/*for���� ������ ������ 1ĭ ������ ���� �ƹ��͵� ��������(������)
		6������ �������ν� 6���� �Է±�ȸ(������ �����)*/
		for(int i=0; i<6; i++){
			KeyboardController();
			if (FlagNeedNewBlock == 1) {
				NewBlockMaker();
			}
			PrintGameBoard();
			Sleep(50);
		}
		/*�� �Ӹ� ����
		if (CrashCheck(0, 1, 0) == TRUE) {
			BlockFix();
		}
		else{
			BlockMove(0, 1, 0);
		}*/
		//�ٸ� ����� ����
		AutoDrop();
	}


	return 0;
}