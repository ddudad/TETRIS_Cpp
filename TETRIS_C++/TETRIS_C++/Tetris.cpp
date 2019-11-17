#include"Tetris.h"

//SetGameBoard.cpp�� ����� Board�迭 
extern int Board[24][12];
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
//�������� �ٸ� ���Ͽ� �ִٰ� �˷��ִ� ���� �𸣰���
enum { EMPTY=0, MOVEBLOCK, DEADLINE, SHADOWBLOCK, WALL, FIXBLOCK};
bool FlagNeedNewBlock = FALSE;

void NewBlockMaker()
{
	blockType = rand() % 7;
	blockX = 4;
	blockY = 0;
	blockLotation = 0;
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

void BlockMove(int inputX, int inputY)
{
	for (int y = 0; y < 4; y++) {
		for (int x = 0; x < 4; x++) {
			if (blocks[blockType][blockLotation][y][x] == 1) {
				Board[blockY + y][blockX + x] = EMPTY;
			}
		}
	}

	for (int y = 0; y < 4; y++) {
		for (int x = 0; x < 4; x++) {
			if (blocks[blockType][blockLotation][y][x] == 1) {
				Board[blockY + y + inputY][blockX + x + inputX] = MOVEBLOCK;
			}
		}
	}
	blockX += inputX;
	blockY += inputY;
}

bool CrashCheck(int inputX, int inputY)
{
	for (int y = 0; y < 4; y++) {
		for (int x = 0; x < 4; x++) {
			//�迭�� ����̸鼭 && �Ʒ���(inputY�� 1 ���� inputX�� 0 ��) 3�̻�(���̳� ������)�� ���
			if (blocks[blockType][blockLotation][y][x] == 1 && Board[blockY + y + inputY][blockX + x + inputX] > 3) {
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
				Board[y][x] == FIXBLOCK;
			}
		}
	}
	FlagNeedNewBlock = TRUE;
}