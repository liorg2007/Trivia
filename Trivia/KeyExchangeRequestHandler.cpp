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
	Buffer encryptedBuffer;

	int msgSize;
	std::memcpy(&msgSize, &reqInfo.buffer.at(CODE_FIELD_LENGTH), SIZE_FIELD_LENGTH);

	encryptedBuffer.resize(msgSize);

	encryptedBuffer = { reqInfo.buffer.begin() + HEADER_FIELD_LENGTH, reqInfo.buffer.end()};
	
	Buffer decryptedBuffer = _rsaEncryption->decrypt(encryptedBuffer);

	try {
		keyAndIv = JsonRequestPacketDeserializer::deserialzieKeyExchangeRequest(decryptedBuffer).keyAndIv;
		res.status = SUCCESS;
		result.newHandler = _handlerFactory.createLoginRequestHandler();
	}
	catch (std::exception e)
	{
		res.status = FAILURE;
		throw(e);
	}

	result.response = JsonResponsePacketSerializer::serializeResponse(res);

	Communicator::getInstance().addEncryptionToClient(_clientSocket, keyAndIv);

	return result;
}

void KeyExchangeRequestHandler::handleDisconnect()
{
}
