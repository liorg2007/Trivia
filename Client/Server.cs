using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.IO;
using System.Net.Sockets;
using System.Net;

namespace Client
{
    public class Server
    {
        private NetworkStream? _socket { get; set; }
        private struct ServerData
        {
            public IPAddress ip;
            public int port;
        }

        ~Server()
        {
            _socket?.Close();
        }

        private ServerData GetServerConnData(string serverDataFileName)
        {
            var serverData = new ServerData();

            if (!File.Exists(serverDataFileName))
                throw new Exception("No " + serverDataFileName + " file!");

            string[] data = File.ReadAllLines(serverDataFileName);

            try
            {
                serverData.ip = IPAddress.Parse(data[0]);
                serverData.port = int.Parse(data[1]);
            }
            catch
            {
                throw new Exception("Can't read from config file!");
            }

            return serverData;
        }

        public bool ConnectToServer(string serverDataFileName = "serverConfig.txt")
        {
            ServerData serverData = GetServerConnData(serverDataFileName);
            using TcpClient client = new TcpClient();
            IPEndPoint serverEndPoint = new IPEndPoint(serverData.ip, serverData.port);
            try
            {
                client.Connect(serverEndPoint);
            }
            catch
            {
                return false;
            }

            _socket?.Close(); // Close previous socket before assigning a new one
            _socket = client.GetStream();

            return true;
        }

        public void sendMessage(byte[] buffer)
        {
            if (_socket == null) throw new Exception("Haven't connected to server yet");
            _socket.Write(buffer, 0, buffer.Length);
            _socket.Flush();
        }

        public byte[] receiveMessage()
        {
            if (_socket == null) throw new Exception("Haven't connected to server yet");
            byte[] data = new byte[1024];
            using MemoryStream ms = new();
            int numBytesRead;
            while ((numBytesRead = _socket.Read(data, 0, data.Length)) > 0)
            {
                ms.Write(data, 0, numBytesRead);
            }
            return ms.ToArray();
        }
    }
}
