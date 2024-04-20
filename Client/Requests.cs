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
            Login,
            Signup
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
    }
}
