#pragma once
#include "IDatabase.h"
#include "Game.h"
#include "Room.h"
#include <vector>
#include <memory>

class GameManager 
{
public:
	GameManager();
	Game createGame(const Room& room);
	void deleteGame(unsigned int gameId);

private:
	std::shared_ptr<IDatabase> _database;
	std::vector<Game> _games;
};