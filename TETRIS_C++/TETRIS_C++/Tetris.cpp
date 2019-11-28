#include"Tetris.h"

extern int Board[24][12];											//SetGameBoard.cpp�� ����� Board�迭, extern = �ٸ� ���Ͽ� Board�迭�� ����Ǿ� �ִ�.
int blocks[7][4][4][4] = {
	{
		0,0,0,0,
		0,1,0,0,
		0,1,1,1,
		0,0,0,0,

		0,0,0,0,
		0,0,1,1,
		0,0,1,0,
		0,0,1,0,

		0,0,0,0,
		0,0,0,0,
		0,1,1,1,
		0,0,0,1,

		0,0,0,0,
		0,0,1,0,
		0,0,1,0,
		0,1,1,0
	},

	{
		0,0,0,0,
		0,0,0,1,
		0,1,1,1,
		0,0,0,0,

		0,0,0,0,
		0,0,1,0,
		0,0,1,0,
		0,0,1,1,

		0,0,0,0,
		0,0,0,0,
		0,1,1,1,
		0,1,0,0,

		0,0,0,0,
		0,1,1,0,
		0,0,1,0,
		0,0,1,0
	},

	{
		0,0,0,0,
		0,1,1,0,
		0,1,1,0,
		0,0,0,0,

		0,0,0,0,
		0,1,1,0,
		0,1,1,0,
		0,0,0,0,

		0,0,0,0,
		0,1,1,0,
		0,1,1,0,
		0,0,0,0,

		0,0,0,0,
		0,1,1,0,
		0,1,1,0,
		0,0,0,0
	},

	{
		0,0,0,0,
		0,0,1,0,
		0,1,1,1,
		0,0,0,0,

		0,0,0,0,
		0,0,1,0,
		0,0,1,1,
		0,0,1,0,

		0,0,0,0,
		0,0,0,0,
		0,1,1,1,
		0,0,1,0,

		0,0,0,0,
		0,0,1,0,
		0,1,1,0,
		0,0,1,0
	},
	{
		0,0,0,0,
		0,0,0,0,
		1,1,1,1,
		0,0,0,0,

		0,0,1,0,
		0,0,1,0,
		0,0,1,0,
		0,0,1,0,

		0,0,0,0,
		1,1,1,1,
		0,0,0,0,
		0,0,0,0,

		0,1,0,0,
		0,1,0,0,
		0,1,0,0,
		0,1,0,0
	},

	{
		0,0,0,0,
		0,1,1,0,
		0,0,1,1,
		0,0,0,0,

		0,0,0,1,
		0,0,1,1,
		0,0,1,0,
		0,0,0,0,

		0,1,1,0,
		0,0,1,1,
		0,0,0,0,
		0,0,0,0,

		0,0,1,0,
		0,1,1,0,
		0,1,0,0,
		0,0,0,0
	},

	{
		0,0,0,0,
		0,0,1,1,
		0,1,1,0,
		0,0,0,0,

		0,0,1,0,
		0,0,1,1,
		0,0,0,1,
		0,0,0,0,

		0,0,1,1,
		0,1,1,0,
		0,0,0,0,
		0,0,0,0,

		0,1,0,0,
		0,1,1,0,
		0,0,1,0,
		0,0,0,0
	}
};
int blockX = 0, blockY = 0, blockLotation = 0, blockType = 0;
enum { EMPTY=0, MOVEBLOCK, DEADLINE, SHADOWBLOCK, WALL, FIXBLOCK};	//�������� �ٸ� ���Ͽ� �ִٰ� �˷��ִ� ���� �𸣰��� ���⼭ �� ������
bool FlagNeedNewBlock = FALSE;										//����� �����ż� ���ο� ���� �ʿ��� ��츦 �˷��ִ� �÷���
bool FlagCrash = FALSE;							//AutoDrop() ��� �浹�� �ִ� ��츦 �˷��ִ� �÷���(����� �浹�ص� �¿� �����̴� ��츦 üũ�ϱ� ���� ����ϴ� �÷���)
bool FlagHarddrop = FALSE;
int level, countDeleteLine, comboDeleteLine, gameSpeed, bestScore, score;

