#include "GameManager.h"

GameManager::GameManager()
	: _database(IDatabase::getInstance())
{
}

GameManager& GameManager::getInstance()
{
	static GameManager instance;
	return instance;
}

Game& GameManager::createGame(const Room& room)
{
	const auto& roomData = room.getRoomData();
	GameDetails details;
	details.answerCount = roomData.numOfQuestionsInGame;
	details.answerTimeout = roomData.timerPerQuestion;
	details.gameStartTime = roomData.startTime;
	details.gameId = roomData.id;
	
	std::unique_lock<std::shared_mutex> lock(_mtx);
	const auto& newGameIt = _games.emplace(std::piecewise_construct, std::make_tuple(roomData.id),
		std::make_tuple(room.getAllUsers(), details, _database->getQuestions(details.answerCount)));

	return newGameIt.first->second;
}

Game& GameManager::getGame(unsigned int gameId)
{
	std::shared_lock<std::shared_mutex> lock(_mtx);
	return _games.at(gameId);
}

void GameManager::deleteGame(unsigned int gameId)
{
	_games.at(gameId).submitGameStatsToDB(_database);
	std::unique_lock<std::shared_mutex> lock(_mtx);
	_games.erase(gameId);
}

