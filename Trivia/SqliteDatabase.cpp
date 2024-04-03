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
	std::string query = "SELECT COUNT(*) FROM USERS WHERE username = '" + username + "'";
	int count = 0;

	sqlite3_exec(_db, query.c_str(), &SqliteDatabase::getCountCallback, &count, nullptr);

	return count == 1;
}

bool SqliteDatabase::IsPasswordOk(const std::string& username, const std::string& password)
{
	std::string query = "SELECT password FROM USERS WHERE username = '" + username + "'";
	std::string userPassword = "";

	sqlite3_exec(_db, query.c_str(), &SqliteDatabase::getSingleStringCallback, &userPassword, nullptr);

	return userPassword == password;
}

int SqliteDatabase::getCountCallback(void* data, int argc, char** argv, char** azColName)
{
	*((int*)data) = atoi(argv[0]);	//0 is first and only value
	return 0;
}

int SqliteDatabase::getSingleStringCallback(void* data, int argc, char** argv, char** azColName)
{
	*((std::string*)data) = argv[0]; //0 is first and only value
	return 0;
}