void NewBlockMaker()
{
	blockType = rand() % 7;
	blockX = 4;				//���� ��� ��ġ ���ذ�
	blockY = 0;				//���� ��� ��ġ ���ذ�
	blockLotation = 0;		//���� ��� ȸ���� 
	FlagNeedNewBlock = FALSE;
	
	//blockX, blockY�� �迭������ ������ �� ��, �Ʒ� x,y�� ���� �������� ��ġ �̵��ؼ� ǥ�����ִ� ��
	for (int y = 0; y < 4; y++) {
		for (int x = 0; x < 4; x++) {
			if (blocks[blockType][blockLotation][y][x] == 1) {
				Board[blockY + y][blockX + x] = MOVEBLOCK;
			}
		}
	}
}

void BlockMove(int inputX, int inputY, int inputZ)
{
	int temp_rotation = blockLotation + inputZ;	//�ӽ� ȸ���� = ����ȸ���� + inputZ(�߰� ȸ����)
	if (temp_rotation > 3) {					//ȸ������ 3�� �Ѿ��
		temp_rotation = 0;						//0���� �ʱ�ȭ
	}

	for (int y = 0; y < 4; y++) {
		for (int x = 0; x < 4; x++) {
			if (blocks[blockType][blockLotation][y][x] == 1) {
				Board[blockY + y][blockX + x] = EMPTY;
			}
		}
	}

	for (int y = 0; y < 4; y++) {
		for (int x = 0; x < 4; x++) {
			if (blocks[blockType][temp_rotation][y][x] == 1) {
				Board[blockY + y + inputY][blockX + x + inputX] = MOVEBLOCK;
			}
		}
	}
	blockX += inputX;				//���� ��� ��ġ ������Ʈ
	blockY += inputY;				//���� ��� ��ġ ������Ʈ
	blockLotation = temp_rotation;	//���� ��� ȸ����ȣ ������Ʈ
}

bool CrashCheck(int inputX, int inputY, int inputZ)
{
	int temp_rotation = blockLotation + inputZ;	//�ӽ� ȸ���� = ����ȸ���� + inputZ(�߰� ȸ����)
	if (temp_rotation > 3) {					//ȸ������ 3�� �Ѿ��
		temp_rotation = 0;						//0���� �ʱ�ȭ
	}

	for (int y = 0; y < 4; y++) {
		for (int x = 0; x < 4; x++) {
			//�迭�� ����̸鼭 && �Ʒ���(inputY�� 1 ���� inputX�� 0 ��) 3�̻�(���̳� ������)�� ���
			if (blocks[blockType][temp_rotation][y][x] == 1 && Board[blockY + y + inputY][blockX + x + inputX] > 3) {
				return TRUE;
			}
		}
	}
	return FALSE;
}

void BlockFix()
{
	for (int y = 0; y < SIZE_Y; y++) {
		for (int x = 0; x < SIZE_X; x++) {
			if (Board[y][x] == MOVEBLOCK) {
				Board[y][x] = FIXBLOCK;
			}
		}
	}
	FlagNeedNewBlock = TRUE;
}

void KeyboardController()
{
	int key;

	if (_kbhit()) {
		key = _getch();
		if (key == 224) {
			key = _getch();

			switch (key) {
			case LEFT:
				if(CrashCheck(-1,0,0) == FALSE)		//�浹�� ������
					BlockMove(-1, 0, 0);			//������
				break;
			case RIGHT:
				if (CrashCheck(1, 0, 0) == FALSE)
					BlockMove(1, 0, 0);
				break;
			case DOWN:
				if (CrashCheck(0, 1, 0) == FALSE)
					BlockMove(0, 1, 0);
				break;
			case UP:
				if (CrashCheck(0, 0, 1) == FALSE)
					BlockMove(0, 0, 1);
				break;
			}
		}
		else {
			switch (key) {
			case SPACE:
				FlagHarddrop = TRUE;
				while (FlagCrash != TRUE) {
					AutoDrop();
				}
				break;
			}
		}
	}
	return;
}

