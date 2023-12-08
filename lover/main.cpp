#include "UserManager.h"


void myTerminate() {
	cerr << "Необработанное исключение! Программа завершена." << endl;
	exit(1);
}

int main() {

	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "Russian");

	set_terminate(myTerminate);
	Inventory::getInstance()->readFromFile();


	UserManager* manager = UserManager::getInstance();
	manager->welcomeMessage();
	manager->showMenu();

	return 0;
}