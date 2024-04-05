#pragma once
#include "Lib/sqlite3.h"
#include "IDatabase.h"
#include <iostream>

class SqliteDatabase : public IDatabase {
public:
	SqliteDatabase(const std::string& dbName);
	~SqliteDatabase();

	bool open() override;
	bool close() override;

	void AddUser(const std::string& username, const std::string& password, const std::string& email) override;
	bool DoesUserExist(const std::string& username) override;
	bool IsPasswordOk(const std::string& username, const std::string& password) override;

private:
	/* Private Members */
	std::string _dbFileName;
	sqlite3* _db;

	/* Callbacks */
	static int getCountCallback(void* data, int argc, char** argv, char** azColName);
	static int getSingleStringCallback(void* data, int argc, char** argv, char** azColName);
};