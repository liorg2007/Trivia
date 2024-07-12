#include "LoginManager.h"

LoginManager::LoginManager()
	: _database(IDatabase::getInstance())
{
}

LoginManager& LoginManager::getInstance()
{
	static LoginManager instance;
	return instance;
}

bool LoginManager::signup(const std::string& username, const std::string& password, const std::string& email, const std::string& address, const std::string& phoneNumber, const std::string& birthDate)
{
	try {
		if (!_database->doesUserExist(username))
		{
			std::lock_guard<std::mutex> lock(_loggedUserMtx);

			_database->addNewUser(username, password, email, address, phoneNumber, birthDate);
			_loggedUsers.emplace_back(username);
			return true;
		}
	}
	catch (const DatabaseException& e) {
		std::cerr << e.what() << std::endl;
		return false;
	}

	return false;
}

bool LoginManager::login(const std::string& username, const std::string& password)
{
	std::lock_guard<std::mutex> lock(_loggedUserMtx);
	try {
		if (std::find(_loggedUsers.begin(), _loggedUsers.end(), username) == _loggedUsers.end()
			&& _database->doesPasswordMatch(username, password))
		{
			_loggedUsers.emplace_back(username);
			return true;
		}
	}
	catch (const DatabaseException& e)
	{
		std::cerr << e.what() << std::endl;
		return false;
	}

	return false;
}

bool LoginManager::logout(const std::string& username)
{
	std::lock_guard<std::mutex> lock(_loggedUserMtx);
	const auto& search = std::find(_loggedUsers.begin(), _loggedUsers.end(), username);
	if (search != _loggedUsers.end())
	{
		_loggedUsers.erase(search);
		return true;
	}
	return false;
}
