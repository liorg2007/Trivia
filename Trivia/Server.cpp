#include "Server.h"

Server::Server()
	: _communicatorThread(nullptr)
{
}

Server::~Server()
{
	if (_communicatorThread != nullptr)
	{
		_communicatorThread->join();
		delete _communicatorThread;
	}
}

void Server::run()
{
	_communicatorThread = new std::thread(&Communicator::startHandleRequests,
		_communicator);
	std::string inp;
	do
	{
		std::cout << "Enter command (EXIT to close program):" << std::endl;
		std::cin >> inp;

		// IMPLEMENT ADMIN COMMANDS HERE

	} while (inp != "EXIT");
	exit(0);
}
