#pragma once
#include "IRequestHandler.h"

class LoginRequestHandler : public IRequestHandler {
public:
	bool isRequestRelevant(const RequestInfo& req) override;
	RequestResult handleRequest(const RequestInfo& req) override;
};