using System;
using System.Collections.Generic;
using System.Linq;
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
using static Client.Requests;

namespace Client.Rooms
{
    /// <summary>
    /// Interaction logic for RoomMember.xaml
    /// </summary>
    public partial class RoomMember : Window
    {
        private string username;
        private bool ContinueBackgroundThread;
        private static Mutex mut = new Mutex();

        public RoomMember(string username)
        {
            ContinueBackgroundThread = true;
            InitializeComponent();
            this.username = username;
        }

        /* Button events */
        private void exitPress(object sender, MouseButtonEventArgs e)
        {
            if (WaitingRoomCommands.LeaveRoom((App)Application.Current))
            {
                MainMenu window = new MainMenu(username);
                window.Show();
            }
        }

        /* Get Update Thread */
        private void Background_Update_Thread()
        {
            while(ContinueBackgroundThread)
            {
                mut.WaitOne();

                if (!ContinueBackgroundThread)//check if while waiting state was changed
                    break;

                ServerResponse response = Helper.SendMessageWithCode(Code.GetRoomState, (App)Application.Current);

                if(response.code == Code.LeaveRoom)
                {
                    if (WaitingRoomCommands.GetLeaveRoomResponse(response.message))
                    {
                        MainMenu window = new MainMenu(username);
                        window.Show();
                    }
                    else
                        Helper.raiseErrorBox("can't leave room");
                }
            }
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
