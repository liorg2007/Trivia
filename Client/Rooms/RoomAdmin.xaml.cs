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

namespace Client.Rooms
{
    /// <summary>
    /// Interaction logic for RoomAdmin.xaml
    /// </summary>
    public partial class RoomAdmin : Window
    {
        private string _username;

        public RoomAdmin(string username)
        {
            InitializeComponent();
            _username = username;
        }

        /* Button events */
        private void exitPress(object sender, MouseButtonEventArgs e)
        {
            if(WaitingRoomCommands.LeaveRoom((App)Application.Current))
            {
                MainMenu window = new MainMenu(_username);
                window.Show();
            }
        }

        private void startPress(object sender, MouseButtonEventArgs e)
        {
            long startTime;
            try
            {
                startTime = WaitingRoomCommands.StartGame((App)Application.Current);
                Helper.raiseSuccessBox("Game starts at:" + startTime);
            }
            catch (Exception ex)
            {
                Helper.raiseErrorBox(ex.Message);
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
