#include "JsonRequestPacketSerializer.h"

Buffer JsonRequestPacketSerializer::serializeResponse(ErrorResponse res)
{
    return Buffer();
}

Buffer JsonRequestPacketSerializer::serializeResponse(LoginResponse res)
{
    return Buffer();
}

Buffer JsonRequestPacketSerializer::serializeResponse(SignupResponse res)
{
    return Buffer();
}
