#pragma once
#include "IRequestHandler.h"
#include "LoggedUser.h"
#include "Game.h"
#include "GameManager.h"
#include "RequestHandlerFactory.h"
#include "Responses.h"
#include "JsonResponsePacketSerializer.h"

class GameRequestHandler : public IRequestHandler
{
public:
	GameRequestHandler(const LoggedUser& user, Game& game);

	virtual bool isRequestRelevant(const RequestInfo& reqInfo) override;
	virtual RequestResult handleRequest(const RequestInfo& reqInfo) override;
	virtual void handleDisconnect() override;

private:
	RequestResult getQuestion(const RequestInfo& reqInfo);
	RequestResult submitAnswer(const RequestInfo& reqInfo);
	RequestResult getGameResults(const RequestInfo& reqInfo);
	RequestResult leaveGame(const RequestInfo& reqInfo);

	Game& _game; 
	LoggedUser _user;
	GameManager& _gameManager; 
	RequestHandlerFactory& _handlerFactory;
};