#pragma once
#include "json.hpp"
#include "Responses.h"
#include "Constants.h"

class JsonRequestPacketSerializer
{
public:
	static Buffer serializeResponse(ErrorResponse res);
	static Buffer serializeResponse(LoginResponse res);
	static Buffer serializeResponse(SignupResponse res);
};
