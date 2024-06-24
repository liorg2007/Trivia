#include "SqliteDatabase.h"
#include "QuestionsRetriever.h"

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
			"username TEXT NOT NULL UNIQUE, "
			"gameAmount INTEGER, "
			"questions INTEGER, "
			"correctAnswers INTEGER, "
			"avgTime REAL, "
			"FOREIGN KEY(username) REFERENCES USERS(username));";
		execQuery(tableQuery);
		insertNewQuestionsIfNeeded(QUESTIONS_MINIMUM_AMOUNT);
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
	//create the user in USERS table
	std::string query = "INSERT INTO USERS(username, password, email, address, phoneNumber, birthDate, score) "
		"VALUES('" + username + "', '" + password + "', '" + email + "', '" + address + "', '" + phoneNumber + "', '" + birthDate + "', 0)";

	execQuery(query);

	//create the user in STATISTICS table
	query = "INSERT INTO STATISTICS(username, gameAmount, questions, correctAnswers, avgTime) "
		"VALUES('" + username + "', 0, 0, 0, 0);";

	execQuery(query);
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

std::vector<Question> SqliteDatabase::getQuestions(int amount)
{
	insertNewQuestionsIfNeeded(amount);
	std::vector<Question> questions;
	questions.reserve(amount);
	auto query = "SELECT * FROM QUESTIONS ORDER BY RANDOM() LIMIT " + std::to_string(amount) + ';';
	execQuery(query, getQuestionsCallback, &questions);
	return questions;
}

double SqliteDatabase::getPlayerAverageAnswerTime(const std::string& userName)
{
	double answer;
	std::string query = "SELECT avgTime FROM STATISTICS WHERE username = '" + userName + "'";

	execQuery(query, getDoubleCallback, &answer);

	return answer;
}

