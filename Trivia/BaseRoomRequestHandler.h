#pragma once
#include "IRequestHandler.h"
#include "LoggedUser.h"
#include "Room.h"
#include "RoomManager.h"

// Defined here in order to prevent linker errors
// src: https://gamedev.stackexchange.com/questions/162229/base-class-undefined
class RequestHandlerFactory;

class BaseRoomRequestHandler : public IRequestHandler
{
public:
	BaseRoomRequestHandler(int roomId, const LoggedUser& user);
	
	virtual bool isRequestRelevant(const RequestInfo& reqInfo) override = 0;
	virtual RequestResult handleRequest(const RequestInfo& reqInfo) override = 0;
	virtual void handleDisconnect() override = 0;

protected:
	RequestResult getRoomState() const;

	int _roomId;
	Room& _roomRef;
	LoggedUser _user;
	RoomManager& _roomManager;
	RequestHandlerFactory& _handlerFactory;
};
