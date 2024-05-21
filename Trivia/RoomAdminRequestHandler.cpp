#include "RoomAdminRequestHandler.h"
#include "JsonResponsePacketSerializer.h"

const std::unordered_map<ProtocolCode, RoomAdminRequestHandler::HandlerFunction> RoomAdminRequestHandler::codeToFunction = {
		{ ProtocolCode::StartGame, &RoomAdminRequestHandler::startGame },
		{ ProtocolCode::GetRoomState, &RoomAdminRequestHandler::getRoomState },
		{ ProtocolCode::CloseRoom, &RoomAdminRequestHandler::closeRoom },
};

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
	catch (...)
	{
		res.startTime = 0;
		res.status = FAILURE;
	}

	serializedRes.response = JsonResponsePacketSerializer::serializeResponse(res);
	serializedRes.newHandler = nullptr;
	return serializedRes;
}

std::time_t RoomAdminRequestHandler::getUTCGameStartTime()
{
	std::time_t gameStartTime = std::time(nullptr) + SECONDS_TO_GAME_START;
	
	// Convert to UTC
	std::tm utcGameStartTime;
	if (gmtime_s(&utcGameStartTime, &gameStartTime) == 0)
	{
		throw std::exception("Can't get game start time");
	}
	// Convert to time_t
	return std::mktime(&utcGameStartTime);
}
