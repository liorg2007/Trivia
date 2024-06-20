#include "Game.h"

Game::Game(std::vector<std::string>&& players, const GameDetails& gameDetails, std::vector<Question>&& questions)
	: _gameDetails(gameDetails), _questions(std::move(questions))
{
	for (const auto& player : players)
	{
		_players.emplace(player, GameData(0, 0, 0, 0, 0));
	}
}

Question& Game::getQuestionForUser(const LoggedUser& user)
{
	GameData& userGameData = _players.at(user.getUsername());

	Question& question = _questions.at(userGameData.currentQuestionIndex + 1);

	userGameData.currQuestionStartTime = std::time(nullptr);//the user's time starts when he asks for question
	userGameData.currentQuestionIndex++; //update, user gets next question

	return question;//used a variable for question so if it crashes the lastSubmission and currentQuestionIndex arent tampered
}

bool Game::submitAnswer(const LoggedUser& user, unsigned int answerId)
{
	bool isCorrect;
	GameData& userGameData = _players.at(user.getUsername());

	if (std::time(nullptr) - _gameDetails.answerTimeout > userGameData.currQuestionStartTime // user either didnt submit in time
		|| _questions.at(userGameData.currentQuestionIndex).getCorrectAnswerId() != answerId) // or the answer is wrong
	{
		++userGameData.wrongAnswerCount;
		isCorrect = false;
	}
	else //check if user submitted correct answer
	{
		++userGameData.correctAnswerCount;
		isCorrect = true;
	}

	userGameData.averageAnswerTime = (userGameData.currQuestionStartTime - _gameDetails.gameStartTime)
		/ (userGameData.correctAnswerCount + userGameData.wrongAnswerCount);

	return isCorrect;
}

void Game::removePlayer(const LoggedUser& user)
{
	//player removal requires all his remaining answers to be wrong
	GameData& userData = _players.at(user.getUsername());
	userData.hasLeftGame = true;

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

std::list<PlayerResults> Game::getPlayersStats() const
{
	std::list<PlayerResults> resultsList;
	PlayerResults result;
	for (const auto& gameStat : _players)
	{
		const int totalAnswered = gameStat.second.correctAnswerCount + gameStat.second.wrongAnswerCount;
		result.username = gameStat.first; //username
		result.wrongAnswerCount = _gameDetails.answerCount - gameStat.second.correctAnswerCount; //also satisfies case where user didnt answer everything
		result.correctAnswerCount = gameStat.second.correctAnswerCount; //all users correct answers

		result.averageAnswerTime = gameStat.second.averageAnswerTime;

		result.finishedGame = (totalAnswered < _gameDetails.answerCount);

		//add the result to the list
		resultsList.push_back(result);
	}
	return resultsList;
}
