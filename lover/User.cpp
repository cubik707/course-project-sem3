#include "User.h"

User::User(const string& login, const string& hashPassword, const string& salt, LoginState state)
    : login(login), hashPassword(hashPassword), salt(salt), state(state)
{
    menu[0] = "|  ���������� ������ �����������  |";
    menu[1] = "|  ����� �� ���������             |";
    menu[2] = "|  ���������� �� ���������        |";
    menu[3] = "|  ����� �� ���������             |";
    menu[4] = "|  ������� �����                  |";
    menu[5] = "|  �������� ������ � ����         |";
    menu[6] = "|  ����� �� ��������              |";
}

void User::showMenu()
{
    system("CLS");
    cout << "���� ������������";
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
