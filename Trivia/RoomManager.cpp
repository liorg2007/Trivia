#include "RoomManager.h"

RoomManager::RoomManager()
{
}

RoomManager& RoomManager::getInstance()
{
	static RoomManager instance;
	return instance;
}

void RoomManager::createRoom(const LoggedUser& user, const RoomData& roomData)
{
	_rooms.emplace(roomData.id, roomData, user);
}

void RoomManager::deleteRoom(int roomId)
{
	_rooms.erase(roomId);
}

unsigned int RoomManager::getRoomState(int roomId) const
{
	return _rooms.at(roomId).getRoomData().isActive;
}

std::vector<RoomData> RoomManager::getRooms() const
{
	std::vector<RoomData> rooms;

	for (const auto& room : _rooms)
		rooms.push_back(room.second.getRoomData());

	return rooms;
}

Room& RoomManager::getRoom(int roomId) const
{
	return (Room&)_rooms.at(roomId);
}
