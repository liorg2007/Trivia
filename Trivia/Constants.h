#pragma once
#include <vector>

typedef unsigned char Byte;
typedef std::vector<Byte> Buffer;

enum MessageCode {
	SignupResponseCode,
	LoginResponseCode,
	ErrorResponseCode
};
