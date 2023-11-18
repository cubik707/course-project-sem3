#pragma once
#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <iomanip>
#include <string>

#define ESCAPE 27
#define UP 72
#define DOWN 80
#define ENTER 13
#define BACKSPACE 8


using namespace std;

class ConsoleHelper
{
private:
	HANDLE hStdOut;
public:
	ConsoleHelper();

	HANDLE getHStdOut(); //������� ��� ��������� ����������� ������������ ������ ������

	void cursorVisible(bool show, short size); //������� ��������� ��������� � ������� �������
	void goToXY(short x, short y); //������� ��� ����������� ������� � ����� � ������������ x, y
	void lightingMenu(int activeMenu, string* menu, int x, int y, int size); //������� ��� ��������� ������ ����
	void printLine(int length); // �������, ��������� �� ������� ����� �������� �����
	void clearLine(int x, int y, int length); //������� ��� �������� ����������� �� �������
};