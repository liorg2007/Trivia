#pragma once
#include <string>
#include <ctime>
#include "Constants.h"

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
};

struct RequestInfo
{
	MessageCode id;
	std::time_t receivalTIme;
	Buffer buffer;
};
