#pragma once
#include "Lib/sqlite3.h"
#include "IDatabase.h"
#include <iostream>

class SqliteDatabase : public IDatabase {
public:
	SqliteDatabase(const std::string& dbName);
	~SqliteDatabase();

	void AddUser(const std::string& username, const std::string& password, const std::string& email) override;

private:
	/* Private Members */
	sqlite3* _db;

	/* Private Queries */
	bool DoesUserExist(const std::string& username) override;
	bool IsPasswordOk(const std::string& password) override;
};