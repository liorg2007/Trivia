#include "LoginRequestHandler.h"
#include "JsonRequestPacketDeserializer.h"
#include "JsonResponsePacketSerializer.h"

LoginRequestHandler::LoginRequestHandler(SOCKET userSocket)
	: _handlerFactory(RequestHandlerFactory::getInstance()), _userSocket(userSocket)
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

	if (loginManager.login(_userSocket, loginData.username, loginData.password)) {
		loginResponse.status = SUCCESS;
		result.newHandler = _handlerFactory.createMenuRequestHandler(LoggedUser(loginData.username, _userSocket));
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

	if (isDataValid && loginManager.signup(_userSocket, signupData.username, signupData.password, signupData.email, signupData.address, signupData.phoneNumber, signupData.birthDate)) {
		signupResponse.status = SUCCESS;
		result.newHandler = _handlerFactory.createMenuRequestHandler(LoggedUser(signupData.username, _userSocket));
	}
	else {
		signupResponse.status = FAILURE;
		result.newHandler = nullptr;
	}

	result.response = JsonResponsePacketSerializer::serializeResponse(signupResponse);

	return result;
}
