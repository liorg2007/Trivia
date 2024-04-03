#pragma once
#include <vector>
#include "IDatabase.h"
#include "LoggedUser.h"

class LoginManager
{
public:
	LoginManager(IDatabase* database);

	void signup(const std::string& username, const std::string& password, const std::string& email);
	void login(const std::string& username, const std::string& password);
	void logout(const std::string& username);

private:
	IDatabase* _database;
	std::vector<LoggedUser> _loggedUsers;
};

