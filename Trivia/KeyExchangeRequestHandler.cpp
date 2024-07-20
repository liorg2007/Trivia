#include "KeyExchangeRequestHandler.h"

KeyExchangeRequestHandler::KeyExchangeRequestHandler(std::shared_ptr<RSACryptoAlgorithm> rsaEncryption)
	:_rsaEncryption(rsaEncryption), _handlerFactory(RequestHandlerFactory::getInstance())
{
}

bool KeyExchangeRequestHandler::isRequestRelevant(const RequestInfo& reqInfo)
{
	return reqInfo.id == ProtocolCode::KeyExchange;
}

RequestResult KeyExchangeRequestHandler::handleRequest(const RequestInfo& reqInfo)
{
	RequestResult result;
	KeyExchangeResponse res;
	KeyAndIv keyAndIv;
	
	Buffer decryptedBuffer = _rsaEncryption->decrypt(reqInfo.buffer);

	try {
		auto data = JsonRequestPacketDeserializer::deserialzieKeyExchangeRequest(decryptedBuffer);
		res.status = SUCCESS;
		result.newHandler = _handlerFactory.createLoginRequestHandler();
	}
	catch (...)
	{
		res.status = FAILURE;
	}

	result.response = JsonResponsePacketSerializer::serializeResponse(res);

	return result;
}

void KeyExchangeRequestHandler::handleDisconnect()
{
}
