#pragma once
#include <string>
#include <vector>

typedef std::vector<unsigned char> Buffer;

struct LoginResponse
{
	unsigned int status;
};

struct SignupResponse
{
	unsigned int status;
};

struct ErrorResponse
{
	std::string message;
};
