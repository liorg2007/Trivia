using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Text.Json;
using System.Threading.Tasks;
using static Client.Requests;
using static Client.Helper;

namespace Client.Menu
{
    internal static class RoomManagement
    {
        public static byte[] CreateCreateRoomRequest(CreateRoomRequest request)
        {
            string json = JsonSerializer.Serialize(request);
            return Helper.createProtocol(json, (int)Codes.CreateRoom);
        }

        public static byte[] CreateGetRoomsRequests()
        {
            return Helper.createProtocol("", (int)Codes.GetRooms);
        }
    }
}
