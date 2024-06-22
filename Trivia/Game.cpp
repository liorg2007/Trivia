#include "Game.h"
#include "GameManager.h"

Game::Game(std::vector<std::string>&& players, const GameDetails& gameDetails, std::vector<Question>&& questions)
	: _gameDetails(gameDetails), _questions(std::move(questions)), _leftPlayersCount(0), _totalAnswers(players.size() * gameDetails.answerCount), _answersCount(0)
{
	for (const auto& player : players)
	{
		_players.emplace(std::piecewise_construct, std::make_tuple(player), std::make_tuple(-1, 0, 0, 0, 0));
	}
}

Question& Game::getQuestionForUser(const LoggedUser& user)
{
	const auto& search = _players.find(user.getUsername());
	if (search == _players.end())
	{
		throw std::exception("Player not in game");
	}
	GameData& userGameData = search->second;
	Question& question = _questions.at(userGameData.currentQuestionIndex + 1);

	std::unique_lock<std::shared_mutex> lock(_mtx);

	userGameData.currQuestionStartTime = std::time(nullptr);//the user's time starts when he asks for question
	userGameData.currentQuestionIndex++; //update, user gets next question

	return question;//used a variable for question so if it crashes the lastSubmission and currentQuestionIndex arent tampered
}

bool Game::submitAnswer(const LoggedUser& user, unsigned int answerId)
{
	std::unique_lock<std::shared_mutex> lock(_mtx);

	GameData& userGameData = _players.at(user.getUsername());
	unsigned int correctAnswerId = _questions.at(userGameData.currentQuestionIndex).getCorrectAnswerId();

	if (std::time(nullptr) - _gameDetails.answerTimeout > userGameData.currQuestionStartTime // user either didnt submit in time
		|| correctAnswerId != answerId) // or the answer is wrong
	{
		++userGameData.wrongAnswerCount;
	}
	else //check if user submitted correct answer
	{
		++userGameData.correctAnswerCount;
	}

	userGameData.averageAnswerTime = (userGameData.currQuestionStartTime - _gameDetails.gameStartTime)
		/ (userGameData.correctAnswerCount + userGameData.wrongAnswerCount);

	_answersCount++;

	return correctAnswerId;
}

void Game::removePlayer(const LoggedUser& user)
{
	std::unique_lock<std::shared_mutex> lock(_mtx);

	//player removal requires all his remaining answers to be wrong
	GameData& userData = _players.at(user.getUsername());
	int totalAnswered = userData.wrongAnswerCount + userData.correctAnswerCount;

	if (totalAnswered != _gameDetails.answerCount)
	{
		time_t answeredTime = userData.averageAnswerTime * totalAnswered; //avg = answeredTime / totalAnswered. answeredTime = avg * totalAnswered
		time_t totalTime = answeredTime + _gameDetails.answerTimeout * (_gameDetails.answerCount - totalAnswered); //totalTime = already Answred Time + (answer Timeout * not answered)

		userData.averageAnswerTime = totalTime / _gameDetails.answerCount;
		userData.wrongAnswerCount = _gameDetails.answerCount - userData.correctAnswerCount;
		_answersCount += _gameDetails.answerCount - totalAnswered;
	}

	if (++_leftPlayersCount == _players.size())
	{
		closeGame();
	}
}

const GameDetails& Game::getGameDetails() const
{
	std::shared_lock<std::shared_mutex> lock(_mtx);
	return _gameDetails;
}

std::list<PlayerResults> Game::getPlayersStats() const
{
	std::shared_lock<std::shared_mutex> lock(_mtx);

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

bool Game::isGameFinished() const
{
	return _answersCount == _totalAnswers;
}

void Game::closeGame()
{
	// TODO: submit stats to db
	GameManager::getInstance().deleteGame(_gameDetails.gameId);
}
