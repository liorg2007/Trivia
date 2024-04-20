#pragma once
#include "SqliteDatabase.h"
#include "Question.h"
#include "Constants.h"
#include "json.hpp"

using json = nlohmann::json;

class QuestionsRetriever
{
public:
	static std::vector<Question> retrieveQuestions();
private:
	static Buffer HTTPSRequest(const std::string& url);
	static std::vector<Question> deserializeQuestionsJson(const Buffer& buff);

	static constexpr auto INIT_BUFFER_SIZE = 1024;
};