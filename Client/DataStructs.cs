using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Client
{
    internal static class DataStructs
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
    }
}
