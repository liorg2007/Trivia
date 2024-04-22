#include "QuestionsRetriever.h"
#include <Windows.h>
#include <wininet.h>
#include <random>

#pragma comment(lib, "wininet.lib")

std::vector<Question> QuestionsRetriever::retrieveQuestions(int amount)
{
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

	Buffer response(INIT_BUFFER_SIZE);
	DWORD currBytesRead = 0;
	DWORD lastBytesRead = 0;
	while (InternetReadFile(hConnect, &response.at(response.size() - INIT_BUFFER_SIZE), INIT_BUFFER_SIZE, &currBytesRead) && currBytesRead > 0) {
		response.resize(response.size() + INIT_BUFFER_SIZE);
		lastBytesRead = currBytesRead;
	}
	// trim the buffer size (+1 to save space for the string terminating NULL char)
	response.resize(response.size() - INIT_BUFFER_SIZE * 2 + lastBytesRead + 1);
	response.back() = '\0'; // string terminating NULL char

	InternetCloseHandle(hConnect);
	InternetCloseHandle(hInternet);

	return response;
}

std::vector<Question> QuestionsRetriever::deserializeQuestionsJson(Buffer& buff, int questionAmount)
{
	std::vector<Question> questionsVec;
	questionsVec.reserve(questionAmount);
	try
	{
		json questions = json::parse((char*)buff.data());
		if (questions.at(RESPONSE_CODE_JSON) != 0)
		{
			throw std::runtime_error("Server responded with invalid response code");
		}
		for (auto& question : questions.at(RESULTS_JSON))
		{
			int correctAnswerIndex; // gets set by the getAnswers function
			auto answers = getAnswersFromQuestion(question, correctAnswerIndex);
			questionsVec.emplace_back(std::move(question.at(QUESTION_STRING_JSON)), std::move(answers), correctAnswerIndex);
		}
	}
	catch (const json::exception& e)
	{
		throw std::runtime_error("Error while parsing json: " + std::string(e.what()));
	}
	return questionsVec;
}

std::vector<std::string> QuestionsRetriever::getAnswersFromQuestion(json& question, int& correctAnswerIndex)
{
	/* For randomily organizing the answers.
	 * (Has to be static since all shuffles must have the random same engine) */
	static auto randomEngine = std::default_random_engine();
	static std::uniform_int_distribution<> randomAnswerIndexGenerator(0, ANSWER_AMOUNT - 1);

	std::vector<std::string> answers;
	answers.reserve(ANSWER_AMOUNT);

	correctAnswerIndex = randomAnswerIndexGenerator(randomEngine);
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
