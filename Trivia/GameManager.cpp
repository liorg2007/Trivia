#include "GameManager.h"

GameManager::GameManager()
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

	Game game = Game(room.getAllUsers(), details);
	_games.insert({ roomData.id, game });

	return game;
}

Game& GameManager::getGame(unsigned int gameId)
{
	return _games.at(gameId);
}

