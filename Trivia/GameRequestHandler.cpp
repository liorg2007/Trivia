#include "GameRequestHandler.h"

GameRequestHandler::GameRequestHandler(const LoggedUser& user, Game& game)
	: _handlerFactory(RequestHandlerFactory::getInstance()),
	_gameManager(RequestHandlerFactory::getInstance().getGameManager()), _user(user),
	_game(game), _hasGameStarted(false)
{
}

bool GameRequestHandler::isRequestRelevant(const RequestInfo& reqInfo)
{
	if (!_hasGameStarted)
	{
		// to avoid calling std::time many times
		_hasGameStarted = (_game.getGameDetails().gameStartTime <= std::time(nullptr));
	}
	return (reqInfo.id == ProtocolCode::GetQuestion
		|| reqInfo.id == ProtocolCode::SubmitAnswer
		|| reqInfo.id == ProtocolCode::GetGameResults
		|| reqInfo.id == ProtocolCode::LeaveGame) && _hasGameStarted;
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

	try {
		Question& question = _game.getQuestionForUser(_user);

		res.status = SUCCESS;
		res.question = question.getQuestion();
		res.answers = question.getPossibleAnswers();
	}
	catch (...) //getQuestionForUser fails
	{
		res.status = FAILURE;
	}

	serializedRes.response = JsonResponsePacketSerializer::serializeResponse(res);
	serializedRes.newHandler = nullptr;
	return serializedRes;
}

RequestResult GameRequestHandler::submitAnswer(const RequestInfo& reqInfo)
{
	SubmitAnswerResponse res;
	RequestResult serializedRes;

	auto answer = JsonRequestPacketDeserializer::deserializeSubmitAnswerRequest(reqInfo.buffer);
	res.correctAnswerId = _game.submitAnswer(_user, answer.answerId);

	res.status = SUCCESS;
	serializedRes.response = JsonResponsePacketSerializer::serializeResponse(res);
	serializedRes.newHandler = nullptr;
	return serializedRes;
}

RequestResult GameRequestHandler::getGameResults(const RequestInfo& reqInfo)
{
	GetGameResultsResponse res;
	RequestResult serializedRes;
	const GameDetails& gameDetails = _game.getGameDetails();

	if (!_game.isGameFinished()) //if user requests game results before game finished
	{
		res.status = FAILURE;
		serializedRes.newHandler = nullptr;
	}
	else
	{
		try
		{
			res.results = _game.getPlayersStats();
			_game.removePlayer(_user);
			res.status = SUCCESS;
			serializedRes.newHandler = _handlerFactory.createMenuRequestHandler(_user);
		}
		catch (const std::exception& ex)
		{
			res.status = FAILURE;
			serializedRes.newHandler = nullptr;
		}
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
	}
	catch (...) {} // either way will leave the room, no need to return FAILURE status

	res.status = SUCCESS;
	serializedRes.response = JsonResponsePacketSerializer::serializeResponse(res);
	serializedRes.newHandler = _handlerFactory.createMenuRequestHandler(_user);
	return serializedRes;
}

RequestResult GameRequestHandler::handleRequest(const RequestInfo& reqInfo)
{
	switch (reqInfo.id)
	{
	case ProtocolCode::GetQuestion:
		return getQuestion(reqInfo);
	case ProtocolCode::SubmitAnswer:
		return submitAnswer(reqInfo);
	case ProtocolCode::GetGameResults:
		return getGameResults(reqInfo);
	default:
		return leaveGame(reqInfo);
	}
}
