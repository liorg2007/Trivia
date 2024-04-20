#include "QuestionsRetriever.h"
#include <Windows.h>
#include <wininet.h>

#pragma comment(lib, "wininet.lib")

std::vector<Question> QuestionsRetriever::retrieveQuestions()
{
	Buffer requestBuffer = HTTPSRequest("https://www.opentdb.com/api.php?amount=10&type=multiple");
	return deserializeQuestionsJson(requestBuffer);
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
		curr += bytesRead;
		response.resize(curr + bytesRead);
	}
	response.resize(curr + 1); // + 1 for the string terminating NULL char
	response.push_back(0);

	InternetCloseHandle(hConnect);
	InternetCloseHandle(hInternet);

	return response;
}

std::vector<Question> QuestionsRetriever::deserializeQuestionsJson(const Buffer& buff)
{
	std::vector<Question> questionsVec;
	std::cout << (char*)buff.data() << std::endl;
	try
	{
		json questions = json::parse((char*)buff.data());
		if (questions.at("response_code") != 0)
		{
			throw std::runtime_error("Server responded with invalid response code");
		}
		for (auto& question : questions.at("results"))
		{
			std::vector<std::string> answers;
			answers.push_back(std::move(question.at("correct_answer")));
			for (auto& incorrect_answer : question.at("incorrect_answers"))
			{
				answers.push_back(std::move(incorrect_answer));
			}
			questionsVec.emplace_back(std::move(question.at("question")), std::move(answers), 0);
		}
	}
	catch (const json::exception& e)
	{
		throw std::runtime_error("Error while parsing json: " + std::string(e.what()));
	}
	return questionsVec;
}
