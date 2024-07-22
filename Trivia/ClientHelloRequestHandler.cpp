#include "ClientHelloRequestHandler.h"

ClientHelloRequestHandler::ClientHelloRequestHandler(SOCKET clientSocket)
	:_handlerFactory(RequestHandlerFactory::getInstance()), _clientSocket(clientSocket)
{
	_rsaEncryption = _handlerFactory.createRSAEncryption();
}

bool ClientHelloRequestHandler::isRequestRelevant(const RequestInfo& reqInfo)
{
	return reqInfo.id == ProtocolCode::ClientHello;
}

RequestResult ClientHelloRequestHandler::handleRequest(const RequestInfo& reqInfo)
{
	RequestResult result;
	ClientHelloResponse res;

	res.status = SUCCESS;
	res.publicKey = _rsaEncryption->getKey();

	result.response = JsonResponsePacketSerializer::serializeResponse(res);
	result.newHandler = _handlerFactory.createKeyExchangeRequestHandler(_rsaEncryption, _clientSocket);

	return result;
}

void ClientHelloRequestHandler::handleDisconnect()
{
}
