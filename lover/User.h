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
ostream& operator<<(ostream& os, const LoginState& state);

class User
{
protected:
    string login;
    string hashPassword;
    string salt;
    LoginState state;

    ConsoleHelper console;
public:
    User();
    User(const string& login, const string& hashPassword, const string& salt, LoginState state);
    virtual void showMenu();

    void searchMenu();
    void searchForName();
    void searchForBrand();
    void searchForModel();
    void searchForCode();

    void sortMenu();

    void filterMenu();
    void filterForPrice();
    void filterForShopQ();
    void filterForWarehouseQ();
    void filterForSoldQ();

    void createReport();

    string genSalt();

    string getLogin() { return login; }
    string getHashPassword() { return hashPassword; }
    string getSalt() { return salt; }
    LoginState getState() { return state; }
    void setLogin(string login) { this->login = login; }
    void setHashPassword(string hashPassword) { this->hashPassword = hashPassword; }
    void setSalt(string salt) { this->salt = salt; }
    void setState(LoginState state) { this->state = state; }
};

