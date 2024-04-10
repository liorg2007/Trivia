#pragma once
#include <string>
#include <vector>
#include "DatabaseException.hpp"

class IDatabase {
public:
	virtual ~IDatabase() = default;

	virtual bool open() = 0;
	virtual bool close() = 0;

	/* Login Queries*/
	virtual void addNewUser(const std::string& username, const std::string& password, const std::string& email, const std::string& address, const std::string& phoneNumber, const std::string& birthDate) = 0;
	virtual bool doesUserExist(const std::string& username) = 0;
	virtual bool doesPasswordMatch(const std::string& username, const std::string& password) = 0;

	/* Statistics Queries */
	virtual float getPlayerAverageAnswerTime(const std::string& userName) = 0;
	virtual int getNumOfCorrectAnswers(const std::string& userName) = 0;
	virtual int getNumOfTotalAnswers(const std::string& userName) = 0;
	virtual int getNumOfPlayerGames(const std::string& userName) = 0;
	virtual int getNumOfCorrectAnswers(const std::string& userName) = 0;
	virtual int getPlayerScore(const std::string& userName) = 0;
	virtual std::vector<std::string> getHighScores() = 0;

	IDatabase(IDatabase&) = delete;
	void operator=(const IDatabase&) = delete;

	static IDatabase* getInstance();
protected:
	/* Default c'tor must be declared since the copy c'tor is deleted */
	IDatabase() = default;
};