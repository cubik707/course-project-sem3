#include "UserManager.h"

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
	return 0;
}