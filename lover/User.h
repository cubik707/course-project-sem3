#pragma once
#include <iostream>
#include <conio.h>
#include <string>
#include "ConsoleHelper.h"
#include "Inventory.h"

using namespace std;

enum class LoginState { // Перечисление состояний авторизации
    Admin,
    User,
    UserToVerify
};
ostream& operator<<(ostream& os, const LoginState& state); // Перегрузка оператора << для вывода состояния авторизации в поток

class User
{
protected:
    string login;                // Имя пользователя
    string hashPassword;         // Хэш пароля пользователя
    string salt;                 // Соль для хэширования пароля
    LoginState state;            // Состояние авторизации пользователя

    ConsoleHelper console;       // Вспомогательный класс для ввода/вывода через консоль
public:
    User(); // Конструктор по умолчанию
    User(const string& login, const string& hashPassword, const string& salt, LoginState state); // Параметризированный конструктор
    virtual void showMenu(); // Виртуальная функция для отображения меню пользователя

    void searchMenu(); // Меню поиска
    void searchForName(); // Поиск по названию продукта
    void searchForBrand(); // Поиск по бренду продукта
    void searchForModel(); // Поиск по модели продукта
    void searchForCode(); // Поиск по коду продукта

    void sortMenu(); // Меню сортировки продуктов

    void filterMenu(); // Меню фильтрации продуктов
    void filterForPrice(); // Фильтрация по цене
    void filterForShopQ(); // Фильтрация по количеству в магазине
    void filterForWarehouseQ(); // Фильтрация по количеству на складе
    void filterForSoldQ(); // Фильтрация по количеству проданных продуктов

    void createReport(); // Создание отчета

    string genSalt(); // Генерация случайной соли

    // Геттеры и сеттеры для полей класса
    string getLogin() { return login; }
    string getHashPassword() { return hashPassword; }
    string getSalt() { return salt; }
    LoginState getState() { return state; }
    void setLogin(string login) { this->login = login; }
    void setHashPassword(string hashPassword) { this->hashPassword = hashPassword; }
    void setSalt(string salt) { this->salt = salt; }
    void setState(LoginState state) { this->state = state; }
};

