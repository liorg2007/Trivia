#pragma once
#include <string>
#include <ctime>
#include "Constants.h"
#include "IRequestHandler.h"

class IRequestHandler;

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

struct RequestInfo
{
	MessageCode id;
	std::time_t receivalTime;
	Buffer buffer;
};

struct RequestResult
{
	Buffer response;
	IRequestHandler* newHandler = nullptr;
};
