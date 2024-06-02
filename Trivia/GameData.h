#include <string>
#include "json.hpp"

struct PlayerResults {
	std::string Username;
	unsigned int CorrectAnswerCount;
	unsigned int WrongAnswerCount;
	double averageAnswerTime;

	// https://json.nlohmann.me/api/macros/nlohmann_define_type_intrusive/
	// in order for SerializeResponse to work
	NLOHMANN_DEFINE_TYPE_INTRUSIVE_ONLY_SERIALIZE(PlayerResults, Username, CorrectAnswerCount, WrongAnswerCount, averageAnswerTime);
};