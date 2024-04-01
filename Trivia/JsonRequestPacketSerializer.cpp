#include "JsonRequestPacketSerializer.h"

using json = nlohmann::json;

Buffer JsonRequestPacketSerializer::serializeResponse(ErrorResponse res)
{
    json jsonObj;
    jsonObj["message"] = res.message;
    json.to_string(jsonObj);
}

Buffer JsonRequestPacketSerializer::serializeResponse(LoginResponse res)
{
    return Buffer();
}

Buffer JsonRequestPacketSerializer::serializeResponse(SignupResponse res)
{
    return Buffer();
}
