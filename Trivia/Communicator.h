#pragma once
#include <winsock.h>
#include "IRequestHandler.h"
#include <unordered_map>
#include <thread>
#include <iostream>

class Communicator {
private:
	SOCKET _serverSocket;
	std::unordered_map<SOCKET, IRequestHandler> _clients;
	
	std::vector<std::thread*> _threadPool;

	const int PORT = 6969;

	/* Initialize listening socket for the server */
	void bindAndListen();

	/* handles a client socket */
	void handleNewClient(SOCKET clientSocket);

public:
	Communicator();

	/* Free used memory in the end (if needed)*/
	~Communicator();

	/* starts handling the client requests */
	void startHandleRequests();
};