#include "GameManager.h"

GameManager::GameManager()
{
}

GameManager& GameManager::getInstance()
{
	static GameManager instance;
	return instance;
}

Game& GameManager::getGame(unsigned int gameId)
{
	return _games.at(gameId);
}

