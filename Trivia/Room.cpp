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
	std::shared_lock<std::shared_mutex> lock(_mtx);
	return _roomData;
}

void Room::addUser(const LoggedUser& loggedUser)
{
	std::unique_lock<std::shared_mutex> lock(_mtx);
	if (_roomData.maxPlayers == _users.size())
	{
		throw std::runtime_error("Max players amount reached");
	}
	_users.push_back(loggedUser);
}

void Room::removeUser(const LoggedUser& loggedUser)
{
	std::unique_lock<std::shared_mutex> lock(_mtx);
	const auto& position = std::find(_users.begin(), _users.end(), loggedUser);

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
	std::shared_lock<std::shared_mutex> lock(_mtx);
	std::vector<std::string> ans;

	for (const auto& user : _users)
		ans.push_back(user.getUsername());

	return ans;
}
