#include "RoomManager.h"

RoomManager::RoomManager()
{
}

RoomManager& RoomManager::getInstance()
{
	static RoomManager instance;
	return instance;
}

void RoomManager::createRoom(const LoggedUser& user, RoomData&& roomData)
{
	roomData.id = _rooms.size();
	_rooms.emplace(std::piecewise_construct, std::forward_as_tuple(roomData.id), std::forward_as_tuple(roomData, user));
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
	std::vector<RoomData> ans;

	for (const auto& room : _rooms)
		ans.push_back(room.second.getRoomData());

	return ans;
}

Room& RoomManager::getRoom(int roomId)
{
	return _rooms.at(roomId);
}
