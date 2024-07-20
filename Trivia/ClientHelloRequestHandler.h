#pragma once

#include "IRequestHandler.h"
#include "RequestHandlerFactory.h"
#include "RSACryptoAlgorithm.h"
#include "Constants.h"
		
#include <WinSock2.h>

class ClientHelloRequestHandler : public IRequestHandler
{
public:
	ClientHelloRequestHandler(SOCKET _clientSocket);

	virtual bool isRequestRelevant(const RequestInfo& reqInfo) override;
	virtual RequestResult handleRequest(const RequestInfo& reqInfo) override;
	virtual void handleDisconnect() override;

private:
	SOCKET _clientSocket;
	std::shared_ptr<RSACryptoAlgorithm> _rsaEncryption;
	RequestHandlerFactory& _handlerFactory;
};