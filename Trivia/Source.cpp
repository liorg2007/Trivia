#include "Server.h"
#include "WSAInitializer.h"
#include "JsonRequestPacketDeserializer.h"
#include "JsonRequestPacketSerializer.h"

int main()
{
	WSAInitializer wsaInit;
	Server& server = Server::getInstance();

	std::vector<std::pair<std::string, int>> highscores;
	highscores.emplace_back(std::make_pair("nigga", 2323));
	highscores.emplace_back(std::make_pair("nidsadsa", 2322323));

	GetHighScoreResponse res;
	res.status = 0;
	res.highScores = highscores;
	auto a =JsonRequestPacketSerializer::serializeResponse(res);
	std::cout << (char*)a.data()[HEADER_FIELD_LENGTH] << std::endl;
	server.run();

	system("PAUSE");
	return 0;
}