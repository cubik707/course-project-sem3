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
	Manager(); // ����������� �� ���������
	~Manager(); // ����������

	virtual void readFromFile() = 0;
	virtual void fillVector(ifstream& file) = 0;
	virtual void writeToFile(const string& filename) = 0;

	void welcomeMessage(); //�������, ��������� �� ������� ��������� "����� ����������!"
};

