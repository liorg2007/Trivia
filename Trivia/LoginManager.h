#pragma once
#include <vector>
#include <mutex>
#include "IDatabase.h"
#include "LoggedUser.h"

class LoginManager
{
public:
	/* Singleton instance */
	static LoginManager& getInstance(IDatabase* database);

	bool signup(const std::string& username, const std::string& password, const std::string& email);
	bool login(const std::string& username, const std::string& password);
	bool logout(const std::string& username);

	/* No copy constructor */
	LoginManager(LoginManager&) = delete;
	void operator=(const LoginManager&) = delete;

private:
	LoginManager(IDatabase* database);

	std::mutex _loggedUserMtx;
	IDatabase* _database;
	std::vector<LoggedUser> _loggedUsers;
};

