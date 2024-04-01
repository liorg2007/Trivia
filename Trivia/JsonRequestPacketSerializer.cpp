#include "JsonRequestPacketSerializer.h"
#include "MessageCode.h"

using json = nlohmann::json;

Buffer JsonRequestPacketSerializer::serializeResponse(ErrorResponse res)
{
    json jsonObj;
    
    jsonObj["message"] = res.message;
    auto msg = jsonObj.dump();
    Buffer buff(msg.size() + 5); // another byte for a response code and message size
    buff[0] = ErrorResponseCode;

}

Buffer JsonRequestPacketSerializer::serializeResponse(LoginResponse res)
{
    return Buffer();
}

Buffer JsonRequestPacketSerializer::serializeResponse(SignupResponse res)
{
    return Buffer();
}
