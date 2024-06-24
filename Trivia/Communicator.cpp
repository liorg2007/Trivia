#include "Communicator.h"
#include "JsonResponsePacketSerializer.h"

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
		_clients.emplace(clientSocket, _handlerFactory.createLoginRequestHandler());
		_threadPool.push_back(
			new std::thread(&Communicator::handleNewClient,
				this, clientSocket));
	}
}

void Communicator::handleNewClient(SOCKET clientSocket)
{
	bool keepHandling = true;
	try
	{
		while (keepHandling)
		{
			auto handlerSearch = _clients.find(clientSocket);
			if(handlerSearch == _clients.end()) //check if user isnt in handler search
			{
				terminateConnection(clientSocket, handlerSearch);
				keepHandling = false;
				continue;
			}

			RequestInfo reqInfo;
			try
			{
				reqInfo = recieveData(clientSocket);
			}
			catch (const std::exception& e)
			{
				sendData(clientSocket, parseErrorMessage(e.what()));
				continue;
			}

			if (handlerSearch->second->isRequestRelevant(reqInfo))
			{
				RequestResult res;
				try
				{
					res = handlerSearch->second->handleRequest(reqInfo);
				}
				catch (const std::exception& e)
				{
					res.newHandler = nullptr;
					res.response = parseErrorMessage(e.what());
				}

				if (res.newHandler != nullptr)
				{
					handlerSearch->second = std::move(res.newHandler);
				}

				sendData(clientSocket, res.response);
			}
			else
			{
				// send error message
				sendData(clientSocket,
					parseErrorMessage("Request is not relevant to current client state"));
			}
		}
	}
	catch (...)
	{
		terminateConnection(clientSocket, std::nullopt);
	}
}

void Communicator::sendData(SOCKET clientSocket, const Buffer& buff) const
{
	if (send(clientSocket, (const char*)&buff.at(0), buff.size(), 0) == INVALID_SOCKET)
	{
		throw std::exception("Error while sending message to client");
	}
}

RequestInfo Communicator::recieveData(SOCKET clientSocket) const
{
	RequestInfo req;
	req.buffer = Buffer(HEADER_FIELD_LENGTH);
	uint32_t msgSize = 0;

	if (recv(clientSocket, (char*)&req.buffer.at(0), HEADER_FIELD_LENGTH, 0) != HEADER_FIELD_LENGTH)
	{
		throw std::exception("Invalid packet protocol");
	}
	std::memcpy(&msgSize, &req.buffer.at(CODE_FIELD_LENGTH), SIZE_FIELD_LENGTH);
	req.buffer.resize(HEADER_FIELD_LENGTH + msgSize);
	if (msgSize > 0)
		if (recv(clientSocket, (char*)&req.buffer.at(HEADER_FIELD_LENGTH), msgSize, 0) != msgSize)
		{
			throw std::exception("Packet length is not as expected");
		}
	req.id = (ProtocolCode)req.buffer.at(0);
	req.receivalTime = std::time(0);
	// std::cout << "Client says: " << (char*)&req.buffer.at(0) << std::endl;
	return req;
}

Buffer Communicator::parseErrorMessage(std::string&& errMsg) const
{
	ErrorResponse res;
	res.message = std::move(errMsg);
	return JsonResponsePacketSerializer::serializeResponse(res);
}

void Communicator::terminateConnection(SOCKET clientSocket, const std::optional<map_iterator>& handlerSearchResult)
{
	std::cerr << "User " << clientSocket << " disconnected." << std::endl;
	auto handlerSearch = handlerSearchResult.value_or(_clients.find(clientSocket));
	if (handlerSearch != _clients.end())
	{
		handlerSearch->second->handleDisconnect();
		handlerSearch->second.release();
		_clients.erase(clientSocket);
	}
	closesocket(clientSocket);
}

Communicator::Communicator()
	: _serverSocket(socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)),
	_handlerFactory(RequestHandlerFactory::getInstance())
{
	if (_serverSocket == INVALID_SOCKET)
	{
		throw std::exception(__FUNCTION__ " - socket");
	}
}

Communicator& Communicator::getInstance()
{
	static Communicator instance;
	return instance;
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
	_threadPool.push_back(
		new std::thread(&Communicator::bindAndListen,
			this));
}
