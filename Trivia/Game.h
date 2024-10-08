#pragma once
#include <optional>
#include "Question.h"
#include "LoggedUser.h"
#include "GameData.h"
#include "QuestionsRetriever.h"
#include <vector>
#include <unordered_map>
#include <shared_mutex>


struct GameDetails
{
	unsigned int gameId;
	unsigned int answerCount;
	unsigned int answerTimeout;
	std::time_t gameStartTime;
};

class Game
{
public:
	Game(std::vector<std::string>&& players, const GameDetails& gameDetails, std::vector<Question>&& questions);
	Question& getQuestionForUser(const LoggedUser& user);
	unsigned int submitAnswer(const LoggedUser& user, unsigned int answerId); //might not be the correct function
	void removePlayer(const LoggedUser& user); //might not be the correct function
	const GameDetails& getGameDetails() const;
	std::list<PlayerResults> getPlayersStats() const;
	bool isGameFinished() const;

private:
	void closeGame();

	int _answersCount;
	const int _totalAnswers;

	std::vector<Question> _questions;
	std::unordered_map<std::string, GameData> _players;
	GameDetails _gameDetails;
	mutable std::shared_mutex _mtx;
	int _leftPlayersCount;
};