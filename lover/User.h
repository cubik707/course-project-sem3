#pragma once
#include <iostream>
#include <conio.h>
#include <string>
#include "ConsoleHelper.h"


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

    string menu[7];
    int size;
    string line;

    ConsoleHelper console;
public:
    User(const string& login, const string& hashPassword, const string& salt, LoginState state);
    virtual void showMenu();

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

