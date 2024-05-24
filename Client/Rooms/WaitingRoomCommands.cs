using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using static Client.Requests;

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
            {
                LeaveRoomResponse res = JsonPacketDeserializer.DeserializeLeaveRoomResponse(response.message);

                if (res.status != 1)
                    return false;
                else
                    return true;
            }

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
            {
                StartGameResponse res = JsonPacketDeserializer.DeserializeStartGameResponse(response.message);

                if (res.status != 1)
                    throw new Exception("Can't start game");
                else
                    return res.start_time;
            }

            throw new Exception("Bad response");
        }
    }
}
