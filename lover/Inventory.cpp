#include "Inventory.h"


Inventory* Inventory::instance = nullptr;

Inventory* Inventory::getInstance()
{
	if (!instance) {
		instance = new Inventory();
	}
	return instance;
}

Inventory::~Inventory()
{
	if (instance) {
		delete instance;
		instance = nullptr;
	}
}

std::vector<shared_ptr<Product>> Inventory::getProducts()
{
	return products;
}

void Inventory::readFromFile()
{
	ifstream file;
	try
	{
		file.open("inventory.txt");

		if (file.bad()) {
			throw runtime_error("Ошибка в открытии файла.");
		}
		if (file.good()) {
			fillVectorFromFile(file);
		}

		file.close();
	}
	catch (const runtime_error& e)
	{
		cout << e.what() << endl;
		exit(0);
	}
}

void Inventory::fillVectorFromFile(ifstream& file)
{
	// Очищаем текущий контейнер перед чтением из файла
	products.clear();

	Product product;
	while (!file.eof()) {

		if (file >> product) {
			// Добавляем считанный продукт в вектор
			shared_ptr<Product> productPtr = make_shared<Product>(product);
			products.push_back(productPtr);
		}
		else {
			throw runtime_error("Ошибка при чтиении файла.");
		}
	}
}

void Inventory::writeInFile()
{
	fstream file;
	file.exceptions(fstream::failbit | fstream::badbit);

	try
	{
		file.open("inventor.txt", ios::out | ios::trunc); // Открываем файл для записи, существующий файл будет перезаписан

		if (file.bad()) {
			throw runtime_error("Ошибка в открытии файла для записи.");
		}

		for (const auto& product : products) {
			file << product; // Используем перегруженный оператор <<
		}

		file.close();
	}
	catch (const ios_base::failure& e)
	{
		// Обрабатываем ошибку, используя флаги статуса ошибок
		cerr << "Ошибка ввода-вывода: " << e.what() << endl;
		exit(0);
	}
	catch (const runtime_error& e)
	{
		cerr << e.what() << endl;
		exit(0);
	}
}

bool Inventory::hasProduct(const string& productName) // изменить посик по коду
{
	for (const auto& product : products) {
		if (product->getName() == productName) {
			return true;
		}
	}
	return false;
}


shared_ptr<Product> Inventory::searchByName(const string& productName)
{
	Validator<string> valid;
	string lowercaseName = productName;
	valid.convertRegister(lowercaseName);

	for (const auto& product : products) {
		string productLowercase = product->getName();
		valid.convertRegister(productLowercase);

		if (productLowercase == lowercaseName) {
			return product;
		}
	}

	return nullptr;
}

shared_ptr<Product> Inventory::searchByCode(const string& productCode)
{
	Validator<string> valid;
	string lowercaseCode = productCode;
	valid.convertRegister(lowercaseCode);
	for (const auto& product : products) {
		string productLowercase = product->getCode();
		valid.convertRegister(productLowercase);

		if (productLowercase == lowercaseCode) {
			return product;
		}
	}

	return nullptr;
}

shared_ptr<Product> Inventory::searchByBrand(const string& productBrand)
{
	Validator<string> valid;
	string lowercaseBrand = productBrand;
	valid.convertRegister(lowercaseBrand);

	for (const auto& product : products) {
		string productLowercase = product->getBrand();
		valid.convertRegister(productLowercase);

		if (productLowercase == lowercaseBrand) {
			return product;
		}
	}

	return nullptr;
}

shared_ptr<Product> Inventory::searchByModel(const string& productModel)
{
	Validator<string> valid;
	string lowercaseModel = productModel;
	valid.convertRegister(lowercaseModel);

	for (const auto& product : products) {
		string productLowercase = product->getModel();
		valid.convertRegister(productLowercase);

		if (productLowercase == lowercaseModel) {
			return product;
		}
	}

	return nullptr;
}


void Inventory::sortByName()
{
	sort(products.begin(), products.end(), [](const shared_ptr<Product>& a, const shared_ptr<Product>& b) {
		return a->getName() < b->getName();
		});
}

//void Inventory::sortByPrice()
//{
//	sort(products.begin(), products.end(), compareByPrice);
//}
//
//
//void Inventory::sortByCode()
//{
//	sort(products.begin(), products.end(), compareByCode);
//}


void Inventory::addProduct(shared_ptr<Product> product)
{
	products.push_back(product);
}

void Inventory::removeProduct(shared_ptr<Product> product)
{
	auto it = find(products.begin(), products.end(), product);
	if (it != products.end()) {
		products.erase(it);
	}
}


void Inventory::printInventory()
{
	ConsoleHelper console;
	SetConsoleTextAttribute(console.getHStdOut(), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	int i = 1;
	printTableFields(LINE_LENGTH);
	for (auto& product : products) {
		cout << left << setw(5) << "| " + to_string(i++);
		product->print();
		console.printLine(LINE_LENGTH);
	}
	system("pause");
	system("CLS");
}

void Inventory::printProduct(shared_ptr<Product> product)
{
	ConsoleHelper console;
	SetConsoleTextAttribute(console.getHStdOut(), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	int i = 1;
	cout << left << setw(5) << "| " + to_string(i++);
	product->print();
	console.printLine(LINE_LENGTH);
}

void Inventory::printTableFields() {
	ConsoleHelper console;
	console.printLine(LINE_LENGTH);
	cout << left << setw(5) << "| №" << setw(17) << "| Название";
	cout << setw(17) << "| Марка";
	cout << setw(20) << "| Модель";
	cout << setw(8) << "| Цена";
	cout << setw(23) << "| Количество на складе";
	cout << setw(24) << "| Количество в магазине";
	cout << setw(23) << "| Количество проданное";
	cout << setw(7) << "| Код" << "|" << endl;
	console.printLine(LINE_LENGTH);
}
