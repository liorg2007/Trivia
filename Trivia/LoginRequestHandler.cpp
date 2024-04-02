#include "LoginRequestHandler.h"
#include "JsonRequestPacketDeserializer.h"
#include "JsonRequestPacketSerializer.h"

bool LoginRequestHandler::isRequestRelevant(const RequestInfo& req)
{
	return req.id == MessageCode::LoginRequestCode
		|| req.id == MessageCode::SignupRequestCode;
}

RequestResult LoginRequestHandler::handleRequest(const RequestInfo& req)
{
	RequestResult reqResult;
	LoginResponse res;
	res.status = 1;
	if (req.id == MessageCode::LoginRequestCode)
	{
		auto login = JsonRequestPacketDeserializer::deserializeLoginRequest(req.buffer);
		// LOGIN AND SET STATUS 1 IF SUCCESSFUL
	}
	else
	{
		auto signup = JsonRequestPacketDeserializer::deserializeSignupRequest(req.buffer);
		// SIGNUP AND SET STATUS 1 IF SUCCESSFUL
	}
	reqResult.newHandler = new LoginRequestHandler(); // the next state, not LoginRequestHandler
	reqResult.response = JsonRequestPacketSerializer::serializeResponse(res);
	return reqResult;
}
