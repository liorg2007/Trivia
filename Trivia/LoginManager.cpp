#include "LoginManager.h"

LoginManager::LoginManager(IDatabase* database)
	: _database(database)
{
}

bool LoginManager::signup(const std::string& username, const std::string& password, const std::string& email)
{
	if (!_database->DoesUserExist(username))
	{
		std::lock_guard<std::mutex> lock(_loggedUserMtx);

		_database->AddUser(username, password, email);
		_loggedUsers.push_back(LoggedUser(username));
		return true;
	}
	return false;
}

bool LoginManager::login(const std::string& username, const std::string& password)
{
	LoggedUser newLoggedUser(username);
	{
		std::lock_guard<std::mutex> lock(_loggedUserMtx);

		if (std::find(_loggedUsers.begin(), _loggedUsers.end(), newLoggedUser) == _loggedUsers.end()
			&& _database->IsPasswordOk(username, password))
		{
			_loggedUsers.push_back(LoggedUser(username));
			return true;
		}
	}
	return false;
}

bool LoginManager::logout(const std::string& username)
{
	auto search = std::find(_loggedUsers.begin(), _loggedUsers.end(), LoggedUser(username));
	if (search != _loggedUsers.end())
	{
		_loggedUsers.erase(search);
		return true;
	}
	return false;
}
