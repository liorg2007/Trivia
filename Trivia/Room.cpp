#include "Room.h"

Room::Room()
{
}

void Room::addUser(const LoggedUser& loggedUser)
{
	_users.push_back(loggedUser);
}

void Room::removeUser(const LoggedUser& loggedUser)
{
	auto position = std::find(_users.begin(), _users.end(), loggedUser);

	if (position != _users.end())
		_users.erase(position);
}

std::vector<std::string> Room::getAllUsers() const
{
	return std::vector<std::string>();
}
