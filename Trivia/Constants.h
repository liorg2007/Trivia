#pragma once
#include <vector>
#include <string>

typedef uint8_t Byte;
typedef std::vector<Byte> Buffer;

enum class MessageCode : Byte
{
	LoginRequestCode,
	SignupRequestCode,

	LoginResponseCode,
	SignupResponseCode,
	ErrorResponseCode
};


constexpr auto CODE_FIELD_LENGTH = 1;
constexpr auto SIZE_FIELD_LENGTH = 4;
constexpr auto HEADER_FIELD_LENGTH = CODE_FIELD_LENGTH + SIZE_FIELD_LENGTH;

constexpr auto DATABASE_FILE_NAME = "UsersDB.sqlite3";
