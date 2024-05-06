using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Interop;
using static Client.Requests;


namespace Client
{
    internal static class Helper
    {
        public const int HEADER_LENGTH = 5;

        public static void raiseErrorBox(string message)
        {
            MessageBoxButton button = MessageBoxButton.OK;
            MessageBoxImage icon = MessageBoxImage.Warning;
            MessageBox.Show(message, "Error", button, icon, MessageBoxResult.Yes);
        }

        public static void raiseSuccessBox(string message)
        {
            MessageBoxButton button = MessageBoxButton.OK;
            MessageBoxImage icon = MessageBoxImage.Asterisk;
            MessageBox.Show(message, "Ok", button, icon, MessageBoxResult.Yes);
        }

        public static string raiseQuestionBox(string message)
        {
            MessageBoxButton button = MessageBoxButton.YesNo;
            MessageBoxImage icon = MessageBoxImage.Question;
            var result = MessageBox.Show(message, "?", button, icon, MessageBoxResult.Yes);

            return result.ToString();
        }

        public static byte[] createProtocol(Code code, byte[]? message=null)
        {
            int msgLen = message != null ? message.Length : 0;
            byte[] buffer = new byte[HEADER_LENGTH + msgLen];

            buffer[0] = (byte)code;
            buffer[1] = (byte)msgLen;
            buffer[2] = (byte)(msgLen >> 8);
            buffer[3] = (byte)(msgLen >> 0x10);
            buffer[4] = (byte)(msgLen >> 0x18);

            message?.CopyTo(buffer, HEADER_LENGTH);

            return buffer;
        }

        public static ServerResponse decodeProtocol(byte[] buffer)
        {
            byte code = buffer[0];
            uint messageLength = BitConverter.ToUInt32(buffer, 1);

            byte[] messageBuffer = new byte[messageLength];
            Array.Copy(buffer, HEADER_LENGTH, messageBuffer, 0, messageLength);

            string message = Encoding.UTF8.GetString(messageBuffer);

            return new ServerResponse() { code = code, message = message };
        }
    }
}
