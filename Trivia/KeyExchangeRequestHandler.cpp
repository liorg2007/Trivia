#include "KeyExchangeRequestHandler.h"

KeyExchangeRequestHandler::KeyExchangeRequestHandler(std::shared_ptr<RSACryptoAlgorithm> rsaEncryption)
	:_rsaEncryption(rsaEncryption), _handlerFactory(RequestHandlerFactory::getInstance())
{
}

bool KeyExchangeRequestHandler::isRequestRelevant(const RequestInfo& reqInfo)
{
	return false;
}

RequestResult KeyExchangeRequestHandler::handleRequest(const RequestInfo& reqInfo)
{
	return RequestResult();
}

void KeyExchangeRequestHandler::handleDisconnect()
{
}
