#include "GameRequestHandler.h"
#include "GameRequestHandler.h"
#include "GameRequestHandler.h"

GameRequestHandler::GameRequestHandler(const LoggedUser& user)
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
	_handlerFactory.getLoginManager().logout(_user.getUsername());
}

RequestResult GameRequestHandler::getQuestion(const RequestInfo& reqInfo)
{
	GetQuestionResponse res;
	RequestResult serializedRes;

	Question& question = _game.getQuestionForUser(_user);

	res.question = question.getQuestion();
	res.answers = question.getPossibleAnswers();

	serializedRes.response = JsonResponsePacketSerializer::serializeResponse(res);
	serializedRes.newHandler = nullptr;
	return serializedRes;
}

RequestResult GameRequestHandler::leaveGame(const RequestInfo& reqInfo)
{
	LeaveGameResponse res;
	RequestResult serializedRes;

	try
	{
		_game.removePlayer(_user)
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