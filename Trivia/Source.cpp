#include "Server.h"
#include "WSAInitializer.h"
#include "JsonRequestPacketDeserializer.h"
#include "JsonResponsePacketSerializer.h"
#include "QuestionsRetriever.h"

#include "time.h"
#include "AESCryptoAlgorithm.h"
#include "aes.h"

int main()
{
	Buffer key(CryptoPP::AES::DEFAULT_KEYLENGTH);
	std::string message("test");
	Buffer m(message.begin(), message.end());

	AESCryptoAlgorithm().encrypt(m, key);
	/*
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
	return 0;*/
}