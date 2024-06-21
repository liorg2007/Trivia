using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using static Client.Requests;
using static Client.DataStructs;
using System.Windows;
using System.Windows.Controls;

namespace Client.Rooms
{
    static class WaitingRoomCommands
    {
        public static bool LeaveRoom(App app)
        {
            ServerResponse response = Helper.SendMessageWithCode(Code.LeaveRoom, app);

            if (response.code == Code.LeaveRoom)
                return GetLeaveRoomResponse(response.message);

            return false;
        }

        public static bool CloseRoom(App app)
        {
            ServerResponse response = Helper.SendMessageWithCode(Code.CloseRoom, app);

            if (response.code == Code.CloseRoom)
            {
                CloseRoomResponse res = JsonPacketDeserializer.DeserializeCloseRoomResponse(response.message);

                return res.status == 1;
            }

            return false;
        }

        public static DateTime StartGame(App app)
        {
            ServerResponse response = Helper.SendMessageWithCode(Code.StartGame, app);

            if (response.code == Code.StartGame)
                return GetStartGameResponse(response.message);

            throw new Exception("Bad response");
        }

        public static RoomState GetRoomStateResponse(string message)
        {
            GetRoomStateResponse res = JsonPacketDeserializer.DeserializeGetRoomStateResponse(message);

            if (res.status != 1)
                throw new Exception("Can't get room data");
            return res.roomState;
        }

        public static DateTime GetStartGameResponse(string message)
        {
            StartGameResponse res = JsonPacketDeserializer.DeserializeStartGameResponse(message);

            if (res.status != 1)
            {
                throw new Exception("Can't start game");
            }

            DateTimeOffset utcGameStartTimeOffset = DateTimeOffset.FromUnixTimeSeconds(res.startTime);
            DateTime localGameStartTime = utcGameStartTimeOffset.ToLocalTime().DateTime;

            return localGameStartTime;

        }

        public static void startGameInTime(DateTime gameStartTime, Window currWindow, RoomState roomState)
        {
            var timeToWait = gameStartTime - DateTime.Now;
            Helper.raiseSuccessBox("Game starts in " + timeToWait.Seconds + " seconds");
            Timer timer = new Timer(o =>
            {
                Application.Current.Dispatcher.Invoke(() =>
                    {
                        QuestionWindow gameWindow = new(roomState.answerTimeout, roomState.answerCount);
                        gameWindow.Show();
                        currWindow.Close();
                    }, null, TimeSpan.Zero, timeToWait);
            });
        }

        public static bool GetLeaveRoomResponse(string message)
        {
            LeaveRoomResponse res = JsonPacketDeserializer.DeserializeLeaveRoomResponse(message);

            return res.status == 1;
        }

        public static RoomState? HandleRoomData(App app, Window window, string message)
        {
            RoomState roomState;
            try
            {
                roomState = GetRoomStateResponse(message);
            }
            catch (Exception e)
            {
                Helper.raiseErrorBox(e.Message);
                return null;
            }

            window.Dispatcher.Invoke(() =>
            {
                var listBox = (ListBox)window.FindName("PlayerList");
                if (listBox != null)
                {
                    listBox.Items.Clear();  // Clear existing items

                    foreach (var player in roomState.players)
                    {
                        var listBoxItem = new ListBoxItem
                        {
                            Content = player // Assuming player has a Name property
                        };
                        listBox.Items.Add(listBoxItem);
                    }
                }
                else
                {
                    Helper.raiseErrorBox("PlayerList ListBox not found");
                }
            });
            return roomState;
        }
    }
}
