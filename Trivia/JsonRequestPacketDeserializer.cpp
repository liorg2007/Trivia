#include "JsonRequestPacketDeserializer.h"

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

KeyExchangeRequest JsonRequestPacketDeserializer::deserialzieKeyExchangeRequest(const Buffer& buff)
{
	std::string jsonStr(buff.begin(), buff.end());  // Safely convert the vector to a string
	json data = json::parse(jsonStr);
	KeyExchangeRequest request;

	std::string iv = base64Decode(data.at(IV_HEADER).get<std::string>());

	// Convert the JSON string or array to Buffer
	std::string keyStr = base64Decode(data.at(KEY_HEADER).get<std::string>());
	request.keyAndIv.key = Buffer(keyStr.begin(), keyStr.end());

	std::copy(iv.begin(), iv.end(), request.keyAndIv.iv);

	return request;
}

std::string JsonRequestPacketDeserializer::base64Decode(const std::string& encoded)
{
	std::string decoded;
	CryptoPP::StringSource ss(encoded, true,
		new CryptoPP::Base64Decoder(
			new CryptoPP::StringSink(decoded)
		)
	);
	return decoded;
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
