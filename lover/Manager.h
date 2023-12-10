#pragma once
#include "ConsoleHelper.h"
#include "Validator.h"
#include "User.h"
#include "Admin.h"
#include <fstream>

class Manager
{
private:
public:
	Manager(); // Конструктор по умолчанию
	~Manager(); // Деструктор

	virtual void readFromFile() = 0; // Чисто виртуальная функция для чтения данных из файла
	virtual void fillVector(ifstream& file) = 0; // Чисто виртуальная функция для заполнения вектора данными из файла
	virtual void writeToFile(const string& filename) = 0; // Чисто виртуальная функция для записи данных в файл

	void welcomeMessage(); //Функция, выводящая на консоль сообщение "Добро пожаловать!"
};

