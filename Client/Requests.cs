using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using static Client.DataStructs;

namespace Client
{
    internal static class Requests
    {
        public enum Codes
        {
            Login,
            Signup,
            Logout,
            CreateRoom,
            JoinRoom,
            GetRooms,
            GetPlayersInRoom,
            HighScores,
            Stats
        }

        public struct ServerResponse
        {
            public uint code;
            public string message;
        }

        public struct LoginRequest
        {
            public string username { get; set; }
            public string password { get; set; }
        }

        public struct LoginResponse
        {
            public int status { get; set; }
        }

        public struct SignupRequest
        {
            public string username { get; set; }
            public string password { get; set; }
            public string email { get; set; }
            public string address { get; set; }
            public string phoneNumber { get; set; }
            public string birthDate { get; set; }
        }

        public struct SignupResponse
        {
            public int status { get; set; }
        }

        public struct StatsRequest
        {
            public uint code { get; set; }
        }

        public struct StatsResponse
        {
            public UserStatistics statistics { get; set; }
        }

        public struct LogoutRequest
        {
            public uint code { get; set; }
        }

        public struct LogoutResponse
        {
            public uint status { get; set; }
        }

        public struct CreateRoomRequest
        {
            public string roomName { get; set; }
            public uint maxUsers { get; set; }
            public uint questionCount { get; set; }
            public uint answerTimeout { get; set; }
        }

        public struct CreateRoomResponse
        {
            public uint status { get; set; }
        }


        public struct GetRoomsResponse
        {
            public List<RoomData> rooms { get; set; }
        }

        public struct GetUsersInRoomRequest
        {
            public uint roomId { get; set; }
        }

        public struct GetUsersInRoomResponse
        {
            public List<string> PlayersInRoom { get; set; }
        }

        public struct JoinRoomRequest
        {
            public uint roomId { get; set; }
        }

        public struct JoinRoomResponse
        {
            public uint status { get; set; }
        }
    }
}
