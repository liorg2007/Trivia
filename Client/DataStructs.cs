using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Client
{
    public static class DataStructs
    {
        public struct UserStatistics
        {
            public int score { get; set; }
            public double averageAnswerTime { get; set; }
            public int correctAnswers { get; set; }
            public int totalAnswers { get; set; }
        }

        public struct TopPlayers
        {
            public List<Tuple<string, int>> bestScores;
        }

        public struct RoomData
        {
            public uint id { get; set; }
            public string name { get; set; }
            public uint maxPlayers { get; set; }
            public uint numOfQuestionsInGame { get; set; }
            public uint timerPerQuestion { get; set; }
            public uint isActive { get; set; }
        }

        public struct Room
        {
            public RoomData roomData { get; set; }
            public List<string> players { get; set; }
        }

        public struct RoomState
        {
            public bool hasGameBegun { get; set; }
            public List<string> players { get; set; }
            public uint answerCount { get; set; }
            public uint answerTimeout { get; set; }
        }

        public struct PlayerResults
        {
            public string username { get; set; }
            public uint correctAnswerCount { get; set; }
            public uint wrongAnswerCount { get; set; }
            public double averageAnswerTime { get; set; }
            public bool finishedGame { get; set; }
        }
    }
}
