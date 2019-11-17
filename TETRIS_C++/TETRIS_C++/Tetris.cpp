#include"Tetris.h"

//SetGameBoard.cpp에 선언된 Board배열 
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
//열거형은 다른 파일에 있다고 알려주는 법을 모르겠음
enum { EMPTY=0, MOVEBLOCK, DEADLINE, SHADOWBLOCK, WALL, FIXBLOCK};
bool FlagNeedNewBlock = FALSE;

void NewBlockMaker()
{
	blockType = rand() % 7;
	blockX = 4;
	blockY = 0;
	blockLotation = 0;
	FlagNeedNewBlock = FALSE;
	
	//blockX, blockY는 배열값에서 기준이 될 값, 아래 x,y는 값을 기준으로 위치 이동해서 표시해주는 값
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
			//배열중 블록이면서 && 아래가(inputY에 1 들어가고 inputX에 0 들어감) 3이상(벽이나 고정블럭)인 경우
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