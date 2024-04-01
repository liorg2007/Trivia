#include "JsonRequestPacketSerializer.h"

using json = nlohmann::json;

Buffer JsonRequestPacketSerializer::serializeResponse(ErrorResponse res)
{
    json jsonObj{ { "message", res.message } };
    
    auto msg = jsonObj.dump();
    int msgSize = msg.length();

    Buffer buff;
    buff.resize(msgSize + HEADER_FIELD_LENGTH); // another byte for a response code and message size)
    buff[0] = ErrorResponseCode; // no need for memcpy for a size of 1
    std::memcpy(&buff[CODE_FIELD_LENGTH], &msgSize, SIZE_FIELD_LENGTH);
    std::memcpy(&buff[HEADER_FIELD_LENGTH], msg.c_str(), msgSize);
    return buff;
}

Buffer JsonRequestPacketSerializer::serializeResponse(LoginResponse res)
{
    json jsonObj{ { "status", res.status } };

    auto msg = jsonObj.dump();
    int msgSize = msg.length();

    Buffer buff;
    buff.resize(msgSize + HEADER_FIELD_LENGTH); // another byte for a response code and message size)
    buff[0] = LoginResponseCode; // no need for memcpy for a size of 1
    std::memcpy(&buff[CODE_FIELD_LENGTH], &msgSize, SIZE_FIELD_LENGTH);
    std::memcpy(&buff[HEADER_FIELD_LENGTH], msg.c_str(), msgSize);
    return buff;
}

Buffer JsonRequestPacketSerializer::serializeResponse(SignupResponse res)
{
    json jsonObj{ { "status", res.status } };

    auto msg = jsonObj.dump();
    int msgSize = msg.length();

    Buffer buff;
    buff.resize(msgSize + HEADER_FIELD_LENGTH); // another byte for a response code and message size)
    buff[0] = SignupResponseCode; // no need for memcpy for a size of 1
    std::memcpy(&buff[CODE_FIELD_LENGTH], &msgSize, SIZE_FIELD_LENGTH);
    std::memcpy(&buff[HEADER_FIELD_LENGTH], msg.c_str(), msgSize);
    return buff;
}
