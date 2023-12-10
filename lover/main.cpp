#include "UserManager.h"

namespace MyNamespace {
	int m;
}

int main() {

	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "Russian");

	UserManager* manager = UserManager::getInstance();
	manager->readFromFile();
	manager->welcomeMessage();
	manager->showMenu();
	manager->writeToFile("users.txt");
	Inventory::getInstance()->writeInFile();
	MyNamespace::m = 1;
	return 0;
}