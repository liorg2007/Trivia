#pragma once

#include "IRequestHandler.h"
#include "RSACryptoAlgorithm.h"
#include "RequestHandlerFactory.h"

class KeyExchangeRequestHandler : IRequestHandler
{
public:
	KeyExchangeRequestHandler(std::unique_ptr<RSACryptoAlgorithm> rsaEncryption);

	virtual bool isRequestRelevant(const RequestInfo& reqInfo) override;
	virtual RequestResult handleRequest(const RequestInfo& reqInfo) override;
	virtual void handleDisconnect() override;

private:
	std::unique_ptr<RSACryptoAlgorithm> _rsaEncryption;
	RequestHandlerFactory& _handlerFactory;
};