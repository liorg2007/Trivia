#pragma once
#include "LoginRequestHandler.h"
#include "MenuRequestHandler.h"
#include "IDatabase.h"
#include "LoginManager.h"

class LoginRequestHandler;
class MenuRequestHandler;

class RequestHandlerFactory
{
public:
	RequestHandlerFactory(IDatabase* database);

	LoginRequestHandler* createLoginRequestHandler();
	LoginManager& getLoginManager();

	MenuRequestHandler* createMenuRequestHandler();

private:
	LoginManager _loginManager;
	IDatabase* _database;
};

