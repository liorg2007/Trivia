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
using static System.Byte;
using static Client.Helper;
using static Client.Menu.Statistics;

namespace Client.Menu
{
    /// <summary>
    /// Interaction logic for BestScores.xaml
    /// </summary>
    public partial class BestScores : Window
    {
        public BestScores()
        {
            InitializeComponent();
            ShowBestScores();
        }

        public void ShowBestScores()
        {
            TopPlayers highScores = new TopPlayers();
            var message = CreateHighScoresRequest();

            ((App)Application.Current)._server.sendMessage(message);

            ServerResponse response = decodeProtocol(((App)Application.Current)._server.receiveMessage());

            try
            {
                highScores = GetHighScores(response);
            }
            catch (Exception ex)
            {
                raiseErrorBox(ex.Message);
                System.Environment.Exit(0);
            }

            //Put stats in labels
        }

        private void exitPress(object sender, RoutedEventArgs e)
        {
            this.Close();
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
