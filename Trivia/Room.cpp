#include "Room.h"
#include "Communicator.h"
#include "Responses.h"
#include "JsonRequestPacketSerializer.h"
#include <chrono>

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
}

void Room::startGame(std::time_t startTime)
{
	_roomData.isActive = true;

	StartGameResponse startGameRes;
	startGameRes.status = SUCCESS;
	startGameRes.startTime = startTime;

	RequestResult serializedRes;
	serializedRes.response = JsonResponsePacketSerializer::serializeResponse(startGameRes);
	for (const auto& user : _users)
	{
		// will be updated to createGameRequestHandler
		serializedRes.newHandler = RequestHandlerFactory::getInstance().createMenuRequestHandler(user);
		Communicator::getInstance().sendAndHandleRequestResult(serializedRes, user.getSocket());
	}
}

void Room::removeAllUsers()
{
	LeaveRoomResponse leaveRoomRes;
	leaveRoomRes.status = SUCCESS;
	RequestResult serializedRes;
	serializedRes.response = JsonResponsePacketSerializer::serializeResponse(leaveRoomRes);

	for (const auto& user : _users)
	{
		serializedRes.newHandler = RequestHandlerFactory::getInstance().createMenuRequestHandler(user);
		Communicator::getInstance().sendAndHandleRequestResult(serializedRes, user.getSocket());
	}
	_users.clear();
}

std::vector<std::string> Room::getAllUsers() const
{
	std::vector<std::string> ans;

	for (const auto& user : _users)
		ans.push_back(user.getUsername());

	return ans;
}
