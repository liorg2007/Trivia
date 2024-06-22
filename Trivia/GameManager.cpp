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
	auto roomData = room.getRoomData();
	GameDetails details;
	details.answerCount = roomData.numOfQuestionsInGame;
	details.answerTimeout = roomData.timerPerQuestion;
	details.gameStartTime = roomData.startTime;
	details.gameId = roomData.id;

	const auto& newGameIt = _games.emplace(std::piecewise_construct, std::make_tuple(roomData.id),
		std::make_tuple(room.getAllUsers(), details, _database->getQuestions(details.answerCount)));

	return newGameIt.first->second;
}

Game& GameManager::getGame(unsigned int gameId)
{
	return _games.at(gameId);
}

void GameManager::deleteGame(unsigned int gameId)
{
	_games.erase(gameId);
}

