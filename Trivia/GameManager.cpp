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

Game GameManager::createGame(const Room& room)
{
	auto roomData = room.getRoomData();
	GameDetails details;
	details.answerCount = roomData.numOfQuestionsInGame;
	details.answerTimeout = roomData.timerPerQuestion;
	details.gameStartTime = roomData.startTime;
	details.gameId = roomData.id;

	Game game = Game(room.getAllUsers(), details, _database->getQuestions(details.answerCount));
	_games.insert({ roomData.id, game });

	return game;
}

Game& GameManager::getGame(unsigned int gameId)
{
	return _games.at(gameId);
}

void GameManager::deleteGame(unsigned int gameId)
{
	_games.erase(gameId);
}

