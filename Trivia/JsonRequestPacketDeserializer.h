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

	static SubmitAnswerRequest deserializeSubmitAnswerRequest(const Buffer& buff);

private:
	static json deserializeJsonObject(const Buffer& buff);

	static constexpr auto USERNAME_HEADER = "username";
	static constexpr auto PASSWORD_HEADER = "password";
	static constexpr auto EMAIL_HEADER = "email";
	static constexpr auto ADDRESS_HEADER = "address";
	static constexpr auto PHONE_NUMBER_HEADER = "phoneNumber";
	static constexpr auto BIRTH_DATE_HEADER = "birthDate";

	static constexpr auto ROOMID_HEADER = "roomId";
	static constexpr auto ROOM_NAME_HEADER = "roomName";
	static constexpr auto MAX_USERS_HEADER = "maxUsers";
	static constexpr auto QUESTION_COUNT_HEADER = "questionCount";
	static constexpr auto ANSWER_TIMEOUT_HEADER = "answerTimeout";

	static constexpr auto ANSWERID_HEADER = "answerId";

};