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
	std::string query = "INSERT INTO USERS(username, password, email, address, phoneNumber, birthDate, score) "
		"VALUES('" + username + "', '" + password + "', '" + email + "', '" + address + "', '" + phoneNumber + "', '" + birthDate + "' + 0)";

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

double SqliteDatabase::getPlayerAverageAnswerTime(const std::string& userName)
{
	std::string answer;
	std::string query = "SELECT AVG(time) FROM STATISTICS WHERE username = '" + userName + "'";

	execQuery(query, getSingleStringCallback, &answer);

	return std::stod(answer);
}

int SqliteDatabase::getNumOfCorrectAnswers(const std::string& userName)
{
	std::string answer;
	std::string query = "SELECT COUNT(*) FROM STATISTICS WHERE username = '" + userName + "' AND isCorrect = 1";

	execQuery(query, getSingleStringCallback, &answer);

	return std::stoi(answer);
}

int SqliteDatabase::getPlayerScore(const std::string& userName)
{
	int answer;
	std::string query = "SELECT score FROM USERS WHERE username = '" + userName + "'";

	execQuery(query, getCountCallback, &answer);

	return answer;
}

std::vector<std::pair<std::string,int>> SqliteDatabase::getHighScores()
{
	ScoreList answer;
	std::string query = "SELECT username, score FROM USERS ORDER BY score DESC LIMIT 5";

	execQuery(query, getHighScoresCallback, &answer);

	return answer;
}

int SqliteDatabase::getNumOfTotalAnswers(const std::string& userName)
{
	std::string answer;
	std::string query = "SELECT COUNT(*) FROM STATISTICS WHERE username = '" + userName + "'";

	execQuery(query, getSingleStringCallback, &answer);

	return std::stoi(answer);
}

int SqliteDatabase::getNumOfPlayerGames(const std::string& userName)
{
	std::string answer;
	std::string query = "SELECT COUNT(DISTINCT gameId) FROM STATISTICS WHERE username = '" + userName + "'";

	execQuery(query, getSingleStringCallback, &answer);

	return std::stoi(answer);
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

int SqliteDatabase::calculateScore(const std::string& userName)
{
	int correctAnswers = getNumOfCorrectAnswers(userName);
	int totalAnswers = getNumOfTotalAnswers(userName);
	int averageTime = getPlayerAverageAnswerTime(userName);

	double timeFunction = 1.0 / averageTime;

	return ((correctAnswers / totalAnswers) * CORRECT_ANSWER_WEIGHT * timeFunction) + (((double)totalAnswers / averageTime) * ANSWER_TIME_WEIGHT);
}

int SqliteDatabase::getCountCallback(void* data, int argc, char** argv, char** azColName)
{
	*((int*)data) = atoi(argv[FIRST_VALUE]);
	return 0;
}

int SqliteDatabase::getSingleStringCallback(void* data, int argc, char** argv, char** azColName)
{
	*((std::string*)data) = argv[FIRST_VALUE];
	return 0;
}

int SqliteDatabase::getHighScoresCallback(void* data, int argc, char** argv, char** azColName)
{
	((ScoreList*)data)->push_back(std::make_pair(argv[FIRST_VALUE], atoi(argv[SECOND_VALUE])));
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
