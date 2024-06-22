#include "JsonResponsePacketSerializer.h"

Buffer JsonResponsePacketSerializer::serializeResponse(const ErrorResponse& res)
{
	json jsonObj{ { "message", res.message } };
	return buildBuffer(ProtocolCode::Error, jsonObj);
}

Buffer JsonResponsePacketSerializer::serializeResponse(const LoginResponse& res)
{
	json jsonObj{ { "status", res.status } };
	return buildBuffer(ProtocolCode::Login, jsonObj);
}

Buffer JsonResponsePacketSerializer::serializeResponse(const SignupResponse& res)
{
	json jsonObj{ { "status", res.status } };
	return buildBuffer(ProtocolCode::Signup, jsonObj);
}

Buffer JsonResponsePacketSerializer::serializeResponse(const LogoutResponse& res)
{
	json jsonObj{ { "status", res.status } };
	return buildBuffer(ProtocolCode::Logout, jsonObj);
}

Buffer JsonResponsePacketSerializer::serializeResponse(const GetRoomsResponse& res)
{
	/* Gets serialized using a member function (see RoomData's definition) */
	json jsonObj{ {"Rooms", res.rooms} };
	return buildBuffer(ProtocolCode::GetRooms, jsonObj);
}

Buffer JsonResponsePacketSerializer::serializeResponse(const GetPlayersInRoomResponse& res)
{
	json jsonObj{ { "PlayersInRoom", res.players } };
	return buildBuffer(ProtocolCode::GetPlayersInRoom, jsonObj);
}

Buffer JsonResponsePacketSerializer::serializeResponse(const JoinRoomResponse& res)
{
	json jsonObj{ { "status", res.status} };
	return buildBuffer(ProtocolCode::JoinRoom, jsonObj);
}

Buffer JsonResponsePacketSerializer::serializeResponse(const CreateRoomResponse& res)
{
	json jsonObj{ { "status", res.status} };
	return buildBuffer(ProtocolCode::CreateRoom, jsonObj);
}

Buffer JsonResponsePacketSerializer::serializeResponse(const GetHighScoresResponse& res)
{
	/* format: { "HighScores": [ [name1, score1], [name2, score2] ... ] } */
	json jsonObj{ { "HighScores", res.highScores } };
	return buildBuffer(ProtocolCode::GetHighScores, jsonObj);
}

Buffer JsonResponsePacketSerializer::serializeResponse(const GetPersonalStatsResponse& res)
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

Buffer JsonResponsePacketSerializer::serializeResponse(const CloseRoomResponse& res)
{
	json jsonObj{ { "status", res.status } };
	return buildBuffer(ProtocolCode::CloseRoom, jsonObj);
}

Buffer JsonResponsePacketSerializer::serializeResponse(const StartGameResponse& res)
{
	json jsonObj{ { "status", res.status, }, { "startTime", res.startTime } };
	return buildBuffer(ProtocolCode::StartGame, jsonObj);
}

Buffer JsonResponsePacketSerializer::serializeResponse(const GetRoomStateResponse& res)
{
	json jsonObj
	{
		{ "status", res.status, },
		{ "RoomState",
			{ "hasGameBegun", res.roomState.hasGameBegun },
			{ "players", res.roomState.players },
			{ "answerCount", res.roomState.answerCount },
			{ "answerTimeout", res.roomState.answerTimeout }
		}
	};
	return buildBuffer(ProtocolCode::GetRoomState, jsonObj);
}

Buffer JsonResponsePacketSerializer::serializeResponse(const LeaveRoomResponse& res)
{
	json jsonObj{ { "status", res.status } };
	return buildBuffer(ProtocolCode::LeaveRoom, jsonObj);
}

Buffer JsonResponsePacketSerializer::serializeResponse(const GetGameResultsResponse& res)
{
	json jsonObj
	{
		{ "status", res.status },
		{ "results", res.results }
	};
	return buildBuffer(ProtocolCode::GetGameResults, jsonObj);
}

Buffer JsonResponsePacketSerializer::serializeResponse(const SubmitAnswerResponse& res)
{
	json jsonObj{ { "status", res.status }, { "correctAnswerId", res.correctAnswerId } };
	return buildBuffer(ProtocolCode::SubmitAnswer, jsonObj);
}

Buffer JsonResponsePacketSerializer::serializeResponse(const GetQuestionResponse& res)
{
	json jsonObj
	{
		{ "status", res.status },
		{ "question", res.question },
		{ "answers", res.answers }
	};
	return buildBuffer(ProtocolCode::GetGameResults, jsonObj);
}

Buffer JsonResponsePacketSerializer::serializeResponse(const LeaveGameResponse& res)
{
	json jsonObj{ { "status", res.status } };
	return buildBuffer(ProtocolCode::LeaveGame, jsonObj);
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
