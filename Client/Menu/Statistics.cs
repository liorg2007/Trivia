using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Text.Json;
using System.Threading.Tasks;
using static Client.Requests;
using static Client.JsonPacketDeserializer;
using static Client.DataStructs;


namespace Client.Menu
{
    static class Statistics
    {
        public static byte[] CreateStatsRequest()
        {
            return Helper.createProtocol(Code.GetPersonalStats);
        }

        public static UserStatistics GetStats(ServerResponse response)
        {
            if (response.code == 9)
            {
                UserStatistics res = DeserializeStatsResponse(response.message);
                return res;
            }

            throw new Exception("Problem with server");
        }


        public static byte[] CreateHighScoresRequest()
        {
            return Helper.createProtocol(Code.GetHighScores);
        }

        public static TopPlayers GetHighScores(ServerResponse response)
        {
            if (response.code == 8)
            {
                TopPlayers res = DeserializeHighScoresResponse(response.message);
                return res;
            }

            throw new Exception("Problem with server");
        }
    }
}
