#pragma once
#include <string>
#include "json.hpp"

struct RoomData {
	unsigned int id;
	std::string name;
	unsigned int maxPlayers;
	unsigned int numOfQuestionsInGame;
	unsigned int timerPerQuestion;
	unsigned int isActive;
	// https://json.nlohmann.me/api/macros/nlohmann_define_type_intrusive/
	// in order for SerializeResponse to work
	NLOHMANN_DEFINE_TYPE_INTRUSIVE_ONLY_SERIALIZE(RoomData, id, name, maxPlayers, numOfQuestionsInGame, timerPerQuestion, isActive);
};


struct RoomState {
	bool hasGameBegun;
	std::vector<std::string> players;
	unsigned int numOfQuestionsInGame;
	unsigned int timerPerQuestion;
};
