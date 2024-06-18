#include "Game.h"
#include <optional>

Game::Game(std::vector<std::string>&& players, const GameDetails& gameDetails, std::vector<Question>&& questions)
	: _gameDetails(gameDetails), _questions(questions)
{
	for (const auto& player : players)
	{
		GameData data(0, 0, 0, 0, 0);

		_players.emplace(player, data);
	}
}

Question& Game::getQuestionForUser(const LoggedUser& user)
{
	GameData& userGameData = _players.at(user.getUsername());

	Question& question = _questions.at(userGameData.currentQuestionIndex + 1);

	userGameData.lastSubmission = std::time(nullptr);//the user's time starts when he asks for question
	userGameData.currentQuestionIndex++; //update, user gets next question

	return question;//used a variable for question so if it crashes the lastSubmission and currentQuestionIndex arent tampered
}

bool Game::submitAnswer(const LoggedUser& user, unsigned int answerId)
{ 
	bool isCorrect = false; //this is the starting state, if answer is correct it'll be true
	GameData& userGameData = _players.at(user.getUsername());

	if (std::time(nullptr) - _gameDetails.answerTimeout >= userGameData.lastSubmission) 	//check if user submitted answer in time
		++(userGameData.wrongAnswerCount);
	else if (_questions.at(userGameData.currentQuestionIndex).getCorrectAnswerId() == answerId) 	//check if user submitted correct answer
	{
		++(userGameData.correctAnswerCount);
		isCorrect = true;
	}
	else
		++(userGameData.wrongAnswerCount);

	userGameData.averageAnswerTime = (userGameData.lastSubmission - _gameDetails.gameStartTime) / (userGameData.correctAnswerCount + userGameData.wrongAnswerCount);

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

std::unordered_map<std::string, GameData>& Game::getPlayersStats()
{
	return _players;
}
