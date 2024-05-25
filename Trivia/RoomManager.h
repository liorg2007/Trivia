#pragma once
#include <unordered_map>
#include "Room.h"
#include <shared_mutex>
#include <mutex>

class RoomManager {
public:
	static RoomManager& getInstance();

	unsigned int createRoom(const LoggedUser& user, RoomData&& roomData);
	void deleteRoom(int roomId);
	RoomState getRoomState(int roomId) const;
	std::vector<RoomData> getRooms() const;
	Room& getRoom(int roomId);

private:
	RoomManager() = default;
	std::unordered_map<int, Room> _rooms;
	mutable std::shared_mutex _mtx;

};