#include "Server.h"

Server::Server()
{
}

void Server::run()
{
	_communicator.startHandleRequests();
}
