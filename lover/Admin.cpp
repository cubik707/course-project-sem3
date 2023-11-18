#include "Admin.h"



Admin::Admin(const string& login, const string& hashPassword, const string& salt, LoginState state)
	: User(login, hashPassword, salt, state)
{
}

void Admin::showMenu()
{
	system("CLS");
	char ch;
	int activeMenu = 0;
	string line = "+---------------------------------+";
	string menu[] = {
		"|  ���������� ������ �����������  |",
		"|  �������� �����                 |" ,
		"|  �������� ������ � ������       |",
		"|  ������� �����                  |",
		"|  ����� �� ���������             |",
		"|  ���������� �� ���������        |",
		"|  ����������                     |",
		"|  ������ � �������� ��������     |",
		"|  ������� �����                  |",
		"|  ����� �� ��������              |" };
	int size = sizeof(menu) / sizeof(string);
	bool IsActive = true;
	while (true) {
		int x = 60, y = 10;
		console.cursorVisible(false, 100);
		SetConsoleTextAttribute(console.getHStdOut(), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		console.goToXY(x, y);
		cout << line;
		console.goToXY(x, ++y);
		cout << "|       ���� ��������������:      |";
		console.goToXY(x, ++y);
		cout << line;
		console.goToXY(x, y + 11);
		cout << line;
		console.lightingMenu(activeMenu, menu, x, ++y, size);
		ch = _getch();
		if (ch == -32) ch = _getch();
		switch (ch)
		{
		case ESCAPE:
			system("CLS");
			return;
		case UP:
			if (activeMenu > 0)
				activeMenu--;
			break;
		case DOWN:
			if (activeMenu < size - 1)
				activeMenu++;
			break;
		case ENTER:
			switch (activeMenu)
			{
			case 0:
				system("CLS");
				Inventory::getInstance()->printInventory();
				break;
			case 1:
				//cout << "��� ����� ��� �� ������..." << endl;
				//addNewUser();
				break;
			case 2:
				//cout << "��� ����� ��� �� ������..." << endl;
				//changeUserData();
				break;
			case 3:
				//cout << "��� ����� ��� �� ������..." << endl;
				//deleteUser();
				break;
			case 4:
				//cout << "��� ����� ��� �� ������..." << endl;
				//searchUser();
				break;
			case 5:
				//cout << "��� ����� ��� �� ������..." << endl;
				//sortUsers();
				break;
			case 6:
				//cout << "��� ����� ��� �� ������..." << endl;
				//userControlMenu();
				break;
			case 7:
				//cout << "��� ����� ��� �� ������..." << endl;
				//showReport();
				break;
			case 8:
				system("CLS");
				break;
			}
			break;
		}
	}
}

// write showAllUsers() function
