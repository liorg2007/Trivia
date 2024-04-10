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
    LoginRequestHandler* reqHandler = new LoginRequestHandler(*this);
    // do a bunch of stuff
    return reqHandler;
}

LoginManager& RequestHandlerFactory::getLoginManager()
{
  return _loginManager;
}

MenuRequestHandler* RequestHandlerFactory::createMenuRequestHandler()
{
  MenuRequestHandler* reqHandler = new MenuRequestHandler(*this);
  // do a bunch of stuff
  return reqHandler;
}

StatisticsManager& RequestHandlerFactory::getStatisticsManager()
{
    return _statisticsManager;
}

RoomManager& RequestHandlerFactory::getRoomManager()
{
    return _roomManager;
}
