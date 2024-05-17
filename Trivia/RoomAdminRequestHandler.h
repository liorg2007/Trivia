#pragma once
#include "IRequestHandler.h"
#include "RoomManager.h"
#include "RequestHandlerFactory.h"

class RoomAdminRequestHandler : public IRequestHandler
{
public:
	RoomAdminRequestHandler(const Room& room, const LoggedUser& user, RequestHandlerFactory& handlerFactory);

	bool isRequestRelevant(const RequestInfo& reqInfo) override;
	RequestResult handleRequest(const RequestInfo& reqInfo) override;
	
private:
	RequestResult closeRoom(const RequestInfo& reqInfo);
	RequestResult startGame(const RequestInfo& reqInfo);
	RequestResult isRoomActive(const RequestInfo& reqInfo);

	using HandlerFunction = RequestResult(RoomAdminRequestHandler::*)(const RequestInfo&);
	static const std::unordered_map<ProtocolCode, HandlerFunction> codeToFunction;
	Room _room;
	LoggedUser _user;
	RoomManager& _roomManager;
	RequestHandlerFactory& _handlerFactory;

};