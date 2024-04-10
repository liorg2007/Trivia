#pragma once
#include "json.hpp"
#include "Responses.h"
#include "Constants.h"

using json = nlohmann::json;

class JsonRequestPacketSerializer
{
public:
	static Buffer serializeResponse(ErrorResponse res);
	static Buffer serializeResponse(LoginResponse res);
	static Buffer serializeResponse(SignupResponse res);

private:
	static Buffer buildBuffer(MessageCode resCode, const json& jsonObj);
};
