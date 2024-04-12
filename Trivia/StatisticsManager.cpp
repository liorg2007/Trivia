#include "StatisticsManager.h"

StatisticsManager::StatisticsManager()
    : _database(IDatabase::getInstance())
{
}

ScoreList StatisticsManager::getHighScores() const
{
    return _database->getHighScores();
}

UserStatistics StatisticsManager::getUserStatistics(const std::string& username) const
{
    UserStatistics stats;
    stats.averageAnswerTime = _database->getPlayerAverageAnswerTime(username);
    stats.correctAnswers = _database->getNumOfCorrectAnswers(username);
    stats.score = _database->getPlayerScore(username);
    stats.totalAnswers = _database->getNumOfTotalAnswers(username);
    return stats;
}

StatisticsManager& StatisticsManager::getInstance()
{
    static StatisticsManager instance;
    return instance;
}