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
#include "GameRequestHandler.h"

class LoginRequestHandler;
class MenuRequestHandler;
class RoomMemberRequestHandler;
class RoomAdminRequestHandler;
class GameRequestHandler;

class RequestHandlerFactory
{
public:
	static RequestHandlerFactory& getInstance();

	std::unique_ptr<LoginRequestHandler> createLoginRequestHandler();

	std::unique_ptr<MenuRequestHandler> createMenuRequestHandler(const LoggedUser& user);

	std::unique_ptr<RoomAdminRequestHandler> createRoomAdminRequestHandler(int roomId, const LoggedUser& user);
	std::unique_ptr<RoomMemberRequestHandler> createRoomMemberRequestHandler(int roomId, const LoggedUser& user);

	std::unique_ptr<GameRequestHandler> createGameRequestHandler(const LoggedUser& user, Game& game);

	LoginManager& getLoginManager();
	StatisticsManager& getStatisticsManager();
	RoomManager& getRoomManager();
	GameManager& getGameManager();

	RequestHandlerFactory(RequestHandlerFactory&) = delete;
	void operator=(const RequestHandlerFactory&) = delete;

private:
	RequestHandlerFactory();
	
	LoginManager& _loginManager;
	RoomManager& _roomManager;
	StatisticsManager& _statisticsManager;
	GameManager& _gameManager;

	IDatabase* _database;

};

