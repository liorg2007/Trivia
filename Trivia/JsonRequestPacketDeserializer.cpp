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

	char* jsonString = new char[msgSize + 1];
	std::memcpy(jsonString, &buff[HEADER_FIELD_LENGTH], msgSize);
	jsonString[msgSize] = '\0';

	json data = json::parse(jsonString);
	delete[] jsonString;

	return data;
}
