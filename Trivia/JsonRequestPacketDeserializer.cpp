#include "JsonRequestPacketDeserializer.h"
#include <iostream>
LoginRequest JsonRequestPacketDeserializer::deserializeLoginRequest(const Buffer& buff)
{
	json data = deserializeJsonObject(buff);
	LoginRequest request;

	request.username = std::move(data.at("username"));
	request.password = std::move(data.at("password"));

	return request;
}

SignupRequest JsonRequestPacketDeserializer::deserializeSignupRequest(const Buffer& buff)
{
	json data = deserializeJsonObject(buff);
	SignupRequest request;

	request.username = std::move(data.at("username"));
	request.password = std::move(data.at("password"));
	request.email = std::move(data.at("email"));
	request.address = std::move(data.at("address"));
	request.phoneNumber = std::move(data.at("phoneNumber"));
	request.birthDate = std::move(data.at("birthDate"));

	return request;
}

json JsonRequestPacketDeserializer::deserializeJsonObject(const Buffer& buff)
{
	int msgSize;
	std::memcpy(&msgSize, &buff[CODE_FIELD_LENGTH], SIZE_FIELD_LENGTH);
	if (msgSize > buff.size() - HEADER_FIELD_LENGTH)
	{
		throw std::exception("Recieved message size is longer than message");
	}
	return json::parse(std::string((char*)&buff.at(HEADER_FIELD_LENGTH), msgSize));
}
