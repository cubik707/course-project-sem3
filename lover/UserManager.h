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
	static UserManager* instance;
	UserManager();

	vector<shared_ptr<User>> users;
	vector<shared_ptr<Admin>> admins;
	vector<shared_ptr<User>> usersToVerify;
	ConsoleHelper console;
public:
	static UserManager* getInstance();
	UserManager(const UserManager&) = delete;
	UserManager& operator=(const UserManager&) = delete;
	~UserManager();

	vector<shared_ptr<User>> getUsers() const;
	vector<shared_ptr<Admin>> getAdmins() const;
	vector<shared_ptr<User>> getUsersToVerify() const;

	void showMenu();

	void autorisation(LoginState state);
	shared_ptr<Admin> isAuthenticationAdmin(const string& login, const string& password);
	shared_ptr<User> isAuthenticationUser(const string& login, const string& password);
	void checkLogPass(LoginState state, const string& login, const string& password);
	void errorAutorisation();
	void registration();

	void printAccount();
	void addAccount();
	void deleteAccount(int choice, string login);
	void editAccount();
	void confirmAccount();

	string genHashPassword(string password, string salt);

	void readFromFile() override;
	void fillVector(ifstream& file) override;
	LoginState stateToString(const string& stateStr);
	void writeToFile(const string& filename) override;
};

