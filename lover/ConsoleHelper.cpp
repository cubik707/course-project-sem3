#include "ConsoleHelper.h"

ConsoleHelper::ConsoleHelper()
{
	hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
}

HANDLE ConsoleHelper::getHStdOut()
{
	return hStdOut;
}

void ConsoleHelper::cursorVisible(bool show, short size)
{
	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo(hStdOut, &cursorInfo);
	cursorInfo.bVisible = show; // Изменяем видимость курсора
	cursorInfo.dwSize = size; // Изменяем размер курсора
	SetConsoleCursorInfo(hStdOut, &cursorInfo);
}

void ConsoleHelper::goToXY(short x, short y)
{
	SetConsoleCursorPosition(hStdOut, { x, y });
}

void ConsoleHelper::lightingMenu(int activeMenu, string* menu, int x, int y, int size)
{
	goToXY(x, y);
	for (int i = 0; i < size; i++)
	{
		if (i == activeMenu) {
			SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		}
		else SetConsoleTextAttribute(hStdOut, FOREGROUND_INTENSITY);
		goToXY(x, y++);
		cout << menu[i] << endl;
	}
}

void ConsoleHelper::printLine(int length)
{
	cout << "+" << setfill('-') << setw(length) << "";
	cout << setfill(' ');
	cout << "+" << endl;
}

void ConsoleHelper::clearLine(int x, int y, int length)
{
	COORD coord;
	DWORD written;
	coord.X = x;
	coord.Y = y;
	FillConsoleOutputCharacter(hStdOut, ' ', length, coord, &written);
}
