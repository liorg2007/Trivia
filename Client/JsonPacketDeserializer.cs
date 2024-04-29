﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using static Client.Requests;
using System.Text.Json;
using static Client.DataStructs;
using Client.Menu;
using System.Security.RightsManagement;

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

        public static TopPlayers DeserializeHighScoresResponse(string message)
        {
            JsonDocument document = JsonDocument.Parse(message);

            var highScoresArray = document.RootElement.GetProperty("HighScores").EnumerateArray();

            List<Tuple<string, int>> highScoresList = new List<Tuple<string, int>>();

            foreach (var element in highScoresArray)
            {
                JsonElement nameElement = element[0];
                JsonElement scoreElement = element[1];

                string name = nameElement.GetString();
                int score = scoreElement.GetInt32();

                highScoresList.Add(new Tuple<string, int>(name, score));
            }

            TopPlayers topPlayers = new TopPlayers();
            topPlayers.bestScores = highScoresList;

            return topPlayers;
        }

        public static CreateRoomResponse DeserializeCreateRoomResponseResponse(string message)
        {
            return JsonSerializer.Deserialize<CreateRoomResponse>(message);
        }

        public static GetRoomsResponse DeserializeGetRoomsResponse(string message)
        {

        }
    }
}
