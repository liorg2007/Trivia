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

RequestResult GameRequestHandler::leaveGame(const RequestInfo& reqInfo)
{

	return RequestResult();
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