#include "RoomAdminRequestHandler.h"
#include "JsonRequestPacketSerializer.h"

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
	return (this->*(it->second))(reqInfo);
}

RequestResult RoomAdminRequestHandler::closeRoom(const RequestInfo& reqInfo)
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

RequestResult RoomAdminRequestHandler::startGame(const RequestInfo& reqInfo)
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

RequestResult RoomAdminRequestHandler::getRoomState(const RequestInfo& reqInfo)
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
