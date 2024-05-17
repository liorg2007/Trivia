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
	std::lock_guard<std::mutex> lock(_mtx);
	unsigned int id = _rooms.size();
	_rooms.emplace(std::piecewise_construct, std::forward_as_tuple(id), std::forward_as_tuple(std::move(roomData), user));
}

void RoomManager::deleteRoom(int roomId)
{
	std::lock_guard<std::mutex> lock(_mtx);
	_rooms.erase(roomId);
}

unsigned int RoomManager::isRoomActive(int roomId) const
{
	return _rooms.at(roomId).getRoomData().isActive;
}

std::vector<RoomData> RoomManager::getRooms() const
{
	std::vector<RoomData> ans(_rooms.size());

	for (const auto& room : _rooms)
		ans.push_back(room.second.getRoomData());

	return ans;
}

Room& RoomManager::getRoom(int roomId)
{
	return _rooms.at(roomId);
}
