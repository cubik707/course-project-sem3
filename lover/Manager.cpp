#include "Manager.h"

Manager::Manager()
{

}


Manager::~Manager()
{
}


void Manager::welcomeMessage()
{
	ConsoleHelper console;
	int x = 56, y = 14;

	console.cursorVisible(false, 100);
	console.goToXY(x, y);
	cout << "#########################";
	console.goToXY(x, y + 1);
	cout << "#                       #";
	console.goToXY(x, y + 2);
	cout << "#   ����� ����������!   #";
	console.goToXY(x, y + 3);
	cout << "#                       #";
	console.goToXY(x, y + 4);
	cout << "#########################";

	console.goToXY(x - 7, y + 7);
	SetConsoleTextAttribute(console.getHStdOut(), FOREGROUND_INTENSITY);
	system("pause");
}
