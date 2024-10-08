#include "MenuRequestHandler.h"
#include "JsonResponsePacketSerializer.h"
#include "JsonRequestPacketDeserializer.h"

const std::unordered_map<ProtocolCode, MenuRequestHandler::HandlerFunction> MenuRequestHandler::codeToFunction = {
		{ ProtocolCode::Logout, &MenuRequestHandler::logout },
		{ ProtocolCode::CreateRoom, &MenuRequestHandler::createRoom },
		{ ProtocolCode::JoinRoom, &MenuRequestHandler::joinRoom },
		{ ProtocolCode::GetPlayersInRoom, &MenuRequestHandler::getPlayersInRoom },
		{ ProtocolCode::GetRooms, &MenuRequestHandler::getRooms },
		{ ProtocolCode::GetPersonalStats, &MenuRequestHandler::getPersonalStats },
		{ ProtocolCode::GetHighScores, &MenuRequestHandler::getHighScore }
};

MenuRequestHandler::MenuRequestHandler(const LoggedUser& user)
	: _handlerFactory(RequestHandlerFactory::getInstance()), _user(user)
{
}

bool MenuRequestHandler::isRequestRelevant(const RequestInfo& req)
{
	return codeToFunction.find(req.id) != codeToFunction.end();
}

RequestResult MenuRequestHandler::handleRequest(const RequestInfo& req)
{
	const auto& it = codeToFunction.find(req.id);
	return (this->*(it->second))(req);
}

void MenuRequestHandler::handleDisconnect()
{
	_handlerFactory.getLoginManager().logout(_user.getUsername());
}

RequestResult MenuRequestHandler::logout(const RequestInfo& req)
{
	RequestResult result;
	LogoutResponse response;
	if (_handlerFactory.getLoginManager().logout(_user.getUsername()))
		response.status = SUCCESS;
	else
		throw(std::exception("Cannot logout non-existing user"));

	result.newHandler = _handlerFactory.createLoginRequestHandler();
	result.response = JsonResponsePacketSerializer::serializeResponse(response);
	return result;
}

RequestResult MenuRequestHandler::getRooms(const RequestInfo& req)
{
	RequestResult result;
	GetRoomsResponse response;
	try
	{
		response.rooms = _handlerFactory.getRoomManager().getRooms();
		response.status = SUCCESS;
	}
	catch (...)
	{
		response.status = FAILURE;
	}
	result.response = JsonResponsePacketSerializer::serializeResponse(response);
	result.newHandler = nullptr;
	return result;
}

RequestResult MenuRequestHandler::createRoom(const RequestInfo& req)
{
	int roomId;
	RequestResult result;
	CreateRoomRequest request = JsonRequestPacketDeserializer::deserializeCreateRoomRequest(req.buffer);
	CreateRoomResponse response;
	RoomData newRoomData(
		0, // will be set in RoomManager's createRoom
		request.roomName,
		request.maxUsers,
		request.answerCount,
		request.answerTimeout,
		static_cast<unsigned int>(INACTIVE_ROOM),
		0);

	try
	{
		roomId = _handlerFactory.getRoomManager().createRoom(_user, std::move(newRoomData));
		response.status = SUCCESS;
	}
	catch (...)
	{
		response.status = FAILURE;
	}
	result.response = JsonResponsePacketSerializer::serializeResponse(response);
	result.newHandler = _handlerFactory.createRoomAdminRequestHandler(roomId, _user);
	return result;
}

RequestResult MenuRequestHandler::joinRoom(const RequestInfo& req)
{
	JoinRoomRequest request = JsonRequestPacketDeserializer::deserializeJoinRoomRequest(req.buffer);
	JoinRoomResponse response;
	RequestResult result;
	try
	{
		_handlerFactory.getRoomManager().getRoom(request.roomId).addUser(_user);
		response.status = SUCCESS;
	}
	catch (...)
	{
		response.status = FAILURE;
	}
	result.response = JsonResponsePacketSerializer::serializeResponse(response);
	result.newHandler = _handlerFactory.createRoomMemberRequestHandler(request.roomId, _user);
	return result;
}

RequestResult MenuRequestHandler::getPlayersInRoom(const RequestInfo& req)
{
	GetPlayersInRoomRequest request = JsonRequestPacketDeserializer::deserializeGetPlayersRequest(req.buffer);
	GetPlayersInRoomResponse response;
	RequestResult result;
	response.players = _handlerFactory.getRoomManager().getRoom(request.roomId).getAllUsers();
	result.response = JsonResponsePacketSerializer::serializeResponse(response);
	result.newHandler = nullptr;
	return result;
}

RequestResult MenuRequestHandler::getPersonalStats(const RequestInfo& req)
{
	GetPersonalStatsResponse response;
	RequestResult result;
	response.statistics = _handlerFactory.getStatisticsManager().getUserStatistics(_user.getUsername());
	result.response = JsonResponsePacketSerializer::serializeResponse(response);
	result.newHandler = nullptr;
	return result;
}

RequestResult MenuRequestHandler::getHighScore(const RequestInfo& req)
{
	GetHighScoresResponse response;
	RequestResult result;
	response.highScores = _handlerFactory.getStatisticsManager().getHighScores();
	result.response = JsonResponsePacketSerializer::serializeResponse(response);
	result.newHandler = nullptr;
	return result;
}
