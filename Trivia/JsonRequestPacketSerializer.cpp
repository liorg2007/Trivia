#include "JsonRequestPacketSerializer.h"

Buffer JsonRequestPacketSerializer::serializeResponse(ErrorResponse res)
{
	json jsonObj{ { "message", res.message } };
	return buildBuffer(ResponseCode::Error, jsonObj);
}

Buffer JsonRequestPacketSerializer::serializeResponse(LoginResponse res)
{
	json jsonObj{ { "status", res.status } };
	return buildBuffer(ResponseCode::Login, jsonObj);
}

Buffer JsonRequestPacketSerializer::serializeResponse(SignupResponse res)
{
	json jsonObj{ { "status", res.status } };
	return buildBuffer(ResponseCode::Signup, jsonObj);
}

Buffer JsonRequestPacketSerializer::serializeResponse(LogoutResponse res)
{
	json jsonObj{ { "status", res.status } };
	return buildBuffer(ResponseCode::Logout, jsonObj);
}

Buffer JsonRequestPacketSerializer::serializeResponse(GetRoomsResponse res)
{
	json jsonObj{ {"Rooms", res.rooms} };
	return buildBuffer(ResponseCode::GetRooms, jsonObj);
}

Buffer JsonRequestPacketSerializer::serializeResponse(GetPlayersInRoomResponse res)
{
	json jsonObj{ {"PlayersInRoom", res.players} };
	return buildBuffer(ResponseCode::GetPlayersInRoom, jsonObj);
}

Buffer JsonRequestPacketSerializer::serializeResponse(JoinRoomResponse res)
{
	json jsonObj{ { "status", res.status} };
	return buildBuffer(ResponseCode::JoinRoom, jsonObj);
}

Buffer JsonRequestPacketSerializer::serializeResponse(CreateRoomResponse res)
{
	json jsonObj{ { "status", res.status} };
	return buildBuffer(ResponseCode::CreateRoom, jsonObj);
}

Buffer JsonRequestPacketSerializer::serializeResponse(GetHighScoresResponse res)
{
	/* format: { "HighScores": [ [name1, score1], [name2, score2] ... ] } */
	json jsonObj{ { "HighScores", res.highScores } };
	return buildBuffer(ResponseCode::GetHighScores, jsonObj);
}

Buffer JsonRequestPacketSerializer::serializeResponse(GetPersonalStatsResponse res)
{
	json jsonObj
	{
		{ "UserStatistics",
			{ "score", res.statistics.score },
			{ "averageAnswerTime", res.statistics.averageAnswerTime},
			{ "correctAnswers", res.statistics.correctAnswers },
			{ "totalAnswers", res.statistics.totalAnswers }
		} 
	};
	return buildBuffer(ResponseCode::GetPersonalStats, jsonObj);
}

Buffer JsonRequestPacketSerializer::buildBuffer(ResponseCode resCode, const json& jsonObj)
{
	auto msg = jsonObj.dump();
	int msgSize = msg.length();

	Buffer buff(msgSize + HEADER_FIELD_LENGTH);

	buff.at(0) = (Byte)resCode; // no need for memcpy for a size of 1
	std::memcpy(&buff.at(CODE_FIELD_LENGTH), &msgSize, SIZE_FIELD_LENGTH);
	std::memcpy(&buff.at(HEADER_FIELD_LENGTH), msg.c_str(), msgSize);
	return buff;
}
