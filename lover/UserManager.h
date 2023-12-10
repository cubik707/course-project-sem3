#pragma once
#include <vector>
#include <memory>
#include "Validator.h"
#include "Manager.h"
#include "Admin.h"
#include <sstream>

using namespace std;

class UserManager
	: public Manager
{
private:
	static UserManager* instance; // Указатель на единственный экземпляр UserManager
	UserManager(); // Приватный конструктор для реализации синглтона

	vector<shared_ptr<User>> users; // Вектор всех пользователей
	vector<shared_ptr<Admin>> admins; // Вектор всех администраторов
	vector<shared_ptr<User>> usersToVerify; // Вектор пользователей, ожидающих верификации
	ConsoleHelper console; // Объект для ввода/вывода через консоль

public:
	static UserManager* getInstance(); // Получение единственного экземпляра UserManager
	UserManager(const UserManager&) = delete; // Запрещаем копирование
	UserManager& operator=(const UserManager&) = delete; // Запрещаем присваивание
	~UserManager(); // Деструктор

	vector<shared_ptr<User>> getUsers() const; // Получение всех пользователей
	vector<shared_ptr<Admin>> getAdmins() const; // Получение всех администраторов
	vector<shared_ptr<User>> getUsersToVerify() const; // Получение пользователей, ожидающих верификации

	void showMenu(); // Отображение меню пользователя

	void autorisation(LoginState state); // Авторизация пользователя
	shared_ptr<Admin> isAuthenticationAdmin(const string& login, const string& password); // Проверка аутентификации администратора
	shared_ptr<User> isAuthenticationUser(const string& login, const string& password); // Проверка аутентификации пользователя
	void checkLogPass(LoginState state, const string& login, const string& password); // Проверка логина и пароля
	void errorAutorisation(); // Ошибка авторизации
	void registration(); // Регистрация нового пользователя

	void printAccount(); // Вывод информации об аккаунте
	void addAccount(); // Добавление нового аккаунта
	void deleteAccount(int choice, string login); // Удаление аккаунта
	void editAccount(); // Редактирование аккаунта
	void confirmAccount(); // Подтверждение аккаунта

	string genHashPassword(string password, string salt); // Генерация хэша пароля с использованием соли

	void readFromFile() override; // Чтение данных из файла
	void fillVector(ifstream& file) override; // Заполнение векторов данными из файла
	LoginState stateToString(const string& stateStr); // Преобразование строки в состояние авторизации
	void writeToFile(const string& filename) override; // Запись данных в файл
};

