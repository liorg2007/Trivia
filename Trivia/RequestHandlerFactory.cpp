#include "RequestHandlerFactory.h"

RequestHandlerFactory::RequestHandlerFactory(IDatabase* database)
    : _database(database), _loginManager(database)
{
}

LoginRequestHandler* RequestHandlerFactory::createLoginRequestHandler() const
{
    return nullptr;
}

LoginManager& RequestHandlerFactory::getLoginManager()
{
    return _loginManager;
}
