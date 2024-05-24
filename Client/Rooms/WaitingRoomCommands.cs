using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using static Client.Requests;
using static Client.DataStructs;

namespace Client.Rooms
{
    static class WaitingRoomCommands
    {
        public static bool LeaveRoom(App app)
        {
            var message = Helper.createProtocol(Code.LeaveRoom);

            app._server.sendMessage(message);

            ServerResponse response = Helper.decodeProtocol(app._server.receiveMessage());

            if (response.code == Code.LeaveRoom)
                return GetLeaveRoomResponse(response.message);

            return false;
        }

        public static bool CloseRoom(App app)
        {
            var message = Helper.createProtocol(Code.CloseRoom);

            app._server.sendMessage(message);

            ServerResponse response = Helper.decodeProtocol(app._server.receiveMessage());

            if (response.code == Code.CloseRoom)
            {
                CloseRoomResponse res = JsonPacketDeserializer.DeserializeCloseRoomResponse(response.message);

                if (res.status != 1)
                    return false;
                else
                    return true;
            }

            return false;
        }

        public static long StartGame(App app)
        {
            var message = Helper.createProtocol(Code.StartGame);

            app._server.sendMessage(message);

            ServerResponse response = Helper.decodeProtocol(app._server.receiveMessage());

            if (response.code == Code.StartGame)
                return GetStartGameResponse(response.message);
            

            throw new Exception("Bad response");
        }

        public static ServerResponse GetRoomStateRequest(App app)
        {
            var message = Helper.createProtocol(Code.StartGame);

            app._server.sendMessage(message);

            return Helper.decodeProtocol(app._server.receiveMessage());
        }

        public static RoomState GetRoomStateResponse(string message)
        {
            GetRoomStateResponse res = JsonPacketDeserializer.DeserializeGetRoomStateResponse(message);

            if (res.status != 1)
                throw new Exception("Can't get room data");
            else
                return res.roomState;
        }

        public static long GetStartGameResponse(string message)
        {
            StartGameResponse res = JsonPacketDeserializer.DeserializeStartGameResponse(message);

            if (res.status != 1)
                throw new Exception("Can't start game");
            else
                return res.start_time;
        }

        public static bool GetLeaveRoomResponse(string message)
        {
            LeaveRoomResponse res = JsonPacketDeserializer.DeserializeLeaveRoomResponse(message);

            if (res.status != 1)
                return false;
            else
                return true;
        }
    }
}
