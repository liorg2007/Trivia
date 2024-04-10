#include "MenuRequestHandler.h"

MenuRequestHandler::MenuRequestHandler(RequestHandlerFactory& handlerFactory)
	:_handlerFactory(handlerFactory)
{
}

bool MenuRequestHandler::isRequestRelevant(const RequestInfo& req)
{
	return false;
}

RequestResult MenuRequestHandler::handleRequest(const RequestInfo& req)
{
	return RequestResult();
}
