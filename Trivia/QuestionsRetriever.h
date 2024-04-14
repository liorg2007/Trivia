#pragma once
#include "SqliteDatabase.h"
#include "Question.h"
#include "Constants.h"

class QuestionsRetriever
{
public:
	static std::vector<Question> retrieveQuestions();
private:
	static Buffer httpRequest(const std::string& urlHost, const std::string& urlParams);

	static constexpr auto INIT_BUFFER_SIZE = 1024;
	static constexpr auto HTTP_PORT = 80;
};