#include "Server.h"
#include "WSAInitializer.h"

#include "RSACryptoAlgorithm.h"

int main()
{
	std::srand(std::time(nullptr)); // For randomly generating numbers using std::rand()
	WSAInitializer wsaInit;
	try
	{
		Server& server = Server::getInstance();
		server.run();
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << "\n";
	}

	system("PAUSE");
	return 0;
}