//�� �Ӹ��� �� ����
void AutoDrop()
{
	if (CrashCheck(0, 1, 0) == FALSE && FlagCrash == FALSE) {
		BlockMove(0, 1, 0);
	}
	else if (CrashCheck(0, 1, 0) == TRUE && FlagCrash == FALSE) {
		FlagCrash = TRUE;
	}
	else if (CrashCheck(0, 1, 0) == FALSE && FlagCrash == TRUE) {
		FlagCrash = 0;
	}
	else if(CrashCheck(0, 1, 0) == TRUE && FlagCrash == TRUE) {
		BlockFix();
		LineCheckDestroy();
		FlagCrash = FALSE;
	}
}

void LineCheckDestroy()
{
	int LineCheck = 0;

	for (int y = SIZE_Y - 2; y > 2;) {
		LineCheck = 0;

		for (int x = 1; x < SIZE_X - 1; x++) {			//���� üũ
			if (Board[y][x] == FIXBLOCK)
				LineCheck++;
		}

		if (LineCheck == SIZE_X - 2) {
			countDeleteLine++;
			comboDeleteLine++;

			for (int k = y; k > 1; k--) {
				for (int l = 1; l < SIZE_X - 1; l++) {
					if (Board[k - 1][l] != DEADLINE) {
						Board[k][l] = Board[k - 1][l];
					}
					if (Board[k - 1][l] == DEADLINE) {
						Board[k][l] = EMPTY;
					}
				}
			}
		}
		else{
			y--;
		}
	}
	ScoreManager();
	comboDeleteLine = 0;
}

void SpeedManager()
{
	if (countDeleteLine < 10) {
		level = 1;
		gameSpeed = 75;
		return;
	}
	else if (countDeleteLine < 20) {
		level = 2;
		gameSpeed = 45;
		return;
	}
	else if (countDeleteLine < 30) {
		level = 3;
		gameSpeed = 35;
		return;
	}
	else if (countDeleteLine < 40) {
		level = 4;
		gameSpeed = 30;
		return;
	}
	else if (countDeleteLine < 50) {
		level = 5;
		gameSpeed = 25;
		return;
	}
	else if (countDeleteLine < 60) {
		level = 6;
		gameSpeed = 20;
		return;
	}
	else if (countDeleteLine < 70) {
		level = 7;
		gameSpeed = 15;
		return;
	}
	else {
		level = 8;
		gameSpeed = 10;
	}
}

void ScoreManager()
{
	score += 5;
	switch (comboDeleteLine) {
	case 1:
		score += 50;
		break;
	case 2:
		score += 150;
		break;
	case 3:
		score += 300;
		break;
	case 4:
		score += 500;
		break;
	default:
		break;
	}
}

void ResetInformation()
{
	level = 1;
	score = 0;
	countDeleteLine = 0;
	gameSpeed = 50;
}

void PrintInformation()
{
	Gotoxy(15, 10);
	cout << "BestScore: " << bestScore;

	Gotoxy(15, 12);
	cout << "Score: " << score;

	Gotoxy(15, 14);
	cout << "DeleteLine: " << countDeleteLine;

	Gotoxy(15, 16);
	cout << "Level: " << level;
}

void PrintGameOver()
{
	for (int y = 0; y < SIZE_Y - 1; y++) {
		for (int x = 1; x < SIZE_X - 1; x++) {
			Board[y][x] = EMPTY;
		}
	}
	PrintGameBoard();

	Gotoxy(4, 12);
	cout << "Game Over";

	Gotoxy(2, 14);
	cout << "Press Any Button";

	Sleep(500);

	while (_kbhit()) {
		_getch();
	}

	_getch();
}

void GameOverCheck()
{
	for (int x = 1; x < SIZE_X - 2; x++) {
		if (Board[1][x] == FIXBLOCK) {
			PrintGameOver();
			system("cls");

			ResetInformation();

			PrintGameBoard();
			PrintInformation();
		}
	}
}