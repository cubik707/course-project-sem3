#pragma once
#include "Product.h"
#include "Validator.h"
#include "ConsoleHelper.h"
#include <iterator>
#include <algorithm>

#define LINE_LENGTH 143

class Inventory
{
private:
	static Inventory* instance;
	std::vector<shared_ptr<Product>> products;
	Inventory() {};
public:
	static Inventory* getInstance();
	Inventory(const Inventory&) = delete;
	Inventory& operator=(Inventory&) = delete;
	~Inventory();

	std::vector<shared_ptr<Product>> getProducts();

	void readFromFile();
	void fillVectorFromFile(ifstream& file);
	void writeInFile();

	bool hasProduct(const string& productName);

	shared_ptr<Product> searchByName(const string& productName);
	shared_ptr<Product> searchByCode(const string& productCode);
	shared_ptr<Product> searchByBrand(const string& productBrand);
	shared_ptr<Product> searchByModel(const string& productModel);
	//shared_ptr<Product> searchByPrice(double productPrice);
	//shared_ptr<Product> searchByQuantity(int productQuantity);

	void sortByName();
	void sortByPrice();
	//void sortByQuantity();
	void sortByCode();

	void addProduct(shared_ptr<Product> product);
	void removeProduct(shared_ptr<Product> product);

	void printTableFields();
	void printInventory();
	void printProduct(shared_ptr<Product> product);
};