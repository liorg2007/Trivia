using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Client
{
    static class DataStructs
    {
        public struct UserStatistics
        {
            public double averageAnswerTime { get; set; }
            public int correctAnswers { get; set; }
            public int totalAnswers { get; set; }
            public int score { get; set; }
        }
    }
}
