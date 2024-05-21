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
	GetRoomStateResponse roomStateRes;
	try
	{
		roomStateRes.roomState = _roomManager.getRoomState(_roomId);
	}
	catch (...)
	{
		// Exception: room not found, player needs to leave the room
		LeaveRoomResponse res;
		res.status = SUCCESS;
		return RequestResult {
			JsonResponsePacketSerializer::serializeResponse(res),
			_handlerFactory.createMenuRequestHandler(_user)
		};
	}

	if (roomStateRes.roomState.hasGameBegun == true)
	{
		// Tell the player the game started
		StartGameResponse res;
		res.status = SUCCESS;
		res.startTime = _roomRef.getRoomData().startTime;
		return RequestResult{
			JsonResponsePacketSerializer::serializeResponse(res),
			_handlerFactory.createGameRequestHandler()
		};
	}
	
	// Room hasn't started or closed, return a normal GetRoomStateResult
	roomStateRes.status = SUCCESS;
	return RequestResult { 
		JsonResponsePacketSerializer::serializeResponse(roomStateRes),
		nullptr 
	};
}
