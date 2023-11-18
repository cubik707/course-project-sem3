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
	file.exceptions(std::fstream::failbit | std::fstream::badbit);

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
	catch (const std::ios_base::failure& e)
	{
		// Обрабатываем ошибку, используя флаги статуса ошибок
		std::cerr << "Ошибка ввода-вывода: " << e.what() << std::endl;
		exit(0);
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

bool Inventory::hasProduct(const string& productName)
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
	valid.toLowercase(lowercaseName);

	for (const auto& product : products) {
		string productLowercase = product->getName();
		valid.toLowercase(productLowercase);

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
	valid.toLowercase(lowercaseCode);
	for (const auto& product : products) {
		string productLowercase = product->getCode();
		valid.toLowercase(productLowercase);

		if (productLowercase == lowercaseCode) {
			return product;
		}
	}

	return nullptr;
}


void Inventory::sortByName()
{
	sort(products.begin(), products.end(), compareByName);
}

void Inventory::sortByPrice()
{
	sort(products.begin(), products.end(), compareByPrice);
}


void Inventory::sortByCode()
{
	sort(products.begin(), products.end(), compareByCode);
}


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



void Inventory::editProduct(shared_ptr<Product> product) {

	Validator<string> validString;
	Validator<double> validDouble;
	Validator<int> validInt;

	string newName, newCode;
	double newPrice;
	int newSoldQuantity, newWarehouseQuantity, newShopQuantity;


	cout << "Введите новое название продукта: ";
	newName = validString.getValidStr();

	cout << "Введите новую цену: ";
	newPrice = validDouble.getVar(0, INT_MAX);

	// Enter new sold quantity
	cout << "Введите новое количество проданного товара: ";
	newSoldQuantity = validInt.getVar(0, INT_MAX);

	cout << "Введите новое количество товара на складе: ";
	newWarehouseQuantity = validInt.getVar(0, INT_MAX);

	cout << "Введите новое количество товара в магазине: ";
	newShopQuantity = validInt.getVar(0, INT_MAX);

	



	do {
		cout << "Введите новый код: ";
		newCode = validString.getValidStr();
	} while (hasProduct(newCode));



	product->setName(newName);
	product->setPrice(newPrice);
	product->setSoldQuantity(newSoldQuantity);
	product->setWarehouseQuantity(newWarehouseQuantity);
	product->setShopQuantity(newShopQuantity);

	product->setCode(newCode);

	return;
}

void Inventory::printInventory()
{
	int length = 89, i = 1;
	ConsoleHelper console;

	printTableFields(length);
	for (auto& product : products) {
		cout << left << setw(5) << "| " + to_string(i++);
		product->print();
		console.printLine(length);
	}
}

void Inventory::printTableFields(int length) {
	int width = 15;
	ConsoleHelper console;
	console.printLine(length);
	cout << setw(5) << "| №" << setw(40) << "| Название";
	cout << setw(width) << "| Цена";
	cout << setw(width) << "| Количество";
	cout << setw(width) << "| Код" << "|" << endl;
	console.printLine(length);
}


bool compareByName(const shared_ptr<Product>& a, const shared_ptr<Product>& b)
{
	return a->getName() < b->getName();
}

bool compareByCode(const shared_ptr<Product>& a, const shared_ptr<Product>& b)
{
	return a->getCode() < b->getCode();
}

bool compareByPrice(const shared_ptr<Product>& a, const shared_ptr<Product>& b)
{
	return a->getPrice() < b->getPrice();
}
