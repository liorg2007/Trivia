#pragma once
#include "Communicator.h"
#include "IDatabase.h"
#include "RequestHandlerFactory.h"

class Server {
private:
	IDatabase* _database;
	RequestHandlerFactory& _handlerFactory;
	Communicator& _communicator;

	Server();
public:
	static Server& getInstance();

	void run();

	Server(Server&) = delete;
	void operator=(const Server&) = delete;
};