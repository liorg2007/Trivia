#pragma once
#include "Responses.h"
#include <vector>

typedef std::vector<unsigned char> Buffer;

class JsonRequestPacketSerializer
{
public:
	static Buffer serializeResponse(ErrorResponse res);
	static Buffer serializeResponse(LoginResponse res);
	static Buffer serializeResponse(SignupResponse res);
};
