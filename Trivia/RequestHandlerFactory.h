#pragma once
#include "LoginRequestHandler.h"
#include "IDatabase.h"
#include "LoginManager.h"

class RequestHandlerFactory
{
public:
	RequestHandlerFactory(IDatabase* database);

	LoginRequestHandler* createLoginRequestHandler() const;
	LoginManager& getLoginManager();

private:
	LoginManager _loginManager;
	IDatabase* _database;
};

