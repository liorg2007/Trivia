#pragma once
#include "Question.h"
#include "LoggedUser.h"
#include "GameData.h"
#include <vector>
#include <unordered_map>

class Game
{
public:
	Game(unsigned int gameId);
	void getQuestionForUser(LoggedUser user);
	void submitAnswer(); //might not be the correct function
	void removePlayer(); //might not be the correct function

private:
	void submitGameStatsToDB(GameData);

	std::vector<Question> _questions;
	std::map<LoggedUser, GameData> _players;
	unsigned int _gameId;
};