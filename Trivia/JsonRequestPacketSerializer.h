#pragma once
#include "json.hpp"
#include "Responses.h"
#include "Constants.h"
#include "RoomData.h"

using json = nlohmann::json;

class JsonRequestPacketSerializer
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
	static Buffer serializeResponse(GetHighScoreResponse res);
	static Buffer serializeResponse(GetPersonalStatsResponse res);

private:
	static Buffer buildBuffer(MessageCode resCode, const json& jsonObj);
};
