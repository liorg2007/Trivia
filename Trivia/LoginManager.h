#pragma once
#include <vector>
#include <mutex>
#include "IDatabase.h"
#include "LoggedUser.h"
#include <iostream>

class LoginManager
{
public:
	/* Singleton instance */
	static LoginManager& getInstance();

	bool signup(const std::string& username, const std::string& password, const std::string& email, const std::string& address, const std::string& phoneNumber, const std::string& birthDate);
	bool login(const std::string& username, const std::string& password);
	bool logout(const std::string& username);

	/* No copy constructor */
	LoginManager(LoginManager&) = delete;
	void operator=(const LoginManager&) = delete;

private:
	LoginManager();

	std::mutex _loggedUserMtx;
	std::shared_ptr<IDatabase> _database;
	std::vector<LoggedUser> _loggedUsers;
};

