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
            string json = "";
            return Helper.createProtocol(json, (int)Codes.Stats);
        }

        public static UserStatistics GetStats(ServerResponse response)
        {
            if (response.code == 1)
            {
                UserStatistics res = DeserializeStatsResponse(response.message);
                return res;
            }

            throw new Exception("Problem with server");
        }
    }
}
