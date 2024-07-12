#include "QuestionsRetriever.h"
#include <Windows.h>
#include <wininet.h>
#include <random>
#include <ctime>

#pragma comment(lib, "wininet.lib")

std::vector<Question> QuestionsRetriever::retrieveQuestions(int amount)
{
	static std::time_t lastSentRequestTime = 0;
	std::time_t now = std::time(nullptr);
	if (now - lastSentRequestTime < REQUEST_TIMEOUT_SECONDS)
	{
		// To avoid sending requests to the server often
		throw std::exception("Request timeout");
	}
	lastSentRequestTime = now;
	Buffer requestBuffer = HTTPSRequest(DATABASE_API_URL + std::to_string(amount));
	return deserializeQuestionsJson(requestBuffer, amount);
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

	// to avoid reallocating the buffer in the heap too much, which results to problems
	Byte stackResponseBuffer[INIT_BUFFER_SIZE];
	Buffer response(1); // reserve space for null terminating char
	DWORD bytesRead = 0;
	while (InternetReadFile(hConnect, stackResponseBuffer, INIT_BUFFER_SIZE, &bytesRead) && bytesRead > 0)
	{
		response.resize(response.size() + bytesRead);
		std::memcpy(&response.at(response.size() - bytesRead - 1), stackResponseBuffer, bytesRead);
	}
	response.back() = '\0'; // string terminating NULL char

	InternetCloseHandle(hConnect);
	InternetCloseHandle(hInternet);

	return response;
}

std::vector<Question> QuestionsRetriever::deserializeQuestionsJson(Buffer& buff, int questionAmount)
{
	std::vector<Question> questionsList;
	json questions = json::parse((char*)buff.data());
	if (questions.at(RESPONSE_CODE_JSON) != 0)
	{
		throw std::exception("Server responded with invalid response code");
	}
	for (auto& question : questions.at(RESULTS_JSON))
	{
		int correctAnswerIndex; // gets set by the getAnswers function
		std::vector<std::string> answers = getAnswersFromQuestion(question, correctAnswerIndex);
		parseHTMLString(question.at(QUESTION_STRING_JSON).get_ref<std::string&>());
		for (auto& ans : answers)
			parseHTMLString(ans);
		questionsList.emplace_back(std::move(question.at(QUESTION_STRING_JSON).get_ref<std::string&>()), std::move(answers), correctAnswerIndex);
	}
	return questionsList;
}

std::vector<std::string> QuestionsRetriever::getAnswersFromQuestion(json& question, int& correctAnswerIndex)
{
	/* For randomily organizing the answers.
	 * (Has to be static since all shuffles must have the random same engine) */
	static auto randomEngine = std::default_random_engine();

	std::vector<std::string> answers;
	answers.reserve(ANSWER_AMOUNT);

	correctAnswerIndex = std::rand() % ANSWER_AMOUNT;
	json& correctAnswer = question.at(CORRECT_ANSWER_JSON);

	json& incorrectAnswers = question.at(INCORRECT_ANSWERS_ARRAY_JSON);
	std::shuffle(incorrectAnswers.begin(), incorrectAnswers.end(), randomEngine);

	auto incorrectAnswerIt = incorrectAnswers.begin();
	for (int i = 0; i < ANSWER_AMOUNT; ++i)
	{
		if (i == correctAnswerIndex)
		{
			answers.emplace_back(std::move(correctAnswer));
		}
		else if (incorrectAnswerIt != incorrectAnswers.end())
		{
			answers.emplace_back(std::move(*(incorrectAnswerIt++)));
		}
	}
	return answers;
}

void QuestionsRetriever::parseHTMLString(std::string& str)
{
	static std::unordered_map<std::string, std::string> HTMLToAscii
	{
		{ "&Eacute;", "E" },
		{ "&Aacute;", "A" },
		{ "&quot;",  "\'" },
		{ "&rsquo;",  "\'" },
		{ "&apos;",  "\'" },
		{ "&#34;",   "\'" },
		{ "&#039;",  "\'" },
		{ "&amp;",   "&"  },
		{ "&gt;",    ">"  },
		{ "&lt;",    "<"  },
		{ "&frasl;", "/"  },
		{ "&nbsp;",  " "  },
		{ "&reg;",   ""   },
		{ "&copy;",  ""   }
	};
	for (const auto& [toReplace, replaceWith] : HTMLToAscii)
	{
		auto pos = str.find(toReplace);
		while (pos != std::string::npos)
		{
			str.replace(pos, toReplace.size(), replaceWith);
			pos = str.find(toReplace, pos + replaceWith.size());
		}
	}
}
