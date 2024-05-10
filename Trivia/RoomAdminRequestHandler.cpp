#include "RoomAdminRequestHandler.h"
#include "JsonRequestPacketSerializer.h"

const std::unordered_map<ProtocolCode, RoomAdminRequestHandler::HandlerFunction> RoomAdminRequestHandler::codeToFunction = {
		{ ProtocolCode::StartGame, &RoomAdminRequestHandler::startGame },
		{ ProtocolCode::GetRoomState, &RoomAdminRequestHandler::getRoomState },
		{ ProtocolCode::CloseRoom, &RoomAdminRequestHandler::closeRoom },
};

RoomAdminRequestHandler::RoomAdminRequestHandler(const Room& room, const LoggedUser& user, RoomManager& roomManager, RequestHandlerFactory& handlerFactory)
	: _room(room), _user(user), _roomManager(roomManager), _handlerFactory(handlerFactory)
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
	_roomManager.deleteRoom(_room.getRoomData().id);

	// TODO: Send LeaveRoomResponse to all users in the room

	CloseRoomResponse res;
	RequestResult serializedRes;
	res.status = SUCCESS;

	serializedRes.response = JsonRequestPacketSerializer::serializeResponse(res);
	serializedRes.newHandler = _handlerFactory.createMenuRequestHandler(_user);
	return serializedRes;
}

RequestResult RoomAdminRequestHandler::startGame(const RequestInfo& reqInfo)
{
	// TODO: Send StartGameResponse to all users in the room

	StartGameResponse res;
	RequestResult serializedRes;
	res.status = SUCCESS;

	serializedRes.response = JsonRequestPacketSerializer::serializeResponse(res);
	serializedRes.newHandler = nullptr;
	return serializedRes;
}

RequestResult RoomAdminRequestHandler::getRoomState(const RequestInfo& reqInfo)
{
	GetRoomStateResponse res;
	RequestResult serializedRes;
	res.roomState.answerCount = _room.getRoomData().numOfQuestionsInGame;
	res.roomState.answerTimeOut = _room.getRoomData().timerPerQuestion;
	res.roomState.players = _room.getAllUsers();
	res.roomState.hasGameBegun = _room.getRoomData().isActive;
	res.status = SUCCESS;

	serializedRes.response = JsonRequestPacketSerializer::serializeResponse(res);
	serializedRes.newHandler = nullptr;
	return serializedRes;
}
