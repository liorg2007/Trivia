#include "Server.h"
#include "WSAInitializer.h"
#include "JsonRequestPacketDeserializer.h"
#include "JsonResponsePacketSerializer.h"
#include "QuestionsRetriever.h"

#include "time.h"

int main()
{
	std::srand(std::time(nullptr)); // For randomly generating numbers using std::rand()
	WSAInitializer wsaInit;
	auto a = QuestionsRetriever::retrieveQuestions(5);
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