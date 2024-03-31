#include "Server.h"
#include "WSAInitializer.h"

int main()
{
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);
	try {
		Server server = Server();
		server.run();
	}
	catch (const std::exception& e) {
		std::cout << e.what() << std::endl;
	}
}