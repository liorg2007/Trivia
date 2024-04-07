#include "JsonRequestPacketSerializer.h"

Buffer JsonRequestPacketSerializer::serializeResponse(ErrorResponse res)
{
    json jsonObj{ { "message", res.message } };
    
    return buildBuffer(MessageCode::ErrorResponseCode, jsonObj);
}

Buffer JsonRequestPacketSerializer::serializeResponse(LoginResponse res)
{
    json jsonObj{ { "status", res.status } };

    return buildBuffer(MessageCode::LoginResponseCode, jsonObj);
}

Buffer JsonRequestPacketSerializer::serializeResponse(SignupResponse res)
{
    json jsonObj{ { "status", res.status } };

    return buildBuffer(MessageCode::SignupResponseCode, jsonObj);
}

Buffer JsonRequestPacketSerializer::buildBuffer(MessageCode resCode, const json& jsonObj)
{
    auto msg = jsonObj.dump();
    int msgSize = msg.length();

    Buffer buff(msgSize + HEADER_FIELD_LENGTH);

    buff.at(0) = (int)resCode; // no need for memcpy for a size of 1
    std::memcpy(&buff.at(CODE_FIELD_LENGTH), &msgSize, SIZE_FIELD_LENGTH);
    std::memcpy(&buff.at(HEADER_FIELD_LENGTH), msg.c_str(), msgSize);
    return buff;
}
