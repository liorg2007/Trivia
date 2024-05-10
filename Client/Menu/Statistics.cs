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
        public static UserStatistics SendStatsRequest(Server server)
        {
            ServerResponse response = Helper.SendRequest(server, Code.GetPersonalStats);
            return GetStats(response);
        }

        private static UserStatistics GetStats(ServerResponse response)
        {
            if (response.code == Code.GetPersonalStats)
            {
                UserStatistics res = DeserializeStatsResponse(response.message);
                return res;
            }

            throw new Exception("Server returned wrong response code");
        }

        public static TopPlayers SendHighScoresRequest(Server server)
        {
            ServerResponse response = Helper.SendRequest(server, Code.GetHighScores);
            return GetHighScores(response);
        }

        private static TopPlayers GetHighScores(ServerResponse response)
        {
            if (response.code == Code.GetHighScores)
            {
                TopPlayers res = DeserializeHighScoresResponse(response.message);
                return res;
            }

            throw new Exception("Server returned wrong response code");
        }
    }
}
