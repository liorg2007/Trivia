#include "Room.h"


Room::Room(RoomData&& roomData, const LoggedUser& user)
	: _roomData(std::move(roomData))
{
	addUser(user);
}

const RoomData& Room::getRoomData() const
{
	return _roomData;
}

void Room::addUser(const LoggedUser& loggedUser)
{
	if (_roomData.maxPlayers == _users.size())
	{
		throw std::runtime_error("Max players amount reached");
	}
	_users.push_back(loggedUser);
}

void Room::removeUser(const LoggedUser& loggedUser)
{
	auto position = std::find(_users.begin(), _users.end(), loggedUser);

	if (position != _users.end())
		_users.erase(position);
}

const std::vector<LoggedUser>& Room::getAllUsers() const
{
	return _users;
}

std::vector<std::string> Room::getAllUsernames() const
{
	std::vector<std::string> ans;

	for (const auto& user : _users)
		ans.push_back(user.getUsername());

	return ans;
}
