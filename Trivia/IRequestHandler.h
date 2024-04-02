#pragma once
#include "Requests.h"

class IRequestHandler {
public:
	virtual bool isRequestRelevant(const RequestInfo&) = 0;
	virtual RequestResult handleRequest(const RequestInfo&) = 0;
};