#pragma once
#include <string>
#include <vector>

class Question
{
public:
	Question(std::string&& question, std::vector<std::string>&& answers, int correctAnsId);

	const std::string& getQuestion() const;
	const std::vector<std::string>& getPossibleAnswers() const;
	int getCorrectAnswerId() const;
	
private:
	std::string _question;
	std::vector<std::string> _possibleAnswers;
	int _correctAnswerId;
};

