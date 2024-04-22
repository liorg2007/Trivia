using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using static Client.Requests;
using System.Text.Json;
using static Client.DataStructs;

namespace Client
{
    internal static class JsonPacketDeserializer
    {
        public static LoginResponse DeserializeLoginResponse(string message)
        {
            return JsonSerializer.Deserialize<LoginResponse>(message);
        }

        public static SignupResponse DeserializeSignupResponse(string message)
        {
            return JsonSerializer.Deserialize<SignupResponse>(message);
        }

        public static UserStatistics DeserializeStatsResponse(string message)
        {
            return JsonSerializer.Deserialize<UserStatistics>(message);
        }
    }
}
