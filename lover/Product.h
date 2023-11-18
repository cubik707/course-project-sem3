#pragma once
#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <atltime.h>
#include "ConsoleHelper.h"

using namespace std;
#define FIELD_SEPARATOR '|'

class Product
{
protected:
	string name;
	string brand;
	string model;
	double price;
	int shopQuantity;
	int warehouseQuantity;
	int soldQuantity;
	string code;
public:
	Product();
	Product(const string& name, double price, int soldQuantity, int warehouseQuantity, int shopQuantity, const string& code, const string& brand, const string& model);

	string getName() const;
	void setName(const string& name);
	double getPrice() const;
	void setPrice(double price);
	string getCode() const;
	void setCode(const string& code);
	string getBrand() const;
	void setBrand(const string& brand);
	string getModel() const;
	void setModel(const string& model);
	int getSoldQuantity() const;
	void setSoldQuantity(int soldQuantity);
	int getShopQuantity() const;
 	void setShopQuantity(int shopQuantity);
	int getWarehouseQuantity() const;
	void setWarehouseQuantity(int warehouseQuantity);




	void print() const;

	friend ofstream& operator<< (ofstream& out, const Product& product);
	friend ifstream& operator>> (ifstream& is, Product& product);
};

class ProductException : public std::exception {
public:
	const char* what() const noexcept override {
		return "Ошибка при создании продукта";
	}
};
