#include "LoginRequestHandler.h"
#include "JsonRequestPacketDeserializer.h"
#include "JsonRequestPacketSerializer.h"

bool LoginRequestHandler::isRequestRelevant(const RequestInfo& req)
{
	return req.id == MessageCode::LoginRequestCode;
}

RequestResult LoginRequestHandler::handleRequest(const RequestInfo& req)
{
	LoginRequest login = JsonRequestPacketDeserializer::deserializeLoginRequest(req.buffer);
	RequestResult reqResult;
	LoginResponse res;

	// check if username matches password according to the database
	if (true) 
	{
		res.status = 1;
	}
	else
	{
		res.status = 0;
	}
	reqResult.newHandler = new LoginRequestHandler(); // the next state, not LoginRequestHandler
	reqResult.response = JsonRequestPacketSerializer::serializeResponse(res);
	return reqResult;
}
