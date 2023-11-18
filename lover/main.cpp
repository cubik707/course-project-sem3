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

	UserManager manager;
	//Admin user1("admin123", manager.genHashPassword("admin123", "12345"), "12345", LoginState::Admin);
	//User user2("user456", manager.genHashPassword("user456", "67890"), "67890", LoginState::User);
	//fstream file("users.txt");
	//file << user1.getState() << "|" << user1.getLogin() << "|" << user1.getHashPassword() << "|" << user1.getSalt() << endl;
	//file << user2.getState() << "|" << user2.getLogin() << "|" << user2.getHashPassword() << "|" << user2.getSalt() << endl;
	//cout << "Файл запонен" << endl;

	manager.welcomeMessage();
	manager.showMenu();

	return 0;
}