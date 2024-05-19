#pragma once
#include "RoomData.h"
#include "LoggedUser.h"
#include <vector>

class Room {
private:
	RoomData _roomData;
	LoggedUser _adminUser;
	std::vector<LoggedUser> _users;

public:
	Room(RoomData&& roomData, const LoggedUser& roomAdmin);

	const RoomData& getRoomData() const;

	void addUser(const LoggedUser& loggedUser);
	void removeUser(const LoggedUser& loggedUser);

	void removeAllUsers();
	void startGame();

	std::vector<std::string> getAllUsers() const;
};