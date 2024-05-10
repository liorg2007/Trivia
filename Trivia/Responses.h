#pragma once
#include <vector>
#include <string>
#include <utility>
#include "RoomData.h"
#include "Constants.h"

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

struct GetHighScoresResponse
{
	unsigned int status;
	ScoreList highScores;
};

struct GetPersonalStatsResponse
{
	unsigned int status;
	UserStatistics statistics;
};

struct JoinRoomResponse
{
	unsigned int status;
};

struct CreateRoomResponse
{
	unsigned int status;
};

struct CloseRoomResponse
{
	unsigned int status;

};

struct StartGameResponse
{
	unsigned int status;
};

struct GetRoomStateResponse
{
	unsigned int status;
	bool hasGameBegun;
	std::list<std::string> players;
	unsigned int AnswerCount;
	int answerTimeOut;
};

struct LeaveRoomResponse
{
	unsigned int status;
};