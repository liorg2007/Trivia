#include "Communicator.h"
#include "JsonRequestPacketSerializer.h"

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
		_clients.insert({ clientSocket, _handlerFactory.createLoginRequestHandler() });
		_threadPool.push_back(
			new std::thread(&Communicator::handleNewClient,
				this, clientSocket));
	}
}

void Communicator::handleNewClient(SOCKET clientSocket)
{
	try
	{
		while (true)
		{
			auto handlerSearch = _clients.find(clientSocket);
			if (handlerSearch == _clients.end())
			{
				throw std::exception("Can't find client's state");
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
					delete handlerSearch->second; // free previous handler
					handlerSearch->second = res.newHandler;
				}
				sendData(clientSocket, res.response);
			}
			else
			{
				// send error message
				ErrorResponse errRes;
				errRes.message = "Request is not relevant to current client state";
				sendData(clientSocket,
					JsonRequestPacketSerializer::serializeResponse(errRes));
			}
		}
	}
	catch (...)
	{
		// TODO: Logout using the login manager here
		std::cerr << "User " << clientSocket << " disconnected." << std::endl;
		auto handlerSearch = _clients.find(clientSocket);
		if (handlerSearch != _clients.end())
		{
			delete handlerSearch->second;
			_clients.erase(clientSocket);
		}
		closesocket(clientSocket);
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
	if(msgSize > 0)
		if (recv(clientSocket, (char*)&req.buffer.at(HEADER_FIELD_LENGTH), msgSize, 0) != msgSize)
		{
			throw std::exception("Packet length is not as expected");
		}
	req.id = (ProtocolCode)req.buffer.at(0);
	req.receivalTime = std::time(0);
	// std::cout << "Client says: " << (char*)&req.buffer.at(0) << std::endl;
	return req;
}

Buffer Communicator::parseErrorMessage(const std::string& errMsg) const
{
	ErrorResponse res;
	res.message = errMsg;
	return JsonRequestPacketSerializer::serializeResponse(res);
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
		for (const auto& pair : _clients)
		{
			// free handlers memory
			delete pair.second;
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
