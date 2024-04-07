#include "JsonRequestPacketDeserializer.h"
#include <iostream>
LoginRequest JsonRequestPacketDeserializer::deserializeLoginRequest(const Buffer& buff)
{
	json data = deserializeJsonObject(buff);
	LoginRequest request;

	request.username = std::move(data.at(USERNAME_HEADER));
	request.password = std::move(data.at(PASSWORD_HEADER));

	return request;
}

SignupRequest JsonRequestPacketDeserializer::deserializeSignupRequest(const Buffer& buff)
{
	json data = deserializeJsonObject(buff);
	SignupRequest request;

	request.username = std::move(data.at(USERNAME_HEADER));
	request.password = std::move(data.at(PASSWORD_HEADER));
	request.email = std::move(data.at(EMAIL_HEADER));
	request.address = std::move(data.at(ADDRESS_HEADER));
	request.phoneNumber = std::move(data.at(PHONE_NUMBER_HEADER));
	request.birthDate = std::move(data.at(BIRTH_DATE_HEADER));

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
