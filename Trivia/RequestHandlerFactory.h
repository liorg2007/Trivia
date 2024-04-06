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
	static RequestHandlerFactory& getInstance(IDatabase* database);

	LoginRequestHandler* createLoginRequestHandler();
	LoginManager& getLoginManager();

	MenuRequestHandler* createMenuRequestHandler();

	RequestHandlerFactory(RequestHandlerFactory&) = delete;
	void operator=(const RequestHandlerFactory&) = delete;
private:
	RequestHandlerFactory(IDatabase* database);
	LoginManager& _loginManager;
	IDatabase* _database;
};

