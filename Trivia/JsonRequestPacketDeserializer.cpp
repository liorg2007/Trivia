#include "JsonRequestPacketDeserializer.h"
#include <iostream>
LoginRequest JsonRequestPacketDeserializer::deserializeLoginRequest(const Buffer& buff)
{
	json data = deserializeJsonObject(buff);
	LoginRequest request;

	request.username = std::move(data["username"]);
	request.password = std::move(data["password"]);

	return request;
}

SignupRequest JsonRequestPacketDeserializer::deserializeSignupRequest(const Buffer& buff)
{
	json data = deserializeJsonObject(buff);
	SignupRequest request;

	request.username = std::move(data["username"]);
	request.password = std::move(data["password"]);
	request.email = std::move(data["email"]);
	request.address = std::move(data["address"]);
	request.phoneNumber = std::move(data["phoneNumber"]);
	request.birthDate = std::move(data["birthDate"]);

	return request;
}

json JsonRequestPacketDeserializer::deserializeJsonObject(const Buffer& buff)
{
	int msgSize;
	std::memcpy(&msgSize, &buff[CODE_FIELD_LENGTH], SIZE_FIELD_LENGTH);
	json data = json::parse(std::string((char*)&buff.at(HEADER_FIELD_LENGTH), msgSize));

	return data;
}
