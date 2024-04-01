#pragma once
#include "json.hpp"
#include "Requests.h"
#include "Responses.h"
#include "Constants.h"

class JsonRequestPacketDeserializer
{
public:
	static LoginRequest deserializeLoginRequest(Buffer buff);
	static SignupRequest deserializeSignupRequest(Buffer buff);
};