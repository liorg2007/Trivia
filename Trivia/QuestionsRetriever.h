#pragma once
#include "SqliteDatabase.h"
#include "Question.h"
#include "Constants.h"
#include "json.hpp"

using json = nlohmann::json;

class QuestionsRetriever
{
public:
	static std::forward_list<Question> retrieveQuestions(int amount);
private:
	static Buffer HTTPSRequest(const std::string& url);
	static std::forward_list<Question> deserializeQuestionsJson(Buffer& buff, int questionAmount);
	static std::vector<std::string> getAnswersFromQuestion(json& question, int& correctAnswerIndex);
	
	static constexpr auto ANSWER_AMOUNT = 4;

	/* HTTPS constants */
	static constexpr auto DATABASE_API_URL = "https://www.opentdb.com/api.php?type=multiple&amount=";
	static constexpr auto INIT_BUFFER_SIZE = 1024;

	/* JSON Headers for the opentdb api */
	static constexpr auto RESPONSE_CODE_JSON = "response_code";
	static constexpr auto RESULTS_JSON = "results";
	static constexpr auto CORRECT_ANSWER_JSON = "correct_answer";
	static constexpr auto INCORRECT_ANSWERS_ARRAY_JSON = "incorrect_answers";
	static constexpr auto QUESTION_STRING_JSON = "question";

};
