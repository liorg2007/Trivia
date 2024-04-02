#include "SqliteDatabase.h"

SqliteDatabase::SqliteDatabase(const std::string& dbName)
{
	int result = 0;
	result = sqlite3_open(dbName.c_str(), &_db); //open database file

	if (result) {
		std::string errorMsg = std::string(sqlite3_errmsg(_db));
		sqlite3_close(_db);
		throw("Error with sqlite database: " + errorMsg);
	}
	else {
		std::cout << "Sqlite database opened!" << std::endl;

		//create table if it doesnt exists
		std::string tableQuery = "CREATE TABLE IF NOT EXISTS USERS ("
                            "id INTEGER PRIMARY KEY,"
                            "username TEXT UNIQUE NOT NULL,"
                            "password TEXT NOT NULL,"
														"email TEXT NOT NULL);";

		sqlite3_exec(_db, tableQuery.c_str(), nullptr, nullptr, nullptr);
	}
	sqlite3_close(_db);
}

SqliteDatabase::~SqliteDatabase()
{
	sqlite3_close(_db);
}

void SqliteDatabase::AddUser(const std::string& username, const std::string& password, const std::string& email)
{
}

bool SqliteDatabase::DoesUserExist(const std::string& username)
{
	return false;
}

bool SqliteDatabase::IsPasswordOk(const std::string& password)
{
	return false;
}
