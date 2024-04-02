#pragma once
#include "Requests.h"

class IRequestHandler {
protected:
	virtual bool isRequestRelevant(const RequestInfo& reqInfo) = 0;
	virtual RequestResult handleRequest(const RequestInfo& reqInfo) = 0;
};