#include "RoomAdminRequestHandler.h"

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
	return RequestResult();
}

RequestResult RoomAdminRequestHandler::startGame(const RequestInfo& reqInfo)
{
	return RequestResult();
}

RequestResult RoomAdminRequestHandler::getRoomState(const RequestInfo& reqInfo)
{
	return RequestResult();
}
