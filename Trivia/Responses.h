#pragma once
#include <vector>
#include <string>
#include <utility>
#include "RoomData.h"

struct LoginResponse
{
	unsigned int status;
};

struct SignupResponse
{
	unsigned int status;
};

struct LogoutResponse
{
	unsigned int status;
};

struct ErrorResponse
{
	std::string message;
};

struct GetRoomsResponse
{
	unsigned int status;
	std::vector<RoomData> rooms;
};

struct GetPlayersInRoomResponse
{
	std::vector<std::string> players;
};

struct GetHighScoreResponse
{
	unsigned int status;
	std::vector<std::pair<std::string, int>> highScores;
};

struct GetPersonalStatsResponse
{
	unsigned int status;
	double averageAnswerTime;
	int correctAnswers;
	int totalAnswers;
	int score;
};

struct JoinRoomResponse
{
	unsigned int status;
};

struct CreateRoomResponse
{
	unsigned int status;
};
