#include "Server.h"
#include "SqliteDatabase.h"
#include "Constants.h"

Server::Server()
	: _database(new SqliteDatabase(DATABASE_FILE_NAME)), _handlerFactory(_database), _communicator(_handlerFactory)
{
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
