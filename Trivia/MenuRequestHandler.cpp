#include "MenuRequestHandler.h"
#include <array>
#include <utility>

MenuRequestHandler::MenuRequestHandler(RequestHandlerFactory& handlerFactory, const LoggedUser& user)
	: _handlerFactory(handlerFactory), _user(user),
	codeToFunction{ 
		{ RequestCode::Logout, &MenuRequestHandler::logout }, 
		{ RequestCode::CreateRoom, &MenuRequestHandler::createRoom },
		{ RequestCode::JoinRoom, &MenuRequestHandler::createRoom }, 
		{ RequestCode::GetPlayersInRoom, &MenuRequestHandler::getPlayersInRoom },
		{ RequestCode::GetRooms, &MenuRequestHandler::getRooms },
		{ RequestCode::GetPersonalStats, &MenuRequestHandler::getPersonalStats },
		{ RequestCode::GetHighScores, &MenuRequestHandler::getHighScore }
	 }
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
	_handlerFactory.getLoginManager().logout(_user.getUsername());
}

RequestResult MenuRequestHandler::getRooms(const RequestInfo& req)
{
	return RequestResult();
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
