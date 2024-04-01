#include "JsonRequestPacketSerializer.h"

using json = nlohmann::json;

Buffer JsonRequestPacketSerializer::serializeResponse(ErrorResponse res)
{
    json jsonObj{ { "message", res.message } };
    
    auto msg = jsonObj.dump();
    int msgSize = msg.length();

    Buffer buff;
    buff.resize(msgSize + MESSAGE_HEADER_LENGTH); // another byte for a response code and message size)
    buff[0] = ErrorResponseCode;
    std::memcpy(&buff[1], &msgSize, 4);
    std::memcpy(&buff[5], msg.c_str(), msgSize);
    return buff;
}

Buffer JsonRequestPacketSerializer::serializeResponse(LoginResponse res)
{
    return Buffer();
}

Buffer JsonRequestPacketSerializer::serializeResponse(SignupResponse res)
{
    return Buffer();
}
