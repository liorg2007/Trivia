#include "JsonRequestPacketSerializer.h"

Buffer JsonRequestPacketSerializer::serializeResponse(ErrorResponse res)
{
    json jsonObj{ { "message", res.message } };
    
    return buildBuffer(ErrorResponseCode, jsonObj);
}

Buffer JsonRequestPacketSerializer::serializeResponse(LoginResponse res)
{
    json jsonObj{ { "status", res.status } };

    return buildBuffer(LoginResponseCode, jsonObj);
}

Buffer JsonRequestPacketSerializer::serializeResponse(SignupResponse res)
{
    json jsonObj{ { "status", res.status } };

    return buildBuffer(SignupResponseCode, jsonObj);
}

Buffer JsonRequestPacketSerializer::buildBuffer(MessageCode resCode, const json& jsonObj)
{
    auto msg = jsonObj.dump();
    int msgSize = msg.length();

    Buffer buff(msgSize + HEADER_FIELD_LENGTH);

    buff[0] = resCode; // no need for memcpy for a size of 1
    std::memcpy(&buff[CODE_FIELD_LENGTH], &msgSize, SIZE_FIELD_LENGTH);
    std::memcpy(&buff[HEADER_FIELD_LENGTH], msg.c_str(), msgSize);
    return buff;
}
