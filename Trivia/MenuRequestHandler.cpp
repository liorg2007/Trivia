#include "MenuRequestHandler.h"
#include <array>
#include <utility>

MenuRequestHandler::MenuRequestHandler(RequestHandlerFactory& handlerFactory)
	:_handlerFactory(handlerFactory)
{
}

bool MenuRequestHandler::isRequestRelevant(const RequestInfo& req)
{
	return std::find(VALID_CODES.begin(), VALID_CODES.end(), req.id) != VALID_CODES.end();
}

RequestResult MenuRequestHandler::handleRequest(const RequestInfo& req)
{
	return RequestResult();
}
