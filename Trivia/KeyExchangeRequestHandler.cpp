#include "KeyExchangeRequestHandler.h"

KeyExchangeRequestHandler::KeyExchangeRequestHandler(std::unique_ptr<RSACryptoAlgorithm> rsaEncryption)
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
