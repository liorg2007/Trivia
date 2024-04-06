#pragma once
#include "IRequestHandler.h"
#include "RequestHandlerFactory.h"
#include "CheckSignupData.h"

class RequestHandlerFactory;

class LoginRequestHandler : public IRequestHandler {
public:
	LoginRequestHandler(RequestHandlerFactory& handlerFactory);

	bool isRequestRelevant(const RequestInfo& req) override;
	RequestResult handleRequest(const RequestInfo& req) override;

private:
	RequestResult login(const RequestInfo& req);
	RequestResult signup(const RequestInfo& req);

	RequestHandlerFactory& _handlerFactory;
};