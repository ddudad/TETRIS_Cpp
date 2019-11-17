#include"Tetris.h"

extern int Board[24][12];											//SetGameBoard.cpp에 선언된 Board배열, extern = 다른 파일에 Board배열이 선언되어 있다.
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
enum { EMPTY=0, MOVEBLOCK, DEADLINE, SHADOWBLOCK, WALL, FIXBLOCK};	//열거형은 다른 파일에 있다고 알려주는 법을 모르겠음 여기서 또 선언함
bool FlagNeedNewBlock = FALSE;										//블록이 고정돼서 새로운 블럭이 필요한 경우를 알려주는 플래그
bool FlagCrash = FALSE;							//AutoDrop() 블록 충돌이 있는 경우를 알려주는 플래그(블록이 충돌해도 좌우 움직이는 경우를 체크하기 위해 사용하는 플래그)

void NewBlockMaker()
{
	blockType = rand() % 7;
	blockX = 4;				//현재 블록 위치 기준값
	blockY = 0;				//현재 블록 위치 기준값
	blockLotation = 0;		//현재 블록 회전값 
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

void BlockMove(int inputX, int inputY, int inputZ)
{
	int temp_rotation = blockLotation + inputZ;	//임시 회전값 = 현재회전값 + inputZ(추가 회전값)
	if (temp_rotation > 3) {					//회전값이 3을 넘어가면
		temp_rotation = 0;						//0으로 초기화
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
	blockX += inputX;				//현재 블록 위치 업데이트
	blockY += inputY;				//현재 블록 위치 업데이트
	blockLotation = temp_rotation;	//현재 블록 회전번호 업데이트
}

bool CrashCheck(int inputX, int inputY, int inputZ)
{
	int temp_rotation = blockLotation + inputZ;	//임시 회전값 = 현재회전값 + inputZ(추가 회전값)
	if (temp_rotation > 3) {					//회전값이 3을 넘어가면
		temp_rotation = 0;						//0으로 초기화
	}

	for (int y = 0; y < 4; y++) {
		for (int x = 0; x < 4; x++) {
			//배열중 블록이면서 && 아래가(inputY에 1 들어가고 inputX에 0 들어감) 3이상(벽이나 고정블럭)인 경우
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
				if(CrashCheck(-1,0,0) == FALSE)		//충돌이 없으면
					BlockMove(-1, 0, 0);			//움직임
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
				break;
			}
		}
	}
	return;
}

//내 머리론 못 만듬
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

		for (int x = 1; x < SIZE_X - 1; x++) {			//라인 체크
			if (Board[y][x] == FIXBLOCK)
				LineCheck++;
		}

		if (LineCheck == SIZE_X - 2) {
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
}