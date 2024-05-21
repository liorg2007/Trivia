#pragma once
#include "BaseRoomRequestHandler.h"
#include "RequestHandlerFactory.h"
#include <unordered_map>
#include <ctime>

class RoomAdminRequestHandler : public BaseRoomRequestHandler
{
public:
	using BaseRoomRequestHandler::BaseRoomRequestHandler;

	bool isRequestRelevant(const RequestInfo& reqInfo) override;
	RequestResult handleRequest(const RequestInfo& reqInfo) override;
	void handleDisconnect() override;
	
private:
	RequestResult closeRoom();
	RequestResult startGame();

	std::time_t getUTCGameStartTime();

	static constexpr auto SECONDS_TO_GAME_START = 7;
};