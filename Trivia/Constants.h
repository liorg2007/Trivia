#pragma once
#include <vector>

typedef unsigned char Byte;
typedef std::vector<Byte> Buffer;

enum MessageCode {
	SignupResponseCode,
	LoginResponseCode,
	ErrorResponseCode
};

// Message code - 1 bytes
// Message length - 4 bytes
constexpr auto MESSAGE_HEADER_LENGTH = 5;