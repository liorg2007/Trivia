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
using System.Windows.Controls;
using Client.Crypto;
using System.Text.Json;
using System.Collections;

namespace Client
{
    public struct ServerData
    {
        public string ip;
        public int port;
    }

    public class Server
    {
        private NetworkStream _socket { get; set; }
        private AES_Crypt aesEncryption { get; set; }
        private bool finishedKeyExchange;

        public Server()
        {
            finishedKeyExchange = false;
            aesEncryption = new AES_Crypt();
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

        public void StartHandshake()
        {
            var rsaPublicKey = ClientHello();
            KeyExchange(rsaPublicKey);
        }

        private byte[] ClientHello()
        {
            var message = Helper.createProtocol(Code.ClientHello);
            ServerResponse response = Helper.SendMessageWithByteArr(message, (App)Application.Current);
            ClientHelloResponse data = JsonPacketDeserializer.DeserializeClientHelloResponse(response.message);

            return data.PublicKey;
        }

        private void KeyExchange(byte[] rsaPublicKey)
        {
            KeyIvPair keyIvPair = aesEncryption.GetKeyIv();

            var json = JsonSerializer.SerializeToUtf8Bytes(keyIvPair);

            var encryptedKey = RSA_Crypt.Encrypt(json, rsaPublicKey);

            var message = Helper.createProtocol(Code.KeyExchange, encryptedKey);

            sendMessage(message);

            finishedKeyExchange = true;

            receiveMessage();
        }


        public void sendMessage(byte[] buffer)
        {
            if (finishedKeyExchange)
            {
                byte[] encryptedBuffer = EncryptBuffer(buffer);

                _socket.Write(encryptedBuffer, 0, encryptedBuffer.Length);
                _socket.Flush();
            }
            else
            {
                _socket.Write(buffer, 0, buffer.Length);
                _socket.Flush();
            }
        }

        private byte[] EncryptBuffer(byte[] buffer)
        {
            byte[] encrypted = aesEncryption.Encrypt(System.Text.Encoding.ASCII.GetString(buffer));
            int msgLen = encrypted.Length;
            byte[] finalBuffer = new byte[4 + msgLen];

            finalBuffer[0] = (byte)msgLen;
            finalBuffer[1] = (byte)(msgLen >> 8);
            finalBuffer[2] = (byte)(msgLen >> 0x10);
            finalBuffer[3] = (byte)(msgLen >> 0x18);

            encrypted?.CopyTo(finalBuffer, 4);

            return finalBuffer;
        }


        public ServerResponse receiveMessage()
        {
            if(finishedKeyExchange)
                return receiveMessageEncrypted();

            return receiveMessageWithoutEncryption();
        }


        public ServerResponse receiveMessageEncrypted()
        {
            byte[] headerBuff = new byte[Helper.ENC_HEADER_LENGTH];
            _socket.Read(headerBuff, 0, Helper.ENC_HEADER_LENGTH);
            int encryptedMessageLength = BitConverter.ToInt32(headerBuff);

            byte[] encryptedBuffer = new byte[encryptedMessageLength];
            _socket.Read(encryptedBuffer, 0, encryptedMessageLength);

            byte[] decryptedBuffer = Encoding.UTF8.GetBytes(aesEncryption.Decrypt(encryptedBuffer));

            Code code = (Code)decryptedBuffer[0];

            // get string length 
            byte[] subset = new byte[4];
            Array.Copy(decryptedBuffer, 1, subset, 0, 4);
            int messageLength = BitConverter.ToInt32(subset, 0);

            string message = Encoding.ASCII.GetString(decryptedBuffer, Helper.HEADER_LENGTH, messageLength);

            return new ServerResponse() { code = code, message = message };
        }


        public ServerResponse receiveMessageWithoutEncryption()
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
