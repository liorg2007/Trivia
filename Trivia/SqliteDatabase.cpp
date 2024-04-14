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

		// create user table if it doesnt exists
		std::string tableQuery = 
			"CREATE TABLE IF NOT EXISTS USERS ("
			"username TEXT NOT NULL PRIMARY KEY,"
			"password TEXT NOT NULL,"
			"email TEXT NOT NULL,"
			"address TEXT NOT NULL, "
			"phoneNumber TEXT NOT NULL, "
			"birthDate TEXT NOT NULL, "
			"score INTEGER); "
			
		// create questions table if it doesnt exists
			"CREATE TABLE IF NOT EXISTS QUESTIONS ("
			"id INTEGER PRIMARY KEY AUTOINCREMENT,"
			"question TEXT UNIQUE NOT NULL,"
			"answer_1 TEXT NOT NULL,"
			"answer_2 TEXT NOT NULL,"
			"answer_3 TEXT NOT NULL,"
			"answer_4 TEXT NOT NULL,"
			"correctAnswerId INTEGER NOT NULL); "

		// create statistics table if it doesnt exists
			"CREATE TABLE IF NOT EXISTS STATISTICS ("
			"gameId INTEGER, "
			"username TEXT NOT NULL, "
			"questionId INTEGER, "
			"isCorrect INTEGER, "
			"time REAL, "
			"FOREIGN KEY(username) REFERENCES USERS(username), "
			"FOREIGN KEY(gameId) REFERENCES GAMES(id));";

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

std::list<Question> SqliteDatabase::getQuestions(int amount)
{
	std::list<Question> questions;
	auto query = "SELECT * FROM QUESTIONS ORDER BY RANDOM() LIMIT " + std::to_string(amount) + ';';
	execQuery(query, getQuestionsCallback, &questions);
	return questions;
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

void SqliteDatabase::insertNewQuestions()
{
	// https://opentdb.com/api.php?amount=10&type=multiple

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

int SqliteDatabase::getQuestionsCallback(void* data, int argc, char** argv, char** azColName)
{
	std::list<Question>& questions = *((std::list<Question>*)data);
	std::vector<std::string> answers;
	char* questionPromptPtr;
	int correctAnswerId;
	for (int i = 0; i < argc; i++)
	{
		std::string col = azColName[i];
		if (col.rfind("answer", 0) == 0)
		{
			answers.emplace_back(argv[i]);
		}
		else if (col == "question")
		{
			questionPromptPtr = argv[i];
		}
		else if (col == "correctAnswerId")
		{
			correctAnswerId = std::stoi(argv[i]);
		}
	}
	questions.emplace_back(questionPromptPtr, answers, correctAnswerId);
	return 0;
}
