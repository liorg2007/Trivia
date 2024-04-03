#pragma once
#include "Communicator.h"

class Server {
private:
	Communicator _communicator;

public:
	Server();

	void run();
};