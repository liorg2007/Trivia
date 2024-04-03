#pragma once
#include <string>

class LoggedUser
{
public:
	LoggedUser(const std::string& username);

	std::string getUsername() const;
private:
	std::string _username;
};

