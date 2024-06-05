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

GetPlayersInRoomRequest JsonRequestPacketDeserializer::deserializeGetPlayersRequest(const Buffer& buff)
{
	json data = deserializeJsonObject(buff);
	GetPlayersInRoomRequest request;
	request.roomId = std::move(data.at(ROOMID_HEADER));
	return request;
}

JoinRoomRequest JsonRequestPacketDeserializer::deserializeJoinRoomRequest(const Buffer& buff)
{
	json data = deserializeJsonObject(buff);
	JoinRoomRequest request;
	request.roomId = std::move(data.at(ROOMID_HEADER));
	return request;
}

CreateRoomRequest JsonRequestPacketDeserializer::deserializeCreateRoomRequest(const Buffer& buff)
{
	json data = deserializeJsonObject(buff);
	CreateRoomRequest request;
	request.roomName = std::move(data.at(ROOM_NAME_HEADER));
	request.maxUsers = std::move(data.at(MAX_USERS_HEADER));
	request.answerCount = std::move(data.at(QUESTION_COUNT_HEADER));
	request.answerTimeout = std::move(data.at(ANSWER_TIMEOUT_HEADER));
	return request;
}

SubmitAnswerRequest JsonRequestPacketDeserializer::deserializeSubmitAnswerRequest(const Buffer& buff)
{
	json data = deserializeJsonObject(buff);
	SubmitAnswerRequest request;
	request.answerId = std::move(data.at(ANSWERID_HEADER));
	return request;
}

json JsonRequestPacketDeserializer::deserializeJsonObject(const Buffer& buff)
{
	if (buff.size() <= HEADER_FIELD_LENGTH)
	{
		throw std::exception("Recieved buffer is too short");
	}
	int msgSize;
	std::memcpy(&msgSize, &buff.at(CODE_FIELD_LENGTH), SIZE_FIELD_LENGTH);
	if (msgSize > buff.size() - HEADER_FIELD_LENGTH)
	{
		throw std::exception("Recieved message size is longer than message");
	}

	std::string jsonStr((char*)&buff.at(HEADER_FIELD_LENGTH), msgSize);
	try
	{
		return json::parse(jsonStr);
	}
	catch (const json::parse_error& e)
	{
		throw std::exception("Error parsing JSON");
	}
}
