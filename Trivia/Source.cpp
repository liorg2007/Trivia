#include "Server.h"
#include "WSAInitializer.h"
#include "JsonRequestPacketDeserializer.h"
#include "JsonRequestPacketSerializer.h"
#include "QuestionsRetriever.h"

int main()
{
	QuestionsRetriever::retrieveQuestions();
	/*WSAInitializer wsaInit;
	Server& server = Server::getInstance();
	
	server.run();

	system("PAUSE");*/
	return 0;
}