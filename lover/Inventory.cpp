#include "Inventory.h"


Inventory* Inventory::instance = nullptr;

Inventory::Inventory() {
	readFromFile();
}

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
	writeInFile();
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
	ofstream file;
	file.exceptions(fstream::failbit | fstream::badbit);

	try
	{
		file.open("inventory_.txt", ios::out | ios::trunc); // Открываем файл для записи, существующий файл будет перезаписан

		if (file.bad()) {
			throw runtime_error("Ошибка в открытии файла для записи.");
		}

		for (const auto& product : products) {
			file << *product; // Используем перегруженный оператор <<
		}
		cout << "Данные о товарах успешно сохранены в файле!" << endl;
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


vector<shared_ptr<Product>> Inventory::searchByBrand(const string& productBrand)
{
	Validator<string> valid;
	string lowercaseBrand = productBrand;
	valid.convertRegister(lowercaseBrand);

	vector<shared_ptr<Product>> matchingProducts;

	for (const auto& product : products) {
		string productLowercase = product->getBrand();
		valid.convertRegister(productLowercase);

		if (productLowercase == lowercaseBrand) {
			matchingProducts.push_back(product);
		}
	}

	return matchingProducts;
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

vector<shared_ptr<Product>> Inventory::searchByName(const string& productName)
{
	Validator<string> valid;
	string lowercaseName = productName;
	valid.convertRegister(lowercaseName);

	vector<shared_ptr<Product>> matchingProducts;

	for (const auto& product : products) {
		string productLowercase = product->getName();
		valid.convertRegister(productLowercase);

		if (productLowercase == lowercaseName) {
			matchingProducts.push_back(product);
		}
	}

	return matchingProducts;
}

vector<shared_ptr<Product>> Inventory::searchByModel(const string& productModel)
{
	Validator<string> valid;
	string lowercaseModel = productModel;
	valid.convertRegister(lowercaseModel);

	vector<shared_ptr<Product>> matchingProducts;

	for (const auto& product : products) {
		string productLowercase = product->getModel();
		valid.convertRegister(productLowercase);

		if (productLowercase == lowercaseModel) {
			matchingProducts.push_back(product);
		}
	}

	return matchingProducts;
}

vector<shared_ptr<Product>> Inventory::searchByPriceRange(double minPrice, double maxPrice)
{
	vector<shared_ptr<Product>> matchingProducts;

	for (const auto& product : products) {
		double productPrice = product->getPrice();
		if (productPrice >= minPrice && productPrice <= maxPrice) {
			matchingProducts.push_back(product);
		}
	}

	return matchingProducts;
}

vector<shared_ptr<Product>> Inventory::searchByShopQuantity(int minQuantity, int maxQuantity)
{
	vector<shared_ptr<Product>> matchingProducts;

	for (const auto& product : products) {
		int shopQuantity = product->getShopQuantity();
		if (shopQuantity >= minQuantity && shopQuantity <= maxQuantity) {
			matchingProducts.push_back(product);
		}
	}

	return matchingProducts;
}

vector<shared_ptr<Product>> Inventory::searchByWarehouseQuantity(int minQuantity, int maxQuantity)
{
	vector<shared_ptr<Product>> matchingProducts;

	for (const auto& product : products) {
		int warehouseQuantity = product->getWarehouseQuantity();
		if (warehouseQuantity >= minQuantity && warehouseQuantity <= maxQuantity) {
			matchingProducts.push_back(product);
		}
	}

	return matchingProducts;
}

vector<shared_ptr<Product>> Inventory::searchBySoldQuantity(int minQuantity, int maxQuantity)
{
	vector<shared_ptr<Product>> matchingProducts;

	for (const auto& product : products) {
		int soldQuantity = product->getSoldQuantity();
		if (soldQuantity >= minQuantity && soldQuantity <= maxQuantity) {
			matchingProducts.push_back(product);
		}
	}

	return matchingProducts;
}


void Inventory::sortByName()
{
	sort(products.begin(), products.end(), [](const shared_ptr<Product>& a, const shared_ptr<Product>& b) {
		return a->getName() < b->getName();
		});
}

void Inventory::sortByNameDescending()
{
	sort(products.begin(), products.end(), [](const shared_ptr<Product>& a, const shared_ptr<Product>& b) {
		return a->getName() > b->getName();  // Изменено условие сравнения
		});
}

void Inventory::sortByPrice()
{
	sort(products.begin(), products.end(), [](const shared_ptr<Product>& a, const shared_ptr<Product>& b) {
		return a->getPrice() < b->getPrice();
		});
}

void Inventory::sortByPriceDescending()
{
	sort(products.begin(), products.end(), [](const shared_ptr<Product>& a, const shared_ptr<Product>& b) {
		return a->getPrice() > b->getPrice();
		});
}

void Inventory::sortByCode()
{
	sort(products.begin(), products.end(), [](const shared_ptr<Product>& a, const shared_ptr<Product>& b) {
		return a->getCode() < b->getCode();
		});
}

void Inventory::sortByCodeDescending()
{
	sort(products.begin(), products.end(), [](const shared_ptr<Product>& a, const shared_ptr<Product>& b) {
		return a->getCode() > b->getCode();
		});
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


void Inventory::printInventory()
{
	ConsoleHelper console;
	SetConsoleTextAttribute(console.getHStdOut(), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	int i = 1;
	printTableFields();
	for (auto& product : products) {
		cout << left << setw(5) << "| " + to_string(i++);
		product->print();
		console.printLine(LINE_LENGTH);
	}
	system("pause");
	system("CLS");
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
