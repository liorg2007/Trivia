#pragma once
#include "Requests.h"

class IRequestHandler {
protected:
	virtual bool isRequestRelevant(const RequestInfo&) = 0;
	virtual RequestResult handleRequest(const RequestInfo&) = 0;
};