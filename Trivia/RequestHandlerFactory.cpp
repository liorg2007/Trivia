#include "RequestHandlerFactory.h"

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
	return new LoginRequestHandler(*this);
}

LoginManager& RequestHandlerFactory::getLoginManager()
{
	return _loginManager;
}

MenuRequestHandler* RequestHandlerFactory::createMenuRequestHandler()
{
	return new MenuRequestHandler(*this);
}

StatisticsManager& RequestHandlerFactory::getStatisticsManager()
{
	return _statisticsManager;
}

RoomManager& RequestHandlerFactory::getRoomManager()
{
	return _roomManager;
}
