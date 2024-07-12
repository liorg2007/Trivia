#include "RequestHandlerFactory.h"
#include "RoomAdminRequestHandler.h"
#include "RoomMemberRequestHandler.h"

RequestHandlerFactory::RequestHandlerFactory()
	: _database(IDatabase::getInstance()),
	_loginManager(LoginManager::getInstance()),
	_roomManager(RoomManager::getInstance()),
	_statisticsManager(StatisticsManager::getInstance()),
	_gameManager(GameManager::getInstance())
{
}

RequestHandlerFactory& RequestHandlerFactory::getInstance()
{
	static RequestHandlerFactory instance;
	return instance;
}

std::unique_ptr<LoginRequestHandler> RequestHandlerFactory::createLoginRequestHandler()
{
	return std::make_unique<LoginRequestHandler>();
}

LoginManager& RequestHandlerFactory::getLoginManager()
{
	return _loginManager;
}

std::unique_ptr<MenuRequestHandler> RequestHandlerFactory::createMenuRequestHandler(const LoggedUser& user)
{
	return std::make_unique<MenuRequestHandler>(user);
}

std::unique_ptr<RoomAdminRequestHandler> RequestHandlerFactory::createRoomAdminRequestHandler(int roomId, const LoggedUser& user)
{
	return std::make_unique<RoomAdminRequestHandler>(roomId, user);
}

std::unique_ptr<RoomMemberRequestHandler> RequestHandlerFactory::createRoomMemberRequestHandler(int roomId, const LoggedUser& user)
{
	return std::make_unique<RoomMemberRequestHandler>(roomId, user);
}

std::unique_ptr<GameRequestHandler> RequestHandlerFactory::createGameRequestHandler(const LoggedUser& user, Game& game)
{
	return std::make_unique<GameRequestHandler>(user, game);
}

StatisticsManager& RequestHandlerFactory::getStatisticsManager()
{
	return _statisticsManager;
}

RoomManager& RequestHandlerFactory::getRoomManager()
{
	return _roomManager;
}

GameManager& RequestHandlerFactory::getGameManager()
{
	return _gameManager;
}
