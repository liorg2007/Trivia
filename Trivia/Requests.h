#pragma once
#include <string>
#include <ctime>
#include "Constants.h"
#include "IRequestHandler.h"

enum class RequestCode : Byte
{
	/* Login State */
	Login,
	Signup,

	/* Menu State*/
	Logout,
	CreateRoom,
	JoinRoom,
	GetRooms,
	GetPlayersInRoom,
	GetStatistics
};

struct RequestInfo
{
	RequestCode id;
	std::time_t receivalTime;
	Buffer buffer;
};

struct LoginRequest
{
	std::string username;
	std::string password;
};

struct SignupRequest
{
	std::string username;
	std::string password;
	std::string email;
	std::string address;
	std::string phoneNumber;
	std::string birthDate;
};

class IRequestHandler;
struct RequestResult
{
	Buffer response;
	IRequestHandler* newHandler = nullptr;
};

struct CreateRoomRequest
{
	std::string roomName;
	unsigned int maxUsers;
	unsigned int questionCount;
	unsigned int answerTimeout;
};

struct JoinRoomRequest
{
	unsigned int roomId;
};

struct GetPlayersInRoomRequest
{
	unsigned int roomId;
};
