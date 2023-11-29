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
				addProduct();
				break;
			case 2:
				//cout << "��� ����� ��� �� ������..." << endl;
				//changeUserData();
				break;
			case 3:
				deleteProduct();
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

void Admin::addProduct()
{
	system("CLS");
	console.cursorVisible(true, 80);
	SetConsoleTextAttribute(console.getHStdOut(), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	Validator<string> validString;
	Validator<double> validDouble;
	Validator<int> validInt;

	string name, brand, model, code;
    double price;
    int shopQuantity, warehouseQuantity, soldQuantity;
	
    cout << "������� �������� ��������: ";
    name = validString.getValidStr();
	validString.convertRegister(name);

    cout << "������� ����� ��������: ";
    brand = validString.getValidStr();
	validString.convertRegister(brand);

    cout << "������� ������ ��������: ";
    model = validString.getValidStr();
	validString.convertRegister(model);

    cout << "������� ���� ��������: ";
    price = validDouble.getVar(0, INT_MAX);
    cout << "������� ���������� �������� � ��������: ";
    shopQuantity = validInt.getVar(0, INT_MAX);
    cout << "������� ���������� �������� �� ������: ";
    warehouseQuantity = validInt.getVar(0, INT_MAX);
    cout << "������� ���������� ��������� ���������: ";
    soldQuantity = validInt.getVar(0, INT_MAX);
	cin.ignore();
    cout << "������� ��� ��������: ";
    code = validString.getValidStr();
	while (code.length() != 3) {
		cout << "��� ������ ��������� 3 �������!" << endl;
		code = validString.getValidStr();
	}
	

    shared_ptr<Product> product = make_shared<Product>(name, price, soldQuantity, warehouseQuantity, shopQuantity, code, brand, model);
    Inventory* inventory = Inventory::getInstance();
    inventory->addProduct(product);
    cout << "������� ������� ��������." << endl;
	system("pause");
	system("CLS");
}

void Admin::deleteProduct()
{
	system("CLS");
	console.cursorVisible(true, 80);
	SetConsoleTextAttribute(console.getHStdOut(), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	Validator<string> validString;
	string code;
	cout << "������� ��� ��������: ";
	code = validString.getValidStr();
	while (code.length() != 3) {

		cout << "��� ������ ��������� 3 �������!" << endl;
		code = validString.getValidStr();
	}
	Inventory* inventory = Inventory::getInstance();
	shared_ptr<Product> product = inventory->searchByCode(code);
	if (product == nullptr) {
		cout << "������� �� ������" << endl;
		system("pause");
		system("CLS");
		return;
	}
	inventory->removeProduct(product);
	cout << "������� ������." << endl;
	system("pause");
	system("CLS");
}

