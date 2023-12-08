#pragma once
#include "User.h"
#include "Inventory.h"
#include "Product.h"

class UserManager;

class Admin :
    public User
{

public:
    Admin();
    Admin(const string& login, const string& hashPassword, const string& salt, LoginState state);
    void showMenu() override;
    
    void addProduct();
    void deleteProduct();
    void editProduct();
    void editMenu(shared_ptr<Product> productToEdit);
    void userMenu();
};

