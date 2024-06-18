#pragma once
#include <optional>
#include "Question.h"
#include "LoggedUser.h"
#include "GameData.h"
#include "QuestionsRetriever.h"
#include <vector>
#include <unordered_map>

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
	bool submitAnswer(const LoggedUser& user, unsigned int answerId); //might not be the correct function
	void removePlayer(const LoggedUser& user); //might not be the correct function
	const GameDetails& getGameDetails() const;
	std::unordered_map<std::string, GameData>& getPlayersStats();

private:
	void submitGameStatsToDB();

	std::vector<Question> _questions;
	std::unordered_map<std::string, GameData> _players;
	GameDetails _gameDetails;
};