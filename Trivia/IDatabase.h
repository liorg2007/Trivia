#pragma once
#include <string>
#include "DatabaseException.hpp"

class IDatabase {
public:
	virtual ~IDatabase() = default;

	virtual bool open() = 0;
	virtual bool close() = 0;

	/* Public Queries*/
	virtual void AddUser(const std::string& username, const std::string& password, const std::string& email) = 0;
	virtual bool DoesUserExist(const std::string& username) = 0;
	virtual bool IsPasswordOk(const std::string& username, const std::string& password) = 0;

	IDatabase(IDatabase&) = delete;
	void operator=(const IDatabase&) = delete;

	static IDatabase* getInstance();
protected:
	/* Default c'tor must be declared since the copy c'tor is deleted */
	IDatabase() = default;
};