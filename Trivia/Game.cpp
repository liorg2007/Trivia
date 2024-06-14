#include "Game.h"
#include <optional>

Game::Game(std::vector<std::string> players, GameDetails gameDetails)
	:_gameDetails(gameDetails)
{
	_questions = QuestionsRetriever::retrieveQuestions(gameDetails.answerCount);

	for (const auto& player : players)
	{
		GameData data;
		data.averageAnswerTime = 0;
		data.correctAnswerCount = 0;
		data.wrongAnswerCount = 0;
		data.lastSubmission = 0;
		data.currentQuestion = std::make_shared<Question>(_questions.at(0));

		_players.emplace(player, data);
	}
}

std::optional<std::shared_ptr<Question>> Game::getQuestionForUser(const LoggedUser& user)
{
	std::optional<std::shared_ptr<Question>> question;
	std::shared_ptr<GameData> userGameData = std::make_shared<GameData>(_players.at(user.getUsername()));

	if (userGameData->correctAnswerCount + userGameData->wrongAnswerCount >= _gameDetails.answerCount)
		return question;

	question = std::make_shared<Question>(_questions.at(userGameData->correctAnswerCount + userGameData->wrongAnswerCount));
	return question;
}

void Game::submitAnswer(const LoggedUser& user, unsigned int answerId)
{ 
	std::shared_ptr<GameData> userGameData = std::make_shared<GameData>(_players.at(user.getUsername()));

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
	userGameData->currentQuestion = getQuestionForUser(user).value_or(nullptr);
}

void Game::removePlayer(const LoggedUser& user)
{
	//player removal requires all his remaining answers to be wrong
	GameData& userData = _players.at(user.getUsername());
	userData.wrongAnswerCount = _gameDetails.answerCount - userData.wrongAnswerCount - userData.correctAnswerCount;
}

GameDetails& Game::getGameDetails()
{
	return _gameDetails;
}

std::shared_ptr<std::unordered_map<std::string, GameData>> Game::getPlayersStats()
{
	return std::make_shared<std::unordered_map<std::string, GameData>>(_players);
}
