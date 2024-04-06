#include "CheckSignupData.h"

bool CheckSignupData::CheckData(const SignupRequest& userData)
{
    return false;
}

bool CheckSignupData::CheckPassword(const std::string& password)
{
  return std::regex_match(password, std::regex("^(?=.*?[A-Z])(?=.*?[a-z])(?=.*?[0-9])(?=.*?[#?!@$%^&*-]).{8,}$"));
}

bool CheckSignupData::CheckEmail(const std::string& email)
{
  return false;
}

bool CheckSignupData::CheckAddress(const std::string& address)
{
  return false;
}

bool CheckSignupData::CheckPhoneNumber(const std::string& phoneNumber)
{
  return false;
}

bool CheckSignupData::CheckBirthDate(const std::string& birthDate)
{
  return false;
}
