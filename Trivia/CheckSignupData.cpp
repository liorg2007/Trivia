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
  return std::regex_match(email, std::regex("^[\w-\.]+@([\w-]+\.)+[\w-]{2,4}$"));
}

bool CheckSignupData::CheckAddress(const std::string& address)
{
  return std::regex_match(address, std::regex("^[a-zA-Z]+,[\d]+,[a-zA-Z]+$"));
}

bool CheckSignupData::CheckPhoneNumber(const std::string& phoneNumber)
{
  return std::regex_match(phoneNumber, std::regex("^0[0-9]{9}$"));
}

bool CheckSignupData::CheckBirthDate(const std::string& birthDate)
{
  return std::regex_match(birthDate, std::regex("\d\d+\/+\d\d+\/+\d\d\d\d$"));
}
