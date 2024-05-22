#pragma once
#include <memory>
#include "LoginRequestHandler.h"
#include "MenuRequestHandler.h"
#include "IDatabase.h"
#include "LoginManager.h"
#include "RoomManager.h"
#include "StatisticsManager.h"
#include "LoggedUser.h"
#include "RoomAdminRequestHandler.h"
#include "RoomMemberRequestHandler.h"

class LoginRequestHandler;
class MenuRequestHandler;
class RoomMemberRequestHandler;
class RoomAdminRequestHandler;

class RequestHandlerFactory
{
public:
	static RequestHandlerFactory& getInstance();

	std::unique_ptr<LoginRequestHandler> createLoginRequestHandler();

	std::unique_ptr<MenuRequestHandler> createMenuRequestHandler(const LoggedUser& user);

	std::unique_ptr<RoomAdminRequestHandler> createRoomAdminRequestHandler(int roomId, const LoggedUser& user);
	std::unique_ptr<RoomMemberRequestHandler> createRoomMemberRequestHandler(int roomId, const LoggedUser& user);

	std::unique_ptr<IRequestHandler> createGameRequestHandler();

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

