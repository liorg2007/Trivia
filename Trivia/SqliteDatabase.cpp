#include "SqliteDatabase.h"

SqliteDatabase::SqliteDatabase(const std::string& dbName)
	: _dbFileName(dbName), _db(nullptr)
{
	open();
}

SqliteDatabase::~SqliteDatabase()
{
	close();
}

bool SqliteDatabase::open()
{
	int result = sqlite3_open(_dbFileName.c_str(), &_db); //open database file

	if (result) {
		std::string errorMsg = std::string(sqlite3_errmsg(_db));
		sqlite3_close(_db);
		throw DatabaseException("Error with sqlite database: " + errorMsg);
	}
	else {
		std::cout << "Sqlite database opened!" << std::endl;

		//create user table if it doesnt exists
		std::string tableQuery = "CREATE TABLE IF NOT EXISTS USERS ("
			"username TEXT NOT NULL PRIMARY KEY,"
			"password TEXT NOT NULL,"
			"email TEXT NOT NULL,"
			"address TEXT NOT NULL, "
			"phoneNumber TEXT NOT NULL, "
			"birthDate TEXT NOT NULL); ";

		execQuery(tableQuery, nullptr, nullptr);

		//create statistics table if it doesnt exists
		tableQuery = "CREATE TABLE IF DOESNT EXISTS STATISTICS ("
			"gameId INTEGER, "
			"username TEXT NOT NULL, "
			"questionId INTEGER, "
			"isCorrect INTEGER, "
			"time REAL, ";

		execQuery(tableQuery, nullptr, nullptr);
	}
	return true;
}

bool SqliteDatabase::close()
{
	if (_db != nullptr)
	{
		sqlite3_close(_db);
		return true;
	}
	return false;
}

void SqliteDatabase::addNewUser(const std::string& username, const std::string& password, const std::string& email, const std::string& address, const std::string& phoneNumber, const std::string& birthDate)
{
	std::string query = "INSERT INTO USERS(username, password, email, address, phoneNumber, birthDate) "
		"VALUES('" + username + "', '" + password + "', '" + email + "', '" + address + "', '" + phoneNumber + "', '" + birthDate + "')";

	execQuery(query, nullptr, nullptr);
}

bool SqliteDatabase::doesUserExist(const std::string& username)
{
	std::string query = "SELECT EXISTS(SELECT 1 FROM USERS WHERE username = '" + username + "')";
	int count = 0;

	execQuery(query, getCountCallback, &count);

	return count;
}

bool SqliteDatabase::doesPasswordMatch(const std::string& username, const std::string& password)
{
	std::string query = "SELECT password FROM USERS WHERE username = '" + username + "'";
	std::string userPassword = "";

	execQuery(query, getSingleStringCallback, &userPassword);

	return userPassword == password;
}

float SqliteDatabase::getPlayerAverageAnswerTime(const std::string& userName)
{
	return 0.0f;
}

void SqliteDatabase::execQuery(const std::string& query, int(*callback)(void*, int, char**, char**), void* out)
{
	std::lock_guard<std::mutex> lock(_mtx);
	char* errmsg = nullptr;
	if (sqlite3_exec(_db, query.c_str(), callback, out, &errmsg) != SQLITE_OK)
	{
		DatabaseException exception(errmsg);
		sqlite3_free(errmsg);
		throw exception;
	}
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
