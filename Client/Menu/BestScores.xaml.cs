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

            ((App)Application.Current).server.sendMessage(message);

            ServerResponse response = decodeProtocol(((App)Application.Current).server.receiveMessage());

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
            int listLength = highScores.bestScores.Count;


            for (int i = 0; i < listLength; i++)
            {
                ((ListBoxItem)champList.Items[i + 1]).Content = highScores.bestScores[i].Item1 + " - " + highScores.bestScores[i].Item2; //item1 is name item2 is score
            }
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
