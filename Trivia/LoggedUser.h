#pragma once
#include <string>
#include <WinSock2.h>

class LoggedUser
{
public:
	LoggedUser(const std::string& username);

	std::string getUsername() const;
	bool operator==(const LoggedUser& other) const;
	bool operator==(const std::string& other) const;
private:
	std::string _username;
};

