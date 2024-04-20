using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using static Client.Requests;
using static Client.Helper;
using System.Text.Json;
using static Client.JsonPacketDeserializer;
using System.Diagnostics;

namespace Client
{
    internal static class LoginSignup
    {
        public static byte[] CreateLoginRequest(LoginRequest loginRequest)
        {
            string json = JsonSerializer.Serialize(loginRequest);
            return Helper.createProtocol(json, (int)Codes.Login);
        }

        public static bool CheckLogin(ServerResponse response)
        {
            if (response.code == 1)
            {
                LoginResponse res = DeserializeLoginResponse(response.message);
                return res.status == 1;
            }

            throw new Exception("Problem with server");
        }

        public static byte[] CreateSignupRequest(SignupRequest userData)
        {
            string json = JsonSerializer.Serialize(userData);
            return Helper.createProtocol(json, (int)Codes.Signup);
        }
    }
}
