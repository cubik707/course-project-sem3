#pragma once
#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

template <class T>
class Validator
{
public:
	// ��������� �� ������������ �������� ���� T � �������� ���������
	static T getVar(T minLim, T maxLim);
	// ��������� �� ������������ �������� ������
	static string getValidStr();
	// �������������� ������ ����� ������ � �������� ��������, � ��������� � �������
	static void convertRegister(std::string& str);
};
template<class T>
inline T Validator<T>::getVar(T minLim, T maxLim)
{
	T resultVar = T();
	bool is_valid = false;
	do {
		try
		{
			std::cin >> resultVar;
			if (std::cin.fail() || resultVar > maxLim || resultVar < minLim)
			{
				throw std::runtime_error("������ �����!");
			}
			is_valid = true;
		}
		catch (const std::exception& e)
		{
			std::cout << e.what() << std::endl;
			std::cout << "������� ����� �� "
				+ std::to_string(minLim) + " �� " + std::to_string(maxLim) + "." << std::endl;
			std::cin.clear();
			std::cin.ignore(INT_MAX, '\n');
		}

	} while (!is_valid || std::cin.peek() != '\n');

	return resultVar;
}

template<class T>
inline string Validator<T>::getValidStr() {
	std::string str;
	bool is_valid = false;

	do {
		try {
			std::getline(std::cin, str);
			if (std::cin.fail() || str.empty()) {
				throw std::runtime_error("������ �����! ������ �����!");
				std::cin.ignore();
			}
			is_valid = true;
		}
		catch (const std::exception& e) {
			std::cerr << e.what() << std::endl;
		}
	} while (!is_valid);

	return str;
}

template<class T>
inline void Validator<T>::convertRegister(std::string& str)
{
	if (!str.empty()) {
		str[0] = toupper(str[0]);
		for (int i = 1; i < str.length(); i++) {
			str[i] = tolower(str[i]);
		}
	}
}


