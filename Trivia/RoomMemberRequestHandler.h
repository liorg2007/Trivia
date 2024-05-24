#pragma once
#include "BaseRoomRequestHandler.h"

class RoomMemberRequestHandler : public BaseRoomRequestHandler
{
public:
	using BaseRoomRequestHandler::BaseRoomRequestHandler;

	bool isRequestRelevant(const RequestInfo& reqInfo) override;
	RequestResult handleRequest(const RequestInfo& reqInfo) override;
	void handleDisconnect() override;

private:
	RequestResult leaveRoom();
};