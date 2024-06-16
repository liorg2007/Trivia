#include <string>
#include "Question.h"
#include "json.hpp"

#ifndef GAMEDATA_H
#define GAMEDATA_H

 struct PlayerResults {
	std::string username;
	unsigned int correctAnswerCount;
	unsigned int wrongAnswerCount;
	double averageAnswerTime;

	// https://json.nlohmann.me/api/macros/nlohmann_define_type_intrusive/
	// in order for SerializeResponse to work
	NLOHMANN_DEFINE_TYPE_INTRUSIVE_ONLY_SERIALIZE(PlayerResults, username, correctAnswerCount, wrongAnswerCount, averageAnswerTime);
} ;

struct GameData 
{
	Question& currentQuestion;
	std::time_t lastSubmission;
	unsigned int correctAnswerCount;
	unsigned int wrongAnswerCount;
	unsigned int averageAnswerTime;

	GameData(Question& _currentQuestion,
	std::time_t _lastSubmission,
	unsigned int _correctAnswerCount,
	unsigned int _wrongAnswerCount,
	unsigned int _averageAnswerTime) : currentQuestion(_currentQuestion), lastSubmission(_lastSubmission), 
		correctAnswerCount(_correctAnswerCount), wrongAnswerCount(_wrongAnswerCount),
		averageAnswerTime(_averageAnswerTime)
	{}
} ;

#endif