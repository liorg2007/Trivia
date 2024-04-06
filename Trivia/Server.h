#pragma once
#include "Communicator.h"
#include "IDatabase.h"
#include "RequestHandlerFactory.h"

class Server {
private:
	IDatabase* _database;
	RequestHandlerFactory& _handlerFactory;
	Communicator& _communicator;

public:
	Server();

	void run();
};