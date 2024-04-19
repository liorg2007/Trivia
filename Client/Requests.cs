using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Client
{
    internal static class Requests
    {
        public enum Codes {
            Login
        }

        public struct ServerResponse
        {
            public uint code;
            public string message;
        }


        public struct LoginRequest
        {
            public string username;
            public string password;
        }

        public struct LoginResponse
        {
            public uint code;
        }
        
    }
}
