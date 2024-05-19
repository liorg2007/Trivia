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
	_rooms.at(roomId).removeAllUsers();
	std::lock_guard<std::mutex> lock(_mtx);
	_rooms.erase(roomId);
}

RoomState RoomManager::getRoomState(int roomId) const
{
	RoomState roomState;
	const auto& ref = _rooms.at(roomId).getRoomData();
	roomState.hasGameBegun = ref.isActive;
	roomState.answerTimeout = ref.timerPerQuestion;
	roomState.answerCount = ref.numOfQuestionsInGame;
	roomState.players = _rooms.at(roomId).getAllUsers();
	return roomState;
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
