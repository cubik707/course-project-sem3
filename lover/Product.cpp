#include "Product.h"

Product::Product()
	: name("-"), price(0), soldQuantity(0), warehouseQuantity(0), shopQuantity(0), code("-"), brand("-"), model("-")
{

}



Product::Product(const string& name, double price, int soldQuantity, int warehouseQuantity, int shopQuantity, const string& code, const string& brand, const string& model)
	: name(name), price(price), soldQuantity(soldQuantity), warehouseQuantity(warehouseQuantity), shopQuantity(shopQuantity), code(code), brand(brand), model(model)
{
}


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
	int width = 15; // Øטנטםא סעמכבצמג
	cout.setf(ios::left);
	cout << "| " << setw(width) << name;
	cout << "| " << setw(width) << brand;
	cout << "| " << setw(18) << model;
	cout << "| " << setw(6) << price << std::noshowpoint;
	cout << "| " << setw(21) << warehouseQuantity;
	cout << "| " << setw(22) << shopQuantity;
	cout << "| " << setw(21) << soldQuantity;
	cout << "| " << setw(5) << code << "|" << endl;
	cout.unsetf(ios::left);
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
	os << product.name << "|" << product.brand << "|" << product.model << "|" 
		<< product.price << "|" << product.warehouseQuantity << "|" <<  product.shopQuantity 
		<< "|" << product.soldQuantity << "|" << product.code << endl;
	return os;
}


ifstream& operator>>(ifstream& is, Product& product)
{
	getline(is, product.name, FIELD_SEPARATOR);
	getline(is, product.brand, FIELD_SEPARATOR);
	getline(is, product.model, FIELD_SEPARATOR);
	is >> product.price;
	is.ignore(1, FIELD_SEPARATOR);
	is >> product.warehouseQuantity;
	is.ignore(1, FIELD_SEPARATOR);
	is >> product.shopQuantity;
	is.ignore(1, FIELD_SEPARATOR);
	is >> product.soldQuantity;
	is.ignore(1, FIELD_SEPARATOR);
	getline(is, product.code, '\n');
	return is;
}
