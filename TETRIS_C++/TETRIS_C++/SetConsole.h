#pragma once

#include<Windows.h>

void Gotoxy(int x, int y);		//�ܼ� Ŀ�� ��ġ �̵�
void Removecurser();			//�ܼ� Ŀ��(������) ǥ��x
void Removescrollbar();			//�ܼ� ��ũ�ѹ� ����
void ConsoleSize();				//�ܼ� ũ�� ����
void SetConsole();				//Gotoxy������ ������ 3�� ����