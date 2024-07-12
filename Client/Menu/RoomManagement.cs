using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Text.Json;
using System.Threading.Tasks;
using static Client.Requests;

namespace Client.Menu
{
    internal static class RoomManagement
    {
        public static byte[] CreateCreateRoomRequest(CreateRoomRequest request)
        {
            var json = JsonSerializer.SerializeToUtf8Bytes(request);
            return Helper.createProtocol(Code.CreateRoom, json);
        }

        public static byte[] CreateGetRoomsRequests()
        {
            return Helper.createProtocol(Code.GetRooms);
        }

        public static byte[] CreateGetUsersInRoomsRequests(GetUsersInRoomRequest request)
        {
            var json = JsonSerializer.SerializeToUtf8Bytes(request);
            return Helper.createProtocol(Code.GetPlayersInRoom, json);
        }

        public static byte[] CreateJoinRoomRequests(JoinRoomRequest request)
        {
            var json = JsonSerializer.SerializeToUtf8Bytes(request);
            return Helper.createProtocol(Code.JoinRoom, json);
        }
    }
}
