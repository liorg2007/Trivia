#include "GameRequestHandler.h"

GameRequestHandler::GameRequestHandler(const LoggedUser& user, Game& game)
	:_handlerFactory(RequestHandlerFactory::getInstance()), _gameManager(RequestHandlerFactory::getInstance().getGameManager()), _user(user), _game(game)
{
}

bool GameRequestHandler::isRequestRelevant(const RequestInfo& reqInfo)
{
	return reqInfo.id == ProtocolCode::GetQuestion
		|| reqInfo.id == ProtocolCode::SubmitAnswer
		|| reqInfo.id == ProtocolCode::GetGameResults
		|| reqInfo.id == ProtocolCode::LeaveGame;
}

void GameRequestHandler::handleDisconnect()
{
	//Don't remove from room because stats of player should be shown in the end
	_game.removePlayer(_user);
	_handlerFactory.getLoginManager().logout(_user.getUsername());
}

RequestResult GameRequestHandler::getQuestion(const RequestInfo& reqInfo)
{
	GetQuestionResponse res;
	RequestResult serializedRes;

	std::shared_ptr<Question> question = _game.getQuestionForUser(_user).value_or(nullptr);

	res.status = SUCCESS;
	res.question = question->getQuestion();
	res.answers = question->getPossibleAnswers();

	serializedRes.response = JsonResponsePacketSerializer::serializeResponse(res);
	serializedRes.newHandler = nullptr;
	return serializedRes;
}

RequestResult GameRequestHandler::submitAnswer(const RequestInfo& reqInfo)
{
	SubmitAnswerResponse res;
	RequestResult serializedRes;

	auto answer = JsonRequestPacketDeserializer::deserializeSubmitAnswerRequest(reqInfo.buffer);
	res.isCorrect = _game.submitAnswer(_user, answer.answerId);

	res.status = SUCCESS;
	serializedRes.response = JsonResponsePacketSerializer::serializeResponse(res);
	serializedRes.newHandler = nullptr;
	return serializedRes;
}

RequestResult GameRequestHandler::getGameResults(const RequestInfo& reqInfo)
{
	GetGameResultsResponse res;
	RequestResult serializedRes;
	std::list<PlayerResults> results;
	GameDetails gameDetails = _game.getGameDetails();

	if (std::time(nullptr) - gameDetails.answerCount * gameDetails.answerTimeout > gameDetails.gameStartTime) //if user requests game results before game finished
	{
		res.status = FAILURE;
		serializedRes.newHandler = nullptr;
	}
	else
	{
		PlayerResults result;

		for (const auto& gameStat : *_game.getPlayersStats())
		{
			int totalAnswered = gameStat.second.correctAnswerCount + gameStat.second.wrongAnswerCount;
			result.username = gameStat.first; //username
			result.wrongAnswerCount = gameDetails.answerCount - gameStat.second.correctAnswerCount; //also satisfies case where user didnt answer everything
			result.correctAnswerCount = gameStat.second.correctAnswerCount; //all users correct answers
			
			if (totalAnswered < gameDetails.answerCount) //if user didnt answer all, add the full time of questions didnt answered to average time
			{
				time_t answeredTime = gameStat.second.averageAnswerTime * totalAnswered; //avg = answeredTime / totalAnswered. answeredTime = avg * totalAnswered
				time_t totalTime = answeredTime + gameDetails.answerTimeout * (gameDetails.answerCount - totalAnswered); //totalTime = already Answred Time + (answer Timeout * not answered)

				result.averageAnswerTime = totalTime / gameDetails.answerCount;
			}
			else
			{
				result.averageAnswerTime = gameStat.second.averageAnswerTime;
			}

			//add the result to the list
			results.push_back(result);
		}

		res.results = results;
		res.status = SUCCESS;
		serializedRes.newHandler = _handlerFactory.createMenuRequestHandler(_user);
	}

	serializedRes.response = JsonResponsePacketSerializer::serializeResponse(res);
	return serializedRes;
}

RequestResult GameRequestHandler::leaveGame(const RequestInfo& reqInfo)
{
	LeaveGameResponse res;
	RequestResult serializedRes;

	try
	{
		_game.removePlayer(_user);
		res.status = SUCCESS;
	}
	catch (...) {} // either way will leave the room, no need to return FAILURE status
	serializedRes.response = JsonResponsePacketSerializer::serializeResponse(res);
	serializedRes.newHandler = _handlerFactory.createMenuRequestHandler(_user);
	return serializedRes;
}

RequestResult GameRequestHandler::handleRequest(const RequestInfo& reqInfo)
{
	if (reqInfo.id == ProtocolCode::GetQuestion)
		return getQuestion(reqInfo);
	else if (reqInfo.id == ProtocolCode::SubmitAnswer)
		return submitAnswer(reqInfo);
	else if (reqInfo.id == ProtocolCode::GetGameResults)
		return getGameResults(reqInfo);
	else
		return leaveGame(reqInfo);
}