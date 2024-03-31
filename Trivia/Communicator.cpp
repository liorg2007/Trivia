#include "Communicator.h"

void Communicator::bindAndListen()
{
	struct sockaddr_in sockAddr = { 0 };

	sockAddr.sin_port = htons(_PORT); // port that server will listen for
	sockAddr.sin_family = AF_INET;   // must be AF_INET
	sockAddr.sin_addr.s_addr = INADDR_ANY;    // when there are few ip's for the machine. We will use always "INADDR_ANY"

	if (bind(_serverSocket, (struct sockaddr*)&sockAddr, sizeof(sockAddr)) == SOCKET_ERROR)
		throw std::exception(__FUNCTION__ " - bind");

	if (listen(_serverSocket, SOMAXCONN) == SOCKET_ERROR)
		throw std::exception(__FUNCTION__ " - listen");
	std::cout << "Listening on port " << _PORT << std::endl;

	while (true)
	{
		std::cout << "Waiting for client connection request" << std::endl;

		// GOT A NEW CLIENT
		SOCKET clientSocket = accept(_serverSocket, NULL, NULL);
		if (clientSocket == INVALID_SOCKET)
			throw std::exception(__FUNCTION__);

		std::cout << "New client accepted, starting a new thread" << std::endl;
		_threadPool.push_back(
			new std::thread(&Communicator::handleNewClient,
				this, clientSocket));
		_clients.insert({ clientSocket, LoginRequestHandler() });
	}
}

void Communicator::handleNewClient(SOCKET clientSocket)
{
	char data[6] = { 0 };
	recv(clientSocket, data, 5, 0);
	std::cout << "Client says: " << data << std::endl;
	try
	{
		while (true)
		{
			// handle requests using _clients.at(clientSocket)
		}
	}
	catch (...)
	{
		std::cerr << "User " << clientSocket << " disconnected." << std::endl;
		_clients.erase(clientSocket);
		closesocket(clientSocket);
	}
}

Communicator::Communicator()
	: _serverSocket(socket(AF_INET, SOCK_STREAM, IPPROTO_TCP))
{
	if (_serverSocket == INVALID_SOCKET)
	{
		throw std::exception(__FUNCTION__ " - socket");
	}
}

Communicator::~Communicator()
{
	try
	{
		for (const auto& pThread : _threadPool)
		{
			pThread->join();
			delete pThread;
		}
		closesocket(_serverSocket);
	}
	catch (...) {}
}

void Communicator::startHandleRequests()
{
	bindAndListen();
}
