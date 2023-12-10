#include "UserManager.h"

UserManager* UserManager::instance = nullptr;

UserManager::UserManager()
{
}

UserManager* UserManager::getInstance()
{
	if (instance == nullptr) {
		instance = new UserManager();
	}
	return instance;
}

UserManager::~UserManager()
{
	delete instance;
	instance = nullptr;
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
	string line = "+-------------------------------------------------------+";
	string menu[] = {
		"| �������������                                         |",
		"| ������������                                          |",
		"| ����������� � �������� ������������                   |",
		"| �����                                                 |",
	};
	char ch;
	int activeMenu = 0, size = sizeof(menu) / sizeof(string), x = 46, y = 14;
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
				registration();
				break;
			case 3:
				system("CLS");
				return;
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
	writeToFile("users.txt");
	cin.ignore();
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
	system("pause");
}

void UserManager::errorAutorisation()
{
	console.goToXY(51, 23);
	cout << "\033[1;31m������ �����������. �������� ����� ��� ������\033[0m";
	console.goToXY(54, 25);
	system("pause");
	system("CLS");
	return;
}

void UserManager::registration()
{
	console.cursorVisible(true, 80);
	SetConsoleTextAttribute(console.getHStdOut(), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	system("CLS");
	int x = 0, y = 0;
	console.goToXY(x, y);
	cout << "################################";
	console.goToXY(x, y + 1);
	cout << "#                              #";
	console.goToXY(x, y + 2);
	cout << "#         �����������          #";
	console.goToXY(x, y + 3);
	cout << "#                              #";
	console.goToXY(x, y + 4);
	cout << "################################";
	console.goToXY(x, y + 6);
	cout << "������ �����: ";

	string login = Validator<string>::getValidStr();
	cout << "������� ������: ";
	string password = "";
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
	User tempUser;
	string salt =  tempUser.genSalt();
	shared_ptr<User> regUser = make_shared<User>(login, genHashPassword(password, salt), salt, LoginState::UserToVerify);
	usersToVerify.push_back(regUser);
	cout << endl << "�� ������� ������������������! �������� ������������� � �����������!" << endl;
	system("pause");
	system("CLS");
}


void UserManager::printAccount()
{
	SetConsoleTextAttribute(console.getHStdOut(), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	int length = 24;
	cout.setf(ios::left);
	console.printLine(length);

	cout << left << "|" << setw(23) << " ��������������" << " |" << endl;
	console.printLine(length);
	cout << left << setw(5) << "| �" <<
		setw(20) << "| �����" << "|" << endl;
	console.printLine(length);

	for (int i = 0; i < admins.size(); i++) {
		cout << setw(5) << "| " + to_string(i+1) << "| "
			<< setw(18) << admins[i]->getLogin() << "|" << endl;
		console.printLine(length);
	}

	cout << endl;
	console.printLine(length);
	cout << left << "|" << setw(23) << " ������������" << " |" << endl;
	console.printLine(length);
	cout << left << setw(5) << "| �" <<
		setw(20) << "| �����" << "|" << endl;
	console.printLine(length);
	for (int i = 0; i < users.size(); i++) {
		cout << setw(5) << "| " + to_string(i+1) << "| "
			<< setw(18) << users[i]->getLogin() << "|" << endl;
		console.printLine(length);
	}
	cout.unsetf(ios::left);
	system("pause");
	system("CLS");
}

void UserManager::addAccount()
{
	system("CLS");
	string login, password;
	cout << "��������, ���� �� ������ �������� (1- �����/0 - ������������)" << endl;
	int choice = Validator<int>::getVar(0, 1);
	cout << "������� �����: " << endl;
	cin.ignore();
	login = Validator<string>::getValidStr();
	cout << "������� ������: " << endl;
	password = Validator<string>::getValidStr();
	
	switch (choice)
	{
	case 0: {
		for (const auto& user : users)
		{
			if (user->getLogin() == login) {
				cout << "����� � ����� ������� ��� ����������!" << endl;
			}
		}
		User tempUser;
		string salt = tempUser.genSalt();
		shared_ptr<User> user = make_shared<User>(login, genHashPassword(password, salt),
			salt, LoginState::User);
		users.push_back(user);
	}
		break;
	case 1: {
		for (const auto& admin : admins)
		{
			if (admin->getLogin() == login) {
				cout << "����� � ����� ������� ��� ����������!" << endl;
			}
		}
		User tempUser;
		string salt = tempUser.genSalt();
		shared_ptr<Admin> admin = make_shared<Admin>(login, genHashPassword(password, salt),
			salt, LoginState::Admin);
		admins.push_back(admin);
	}
		break;
		cout << "������� ������ ������� ���������!" << endl;
	}
	system("pause");
	system("CLS");
}

void UserManager::deleteAccount(int choice, string login)
{
	switch (choice)
	{
	case 0: {
		auto it = find_if(users.begin(), users.end(), [login](const shared_ptr<User>& user) {
			return user->getLogin() == login;
			});

		if (it != users.end()) {
			users.erase(it);
		}
		else {
			cout << "����� ������� ������ �� �������!" << endl;
		}
		break;
	}
		break;
	case 1:
		auto it = find_if(admins.begin(), admins.end(), [login](const shared_ptr<Admin>& admin) {
			return admin->getLogin() == login;
			});

		if (it != admins.end()) {
			admins.erase(it);
		}
		else {
			cout << "����� ������� ������ �� �������!" << endl;
		}
	}
	cout << "������� ������ ������� �������!" << endl;
}

void UserManager::editAccount()
{
	system("CLS");
	string login, password;
	cout << "��������, ���� �� ������ ������������� (1- �����/0 - ������������)" << endl;
	int choice = Validator<int>::getVar(0, 1);
	cout << "������� �����: " << endl;
	cin.ignore();
	login = Validator<string>::getValidStr();
	cout << "������� ����� ������: " << endl;
	password = Validator<string>::getValidStr();
	switch (choice)
	{
	case 0: {
		bool isFound = false;
		for (const auto& user : users)
		{
			if (user->getLogin() == login) {
				user->setHashPassword(genHashPassword(password, user->genSalt()));
				isFound = true;
			}
		}
		if (!isFound) {
			cout << "����� ������� ������ �� �������!" << endl;
		}
	}
		  break;
	case 1: {
		bool isFound = false;
		for (const auto& admin : admins)
		{
			if (admin->getLogin() == login) {
				admin->setHashPassword(genHashPassword(password, admin->genSalt()));
				isFound = true;
			}
		}
		if (!isFound) {
			cout << "����� ������� ������ �� �������!" << endl;
		}
	}
		  break;
		  cout << "������� ������ ������� ��������!" << endl;
	}
	system("pause");
	system("CLS");
}

void UserManager::confirmAccount()
{
	system("CLS");
	if (usersToVerify.empty()) {
		cout << "��� ������� ������� ��� �������������." << endl;
		system("pause");
		system("CLS");
		return;
	}
	int choice;
	// ������� ������ �������������, ������� ����� �����������
	cout << "������ �������������, ��������� �������������:" << endl;
	for (auto& userToVerify : usersToVerify) {
		cout << "�����: " << userToVerify->getLogin() << endl;
		cout << "������ ������� ����� ������������? (1-��/0-���)" << endl;
		choice = Validator<int>::getVar(0, 1);
		if (choice) {
			users.push_back(userToVerify);
		}
	}
	// ������� ������ �������������, ��������� �������������
	usersToVerify.clear();
	system("pause");
	system("CLS");
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
	ofstream file;

	try {
		file.open(filename, ios::out | ios::trunc);
		if (file.bad()) {
			throw runtime_error("������ � �������� �����.");
		}
		else {
			for (const auto& admin : admins) {
				file << "Admin|" << admin->getLogin() << "|" << admin->getHashPassword() << "|" << admin->getSalt() << endl;
			}
			for (auto& user : users) {
				file << "User|" << user->getLogin() << "|" << user->getHashPassword() << "|" << user->getSalt() << endl;
			}
			for (auto& user : usersToVerify) {
				file << "UserToVerify|" << user->getLogin() << "|" << user->getHashPassword() << "|" << user->getSalt() << endl;
			}
		}
		file.close();
		}
		catch (const runtime_error& e)
		{
			cerr << e.what() << endl;
			exit(0);
		}
}
