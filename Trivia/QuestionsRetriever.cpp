#include "QuestionsRetriever.h"
#include <Windows.h>
#include <wininet.h>

#pragma comment(lib, "wininet.lib")

std::vector<Question> QuestionsRetriever::retrieveQuestions()
{
	std::vector<Question> ans;
	Buffer httpBuffer = HTTPSRequest("https://www.opentdb.com/api.php?amount=10&type=multiple");
	
	return ans;
}

Buffer QuestionsRetriever::HTTPSRequest(const std::string& url)
{
	HINTERNET hInternet = InternetOpen(L"HTTPS Request", INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);
	if (!hInternet) {
		throw std::exception("InternetOpen failed");
	}

	HINTERNET hConnect = InternetOpenUrlA(hInternet, url.c_str(), NULL, 0, INTERNET_FLAG_SECURE, 0);
	if (!hConnect) {
		InternetCloseHandle(hInternet);
		throw std::exception("InternetOpenUrl failed");
	}

	Buffer response(INIT_BUFFER_SIZE);
	DWORD curr = 0;
	DWORD bytesRead;
	while (InternetReadFile(hConnect, &response.data()[curr], INIT_BUFFER_SIZE, &bytesRead) && bytesRead > 0) {
		curr += INIT_BUFFER_SIZE;
		response.resize(curr + INIT_BUFFER_SIZE);
	}

	InternetCloseHandle(hConnect);
	InternetCloseHandle(hInternet);

	return response;
}

json QuestionsRetriever::deserializeQuestionsJson(const Buffer& buff)
{
	return json();
}
