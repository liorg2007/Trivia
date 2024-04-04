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
		result = login(req);
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
	LoginManager loginManager = _handlerFactory.getLoginManager();
	LoginRequest loginData = JsonRequestPacketDeserializer::deserializeLoginRequest(req.buffer);
	LoginResponse loginResponse;
	RequestResult result;

	if (loginManager.login(loginData.username, loginData.password)) {
		loginResponse.status = SUCCESS;
		//TODO: _handlerFactory.createMenuRequestHandler
	}
	else {
		loginResponse.status = FAILURE;
		result.newHandler = _handlerFactory.createLoginRequestHandler();//leave user in login handler
	}

	result.response = JsonRequestPacketSerializer::serializeResponse(loginResponse);

	return result;
}

RequestResult LoginRequestHandler::signup(const RequestInfo& req)
{
	return RequestResult();
}
