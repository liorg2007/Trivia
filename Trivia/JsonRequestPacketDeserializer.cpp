#include "JsonRequestPacketDeserializer.h"
#include <iostream>
LoginRequest JsonRequestPacketDeserializer::deserializeLoginRequest(Buffer buff)
{
	json data = deserializeJsonObject(buff);
	LoginRequest request;

	request.username = data["username"];
	request.password = data["password"];

	return request;
}

SignupRequest JsonRequestPacketDeserializer::deserializeSignupRequest(Buffer buff)
{
	json data = deserializeJsonObject(buff);
	SignupRequest request;

	request.username = data["username"];
	request.password = data["password"];
	request.email = data["email"];

	return request;
}

json JsonRequestPacketDeserializer::deserializeJsonObject(Buffer buff)
{
	json data;
	int msgSize;

	std::memcpy(&msgSize, &buff[CODE_FIELD_LENGTH], SIZE_FIELD_LENGTH);
	char* jsonString = new char[msgSize + 1];

	std::memcpy(jsonString, &buff[HEADER_FIELD_LENGTH], msgSize);
	jsonString[msgSize] = '\0';
	data = json::parse(jsonString);
	delete[] jsonString;

	return data;
}
