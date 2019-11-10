#pragma once

#include<Windows.h>

void Gotoxy(int x, int y);		//콘솔 커서 위치 이동
void Removecurser();			//콘솔 커서(깜빡임) 표시x
void Removescrollbar();			//콘솔 스크롤바 제거
void ConsoleSize();				//콘솔 크기 조정
void SetConsole();				//Gotoxy제외한 나머지 3개 모음