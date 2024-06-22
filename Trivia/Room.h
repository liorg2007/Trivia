#pragma once
#include "RoomData.h"
#include "LoggedUser.h"
#include <vector>
#include <shared_mutex>

class Room {
private:
	RoomData _roomData;
	LoggedUser _adminUser;
	std::vector<LoggedUser> _users;
	mutable std::shared_mutex _mtx;

public:
	Room(RoomData&& roomData, const LoggedUser& roomAdmin);

	const RoomData& getRoomData() const;

	void addUser(const LoggedUser& loggedUser);
	void removeUser(const LoggedUser& loggedUser);

	void startGame(std::time_t startTime);

	std::vector<std::string> getAllUsers() const;
};