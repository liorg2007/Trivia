#include "Server.h"
#include "SqliteDatabase.h"
#include "Constants.h"

Server::Server()
	: _database(IDatabase::getInstance()),
	_handlerFactory(RequestHandlerFactory::getInstance()),
	_communicator(Communicator::getInstance())
{
}

Server& Server::getInstance()
{
	static Server instance;
	return instance;
}

void Server::run()
{
	_communicator.startHandleRequests();
	std::string inp;
	do
	{
		std::cout << "Enter command (EXIT to close program):" << std::endl;
		std::cin >> inp;

		// IMPLEMENT ADMIN COMMANDS HERE

	} while (inp != "EXIT");
	exit(0);
}
