#pragma once
#include "Requests.h"
#include <regex>

class CheckSignupData {
public:
	static bool CheckData(const SignupRequest& userData);

private:
	bool CheckPassword(const std::string& password);
	bool CheckEmail(const std::string& email);
	bool CheckAddress(const std::string& address);
	bool CheckPhoneNumber(const std::string& phoneNumber);
	bool CheckBirthDate(const std::string& birthDate);
};