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
	cout << "#   ÄÎÁÐÎ ÏÎÆÀËÎÂÀÒÜ!   #";
	console.goToXY(x, y + 3);
	cout << "#                       #";
	console.goToXY(x, y + 4);
	cout << "#########################";

	console.goToXY(x - 7, y + 7);
	SetConsoleTextAttribute(console.getHStdOut(), FOREGROUND_INTENSITY);
	system("pause");
}

bool Manager::confirmAction(const string& str)
{
	/*system("CLS");
	int choice, x = 54, y = 16;
	ConsoleHelper console;
	console.cursorVisible(true, 80);
	SetConsoleTextAttribute(console.getHStdOut(), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	*/
	return true;
}
