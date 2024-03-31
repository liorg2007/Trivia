#include "Server.h"
#include "WSAInitializer.h"

int main()
{
	WSAInitializer wsaInit;
	Server server;
	
	server.run();

	system("PAUSE");
	return 0;
}