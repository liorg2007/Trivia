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
            JsonDocument document = JsonDocument.Parse(message);
            JsonElement rootElement = document.RootElement;

            UserStatistics stats = new UserStatistics();

            if (rootElement.ValueKind == JsonValueKind.Array && rootElement.GetArrayLength() > 0)
            {
                JsonElement statsArray = rootElement[0];

                foreach (JsonElement element in statsArray.EnumerateArray())
                {
                    if (element.ValueKind == JsonValueKind.Array && element.GetArrayLength() == 2)
                    {
                        string propertyName = element[0].GetString();
                        JsonElement propertyValue = element[1];

                        switch (propertyName)
                        {
                            case "score":
                                stats.score = propertyValue.GetInt32();
                                break;
                            case "averageAnswerTime":
                                stats.averageAnswerTime = propertyValue.GetDouble();
                                break;
                            case "correctAnswers":
                                stats.correctAnswers = propertyValue.GetInt32();
                                break;
                            case "totalAnswers":
                                stats.totalAnswers = propertyValue.GetInt32();
                                break;
                        }
                    }
                }
            }

            return stats;
        }

        public static LogoutResponse DeserializeLogoutResponse(string message)
        {
            return JsonSerializer.Deserialize<LogoutResponse>(message);
        }
    }
}
