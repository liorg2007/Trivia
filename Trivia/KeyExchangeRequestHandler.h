#pragma once

#include "IRequestHandler.h"
#include "RSACryptoAlgorithm.h"
#include "AESCryptoAlgorithm.h"
#include "RequestHandlerFactory.h"

class KeyExchangeRequestHandler : public IRequestHandler
{
public:
	KeyExchangeRequestHandler(std::shared_ptr<RSACryptoAlgorithm> rsaEncryption);

	virtual bool isRequestRelevant(const RequestInfo& reqInfo) override;
	virtual RequestResult handleRequest(const RequestInfo& reqInfo) override;
	virtual void handleDisconnect() override;

private:
	std::shared_ptr<RSACryptoAlgorithm> _rsaEncryption;
	RequestHandlerFactory& _handlerFactory;
};