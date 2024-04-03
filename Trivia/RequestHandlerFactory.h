#pragma once
#include "LoginRequestHandler.h"
#include "IDatabase.h"

class RequestHandlerFactory
{
public:
	LoginRequestHandler* createLoginRequestHandler() const;
	LoginManager& getLoginManager() const;

private:
	LoginManager _loginManager;
	IDatabase* _database;
};

