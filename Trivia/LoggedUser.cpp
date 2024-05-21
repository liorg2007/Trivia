#include "LoggedUser.h"

LoggedUser::LoggedUser(const std::string& username)
	: _username(username)
{
}

std::string LoggedUser::getUsername() const
{
	return _username;
}

bool LoggedUser::operator==(const LoggedUser& other) const
{
	return other.getUsername() == _username;
}

bool LoggedUser::operator==(const std::string& other) const
{
	return other == _username;
}