int SqliteDatabase::getNumOfCorrectAnswers(const std::string& userName)
{
	std::string answer;
	std::string query = "SELECT correctAnswers FROM STATISTICS WHERE username = '" + userName + "'";

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

ScoreList SqliteDatabase::getHighScores()
{
	ScoreList answer;
	std::string query = "SELECT username, score FROM USERS ORDER BY score DESC LIMIT 5";

	execQuery(query, getHighScoresCallback, &answer);

	return answer;
}

void SqliteDatabase::submitGameStatsToDB(const std::unordered_map<std::string, GameData>& gameData) 
{
	int updatedScore;

	for (const auto& pair : gameData) {
		const std::string& username = pair.first;
		const GameData& data = pair.second;

		// Update existing statistics
		std::stringstream updateStatsSQL;
		updateStatsSQL << "UPDATE STATISTICS SET "
			<< "gameAmount = gameAmount + 1, "
			<< "correctAnswers = correctAnswers + " << data.correctAnswerCount << ", "
			<< "avgTime = " << "(avgTime * questions +" << data.averageAnswerTime * (data.wrongAnswerCount + data.correctAnswerCount) << ")" <<
			"/ ( questions + " << (data.correctAnswerCount + data.wrongAnswerCount) << "), "
			<< "questions = questions + " << data.correctAnswerCount + data.wrongAnswerCount
			<< " WHERE username = '" << username << "';";

		execQuery(updateStatsSQL.str());

		// Update the user's score in the USERS table
		updatedScore = calculateScore(username);

		std::stringstream updateUserScoreSQL;
		updateUserScoreSQL << "UPDATE USERS SET score = " << updatedScore << " WHERE username = '" << username << "';";

		execQuery(updateUserScoreSQL.str());
	}
}

int SqliteDatabase::getNumOfTotalAnswers(const std::string& userName)
{
	std::string answer;
	std::string query = "SELECT questions FROM STATISTICS WHERE username = '" + userName + "'";

	execQuery(query, getSingleStringCallback, &answer);

	return std::stoi(answer);
}

int SqliteDatabase::getNumOfPlayerGames(const std::string& userName)
{
	std::string answer;
	std::string query = "SELECT gameAmount FROM STATISTICS WHERE username = '" + userName + "'";

	execQuery(query, getSingleStringCallback, &answer);

	return std::stoi(answer);
}

inline void SqliteDatabase::execQuery(const std::string& query)
{
	execQuery(query, nullptr, nullptr);
}

void SqliteDatabase::execQuery(const std::string& query, int(*callback)(void*, int, char**, char**), void* out)
{
	std::lock_guard<std::mutex> lock(_mtx);
	char* errmsg = nullptr;
	if (sqlite3_exec(_db, query.c_str(), callback, out, &errmsg) != SQLITE_OK)
	{
		DatabaseException exception(errmsg);
		std::cerr << "Database exception: " << exception.what() << std::endl;
		sqlite3_free(errmsg);
		throw exception;
	}
}

void SqliteDatabase::insertNewQuestionsIfNeeded(int amount)
{
	auto query = "SELECT COUNT(*) FROM QUESTIONS;";
	std::string questionsCountString;
	execQuery(query, getSingleStringCallback, &questionsCountString);
	auto questionsCount = std::stoi(questionsCountString);
	if (questionsCount < amount)
	{
		try
		{
			insertNewQuestions(amount - questionsCount);
		}
		catch (const std::exception& e)
		{
			std::cerr << "Error recieving questions from api: " << e.what() << std::endl;
		}
	}
}

void SqliteDatabase::insertNewQuestions(int amount)
{
	// the begin keyword is for starting a transaction (https://www.geeksforgeeks.org/sqlite-transaction/)
	std::string query = "BEGIN;";
	for (const auto& question : QuestionsRetriever::retrieveQuestions(amount))
	{
		query += "INSERT OR IGNORE INTO QUESTIONS(question, correctAnswerId, answer_1, answer_2, answer_3, answer_4) "
			"VALUES(\"" + question.getQuestion() + "\", " + std::to_string(question.getCorrectAnswerId());
		for (const auto& answer : question.getPossibleAnswers())
		{
			query += ",\"" + answer + '"';
		}
		query += ");";
	}
	// ending the transaction
	query += "END;";
	execQuery(query);
}

int SqliteDatabase::calculateScore(const std::string& userName)
{
	ScoreData scoreData = { 0, 0, 0 };

	std::stringstream query;
	query << "SELECT "
		<< "correctAnswers, "
		<< "questions, "
		<< "avgTime "
		<< "FROM STATISTICS "
		<< "WHERE username = '" << userName << "';";

	execQuery(query.str(), scoreDataCallback, &scoreData);

	// Avoid division by zero
	if (scoreData.totalAnswers == 0 || scoreData.averageTime == 0)
		return 0;

	double accuracy = static_cast<double>(scoreData.correctAnswers) / scoreData.totalAnswers;
	double timeFactor = 1.0 / scoreData.averageTime;

	double score = (accuracy * 100) * (timeFactor * SCALING_FACTOR);

	return static_cast<int>(score);
}

int SqliteDatabase::getCountCallback(void* data, int argc, char** argv, char** azColName)
{
	*(reinterpret_cast<int*>(data)) = atoi(argv[FIRST_VALUE]);
	return 0;
}

int SqliteDatabase::getSingleStringCallback(void* data, int argc, char** argv, char** azColName)
{
	*(reinterpret_cast<std::string*>(data)) = argv[FIRST_VALUE];
	return 0;
}

int SqliteDatabase::getDoubleCallback(void* data, int argc, char** argv, char** azColName)
{
	if (*argv == NULL)
		*(reinterpret_cast<double*>(data)) = 0;
	else
		*(reinterpret_cast<double*>(data)) = std::stod(argv[FIRST_VALUE]);
	return 0;
}

int SqliteDatabase::getHighScoresCallback(void* data, int argc, char** argv, char** azColName)
{
	(reinterpret_cast<ScoreList*>(data))->push_back(std::make_pair(argv[FIRST_VALUE], atoi(argv[SECOND_VALUE])));
	return 0;
}

int SqliteDatabase::scoreDataCallback(void* data, int argc, char** argv, char** azColName)
{
	ScoreData* scoreData = static_cast<ScoreData*>(data);
	scoreData->correctAnswers = std::stoi(argv[0] ? argv[0] : "0");
	scoreData->totalAnswers = std::stoi(argv[1] ? argv[1] : "0");
	scoreData->averageTime = std::stod(argv[2] ? argv[2] : "0.0");
	return 0;
}

int SqliteDatabase::getQuestionsCallback(void* data, int argc, char** argv, char** azColName)
{
	std::vector<Question>& questions = *(reinterpret_cast<std::vector<Question>*>(data));
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
	questions.emplace_back(questionPromptPtr, std::move(answers), correctAnswerId);
	return 0;
}
