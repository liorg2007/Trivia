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
using System.Collections;

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
            JsonDocument document = JsonDocument.Parse(message);
            GetRoomsResponse response = new GetRoomsResponse();

            var roomsArray = document.RootElement.GetProperty("Rooms").EnumerateArray();

            List<RoomData> rooms = new List<RoomData>();

            foreach (var element in roomsArray)
            {
                RoomData roomData  = JsonSerializer.Deserialize<RoomData>(element);

                rooms.Add(roomData);
            }

            response.rooms = rooms;

            return response;
        }
        
        public static GetUsersInRoomResponse DeserializeGetUsersInRoomsRequests(string message)
        {
            return JsonSerializer.Deserialize<GetUsersInRoomResponse>(message);
        }

        public static JoinRoomResponse DeserializeJoinRoomResponse(string message)
        {
            return JsonSerializer.Deserialize<JoinRoomResponse>(message);
        }

        public static LeaveRoomResponse DeserializeLeaveRoomResponse(string message)
        {
            return JsonSerializer.Deserialize<LeaveRoomResponse>(message);
        }

        public static CloseRoomResponse DeserializeCloseRoomResponse(string message)
        {
            return JsonSerializer.Deserialize<CloseRoomResponse>(message);
        }

        public static StartGameResponse DeserializeStartGameResponse(string message)
        {
            return JsonSerializer.Deserialize<StartGameResponse>(message);
        }


        public static GetRoomStateResponse DeserializeGetRoomStateResponse(string message)
        {
            JsonDocument document = JsonDocument.Parse(message);
            JsonElement rootElement = document.RootElement;
            GetRoomStateResponse res = new GetRoomStateResponse();
            RoomState roomState = new RoomState();
            roomState.players = new List<string>();

            res.status = rootElement[0][1].GetUInt32();

            JsonElement roomStateData = rootElement[1];
            foreach (var element in roomStateData.EnumerateArray())
            {
                if (element.ValueKind == JsonValueKind.Array)
                {
                    string propertyName = element[0].GetString();
                    switch (propertyName)
                    {
                        case "hasGameBegun":
                            roomState.hasGameBegun = element[1].GetBoolean();
                            break;
                        case "players":
                            foreach(var player in element[1].EnumerateArray())  
                                roomState.players.Add(player.GetString());
                            break;
                        case "answerCount":
                            roomState.answerCount = element[1].GetUInt32();
                            break;
                        case "answerTimeout":
                            roomState.answerTimeout = element[1].GetUInt32();
                            break;

                    }
                }

            }

            res.roomState = roomState;

            return res;
        }
        public static SubmitAnswerResponse DeserializeSubmitAnswerResponse(string message)
        {
            return JsonSerializer.Deserialize<SubmitAnswerResponse>(message);
        }
        public static GetQuestionResponse DeserializeGetQuestionResponse(string message)
        {
            return JsonSerializer.Deserialize<GetQuestionResponse>(message);
        }
        public static GetGameResultsResponse DeserializeGetGameResultsResponse(string message)
        {
            return JsonSerializer.Deserialize<GetGameResultsResponse>(message);
        }
    }
}
