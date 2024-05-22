#include "RoomMemberRequestHandler.h"
#include "Responses.h"
#include "JsonResponsePacketSerializer.h"
#include "RequestHandlerFactory.h"

bool RoomMemberRequestHandler::isRequestRelevant(const RequestInfo& reqInfo)
{
	return reqInfo.id == ProtocolCode::LeaveRoom
		|| reqInfo.id == ProtocolCode::GetRoomState;
}

RequestResult RoomMemberRequestHandler::handleRequest(const RequestInfo& reqInfo)
{
	if (reqInfo.id == ProtocolCode::LeaveRoom)
	{
		return leaveRoom();
	}
	return getRoomState();
}

void RoomMemberRequestHandler::handleDisconnect()
{
	_roomRef.removeUser(_user);
	_handlerFactory.getLoginManager().logout(_user.getUsername());
}

RequestResult RoomMemberRequestHandler::leaveRoom()
{
	LeaveRoomResponse res;
	RequestResult serializedRes;

	try
	{
		_roomRef.removeUser(_user);
		res.status = SUCCESS;
	}
	catch (...) {} // either way will leave the room, no need to return FAILURE status
	serializedRes.response = JsonResponsePacketSerializer::serializeResponse(res);
	serializedRes.newHandler = std::shared_ptr<IRequestHandler>(_handlerFactory.createMenuRequestHandler(_user));
	return serializedRes;
}
