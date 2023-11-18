#include "UserManager.h"

UserManager::UserManager()
{
	line = "+-------------------------------------------------------+";
	menu[0] = "| �������������                                         |";
	menu[1] = "| ������������                                          |";
	menu[2] = "| ����������� � �������� ������������                   |";
	menu[3] = "| �����                                                 |";
	size = sizeof(menu) / sizeof(string);
	readFromFile();
	//shared_ptr<Admin> user1 = make_shared<Admin>
	//	("admin123", genHashPassword("admin123", "12345"), "12345", LoginState::Admin);
	//shared_ptr<User> user2 = make_shared<User>
	//	("user456", genHashPassword("user456", "67890"), "67890", LoginState::User);
	//admins.push_back(user1);
	//users.push_back(user2);
}

vector<shared_ptr<User>> UserManager::getUsers() const
{
	return users;
}

vector<shared_ptr<Admin>> UserManager::getAdmins() const
{
	return admins;
}

vector<shared_ptr<User>> UserManager::getUsersToVerify() const
{
	return usersToVerify;
}

void UserManager::showMenu()
{
	system("CLS");
	char ch;
	int activeMenu = 0;
	int x = 46, y = 14;
	while (true) {
		console.cursorVisible(false, 100);
		SetConsoleTextAttribute(console.getHStdOut(), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		console.goToXY(x, y);
		cout << line;
		console.goToXY(x, y + 1);
		cout << "|  ��������, � �������� ���� �� ������ ��������� ����:  |";
		console.goToXY(x, y + 2);
		cout << line;
		console.goToXY(x, y + 7);
		cout << line;
		console.lightingMenu(activeMenu, menu, 46, 17, size);
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
				autorisation(LoginState::Admin);
				break;
			case 1:
				autorisation(LoginState::User);
				break;
			case 2:
				/*registration();*/
				cout << "��� ����� ��� �� ������..." << endl;
				break;
			case 3:
				system("CLS");
				if (confirmAction("�����")) {
					exit(0);
				}
				break;
			}
			break;
		}
	}
}

