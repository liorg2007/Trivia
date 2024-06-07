#pragma once
#include "IRequestHandler.h"
#include "LoggedUser.h"
#include "RequestHandlerFactory.h"

class GameRequestHandler : public IRequestHandler
{
public:
	GameRequestHandler(const LoggedUser& user);

	virtual bool isRequestRelevant(const RequestInfo& reqInfo) override = 0;
	virtual RequestResult handleRequest(const RequestInfo& reqInfo) override = 0;
	virtual void handleDisconnect() override = 0;

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