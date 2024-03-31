#pragma once
#include "Communicator.h"

class Server {
private:
	Communicator _communicator;
	std::thread* _communicatorThread;

public:
	Server();

	~Server();

	void run();
};