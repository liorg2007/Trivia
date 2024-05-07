#pragma once
#include "IRequestHandler.h"
#include "RequestHandlerFactory.h"
#include "LoggedUser.h"
#include <unordered_map>

class RequestHandlerFactory;

class MenuRequestHandler : public IRequestHandler {
public:
	MenuRequestHandler(RequestHandlerFactory& handlerFactory, const LoggedUser& user);

	bool isRequestRelevant(const RequestInfo& req) override;
	RequestResult handleRequest(const RequestInfo& req) override;
	void handleDisconnect() override;

private:
	using HandlerFunction = RequestResult(MenuRequestHandler::*)(const RequestInfo&);
	RequestResult logout(const RequestInfo& req);
	RequestResult getRooms(const RequestInfo& req);
	RequestResult createRoom(const RequestInfo& req);
	RequestResult joinRoom(const RequestInfo& req);
	RequestResult getPlayersInRoom(const RequestInfo& req);
	RequestResult getPersonalStats(const RequestInfo& req);
	RequestResult getHighScore(const RequestInfo& req);

	static const std::unordered_map<ProtocolCode, HandlerFunction> codeToFunction;
	LoggedUser _user;
	RequestHandlerFactory & _handlerFactory;
};