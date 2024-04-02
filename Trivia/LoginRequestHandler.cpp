#include "LoginRequestHandler.h"
#include "JsonRequestPacketDeserializer.h"
#include "JsonRequestPacketSerializer.h"

bool LoginRequestHandler::isRequestRelevant(const RequestInfo& req)
{
    return req.id == MessageCode::LoginRequestCode;
}

RequestResult LoginRequestHandler::handleRequest(const RequestInfo& req)
{
}
