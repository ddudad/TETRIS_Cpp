#include<iostream>
#include"SetConsole.h"
#include"SetGameBoard.h"
#include"Tetris.h"

using namespace std;

extern bool FlagNeedNewBlock;
extern int gameSpeed;
extern bool FlagHarddrop;

int main()
{
	srand(time(NULL));

	SetConsole();
	InitGameBoard();
	ResetInformation();
	NewBlockMaker();
	PrintGameBoard();
	PrintInformation();
	while (1) {
		SpeedManager();
		/*for���� ������ ������ 1ĭ ������ ���� �ƹ��͵� ��������(������)
		6������ �������ν� 6���� �Է±�ȸ(������ �����)*/
		for(int i=0; i<5; i++){
			KeyboardController();
			if (FlagNeedNewBlock == 1) {
				NewBlockMaker();
			}
			PrintGameBoard();
			Sleep(gameSpeed);
			if (FlagHarddrop == TRUE) {
				FlagHarddrop = FALSE;
				break;
			}
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
		PrintInformation();
		GameOverCheck();
	}


	return 0;
}