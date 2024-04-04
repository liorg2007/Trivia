#pragma once
#include <vector>
#include <mutex>
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
	std::mutex _loggedUserMtx;
	IDatabase* _database;
	std::vector<LoggedUser> _loggedUsers;
};

