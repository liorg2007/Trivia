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
	static RequestHandlerFactory& getInstance();

	LoginRequestHandler* createLoginRequestHandler();
	LoginManager& getLoginManager();

	MenuRequestHandler* createMenuRequestHandler();

	RequestHandlerFactory(RequestHandlerFactory&) = delete;
	void operator=(const RequestHandlerFactory&) = delete;
private:
	RequestHandlerFactory();
	LoginManager& _loginManager;
	IDatabase* _database;
};

