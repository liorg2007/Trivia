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
	std::shared_ptr<Question> currentQuestion;
	std::time_t lastSubmission;
	unsigned int correctAnswerCount;
	unsigned int wrongAnswerCount;
	unsigned int averageAnswerTime;
} ;

#endif