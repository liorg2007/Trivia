#pragma once
#include "Question.h"
#include "LoggedUser.h"
#include "GameData.h"
#include "QuestionsRetriever.h"
#include <vector>
#include <unordered_map>

class Game
{
public:
	Game(std::vector<std::string> players, GameDetails gameDetails);
	Question& getQuestionForUser(const LoggedUser& user);
	void submitAnswer(const LoggedUser& user, unsigned int answerId); //might not be the correct function
	void removePlayer(); //might not be the correct function

private:
	void submitGameStatsToDB();

	std::vector<Question> _questions;
	std::map<LoggedUser, GameData> _players;
	GameDetails _gameDetails;
};

struct GameDetails
{
	unsigned int _gameId;
	unsigned int answerCount;
	unsigned int answerTimeout;
	std::time_t gameStartTime;
};