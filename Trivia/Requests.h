#pragma once
#include <string>
#include <ctime>
#include "Constants.h"
#include "IRequestHandler.h"
#include <memory>

struct RequestInfo
{
	ProtocolCode id;
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
	std::unique_ptr<IRequestHandler> newHandler;
};

struct CreateRoomRequest
{
	std::string roomName;
	unsigned int maxUsers;
	unsigned int answerCount;
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
