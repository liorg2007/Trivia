#include "Server.h"
#include "WSAInitializer.h"
#include "SqliteDatabase.h"

int main()
{
	SqliteDatabase db = SqliteDatabase("hahaha.sqlite");
	WSAInitializer wsaInit;
	Server server;
	
	server.run();

	system("PAUSE");
	return 0;
}