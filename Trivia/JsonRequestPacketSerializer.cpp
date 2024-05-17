#include "JsonRequestPacketSerializer.h"

Buffer JsonResponsePacketSerializer::serializeResponse(ErrorResponse res)
{
	json jsonObj{ { "message", res.message } };
	return buildBuffer(ProtocolCode::Error, jsonObj);
}

Buffer JsonResponsePacketSerializer::serializeResponse(LoginResponse res)
{
	json jsonObj{ { "status", res.status } };
	return buildBuffer(ProtocolCode::Login, jsonObj);
}

Buffer JsonResponsePacketSerializer::serializeResponse(SignupResponse res)
{
	json jsonObj{ { "status", res.status } };
	return buildBuffer(ProtocolCode::Signup, jsonObj);
}

Buffer JsonResponsePacketSerializer::serializeResponse(LogoutResponse res)
{
	json jsonObj{ { "status", res.status } };
	return buildBuffer(ProtocolCode::Logout, jsonObj);
}

Buffer JsonResponsePacketSerializer::serializeResponse(GetRoomsResponse res)
{
	/* Gets serialized using a member function (see RoomData's definition) */
	json jsonObj{ {"Rooms", res.rooms} };
	return buildBuffer(ProtocolCode::GetRooms, jsonObj);
}

Buffer JsonResponsePacketSerializer::serializeResponse(GetPlayersInRoomResponse res)
{
	json jsonObj{ {"PlayersInRoom", res.players} };
	return buildBuffer(ProtocolCode::GetPlayersInRoom, jsonObj);
}

Buffer JsonResponsePacketSerializer::serializeResponse(JoinRoomResponse res)
{
	json jsonObj{ { "status", res.status} };
	return buildBuffer(ProtocolCode::JoinRoom, jsonObj);
}

Buffer JsonResponsePacketSerializer::serializeResponse(CreateRoomResponse res)
{
	json jsonObj{ { "status", res.status} };
	return buildBuffer(ProtocolCode::CreateRoom, jsonObj);
}

Buffer JsonResponsePacketSerializer::serializeResponse(GetHighScoresResponse res)
{
	/* format: { "HighScores": [ [name1, score1], [name2, score2] ... ] } */
	json jsonObj{ { "HighScores", res.highScores } };
	return buildBuffer(ProtocolCode::GetHighScores, jsonObj);
}

Buffer JsonResponsePacketSerializer::serializeResponse(GetPersonalStatsResponse res)
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

Buffer JsonResponsePacketSerializer::serializeResponse(CloseRoomResponse res)
{
	json jsonObj{ { "status", res.status } };
	return buildBuffer(ProtocolCode::CloseRoom, jsonObj);
}

Buffer JsonResponsePacketSerializer::serializeResponse(StartGameResponse res)
{
	json jsonObj{ { "status", res.status, }, { "startTime", res.startTime } };
	return buildBuffer(ProtocolCode::StartGame, jsonObj);
}

Buffer JsonResponsePacketSerializer::serializeResponse(GetRoomStateResponse res)
{
	json jsonObj
	{
		{ "RoomState",
			{ "hasGameBegun", res.roomState.hasGameBegun },
			{ "players", res.roomState.players},
			{ "answerCount", res.roomState.numOfQuestionsInGame },
			{ "answerTimeOut", res.roomState.timerPerQuestion }
		}
	};
	return buildBuffer(ProtocolCode::GetRoomState, jsonObj);
}

Buffer JsonResponsePacketSerializer::serializeResponse(LeaveRoomResponse res)
{
	json jsonObj{ { "status", res.status } };
	return buildBuffer(ProtocolCode::LeaveRoom, jsonObj);
}

Buffer JsonResponsePacketSerializer::buildBuffer(ProtocolCode resCode, const json& jsonObj)
{
	auto msg = jsonObj.dump();
	int msgSize = msg.length();

	Buffer buff(msgSize + HEADER_FIELD_LENGTH);

	buff.at(0) = (Byte)resCode; // no need for memcpy for a size of 1
	std::memcpy(&buff.at(CODE_FIELD_LENGTH), &msgSize, SIZE_FIELD_LENGTH);
	std::memcpy(&buff.at(HEADER_FIELD_LENGTH), msg.c_str(), msgSize);
	return buff;
}
