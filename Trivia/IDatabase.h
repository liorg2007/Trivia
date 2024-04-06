#pragma once
#include <string>
#include "DatabaseException.hpp"

class IDatabase {
public:
	virtual bool open() = 0;
	virtual bool close() = 0;

	/* Public Queries*/
	virtual void AddUser(const std::string& username, const std::string& password, const std::string& email, const std::string& address, const std::string& phoneNumber, const std::string& birthDate) = 0;
	virtual bool DoesUserExist(const std::string& username) = 0;
	virtual bool IsPasswordOk(const std::string& username, const std::string& password) = 0;

};