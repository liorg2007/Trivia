#include "Game.h"
#include <optional>

Game::Game(std::vector<std::string>&& players, const GameDetails& gameDetails, std::vector<Question>&& questions)
	: _gameDetails(gameDetails), _questions(questions)
{
	for (const auto& player : players)
	{
		GameData data(_questions.at(0), 0, 0, 0, 0);

		_players.emplace(player, data);
	}
}

Question& Game::getQuestionForUser(const LoggedUser& user)
{
	GameData& userGameData = _players.at(user.getUsername());

	if (userGameData.correctAnswerCount + userGameData.wrongAnswerCount >= _gameDetails.answerCount)
		throw std::exception();

	return _questions.at(userGameData.correctAnswerCount + userGameData.wrongAnswerCount);
}

bool Game::submitAnswer(const LoggedUser& user, unsigned int answerId)
{ 
	bool isCorrect = false; //this is the starting state, if answer is correct it'll be true
	GameData& userGameData = _players.at(user.getUsername());

	if (std::time(nullptr) - _gameDetails.answerTimeout >= userGameData.lastSubmission) 	//check if user submitted answer in time
		++(userGameData.wrongAnswerCount);
	else if (userGameData.currentQuestion.getCorrectAnswerId() == answerId) 	//check if user submitted correct answer
	{
		++(userGameData.correctAnswerCount);
		isCorrect = true;
	}
	else
		++(userGameData.wrongAnswerCount);


	userGameData.lastSubmission = std::time(nullptr);
	userGameData.averageAnswerTime = (userGameData.lastSubmission - _gameDetails.gameStartTime) / (userGameData.correctAnswerCount + userGameData.wrongAnswerCount);
	userGameData.currentQuestion = getQuestionForUser(user);

	return isCorrect;
}

void Game::removePlayer(const LoggedUser& user)
{
	//player removal requires all his remaining answers to be wrong
	GameData& userData = _players.at(user.getUsername());

	int totalAnswered = userData.wrongAnswerCount + userData.correctAnswerCount;

	time_t answeredTime = userData.averageAnswerTime * totalAnswered; //avg = answeredTime / totalAnswered. answeredTime = avg * totalAnswered
	time_t totalTime = answeredTime + _gameDetails.answerTimeout * (_gameDetails.answerCount - totalAnswered); //totalTime = already Answred Time + (answer Timeout * not answered)

	userData.averageAnswerTime = totalTime / _gameDetails.answerCount;
	userData.wrongAnswerCount = _gameDetails.answerCount - userData.correctAnswerCount;
}

const GameDetails& Game::getGameDetails() const
{
	return _gameDetails;
}

std::shared_ptr<std::unordered_map<std::string, GameData>> Game::getPlayersStats()
{
	return std::make_shared<std::unordered_map<std::string, GameData>>(_players);
}
