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
	std::shared_ptr<GameData> userGameData = _players.at(user);

	if (userGameData->currentQuestion == nullptr) //check that question isn't nullptr. !shouldn't happen but in case of some tampering maybe, then server won't crash
		return;

	if (std::time(nullptr) - _gameDetails.answerTimeout >= userGameData->lastSubmission) 	//check if user submitted answer in time
		++(userGameData->wrongAnswerCount);
	else if(userGameData->currentQuestion->getCorrectAnswerId() == answerId) 	//check if user submitted correct answer
		++(userGameData->correctAnswerCount);
	else
		++(userGameData->wrongAnswerCount);


	userGameData->lastSubmission = std::time(nullptr);
	userGameData->averageAnswerTime = (userGameData->lastSubmission - _gameDetails.gameStartTime) / (userGameData->correctAnswerCount + userGameData->wrongAnswerCount);
	userGameData->currentQuestion = getQuestionForUser(user);
}
