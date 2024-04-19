using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using static Client.Requests;
using static Client.Helper;
using System.Text.Json;

namespace Client
{
    internal static class LoginSignup
    {
        public static byte[] CreateLoginRequest(string username, string password)
        {
            LoginRequest loginRequest = new LoginRequest()
            {
                username = username,
                password = password
        };

            string json = JsonSerializer.Serialize(loginRequest);
            return Helper.createProtocol(json, (int)Codes.Login);
        }
    }
}
