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

		RequestResult result;
		result.response = JsonResponsePacketSerializer::serializeResponse(res);
		result.newHandler = std::shared_ptr<IRequestHandler>(_handlerFactory.createMenuRequestHandler(_user));
		return result;
	}

	if (roomStateRes.roomState.hasGameBegun == true)
	{
		// Tell the player the game started
		StartGameResponse res;
		res.status = SUCCESS;
		res.startTime = _roomRef.getRoomData().startTime;

		RequestResult result;
		result.response = JsonResponsePacketSerializer::serializeResponse(res);
		result.newHandler = std::shared_ptr<IRequestHandler>(_handlerFactory.createGameRequestHandler());
		return result;
	}
	
	// Room hasn't started or closed, return a normal GetRoomStateResult
	roomStateRes.status = SUCCESS;

	RequestResult result;
	result.response = JsonResponsePacketSerializer::serializeResponse(roomStateRes);
	result.newHandler = nullptr;
	return result;
}
