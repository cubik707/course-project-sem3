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
				editProduct();
				break;
			case 3:
				deleteProduct();
				break;
			case 4:
				searchMenu();
				break;
			case 5:
				sortMenu();
				break;
			case 6:
				filterMenu();
				break;
			case 7:
				
				break;
			case 9:
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
	
    cout << "Введите название продукта: ";
    name = validString.getValidStr();
	validString.convertRegister(name);

    cout << "Введите бренд продукта: ";
    brand = validString.getValidStr();
	validString.convertRegister(brand);

    cout << "Введите модель продукта: ";
    model = validString.getValidStr();
	validString.convertRegister(model);

    cout << "Введите цену продукта: ";
    price = validDouble.getVar(0, INT_MAX);
    cout << "Введите количество продукта в магазине: ";
    shopQuantity = validInt.getVar(0, INT_MAX);
    cout << "Введите количество продукта на складе: ";
    warehouseQuantity = validInt.getVar(0, INT_MAX);
    cout << "Введите количество проданных продуктов: ";
    soldQuantity = validInt.getVar(0, INT_MAX);
	cin.ignore();
    cout << "Введите код продукта: ";
    code = validString.getValidStr();
	while (code.length() != 3) {
		cout << "Код должен содержать 3 символа!" << endl;
		code = validString.getValidStr();
	}
	
	Inventory* inventory = Inventory::getInstance();
	if (inventory->searchByCode(code) != nullptr) {
		cout << "Продукт с кодом \"" << code << "\" уже существует. Невозможно добавить." << endl;
	}
	else {
		shared_ptr<Product> product = make_shared<Product>(name, price, soldQuantity, warehouseQuantity, shopQuantity, code, brand, model);
		inventory->addProduct(product);
		cout << "Продукт успешно добавлен." << endl;
	}
    
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
	cout << "Введите код продукта: ";
	code = validString.getValidStr();
	while (code.length() != 3) {

		cout << "Код должен содержать 3 символа!" << endl;
		code = validString.getValidStr();
	}
	Inventory* inventory = Inventory::getInstance();
	shared_ptr<Product> product = inventory->searchByCode(code);
	if (product == nullptr) {
		cout << "Продукт не найден" << endl;
		system("pause");
		system("CLS");
		return;
	}
	inventory->removeProduct(product);
	cout << "Продукт удален." << endl;
	system("pause");
	system("CLS");
}

void Admin::editProduct()
{
	system("CLS");
	console.cursorVisible(true, 80);
	SetConsoleTextAttribute(console.getHStdOut(), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	Validator<string> validString;
	string code;
	cout << "Введите код продукта для редактирования: ";
	code = validString.getValidStr();
	while (code.length() != 3) {
		cout << "Код должен содержать 3 символа!" << endl;
		code = validString.getValidStr();
	}

	Inventory* inventory = Inventory::getInstance();
	shared_ptr<Product> productToEdit = inventory->searchByCode(code);

	if (productToEdit == nullptr) {
		cout << "Продукт с кодом \"" << code << "\" не найден." << endl;
		system("pause");
		system("CLS");
		return;
	}
	editMenu(productToEdit);
}

void Admin::editMenu(shared_ptr<Product> productToEdit)
{
	system("CLS");
	char ch;
	int activeMenu = 0;
	string line = "+---------------------------------+";
	string menu[] = {
		"|  Название продукта              |",
		"|  Бренд продукта                 |" ,
		"|  Модель продукта                |",
		"|  Цену продукта                  |",
		"|  Количество продукта в магазине |",
		"|  Количество продукта на складе  |",
		"|  Количество проданных продуктов |",
		"|  Завершить редактирование       |" };
	int size = sizeof(menu) / sizeof(string);
	bool IsActive = true;
	while (true) {
		int x = 60, y = 10;
		console.cursorVisible(false, 100);
		SetConsoleTextAttribute(console.getHStdOut(), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		console.goToXY(x, y);
		cout << line;
		console.goToXY(x, ++y);
		cout << "|     Что вы хотите изменить?     |";
		console.goToXY(x, ++y);
		cout << line;
		console.goToXY(x, y + 9);
		cout << line;
		console.lightingMenu(activeMenu, menu, x, ++y, size);
		ch = _getch();
		string name, brand, model;
		double price;
		int shopQuantity, warehouseQuantity, soldQuantity;
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
				cout << "Введите новое название продукта: ";
				name = Validator<string>::getValidStr();
				Validator<string>::convertRegister(name);
				productToEdit->setName(name);
				break;
			case 1:
				cout << "Введите новый бренд продукта: ";
				brand = Validator<string>::getValidStr();
				Validator<string>::convertRegister(brand);
				productToEdit->setBrand(brand);
				break;
			case 2:
				cout << "Введите новую модель продукта: ";
				model = Validator<string>::getValidStr();
				Validator<string>::convertRegister(model);
				productToEdit->setModel(model);
				break;
			case 3:
				cout << "Введите новую цену продукта: ";
				price = Validator<double>::getVar(0, INT_MAX);
				productToEdit->setPrice(price);
				break;
			case 4:
				cout << "Введите новое количество продукта в магазине: ";
				shopQuantity = Validator<int>::getVar(0, INT_MAX);
				productToEdit->setShopQuantity(shopQuantity);
				break;
			case 5:
				cout << "Введите новое количество продукта на складе: ";
				warehouseQuantity = Validator<int>::getVar(0, INT_MAX);
				productToEdit->setWarehouseQuantity(warehouseQuantity);
				break;
			case 6:
				cout << "Введите новое количество проданных продуктов: ";
				soldQuantity = Validator<int>::getVar(0, INT_MAX);
				productToEdit->setSoldQuantity(soldQuantity);
				break;
			case 7:
				system("CLS");
				return;
			}
			cout << "Редактирование успешно произведено!" << endl;
			Inventory::getInstance()->printTableFields();
			cout << left << setw(5) << "| " + to_string(1);
			productToEdit->print();
			system("pause");
			system("CLS");
		}

	}
}


