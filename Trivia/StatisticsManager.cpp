#include "StatisticsManager.h"

std::vector<std::string> StatisticsManager::getHighScore() const
{
    return std::vector<std::string>();
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

StatisticsManager::StatisticsManager()
{}
