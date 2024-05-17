#include "RoomAdminRequestHandler.h"
#include "JsonRequestPacketSerializer.h"

const std::unordered_map<ProtocolCode, RoomAdminRequestHandler::HandlerFunction> RoomAdminRequestHandler::codeToFunction = {
		{ ProtocolCode::StartGame, &RoomAdminRequestHandler::startGame },
		{ ProtocolCode::GetRoomState, &RoomAdminRequestHandler::isRoomActive },
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
	_roomManager.deleteRoom(_roomId);
	// TODO: Send LeaveRoomResponse to all users in the room

	CloseRoomResponse res;
	RequestResult serializedRes;
	res.status = SUCCESS;

	serializedRes.response = JsonResponsePacketSerializer::serializeResponse(res);
	serializedRes.newHandler = _handlerFactory.createMenuRequestHandler(_user);
	return serializedRes;
}

RequestResult RoomAdminRequestHandler::startGame(const RequestInfo& reqInfo)
{
	// TODO: Send StartGameResponse to all users in the room

	StartGameResponse res;
	RequestResult serializedRes;
	res.status = SUCCESS;

	serializedRes.response = JsonResponsePacketSerializer::serializeResponse(res);
	serializedRes.newHandler = nullptr;
	return serializedRes;
}

RequestResult RoomAdminRequestHandler::isRoomActive(const RequestInfo& reqInfo)
{
	RequestResult serializedRes;
	GetRoomStateResponse res;

	res.roomState.numOfQuestionsInGame = _roomRef.getRoomData().numOfQuestionsInGame;
	res.roomState.timerPerQuestion = _roomRef.getRoomData().timerPerQuestion;
	res.roomState.players = _roomRef.getAllUsers();
	res.roomState.hasGameBegun = _roomRef.getRoomData().isActive;
	res.status = SUCCESS;

	serializedRes.response = JsonResponsePacketSerializer::serializeResponse(res);
	serializedRes.newHandler = nullptr;
	return serializedRes;
}
