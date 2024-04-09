#include "RoomManager.h"

RoomManager::RoomManager()
{
}

void RoomManager::createRoom(const LoggedUser& user, const RoomData& roomData)
{
}

void RoomManager::deleteRoom(int roomId)
{
}

unsigned int RoomManager::getRoomState(int roomId) const
{
	return 0;
}

std::vector<RoomData> RoomManager::getRooms() const
{
	return std::vector<RoomData>();
}

Room& RoomManager::getRoom(int roomId) const
{
	// TODO: insert return statement here
}
