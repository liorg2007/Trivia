#include "KeyExchangeRequestHandler.h"

KeyExchangeRequestHandler::KeyExchangeRequestHandler(std::shared_ptr<RSACryptoAlgorithm> rsaEncryption, SOCKET clientSocket)
	:_rsaEncryption(rsaEncryption), _handlerFactory(RequestHandlerFactory::getInstance()), _clientSocket(clientSocket)
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
		keyAndIv = JsonRequestPacketDeserializer::deserialzieKeyExchangeRequest(decryptedBuffer).keyAndIv;
		res.status = SUCCESS;
		result.newHandler = _handlerFactory.createLoginRequestHandler();
	}
	catch (...)
	{
		res.status = FAILURE;
	}

	result.response = JsonResponsePacketSerializer::serializeResponse(res);

	Communicator::getInstance().addEncryptionToClient(_clientSocket, keyAndIv);

	return result;
}

void KeyExchangeRequestHandler::handleDisconnect()
{
}
