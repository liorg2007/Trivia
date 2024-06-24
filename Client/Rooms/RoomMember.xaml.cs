using System;
using System.Collections.Generic;
using System.Linq;
using System.Net.PeerToPeer.Collaboration;
using System.Net.Sockets;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;
using System.Windows.Threading;
using static Client.Requests;

namespace Client.Rooms
{
    /// <summary>
    /// Interaction logic for RoomMember.xaml
    /// </summary>
    public partial class RoomMember : Window
    {
        private string username;
        private static Mutex mut = new Mutex();
        private const int TIME_BETWEEN_UPDATES = 3000;
        private bool ContinueBackgroundThread = true;

        private DataStructs.RoomState roomState;

        public RoomMember(string username)
        {
            InitializeComponent();
            this.username = username;

            BackgroundUpdate();
        }

        /* Button events */
        void exitPress(object sender, RoutedEventArgs e)
        {
            mut.WaitOne();
            if (WaitingRoomCommands.LeaveRoom((App)Application.Current))
            {
                ContinueBackgroundThread = false;
                MainMenu window = new MainMenu(username);
                window.Show();
                this.Close();
            }
            mut.ReleaseMutex();
        }

        /* Get Update Thread */
        private async void BackgroundUpdate()
        {
            await Task.Run(async () =>
            {
                while (ContinueBackgroundThread)
                {
                    mut.WaitOne();

                    if (!ContinueBackgroundThread)//check if while waiting state was changed
                    {
                        mut.ReleaseMutex();
                        break;
                    }

                    ServerResponse response = Helper.SendMessageWithCode(Code.GetRoomState, (App)Application.Current);

                    if (response.code == Code.LeaveRoom)
                    {
                        if (WaitingRoomCommands.GetLeaveRoomResponse(response.message))
                        {
                            Application.Current.Dispatcher.Invoke(() =>
                            {
                                MainMenu window = new MainMenu(username);
                                window.Show();
                                this.Close();
                                ContinueBackgroundThread = false;
                            });
                        }
                        else
                            Helper.raiseErrorBox("can't leave room");
                    }
                    else if (response.code == Code.StartGame)
                    {
                        DateTime start_time;

                        try
                        {
                            start_time = WaitingRoomCommands.GetStartGameResponse(response.message);
                        }
                        catch (Exception ex)
                        {
                            Helper.raiseErrorBox(ex.Message);
                            continue;
                        }

                        //handle the start game
                        ContinueBackgroundThread = false;
                        WaitingRoomCommands.startGameInTime(start_time, this, gameStartText, exitButton, roomState, username);
                    }
                    else
                    {
                        roomState = WaitingRoomCommands.HandleRoomData((App)Application.Current, this, response.message)
                            ?? roomState;
                    }

                    mut.ReleaseMutex();
                    await Task.Delay(TIME_BETWEEN_UPDATES);
                }
            });
        }

        /* Default screen events*/

        private void Window_MouseDown(object sender, MouseButtonEventArgs e)
        {
            if (e.LeftButton == MouseButtonState.Pressed)
            {
                DragMove();
            }
        }

        private void CloseWindow(object sender, RoutedEventArgs e)
        {
            ((App)Application.Current).stopMusic();
            Thread.Sleep(50);
            Close();
        }

        private void MinimizeWindow(object sender, RoutedEventArgs e)
        {
            this.WindowState = WindowState.Minimized;
        }
    }
}
