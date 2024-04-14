#include "MenuRequestHandler.h"
#include "JsonRequestPacketSerializer.h"
#include "JsonRequestPacketDeserializer.h"

const std::unordered_map<RequestCode, MenuRequestHandler::HandlerFunction> MenuRequestHandler::codeToFunction = {
		{ RequestCode::Logout, &MenuRequestHandler::logout }, 
		{ RequestCode::CreateRoom, &MenuRequestHandler::createRoom },
		{ RequestCode::JoinRoom, &MenuRequestHandler::createRoom }, 
		{ RequestCode::GetPlayersInRoom, &MenuRequestHandler::getPlayersInRoom },
		{ RequestCode::GetRooms, &MenuRequestHandler::getRooms },
		{ RequestCode::GetPersonalStats, &MenuRequestHandler::getPersonalStats },
		{ RequestCode::GetHighScores, &MenuRequestHandler::getHighScore }
};

MenuRequestHandler::MenuRequestHandler(RequestHandlerFactory& handlerFactory, const LoggedUser& user)
	: _handlerFactory(handlerFactory), _user(user)
{
}

bool MenuRequestHandler::isRequestRelevant(const RequestInfo& req)
{
	return codeToFunction.find(req.id) != codeToFunction.end();
}

RequestResult MenuRequestHandler::handleRequest(const RequestInfo& req)
{
	auto it = codeToFunction.find(req.id);
	if (it != codeToFunction.end())
	{
		return (this->*(it->second))(req);
	}
}

RequestResult MenuRequestHandler::logout(const RequestInfo& req)
{
	RequestResult result;
	LogoutResponse response;
	if (_handlerFactory.getLoginManager().logout(_user.getUsername()))
	{
		response.status = SUCCESS;
	}
	else
	{
		// maybe throw an exception?
		response.status = FAILURE;
	}
	result.newHandler = _handlerFactory.createLoginRequestHandler();
	result.response = JsonRequestPacketSerializer::serializeResponse(response);
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
	result.response = JsonRequestPacketSerializer::serializeResponse(response);
	result.newHandler = this;
	return result;
}

RequestResult MenuRequestHandler::createRoom(const RequestInfo& req)
{
	return RequestResult();
}

RequestResult MenuRequestHandler::joinRoom(const RequestInfo& req)
{
	return RequestResult();
}

RequestResult MenuRequestHandler::getPlayersInRoom(const RequestInfo& req)
{
	return RequestResult();
}

RequestResult MenuRequestHandler::getPersonalStats(const RequestInfo& req)
{
	return RequestResult();
}

RequestResult MenuRequestHandler::getHighScore(const RequestInfo& req)
{
	return RequestResult();
}
