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
using static Client.DataStructs;
using static Client.Requests;
using static System.Formats.Asn1.AsnWriter;

namespace Client.Menu
{
    /// <summary>
    /// Interaction logic for RoomCreator.xaml
    /// </summary>
    public partial class RoomCreator : Window
    {
        private string _username;


        public RoomCreator(string username)
        {
            _username = username;
            InitializeComponent();
        }


        /* BUTTON CLICKS */
        private void CancelBtn(object sender, RoutedEventArgs e)
        {
            MainMenu window = new MainMenu(_username);
            window.Show();
            this.Close();
        }

        private void CreateRoomBtn(object sender, RoutedEventArgs e)
        {
            CreateRoom();
        }

        private void CreateRoom()
        {
            
        }

        private void BoxGotFocus(object sender, RoutedEventArgs e)
        {
            if (((TextBox)sender).Text == "Room Name")
                ((TextBox)sender).Text = "";
        }

        private void BoxLostFocus(object sender, RoutedEventArgs e)
        {
            if (((TextBox)sender).Text == "")
                ((TextBox)sender).Text = "Room Name";
        }

        private void Window_MouseDown(object sender, MouseButtonEventArgs e)
        {
            if (e.LeftButton == MouseButtonState.Pressed)
            {
                DragMove();
            }
        }

        private void CloseWindow(object sender, RoutedEventArgs e)
        {
            ((App)Application.Current)._musicWorker.CancelAsync();
            Thread.Sleep(50);
            Close();
        }

        private void MinimizeWindow(object sender, RoutedEventArgs e)
        {
            this.WindowState = WindowState.Minimized;
        }
    }
}
