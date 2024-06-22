#include "Room.h"
#include "Communicator.h"
#include "Responses.h"
#include "JsonResponsePacketSerializer.h"

Room::Room(RoomData&& roomData, const LoggedUser& roomAdmin)
	: _roomData(std::move(roomData)), _adminUser(roomAdmin)
{
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

	if (_users.empty())
		RoomManager::getInstance().deleteRoom(_roomData.id);
}

void Room::startGame(std::time_t startTime)
{
	_roomData.isActive = true;
	_roomData.startTime = startTime;
}

std::vector<std::string> Room::getAllUsers() const
{
	std::vector<std::string> ans;

	for (const auto& user : _users)
		ans.push_back(user.getUsername());

	return ans;
}
