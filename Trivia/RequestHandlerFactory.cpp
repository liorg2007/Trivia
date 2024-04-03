#include "RequestHandlerFactory.h"

RequestHandlerFactory::RequestHandlerFactory(IDatabase* database)
    : _database(database), _loginManager(database)
{
}

LoginRequestHandler* RequestHandlerFactory::createLoginRequestHandler() const
{
    LoginRequestHandler* reqHandler = new LoginRequestHandler();
    // do a bunch of stuff
    return reqHandler;
}

LoginManager& RequestHandlerFactory::getLoginManager()
{
    return _loginManager;
}
