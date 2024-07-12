#pragma once
#include <exception>
#include <string>

class DatabaseException : public std::exception {
public:
	DatabaseException(const std::string& msg)
		: message(msg)
	{
	}

	// Override the what() method to return our message 
	const char* what() const throw()
	{
		return message.c_str();
	}

private:
	std::string message;
};