#pragma once

#include "IRequestHandler.h"
#include "RequestHandlerFactory.h"
#include "RSACryptoAlgorithm.h"
#include "Constants.h"

class ClientHelloRequestHandler : public IRequestHandler
{
public:
	ClientHelloRequestHandler();

	virtual bool isRequestRelevant(const RequestInfo& reqInfo) override;
	virtual RequestResult handleRequest(const RequestInfo& reqInfo) override;
	virtual void handleDisconnect() override;

private:
	std::shared_ptr<RSACryptoAlgorithm> _rsaEncryption;
	RequestHandlerFactory& _handlerFactory;
};