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
using static Client.Helper;
using static Client.JsonPacketDeserializer;
using Client.Menu;

namespace Client
{
    /// <summary>
    /// Interaction logic for MainMenu.xaml
    /// </summary>
    public partial class MainMenu : Window
    {
        private string _username;

        public MainMenu(string username)
        {
            InitializeComponent();
            _username = username;
            helloUserTxt.Text = "Hello " + _username;
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


        /* CLICK EVENTS */
        private void PersonalScoreClick(object sender, RoutedEventArgs e)
        {
            PersonalStats window = new PersonalStats(_username);
            window.Show();
        }

        private void BestScoresClick(object sender, RoutedEventArgs e)
        {
            BestScores window = new BestScores();
            window.Show();
        }

        private void SignoutClick(object sender, RoutedEventArgs e)
        {
            var message = Helper.createProtocol("", (int)Codes.Logout);

            ((App)Application.Current)._server.sendMessage(message);

            ServerResponse response = decodeProtocol(((App)Application.Current)._server.receiveMessage());

            if(response.code == (int)Codes.Logout + 1)
            {
                LogoutResponse res = JsonPacketDeserializer.DeserializeLogoutResponse(response.message);

                if (res.status != 1)
                    raiseErrorBox("Problem with server");
                else
                {
                    MainWindow window = new MainWindow();
                    window.Show();
                    this.Close();
                    raiseSuccessBox("Thanks for playing!");
                }
            }
        }

        private void QuitClick(object sender, RoutedEventArgs e)
        {
            string result = raiseQuestionBox("Are you sure you want to quit?");

            if (result == "Yes")
                CloseWindow(sender, e);
        }
    }
}
