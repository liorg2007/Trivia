#include "LoginRequestHandler.h"
#include "JsonRequestPacketDeserializer.h"
#include "JsonRequestPacketSerializer.h"

LoginRequestHandler::LoginRequestHandler(RequestHandlerFactory& handlerFactory)
	: _handlerFactory(handlerFactory)
{
}

bool LoginRequestHandler::isRequestRelevant(const RequestInfo& req)
{
	return req.id == MessageCode::LoginRequestCode
		|| req.id == MessageCode::SignupRequestCode;
}

RequestResult LoginRequestHandler::handleRequest(const RequestInfo& req)
{
	RequestResult result;
	if (req.id == MessageCode::LoginRequestCode)
	{
		LoginResponse loginRes;
		auto login = JsonRequestPacketDeserializer::deserializeLoginRequest(req.buffer);
		// LOGIN AND SET STATUS 1 IF SUCCESSFUL
		loginRes.status = 1;
		result.response = JsonRequestPacketSerializer::serializeResponse(loginRes);
	}
	else
	{
		SignupResponse signupRes;
		auto signup = JsonRequestPacketDeserializer::deserializeSignupRequest(req.buffer);
		// SIGNUP AND SET STATUS 1 IF SUCCESSFUL
		signupRes.status = 1;
		result.response = JsonRequestPacketSerializer::serializeResponse(signupRes);
	}
	result.newHandler = _handlerFactory.createLoginRequestHandler(); // the next state (menu), not LoginRequestHandler
	return result;
}

RequestResult LoginRequestHandler::login(const RequestInfo& req)
{
	/*auto login = JsonRequestPacketDeserializer::deserializeLoginRequest(req.buffer);
	RequestResult result;
	LoginResponse loginRes;
	_handlerFactory.getLoginManager().login(login.username, login.password);
	loginRes.status = _handlerFactory. // ???????? */
	return RequestResult();
}

RequestResult LoginRequestHandler::signup(const RequestInfo& req)
{
	return RequestResult();
}
