#pragma once
#include "json.hpp"
#include "Requests.h"
#include "Responses.h"
#include "Constants.h"

using json = nlohmann::json;

class JsonRequestPacketDeserializer
{
public:
	static LoginRequest deserializeLoginRequest(const Buffer& buff);
	static SignupRequest deserializeSignupRequest(const Buffer& buff);

private:
	static json deserializeJsonObject(const Buffer& buff);
};