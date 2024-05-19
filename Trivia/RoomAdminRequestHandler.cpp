#include "RoomAdminRequestHandler.h"
#include "JsonResponsePacketSerializer.h"

const std::unordered_map<ProtocolCode, RoomAdminRequestHandler::HandlerFunction> RoomAdminRequestHandler::codeToFunction = {
		{ ProtocolCode::StartGame, &RoomAdminRequestHandler::startGame },
		{ ProtocolCode::GetRoomState, &RoomAdminRequestHandler::getRoomState },
		{ ProtocolCode::CloseRoom, &RoomAdminRequestHandler::closeRoom },
};

RoomAdminRequestHandler::RoomAdminRequestHandler(int roomId, const LoggedUser& user)
	: _roomId(roomId), _user(user), _roomManager(RoomManager::getInstance()), _handlerFactory(RequestHandlerFactory::getInstance()),
	_roomRef(_roomManager.getRoom(roomId))
{
}

bool RoomAdminRequestHandler::isRequestRelevant(const RequestInfo& reqInfo)
{
	return codeToFunction.find(reqInfo.id) != codeToFunction.end();
}

RequestResult RoomAdminRequestHandler::handleRequest(const RequestInfo& reqInfo)
{
	auto it = codeToFunction.find(reqInfo.id);
	return (this->*(it->second))();
}

void RoomAdminRequestHandler::handleDisconnect()
{
	closeRoom();
	// Logout the user
	MenuRequestHandler(_user).handleDisconnect();
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
		_roomRef.startGame();
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

RequestResult RoomAdminRequestHandler::getRoomState()
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
