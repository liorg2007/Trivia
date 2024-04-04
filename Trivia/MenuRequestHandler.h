#pragma once
#include "IRequestHandler.h"
#include "RequestHandlerFactory.h"

class RequestHandlerFactory;

class MenuRequestHandler : public IRequestHandler {
public:
	MenuRequestHandler(RequestHandlerFactory& handlerFactory);

	bool isRequestRelevant(const RequestInfo& req) override;
	RequestResult handleRequest(const RequestInfo& req) override;

private:
	RequestHandlerFactory& _handlerFactory;
};