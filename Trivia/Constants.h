#pragma once
#include <vector>
#include <string>

using Byte = uint8_t;
using Buffer = std::vector<Byte>;
using ScoreList = std::vector<std::pair<std::string, int>>;

enum class MessageCode : Byte
{
	LoginRequestCode,
	SignupRequestCode,

	LoginResponseCode,
	SignupResponseCode,
	ErrorResponseCode
};

static constexpr auto SUCCESS = 1;
static constexpr auto FAILURE = 0;

static constexpr auto CODE_FIELD_LENGTH = 1;
static constexpr auto SIZE_FIELD_LENGTH = 4;
static constexpr auto HEADER_FIELD_LENGTH = CODE_FIELD_LENGTH + SIZE_FIELD_LENGTH;

static constexpr auto DATABASE_FILE_NAME = "UsersDB.sqlite";
