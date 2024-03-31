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
}
