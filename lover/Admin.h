#pragma once
#include "User.h"
#include "Inventory.h"
#include "Product.h"

class Admin : public User {
public:
    Admin(); // Конструктор по умолчанию
    Admin(const string& login, const string& hashPassword, const string& salt, LoginState state); // Параметризированный конструктор
    void showMenu() override; // Переопределенная функция для отображения меню администратора

    void addProduct(); // Функция для добавления нового продукта в инвентарь
    void deleteProduct(); // Функция для удаления продукта из инвентаря
    void editProduct(); // Функция для редактирования существующего продукта в инвентаре
    void editMenu(shared_ptr<Product> productToEdit); // Функция для отображения меню редактирования для конкретного продукта
    void userMenu(); // Функция для отображения меню управления пользователями
};
