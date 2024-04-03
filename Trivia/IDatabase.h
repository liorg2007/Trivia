#pragma once
#include <string>


class IDatabase {
public:
	/* Public Queries*/
	virtual void AddUser(const std::string& username, const std::string& password, const std::string& email) = 0;

	/* Private Queries */
	virtual bool DoesUserExist(const std::string& username) = 0;
	virtual bool IsPasswordOk(const std::string& username, const std::string& password) = 0;
};