#pragma once
#include "RoomData.h"
#include "LoggedUser.h"
#include <vector>

class Room {
private:
	RoomData _roomData;
	std::vector<LoggedUser> _users;

public:
	Room(const RoomData& roomData, const LoggedUser& user);

	void addUser(const LoggedUser& loggedUser);
	void removeUser(const LoggedUser& loggedUser);
	std::vector<std::string> getAllUsers() const;
};