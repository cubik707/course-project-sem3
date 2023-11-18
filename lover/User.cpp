#include "User.h"

User::User(const string& login, const string& hashPassword, const string& salt, LoginState state)
    : login(login), hashPassword(hashPassword), salt(salt), state(state)
{
    menu[0] = "|  Посмотреть список сотрудников  |";
    menu[1] = "|  Поиск по параметру             |";
    menu[2] = "|  Сортировка по параметру        |";
    menu[3] = "|  Поиск по параметру             |";
    menu[4] = "|  Вывести отчет                  |";
    menu[5] = "|  Записать данные в файл         |";
    menu[6] = "|  Выйти из аккаунта              |";
}

void User::showMenu()
{
    system("CLS");
    cout << "Меню пользователя";
}

string User::genSalt()
{
    srand(time(NULL));
    return to_string(rand() % 1000000);
}

ostream& operator<<(ostream& os, const LoginState& state)
{
    switch (state) {
    case LoginState::Admin:
        os << "Admin";
        break;
    case LoginState::User:
        os << "User";
        break;
    case LoginState::UserToVerify:
        os << "UserToVerify";
        break;
    }
    return os;
}
