#include "RoomAdminRequestHandler.h"
#include "JsonResponsePacketSerializer.h"
#include "RequestHandlerFactory.h"

bool RoomAdminRequestHandler::isRequestRelevant(const RequestInfo& reqInfo)
{
	return reqInfo.id == ProtocolCode::CloseRoom
		|| reqInfo.id == ProtocolCode::StartGame
		|| reqInfo.id == ProtocolCode::GetRoomState;
}

RequestResult RoomAdminRequestHandler::handleRequest(const RequestInfo& reqInfo)
{
	switch (reqInfo.id)
	{
	case ProtocolCode::CloseRoom:
		return closeRoom();
	case ProtocolCode::StartGame:
		return startGame();
	case ProtocolCode::GetRoomState:
	default:
		return getRoomState();
	}
}

void RoomAdminRequestHandler::handleDisconnect()
{
	_roomManager.deleteRoom(_roomId);
	_handlerFactory.getLoginManager().logout(_user.getUsername());
}

RequestResult RoomAdminRequestHandler::closeRoom()
{
	CloseRoomResponse res;
	RequestResult serializedRes;
	try
	{
		_roomManager.deleteRoom(_roomId);
		res.status = SUCCESS;
	}
	catch (...)
	{
		res.status = FAILURE;
	}

	serializedRes.response = JsonResponsePacketSerializer::serializeResponse(res);
	serializedRes.newHandler = _handlerFactory.createMenuRequestHandler(_user);
	return serializedRes;
}

RequestResult RoomAdminRequestHandler::startGame()
{
	StartGameResponse res;
	RequestResult serializedRes;
	try
	{
		res.startTime = getUTCGameStartTime();
		_roomRef.startGame(res.startTime);
		res.status = SUCCESS;
	}
	catch (const std::exception& ex)
	{
		res.startTime = 0;
		res.status = FAILURE;
	}

	serializedRes.response = JsonResponsePacketSerializer::serializeResponse(res);

	if (res.status == SUCCESS)
	{
		Game game = GameManager::getInstance().createGame(_roomRef);
		serializedRes.newHandler = _handlerFactory.createGameRequestHandler(_user, game);
	}
	else
		serializedRes.newHandler = nullptr;

	return serializedRes;
}

std::time_t RoomAdminRequestHandler::getUTCGameStartTime()
{
	return std::time(nullptr) + SECONDS_TO_GAME_START;
}
