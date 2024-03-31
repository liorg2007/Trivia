#pragma once
#include "Responses.h"
#include <vector>

class JsonRequestPacketSerializer
{
public:
	static Buffer serializeResponse(ErrorResponse res);
	static Buffer serializeResponse(LoginResponse res);
	static Buffer serializeResponse(SignupResponse res);
};
