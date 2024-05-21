#include "RequestHandlerFactory.h"
#include "RoomAdminRequestHandler.h"
#include "RoomMemberRequestHandler.h"

RequestHandlerFactory::RequestHandlerFactory()
	: _database(IDatabase::getInstance()),
	_loginManager(LoginManager::getInstance()),
	_roomManager(RoomManager::getInstance()),
	_statisticsManager(StatisticsManager::getInstance())
{
}

RequestHandlerFactory& RequestHandlerFactory::getInstance()
{
	static RequestHandlerFactory instance;
	return instance;
}

LoginRequestHandler* RequestHandlerFactory::createLoginRequestHandler()
{
	return new LoginRequestHandler();
}

LoginManager& RequestHandlerFactory::getLoginManager()
{
	return _loginManager;
}

MenuRequestHandler* RequestHandlerFactory::createMenuRequestHandler(const LoggedUser& user)
{
	return new MenuRequestHandler(user);
}

RoomAdminRequestHandler* RequestHandlerFactory::createRoomAdminRequestHandler(int roomId, const LoggedUser& user)
{
	return new RoomAdminRequestHandler(roomId, user);
}

RoomMemberRequestHandler* RequestHandlerFactory::createRoomMemberRequestHandler(int roomId, const LoggedUser& user)
{
	return new RoomMemberRequestHandler(roomId, user);
}

IRequestHandler* RequestHandlerFactory::createGameRequestHandler()
{
	return nullptr;
}

StatisticsManager& RequestHandlerFactory::getStatisticsManager()
{
	return _statisticsManager;
}

RoomManager& RequestHandlerFactory::getRoomManager()
{
	return _roomManager;
}
