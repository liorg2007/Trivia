#pragma once
#pragma comment(lib, "ws2_32.lib")
#include <WinSock2.h>
#include <Windows.h>
#include <unordered_map>
#include <thread>
#include <iostream>
#include "Constants.h"
#include "IRequestHandler.h"
#include "LoginRequestHandler.h"
#include "RequestHandlerFactory.h"


class Communicator {
private:
	SOCKET _serverSocket;
	RequestHandlerFactory& _handlerFactory;

	std::unordered_map<SOCKET, IRequestHandler*> _clients;
	
	std::vector<std::thread*> _threadPool;

	const int _PORT = 6969;

	/* Initialize listening socket for the server */
	void bindAndListen();

	/* handles a client socket */
	void handleNewClient(SOCKET clientSocket);

	void sendData(SOCKET clientSocket, const Buffer& buff) const;
	Buffer recieveData(SOCKET clientSocket) const;

public:
	Communicator(RequestHandlerFactory& handlerFactory);

	/* Free used memory in the end (if needed)*/
	~Communicator();

	/* starts handling the client requests */
	void startHandleRequests();
};