#pragma once
#include "Lib/sqlite3.h"
#include "IDatabase.h"
#include "Constants.h"
#include <array>
#include <iostream>
#include <mutex>

class SqliteDatabase : public IDatabase {
public:
	SqliteDatabase(const std::string& dbName);
	~SqliteDatabase() override;

	bool open() override;
	bool close() override;

	/* Login/Signup Queries */
	void addNewUser(const std::string& username, const std::string& password, const std::string& email, const std::string& address, const std::string& phoneNumber, const std::string& birthDate) override;
	bool doesUserExist(const std::string& username) override;
	bool doesPasswordMatch(const std::string& username, const std::string& password) override;

	std::vector<Question> getQuestions(int amount) override;

	/* Statistics Queries */
	double getPlayerAverageAnswerTime(const std::string& userName) override;
	int getNumOfCorrectAnswers(const std::string& userName) override;
	int getNumOfTotalAnswers(const std::string& userName) override;
	int getNumOfPlayerGames(const std::string& userName) override;
	int getPlayerScore(const std::string& userName) override;
	ScoreList getHighScores() override;

	void submitGameStatsToDB(const std::unordered_map<std::string, GameData>& gameData) override;

private:
	/* Private Members */
	std::string _dbFileName;
	sqlite3* _db;
	std::mutex _mtx;

	void insertNewQuestionsIfNeeded(int amount);
	void insertNewQuestions(int amount);
	inline void execQuery(const std::string& query, int(*callback)(void*, int, char**, char**), void* out);
	// callback-less execQuery
	inline void execQuery(const std::string& query);

	/* Score Components Weights */
	static constexpr double CORRECT_ANSWER_WEIGHT = 0.6;
	static constexpr double ANSWER_TIME_WEIGHT = 0.4;

	int calculateScore(const std::string& userName);

	/* Callbacks */
	static int getCountCallback(void* data, int argc, char** argv, char** azColName);
	static int getSingleStringCallback(void* data, int argc, char** argv, char** azColName);
	static int getDoubleCallback(void* data, int argc, char** argv, char** azColName);
	static int getQuestionsCallback(void* data, int argc, char** argv, char** azColName);
	static int getHighScoresCallback(void* data, int argc, char** argv, char** azColName);
	static int scoreDataCallback(void* data, int argc, char** argv, char** azColName);

	/* Questions table count */
	static constexpr auto QUESTIONS_MINIMUM_AMOUNT = 10;

	/* Callbacks constants */
	static constexpr auto FIRST_VALUE = 0;
	static constexpr auto SECOND_VALUE = 1;
};

struct ScoreData {
	int correctAnswers;
	int totalAnswers;
	int averageTime;
};