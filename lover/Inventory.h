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
	static Inventory* instance; // ��������� �� ������������ ��������� Inventory
	std::vector<shared_ptr<Product>> products; // ������ ��������� � ���������
	Inventory(); // ��������� ����������� ��� ���������� ���������

public:
	static Inventory* getInstance(); // ��������� ������������� ���������� Inventory
	Inventory(const Inventory&) = delete; // ��������� �����������
	Inventory& operator=(Inventory&) = delete; // ��������� ������������
	~Inventory(); // ����������

	std::vector<shared_ptr<Product>> getProducts(); // ��������� ���� ��������� �� ���������

	void readFromFile(); // ������ ������ �� �����
	void fillVectorFromFile(ifstream& file); // ���������� ������� ��������� ������� �� �����
	void writeInFile(); // ������ ������ � ����
	void writeInFile(const string& filename); // ������ ������ � ��������� ����

	bool hasProduct(const string& productName); // �������� ������� �������� �� ��������

	vector<shared_ptr<Product>> searchByName(const string& productName); // ����� �� �������� ��������
	shared_ptr<Product> searchByCode(const string& productCode); // ����� �� ���� ��������
	vector<shared_ptr<Product>> searchByBrand(const string& productBrand); // ����� �� ������ ��������
	vector<shared_ptr<Product>> searchByModel(const string& productModel); // ����� �� ������ ��������
	vector<shared_ptr<Product>> searchByPriceRange(double minPrice, double maxPrice); // ����� �� ��������� ���
	vector<shared_ptr<Product>> searchByShopQuantity(int minQuantity, int maxQuantity); // ����� �� ���������� � ��������
	vector<shared_ptr<Product>> searchByWarehouseQuantity(int minQuantity, int maxQuantity); // ����� �� ���������� �� ������
	vector<shared_ptr<Product>> searchBySoldQuantity(int minQuantity, int maxQuantity); // ����� �� ���������� ��������� ���������

	void sortByName(); // ���������� �� ��������
	void sortByNameDescending(); // ���������� �� �������� � �������� �������
	void sortByPrice(); // ���������� �� ����
	void sortByPriceDescending(); // ���������� �� ���� � �������� �������
	void sortByCode(); // ���������� �� ����
	void sortByCodeDescending(); // ���������� �� ���� � �������� �������

	void addProduct(shared_ptr<Product> product); // ���������� �������� � ���������
	void removeProduct(shared_ptr<Product> product); // �������� �������� �� ���������

	void printTableFields(); // ����� ���������� �������
	void printInventory(); // ����� ����������� ���������
};