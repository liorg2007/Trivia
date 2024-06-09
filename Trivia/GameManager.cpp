#include "GameManager.h"

GameManager& GameManager::getInstance()
{
	static GameManager instance;
	return instance;
}
