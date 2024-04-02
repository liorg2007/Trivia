#pragma once
#include "json.hpp"
#include "Requests.h"
#include "Responses.h"
#include "Constants.h"

using json = nlohmann::json;

class JsonRequestPacketDeserializer
{
public:
	static LoginRequest deserializeLoginRequest(Buffer buff);
	static SignupRequest deserializeSignupRequest(Buffer buff);

private:
	static json deserializeJsonObject(Buffer buff);
};