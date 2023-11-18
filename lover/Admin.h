#pragma once
#include "User.h"
#include "Inventory.h"
#include "Product.h"

class Admin :
    public User
{
private:
    //string menu[9];

public:
    Admin(const string& login, const string& hashPassword, const string& salt, LoginState state);
    void showMenu() override;

    void addProduct();
    void removeProduct();
    void editProduct();
    void showAllProducts();
    void showAllUsers();
    void changeUserData();
    void deleteUser();
    void sortUsers();
    void searchUser();
    void userControlMenu();
    void showReport();
};

