#pragma once
#include <string>

class LoggedUser
{
public:
	LoggedUser(const std::string& username);

	std::string getUsername() const;
	bool operator==(const LoggedUser& other) const;
private:
	std::string _username;
};

