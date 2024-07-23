#pragma once
#pragma comment(lib, "ws2_32.lib")
#include <optional>
#include <WinSock2.h>
#include <Windows.h>
#include <unordered_map>
#include <thread>
#include <iostream>
#include "Constants.h"
#include "IRequestHandler.h"
#include "LoginRequestHandler.h"
#include "RequestHandlerFactory.h"
#include "AESCryptoAlgorithm.h"

typedef std::unordered_map<SOCKET, std::unique_ptr<IRequestHandler>>::iterator map_iterator;

class Communicator {
private:
	SOCKET _serverSocket;
	RequestHandlerFactory& _handlerFactory;

	std::unordered_map<SOCKET, std::unique_ptr<IRequestHandler>> _clients;
	std::unordered_map<SOCKET, KeyAndIv> _clientKeys;

	mutable std::shared_mutex _clientKeysMtx;
	
	std::vector<std::thread*> _threadPool;

	const int _PORT = 6969;

	/* Initialize listening socket for the server */
	void bindAndListen();
	void acceptClients();

	/* handles a client socket */
	void handleNewClient(SOCKET clientSocket);

	void sendData(SOCKET clientSocket, const Buffer& buff) const;
	void sendEncryptedData(SOCKET clientSocket, const Buffer& buff) const;

	RequestInfo receiveData(SOCKET clientSocket) const;
	RequestInfo receiveEncryptedData(SOCKET clientSocket) const;
	RequestInfo receiveRegularData(SOCKET clientSocket) const;
	Buffer parseErrorMessage(std::string&& errMsg) const;

	void terminateConnection(SOCKET clientSocket, const std::optional<map_iterator>& handlerSearchResult);

	Communicator();
public:
	static Communicator& getInstance();

	/* Free used memory in the end (if needed)*/
	~Communicator();

	/* starts handling the client requests */
	void startHandleRequests();

	void addEncryptionToClient(SOCKET clientSocket, const KeyAndIv& keyAndIv);

	Communicator(Communicator&) = delete;
	void operator=(const Communicator&) = delete;
};