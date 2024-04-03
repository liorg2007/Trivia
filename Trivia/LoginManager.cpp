#include "LoginManager.h"

LoginManager::LoginManager(IDatabase* database)
	: _database(database)
{
}

void LoginManager::signup(const std::string& username, const std::string& password, const std::string& email)
{
	if (!_database->DoesUserExist(username))
	{
		_database->AddUser(username, password, email);
	}
}

void LoginManager::login(const std::string& username, const std::string& password)
{
	LoggedUser newLoggedUser(username);
	if (std::find(_loggedUsers.begin(), _loggedUsers.end(), newLoggedUser) != _loggedUsers.end()
		&& _database->IsPasswordOk(username, password))
	{
		_loggedUsers.push_back(LoggedUser(username));
	}
}

void LoginManager::logout(const std::string& username)
{
	auto search = std::find(_loggedUsers.begin(), _loggedUsers.end(), LoggedUser(username));
	if (search != _loggedUsers.end())
	{
		_loggedUsers.erase(search);
	}
}
