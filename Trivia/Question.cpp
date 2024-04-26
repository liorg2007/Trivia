#include "Question.h"

Question::Question(std::string&& question, std::vector<std::string>&& answers, int correctAnsId)
    : _question(std::move(question)), _possibleAnswers(std::move(answers)), _correctAnswerId(correctAnsId)
{
}

const std::string& Question::getQuestion() const
{
    return _question;
}

const std::vector<std::string>& Question::getPossibleAnswers() const
{
    return _possibleAnswers;
}

int Question::getCorrectAnswerId() const
{
    return _correctAnswerId;
}
