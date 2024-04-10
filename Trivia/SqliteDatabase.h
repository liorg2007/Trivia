#pragma once
#include "Lib/sqlite3.h"
#include "IDatabase.h"
#include <iostream>
#include <mutex>

class SqliteDatabase : public IDatabase {
public:
	SqliteDatabase(const std::string& dbName);
	~SqliteDatabase() override;

	bool open() override;
	bool close() override;

	/* Login/Signup Queris */
	void addNewUser(const std::string& username, const std::string& password, const std::string& email, const std::string& address, const std::string& phoneNumber, const std::string& birthDate) override;
	bool doesUserExist(const std::string& username) override;
	bool doesPasswordMatch(const std::string& username, const std::string& password) override;

	/* Statistics Queries */
	float getPlayerAverageAnswerTime(const std::string& userName) override;
	int getNumOfCorrectAnswers(const std::string& userName) override;
	int getNumOfTotalAnswers(const std::string& userName) override;
	int getNumOfPlayerGames(const std::string& userName) override;
	int getNumOfCorrectAnswers(const std::string& userName) override;
	int getPlayerScore(const std::string& userName) override;
	std::vector<std::string> getHighScores() override;

private:
	/* Private Members */
	std::string _dbFileName;
	sqlite3* _db;
	std::mutex _mtx;

	void execQuery(const std::string& query, int(*callback)(void*, int, char**, char**), void* out);

	/* Score Components Weights */
	static constexpr float CORRECT_ANSWER_WEIGHT = 0.6;
	static constexpr float ANSWER_TIME_WEIGHT = 0.4;

	/* Callbacks */
	static int getCountCallback(void* data, int argc, char** argv, char** azColName);
	static int getSingleStringCallback(void* data, int argc, char** argv, char** azColName);
};