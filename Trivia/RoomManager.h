#pragma once
#include <unordered_map>
#include "Room.h"
#include <mutex>

class RoomManager {
public:
	static RoomManager& getInstance();

	void createRoom(const LoggedUser& user, RoomData&& roomData);
	void deleteRoom(int roomId);
	unsigned int isRoomActive(int roomId) const;
	std::vector<RoomData> getRooms() const;
	Room& getRoom(int roomId);

private:
	RoomManager();
	std::unordered_map<int, Room> _rooms;
	std::mutex _mtx;

};