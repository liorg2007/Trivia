#include "Server.h"

Server::Server()
	: _commThread(nullptr)
{
}

Server::~Server()
{
	if (_commThread != nullptr)
	{
		_commThread->join();
		delete _commThread;
	}
}

void Server::run()
{
	_commThread = new std::thread(&Communicator::startHandleRequests,
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
