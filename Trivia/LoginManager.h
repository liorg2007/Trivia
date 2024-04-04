#pragma once
#include <vector>
#include "IDatabase.h"
#include "LoggedUser.h"

class LoginManager
{
public:
	LoginManager(IDatabase* database);

	bool signup(const std::string& username, const std::string& password, const std::string& email);
	bool login(const std::string& username, const std::string& password);
	bool logout(const std::string& username);

private:
	IDatabase* _database;
	std::vector<LoggedUser> _loggedUsers;
};

