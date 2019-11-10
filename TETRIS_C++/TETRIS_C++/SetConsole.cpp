#include"SetConsole.h"

void Gotoxy(int x, int y)	//콘솔 커서 위치 이동
{
	COORD pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void Removecurser()			//콘솔 커서(깜빡임) 표시x
{
	CONSOLE_CURSOR_INFO curinfo = { 0, };
	curinfo.dwSize = 1;
	curinfo.bVisible = 0;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curinfo);
}

void Removescrollbar()
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(handle, &info);
	COORD new_size =
	{
		info.srWindow.Right - info.srWindow.Left + 1,
		info.srWindow.Bottom - info.srWindow.Top + 1
	};
	SetConsoleScreenBufferSize(handle, new_size);
}

void ConsoleSize()
{
	system("mode con cols=79 lines=30");
}

void SetConsole()
{
	ConsoleSize();
	Removescrollbar();
	Removecurser();
}