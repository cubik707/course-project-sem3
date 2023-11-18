#include "Product.h"

//Product::Product()
//	: name("-"), price(0), quantity(0), code("-")
//{
//
//}

// default constructor
Product::Product()
	: name("-"), price(0), soldQuantity(0), warehouseQuantity(0), shopQuantity(0), code("-"), brand("-"), model("-")
{

}



Product::Product(const string& name, double price, int soldQuantity, int warehouseQuantity, int shopQuantity, const string& code, const string& brand, const string& model)
	: name(name), price(price), soldQuantity(soldQuantity), warehouseQuantity(warehouseQuantity), shopQuantity(shopQuantity), code(code), brand(brand), model(model)
{
	if (price < 0 || soldQuantity < 0 || warehouseQuantity < 0 || shopQuantity < 0) {
		throw ProductException();
	}
}



//Product::Product(const string& name, double price, int quantity, const string& code)
//	:name(name), price(price), quantity(quantity), code(code)
//{
//	if (price < 0 || quantity < 0) {
//		throw ProductException();
//	}
//}

//getters and setters
string Product::getName() const
{
	return this->name;
}

void Product::setName(const string& name)
{
	this->name = name;
}

double Product::getPrice() const
{
	return this->price;
}

void Product::setPrice(double price)
{
	this->price = price;
}

//int Product::getQuantity() const
//{
//	return this->quantity;
//}

//void Product::setQuantity(int quantity)
//{
//	this->quantity = quantity;
//}

string Product::getCode() const
{
	return this->code;
}

void Product::setCode(const string& code)
{
	this->code = code;
}

void Product::print() const
{
	int width = 13; // Øטנטםא סעמכבצמג
	cout.setf(ios::left | ios::fixed | ios::dec);
	cout << "| " << setw(24) << name;
	cout << "| " << setw(14) << brand;
	cout << "| " << setw(14) << model;
	cout << "| " << setw(11) << price;
	cout << "| " << setw(43) << warehouseQuantity;
	cout << "| " << setw(43) << shopQuantity;
	cout << "| " << setw(43) << soldQuantity;
	cout << "| " << setw(9) << code << "|" << endl;
	cout.unsetf(ios::left | ios::fixed | ios::dec);
}


string Product::getBrand() const {
	return brand;
}
void Product::setBrand(const string& brand) {
	this->brand = brand;
}
string Product::getModel() const {
	return model;
}
void Product::setModel(const string& model) {
	this->model = model;
}
int Product::getSoldQuantity() const {
	return soldQuantity;
}
void Product::setSoldQuantity(int soldQuantity) {
	this->soldQuantity = soldQuantity;
}
int Product::getShopQuantity() const {
	return shopQuantity;
}
void Product::setShopQuantity(int shopQuantity) {
	this->shopQuantity = shopQuantity;
}

int Product::getWarehouseQuantity() const {
	return warehouseQuantity;
}
void Product::setWarehouseQuantity(int warehouseQuantity) {
	this->warehouseQuantity = warehouseQuantity;
}






ofstream& operator<<(ofstream& os, const Product& product)
{
	os << product.name << "|" << product.price << "|" << product.soldQuantity << "|" 
	<< product.warehouseQuantity <<  "|" <<  product.shopQuantity << "|" << product.code << endl;
	return os;
}



ifstream& operator>>(ifstream& is, Product& product)
{
	getline(is, product.name, '|');
	is >> product.price;
	is.ignore(1, '|');
	is >> product.soldQuantity;
	is.ignore(1, '|');
	is >> product.warehouseQuantity;
	is.ignore(1, '|');
	is >> product.shopQuantity;
	is.ignore(1, '|');
	getline(is, product.code, '\n');
	return is;
}
