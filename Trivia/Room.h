#pragma once
#include "RoomData.h"
#include "LoggedUser.h"
#include <vector>

class Room {
private:
	RoomData _RoomData;
	std::vector<LoggedUser> _users;

public:
	Room();

	void addUser(const LoggedUser& loggedUser);
	void removeUser(const LoggedUser& loggedUser);
	std::vector<std::string> getAllUsers() const;
};