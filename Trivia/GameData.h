#pragma once
#include <string>
#include "Question.h"
#include "json.hpp"

struct PlayerResults {
	std::string username;
	unsigned int correctAnswerCount;
	unsigned int wrongAnswerCount;
	double averageAnswerTime;
	bool finishedGame;

	// https://json.nlohmann.me/api/macros/nlohmann_define_type_intrusive/
	// in order for SerializeResponse to work
	NLOHMANN_DEFINE_TYPE_INTRUSIVE_ONLY_SERIALIZE(PlayerResults, username, correctAnswerCount, wrongAnswerCount, averageAnswerTime);
};

struct GameData
{
	int currentQuestionIndex;
	std::time_t currQuestionStartTime;
	unsigned int correctAnswerCount;
	unsigned int wrongAnswerCount;
	unsigned int averageAnswerTime;
	bool hasLeftGame;

	GameData(int _currentQuestionIndex,
		std::time_t _lastSubmission,
		unsigned int _correctAnswerCount,
		unsigned int _wrongAnswerCount,
		unsigned int _averageAnswerTime) : currentQuestionIndex(_currentQuestionIndex), currQuestionStartTime(_lastSubmission),
		correctAnswerCount(_correctAnswerCount), wrongAnswerCount(_wrongAnswerCount),
		averageAnswerTime(_averageAnswerTime), hasLeftGame(false)
	{}
};
