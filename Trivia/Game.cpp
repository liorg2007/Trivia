#include "Game.h"

Game::Game(std::vector<std::string> players, GameDetails gameDetails)
	:_gameDetails(gameDetails)
{
	for (const auto& player : players)
	{
		GameData data;
		data.averageAnswerTime = 0;
		data.correctAnswerCount = 0;
		data.wrongAnswerCount = 0;
		data.lastSubmission = 0;
		data.currentQuestion = nullptr;

		_players.emplace(player, data)
	}

	_questions = QuestionsRetriever::retrieveQuestions(gameDetails.answerCount);
}

void Game::submitAnswer(const LoggedUser& user, unsigned int answerId)
{
}
