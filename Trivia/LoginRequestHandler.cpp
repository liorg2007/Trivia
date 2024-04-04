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
		result = login(req);
	else
		result = signup(req);

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
		result.newHandler = _handlerFactory.createMenuRequestHandler();
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
	LoginManager loginManager = _handlerFactory.getLoginManager();
	SignupRequest signupData = JsonRequestPacketDeserializer::deserializeSignupRequest(req.buffer);
	SignupResponse signupResponse;
	RequestResult result;

	if (loginManager.signup(signupData.username, signupData.password, signupData.email)) {
		signupResponse.status = SUCCESS;
		result.newHandler = _handlerFactory.createMenuRequestHandler();
	}
	else {
		signupResponse.status = FAILURE;
		result.newHandler = _handlerFactory.createLoginRequestHandler();//leave user in login handler
	}

	result.response = JsonRequestPacketSerializer::serializeResponse(signupResponse);

	return result;
}
