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
	
private:
	RequestResult closeRoom(const RequestInfo& reqInfo);
	RequestResult startGame(const RequestInfo& reqInfo);
	RequestResult getRoomState(const RequestInfo& reqInfo);

	using HandlerFunction = RequestResult(RoomAdminRequestHandler::*)(const RequestInfo&);
	static const std::unordered_map<ProtocolCode, HandlerFunction> codeToFunction;

	int _roomId;
	Room& _roomRef;
	LoggedUser _user;
	RoomManager& _roomManager;
	RequestHandlerFactory& _handlerFactory;

};