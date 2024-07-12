#pragma once
#include "IRequestHandler.h"
#include "RequestHandlerFactory.h"
#include "Requests.h" 
#include "CheckSignupData.h"
#include <WinSock2.h>

class RequestHandlerFactory;

class LoginRequestHandler : public IRequestHandler {
public:
	LoginRequestHandler();

	bool isRequestRelevant(const RequestInfo& req) override;
	RequestResult handleRequest(const RequestInfo& req) override;
	void handleDisconnect() override;

private:
	RequestResult login(const RequestInfo& req);
	RequestResult signup(const RequestInfo& req);

	RequestHandlerFactory& _handlerFactory;
};