#pragma once
#include "Lib/sqlite3.h"
#include "IDatabase.h"
#include <iostream>
#include <mutex>

class SqliteDatabase : public IDatabase {
public:
	SqliteDatabase(const std::string& dbName);
	~SqliteDatabase();

	bool open() override;
	bool close() override;

	void AddUser(const std::string& username, const std::string& password, const std::string& email, const std::string& address, const std::string& phoneNumber, const std::string& birthDate) override;
	bool DoesUserExist(const std::string& username) override;
	bool IsPasswordOk(const std::string& username, const std::string& password) override;

private:
	/* Private Members */
	std::string _dbFileName;
	sqlite3* _db;
	std::mutex _mtx;

	void execQuery(const std::string& query, int(*callback)(void*, int, char**, char**), void* out);

	/* Callbacks */
	static int getCountCallback(void* data, int argc, char** argv, char** azColName);
	static int getSingleStringCallback(void* data, int argc, char** argv, char** azColName);
};