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

Buffer JsonRequestPacketSerializer::serializeResponse(LogoutResponse res)
{
	json jsonObj{ { "status", res.status } };
	return buildBuffer(MessageCode::LogoutResponseCode, jsonObj);
}

Buffer JsonRequestPacketSerializer::serializeResponse(GetRoomsResponse res)
{
	json jsonObj{ {"Rooms", res.rooms} };
	return buildBuffer(MessageCode::GetRoomsResponseCode, jsonObj);
}

Buffer JsonRequestPacketSerializer::serializeResponse(GetPlayersInRoomResponse res)
{
	json jsonObj{ {"PlayersInRoom", res.players} };
	return buildBuffer(MessageCode::GetPlayersInRoomResponseCode, jsonObj);
}

Buffer JsonRequestPacketSerializer::serializeResponse(JoinRoomResponse res)
{
	json jsonObj{ { "status", res.status} };
	return buildBuffer(MessageCode::JoinRoomResponseCode, jsonObj);
}

Buffer JsonRequestPacketSerializer::serializeResponse(CreateRoomResponse res)
{
	json jsonObj{ { "status", res.status} };
	return buildBuffer(MessageCode::CreateRoomResponseCode, jsonObj);
}

Buffer JsonRequestPacketSerializer::serializeResponse(GetHighScoresResponse res)
{
	/* format: { "HighScores": [ [name1, score1], [name2, score2] ... ] } */
	json jsonObj{ { "HighScores", res.highScores } };
	return buildBuffer(MessageCode::GetHighScoresResponseCode, jsonObj);
}

Buffer JsonRequestPacketSerializer::serializeResponse(GetPersonalStatsResponse res)
{
	json jsonObj
	{
		{ "UserStatistics",
			{ "score", res.score },
			{ "averageAnswerTime", res.averageAnswerTime},
			{ "correctAnswers", res.correctAnswers },
			{ "totalAnswers", res.totalAnswers }
		} 
	};
	return buildBuffer(MessageCode::GetPersonalStatsResponseCode, jsonObj);
}

Buffer JsonRequestPacketSerializer::buildBuffer(MessageCode resCode, const json& jsonObj)
{
	auto msg = jsonObj.dump();
	int msgSize = msg.length();

	Buffer buff(msgSize + HEADER_FIELD_LENGTH);

	buff.at(0) = (Byte)resCode; // no need for memcpy for a size of 1
	std::memcpy(&buff.at(CODE_FIELD_LENGTH), &msgSize, SIZE_FIELD_LENGTH);
	std::memcpy(&buff.at(HEADER_FIELD_LENGTH), msg.c_str(), msgSize);
	return buff;
}
