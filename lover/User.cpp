#include "User.h"

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
		"|  Посмотреть список сотрудников  |",
		"|  Поиск по параметру             |",
		"|  Сортировка по параметру        |",
		"|  Фильтрация                     |",
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
		cout << "|       Меню пользователя:      |";
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

				break;
			case 3:

				break;
			case 4:

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

void User::searchMenu()
{
	system("CLS");
	char ch;
	int activeMenu = 0;
	string line = "+---------------------------------+";
	string menu[] = {
		"|  По названию продукта           |",
		"|  По бренду продукта             |" ,
		"|  По модели продукта             |",
		"|  По коду продукта               |",
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
		cout << "| По чему вы хотите произвести поиск? |";
		console.goToXY(x, ++y);
		cout << line;
		console.goToXY(x, y + 6);
		cout << line;
		console.lightingMenu(activeMenu, menu, x, ++y, size);
		ch = _getch();
		string name, brand, model;
		
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
	cout << "Введите название продукта:" << endl;
	string name = Validator<string>::getValidStr();
	Validator<string>::convertRegister(name);
	vector<shared_ptr<Product>> matchingProducts;
	Inventory* inventory = Inventory::getInstance();

	for (const auto& product : inventory->getProducts()) {
		string productLowercase = product->getName();
		Validator<string>::convertRegister(productLowercase);

		if (productLowercase == name) {
			matchingProducts.push_back(product);
		}
	}

	if (matchingProducts.empty()) {
		cout << "Продукт с именем \"" << name << "\" не найден." << endl;
		return;
	}
	else {
		cout << "Найденные продукты с именем \"" << name << "\":" << endl;
		for (const auto& matchingProduct : matchingProducts) {
			inventory->printProduct(matchingProduct);
		}
	}
}

void User::searchForBrand()
{
	cout << "Введите производителя продукта:" << endl;
	string brand = Validator<string>::getValidStr();
	Validator<string>::convertRegister(brand);
	shared_ptr<Product> product = Inventory::getInstance()->searchByBrand(brand);
	if (product == nullptr) {
		cout << "Продукт с производителем \"" << brand << "\" не найден." << endl;
		return;
	}
}

void User::searchForModel()
{
	cout << "Введите модель продукта:" << endl;
	string model = Validator<string>::getValidStr();
	Validator<string>::convertRegister(model);
	shared_ptr<Product> product = Inventory::getInstance()->searchByModel(model);
	if (product == nullptr) {
		cout << "Продукт с моделью \"" << model << "\" не найден." << endl;
		return;
	}

}

void User::searchForCode()
{
	cout << "Введите модель продукта:" << endl;
	string code = Validator<string>::getValidStr();
	while (code.length() != 3) {
		cout << "Код должен содержать 3 символа!" << endl;
		code = Validator<string>::getValidStr();
	}
	Validator<string>::convertRegister(code);
	shared_ptr<Product> product = Inventory::getInstance()->searchByCode(code);
	if (product == nullptr) {
		cout << "Продукт с кодом \"" << code << "\" не найден." << endl;
		return;
	}
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
