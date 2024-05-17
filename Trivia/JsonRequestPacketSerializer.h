#pragma once
#include "json.hpp"
#include "Responses.h"
#include "Constants.h"
#include "RoomData.h"

using json = nlohmann::json;

class JsonResponsePacketSerializer
{
public:
	static Buffer serializeResponse(ErrorResponse res);
	static Buffer serializeResponse(LoginResponse res);
	static Buffer serializeResponse(SignupResponse res);
	static Buffer serializeResponse(LogoutResponse res);

	static Buffer serializeResponse(GetRoomsResponse res);
	static Buffer serializeResponse(GetPlayersInRoomResponse res);
	static Buffer serializeResponse(JoinRoomResponse res);
	static Buffer serializeResponse(CreateRoomResponse res);
	static Buffer serializeResponse(GetHighScoresResponse res);
	static Buffer serializeResponse(GetPersonalStatsResponse res);
	static Buffer serializeResponse(CloseRoomResponse res);
	static Buffer serializeResponse(StartGameResponse res);
	static Buffer serializeResponse(GetRoomStateResponse res);
	static Buffer serializeResponse(LeaveRoomResponse res);

private:
	static Buffer buildBuffer(ProtocolCode resCode, const json& jsonObj);
};
