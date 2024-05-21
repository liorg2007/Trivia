#pragma once
#include "IRequestHandler.h"
#include "RoomManager.h"
#include "RequestHandlerFactory.h"

class RoomAdminRequestHandler : public IRequestHandler
{
public:
	RoomAdminRequestHandler(int roomId, const LoggedUser& user);

	bool isRequestRelevant(const RequestInfo& reqInfo) override;
	RequestResult handleRequest(const RequestInfo& reqInfo) override;
	void handleDisconnect() override;
	
private:
	RequestResult closeRoom();
	RequestResult startGame();
	RequestResult getRoomState();

	std::time_t getUTCGameStartTime();

	using HandlerFunction = RequestResult(RoomAdminRequestHandler::*)();
	static const std::unordered_map<ProtocolCode, HandlerFunction> codeToFunction;

	int _roomId;
	Room& _roomRef;
	LoggedUser _user;
	RoomManager& _roomManager;
	RequestHandlerFactory& _handlerFactory;

	static constexpr auto SECONDS_TO_GAME_START = 7;
};