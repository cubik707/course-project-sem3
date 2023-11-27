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
		"|  Посмотреть список сотрудников  |",
		"|  Добавить товар                 |" ,
		"|  Изменить данные о товаре       |",
		"|  Удалить товар                  |",
		"|  Поиск по параметру             |",
		"|  Сортировка по параметру        |",
		"|  Фильтрация                     |",
		"|  Работа с учетными записями     |",
		"|  Вывести отчет                  |",
		"|  Выйти из аккаунта              |" };
	int size = sizeof(menu) / sizeof(string);
	bool IsActive = true;
	while (true) {
		int x = 60, y = 10;
		console.cursorVisible(false, 100);
		SetConsoleTextAttribute(console.getHStdOut(), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		console.goToXY(x, y);
		cout << line;
		console.goToXY(x, ++y);
		cout << "|       Меню администратора:      |";
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
				//cout << "Эта часть еще не готова..." << endl;
				//changeUserData();
				break;
			case 3:
				//cout << "Эта часть еще не готова..." << endl;
				//deleteUser();
				break;
			case 4:
				//cout << "Эта часть еще не готова..." << endl;
				//searchUser();
				break;
			case 5:
				//cout << "Эта часть еще не готова..." << endl;
				//sortUsers();
				break;
			case 6:
				//cout << "Эта часть еще не готова..." << endl;
				//userControlMenu();
				break;
			case 7:
				//cout << "Эта часть еще не готова..." << endl;
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
	SetConsoleTextAttribute(console.getHStdOut(), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	Validator<string> validString;
	Validator<double> validDouble;
	Validator<int> validInt;

	string name, brand, model, code;
    double price;
    int shopQuantity, warehouseQuantity, soldQuantity;

    cout << "Введите название продукта: ";
    name = validString.getValidStr();
    cout << "Введите бренд продукта: ";
    brand = validString.getValidStr();
    cout << "Введите модель продукта: ";
    model = validString.getValidStr();
    cout << "Введите цену продукта: ";
    price = validDouble.getVar(0, INT_MAX);
    cout << "Введите количество продукта в магазине: ";
    shopQuantity = validInt.getVar(0, INT_MAX);
    cout << "Введите количество продукта на складе: ";
    warehouseQuantity = validInt.getVar(0, INT_MAX);
    cout << "Введите количество проданных продуктов: ";
    soldQuantity = validInt.getVar(0, INT_MAX);
    cout << "Введите код продукта: ";
    code = validString.getValidStr();
	while (code.length() != 3) {
		cout << "Код должен содержать 3 символа!" << endl;
		code = validString.getValidStr();
	}
	

    shared_ptr<Product> product = make_shared<Product>(name, price, soldQuantity, warehouseQuantity, shopQuantity, code, brand, model);
    Inventory* inventory = Inventory::getInstance();
    inventory->addProduct(product);
    cout << "Продукт успешно добавлен." << endl;
	system("CLS");
}

// write showAllUsers() function
