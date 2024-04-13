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
	/*
	* Private functions to implement however we need:
	-  signout(RequestInfo): RequestResult
	-  getRooms(RequestInfo): RequestResult
	-  getPlayersInRoom(RequestInfo): RequestResult
	-  getPersonalStats(RequestInfo): RequestResult
	-  getHighScore(RequestInfo): RequestResult
	-  joinRoom(RequestInfo): RequestResult
	-  createRoom(RequestInfo): RequestResult
	*/

	static constexpr std::array<RequestCode, 6> VALID_CODES =
	{
		RequestCode::Logout,
		RequestCode::CreateRoom,
		RequestCode::JoinRoom,
		RequestCode::GetPlayersInRoom,
		RequestCode::GetRooms,
		RequestCode::GetStatistics,
	};
	RequestHandlerFactory & _handlerFactory;
};