void UserManager::autorisation(LoginState state)
{
	console.cursorVisible(true, 80);
	SetConsoleTextAttribute(console.getHStdOut(), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	system("CLS");
	string password, login;
	int x = 56, y = 10, length = 31;
	console.goToXY(x, y);
	cout << "################################";
	console.goToXY(x, y + 1);
	cout << "#                              #";
	console.goToXY(x, y + 2);
	if (state == LoginState::Admin) {
		cout << "#  ����������� ��������������  #";
	}
	if (state == LoginState::User) {
		cout << "#   ����������� ������������   #";
	}
	console.goToXY(x, y + 3);
	cout << "#                              #";
	console.goToXY(x, y + 4);
	cout << "################################";

	x = 58, y = 17;
	console.goToXY(x, y);
	console.goToXY(x, y + 1);
	cout << "| �����:   | ";
	console.goToXY(x + 13, y + 1);

	cin >> login;

	console.goToXY(x, y + 2);
	console.goToXY(x + 13, y + 1);
	console.goToXY(x, y + 2);
	console.printLine(length);
	console.goToXY(x, y + 3);
	cout << "| ������:  | ";
	password = "";
	char ch;
	while ((ch = _getch()) != ENTER) {
		if (ch == BACKSPACE) {
			if (password.length() > 0) {
				password.pop_back();
				cout << "\b \b";  // ������� ��������� ������ � �������� ������ ������ �� 1 �������
			}
		}
		else {
			password += ch;

			cout << "*";  // ���������� ��������� ������ ��� ���������
		}
	}
	checkLogPass(state, login, password);
}

shared_ptr<Admin> UserManager::isAuthenticationAdmin(const string& login, const string& password)
{
	for (const auto& admin : admins)
	{
		if (admin->getLogin() == login) {
			if (admin->getHashPassword() == genHashPassword(password, admin->getSalt())) {
				return admin;
			}
		}
	}
	return nullptr;
}

shared_ptr<User> UserManager::isAuthenticationUser(const string& login, const string& password)
{
	for (const auto& user : users) {
		if (user->getLogin() == login) {
			if (user->getHashPassword() == genHashPassword(password, user->getSalt())) {
				return user;
			}
		}
	}
	return nullptr;
}

void UserManager::checkLogPass(LoginState state, const string& login, const string& password)
{
	console.cursorVisible(false, 80);
	if (state == LoginState::Admin) {
		shared_ptr<Admin> admin = isAuthenticationAdmin(login, password);
		if (admin) {
			admin->showMenu();
			return;
		}
		else {
			errorAutorisation();
			return;
		}
	}
	if (state == LoginState::User) {
		shared_ptr<User> user = isAuthenticationUser(login, password);
		if (user) {
			user->showMenu();
			return;
		}
		else {
			errorAutorisation();
			return;
		}
	}
	system("pause > nul");
}

void UserManager::errorAutorisation()
{
	console.goToXY(51, 23);
	cout << "\033[1;31m������ �����������. �������� ����� ��� ������\033[0m";
	console.goToXY(54, 25);
	system("pause > nul");
	system("CLS");
	return;
}


string UserManager::genHashPassword(string password, string salt)
{
	hash<string> toHash;
	return to_string(toHash(password + salt));
}

void UserManager::readFromFile()
{
	ifstream file;
	try {
		file.open("users.txt");
		if (file.bad()) {
			throw runtime_error("������ � �������� �����.");
		}
		else {
			fillVector(file);
		}
		file.close();
	}
	catch (const runtime_error& e)
	{
		cerr << e.what() << endl;
		exit(0);
	}
}

void UserManager::fillVector(ifstream& file)
{
	string line;
	while (getline(file, line)) {
		if (line.empty()) {
			continue;
		}
		istringstream ss(line);
		string token;

		// ���������� ������������ ����� ("|") � �������� �����������
		vector<string> tokens;
		while (getline(ss, token, '|')) {
			tokens.push_back(token);
		}

		if (tokens.size() == 4) {
			string stateSte = tokens[0];
			LoginState state = stateToString(stateSte);
			string login = tokens[1];
			string hashPassword = tokens[2];
			string salt = tokens[3];
			if (state == LoginState::Admin) {
				shared_ptr<Admin> admin = make_shared<Admin>(login, hashPassword, salt, LoginState::Admin);
				admins.push_back(admin);
			}
			else if (state == LoginState::User) {
				shared_ptr<User> user = make_shared<User>(login, hashPassword, salt, LoginState::User);
				users.push_back(user);
			}
			else if (state == LoginState::UserToVerify) {
				shared_ptr<User> user = make_shared<User>(login, hashPassword, salt, LoginState::UserToVerify);
				usersToVerify.push_back(user);
			}
		}
		else {
			string str = "������ ��� ������ ������: " + line;
			throw runtime_error(str);
		}
	}
}

LoginState UserManager::stateToString(const string& stateStr)
{
	if (stateStr == "Admin") {
		return LoginState::Admin;
	}
	else if (stateStr == "User") {
		return LoginState::User;
	}
	else if (stateStr == "UserToVerify") {
		return LoginState::UserToVerify;
	}
	else {
		throw std::runtime_error("�������� ��������� �����������: " + stateStr);
	}
}

void UserManager::writeToFile(const string& filename)
{
	/*ofstream file;
	try {
		file.open(filename);
		if (file.bad()) {
			throw runtime_error("������ � �������� �����.");
		}
		else {
			if (state == LoginState::Admin) {
				for (auto& admin : admins) {
					file << admin;
				}
			}
			if (state == LoginState::User) {
				for (auto& user : users) {
					file << user;
				}
			}
			if (state == LoginState::UserToVerify) {
				for (auto& user : usersToVerify) {
					file << user;
				}
			}
		}
		file.close();*/
		/*}
		catch (const runtime_error& e)
		{
			cerr << e.what() << endl;
			exit(0);
		}*/
}
