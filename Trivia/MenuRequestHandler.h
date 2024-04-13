#pragma once
#include "IRequestHandler.h"
#include "RequestHandlerFactory.h"

class RequestHandlerFactory;


class MenuRequestHandler : public IRequestHandler {
public:
	MenuRequestHandler(RequestHandlerFactory& handlerFactory);

	bool isRequestRelevant(const RequestInfo& req) override;
	RequestResult handleRequest(const RequestInfo& req) override;

private:
	RequestResult logout(const RequestInfo& req);
	RequestResult getRooms(const RequestInfo& req);
	RequestResult createRoom(const RequestInfo& req);
	RequestResult joinRoom(const RequestInfo& req);
	RequestResult getPlayersInRoom(const RequestInfo& req);
	RequestResult getPersonalStats(const RequestInfo& req);
	RequestResult getHighScore(const RequestInfo& req);

	using HandlerFunction = RequestResult(MenuRequestHandler::*)(const RequestInfo&);
	std::unordered_map<RequestCode, HandlerFunction> codeToFunction;
	RequestHandlerFactory & _handlerFactory;
};