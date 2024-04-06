#pragma once
#include "Requests.h"
#include <regex>

class CheckSignupData {
public:
	static bool CheckData(const SignupRequest& userData);

private:
	static bool CheckPassword(const std::string& password);
	static bool CheckEmail(const std::string& email);
	static bool CheckAddress(const std::string& address);
	static bool CheckPhoneNumber(const std::string& phoneNumber);
	static bool CheckBirthDate(const std::string& birthDate);
};