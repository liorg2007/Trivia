#pragma once
#include "Communicator.h"

class Server {
private:
	Communicator _communicator;
	std::thread* _commThread;

public:
	Server();

	void run();
};