#include "BaseRoomRequestHandler.h"
#include "Responses.h"
#include "JsonResponsePacketSerializer.h"
#include "RequestHandlerFactory.h"

BaseRoomRequestHandler::BaseRoomRequestHandler(int roomId, const LoggedUser& user)
	: _roomId(roomId), _user(user), _roomManager(RoomManager::getInstance()), _handlerFactory(RequestHandlerFactory::getInstance()), _roomRef(RoomManager::getInstance().getRoom(roomId))
{
}

RequestResult BaseRoomRequestHandler::getRoomState() const
{
  RequestResult result;
  std::variant<GetRoomStateResponse, LeaveRoomResponse, StartGameResponse> res;

  try 
  {
    GetRoomStateResponse roomStateRes;
    roomStateRes.roomState = _roomManager.getRoomState(_roomId);

    if (roomStateRes.roomState.hasGameBegun) 
    {
      // The game has started
      StartGameResponse startGameRes;
      startGameRes.startTime = _roomRef.getRoomData().startTime;
      res = startGameRes;

      result.newHandler = _handlerFactory.createGameRequestHandler(_user, GameManager::getInstance().getGame(_roomId));
      _roomRef.removeUser(_user);
    }
    else 
    {
      // Room hasn't started or closed, return a normal GetRoomStateResult
      res = roomStateRes;
      result.newHandler = nullptr;
    }
  }
  catch (...) 
  {
    // Exception: room not found, player needs to leave the room
    LeaveRoomResponse leaveRoomRes;
    res = leaveRoomRes;

    result.newHandler = _handlerFactory.createMenuRequestHandler(_user);
  }

  // Serialize the response
  std::visit([&](auto&& arg) {
    arg.status = SUCCESS;
    result.response = JsonResponsePacketSerializer::serializeResponse(arg);
    }, res);

  return result;
}
