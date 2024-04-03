#include "Server.h"

Server::Server()
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
