#include "Communicator.h"

void Communicator::bindAndListen()
{
	struct sockaddr_in sa = { 0 };

	sa.sin_port = htons(PORT); // port that server will listen for
	sa.sin_family = AF_INET;   // must be AF_INET
	sa.sin_addr.s_addr = INADDR_ANY;    // when there are few ip's for the machine. We will use always "INADDR_ANY"

	if (bind(_serverSocket, (struct sockaddr*)&sa, sizeof(sa)) == SOCKET_ERROR)
		throw std::exception(__FUNCTION__ " - bind");

	if (listen(_serverSocket, SOMAXCONN) == SOCKET_ERROR)
		throw std::exception(__FUNCTION__ " - listen");
	std::cout << "Listening on port " << PORT << std::endl;

	while (true)
	{
		std::cout << "Waiting for client connection request" << std::endl;

		// GOT A NEW CLIENT
		SOCKET client_socket = accept(_serverSocket, NULL, NULL);
		if (client_socket == INVALID_SOCKET)
			throw std::exception(__FUNCTION__);

		std::cout << "New client accepted, starting a new thread" << std::endl;
		_threadPool.push_back(
			new std::thread(&Communicator::handleNewClient,
				this, client_socket));
		_clients.insert({ client_socket, LoginRequestHandler() });
	}
}

void Communicator::handleNewClient(SOCKET clientSocket)
{
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
		for (const auto& t : _threadPool)
		{
			t->join();
			delete t;
		}
		closesocket(_serverSocket);
	}
	catch (...) {}
}

void Communicator::startHandleRequests()
{
	bindAndListen();
}
