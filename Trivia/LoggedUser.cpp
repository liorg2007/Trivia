#include "LoggedUser.h"

LoggedUser::LoggedUser(const std::string& username)
	: _username(username)
{
}

std::string LoggedUser::getUsername() const
{
	return _username;
}
