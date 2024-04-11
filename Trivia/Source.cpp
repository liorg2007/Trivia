#include "Server.h"
#include "WSAInitializer.h"
#include "JsonRequestPacketDeserializer.h"
#include "JsonRequestPacketSerializer.h"

int main()
{
	WSAInitializer wsaInit;
	Server& server = Server::getInstance();

	server.run();

	system("PAUSE");
	return 0;
}