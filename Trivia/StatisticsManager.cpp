#include "StatisticsManager.h"

StatisticsManager::StatisticsManager()
    : _database(IDatabase::getInstance())
{
}

ScoreList StatisticsManager::getHighScores() const
{
    return _database->getHighScores();
}

std::vector<std::string> StatisticsManager::getUserStatistics(const std::string& username) const
{
    return std::vector<std::string>();
}

StatisticsManager& StatisticsManager::getInstance()
{
    static StatisticsManager instance;
    return instance;
}