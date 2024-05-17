#pragma once
#include "RoomData.h"
#include "LoggedUser.h"
#include <vector>

class Room {
private:
	RoomData _roomData;
	std::vector<LoggedUser> _users;

public:
	Room(RoomData&& roomData, const LoggedUser& user);

	const RoomData& getRoomData() const;

	void addUser(const LoggedUser& loggedUser);
	void removeUser(const LoggedUser& loggedUser);
	const std::vector<LoggedUser>& getAllUsers() const;
	std::vector<std::string> getAllUsernames() const;
};