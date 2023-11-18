#pragma once
#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <iomanip>
#include <string>

#define ESCAPE 27
#define UP 72
#define DOWN 80
#define ENTER 13
#define BACKSPACE 8


using namespace std;

class ConsoleHelper
{
private:
	HANDLE hStdOut;
public:
	ConsoleHelper();

	HANDLE getHStdOut(); //Функция для получения дескриптора стандартного потока вывода

	void cursorVisible(bool show, short size); //Функция изменения видимости и размера курсора
	void goToXY(short x, short y); //Функция для перемещения курсора в точку с координатами x, y
	void lightingMenu(int activeMenu, string* menu, int x, int y, int size); //Функция для подсветки пункта меню
	void printLine(int length); // Функция, выводящая на консоль линию заданной длины
	void clearLine(int x, int y, int length); //Функция для очищения написанного на консоли
};