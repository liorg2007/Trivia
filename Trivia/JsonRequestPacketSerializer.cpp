#include "JsonRequestPacketSerializer.h"

Buffer JsonRequestPacketSerializer::serializeResponse(ErrorResponse res)
{
	json jsonObj{ { "message", res.message } };
	return buildBuffer(ProtocolCode::Error, jsonObj);
}

Buffer JsonRequestPacketSerializer::serializeResponse(LoginResponse res)
{
	json jsonObj{ { "status", res.status } };
	return buildBuffer(ProtocolCode::Login, jsonObj);
}

Buffer JsonRequestPacketSerializer::serializeResponse(SignupResponse res)
{
	json jsonObj{ { "status", res.status } };
	return buildBuffer(ProtocolCode::Signup, jsonObj);
}

Buffer JsonRequestPacketSerializer::serializeResponse(LogoutResponse res)
{
	json jsonObj{ { "status", res.status } };
	return buildBuffer(ProtocolCode::Logout, jsonObj);
}

Buffer JsonRequestPacketSerializer::serializeResponse(GetRoomsResponse res)
{
	/* Gets serialized using a member function (see RoomData's definition) */
	json jsonObj{ {"Rooms", res.rooms} };
	return buildBuffer(ProtocolCode::GetRooms, jsonObj);
}

Buffer JsonRequestPacketSerializer::serializeResponse(GetPlayersInRoomResponse res)
{
	json jsonObj{ {"PlayersInRoom", res.players} };
	return buildBuffer(ProtocolCode::GetPlayersInRoom, jsonObj);
}

Buffer JsonRequestPacketSerializer::serializeResponse(JoinRoomResponse res)
{
	json jsonObj{ { "status", res.status} };
	return buildBuffer(ProtocolCode::JoinRoom, jsonObj);
}

Buffer JsonRequestPacketSerializer::serializeResponse(CreateRoomResponse res)
{
	json jsonObj{ { "status", res.status} };
	return buildBuffer(ProtocolCode::CreateRoom, jsonObj);
}

Buffer JsonRequestPacketSerializer::serializeResponse(GetHighScoresResponse res)
{
	/* format: { "HighScores": [ [name1, score1], [name2, score2] ... ] } */
	json jsonObj{ { "HighScores", res.highScores } };
	return buildBuffer(ProtocolCode::GetHighScores, jsonObj);
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
	return buildBuffer(ProtocolCode::GetPersonalStats, jsonObj);
}

Buffer JsonRequestPacketSerializer::serializeResponse(CloseRoomResponse res)
{
	json jsonObj{ { "status", res.status } };
	return buildBuffer(ProtocolCode::CloseRoom, jsonObj);
}

Buffer JsonRequestPacketSerializer::serializeResponse(StartGameResponse res)
{
	json jsonObj{ { "status", res.status } };
	return buildBuffer(ProtocolCode::StartGame, jsonObj);
}

Buffer JsonRequestPacketSerializer::serializeResponse(GetRoomStateResponse res)
{
	json jsonObj
	{
		{ "RoomState",
			{ "hasGameBegun", res.roomState.hasGameBegun },
			{ "players", res.roomState.players},
			{ "answerCount", res.roomState.answerCount },
			{ "answerTimeOut", res.roomState.answerTimeOut }
		}
	};
	return buildBuffer(ProtocolCode::GetRoomState, jsonObj);
}

Buffer JsonRequestPacketSerializer::serializeResponse(LeaveRoomResponse res)
{
	json jsonObj{ { "status", res.status } };
	return buildBuffer(ProtocolCode::LeaveRoom, jsonObj);
}

Buffer JsonRequestPacketSerializer::buildBuffer(ProtocolCode resCode, const json& jsonObj)
{
	auto msg = jsonObj.dump();
	int msgSize = msg.length();

	Buffer buff(msgSize + HEADER_FIELD_LENGTH);

	buff.at(0) = (Byte)resCode; // no need for memcpy for a size of 1
	std::memcpy(&buff.at(CODE_FIELD_LENGTH), &msgSize, SIZE_FIELD_LENGTH);
	std::memcpy(&buff.at(HEADER_FIELD_LENGTH), msg.c_str(), msgSize);
	return buff;
}
