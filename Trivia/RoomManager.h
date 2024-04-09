#pragma once
#include <unordered_map>
#include "Room.h"

class RoomManager {
private:
	std::unordered_map<int, Room> _rooms;
	RoomManager();

public:
	static RoomManager& getInstance();

	void createRoom(const LoggedUser& user, const RoomData& roomData);
	void deleteRoom(int roomId);
	unsigned int getRoomState(int roomId) const;
	std::vector<RoomData> getRooms() const;
	Room& getRoom(int roomId) const;
};