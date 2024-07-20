#include "ClientHelloRequestHandler.h"

ClientHelloRequestHandler::ClientHelloRequestHandler()
	:_handlerFactory(RequestHandlerFactory::getInstance())
{
	_rsaEncryption = _handlerFactory.createRSAEncryption();
}

bool ClientHelloRequestHandler::isRequestRelevant(const RequestInfo& reqInfo)
{
	return false;
}

RequestResult ClientHelloRequestHandler::handleRequest(const RequestInfo& reqInfo)
{
	return RequestResult();
}

void ClientHelloRequestHandler::handleDisconnect()
{
}
