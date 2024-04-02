#include "Server.h"
#include "WSAInitializer.h"
#include "SqliteDatabase.h"

int main()
{
	SqliteDatabase db = SqliteDatabase("hahaha.sqlite");
	db.~SqliteDatabase();
	WSAInitializer wsaInit;
	Server server;
	
	server.run();

	system("PAUSE");
	return 0;
}