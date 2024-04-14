#include "QuestionsRetriever.h"
#include <Windows.h>

std::vector<Question> QuestionsRetriever::retrieveQuestions()
{
	std::vector<Question> ans;
	// Buffer httpBuffer = httpRequest("www.opentdb.com", "/api.php?amount=10&type=multiple");
	return ans;
}

// opentdb probably only uses HTTPS, so we will might have to replace this function
Buffer QuestionsRetriever::httpRequest(const std::string& urlHost, const std::string& urlParams)
{
	SOCKET s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	SOCKADDR_IN SockAddr;
	struct hostent* host;

	//HTTP GET
	std::string get_http = "GET /" + urlParams + "HTTP / 1.1\r\nHost: " + urlHost + "\r\nConnection: close\r\n\r\n";

	host = gethostbyname(urlHost.c_str());

	SockAddr.sin_port = htons(HTTP_PORT);
	SockAddr.sin_family = AF_INET;
	SockAddr.sin_addr.s_addr = *((unsigned long*)host->h_addr);

	if (connect(s, (SOCKADDR*)(&SockAddr), sizeof(SockAddr)) != 0)
	{
		throw std::exception("Couldn't retrieve trivia questions to database");
	}

	// send GET / HTTP
	send(s, get_http.c_str(), strlen(get_http.c_str()), 0);


	int currSize = 0;
	Buffer buff(INIT_BUFFER_SIZE);
	// recieve html
	while (recv(s, (char*)buff.at(currSize), INIT_BUFFER_SIZE, 0) > 0) {
		currSize += INIT_BUFFER_SIZE;
		buff.resize(currSize);
	}

	closesocket(s);
	return buff;
}
