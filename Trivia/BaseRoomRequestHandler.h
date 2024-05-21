#pragma once
#include "IRequestHandler.h"
#include "LoggedUser.h"
#include "RoomManager.h"
#include "RequestHandlerFactory.h"

class BaseRoomRequestHandler : public IRequestHandler
{
public:
	BaseRoomRequestHandler(int roomId, const LoggedUser& user);
	
protected:
	RequestResult getRoomState() const;

	int _roomId;
	Room& _roomRef;
	LoggedUser _user;
	RoomManager& _roomManager;
	RequestHandlerFactory& _handlerFactory;
};
