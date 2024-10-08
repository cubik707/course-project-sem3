#include "User.h"

User::User()
	: login("-"), hashPassword("-"), salt("-"), state(LoginState::User)
{
}

User::User(const string& login, const string& hashPassword, const string& salt, LoginState state)
    : login(login), hashPassword(hashPassword), salt(salt), state(state)
{
}

void User::showMenu()
{
	system("CLS");
	char ch;
	int activeMenu = 0;
	string line = "+---------------------------------+";
	string menu[] = {
		"|  ���������� ������ �����������  |",
		"|  ����� �� ���������             |",
		"|  ���������� �� ���������        |",
		"|  ����������                     |",
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
		cout << "|       ���� ������������:      |";
		console.goToXY(x, ++y);
		cout << line;
		console.goToXY(x, y + 7);
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
				searchMenu();
				break;
			case 2:
				sortMenu();
				break;
			case 3:
				filterMenu();
				break;
			case 4:
				createReport();
				break;
			case 5:
				system("CLS");
				return;
			}
			break;
		}
	}
}

void User::searchMenu()
{
	system("CLS");
	char ch;
	int activeMenu = 0;
	string line = "+-------------------------------------+";
	string menu[] = {
		"|  �� �������� ��������               |",
		"|  �� ������ ��������                 |" ,
		"|  �� ������ ��������                 |",
		"|  �� ���� ��������                   |",
		"|  ��������� ��������������           |" };
	int size = sizeof(menu) / sizeof(string);
	bool IsActive = true;
	while (true) {
		int x = 60, y = 10;
		console.cursorVisible(false, 100);
		SetConsoleTextAttribute(console.getHStdOut(), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		console.goToXY(x, y);
		cout << line;
		console.goToXY(x, ++y);
		cout << "| �� ���� �� ������ ���������� �����? |";
		console.goToXY(x, ++y);
		cout << line;
		console.goToXY(x, y + 6);
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
			system("CLS");
			console.cursorVisible(true, 80);
			SetConsoleTextAttribute(console.getHStdOut(), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
			switch (activeMenu)
			{
			case 0:
				searchForName();
				break;
			case 1:
				searchForBrand();
				break;
			case 2:
				searchForModel();
				break;
			case 3:
				searchForCode();
				break;
			case 4:
				system("CLS");
				return;
			}

			system("pause");
			system("CLS");
		}

	}
}

void User::searchForName()
{
	cout << "������� �������� ��������:" << endl;
	string name = Validator<string>::getValidStr();
	Validator<string>::convertRegister(name);

	Inventory* inventory = Inventory::getInstance();
	vector<shared_ptr<Product>> matchingProducts = inventory->searchByName(name);

	if (matchingProducts.empty()) {
		cout << "������� � ������ \"" << name << "\" �� ������." << endl;
		return;
	}
	else {
		cout << "��������� �������� � ������ \"" << name << "\":" << endl;
		inventory->printTableFields();
		int i = 1;
		for (const auto& matchingProduct : matchingProducts) {
			cout << left << setw(5) << "| " + to_string(i++);
			matchingProduct->print();
			console.printLine(LINE_LENGTH);
		}
	}
}

void User::searchForBrand()
{
	cout << "������� ������������� ��������:" << endl;
	string brand = Validator<string>::getValidStr();
	Validator<string>::convertRegister(brand);

	Inventory* inventory = Inventory::getInstance();
	vector<shared_ptr<Product>> matchingProducts = inventory->searchByBrand(brand);

	if (matchingProducts.empty()) {
		cout << "������� � �������������� \"" << brand << "\" �� ������." << endl;
		return;
	}
	else {
		cout << "��������� �������� � �������������� \"" << brand << "\":" << endl;
		inventory->printTableFields();
		int i = 1;
		for (const auto& matchingProduct : matchingProducts) {
			cout << left << setw(5) << "| " + to_string(i++);
			matchingProduct->print();
			console.printLine(LINE_LENGTH);
		}
	}
}

void User::searchForModel()
{
	cout << "������� ������ ��������:" << endl;
	string model = Validator<string>::getValidStr();
	Validator<string>::convertRegister(model);

	Inventory* inventory = Inventory::getInstance();
	vector<shared_ptr<Product>> matchingProducts = inventory->searchByModel(model);

	if (matchingProducts.empty()) {
		cout << "������� � ������� \"" << model << "\" �� ������." << endl;
		return;
	}
	else {
		cout << "��������� �������� � ������� \"" << model << "\":" << endl;
		inventory->printTableFields();
		int i = 1;
		for (const auto& matchingProduct : matchingProducts) {
			cout << left << setw(5) << "| " + to_string(i++);
			matchingProduct->print();
			console.printLine(LINE_LENGTH);
		}
	}

}

void User::searchForCode()
{
	cout << "������� ������ ��������:" << endl;
	string code = Validator<string>::getValidStr();
	while (code.length() != 3) {
		cout << "��� ������ ��������� 3 �������!" << endl;
		code = Validator<string>::getValidStr();
	}
	Validator<string>::convertRegister(code);
	shared_ptr<Product> product = Inventory::getInstance()->searchByCode(code);
	if (product == nullptr) {
		cout << "������� � ����� \"" << code << "\" �� ������." << endl;
		return;
	}
}

void User::sortMenu()
{
	system("CLS");
	char ch;
	int activeMenu = 0;
	string line = "+---------------------------------------+";
	string menu[] = {
		"|  �� �������� �������� �� �����������  |",
		"|  �� �������� �������� �� ��������     |",
		"|  �� ���� �� �����������               |",
		"|  �� ���� �� ��������                  |",
		"|  �� ���� �������� �� �����������      |",
		"|  �� ���� �������� �� ��������         |",
		"|  ��������� �����                      |" };
	int size = sizeof(menu) / sizeof(string);
	bool IsActive = true;
	Inventory* inventory = Inventory::getInstance();
	while (true) {
		int x = 60, y = 10;
		console.cursorVisible(false, 100);
		SetConsoleTextAttribute(console.getHStdOut(), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		console.goToXY(x, y);
		cout << line;
		console.goToXY(x, ++y);
		cout << "|      �� ���� �������� ����������?     |";
		console.goToXY(x, ++y);
		cout << line;
		console.goToXY(x, y + 8);
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
			system("CLS");
			console.cursorVisible(true, 80);
			SetConsoleTextAttribute(console.getHStdOut(), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
			switch (activeMenu)
			{
			case 0:
				inventory->sortByName();
				inventory->printInventory();
				return;
			case 1:
				inventory->sortByNameDescending();
				inventory->printInventory();
				return;
			case 2:
				inventory->sortByPrice();
				inventory->printInventory();
				return;
			case 3:
				inventory->sortByPriceDescending();
				inventory->printInventory();
				return;
			case 4:
				inventory->sortByCode();
				inventory->printInventory();
				return;
			case 5:
				inventory->sortByCodeDescending();
				inventory->printInventory();
				return;
			case 6:
				system("CLS");
				return;
			}
		}
	}
}

void User::filterMenu()
{
	system("CLS");
	char ch;
	int activeMenu = 0;
	string line = 
		"+-----------------------------------+";
	string menu[] = {
		"|  �� ����                          |",
		"|  �� ���-�� � ��������             |",
		"|  �� ���-�� �� ������              |",
		"|  �� ���������� ���-��             |",
		"|  ��������� �����                  |" };
	int size = sizeof(menu) / sizeof(string);
	bool IsActive = true;
	Inventory* inventory = Inventory::getInstance();
	while (true) {
		int x = 60, y = 10;
		console.cursorVisible(false, 100);
		SetConsoleTextAttribute(console.getHStdOut(), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		console.goToXY(x, y);
		cout << line;
		console.goToXY(x, ++y);
		cout << 
		"|    �� ���� �������� ����������?   |";
		console.goToXY(x, ++y);
		cout << line;
		console.goToXY(x, y + 6);
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
			system("CLS");
			console.cursorVisible(true, 80);
			SetConsoleTextAttribute(console.getHStdOut(), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
			switch (activeMenu)
			{
			case 0:
				filterForPrice();
				break;
			case 1:
				filterForShopQ();
				break;
			case 2:
				filterForWarehouseQ();
				break;
			case 3:
				filterForSoldQ();
				break;
			case 4:
				system("CLS");
				return;
			}
			system("pause");
			system("CLS");
		}
	}
}

void User::filterForPrice()
{
	cout << "������� ����������� ����: ";
	double minPrice = Validator<double>::getVar(0, INT_MAX-1);
	cout << "������� ������������ ����: ";
	double maxPrice = Validator<double>::getVar(minPrice, INT_MAX);
	Inventory* inventory = Inventory::getInstance();
	vector<shared_ptr<Product>> matchingProducts = inventory->searchByPriceRange(minPrice, maxPrice);

	if (matchingProducts.empty()) {
		cout << "������� � ��������� ����� �� ������." << endl;
		return;
	}
	else {
		cout << "��������� �������� � ��������� �����:" << endl;
		inventory->printTableFields();
		int i = 1;
		for (const auto& matchingProduct : matchingProducts) {
			cout << left << setw(5) << "| " + to_string(i++);
			matchingProduct->print();
			console.printLine(LINE_LENGTH);
		}
	}
}

void User::filterForShopQ()
{
	cout << "������� ����������� ����������: ";
	int minQuantity = Validator<int>::getVar(0, INT_MAX - 1);
	cout << "������� ������������ ����������: ";
	int maxQuantity = Validator<int>::getVar(minQuantity, INT_MAX);
	Inventory* inventory = Inventory::getInstance();
	vector<shared_ptr<Product>> matchingProducts = inventory->searchByShopQuantity(minQuantity, maxQuantity);

	if (matchingProducts.empty()) {
		cout << "������� � ��������� ����������� � ��������� �� ������." << endl;
		return;
	}
	else {
		cout << "��������� �������� � ��������� ����������� � ��������:" << endl;
		inventory->printTableFields();
		int i = 1;
		for (const auto& matchingProduct : matchingProducts) {
			cout << left << setw(5) << "| " + to_string(i++);
			matchingProduct->print();
			console.printLine(LINE_LENGTH);
		}
	}
}

void User::filterForWarehouseQ()
{
	cout << "������� ����������� ���������� �� ������: ";
	int minQuantity = Validator<int>::getVar(0, INT_MAX - 1);
	cout << "������� ������������ ���������� �� ������: ";
	int maxQuantity = Validator<int>::getVar(minQuantity, INT_MAX);
	Inventory* inventory = Inventory::getInstance();
	vector<shared_ptr<Product>> matchingProducts = inventory->searchByWarehouseQuantity(minQuantity, maxQuantity);

	if (matchingProducts.empty()) {
		cout << "������� � ��������� ����������� �� ������ �� ������." << endl;
		return;
	}
	else {
		cout << "��������� �������� � ��������� ����������� �� ������:" << endl;
		inventory->printTableFields();
		int i = 1;
		for (const auto& matchingProduct : matchingProducts) {
			cout << left << setw(5) << "| " + to_string(i++);
			matchingProduct->print();
			console.printLine(LINE_LENGTH);
		}
	}
}

void User::filterForSoldQ()
{
	cout << "������� ����������� ��������� ����������: ";
	int minQuantity = Validator<int>::getVar(0, INT_MAX - 1);
	cout << "������� ������������ ��������� ����������: ";
	int maxQuantity = Validator<int>::getVar(minQuantity, INT_MAX);
	Inventory* inventory = Inventory::getInstance();
	vector<shared_ptr<Product>> matchingProducts = inventory->searchBySoldQuantity(minQuantity, maxQuantity);

	if (matchingProducts.empty()) {
		cout << "������� � ��������� ��������� ����������� �� ������." << endl;
		return;
	}
	else {
		cout << "��������� �������� � ��������� ��������� �����������:" << endl;
		inventory->printTableFields();
		int i = 1;
		for (const auto& matchingProduct : matchingProducts) {
			cout << left << setw(5) << "| " + to_string(i++);
			matchingProduct->print();
			console.printLine(LINE_LENGTH);
		}
	}
}

void User::createReport()
{
	system("CLS");
	SetConsoleTextAttribute(console.getHStdOut(), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	ofstream excelFile("InventoryReport.csv");

	if (!excelFile.is_open()) {
		cout << "������ �������� �����!" << endl;
		return;
	}

	excelFile << "������������,�����,������,����,���������� � ��������,���������� �� ������,�������,���" << endl;

	for (const auto& product : Inventory::getInstance()->getProducts()) {
		excelFile << product->getName() << ","
			<< product->getBrand() << ","
			<< product->getModel() << ","
			<< product->getPrice() << ","
			<< product->getShopQuantity() << ","
			<< product->getWarehouseQuantity() << ","
			<< product->getSoldQuantity() << ","
			<< product->getCode() << endl;
	}

	excelFile.close();
	cout << "������ ���� ������� ������������!" << endl;
	system("InventoryReport.csv");
	system("pause");
	system("CLS");
}

string User::genSalt()
{
    srand(time(NULL));
    return to_string(rand() % 1000000);
}

ostream& operator<<(ostream& os, const LoginState& state)
{
    switch (state) {
    case LoginState::Admin:
        os << "Admin";
        break;
    case LoginState::User:
        os << "User";
        break;
    case LoginState::UserToVerify:
        os << "UserToVerify";
        break;
    }
    return os;
}
