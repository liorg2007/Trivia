#pragma once
#include "json.hpp"
#include "Responses.h"
#include "Constants.h"
#include "RoomData.h"

using json = nlohmann::json;

class JsonResponsePacketSerializer
{
public:
	static Buffer serializeResponse(const ErrorResponse& res);
	static Buffer serializeResponse(const LoginResponse& res);
	static Buffer serializeResponse(const SignupResponse& res);
	static Buffer serializeResponse(const LogoutResponse& res);

	static Buffer serializeResponse(const GetRoomsResponse& res);
	static Buffer serializeResponse(const GetPlayersInRoomResponse& res);
	static Buffer serializeResponse(const JoinRoomResponse& res);
	static Buffer serializeResponse(const CreateRoomResponse& res);
	static Buffer serializeResponse(const GetHighScoresResponse& res);
	static Buffer serializeResponse(const GetPersonalStatsResponse& res);
	static Buffer serializeResponse(const CloseRoomResponse& res);
	static Buffer serializeResponse(const StartGameResponse& res);
	static Buffer serializeResponse(const GetRoomStateResponse& res);
	static Buffer serializeResponse(const LeaveRoomResponse& res);

	static Buffer serializeResponse(const GetGameResultsResponse& res);
	static Buffer serializeResponse(const SubmitAnswerResponse& res);
	static Buffer serializeResponse(const GetQuestionResponse& res);
	static Buffer serializeResponse(const LeaveGameResponse& res);

	static Buffer serializeResponse(const ClientHelloResponse& res);

private:
	static Buffer buildBuffer(ProtocolCode resCode, const json& jsonObj);
};
