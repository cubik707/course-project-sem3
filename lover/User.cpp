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
				sortMenu();
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
	string line = "+-------------------------------------+";
	string menu[] = {
		"|  По названию продукта               |",
		"|  По бренду продукта                 |" ,
		"|  По модели продукта                 |",
		"|  По коду продукта                   |",
		"|  Завершить редактирование           |" };
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

	Inventory* inventory = Inventory::getInstance();
	vector<shared_ptr<Product>> matchingProducts = inventory->searchByName(name);

	if (matchingProducts.empty()) {
		cout << "Продукт с именем \"" << name << "\" не найден." << endl;
		return;
	}
	else {
		cout << "Найденные продукты с именем \"" << name << "\":" << endl;
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
	cout << "Введите производителя продукта:" << endl;
	string brand = Validator<string>::getValidStr();
	Validator<string>::convertRegister(brand);

	Inventory* inventory = Inventory::getInstance();
	vector<shared_ptr<Product>> matchingProducts = inventory->searchByBrand(brand);

	if (matchingProducts.empty()) {
		cout << "Продукт с производителем \"" << brand << "\" не найден." << endl;
		return;
	}
	else {
		cout << "Найденные продукты с производителем \"" << brand << "\":" << endl;
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
	cout << "Введите модель продукта:" << endl;
	string model = Validator<string>::getValidStr();
	Validator<string>::convertRegister(model);

	Inventory* inventory = Inventory::getInstance();
	vector<shared_ptr<Product>> matchingProducts = inventory->searchByModel(model);

	if (matchingProducts.empty()) {
		cout << "Продукт с моделью \"" << model << "\" не найден." << endl;
		return;
	}
	else {
		cout << "Найденные продукты с моделью \"" << model << "\":" << endl;
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

void User::sortMenu()
{
	system("CLS");
	char ch;
	int activeMenu = 0;
	string line = "+-------------------------------------+";
	string menu[] = {
		"|  По названию продукта по возрастанию |",
		"|  По названию продукта по убыванию    |",
		"|  По цене по возрастанию              |",
		"|  По цене по убыванию                 |",
		"|  По коду продукта по возрастанию     |",
		"|  По коду продукта по убыванию        |",
		"|  Вернуться назад                     |" };
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
		cout << "|  По чему вы провести сортировку?  |";
		console.goToXY(x, ++y);
		cout << line;
		console.goToXY(x, y + 10);
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
