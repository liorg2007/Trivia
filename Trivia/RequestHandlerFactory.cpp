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

std::unique_ptr<LoginRequestHandler> RequestHandlerFactory::createLoginRequestHandler()
{
	return std::make_unique<LoginRequestHandler>();
}

LoginManager& RequestHandlerFactory::getLoginManager()
{
	return _loginManager;
}

std::unique_ptr<MenuRequestHandler> RequestHandlerFactory::createMenuRequestHandler(const LoggedUser& user)
{
	return std::make_unique<MenuRequestHandler>(user);
}

std::unique_ptr<RoomAdminRequestHandler> RequestHandlerFactory::createRoomAdminRequestHandler(int roomId, const LoggedUser& user)
{
	return std::make_unique<RoomAdminRequestHandler>(roomId, user);
}

std::unique_ptr<RoomMemberRequestHandler> RequestHandlerFactory::createRoomMemberRequestHandler(int roomId, const LoggedUser& user)
{
	return std::make_unique<RoomMemberRequestHandler>(roomId, user);
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
