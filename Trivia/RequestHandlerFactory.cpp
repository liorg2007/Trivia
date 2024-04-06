#include "RequestHandlerFactory.h"

RequestHandlerFactory::RequestHandlerFactory(IDatabase* database)
    : _database(database), _loginManager(LoginManager::getInstance(database))
{
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
