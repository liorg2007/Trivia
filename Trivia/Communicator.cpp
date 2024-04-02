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
		_clients.insert({ clientSocket, new LoginRequestHandler() });
	}
}

void Communicator::handleNewClient(SOCKET clientSocket)
{
	try
	{
		while (true)
		{
			RequestInfo reqInfo;
			reqInfo.buffer = recieveData(clientSocket);
			reqInfo.receivalTime = std::time(0);
			reqInfo.id = (MessageCode)reqInfo.buffer.at(0);
			RequestResult res = _clients.at(clientSocket)->handleRequest(reqInfo);

			_clients.find(clientSocket)->second = res.newHandler;
			sendData(clientSocket, res.response);
		}
	}
	catch (...)
	{
		std::cerr << "User " << clientSocket << " disconnected." << std::endl;
		_clients.erase(clientSocket);
		closesocket(clientSocket);
	}
}

void Communicator::sendData(SOCKET clientSocket, const Buffer& buff) const
{
	if (send(clientSocket, (const char*) & buff[0], buff.size(), 0) == INVALID_SOCKET)
	{
		throw std::exception("Error while sending message to client");
	}
}

Buffer Communicator::recieveData(SOCKET clientSocket) const
{
	Buffer data(HEADER_FIELD_LENGTH);
	uint32_t msgSize = 0;

	if (recv(clientSocket, (char*)&data[0], HEADER_FIELD_LENGTH, 0) != HEADER_FIELD_LENGTH)
	{
		throw std::exception("Client sent protocol invalid length");
	}
	std::memcpy(&msgSize, &data[CODE_FIELD_LENGTH], SIZE_FIELD_LENGTH);
	data.resize(HEADER_FIELD_LENGTH + msgSize);
	if (recv(clientSocket, (char*)&data[HEADER_FIELD_LENGTH], msgSize, 0))
	{
		throw std::exception("Client message length doesn't accord to expected length");
	}

	// std::cout << "Client says: " << (char*)&data[0] << std::endl;
	return data;
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
