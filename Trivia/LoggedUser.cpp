#include "LoggedUser.h"

LoggedUser::LoggedUser(const std::string& username, SOCKET socket)
	: _username(username), _socket(socket)
{
}

std::string LoggedUser::getUsername() const
{
	return _username;
}

SOCKET LoggedUser::getSocket() const
{
	return _socket;
}

bool LoggedUser::operator==(const LoggedUser& other) const
{
	return other.getUsername() == _username;
}

bool LoggedUser::operator==(const std::string& other) const
{
	return other == _username;
}