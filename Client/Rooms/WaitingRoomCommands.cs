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
                {
                    return true;
                }
            }

            return false;
        }
    }
}
