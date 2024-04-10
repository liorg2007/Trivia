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

	static GetPlayersInRoomRequest deserializeGetPlayersRequest(const Buffer& buff);
	static JoinRoomRequest deserializeJoinRoomRequest(const Buffer& buff);
	static CreateRoomRequest deserializeCreateRoomRequest(const Buffer& buff);

private:
	static json deserializeJsonObject(const Buffer& buff);

	static constexpr auto USERNAME_HEADER = "username";
	static constexpr auto PASSWORD_HEADER = "password";
	static constexpr auto EMAIL_HEADER = "email";
	static constexpr auto ADDRESS_HEADER = "address";
	static constexpr auto PHONE_NUMBER_HEADER = "phoneNumber";
	static constexpr auto BIRTH_DATE_HEADER = "birthDate";
};