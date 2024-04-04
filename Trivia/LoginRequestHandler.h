#pragma once
#include "IRequestHandler.h"
#include "RequestHandlerFactory.h"

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