#include "RoomManager.h"

RoomManager::RoomManager()
{
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
	return std::vector<RoomData>();
}

Room& RoomManager::getRoom(int roomId) const
{
	// TODO: insert return statement here
}
