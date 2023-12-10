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
	static Inventory* instance; // Указатель на единственный экземпляр Inventory
	std::vector<shared_ptr<Product>> products; // Вектор продуктов в инвентаре
	Inventory(); // Приватный конструктор для реализации синглтона

public:
	static Inventory* getInstance(); // Получение единственного экземпляра Inventory
	Inventory(const Inventory&) = delete; // Запрещаем копирование
	Inventory& operator=(Inventory&) = delete; // Запрещаем присваивание
	~Inventory(); // Деструктор

	std::vector<shared_ptr<Product>> getProducts(); // Получение всех продуктов из инвентаря

	void readFromFile(); // Чтение данных из файла
	void fillVectorFromFile(ifstream& file); // Заполнение вектора продуктов данными из файла
	void writeInFile(); // Запись данных в файл
	void writeInFile(const string& filename); // Запись данных в указанный файл

	bool hasProduct(const string& productName); // Проверка наличия продукта по названию

	vector<shared_ptr<Product>> searchByName(const string& productName); // Поиск по названию продукта
	shared_ptr<Product> searchByCode(const string& productCode); // Поиск по коду продукта
	vector<shared_ptr<Product>> searchByBrand(const string& productBrand); // Поиск по бренду продукта
	vector<shared_ptr<Product>> searchByModel(const string& productModel); // Поиск по модели продукта
	vector<shared_ptr<Product>> searchByPriceRange(double minPrice, double maxPrice); // Поиск по диапазону цен
	vector<shared_ptr<Product>> searchByShopQuantity(int minQuantity, int maxQuantity); // Поиск по количеству в магазине
	vector<shared_ptr<Product>> searchByWarehouseQuantity(int minQuantity, int maxQuantity); // Поиск по количеству на складе
	vector<shared_ptr<Product>> searchBySoldQuantity(int minQuantity, int maxQuantity); // Поиск по количеству проданных продуктов

	void sortByName(); // Сортировка по названию
	void sortByNameDescending(); // Сортировка по названию в обратном порядке
	void sortByPrice(); // Сортировка по цене
	void sortByPriceDescending(); // Сортировка по цене в обратном порядке
	void sortByCode(); // Сортировка по коду
	void sortByCodeDescending(); // Сортировка по коду в обратном порядке

	void addProduct(shared_ptr<Product> product); // Добавление продукта в инвентарь
	void removeProduct(shared_ptr<Product> product); // Удаление продукта из инвентаря

	void printTableFields(); // Вывод заголовков таблицы
	void printInventory(); // Вывод содержимого инвентаря
};