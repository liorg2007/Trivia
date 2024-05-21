#include "BaseRoomRequestHandler.h"
#include "Responses.h"
#include "JsonResponsePacketSerializer.h"
#include "RequestHandlerFactory.h"

BaseRoomRequestHandler::BaseRoomRequestHandler(int roomId, const LoggedUser& user)
	: _roomId(roomId), _user(user), _roomManager(RoomManager::getInstance()), _handlerFactory(RequestHandlerFactory::getInstance()),
	_roomRef(_roomManager.getRoom(roomId))
{
}

RequestResult BaseRoomRequestHandler::getRoomState() const
{
	GetRoomStateResponse res;
	RequestResult serializedRes;
	try
	{
		res.roomState = _roomManager.getRoomState(_roomId);
		res.status = SUCCESS;
	}
	catch (...)
	{
		res.status = FAILURE;
	}

	serializedRes.response = JsonResponsePacketSerializer::serializeResponse(res);
	serializedRes.newHandler = nullptr;
	return serializedRes;
}
