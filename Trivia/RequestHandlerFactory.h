#pragma once
#include "LoginRequestHandler.h"
#include "MenuRequestHandler.h"
#include "IDatabase.h"
#include "LoginManager.h"
#include "RoomManager.h"
#include "StatisticsManager.h"
#include "LoggedUser.h"
#include "RoomAdminRequestHandler.h"
#include "WinSock2.h"

class LoginRequestHandler;
class MenuRequestHandler;
class RoomAdminRequestHandler;

class RequestHandlerFactory
{
public:
	static RequestHandlerFactory& getInstance();

	LoginRequestHandler* createLoginRequestHandler(SOCKET socket);
	MenuRequestHandler* createMenuRequestHandler(const LoggedUser& user);
	RoomAdminRequestHandler* createRoomAdminRequestHandler(int roomId, const LoggedUser& user);

	LoginManager& getLoginManager();
	StatisticsManager& getStatisticsManager();
	RoomManager& getRoomManager();

	RequestHandlerFactory(RequestHandlerFactory&) = delete;
	void operator=(const RequestHandlerFactory&) = delete;

private:
	RequestHandlerFactory();
	
	LoginManager& _loginManager;
	RoomManager& _roomManager;
	StatisticsManager& _statisticsManager;

	IDatabase* _database;

};

