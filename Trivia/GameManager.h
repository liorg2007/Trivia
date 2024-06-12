#pragma once
#include "IDatabase.h"
#include "Game.h"
#include "Room.h"
#include <vector>
#include <memory>

class GameManager 
{
public:
	static GameManager& getInstance();
	GameManager(GameManager&) = delete;

	Game createGame(const Room& room);
	Game& getGame(unsigned int gameId);
	void deleteGame(unsigned int gameId);

private:
	GameManager();

	std::shared_ptr<IDatabase> _database;
	std::vector<Game> _games;
};