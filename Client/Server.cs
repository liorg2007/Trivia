using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.IO;
using System.Net.Sockets;
using System.Net;
using static Client.Requests;

namespace Client
{
    public struct ServerData
    {
        public string ip;
        public int port;
    }

    public class Server
    {
        private NetworkStream _socket {  get; set; }

        public Server()
        {

        }

        public ServerData getServerConnData()
        {
            const string serverDataFileName = "serverConfig.txt";
            var serverData = new ServerData();

            if (!File.Exists(serverDataFileName))
                throw new Exception("No " + serverDataFileName + " file!");

            string[] data = File.ReadAllLines(serverDataFileName);

            try
            {
                serverData.ip = data[0];
                serverData.port = int.Parse(data[1]);
            }
            catch
            {
                throw new Exception("Can't read from config file!");
            }

            return serverData;
        }

        public bool connectToServer(ServerData serverData)
        {
            TcpClient client = new TcpClient();
            IPEndPoint serverEndPoint = new IPEndPoint(IPAddress.Parse(serverData.ip), serverData.port);
            try
            {
                client.Connect(serverEndPoint);
            }
            catch
            {
                return false;
            }

            _socket = client.GetStream();

            return true;
        }

        public void sendMessage(byte[] buffer)
        {
            _socket.Write(buffer, 0, buffer.Length);
            _socket.Flush();
        }

        public ServerResponse receiveMessage()
        {
            byte[] headerBuff = new byte[Helper.HEADER_LENGTH];
            _socket.Read(headerBuff, 0, Helper.HEADER_LENGTH);
            Code code = (Code)headerBuff[0];
            int messageLength = BitConverter.ToInt32(headerBuff, 1);

            byte[] messageBuffer = new byte[messageLength];
            _socket.Read(messageBuffer, 0, messageLength);
            string message = Encoding.UTF8.GetString(messageBuffer);

            return new ServerResponse() { code = code, message = message };
        }
    }
}
