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

std::unique_ptr<IRequestHandler> RequestHandlerFactory::createLoginRequestHandler()
{
	return std::unique_ptr<IRequestHandler>(new LoginRequestHandler());
}

LoginManager& RequestHandlerFactory::getLoginManager()
{
	return _loginManager;
}

std::unique_ptr<IRequestHandler> RequestHandlerFactory::createMenuRequestHandler(const LoggedUser& user)
{
	return std::unique_ptr<IRequestHandler>(new MenuRequestHandler(user));
}

std::unique_ptr<IRequestHandler> RequestHandlerFactory::createRoomAdminRequestHandler(int roomId, const LoggedUser& user)
{
	return std::unique_ptr<IRequestHandler>(new RoomAdminRequestHandler(roomId, user));
}

std::unique_ptr<IRequestHandler> RequestHandlerFactory::createRoomMemberRequestHandler(int roomId, const LoggedUser& user)
{
	return std::unique_ptr<IRequestHandler>(new RoomMemberRequestHandler(roomId, user));
}

std::unique_ptr<IRequestHandler> RequestHandlerFactory::createGameRequestHandler()
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
