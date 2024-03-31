#pragma once
#include <string>

struct LoginResponse
{
	unsigned int status;
} LoginResponse;

struct SignupResponse
{
	unsigned int status;
};

struct ErrorResponse
{
	std::string message;
};
