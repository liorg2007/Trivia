#pragma once
#include "IDatabase.h"
#include <vector>
#include <string>

class StatisticsManager
{
public:
	ScoreList getHighScores() const;
	std::vector<std::string> getUserStatistics(const std::string& username) const;

	static StatisticsManager& getInstance();
	StatisticsManager(StatisticsManager&) = delete;
	void operator=(StatisticsManager&) = delete;
private:
	StatisticsManager();

	IDatabase* _database;
};