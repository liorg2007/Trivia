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
            uint id { get; set; }
            string name { get; set; }
            uint maxPlayers { get; set; }
            uint numOfQuestionsInGame { get; set; }
            uint timerPerQuestion { get; set; }
            uint isActive { get; set; }
        }

        public struct Room
        {
            RoomData roomData { get; set; }
            List<string> players { get; set; }
        }
    }
}
