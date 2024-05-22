#include "LoginRequestHandler.h"
#include "JsonRequestPacketDeserializer.h"
#include "JsonResponsePacketSerializer.h"

LoginRequestHandler::LoginRequestHandler()
	: _handlerFactory(RequestHandlerFactory::getInstance())
{
}

bool LoginRequestHandler::isRequestRelevant(const RequestInfo& req)
{
	return req.id == ProtocolCode::Login
		|| req.id == ProtocolCode::Signup;
}

RequestResult LoginRequestHandler::handleRequest(const RequestInfo& req)
{
	RequestResult result;
	if (req.id == ProtocolCode::Login)
		result = login(req);
	else
		result = signup(req);

	return result;
}

void LoginRequestHandler::handleDisconnect()
{
}

RequestResult LoginRequestHandler::login(const RequestInfo& req)
{
	LoginManager& loginManager = _handlerFactory.getLoginManager();
	LoginRequest loginData = JsonRequestPacketDeserializer::deserializeLoginRequest(req.buffer);
	LoginResponse loginResponse;
	RequestResult result;

	if (loginManager.login(loginData.username, loginData.password)) {
		loginResponse.status = SUCCESS;
		result.newHandler = std::move(_handlerFactory.createMenuRequestHandler(loginData.username));
	}
	else {
		loginResponse.status = FAILURE;
		result.newHandler = nullptr;
	}

	result.response = JsonResponsePacketSerializer::serializeResponse(loginResponse);

	return result;
}

RequestResult LoginRequestHandler::signup(const RequestInfo& req)
{
	LoginManager& loginManager = _handlerFactory.getLoginManager();
	SignupRequest signupData = JsonRequestPacketDeserializer::deserializeSignupRequest(req.buffer);
	SignupResponse signupResponse;
	RequestResult result;
	bool isDataValid;

	isDataValid = CheckSignupData::CheckData(signupData);

	if (isDataValid && loginManager.signup(signupData.username, signupData.password, signupData.email, signupData.address, signupData.phoneNumber, signupData.birthDate)) {
		signupResponse.status = SUCCESS;
		result.newHandler = std::move(_handlerFactory.createMenuRequestHandler(signupData.username));
	}
	else {
		signupResponse.status = FAILURE;
		result.newHandler = nullptr;
	}

	result.response = JsonResponsePacketSerializer::serializeResponse(signupResponse);

	return result;
}
