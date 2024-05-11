#pragma once
#include <vector>
#include <string>
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
	std::time_t startTime;
};

struct GetRoomStateResponse
{
	unsigned int status;
	RoomState roomState;
};

struct LeaveRoomResponse
{
	unsigned int status;
};
