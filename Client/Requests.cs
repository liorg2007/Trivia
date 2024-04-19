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


        public class LoginRequest
        {
            public string username { get; set; }
            public string password { get; set; }
        }
    }
}
