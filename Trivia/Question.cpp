#include "Question.h"

Question::Question(const std::string& question, const std::vector<std::string>& answers, int correctAnsId)
    : _question(question), _possibleAnswers(answers), _correctAnswerId(correctAnsId)
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
